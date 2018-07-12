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

#include "genealogy/inc/genealogy.h"

/**
* \file VisitorSimpleEdge.cpp
* \brief Contains declaration of VisitorSimpleEdge class.
*/

namespace columbus { namespace genealogy { 
      VisitorSimpleEdge::~VisitorSimpleEdge(){};

      /**
      * \brief Edge  visitor for systems edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitProject_Systems(const Project& begin, const System& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for systems edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndProject_Systems(const Project& begin, const System& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for prev edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTrackable_Prev(const Trackable& begin, const Trackable& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for prev edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTrackable_Prev(const Trackable& begin, const Trackable& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for next edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTrackable_Next(const Trackable& begin, const Trackable& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for next edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTrackable_Next(const Trackable& begin, const Trackable& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for components edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSystem_Components(const System& begin, const Component& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for components edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSystem_Components(const System& begin, const Component& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for cloneClasses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSystem_CloneClasses(const System& begin, const CloneClass& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for cloneClasses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSystem_CloneClasses(const System& begin, const CloneClass& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for smells edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSystem_Smells(const System& begin, const StructuralClone& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for smells edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSystem_Smells(const System& begin, const StructuralClone& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for next edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSystem_Next(const System& begin, const System& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for next edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSystem_Next(const System& begin, const System& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for prev edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSystem_Prev(const System& begin, const System& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for prev edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSystem_Prev(const System& begin, const System& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for nextNeighbours edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCloneClass_NextNeighbours(const CloneClass& begin, const CloneClass& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for nextNeighbours edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCloneClass_NextNeighbours(const CloneClass& begin, const CloneClass& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for prevNeighbours edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCloneClass_PrevNeighbours(const CloneClass& begin, const CloneClass& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for prevNeighbours edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCloneClass_PrevNeighbours(const CloneClass& begin, const CloneClass& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for items edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCloneClass_Items(const CloneClass& begin, const CloneInstance& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for items edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCloneClass_Items(const CloneClass& begin, const CloneInstance& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for intersects edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCloneInstance_Intersects(const CloneInstance& begin, const CloneInstance& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for intersects edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCloneInstance_Intersects(const CloneInstance& begin, const CloneInstance& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for component edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCloneInstance_Component(const CloneInstance& begin, const Component& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for component edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCloneInstance_Component(const CloneInstance& begin, const Component& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for cloneClass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCloneInstance_CloneClass(const CloneInstance& begin, const CloneClass& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for cloneClass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCloneInstance_CloneClass(const CloneInstance& begin, const CloneClass& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for items edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDataClumpsClass_Items(const DataClumpsClass& begin, const DataClumps& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for items edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDataClumpsClass_Items(const DataClumpsClass& begin, const DataClumps& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for dataClumpsClass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDataClumps_DataClumpsClass(const DataClumps& begin, const DataClumpsClass& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for dataClumpsClass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDataClumps_DataClumpsClass(const DataClumps& begin, const DataClumpsClass& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for items edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDataClumps_Items(const DataClumps& begin, const DataElement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for items edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDataClumps_Items(const DataClumps& begin, const DataElement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for component edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDataElement_Component(const DataElement& begin, const Component& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for component edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDataElement_Component(const DataElement& begin, const Component& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for items edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSwitchStatementClass_Items(const SwitchStatementClass& begin, const SwitchStatement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for items edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSwitchStatementClass_Items(const SwitchStatementClass& begin, const SwitchStatement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for switchStatementClass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSwitchStatement_SwitchStatementClass(const SwitchStatement& begin, const SwitchStatementClass& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for switchStatementClass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSwitchStatement_SwitchStatementClass(const SwitchStatement& begin, const SwitchStatementClass& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for items edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSwitchStatement_Items(const SwitchStatement& begin, const CaseLabel& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for items edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSwitchStatement_Items(const SwitchStatement& begin, const CaseLabel& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for component edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCaseLabel_Component(const CaseLabel& begin, const Component& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for component edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCaseLabel_Component(const CaseLabel& begin, const Component& end) {
        visitAllEdgeEnd (begin, end);
      }

}}
