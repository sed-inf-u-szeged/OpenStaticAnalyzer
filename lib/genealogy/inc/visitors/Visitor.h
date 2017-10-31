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

#ifndef _GENEALOGY_VISITOR_H_
#define _GENEALOGY_VISITOR_H_

#include "genealogy/inc/genealogy.h"

/**
* \file Visitor.h
* \brief Contains declaration of Visitor class.
*/

namespace columbus { namespace genealogy { 
  /**
  * \brief Visitor for each non-abstract nodes and all edges of the graph.
  */
  class Visitor {
    public:
      /**
      * \brief Constructor for Visitor.
      */
      Visitor();

      /**
      * \brief Destructor.
      */
      virtual ~Visitor();

      /**
      * \brief Gives back the the actual position's depth in the ASG.
      * \return The depth of the actual position.
      */
      unsigned getDepth() const;

      /**
      * \brief Increasing the depth by one in the ASG.
      */
      void incDepth();

      /**
      * \brief Decreasing the depth by one in the ASG.
      */
      void decDepth();

      /**
      * \brief This function is calling before the beginning of visiting process.
      */
      virtual void beginVisit();

      /**
      * \brief This function is calling when the visiting process has finished.
      */
      virtual void finishVisit();

      /**
      * \brief Visitor which is called at the beginning of the Project node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const Project& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the Project node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const Project& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the Trackable node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const Trackable& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the Trackable node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const Trackable& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the Component node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const Component& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the Component node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const Component& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the SourceCodeElement node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const SourceCodeElement& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the SourceCodeElement node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const SourceCodeElement& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the System node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const System& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the System node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const System& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the Clone node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const Clone& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the Clone node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const Clone& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the StructuralClone node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const StructuralClone& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the StructuralClone node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const StructuralClone& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the CloneClass node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const CloneClass& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the CloneClass node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const CloneClass& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the CloneInstance node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const CloneInstance& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the CloneInstance node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const CloneInstance& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the DataClumpsClass node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const DataClumpsClass& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the DataClumpsClass node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const DataClumpsClass& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the DataClumps node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const DataClumps& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the DataClumps node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const DataClumps& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the DataElement node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const DataElement& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the DataElement node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const DataElement& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the SwitchStatementClass node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const SwitchStatementClass& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the SwitchStatementClass node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const SwitchStatementClass& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the SwitchStatement node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const SwitchStatement& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the SwitchStatement node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const SwitchStatement& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the CaseLabel node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const CaseLabel& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the CaseLabel node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const CaseLabel& node , bool callVirtualBase = true);

      /**
      * \brief Edge  visitor for systems edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitProject_Systems(const Project& begin, const System& end);

      /**
      * \brief Edge end visitor for systems edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndProject_Systems(const Project& begin, const System& end);

      /**
      * \brief Edge visitor for prev edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTrackable_Prev(const Trackable& begin, const Trackable& end);

      /**
      * \brief Edge visitor for prev edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTrackable_Prev(const Trackable& begin, const Trackable& end);

      /**
      * \brief Edge visitor for next edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTrackable_Next(const Trackable& begin, const Trackable& end);

      /**
      * \brief Edge visitor for next edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTrackable_Next(const Trackable& begin, const Trackable& end);

      /**
      * \brief Edge  visitor for components edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSystem_Components(const System& begin, const Component& end);

      /**
      * \brief Edge end visitor for components edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSystem_Components(const System& begin, const Component& end);

      /**
      * \brief Edge  visitor for cloneClasses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSystem_CloneClasses(const System& begin, const CloneClass& end);

      /**
      * \brief Edge end visitor for cloneClasses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSystem_CloneClasses(const System& begin, const CloneClass& end);

      /**
      * \brief Edge  visitor for smells edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSystem_Smells(const System& begin, const StructuralClone& end);

      /**
      * \brief Edge end visitor for smells edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSystem_Smells(const System& begin, const StructuralClone& end);

      /**
      * \brief Edge visitor for next edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSystem_Next(const System& begin, const System& end);

      /**
      * \brief Edge visitor for next edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSystem_Next(const System& begin, const System& end);

      /**
      * \brief Edge visitor for prev edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSystem_Prev(const System& begin, const System& end);

      /**
      * \brief Edge visitor for prev edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSystem_Prev(const System& begin, const System& end);

      /**
      * \brief Edge visitor for nextNeighbours edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCloneClass_NextNeighbours(const CloneClass& begin, const CloneClass& end);

      /**
      * \brief Edge visitor for nextNeighbours edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCloneClass_NextNeighbours(const CloneClass& begin, const CloneClass& end);

      /**
      * \brief Edge visitor for prevNeighbours edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCloneClass_PrevNeighbours(const CloneClass& begin, const CloneClass& end);

      /**
      * \brief Edge visitor for prevNeighbours edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCloneClass_PrevNeighbours(const CloneClass& begin, const CloneClass& end);

      /**
      * \brief Edge  visitor for items edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCloneClass_Items(const CloneClass& begin, const CloneInstance& end);

      /**
      * \brief Edge end visitor for items edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCloneClass_Items(const CloneClass& begin, const CloneInstance& end);

      /**
      * \brief Edge visitor for intersects edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCloneInstance_Intersects(const CloneInstance& begin, const CloneInstance& end);

      /**
      * \brief Edge visitor for intersects edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCloneInstance_Intersects(const CloneInstance& begin, const CloneInstance& end);

      /**
      * \brief Edge visitor for component edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCloneInstance_Component(const CloneInstance& begin, const Component& end);

      /**
      * \brief Edge visitor for component edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCloneInstance_Component(const CloneInstance& begin, const Component& end);

      /**
      * \brief Edge visitor for cloneClass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCloneInstance_CloneClass(const CloneInstance& begin, const CloneClass& end);

      /**
      * \brief Edge visitor for cloneClass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCloneInstance_CloneClass(const CloneInstance& begin, const CloneClass& end);

      /**
      * \brief Edge visitor for items edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDataClumpsClass_Items(const DataClumpsClass& begin, const DataClumps& end);

      /**
      * \brief Edge visitor for items edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDataClumpsClass_Items(const DataClumpsClass& begin, const DataClumps& end);

      /**
      * \brief Edge visitor for dataClumpsClass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDataClumps_DataClumpsClass(const DataClumps& begin, const DataClumpsClass& end);

      /**
      * \brief Edge visitor for dataClumpsClass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDataClumps_DataClumpsClass(const DataClumps& begin, const DataClumpsClass& end);

      /**
      * \brief Edge  visitor for items edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDataClumps_Items(const DataClumps& begin, const DataElement& end);

      /**
      * \brief Edge end visitor for items edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDataClumps_Items(const DataClumps& begin, const DataElement& end);

      /**
      * \brief Edge visitor for component edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDataElement_Component(const DataElement& begin, const Component& end);

      /**
      * \brief Edge visitor for component edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDataElement_Component(const DataElement& begin, const Component& end);

      /**
      * \brief Edge visitor for items edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchStatementClass_Items(const SwitchStatementClass& begin, const SwitchStatement& end);

      /**
      * \brief Edge visitor for items edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSwitchStatementClass_Items(const SwitchStatementClass& begin, const SwitchStatement& end);

      /**
      * \brief Edge visitor for switchStatementClass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchStatement_SwitchStatementClass(const SwitchStatement& begin, const SwitchStatementClass& end);

      /**
      * \brief Edge visitor for switchStatementClass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSwitchStatement_SwitchStatementClass(const SwitchStatement& begin, const SwitchStatementClass& end);

      /**
      * \brief Edge  visitor for items edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchStatement_Items(const SwitchStatement& begin, const CaseLabel& end);

      /**
      * \brief Edge end visitor for items edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSwitchStatement_Items(const SwitchStatement& begin, const CaseLabel& end);

      /**
      * \brief Edge visitor for component edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCaseLabel_Component(const CaseLabel& begin, const Component& end);

      /**
      * \brief Edge visitor for component edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCaseLabel_Component(const CaseLabel& begin, const Component& end);

    protected:
      /** \internal \brief Stores the depth position in the ASG. */
      unsigned depth;
  }; // Visitor


}}
#endif

