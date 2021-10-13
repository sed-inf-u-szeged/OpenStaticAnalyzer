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

#ifndef _LIM_VISITORLIMML_H_
#define _LIM_VISITORLIMML_H_

#include "lim/inc/lim.h"
#include <fstream>

/**
* \file VisitorLIMML.h
* \brief Contains declaration of VisitorLIMML class.
*/

namespace columbus { namespace lim { namespace asg {
  /**
  * \brief Creates XML dump of the ASG.
  */
  class VisitorLIMML : public Visitor {
    public:

      /**
      * \brief Constructor of XML generator visitor.
      * \param targetStream [in] ofstream to write the output
      * \param projectName  [in] Name of project - generated into the output
      * \param noId         [in] Do not write the ID of the nodes.
      * \param noLineInfo   [in] Do not write the line info of the nodes.
      */
      VisitorLIMML(std::ofstream& targetStream,
                   const std::string& _projectName,
                   bool noId = false,
                   bool noLineInfo = false);

      /**
      * \brief Virtual destructor.
      */
      virtual ~VisitorLIMML();

      /**
      * \brief This function is calling before the beginning of visiting process. It flushes the header of xml.
      */
      void beginVisit();

      /**
      * \brief This function is calling when the visiting process has finished. It flushes the tail of xml.
      */
      void finishVisit();

      /**
      * \brief Writes the XML representation of the base::Comment node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Comment& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the base::Comment node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::Comment& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the base::Component node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Component& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the base::Component node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::Component& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the base::ControlFlowBlock node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::ControlFlowBlock& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the base::ControlFlowBlock node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::ControlFlowBlock& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the logical::Attribute node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::Attribute& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the logical::Attribute node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::Attribute& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the logical::AttributeAccess node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::AttributeAccess& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the logical::AttributeAccess node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::AttributeAccess& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the logical::Class node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::Class& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the logical::Class node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::Class& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the logical::ClassGeneric node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::ClassGeneric& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the logical::ClassGeneric node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::ClassGeneric& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the logical::ClassGenericInstance node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::ClassGenericInstance& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the logical::ClassGenericInstance node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::ClassGenericInstance& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the logical::ClassGenericSpec node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::ClassGenericSpec& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the logical::ClassGenericSpec node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::ClassGenericSpec& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the logical::Friendship node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::Friendship& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the logical::Friendship node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::Friendship& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the logical::GenericParameter node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::GenericParameter& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the logical::GenericParameter node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::GenericParameter& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the logical::Method node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::Method& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the logical::Method node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::Method& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the logical::MethodCall node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::MethodCall& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the logical::MethodCall node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::MethodCall& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the logical::MethodGeneric node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::MethodGeneric& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the logical::MethodGeneric node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::MethodGeneric& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the logical::MethodGenericInstance node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::MethodGenericInstance& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the logical::MethodGenericInstance node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::MethodGenericInstance& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the logical::MethodGenericSpec node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::MethodGenericSpec& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the logical::MethodGenericSpec node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::MethodGenericSpec& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the logical::Package node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::Package& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the logical::Package node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::Package& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the logical::Parameter node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::Parameter& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the logical::Parameter node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::Parameter& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the physical::File node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const physical::File& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the physical::File node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const physical::File& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the physical::FileSystem node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const physical::FileSystem& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the physical::FileSystem node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const physical::FileSystem& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the physical::Folder node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const physical::Folder& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the physical::Folder node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const physical::Folder& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::SimpleType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::SimpleType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::SimpleType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::SimpleType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::Type node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::Type& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::Type node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::Type& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::TypeFormerArray node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::TypeFormerArray& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::TypeFormerArray node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::TypeFormerArray& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::TypeFormerMethod node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::TypeFormerMethod& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::TypeFormerMethod node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::TypeFormerMethod& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::TypeFormerNonType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::TypeFormerNonType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::TypeFormerNonType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::TypeFormerNonType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::TypeFormerPointer node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::TypeFormerPointer& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::TypeFormerPointer node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::TypeFormerPointer& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::TypeFormerType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::TypeFormerType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::TypeFormerType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::TypeFormerType& node, bool callVirtualBase = true);

      /**
      * \brief Edge visitor for compilationUnit edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitComponent_CompilationUnit(const base::Component& begin, const physical::File& end);

      /**
      * \brief Edge visitor for compilationUnit edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndComponent_CompilationUnit(const base::Component& begin, const physical::File& end);

      /**
      * \brief Edge visitor for contains edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitComponent_Contains(const base::Component& begin, const base::Component& end);

      /**
      * \brief Edge visitor for contains edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndComponent_Contains(const base::Component& begin, const base::Component& end);

      /**
      * \brief Edge visitor for hasFiles edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitComponent_HasFiles(const base::Component& begin, const physical::File& end);

      /**
      * \brief Edge visitor for hasFiles edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndComponent_HasFiles(const base::Component& begin, const physical::File& end);

      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitControlFlowBlock_Calls(const base::ControlFlowBlock& begin, const logical::Method& end);

      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndControlFlowBlock_Calls(const base::ControlFlowBlock& begin, const logical::Method& end);

      /**
      * \brief Edge visitor for pred edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitControlFlowBlock_Pred(const base::ControlFlowBlock& begin, const base::ControlFlowBlock& end);

      /**
      * \brief Edge visitor for pred edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndControlFlowBlock_Pred(const base::ControlFlowBlock& begin, const base::ControlFlowBlock& end);

      /**
      * \brief Edge visitor for dependsOn edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitNamed_DependsOn(const base::Named& begin, const base::Named& end, const std::string& ac);

      /**
      * \brief Edge visitor for dependsOn edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitEndNamed_DependsOn(const base::Named& begin, const base::Named& end, const std::string& ac);

      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttribute_Calls(const logical::Attribute& begin, const logical::MethodCall& end);

      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAttribute_Calls(const logical::Attribute& begin, const logical::MethodCall& end);

      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttribute_HasType(const logical::Attribute& begin, const type::Type& end);

      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAttribute_HasType(const logical::Attribute& begin, const type::Type& end);

      /**
      * \brief Edge visitor for attribute edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeAccess_Attribute(const logical::AttributeAccess& begin, const logical::Attribute& end);

      /**
      * \brief Edge visitor for attribute edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAttributeAccess_Attribute(const logical::AttributeAccess& begin, const logical::Attribute& end);

      /**
      * \brief Edge visitor for extends edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClass_Extends(const logical::Class& begin, const logical::Class& end);

      /**
      * \brief Edge visitor for extends edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndClass_Extends(const logical::Class& begin, const logical::Class& end);

      /**
      * \brief Edge visitor for grantsFriendship edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClass_GrantsFriendship(const logical::Class& begin, const logical::Friendship& end);

      /**
      * \brief Edge visitor for grantsFriendship edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndClass_GrantsFriendship(const logical::Class& begin, const logical::Friendship& end);

      /**
      * \brief Edge visitor for isSubclass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClass_IsSubclass(const logical::Class& begin, const type::Type& end);

      /**
      * \brief Edge visitor for isSubclass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndClass_IsSubclass(const logical::Class& begin, const type::Type& end);

      /**
      * \brief Edge  visitor for hasGenericParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassGeneric_HasGenericParameter(const logical::ClassGeneric& begin, const logical::GenericParameter& end);

      /**
      * \brief Edge end visitor for hasGenericParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndClassGeneric_HasGenericParameter(const logical::ClassGeneric& begin, const logical::GenericParameter& end);

      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitClassGenericInstance_HasArguments(const logical::ClassGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac);

      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitEndClassGenericInstance_HasArguments(const logical::ClassGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac);

      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitClassGenericSpec_HasArguments(const logical::ClassGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac);

      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitEndClassGenericSpec_HasArguments(const logical::ClassGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac);

      /**
      * \brief Edge visitor for specialize edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassGenericSpec_Specialize(const logical::ClassGenericSpec& begin, const logical::ClassGeneric& end);

      /**
      * \brief Edge visitor for specialize edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndClassGenericSpec_Specialize(const logical::ClassGenericSpec& begin, const logical::ClassGeneric& end);

      /**
      * \brief Edge visitor for friend edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFriendship_Friend(const logical::Friendship& begin, const logical::Scope& end);

      /**
      * \brief Edge visitor for friend edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFriendship_Friend(const logical::Friendship& begin, const logical::Scope& end);

      /**
      * \brief Edge visitor for hasParameterConstraint edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGenericParameter_HasParameterConstraint(const logical::GenericParameter& begin, const type::Type& end);

      /**
      * \brief Edge visitor for hasParameterConstraint edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndGenericParameter_HasParameterConstraint(const logical::GenericParameter& begin, const type::Type& end);

      /**
      * \brief Edge visitor for aggregated edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_Aggregated(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for aggregated edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMember_Aggregated(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for belongsTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_BelongsTo(const logical::Member& begin, const base::Component& end);

      /**
      * \brief Edge visitor for belongsTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMember_BelongsTo(const logical::Member& begin, const base::Component& end);

      /**
      * \brief Edge visitor for compilationUnit edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_CompilationUnit(const logical::Member& begin, const physical::File& end);

      /**
      * \brief Edge visitor for compilationUnit edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMember_CompilationUnit(const logical::Member& begin, const physical::File& end);

      /**
      * \brief Edge visitor for declares edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_Declares(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for declares edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMember_Declares(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for hasComment edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_HasComment(const logical::Member& begin, const base::Comment& end);

      /**
      * \brief Edge visitor for hasComment edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMember_HasComment(const logical::Member& begin, const base::Comment& end);

      /**
      * \brief Edge visitor for instance edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_Instance(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for instance edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMember_Instance(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for isContainedIn edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitMember_IsContainedIn(const logical::Member& begin, const physical::File& end, const SourcePosition& ac);

      /**
      * \brief Edge visitor for isContainedIn edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitEndMember_IsContainedIn(const logical::Member& begin, const physical::File& end, const SourcePosition& ac);

      /**
      * \brief Edge visitor for languageVariant edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_LanguageVariant(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for languageVariant edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMember_LanguageVariant(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for uses edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_Uses(const logical::Member& begin, const type::Type& end);

      /**
      * \brief Edge visitor for uses edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMember_Uses(const logical::Member& begin, const type::Type& end);

      /**
      * \brief Edge visitor for variant edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_Variant(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for variant edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMember_Variant(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for accessesAttribute edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_AccessesAttribute(const logical::Method& begin, const logical::AttributeAccess& end);

      /**
      * \brief Edge visitor for accessesAttribute edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethod_AccessesAttribute(const logical::Method& begin, const logical::AttributeAccess& end);

      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_Calls(const logical::Method& begin, const logical::MethodCall& end);

      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethod_Calls(const logical::Method& begin, const logical::MethodCall& end);

      /**
      * \brief Edge visitor for canThrow edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_CanThrow(const logical::Method& begin, const type::Type& end);

      /**
      * \brief Edge visitor for canThrow edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethod_CanThrow(const logical::Method& begin, const type::Type& end);

      /**
      * \brief Edge  visitor for hasControlFlowBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_HasControlFlowBlock(const logical::Method& begin, const base::ControlFlowBlock& end);

      /**
      * \brief Edge end visitor for hasControlFlowBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethod_HasControlFlowBlock(const logical::Method& begin, const base::ControlFlowBlock& end);

      /**
      * \brief Edge  visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_HasParameter(const logical::Method& begin, const logical::Parameter& end);

      /**
      * \brief Edge end visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethod_HasParameter(const logical::Method& begin, const logical::Parameter& end);

      /**
      * \brief Edge visitor for instantiates edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_Instantiates(const logical::Method& begin, const type::Type& end);

      /**
      * \brief Edge visitor for instantiates edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethod_Instantiates(const logical::Method& begin, const type::Type& end);

      /**
      * \brief Edge visitor for returns edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_Returns(const logical::Method& begin, const type::Type& end);

      /**
      * \brief Edge visitor for returns edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethod_Returns(const logical::Method& begin, const type::Type& end);

      /**
      * \brief Edge visitor for throws edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_Throws(const logical::Method& begin, const type::Type& end);

      /**
      * \brief Edge visitor for throws edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethod_Throws(const logical::Method& begin, const type::Type& end);

      /**
      * \brief Edge visitor for method edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodCall_Method(const logical::MethodCall& begin, const logical::Method& end);

      /**
      * \brief Edge visitor for method edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodCall_Method(const logical::MethodCall& begin, const logical::Method& end);

      /**
      * \brief Edge  visitor for hasGenericParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodGeneric_HasGenericParameter(const logical::MethodGeneric& begin, const logical::GenericParameter& end);

      /**
      * \brief Edge end visitor for hasGenericParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodGeneric_HasGenericParameter(const logical::MethodGeneric& begin, const logical::GenericParameter& end);

      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitMethodGenericInstance_HasArguments(const logical::MethodGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac);

      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitEndMethodGenericInstance_HasArguments(const logical::MethodGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac);

      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitMethodGenericSpec_HasArguments(const logical::MethodGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac);

      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitEndMethodGenericSpec_HasArguments(const logical::MethodGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac);

      /**
      * \brief Edge visitor for specialize edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodGenericSpec_Specialize(const logical::MethodGenericSpec& begin, const logical::MethodGeneric& end);

      /**
      * \brief Edge visitor for specialize edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodGenericSpec_Specialize(const logical::MethodGenericSpec& begin, const logical::MethodGeneric& end);

      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameter_HasType(const logical::Parameter& begin, const type::Type& end);

      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndParameter_HasType(const logical::Parameter& begin, const type::Type& end);

      /**
      * \brief Edge visitor for hasMember edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitScope_HasMember(const logical::Scope& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for hasMember edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndScope_HasMember(const logical::Scope& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for hasComment edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFile_HasComment(const physical::File& begin, const base::Comment& end);

      /**
      * \brief Edge visitor for hasComment edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFile_HasComment(const physical::File& begin, const base::Comment& end);

      /**
      * \brief Edge visitor for includes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFile_Includes(const physical::File& begin, const physical::File& end);

      /**
      * \brief Edge visitor for includes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFile_Includes(const physical::File& begin, const physical::File& end);

      /**
      * \brief Edge  visitor for hasFSEntry edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFileSystem_HasFSEntry(const physical::FileSystem& begin, const physical::FSEntry& end);

      /**
      * \brief Edge end visitor for hasFSEntry edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFileSystem_HasFSEntry(const physical::FileSystem& begin, const physical::FSEntry& end);

      /**
      * \brief Edge  visitor for contains edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFolder_Contains(const physical::Folder& begin, const physical::FSEntry& end);

      /**
      * \brief Edge end visitor for contains edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFolder_Contains(const physical::Folder& begin, const physical::FSEntry& end);

      /**
      * \brief Edge visitor for hasTypeFormer edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitType_HasTypeFormer(const type::Type& begin, const type::TypeFormer& end);

      /**
      * \brief Edge visitor for hasTypeFormer edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndType_HasTypeFormer(const type::Type& begin, const type::TypeFormer& end);

      /**
      * \brief Edge visitor for hasParameterType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitTypeFormerMethod_HasParameterType(const type::TypeFormerMethod& begin, const type::Type& end, ParameterKind ac);

      /**
      * \brief Edge visitor for hasParameterType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitEndTypeFormerMethod_HasParameterType(const type::TypeFormerMethod& begin, const type::Type& end, ParameterKind ac);

      /**
      * \brief Edge visitor for hasReturnType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeFormerMethod_HasReturnType(const type::TypeFormerMethod& begin, const type::Type& end);

      /**
      * \brief Edge visitor for hasReturnType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeFormerMethod_HasReturnType(const type::TypeFormerMethod& begin, const type::Type& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeFormerType_RefersTo(const type::TypeFormerType& begin, const base::Base& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeFormerType_RefersTo(const type::TypeFormerType& begin, const base::Base& end);

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
      * \brief Writes out the attributes of the base::Base node.
      */
      virtual void writeAttributes(const base::Base& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the base::Comment node.
      */
      virtual void writeAttributes(const base::Comment& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the base::Component node.
      */
      virtual void writeAttributes(const base::Component& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the base::ControlFlowBlock node.
      */
      virtual void writeAttributes(const base::ControlFlowBlock& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the base::Named node.
      */
      virtual void writeAttributes(const base::Named& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the logical::Attribute node.
      */
      virtual void writeAttributes(const logical::Attribute& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the logical::AttributeAccess node.
      */
      virtual void writeAttributes(const logical::AttributeAccess& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the logical::Class node.
      */
      virtual void writeAttributes(const logical::Class& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the logical::ClassGeneric node.
      */
      virtual void writeAttributes(const logical::ClassGeneric& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the logical::ClassGenericInstance node.
      */
      virtual void writeAttributes(const logical::ClassGenericInstance& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the logical::ClassGenericSpec node.
      */
      virtual void writeAttributes(const logical::ClassGenericSpec& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the logical::Friendship node.
      */
      virtual void writeAttributes(const logical::Friendship& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the logical::GenericParameter node.
      */
      virtual void writeAttributes(const logical::GenericParameter& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the logical::Member node.
      */
      virtual void writeAttributes(const logical::Member& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the logical::Method node.
      */
      virtual void writeAttributes(const logical::Method& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the logical::MethodCall node.
      */
      virtual void writeAttributes(const logical::MethodCall& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the logical::MethodGeneric node.
      */
      virtual void writeAttributes(const logical::MethodGeneric& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the logical::MethodGenericInstance node.
      */
      virtual void writeAttributes(const logical::MethodGenericInstance& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the logical::MethodGenericSpec node.
      */
      virtual void writeAttributes(const logical::MethodGenericSpec& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the logical::Package node.
      */
      virtual void writeAttributes(const logical::Package& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the logical::Parameter node.
      */
      virtual void writeAttributes(const logical::Parameter& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the logical::Scope node.
      */
      virtual void writeAttributes(const logical::Scope& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the physical::FSEntry node.
      */
      virtual void writeAttributes(const physical::FSEntry& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the physical::File node.
      */
      virtual void writeAttributes(const physical::File& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the physical::FileSystem node.
      */
      virtual void writeAttributes(const physical::FileSystem& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the physical::Folder node.
      */
      virtual void writeAttributes(const physical::Folder& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::SimpleType node.
      */
      virtual void writeAttributes(const type::SimpleType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::Type node.
      */
      virtual void writeAttributes(const type::Type& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::TypeFormer node.
      */
      virtual void writeAttributes(const type::TypeFormer& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::TypeFormerArray node.
      */
      virtual void writeAttributes(const type::TypeFormerArray& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::TypeFormerMethod node.
      */
      virtual void writeAttributes(const type::TypeFormerMethod& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::TypeFormerNonType node.
      */
      virtual void writeAttributes(const type::TypeFormerNonType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::TypeFormerPointer node.
      */
      virtual void writeAttributes(const type::TypeFormerPointer& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::TypeFormerType node.
      */
      virtual void writeAttributes(const type::TypeFormerType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the SourcePosition composite member.
      */
      void writeAttributes(const SourcePosition& node, bool composite);

      /** \internal \brief The ofstrem into the xml will be written. */
      std::ofstream &ofs;

      /** \internal \brief Flag to know if the ID of the nodes have to be written or not. */
      bool noId;

      /** \internal \brief Flag to know if the line info of the nodes have to be written or not. */
      bool noLineInfo;

      const std::string projectName;

  }; // VisitorLIMML


}}}
#endif

