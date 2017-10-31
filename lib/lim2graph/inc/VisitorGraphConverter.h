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

#ifndef _LIM2graph_VISITORGRAPHCONVERTER_H_
#define _LIM2graph_VISITORGRAPHCONVERTER_H_

#include "lim/inc/lim.h"
#include "graph/inc/graph.h"
#include <map>

/**
* \file VisitorGraphConverter.h
* \brief Contains declaration of VisitorGraphConverter class.
*/

namespace columbus { namespace lim2graph { 
  /**
  * \brief Visitor to convert the ASG to Graph.
  */
  class VisitorGraphConverter : public lim::asg::VisitorAbstractNodes {
    public:
      /**
      * \brief Constructor for Visitor.
      * \param factory    [in] The factory of the ASG.
      * \param graph      [in] The ASG is converted into this Graph.
      * \param edges      [in] The marked edges of the ASG is also converted.
      * \param attributes [in] The marked attributes of the ASG is also converted.
      * \param variants   [in] Convert components or not.
      * \param variants   [in] Convert variants or not.
      * \param instances  [in] Convert instance nodes or not.
      */
      VisitorGraphConverter(lim::asg::Factory& factory, graph::Graph &graph, bool edges, bool attributes, bool components, bool variants, bool instances = false);

      virtual void finishVisit();

      virtual void visit(const lim::asg::base::Component& node, bool b);
      virtual void visit(const lim::asg::logical::Package& node, bool b);
      virtual void visit(const lim::asg::logical::Class& node, bool b);
      virtual void visit(const lim::asg::logical::Method& node, bool b);
      virtual void visit(const lim::asg::logical::Attribute& node, bool b);
      virtual void visit(const lim::asg::physical::FileSystem& node, bool b);



      virtual void visitMember_BelongsTo(const lim::asg::logical::Member& begin, const lim::asg::base::Component& end);
      virtual void visitScope_HasMember(const lim::asg::logical::Scope& begin, const lim::asg::logical::Member& end);
      virtual void visitEndScope_HasMember(const lim::asg::logical::Scope& begin, const lim::asg::logical::Member& end);
      virtual void visitMember_Variant(const lim::asg::logical::Member& begin, const lim::asg::logical::Member& end);
      virtual void visitMember_Aggregated(const lim::asg::logical::Member& begin, const lim::asg::logical::Member& end);
      virtual void visitMember_Declares(const lim::asg::logical::Member& begin, const lim::asg::logical::Member& end);
      virtual void visitMember_Instance(const lim::asg::logical::Member& begin, const lim::asg::logical::Member& end);
      virtual void visitFileSystem_HasFSEntry(const lim::asg::physical::FileSystem& begin, const lim::asg::physical::FSEntry& end);
      virtual void visitFolder_Contains(const lim::asg::physical::Folder& begin, const lim::asg::physical::FSEntry& end);
      virtual void visitNamed_DependsOn(const lim::asg::base::Named& begin, const lim::asg::base::Named& end, const std::string& ac);

       /**
      * \brief Function to determine the name of the node in the Graph.
      * \param node [in] The node in the ASG which name have to be determine.
      * \return Name of the node in the Graph.
      */
      static const std::string determineNodeName(const lim::asg::base::Base &node) ;

    protected:
      /**
      * \brief Converts the edges which have been collected during the traversal of the ASG.
      */
      void convertEdges();

        /**
      * \brief Function to make any special beside the generated conversion.
      * \param node  [in] The node in the ASG.
      * \param gnode [in] The converted node.
      */
      void extraConversion(const lim::asg::base::Base &node, graph::Node& gnode);

      /**
      * \brief Function to check if the conversion of the given node is needed.
      * \param node [in] The node in the ASG which has to be checked.
      * \return True in case it has to be converted, No otherwise.
      */
      bool needToConvert(const lim::asg::base::Base &node) const;

      void buildPhysicalTree(const lim::asg::base::Named& begin, const lim::asg::base::Named& end);

    protected:
      typedef std::map<NodeId, graph::Node> NodeMap;
      typedef std::set<std::pair<const lim::asg::base::Base*, const lim::asg::base::Base*> > ConvertedEdgesType;

      typedef struct edge_t {
        edge_t(NodeId fromId, NodeId toId, const std::string& edgeType, bool reverse, const std::string& edgeAttr)
          : fromId(fromId), toId(toId), edgeType(edgeType), edgeAttr(edgeAttr), reverse(reverse) {}
        NodeId fromId;
        NodeId toId;
        const std::string edgeType;
        const std::string edgeAttr;
        bool reverse;
      } edge_t;

      lim::asg::Factory& factory; // the Factory of the ASG
      graph::Graph& g; // the Graph
      bool edges;      // Convert the edges
      bool attributes; // Convert the attributes
      bool components; // Convert the components
      bool variants; // Convert the variants
      bool instances; // Convert the instance nodes
      NodeMap alreadyConverted; // Map for already converted nodes.
      ConvertedEdgesType convertedVariantEdges;
      ConvertedEdgesType convertedAggregateEdges;
      ConvertedEdgesType convertedDeclaresEdges;
      ConvertedEdgesType convertedInstanceEdges;
      ConvertedEdgesType convertedComponentEdges;
      ConvertedEdgesType convertedComponentComponentEdges;
      ConvertedEdgesType convertedDependsOnEdges;
      
      std::set<NodeId> duplicatedNodes; // Set of duplicated nodes.
      std::list<edge_t> edgesToConvert; // List of edges which need to be converted.
      graph::Node logicalRoot;
      graph::Node physicalRoot;
      std::set<NodeId> rootPackages; // Root packages
  }; // VisitorGraphConverter


}}
#endif

