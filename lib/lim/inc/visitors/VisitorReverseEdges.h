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

#ifndef _LIM_VISITORREVERSEEDGES_H_
#define _LIM_VISITORREVERSEEDGES_H_

#include "lim/inc/lim.h"

/**
* \file VisitorReverseEdges.h
* \brief Contains declaration of VisitorReverseEdges class.
*/

namespace columbus { namespace lim { namespace asg {
  /**
  * \brief Collects the inverse relation of any "one way" defined edges.
  */
  class VisitorReverseEdges : public VisitorAbstractNodes {
    private:

      /**
      * \brief Disable the copy of object .
      */
      VisitorReverseEdges(const VisitorReverseEdges& );

      /**
      * \brief Disable the copy of object.
      */
      VisitorReverseEdges& operator=(const VisitorReverseEdges& );

    protected:

      /**
      * \brief Only ReverseEdges can instantiates this class.
      * \param reverseEdges [in] The edges are inserted into this.
      */
      VisitorReverseEdges(ReverseEdges* reverseEdges);

      /**
      * \brief Destructor.
      */
      virtual ~VisitorReverseEdges();

    public:

      /**
      * \brief Sets all node "existing" in AlgorithmReverseEdges.
      * \param node [in] The node.
      */
      virtual void visit(const base::Base &node, bool callVirtualBase = true);

      /**
      * \brief Edge visitor for compilationUnit edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitComponent_CompilationUnit(const base::Component& begin, const physical::File& end);

      /**
      * \brief Edge visitor for contains edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitComponent_Contains(const base::Component& begin, const base::Component& end);

      /**
      * \brief Edge visitor for hasFiles edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitComponent_HasFiles(const base::Component& begin, const physical::File& end);

      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitControlFlowBlock_Calls(const base::ControlFlowBlock& begin, const logical::Method& end);

      /**
      * \brief Edge visitor for pred edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitControlFlowBlock_Pred(const base::ControlFlowBlock& begin, const base::ControlFlowBlock& end);

      /**
      * \brief Edge visitor for dependsOn edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitNamed_DependsOn(const base::Named& begin, const base::Named& end, const std::string& ac);

      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttribute_Calls(const logical::Attribute& begin, const logical::MethodCall& end);

      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttribute_HasType(const logical::Attribute& begin, const type::Type& end);

      /**
      * \brief Edge visitor for attribute edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeAccess_Attribute(const logical::AttributeAccess& begin, const logical::Attribute& end);

      /**
      * \brief Edge visitor for extends edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClass_Extends(const logical::Class& begin, const logical::Class& end);

      /**
      * \brief Edge visitor for grantsFriendship edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClass_GrantsFriendship(const logical::Class& begin, const logical::Friendship& end);

      /**
      * \brief Edge visitor for isSubclass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClass_IsSubclass(const logical::Class& begin, const type::Type& end);

      /**
      * \brief Edge  visitor for hasGenericParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassGeneric_HasGenericParameter(const logical::ClassGeneric& begin, const logical::GenericParameter& end);

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
      virtual void visitClassGenericSpec_HasArguments(const logical::ClassGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac);

      /**
      * \brief Edge visitor for specialize edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassGenericSpec_Specialize(const logical::ClassGenericSpec& begin, const logical::ClassGeneric& end);

      /**
      * \brief Edge visitor for friend edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFriendship_Friend(const logical::Friendship& begin, const logical::Scope& end);

      /**
      * \brief Edge visitor for hasParameterConstraint edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGenericParameter_HasParameterConstraint(const logical::GenericParameter& begin, const type::Type& end);

      /**
      * \brief Edge visitor for aggregated edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_Aggregated(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for belongsTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_BelongsTo(const logical::Member& begin, const base::Component& end);

      /**
      * \brief Edge visitor for compilationUnit edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_CompilationUnit(const logical::Member& begin, const physical::File& end);

      /**
      * \brief Edge visitor for declares edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_Declares(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for hasComment edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_HasComment(const logical::Member& begin, const base::Comment& end);

      /**
      * \brief Edge visitor for instance edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_Instance(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for isContainedIn edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitMember_IsContainedIn(const logical::Member& begin, const physical::File& end, const SourcePosition& ac);

      /**
      * \brief Edge visitor for languageVariant edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_LanguageVariant(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for uses edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_Uses(const logical::Member& begin, const type::Type& end);

      /**
      * \brief Edge visitor for variant edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_Variant(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for accessesAttribute edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_AccessesAttribute(const logical::Method& begin, const logical::AttributeAccess& end);

      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_Calls(const logical::Method& begin, const logical::MethodCall& end);

      /**
      * \brief Edge visitor for canThrow edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_CanThrow(const logical::Method& begin, const type::Type& end);

      /**
      * \brief Edge  visitor for hasControlFlowBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_HasControlFlowBlock(const logical::Method& begin, const base::ControlFlowBlock& end);

      /**
      * \brief Edge  visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_HasParameter(const logical::Method& begin, const logical::Parameter& end);

      /**
      * \brief Edge visitor for instantiates edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_Instantiates(const logical::Method& begin, const type::Type& end);

      /**
      * \brief Edge visitor for returns edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_Returns(const logical::Method& begin, const type::Type& end);

      /**
      * \brief Edge visitor for throws edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_Throws(const logical::Method& begin, const type::Type& end);

      /**
      * \brief Edge visitor for method edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodCall_Method(const logical::MethodCall& begin, const logical::Method& end);

      /**
      * \brief Edge  visitor for hasGenericParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodGeneric_HasGenericParameter(const logical::MethodGeneric& begin, const logical::GenericParameter& end);

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
      virtual void visitMethodGenericSpec_HasArguments(const logical::MethodGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac);

      /**
      * \brief Edge visitor for specialize edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodGenericSpec_Specialize(const logical::MethodGenericSpec& begin, const logical::MethodGeneric& end);

      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameter_HasType(const logical::Parameter& begin, const type::Type& end);

      /**
      * \brief Edge visitor for hasMember edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitScope_HasMember(const logical::Scope& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for hasComment edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFile_HasComment(const physical::File& begin, const base::Comment& end);

      /**
      * \brief Edge visitor for includes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFile_Includes(const physical::File& begin, const physical::File& end);

      /**
      * \brief Edge  visitor for hasFSEntry edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFileSystem_HasFSEntry(const physical::FileSystem& begin, const physical::FSEntry& end);

      /**
      * \brief Edge  visitor for contains edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFolder_Contains(const physical::Folder& begin, const physical::FSEntry& end);

      /**
      * \brief Edge visitor for hasTypeFormer edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitType_HasTypeFormer(const type::Type& begin, const type::TypeFormer& end);

      /**
      * \brief Edge visitor for hasParameterType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitTypeFormerMethod_HasParameterType(const type::TypeFormerMethod& begin, const type::Type& end, ParameterKind ac);

      /**
      * \brief Edge visitor for hasReturnType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeFormerMethod_HasReturnType(const type::TypeFormerMethod& begin, const type::Type& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeFormerType_RefersTo(const type::TypeFormerType& begin, const base::Base& end);

    protected:

      /** \internal \brief Edges are inserted into this ReverseEdges class. */
      ReverseEdges *revEdges;

      friend class ReverseEdges;

  }; // VisitorReverseEdges


}}}
#endif

