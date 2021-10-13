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

#ifndef _LIM_VISITOR_H_
#define _LIM_VISITOR_H_

#include "lim/inc/lim.h"

/**
* \file Visitor.h
* \brief Contains declaration of Visitor class.
*/

namespace columbus { namespace lim { namespace asg {
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
      * \brief Visitor which is called at the beginning of the base::Comment node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Comment& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the base::Comment node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::Comment& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the base::Component node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Component& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the base::Component node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::Component& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the base::ControlFlowBlock node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::ControlFlowBlock& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the base::ControlFlowBlock node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::ControlFlowBlock& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the logical::Attribute node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::Attribute& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the logical::Attribute node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::Attribute& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the logical::AttributeAccess node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::AttributeAccess& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the logical::AttributeAccess node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::AttributeAccess& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the logical::Class node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::Class& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the logical::Class node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::Class& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the logical::ClassGeneric node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::ClassGeneric& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the logical::ClassGeneric node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::ClassGeneric& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the logical::ClassGenericInstance node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::ClassGenericInstance& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the logical::ClassGenericInstance node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::ClassGenericInstance& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the logical::ClassGenericSpec node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::ClassGenericSpec& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the logical::ClassGenericSpec node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::ClassGenericSpec& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the logical::Friendship node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::Friendship& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the logical::Friendship node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::Friendship& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the logical::GenericParameter node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::GenericParameter& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the logical::GenericParameter node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::GenericParameter& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the logical::Method node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::Method& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the logical::Method node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::Method& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the logical::MethodCall node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::MethodCall& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the logical::MethodCall node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::MethodCall& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the logical::MethodGeneric node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::MethodGeneric& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the logical::MethodGeneric node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::MethodGeneric& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the logical::MethodGenericInstance node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::MethodGenericInstance& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the logical::MethodGenericInstance node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::MethodGenericInstance& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the logical::MethodGenericSpec node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::MethodGenericSpec& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the logical::MethodGenericSpec node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::MethodGenericSpec& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the logical::Package node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::Package& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the logical::Package node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::Package& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the logical::Parameter node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::Parameter& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the logical::Parameter node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::Parameter& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the physical::File node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const physical::File& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the physical::File node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const physical::File& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the physical::FileSystem node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const physical::FileSystem& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the physical::FileSystem node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const physical::FileSystem& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the physical::Folder node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const physical::Folder& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the physical::Folder node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const physical::Folder& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the type::SimpleType node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::SimpleType& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the type::SimpleType node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::SimpleType& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the type::Type node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::Type& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the type::Type node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::Type& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the type::TypeFormerArray node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::TypeFormerArray& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the type::TypeFormerArray node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::TypeFormerArray& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the type::TypeFormerMethod node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::TypeFormerMethod& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the type::TypeFormerMethod node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::TypeFormerMethod& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the type::TypeFormerNonType node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::TypeFormerNonType& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the type::TypeFormerNonType node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::TypeFormerNonType& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the type::TypeFormerPointer node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::TypeFormerPointer& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the type::TypeFormerPointer node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::TypeFormerPointer& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the type::TypeFormerType node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::TypeFormerType& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the type::TypeFormerType node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::TypeFormerType& node , bool callVirtualBase = true);

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
      /** \internal \brief Stores the depth position in the ASG. */
      unsigned depth;
  }; // Visitor


}}}
#endif

