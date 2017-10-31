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

#ifndef _GENEALOGY_VISITORGRAPHML_H_
#define _GENEALOGY_VISITORGRAPHML_H_

#include "genealogy/inc/genealogy.h"
#include "io/inc/GraphmlIO.h"

/**
* \file VisitorGraphml.h
* \brief Contains declaration of VisitorGraphml class.
*/

namespace columbus { namespace genealogy { 

  /**
  * \brief Exports the ASG to Graphml format.
  */
  class VisitorGraphml : public Visitor {
    public:
      typedef bool(*NodeCompareFunc)(const Base&);

      /**
      * \brief Constructor for VisitorGraphml.
      */
      VisitorGraphml(columbus::io::GraphmlIO& io, std::set< std::string>& edgeFilter, unsigned int maxDrawingDepth = 0);

      /**
      * \brief Destructor.
      */
      virtual ~VisitorGraphml();

      /**
      * \brief Give back to compare function
      */
      NodeCompareFunc getCompareFunctionToNode( std::string& nodeName);

      /**
      * \brief Create compare map
      */
      static std::map< std::string, NodeCompareFunc> create_map(){
        std::map< std::string, NodeCompareFunc> cmpTable;
        cmpTable.insert( std::make_pair( "Trackable", &Common::getIsTrackable));
        cmpTable.insert( std::make_pair( "SourceCodeElement", &Common::getIsSourceCodeElement));
        cmpTable.insert( std::make_pair( "Clone", &Common::getIsClone));
        cmpTable.insert( std::make_pair( "StructuralClone", &Common::getIsStructuralClone));
        return cmpTable;
      }

      /**
      * \brief Filter node types by matching substring in qualified name
      */
      static const std::set< std::string> getNodeTypeSet(){
        std::set< std::string> types;
        types.insert( "Base");
        types.insert( "Project");
        types.insert( "Trackable");
        types.insert( "Component");
        types.insert( "SourceCodeElement");
        types.insert( "System");
        types.insert( "Clone");
        types.insert( "StructuralClone");
        types.insert( "CloneClass");
        types.insert( "CloneInstance");
        types.insert( "DataClumpsClass");
        types.insert( "DataClumps");
        types.insert( "DataElement");
        types.insert( "SwitchStatementClass");
        types.insert( "SwitchStatement");
        types.insert( "CaseLabel");
        return types;
      }

      /** \internal \brief It contains a table to node names and compare functions */
      static const std::map< std::string, NodeCompareFunc> compareTable;

      /**
      * \brief Set startpoint
      */
      void setStartPoint( NodeId startPoint);

      /**
      * \brief Set it is white color node or not
      */
      void setIsWhiteColor( bool isWhite);

      /**
      * \brief Set it is need to grouping tree nodes or not
      */
      void setIsGroupingTreeNodes( bool groupingTreeNodes);

      /**
      * \brief Set it is enabled to draw cross edges or not
      */
      void setIsEnableCrossEdge( bool isVisitCrossEdge);

      /**
      * \brief Set node type names to show attributes only of these types 
      */
      void addToFilterNodeTypeAttributes( std::string type);

      /**
      * \brief Set node type names to filtering
      */
      void addToFilterNodeType( std::string type);

      /**
      * \brief Set node type names to filtering
      */
      void filterNodeTypeMatch( std::string pattern);

      /**
      * \brief Writes the Graphml representation of the Project node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const Project& node, bool callVirtualBase = true);

      /**
      * \brief Converts the Project node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const Project& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the Trackable node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const Trackable& node, bool callVirtualBase = true);

      /**
      * \brief Converts the Trackable node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const Trackable& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the Component node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const Component& node, bool callVirtualBase = true);

      /**
      * \brief Converts the Component node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const Component& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the SourceCodeElement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const SourceCodeElement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the SourceCodeElement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const SourceCodeElement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the System node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const System& node, bool callVirtualBase = true);

      /**
      * \brief Converts the System node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const System& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the Clone node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const Clone& node, bool callVirtualBase = true);

      /**
      * \brief Converts the Clone node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const Clone& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the StructuralClone node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const StructuralClone& node, bool callVirtualBase = true);

      /**
      * \brief Converts the StructuralClone node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const StructuralClone& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the CloneClass node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const CloneClass& node, bool callVirtualBase = true);

      /**
      * \brief Converts the CloneClass node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const CloneClass& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the CloneInstance node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const CloneInstance& node, bool callVirtualBase = true);

      /**
      * \brief Converts the CloneInstance node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const CloneInstance& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the DataClumpsClass node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const DataClumpsClass& node, bool callVirtualBase = true);

      /**
      * \brief Converts the DataClumpsClass node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const DataClumpsClass& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the DataClumps node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const DataClumps& node, bool callVirtualBase = true);

      /**
      * \brief Converts the DataClumps node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const DataClumps& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the DataElement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const DataElement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the DataElement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const DataElement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the SwitchStatementClass node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const SwitchStatementClass& node, bool callVirtualBase = true);

      /**
      * \brief Converts the SwitchStatementClass node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const SwitchStatementClass& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the SwitchStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const SwitchStatement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the SwitchStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const SwitchStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the CaseLabel node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const CaseLabel& node, bool callVirtualBase = true);

      /**
      * \brief Converts the CaseLabel node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const CaseLabel& node, bool callVirtualBase = true);

      /**
      * \brief Edge  visitor for systems edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitProject_Systems(const Project& begin, const System& end);

      /**
      * \brief Edge visitor for prev edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTrackable_Prev(const Trackable& begin, const Trackable& end);

      /**
      * \brief Edge visitor for next edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTrackable_Next(const Trackable& begin, const Trackable& end);

      /**
      * \brief Edge  visitor for components edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSystem_Components(const System& begin, const Component& end);

      /**
      * \brief Edge  visitor for cloneClasses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSystem_CloneClasses(const System& begin, const CloneClass& end);

      /**
      * \brief Edge  visitor for smells edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSystem_Smells(const System& begin, const StructuralClone& end);

      /**
      * \brief Edge visitor for next edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSystem_Next(const System& begin, const System& end);

      /**
      * \brief Edge visitor for prev edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSystem_Prev(const System& begin, const System& end);

      /**
      * \brief Edge visitor for nextNeighbours edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCloneClass_NextNeighbours(const CloneClass& begin, const CloneClass& end);

      /**
      * \brief Edge visitor for prevNeighbours edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCloneClass_PrevNeighbours(const CloneClass& begin, const CloneClass& end);

      /**
      * \brief Edge  visitor for items edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCloneClass_Items(const CloneClass& begin, const CloneInstance& end);

      /**
      * \brief Edge visitor for intersects edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCloneInstance_Intersects(const CloneInstance& begin, const CloneInstance& end);

      /**
      * \brief Edge visitor for component edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCloneInstance_Component(const CloneInstance& begin, const Component& end);

      /**
      * \brief Edge visitor for cloneClass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCloneInstance_CloneClass(const CloneInstance& begin, const CloneClass& end);

      /**
      * \brief Edge visitor for items edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDataClumpsClass_Items(const DataClumpsClass& begin, const DataClumps& end);

      /**
      * \brief Edge visitor for dataClumpsClass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDataClumps_DataClumpsClass(const DataClumps& begin, const DataClumpsClass& end);

      /**
      * \brief Edge  visitor for items edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDataClumps_Items(const DataClumps& begin, const DataElement& end);

      /**
      * \brief Edge visitor for component edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDataElement_Component(const DataElement& begin, const Component& end);

      /**
      * \brief Edge visitor for items edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchStatementClass_Items(const SwitchStatementClass& begin, const SwitchStatement& end);

      /**
      * \brief Edge visitor for switchStatementClass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchStatement_SwitchStatementClass(const SwitchStatement& begin, const SwitchStatementClass& end);

      /**
      * \brief Edge  visitor for items edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchStatement_Items(const SwitchStatement& begin, const CaseLabel& end);

      /**
      * \brief Edge visitor for component edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCaseLabel_Component(const CaseLabel& begin, const Component& end);

    protected:

      /**
      * \internal
      * \brief Converts the attributes of the Base node.
      */
      void addAttributeToContent(const Base& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the Project node.
      */
      void addAttributeToContent(const Project& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the Trackable node.
      */
      void addAttributeToContent(const Trackable& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the Component node.
      */
      void addAttributeToContent(const Component& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the SourceCodeElement node.
      */
      void addAttributeToContent(const SourceCodeElement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the System node.
      */
      void addAttributeToContent(const System& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the Clone node.
      */
      void addAttributeToContent(const Clone& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the StructuralClone node.
      */
      void addAttributeToContent(const StructuralClone& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the CloneClass node.
      */
      void addAttributeToContent(const CloneClass& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the CloneInstance node.
      */
      void addAttributeToContent(const CloneInstance& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the DataClumpsClass node.
      */
      void addAttributeToContent(const DataClumpsClass& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the DataClumps node.
      */
      void addAttributeToContent(const DataClumps& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the DataElement node.
      */
      void addAttributeToContent(const DataElement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the SwitchStatementClass node.
      */
      void addAttributeToContent(const SwitchStatementClass& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the SwitchStatement node.
      */
      void addAttributeToContent(const SwitchStatement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the CaseLabel node.
      */
      void addAttributeToContent(const CaseLabel& node, std::string& content, bool callVirtualBase);

      /** \internal \brief The ofstream into the DOT graph will be written. */
      columbus::io::GraphmlIO &io;

      /** \internal \brief Internal counter for generating edges. */
      long long edgeCounter;

    private:

      /** \internal \brief It contains ids of the drawed nodes */
      std::map< NodeId, bool> idsToDrawedNodes;

      /** \internal \brief How many edges are should be draw */
      unsigned int maxDrawingDepth;

      /** \internal \brief Edges names to filtering */
      std::set< std::string> edgeFilter;

      /** \internal \brief The contains is not enable to draw */
      std::set< NodeId> nodeFilter;

      /** \internal \brief The contains is not enable to draw */
      bool visitCrossEdge;

      /** \internal \brief It is need to draw into white */
      bool isColorWhite;

      /** \internal \brief Show attributes only of these node types. If it is empty then show all attributes. */
      std::set< std::string> nodeTypeAttributeFilter;

      /** \internal \brief Helper variable for determine is the actual node groupNode it visitEnd */
      NodeId lastVisitedNodeId;

      /** \internal \brief Helper variable for edgeKind grouping */
      std::list<EdgeKind> edgeKindStack;

      /** \internal \brief Helper variable for edgeKind grouping */
      std::list<NodeId> parentNodeStack;

      /** \internal \brief It is need to grouping tree nodes */
      bool isGroupingTreeNodes;

      /** \internal \brief Node type names to filtering out */
      std::set< std::string> nodeTypeFilter;

  }; // VisitorGraphml


}}
#endif

