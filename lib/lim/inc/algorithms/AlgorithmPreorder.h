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

#ifndef _LIM_ALGORITHMPREORDER_H_
#define _LIM_ALGORITHMPREORDER_H_

#include "lim/inc/lim.h"

#include <set>

#include <list>

/**
* \file AlgorithmPreorder.h
* \brief Contains the class `AlgorithmPreorder' which implements the preorder traversal of the ASG.
* This is the visitor which when visit a node it call itself for all tree edges.
*/

namespace columbus { namespace lim { namespace asg {
  /**
  * \brief Implements the preorder traversal of the ASG.
  */
  class AlgorithmPreorder: public Algorithm , public Visitor{
    private:
      /**
      * \brief Disable copy of object.
      */
      AlgorithmPreorder(const AlgorithmPreorder&);

      /**
      * \brief Disable copy of object.
      */
      AlgorithmPreorder& operator=(const AlgorithmPreorder&);

    public:
      /**
      * \brief Constructor.
      */
      AlgorithmPreorder();

      /**
      * \brief Virtual destructor.
      */
      virtual ~AlgorithmPreorder();

      /**
      * \brief Sets that a node will be visited only once in the visiting.
      */
      void setSafeMode();

      /**
      * \brief Sets that the preorder is executed duly the graph (which means that a node can be visited more than once, even if there is a circle in the graph it will be an endless visiting).
      */
      void setUnsafeMode();

      /**
      * \brief Set visit cross edge tree.
      * \param visit [in] If visit parameter is true, cross edge trees are visited, otherwise they are not visited.
      */
      void setVisitCrossEdgeTree(bool visit);

      /**
      * \brief Set visit filtered edges.
      * \param visit [in] If visit parameter is true, filtered edges are visited, otherwise they are not visited.
      */
      void setVisitFilteredEdges(bool visit);

      /**
      * \brief Sets whether special nodes (or only used of them) are visited or not.
      * \param visit    [in] If visit parameter is true, special nodes are visited as well, otherwise they are not visited.
      * \param usedOnly [in] If usedOnly parameter is true, only those special nodes are visited that were 'used' during preorder.
      */
      void setVisitSpecialNodes(bool visit, bool usedOnly);

      /**
      * \brief Set the factory
      * \param node    [in] The preorder visits only the subtree of this node.
      */
      void setFactory(Factory& fact);

      /**
      * \brief add visitor
      * \param node    [in] The preorder visits only the subtree of this node.
      */
      void addVisitor(Visitor& visitor);

      /**
      * \brief Starts a preorder traversal which visits all nodes
      */
      void run();

      /**
      * \brief Starts a preorder traversal, recursively processing all subtres
      * \param node    [in] The preorder visits only the subtree of this node.
      */
      void run(const base::Base& node);

      /**
      * \brief Starts a preorder traversal which visits all nodes of the parameter `fact', then recursively processing all subtrees, and at every nodes call the appropriate visit function of the Visitor `visitor'
      * \param fact    [in] The factory of the ASG.
      * \param visitor [in] The visitor which is called to visit the given node or edge.
      * \deprecated  Please set the visitor with add visitor, set the factory with the set factory function
      */
      void run(const Factory& fact, Visitor& visitor);

      /**
      * \brief Starts a preorder traversal which visits all nodes of the parameter `fact' by processing the parameter `node', then recursively processing all subtrees, and at every nodes call the appropriate visit function of the Visitor `visitor'
      * \param fact    [in] The factory of the ASG.
      * \param visitor [in] The visitor which is called to visit the given node or edge.
      * \param node    [in] The preorder visits only the subtree of this node.
      * \deprecated Please set the visitor with add visitor, set the factory with the set factory function
      */
      void run(const Factory& fact, Visitor& visitor, const base::Base& node);

      /**
      * \brief Starts a preorder traversal which visits all nodes of the parameter `fact' by processing the node with the given id, then recursively processing all subtrees, and at every nodes call the appropriate visit function of the Visitor `visitor'
      * \param fact    [in] The factory of the ASG.
      * \param visitor [in] The visitor which is called to visit the given node or edge.
      * \param nodeId  [in] The preorder visits only the subtree of this node.
      * \deprecated Please set the visitor with add visitor, set the factory with the set factory function
      */
      void run(const Factory& fact, Visitor& visitor, NodeId nodeId);

      /**
      * \brief It set the edge as a tree edge
      * \param edgekind [in] The edge which will used as tree edge.
      */
      void setCrossEdgeToTraversal(EdgeKind edgekind);

      /**
      * \brief Adds the visitor to the stopped visitor set.
      * \param visitor [in] The visitor we adds.
      */
      void stop(Visitor* visitor);

      /** \internal \brief The visitor functions owerloades */
      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const base::Comment& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const base::Component& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const base::ControlFlowBlock& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const logical::Attribute& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const logical::AttributeAccess& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const logical::Class& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const logical::ClassGeneric& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const logical::ClassGenericInstance& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const logical::ClassGenericSpec& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const logical::Friendship& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const logical::GenericParameter& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const logical::Method& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const logical::MethodCall& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const logical::MethodGeneric& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const logical::MethodGenericInstance& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const logical::MethodGenericSpec& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const logical::Package& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const logical::Parameter& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const physical::File& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const physical::FileSystem& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const physical::Folder& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::SimpleType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::Type& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::TypeFormerArray& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::TypeFormerMethod& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::TypeFormerNonType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::TypeFormerPointer& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::TypeFormerType& node , bool callVirtualBase = true);

      /** \internal \brief End The visitor functions owerloades */
    protected:
      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const base::Base& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const base::Comment& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const base::Component& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const base::ControlFlowBlock& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const base::Named& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const logical::Attribute& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const logical::AttributeAccess& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const logical::Class& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const logical::ClassGeneric& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const logical::ClassGenericInstance& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const logical::ClassGenericSpec& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const logical::Friendship& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const logical::GenericParameter& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const logical::Member& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const logical::Method& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const logical::MethodCall& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const logical::MethodGeneric& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const logical::MethodGenericInstance& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const logical::MethodGenericSpec& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const logical::Package& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const logical::Parameter& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const logical::Scope& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const physical::FSEntry& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const physical::File& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const physical::FileSystem& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const physical::Folder& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::SimpleType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::Type& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::TypeFormer& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::TypeFormerArray& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::TypeFormerMethod& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::TypeFormerNonType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::TypeFormerPointer& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::TypeFormerType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief Starts a preorder traversal.
      */
      void mainRun(const Factory* fact, Visitor* visitor, const base::Base* node);

      /**
      * \internal
      * \brief Prepare for traversal. Modyficcate the filters if need it. Call the startvisit function for the all given vistor. ect.)
      */
      void startPreorder();

      /**
      * \internal
      * \brief Reset enviroment to the origal state. and call the visitFinish functions 
      */
      void endPreorder();

      /**
      * \brief Removes the stopped visitors from the visitorList. Sets the needPreorderStop true if the list becomes empty.
      */
      void clearStoppedVisitors();

      /** \internal \brief If it is true, two node are not visited during preorder. */
      bool safeMode;

      /** \internal \brief Stores the ids of the node which are already visited during the actual run. */
      std::vector<bool> visitedNodes;

      /** \internal \brief The set of ids of nodes which need to be visited. */
      std::vector<bool> unvisitedNodes;

      /** \internal \brief If it is true, it collect the sub trees. */
      bool visitCrossEdgeTree;

      /** \internal \brief If it is true, the preorder is stopped because of a visitor. */
      bool needPreorderStop;

      /** \internal \brief The set of visitors we stop in the next clearStoppedVisitors call. */
      std::set<Visitor*> stoppeds;

      /** \internal \brief Determines whether special nodes will be visited or not. */
      bool visitSpecialNodes;

      /** \internal \brief Determines whether only used special nodes will be visited or all of them. */
      bool visitUsedSpecialNodesOnly;

      bool visitFilteredEdge;

      bool originalFilterState;

      const base::Base* apRoot;

      std::list<Visitor*> visitorList;

      Factory* fact;

      bool traversaldCrossEdges[49];

  }; // AlgorithmPreorder


}}}
#endif

