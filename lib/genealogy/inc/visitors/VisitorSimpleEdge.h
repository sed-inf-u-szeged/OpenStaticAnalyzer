/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2018 Department of Software Engineering - University of Szeged
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

#ifndef _GENEALOGY_VISITORSIMPLEEDGE_H_
#define _GENEALOGY_VISITORSIMPLEEDGE_H_

#include "genealogy/inc/genealogy.h"

/**
* \file VisitorSimpleEdge.h
* \brief Contains declaration of VisitorSimpleEdge class.
*/

namespace columbus { namespace genealogy { 
  /**
  * \brief Visitor class for all edges and nodes (including abstract nodes as well).
  */
  class VisitorSimpleEdge: public Visitor {
    public:
      /**
      * \brief Virtual destructor.
      */
      virtual ~VisitorSimpleEdge();

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

      /**
      * \brief Edge  visitor for all edge which is called when the subtree of this edge is finished.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      * \param kind  [in] The kind of the association class.
      */
      virtual void visitAllEdge(const Base& begin, const Base& end) = 0;

      /**
      * \brief Edge end visitor for all edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      * \param kind  [in] The kind of the association class.
      */
      virtual void visitAllEdgeEnd(const Base& begin, const Base& end) = 0;

  }; // VisitorSimpleEdge


}}
#endif
