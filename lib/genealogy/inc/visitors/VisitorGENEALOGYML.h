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

#ifndef _GENEALOGY_VISITORGENEALOGYML_H_
#define _GENEALOGY_VISITORGENEALOGYML_H_

#include "genealogy/inc/genealogy.h"
#include <fstream>

/**
* \file VisitorGENEALOGYML.h
* \brief Contains declaration of VisitorGENEALOGYML class.
*/

namespace columbus { namespace genealogy { 
  /**
  * \brief Creates XML dump of the ASG.
  */
  class VisitorGENEALOGYML : public Visitor {
    public:

      /**
      * \brief Constructor of XML generator visitor.
      * \param targetStream [in] ofstream to write the output
      * \param projectName  [in] Name of project - generated into the output
      * \param noId         [in] Do not write the ID of the nodes.
      * \param noLineInfo   [in] Do not write the line info of the nodes.
      */
      VisitorGENEALOGYML(std::ofstream& targetStream,
                         const std::string& _projectName,
                         bool noId = false,
                         bool noLineInfo = false);

      /**
      * \brief Virtual destructor.
      */
      virtual ~VisitorGENEALOGYML();

      /**
      * \brief This function is calling before the beginning of visiting process. It flushes the header of xml.
      */
      void beginVisit();

      /**
      * \brief This function is calling when the visiting process has finished. It flushes the tail of xml.
      */
      void finishVisit();

      /**
      * \brief Writes the XML representation of the Project node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const Project& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the Project node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const Project& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the Trackable node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const Trackable& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the Trackable node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const Trackable& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the Component node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const Component& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the Component node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const Component& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the SourceCodeElement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const SourceCodeElement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the SourceCodeElement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const SourceCodeElement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the System node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const System& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the System node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const System& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the Clone node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const Clone& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the Clone node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const Clone& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the StructuralClone node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const StructuralClone& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the StructuralClone node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const StructuralClone& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the CloneClass node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const CloneClass& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the CloneClass node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const CloneClass& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the CloneInstance node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const CloneInstance& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the CloneInstance node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const CloneInstance& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the DataClumpsClass node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const DataClumpsClass& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the DataClumpsClass node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const DataClumpsClass& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the DataClumps node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const DataClumps& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the DataClumps node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const DataClumps& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the DataElement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const DataElement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the DataElement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const DataElement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the SwitchStatementClass node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const SwitchStatementClass& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the SwitchStatementClass node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const SwitchStatementClass& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the SwitchStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const SwitchStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the SwitchStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const SwitchStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the CaseLabel node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const CaseLabel& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the CaseLabel node into the output file.
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

      /**
      * \internal
      * \brief Creates the indentation according to the depth.
      */
      void createIndentation();

      /**
      * \internal
      * \brief Replaces the invalid characters for XML in the string.
      */
      std::string chk(std::string s);

      /**
      * \internal
      * \brief Writes out the attributes of the Base node.
      */
      virtual void writeAttributes(const Base& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the Project node.
      */
      virtual void writeAttributes(const Project& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the Trackable node.
      */
      virtual void writeAttributes(const Trackable& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the Component node.
      */
      virtual void writeAttributes(const Component& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the SourceCodeElement node.
      */
      virtual void writeAttributes(const SourceCodeElement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the System node.
      */
      virtual void writeAttributes(const System& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the Clone node.
      */
      virtual void writeAttributes(const Clone& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the StructuralClone node.
      */
      virtual void writeAttributes(const StructuralClone& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the CloneClass node.
      */
      virtual void writeAttributes(const CloneClass& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the CloneInstance node.
      */
      virtual void writeAttributes(const CloneInstance& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the DataClumpsClass node.
      */
      virtual void writeAttributes(const DataClumpsClass& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the DataClumps node.
      */
      virtual void writeAttributes(const DataClumps& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the DataElement node.
      */
      virtual void writeAttributes(const DataElement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the SwitchStatementClass node.
      */
      virtual void writeAttributes(const SwitchStatementClass& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the SwitchStatement node.
      */
      virtual void writeAttributes(const SwitchStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the CaseLabel node.
      */
      virtual void writeAttributes(const CaseLabel& node, bool composite, bool bWithParent = true);

      /** \internal \brief The ofstrem into the xml will be written. */
      std::ofstream &ofs;

      /** \internal \brief Flag to know if the ID of the nodes have to be written or not. */
      bool noId;

      /** \internal \brief Flag to know if the line info of the nodes have to be written or not. */
      bool noLineInfo;

      const std::string projectName;

  }; // VisitorGENEALOGYML


}}
#endif

