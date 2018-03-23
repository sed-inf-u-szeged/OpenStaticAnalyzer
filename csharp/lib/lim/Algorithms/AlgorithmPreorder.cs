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
    using System.Collections.Generic;
    using System.Text;
    using System.Linq;

namespace Columbus.Lim.Asg.Algorithms {
    
    using Visitors;

    /// <summary>
    /// Implements the preorder traversal of the ASG.
    /// </summary>
#if (LIM_INTERNAL)
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

    /// <summary>
    /// Determines whether special nodes will be visited or not.
    /// </summary>
        private bool visitSpecialNodes;

    /// <summary>
    /// Determines whether only used special nodes will be visited or all of them.
    /// </summary>
        private bool visitUsedSpecialNodesOnly;

        private bool visitFilteredEdge;

        private bool originalFilterState;

        private Columbus.Lim.Asg.Nodes.Base.Base apRoot;

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
            visitSpecialNodes = true;
            visitUsedSpecialNodesOnly = false;
            visitFilteredEdge = false;
            originalFilterState = false;
            visitorList = new List<Visitor>();
            traversaldCrossEdges = new List<bool>();
            stoppeds = new List<Visitor>();
            for (int i = 0; i < 49; i++) {
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

        public void setVisitSpecialNodes(bool visit, bool usedOnly) {
          visitSpecialNodes = visit;
          visitUsedSpecialNodesOnly = visit && usedOnly;
        }

        public void run(Factory fact = null, Visitor visitor = null, Columbus.Lim.Asg.Nodes.Base.Base node = null) {
          mainRun(fact, visitor, node);
        }

        private void mainRun(Factory _fact, Visitor visitor, Columbus.Lim.Asg.Nodes.Base.Base node) {
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

                if (!needPreorderStop && visitSpecialNodes && !visitUsedSpecialNodesOnly) {
                    Factory.Iterator it = fact.getIterator();
                    while (it.hasNext()) {
                        Columbus.Lim.Asg.Nodes.Base.Base b = it.getNext();
                        if (!visitedNodes[(int)b.Id] && Common.getIsAPSpecNode(b)) {
                            b.accept(this);

                            if(needPreorderStop)
                                return;
                        }
                    }
                }

                if (!needPreorderStop && (visitCrossEdgeTree || visitUsedSpecialNodesOnly)) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Base.Base node, bool callFirst = true){
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Base.Comment node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Base.Base)(node),false);
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Base.Comment node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Base.Component node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Base.Named)(node),false);


            // edge: contains
            ListIterator<Columbus.Lim.Asg.Nodes.Base.Component> iteratorForcontains = node.ContainsListIteratorBegin;
            while (iteratorForcontains.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Base.Component endNodeRef = (Columbus.Lim.Asg.Nodes.Base.Component)iteratorForcontains.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitComponent_Contains(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkComponent_Contains]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndComponent_Contains(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForcontains = iteratorForcontains.getNext();
            }

            // edge: hasFiles
            ListIterator<Columbus.Lim.Asg.Nodes.Physical.File> iteratorForhasFiles = node.HasFilesListIteratorBegin;
            while (iteratorForhasFiles.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Physical.File endNodeRef = (Columbus.Lim.Asg.Nodes.Physical.File)iteratorForhasFiles.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitComponent_HasFiles(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkComponent_HasFiles]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndComponent_HasFiles(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForhasFiles = iteratorForhasFiles.getNext();
            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Base.Component node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Base.Base)(node),false);


            // edge: calls
            ListIterator<Columbus.Lim.Asg.Nodes.Logical.Method> iteratorForcalls = node.CallsListIteratorBegin;
            while (iteratorForcalls.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Logical.Method endNodeRef = (Columbus.Lim.Asg.Nodes.Logical.Method)iteratorForcalls.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitControlFlowBlock_Calls(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkControlFlowBlock_Calls]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndControlFlowBlock_Calls(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForcalls = iteratorForcalls.getNext();
            }

            // edge: pred
            ListIterator<Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock> iteratorForpred = node.PredListIteratorBegin;
            while (iteratorForpred.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock endNodeRef = (Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock)iteratorForpred.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitControlFlowBlock_Pred(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkControlFlowBlock_Pred]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndControlFlowBlock_Pred(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForpred = iteratorForpred.getNext();
            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Base.Named node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Base.Base)(node),false);


            // edge: dependsOn
            ListIteratorAssocString<Columbus.Lim.Asg.Nodes.Base.Named> iteratorFordependsOn = node.DependsOnListIteratorAssocBegin;
            while (iteratorFordependsOn.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Base.Named endNodeRef = (Columbus.Lim.Asg.Nodes.Base.Named)iteratorFordependsOn.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitNamed_DependsOn(node.Id, endNodeRef.Id, iteratorFordependsOn.getAssocItem());
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkNamed_DependsOn]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndNamed_DependsOn(node.Id, endNodeRef.Id, iteratorFordependsOn.getAssocItem());
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorFordependsOn = iteratorFordependsOn.getNext();
            }
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Logical.Attribute node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Logical.Member)(node),false);


            // edge: calls
            ListIterator<Columbus.Lim.Asg.Nodes.Logical.MethodCall> iteratorForcalls = node.CallsListIteratorBegin;
            while (iteratorForcalls.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Logical.MethodCall endNodeRef = (Columbus.Lim.Asg.Nodes.Logical.MethodCall)iteratorForcalls.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitAttribute_Calls(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkAttribute_Calls]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAttribute_Calls(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForcalls = iteratorForcalls.getNext();
            }

            // edge: hasType
            ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> iteratorForhasType = node.HasTypeListIteratorBegin;
            while (iteratorForhasType.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Type.Type endNodeRef = (Columbus.Lim.Asg.Nodes.Type.Type)iteratorForhasType.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitAttribute_HasType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkAttribute_HasType]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAttribute_HasType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForhasType = iteratorForhasType.getNext();
            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Logical.Attribute node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Logical.AttributeAccess node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Base.Base)(node),false);


            Columbus.Lim.Asg.Nodes.Base.Base genNodePtr;
            // edge: attribute
            genNodePtr = fact.getRef(node.getAttribute()) ;
            if (genNodePtr != null) {
              Columbus.Lim.Asg.Nodes.Logical.Attribute endNodeRef = (Columbus.Lim.Asg.Nodes.Logical.Attribute)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAttributeAccess_Attribute(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkAttributeAccess_Attribute]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAttributeAccess_Attribute(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Logical.AttributeAccess node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Logical.Class node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Logical.Scope)(node),false);


            // edge: grantsFriendship
            ListIterator<Columbus.Lim.Asg.Nodes.Logical.Friendship> iteratorForgrantsFriendship = node.GrantsFriendshipListIteratorBegin;
            while (iteratorForgrantsFriendship.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Logical.Friendship endNodeRef = (Columbus.Lim.Asg.Nodes.Logical.Friendship)iteratorForgrantsFriendship.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitClass_GrantsFriendship(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkClass_GrantsFriendship]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndClass_GrantsFriendship(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForgrantsFriendship = iteratorForgrantsFriendship.getNext();
            }

            // edge: isSubclass
            ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> iteratorForisSubclass = node.IsSubclassListIteratorBegin;
            while (iteratorForisSubclass.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Type.Type endNodeRef = (Columbus.Lim.Asg.Nodes.Type.Type)iteratorForisSubclass.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitClass_IsSubclass(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkClass_IsSubclass]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndClass_IsSubclass(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForisSubclass = iteratorForisSubclass.getNext();
            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Logical.Class node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Logical.ClassGeneric node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Logical.Class)(node),false);


            // edge: hasGenericParameter
            ListIterator<Columbus.Lim.Asg.Nodes.Logical.GenericParameter> iteratorForhasGenericParameter = node.HasGenericParameterListIteratorBegin;
            while (iteratorForhasGenericParameter.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Logical.GenericParameter endNodeRef = (Columbus.Lim.Asg.Nodes.Logical.GenericParameter)iteratorForhasGenericParameter.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitClassGeneric_HasGenericParameter(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef)) {
                    unvisitedNodes[(int)endNodeRef.Id] = true;
                  } else {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndClassGeneric_HasGenericParameter(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForhasGenericParameter = iteratorForhasGenericParameter.getNext();
            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Logical.ClassGeneric node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Logical.Class)(node),false);


            // edge: hasArguments
            ListIteratorAssocTypeArgumentConstraintKind<Columbus.Lim.Asg.Nodes.Type.Type> iteratorForhasArguments = node.HasArgumentsListIteratorAssocBegin;
            while (iteratorForhasArguments.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Type.Type endNodeRef = (Columbus.Lim.Asg.Nodes.Type.Type)iteratorForhasArguments.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitClassGenericInstance_HasArguments(node.Id, endNodeRef.Id, iteratorForhasArguments.getAssocItem());
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkClassGenericInstance_HasArguments]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndClassGenericInstance_HasArguments(node.Id, endNodeRef.Id, iteratorForhasArguments.getAssocItem());
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForhasArguments = iteratorForhasArguments.getNext();
            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Logical.ClassGenericSpec node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Logical.ClassGeneric)(node),false);


            // edge: hasArguments
            ListIteratorAssocTypeArgumentConstraintKind<Columbus.Lim.Asg.Nodes.Type.Type> iteratorForhasArguments = node.HasArgumentsListIteratorAssocBegin;
            while (iteratorForhasArguments.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Type.Type endNodeRef = (Columbus.Lim.Asg.Nodes.Type.Type)iteratorForhasArguments.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitClassGenericSpec_HasArguments(node.Id, endNodeRef.Id, iteratorForhasArguments.getAssocItem());
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkClassGenericSpec_HasArguments]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndClassGenericSpec_HasArguments(node.Id, endNodeRef.Id, iteratorForhasArguments.getAssocItem());
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForhasArguments = iteratorForhasArguments.getNext();
            }

            Columbus.Lim.Asg.Nodes.Base.Base genNodePtr;
            // edge: specialize
            genNodePtr = fact.getRef(node.getSpecialize()) ;
            if (genNodePtr != null) {
              Columbus.Lim.Asg.Nodes.Logical.ClassGeneric endNodeRef = (Columbus.Lim.Asg.Nodes.Logical.ClassGeneric)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitClassGenericSpec_Specialize(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkClassGenericSpec_Specialize]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndClassGenericSpec_Specialize(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Logical.ClassGenericSpec node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Logical.Friendship node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Base.Base)(node),false);


            Columbus.Lim.Asg.Nodes.Base.Base genNodePtr;
            // edge: friend
            genNodePtr = fact.getRef(node.getFriend()) ;
            if (genNodePtr != null) {
              Columbus.Lim.Asg.Nodes.Logical.Scope endNodeRef = (Columbus.Lim.Asg.Nodes.Logical.Scope)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitFriendship_Friend(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkFriendship_Friend]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndFriendship_Friend(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Logical.Friendship node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Logical.GenericParameter node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Base.Named)(node),false);


            // edge: hasParameterConstraint
            ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> iteratorForhasParameterConstraint = node.HasParameterConstraintListIteratorBegin;
            while (iteratorForhasParameterConstraint.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Type.Type endNodeRef = (Columbus.Lim.Asg.Nodes.Type.Type)iteratorForhasParameterConstraint.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitGenericParameter_HasParameterConstraint(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkGenericParameter_HasParameterConstraint]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndGenericParameter_HasParameterConstraint(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForhasParameterConstraint = iteratorForhasParameterConstraint.getNext();
            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Logical.GenericParameter node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Logical.Member node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Base.Named)(node),false);


            Columbus.Lim.Asg.Nodes.Base.Base genNodePtr;
            // edge: aggregated
            genNodePtr = fact.getRef(node.getAggregated()) ;
            if (genNodePtr != null) {
              Columbus.Lim.Asg.Nodes.Logical.Member endNodeRef = (Columbus.Lim.Asg.Nodes.Logical.Member)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitMember_Aggregated(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMember_Aggregated]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMember_Aggregated(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: belongsTo
            ListIterator<Columbus.Lim.Asg.Nodes.Base.Component> iteratorForbelongsTo = node.BelongsToListIteratorBegin;
            while (iteratorForbelongsTo.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Base.Component endNodeRef = (Columbus.Lim.Asg.Nodes.Base.Component)iteratorForbelongsTo.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitMember_BelongsTo(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMember_BelongsTo]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMember_BelongsTo(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForbelongsTo = iteratorForbelongsTo.getNext();
            }

            // edge: compilationUnit
            ListIterator<Columbus.Lim.Asg.Nodes.Physical.File> iteratorForcompilationUnit = node.CompilationUnitListIteratorBegin;
            while (iteratorForcompilationUnit.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Physical.File endNodeRef = (Columbus.Lim.Asg.Nodes.Physical.File)iteratorForcompilationUnit.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitMember_CompilationUnit(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMember_CompilationUnit]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMember_CompilationUnit(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForcompilationUnit = iteratorForcompilationUnit.getNext();
            }

            // edge: declares
            genNodePtr = fact.getRef(node.getDeclares()) ;
            if (genNodePtr != null) {
              Columbus.Lim.Asg.Nodes.Logical.Member endNodeRef = (Columbus.Lim.Asg.Nodes.Logical.Member)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitMember_Declares(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMember_Declares]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMember_Declares(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: hasComment
            ListIterator<Columbus.Lim.Asg.Nodes.Base.Comment> iteratorForhasComment = node.HasCommentListIteratorBegin;
            while (iteratorForhasComment.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Base.Comment endNodeRef = (Columbus.Lim.Asg.Nodes.Base.Comment)iteratorForhasComment.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitMember_HasComment(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMember_HasComment]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMember_HasComment(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForhasComment = iteratorForhasComment.getNext();
            }

            // edge: instance
            ListIterator<Columbus.Lim.Asg.Nodes.Logical.Member> iteratorForinstance = node.InstanceListIteratorBegin;
            while (iteratorForinstance.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Logical.Member endNodeRef = (Columbus.Lim.Asg.Nodes.Logical.Member)iteratorForinstance.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitMember_Instance(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMember_Instance]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMember_Instance(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForinstance = iteratorForinstance.getNext();
            }

            // edge: isContainedIn
            ListIteratorAssocSourcePosition<Columbus.Lim.Asg.Nodes.Physical.File> iteratorForisContainedIn = node.IsContainedInListIteratorAssocBegin;
            while (iteratorForisContainedIn.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Physical.File endNodeRef = (Columbus.Lim.Asg.Nodes.Physical.File)iteratorForisContainedIn.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitMember_IsContainedIn(node.Id, endNodeRef.Id, iteratorForisContainedIn.getAssocItem());
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMember_IsContainedIn]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMember_IsContainedIn(node.Id, endNodeRef.Id, iteratorForisContainedIn.getAssocItem());
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForisContainedIn = iteratorForisContainedIn.getNext();
            }

            // edge: languageVariant
            genNodePtr = fact.getRef(node.getLanguageVariant()) ;
            if (genNodePtr != null) {
              Columbus.Lim.Asg.Nodes.Logical.Member endNodeRef = (Columbus.Lim.Asg.Nodes.Logical.Member)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitMember_LanguageVariant(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMember_LanguageVariant]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMember_LanguageVariant(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: uses
            ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> iteratorForuses = node.UsesListIteratorBegin;
            while (iteratorForuses.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Type.Type endNodeRef = (Columbus.Lim.Asg.Nodes.Type.Type)iteratorForuses.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitMember_Uses(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMember_Uses]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMember_Uses(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForuses = iteratorForuses.getNext();
            }

            // edge: variant
            ListIterator<Columbus.Lim.Asg.Nodes.Logical.Member> iteratorForvariant = node.VariantListIteratorBegin;
            while (iteratorForvariant.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Logical.Member endNodeRef = (Columbus.Lim.Asg.Nodes.Logical.Member)iteratorForvariant.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitMember_Variant(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMember_Variant]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMember_Variant(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForvariant = iteratorForvariant.getNext();
            }
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Logical.Method node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Logical.Scope)(node),false);


            // edge: accessesAttribute
            ListIterator<Columbus.Lim.Asg.Nodes.Logical.AttributeAccess> iteratorForaccessesAttribute = node.AccessesAttributeListIteratorBegin;
            while (iteratorForaccessesAttribute.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Logical.AttributeAccess endNodeRef = (Columbus.Lim.Asg.Nodes.Logical.AttributeAccess)iteratorForaccessesAttribute.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitMethod_AccessesAttribute(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMethod_AccessesAttribute]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMethod_AccessesAttribute(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForaccessesAttribute = iteratorForaccessesAttribute.getNext();
            }

            // edge: calls
            ListIterator<Columbus.Lim.Asg.Nodes.Logical.MethodCall> iteratorForcalls = node.CallsListIteratorBegin;
            while (iteratorForcalls.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Logical.MethodCall endNodeRef = (Columbus.Lim.Asg.Nodes.Logical.MethodCall)iteratorForcalls.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitMethod_Calls(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMethod_Calls]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMethod_Calls(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForcalls = iteratorForcalls.getNext();
            }

            // edge: canThrow
            ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> iteratorForcanThrow = node.CanThrowListIteratorBegin;
            while (iteratorForcanThrow.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Type.Type endNodeRef = (Columbus.Lim.Asg.Nodes.Type.Type)iteratorForcanThrow.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitMethod_CanThrow(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMethod_CanThrow]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMethod_CanThrow(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForcanThrow = iteratorForcanThrow.getNext();
            }

            // edge: hasControlFlowBlock
            ListIterator<Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock> iteratorForhasControlFlowBlock = node.HasControlFlowBlockListIteratorBegin;
            while (iteratorForhasControlFlowBlock.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock endNodeRef = (Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock)iteratorForhasControlFlowBlock.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitMethod_HasControlFlowBlock(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef)) {
                    unvisitedNodes[(int)endNodeRef.Id] = true;
                  } else {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMethod_HasControlFlowBlock(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForhasControlFlowBlock = iteratorForhasControlFlowBlock.getNext();
            }

            // edge: hasParameter
            ListIterator<Columbus.Lim.Asg.Nodes.Logical.Parameter> iteratorForhasParameter = node.HasParameterListIteratorBegin;
            while (iteratorForhasParameter.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Logical.Parameter endNodeRef = (Columbus.Lim.Asg.Nodes.Logical.Parameter)iteratorForhasParameter.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitMethod_HasParameter(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef)) {
                    unvisitedNodes[(int)endNodeRef.Id] = true;
                  } else {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMethod_HasParameter(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForhasParameter = iteratorForhasParameter.getNext();
            }

            // edge: instantiates
            ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> iteratorForinstantiates = node.InstantiatesListIteratorBegin;
            while (iteratorForinstantiates.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Type.Type endNodeRef = (Columbus.Lim.Asg.Nodes.Type.Type)iteratorForinstantiates.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitMethod_Instantiates(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMethod_Instantiates]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMethod_Instantiates(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForinstantiates = iteratorForinstantiates.getNext();
            }

            // edge: returns
            ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> iteratorForreturns = node.ReturnsListIteratorBegin;
            while (iteratorForreturns.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Type.Type endNodeRef = (Columbus.Lim.Asg.Nodes.Type.Type)iteratorForreturns.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitMethod_Returns(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMethod_Returns]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMethod_Returns(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForreturns = iteratorForreturns.getNext();
            }

            // edge: throws
            ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> iteratorForthrows = node.ThrowsListIteratorBegin;
            while (iteratorForthrows.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Type.Type endNodeRef = (Columbus.Lim.Asg.Nodes.Type.Type)iteratorForthrows.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitMethod_Throws(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMethod_Throws]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMethod_Throws(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForthrows = iteratorForthrows.getNext();
            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Logical.Method node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Logical.MethodCall node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Base.Base)(node),false);


            Columbus.Lim.Asg.Nodes.Base.Base genNodePtr;
            // edge: method
            genNodePtr = fact.getRef(node.getMethod()) ;
            if (genNodePtr != null) {
              Columbus.Lim.Asg.Nodes.Logical.Method endNodeRef = (Columbus.Lim.Asg.Nodes.Logical.Method)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitMethodCall_Method(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMethodCall_Method]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMethodCall_Method(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Logical.MethodCall node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Logical.MethodGeneric node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Logical.Method)(node),false);


            // edge: hasGenericParameter
            ListIterator<Columbus.Lim.Asg.Nodes.Logical.GenericParameter> iteratorForhasGenericParameter = node.HasGenericParameterListIteratorBegin;
            while (iteratorForhasGenericParameter.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Logical.GenericParameter endNodeRef = (Columbus.Lim.Asg.Nodes.Logical.GenericParameter)iteratorForhasGenericParameter.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitMethodGeneric_HasGenericParameter(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef)) {
                    unvisitedNodes[(int)endNodeRef.Id] = true;
                  } else {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMethodGeneric_HasGenericParameter(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForhasGenericParameter = iteratorForhasGenericParameter.getNext();
            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Logical.MethodGeneric node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Logical.MethodGenericInstance node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Logical.Method)(node),false);


            // edge: hasArguments
            ListIteratorAssocTypeArgumentConstraintKind<Columbus.Lim.Asg.Nodes.Type.Type> iteratorForhasArguments = node.HasArgumentsListIteratorAssocBegin;
            while (iteratorForhasArguments.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Type.Type endNodeRef = (Columbus.Lim.Asg.Nodes.Type.Type)iteratorForhasArguments.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitMethodGenericInstance_HasArguments(node.Id, endNodeRef.Id, iteratorForhasArguments.getAssocItem());
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMethodGenericInstance_HasArguments]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMethodGenericInstance_HasArguments(node.Id, endNodeRef.Id, iteratorForhasArguments.getAssocItem());
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForhasArguments = iteratorForhasArguments.getNext();
            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Logical.MethodGenericInstance node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Logical.MethodGenericSpec node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Logical.MethodGeneric)(node),false);


            // edge: hasArguments
            ListIteratorAssocTypeArgumentConstraintKind<Columbus.Lim.Asg.Nodes.Type.Type> iteratorForhasArguments = node.HasArgumentsListIteratorAssocBegin;
            while (iteratorForhasArguments.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Type.Type endNodeRef = (Columbus.Lim.Asg.Nodes.Type.Type)iteratorForhasArguments.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitMethodGenericSpec_HasArguments(node.Id, endNodeRef.Id, iteratorForhasArguments.getAssocItem());
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMethodGenericSpec_HasArguments]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMethodGenericSpec_HasArguments(node.Id, endNodeRef.Id, iteratorForhasArguments.getAssocItem());
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForhasArguments = iteratorForhasArguments.getNext();
            }

            Columbus.Lim.Asg.Nodes.Base.Base genNodePtr;
            // edge: specialize
            genNodePtr = fact.getRef(node.getSpecialize()) ;
            if (genNodePtr != null) {
              Columbus.Lim.Asg.Nodes.Logical.MethodGeneric endNodeRef = (Columbus.Lim.Asg.Nodes.Logical.MethodGeneric)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitMethodGenericSpec_Specialize(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkMethodGenericSpec_Specialize]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMethodGenericSpec_Specialize(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Logical.MethodGenericSpec node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Logical.Package node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Logical.Scope)(node),false);
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Logical.Package node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Logical.Parameter node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Base.Named)(node),false);


            Columbus.Lim.Asg.Nodes.Base.Base genNodePtr;
            // edge: hasType
            genNodePtr = fact.getRef(node.getHasType()) ;
            if (genNodePtr != null) {
              Columbus.Lim.Asg.Nodes.Type.Type endNodeRef = (Columbus.Lim.Asg.Nodes.Type.Type)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitParameter_HasType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkParameter_HasType]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndParameter_HasType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Logical.Parameter node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Logical.Scope node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Logical.Member)(node),false);


            // edge: hasMember
            ListIterator<Columbus.Lim.Asg.Nodes.Logical.Member> iteratorForhasMember = node.HasMemberListIteratorBegin;
            while (iteratorForhasMember.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Logical.Member endNodeRef = (Columbus.Lim.Asg.Nodes.Logical.Member)iteratorForhasMember.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitScope_HasMember(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkScope_HasMember]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndScope_HasMember(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForhasMember = iteratorForhasMember.getNext();
            }
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Physical.FSEntry node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Base.Named)(node),false);
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Physical.File node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Physical.FSEntry)(node),false);


            // edge: hasComment
            ListIterator<Columbus.Lim.Asg.Nodes.Base.Comment> iteratorForhasComment = node.HasCommentListIteratorBegin;
            while (iteratorForhasComment.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Base.Comment endNodeRef = (Columbus.Lim.Asg.Nodes.Base.Comment)iteratorForhasComment.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitFile_HasComment(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkFile_HasComment]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndFile_HasComment(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForhasComment = iteratorForhasComment.getNext();
            }

            // edge: includes
            ListIterator<Columbus.Lim.Asg.Nodes.Physical.File> iteratorForincludes = node.IncludesListIteratorBegin;
            while (iteratorForincludes.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Physical.File endNodeRef = (Columbus.Lim.Asg.Nodes.Physical.File)iteratorForincludes.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitFile_Includes(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkFile_Includes]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndFile_Includes(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForincludes = iteratorForincludes.getNext();
            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Physical.File node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Physical.FileSystem node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Base.Named)(node),false);


            // edge: hasFSEntry
            ListIterator<Columbus.Lim.Asg.Nodes.Physical.FSEntry> iteratorForhasFSEntry = node.HasFSEntryListIteratorBegin;
            while (iteratorForhasFSEntry.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Physical.FSEntry endNodeRef = (Columbus.Lim.Asg.Nodes.Physical.FSEntry)iteratorForhasFSEntry.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitFileSystem_HasFSEntry(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef)) {
                    unvisitedNodes[(int)endNodeRef.Id] = true;
                  } else {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndFileSystem_HasFSEntry(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForhasFSEntry = iteratorForhasFSEntry.getNext();
            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Physical.FileSystem node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Physical.Folder node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Physical.FSEntry)(node),false);


            // edge: contains
            ListIterator<Columbus.Lim.Asg.Nodes.Physical.FSEntry> iteratorForcontains = node.ContainsListIteratorBegin;
            while (iteratorForcontains.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Physical.FSEntry endNodeRef = (Columbus.Lim.Asg.Nodes.Physical.FSEntry)iteratorForcontains.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitFolder_Contains(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef)) {
                    unvisitedNodes[(int)endNodeRef.Id] = true;
                  } else {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndFolder_Contains(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForcontains = iteratorForcontains.getNext();
            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Physical.Folder node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Type.SimpleType node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Base.Base)(node),false);
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Type.SimpleType node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Type.Type node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Base.Base)(node),false);


            // edge: hasTypeFormer
            ListIterator<Columbus.Lim.Asg.Nodes.Type.TypeFormer> iteratorForhasTypeFormer = node.HasTypeFormerListIteratorBegin;
            while (iteratorForhasTypeFormer.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Type.TypeFormer endNodeRef = (Columbus.Lim.Asg.Nodes.Type.TypeFormer)iteratorForhasTypeFormer.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitType_HasTypeFormer(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkType_HasTypeFormer]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndType_HasTypeFormer(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForhasTypeFormer = iteratorForhasTypeFormer.getNext();
            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Type.Type node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Type.TypeFormer node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Base.Base)(node),false);
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Type.TypeFormerArray node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Type.TypeFormer)(node),false);
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerArray node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Type.TypeFormer)(node),false);


            // edge: hasParameterType
            ListIteratorAssocParameterKind<Columbus.Lim.Asg.Nodes.Type.Type> iteratorForhasParameterType = node.HasParameterTypeListIteratorAssocBegin;
            while (iteratorForhasParameterType.getValue() != null) {
               Columbus.Lim.Asg.Nodes.Type.Type endNodeRef = (Columbus.Lim.Asg.Nodes.Type.Type)iteratorForhasParameterType.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitTypeFormerMethod_HasParameterType(node.Id, endNodeRef.Id, iteratorForhasParameterType.getAssocItem());
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkTypeFormerMethod_HasParameterType]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTypeFormerMethod_HasParameterType(node.Id, endNodeRef.Id, iteratorForhasParameterType.getAssocItem());
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForhasParameterType = iteratorForhasParameterType.getNext();
            }

            Columbus.Lim.Asg.Nodes.Base.Base genNodePtr;
            // edge: hasReturnType
            genNodePtr = fact.getRef(node.getHasReturnType()) ;
            if (genNodePtr != null) {
              Columbus.Lim.Asg.Nodes.Type.Type endNodeRef = (Columbus.Lim.Asg.Nodes.Type.Type)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitTypeFormerMethod_HasReturnType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkTypeFormerMethod_HasReturnType]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTypeFormerMethod_HasReturnType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Type.TypeFormerNonType node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Type.TypeFormer)(node),false);
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerNonType node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Type.TypeFormerPointer node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Type.TypeFormer)(node),false);
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerPointer node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
        public void visitAllEdges(Columbus.Lim.Asg.Nodes.Type.TypeFormerType node, bool callFirst = true){
            visitAllEdges((Columbus.Lim.Asg.Nodes.Type.TypeFormer)(node),false);


            Columbus.Lim.Asg.Nodes.Base.Base genNodePtr;
            // edge: refersTo
            genNodePtr = fact.getRef(node.getRefersTo()) ;
            if (genNodePtr != null) {
              Columbus.Lim.Asg.Nodes.Base.Base endNodeRef = genNodePtr;
              foreach (var visitor in visitorList) {
                visitor.visitTypeFormerType_RefersTo(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(endNodeRef))) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkTypeFormerType_RefersTo]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTypeFormerType_RefersTo(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerType node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
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
            throw new LimException("", "Factory is null");
          }

          if (visitorList.Count <= 0){
            throw new LimException("", "Visitor array size 0");
          }

          if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
            visitedNodes.Clear();
            for (int i = 0; i < fact.Size; i++){
                visitedNodes.Add(false);
            }
          }

          if (visitCrossEdgeTree || visitSpecialNodes) {
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
