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

#ifndef _GENEALOGY_VISITORABSTRACTNODES_H_
#define _GENEALOGY_VISITORABSTRACTNODES_H_

#include "genealogy/inc/genealogy.h"

/**
* \file VisitorAbstractNodes.h
* \brief Contains declaration of VisitorAbstractNodes class.
*/

namespace columbus { namespace genealogy { 
  /**
  * \brief Visitor class for all edges and nodes (including abstract nodes as well).
  */
  class VisitorAbstractNodes : public Visitor {
    public:
      /**
      * \brief Virtual destructor.
      */
      virtual ~VisitorAbstractNodes();

      /**
      * \brief Empty abstract visitor for Base node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const Base& node , bool callVirtualBase = true);

      /**
      * \brief Empty abstract end visitor for Base node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const Base& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (Base,..) of the Project node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const Project& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (Base,..) of the Project node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const Project& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (Base,..) of the Trackable node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const Trackable& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (Base,..) of the Trackable node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const Trackable& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (Base,..) of the Component node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const Component& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (Base,..) of the Component node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const Component& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (Base,..) of the SourceCodeElement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const SourceCodeElement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (Base,..) of the SourceCodeElement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const SourceCodeElement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (Trackable,..) of the System node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const System& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (Trackable,..) of the System node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const System& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (Trackable,..) of the Clone node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const Clone& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (Trackable,..) of the Clone node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const Clone& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (Trackable,..) of the StructuralClone node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const StructuralClone& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (Trackable,..) of the StructuralClone node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const StructuralClone& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (Clone,..) of the CloneClass node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const CloneClass& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (Clone,..) of the CloneClass node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const CloneClass& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (Clone,..) of the CloneInstance node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const CloneInstance& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (Clone,..) of the CloneInstance node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const CloneInstance& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (StructuralClone,..) of the DataClumpsClass node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const DataClumpsClass& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (StructuralClone,..) of the DataClumpsClass node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const DataClumpsClass& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (StructuralClone,..) of the DataClumps node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const DataClumps& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (StructuralClone,..) of the DataClumps node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const DataClumps& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (SourceCodeElement,..) of the DataElement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const DataElement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (SourceCodeElement,..) of the DataElement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const DataElement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (StructuralClone,..) of the SwitchStatementClass node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const SwitchStatementClass& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (StructuralClone,..) of the SwitchStatementClass node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const SwitchStatementClass& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (StructuralClone,..) of the SwitchStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const SwitchStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (StructuralClone,..) of the SwitchStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const SwitchStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (SourceCodeElement,..) of the CaseLabel node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const CaseLabel& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (SourceCodeElement,..) of the CaseLabel node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const CaseLabel& node , bool callVirtualBase = true);

  }; // VisitorAbstractNodes


}}
#endif

