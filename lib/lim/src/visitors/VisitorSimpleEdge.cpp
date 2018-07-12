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

#include "lim/inc/lim.h"

/**
* \file VisitorSimpleEdge.cpp
* \brief Contains declaration of VisitorSimpleEdge class.
*/

namespace columbus { namespace lim { namespace asg {
      VisitorSimpleEdge::~VisitorSimpleEdge(){};

      /**
      * \brief Edge visitor for contains edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitComponent_Contains(const base::Component& begin, const base::Component& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for contains edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndComponent_Contains(const base::Component& begin, const base::Component& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasFiles edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitComponent_HasFiles(const base::Component& begin, const physical::File& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasFiles edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndComponent_HasFiles(const base::Component& begin, const physical::File& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitControlFlowBlock_Calls(const base::ControlFlowBlock& begin, const logical::Method& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndControlFlowBlock_Calls(const base::ControlFlowBlock& begin, const logical::Method& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for pred edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitControlFlowBlock_Pred(const base::ControlFlowBlock& begin, const base::ControlFlowBlock& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for pred edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndControlFlowBlock_Pred(const base::ControlFlowBlock& begin, const base::ControlFlowBlock& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for dependsOn edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      void VisitorSimpleEdge::visitNamed_DependsOn(const base::Named& begin, const base::Named& end, const std::string& ac) {
        visitAllEdge (begin, end,&ac,acString);
      }
      /**
      * \brief Edge visitor for dependsOn edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      void VisitorSimpleEdge::visitEndNamed_DependsOn(const base::Named& begin, const base::Named& end, const std::string& ac) {
        visitAllEdgeEnd (begin, end,&ac,acString);
      }
      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAttribute_Calls(const logical::Attribute& begin, const logical::MethodCall& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAttribute_Calls(const logical::Attribute& begin, const logical::MethodCall& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAttribute_HasType(const logical::Attribute& begin, const type::Type& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAttribute_HasType(const logical::Attribute& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for attribute edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAttributeAccess_Attribute(const logical::AttributeAccess& begin, const logical::Attribute& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for attribute edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAttributeAccess_Attribute(const logical::AttributeAccess& begin, const logical::Attribute& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for grantsFriendship edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitClass_GrantsFriendship(const logical::Class& begin, const logical::Friendship& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for grantsFriendship edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndClass_GrantsFriendship(const logical::Class& begin, const logical::Friendship& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for isSubclass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitClass_IsSubclass(const logical::Class& begin, const type::Type& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for isSubclass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndClass_IsSubclass(const logical::Class& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge  visitor for hasGenericParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitClassGeneric_HasGenericParameter(const logical::ClassGeneric& begin, const logical::GenericParameter& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge end visitor for hasGenericParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndClassGeneric_HasGenericParameter(const logical::ClassGeneric& begin, const logical::GenericParameter& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      void VisitorSimpleEdge::visitClassGenericInstance_HasArguments(const logical::ClassGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
        visitAllEdge (begin, end,&ac,acTypeArgumentConstraintKind);
      }
      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      void VisitorSimpleEdge::visitEndClassGenericInstance_HasArguments(const logical::ClassGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
        visitAllEdgeEnd (begin, end,&ac,acTypeArgumentConstraintKind);
      }
      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      void VisitorSimpleEdge::visitClassGenericSpec_HasArguments(const logical::ClassGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
        visitAllEdge (begin, end,&ac,acTypeArgumentConstraintKind);
      }
      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      void VisitorSimpleEdge::visitEndClassGenericSpec_HasArguments(const logical::ClassGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
        visitAllEdgeEnd (begin, end,&ac,acTypeArgumentConstraintKind);
      }
      /**
      * \brief Edge visitor for specialize edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitClassGenericSpec_Specialize(const logical::ClassGenericSpec& begin, const logical::ClassGeneric& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for specialize edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndClassGenericSpec_Specialize(const logical::ClassGenericSpec& begin, const logical::ClassGeneric& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for friend edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFriendship_Friend(const logical::Friendship& begin, const logical::Scope& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for friend edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFriendship_Friend(const logical::Friendship& begin, const logical::Scope& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasParameterConstraint edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitGenericParameter_HasParameterConstraint(const logical::GenericParameter& begin, const type::Type& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasParameterConstraint edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndGenericParameter_HasParameterConstraint(const logical::GenericParameter& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for aggregated edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMember_Aggregated(const logical::Member& begin, const logical::Member& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for aggregated edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMember_Aggregated(const logical::Member& begin, const logical::Member& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for belongsTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMember_BelongsTo(const logical::Member& begin, const base::Component& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for belongsTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMember_BelongsTo(const logical::Member& begin, const base::Component& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for compilationUnit edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMember_CompilationUnit(const logical::Member& begin, const physical::File& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for compilationUnit edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMember_CompilationUnit(const logical::Member& begin, const physical::File& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for declares edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMember_Declares(const logical::Member& begin, const logical::Member& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for declares edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMember_Declares(const logical::Member& begin, const logical::Member& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasComment edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMember_HasComment(const logical::Member& begin, const base::Comment& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasComment edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMember_HasComment(const logical::Member& begin, const base::Comment& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for instance edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMember_Instance(const logical::Member& begin, const logical::Member& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for instance edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMember_Instance(const logical::Member& begin, const logical::Member& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for isContainedIn edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      void VisitorSimpleEdge::visitMember_IsContainedIn(const logical::Member& begin, const physical::File& end, const SourcePosition& ac) {
        visitAllEdge (begin, end,&ac,acSourcePosition);
      }
      /**
      * \brief Edge visitor for isContainedIn edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      void VisitorSimpleEdge::visitEndMember_IsContainedIn(const logical::Member& begin, const physical::File& end, const SourcePosition& ac) {
        visitAllEdgeEnd (begin, end,&ac,acSourcePosition);
      }
      /**
      * \brief Edge visitor for languageVariant edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMember_LanguageVariant(const logical::Member& begin, const logical::Member& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for languageVariant edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMember_LanguageVariant(const logical::Member& begin, const logical::Member& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for uses edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMember_Uses(const logical::Member& begin, const type::Type& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for uses edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMember_Uses(const logical::Member& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for variant edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMember_Variant(const logical::Member& begin, const logical::Member& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for variant edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMember_Variant(const logical::Member& begin, const logical::Member& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for accessesAttribute edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethod_AccessesAttribute(const logical::Method& begin, const logical::AttributeAccess& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for accessesAttribute edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethod_AccessesAttribute(const logical::Method& begin, const logical::AttributeAccess& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethod_Calls(const logical::Method& begin, const logical::MethodCall& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethod_Calls(const logical::Method& begin, const logical::MethodCall& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for canThrow edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethod_CanThrow(const logical::Method& begin, const type::Type& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for canThrow edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethod_CanThrow(const logical::Method& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge  visitor for hasControlFlowBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethod_HasControlFlowBlock(const logical::Method& begin, const base::ControlFlowBlock& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge end visitor for hasControlFlowBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethod_HasControlFlowBlock(const logical::Method& begin, const base::ControlFlowBlock& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge  visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethod_HasParameter(const logical::Method& begin, const logical::Parameter& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge end visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethod_HasParameter(const logical::Method& begin, const logical::Parameter& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for instantiates edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethod_Instantiates(const logical::Method& begin, const type::Type& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for instantiates edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethod_Instantiates(const logical::Method& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for returns edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethod_Returns(const logical::Method& begin, const type::Type& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for returns edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethod_Returns(const logical::Method& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for throws edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethod_Throws(const logical::Method& begin, const type::Type& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for throws edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethod_Throws(const logical::Method& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for method edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethodCall_Method(const logical::MethodCall& begin, const logical::Method& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for method edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethodCall_Method(const logical::MethodCall& begin, const logical::Method& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge  visitor for hasGenericParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethodGeneric_HasGenericParameter(const logical::MethodGeneric& begin, const logical::GenericParameter& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge end visitor for hasGenericParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethodGeneric_HasGenericParameter(const logical::MethodGeneric& begin, const logical::GenericParameter& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      void VisitorSimpleEdge::visitMethodGenericInstance_HasArguments(const logical::MethodGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
        visitAllEdge (begin, end,&ac,acTypeArgumentConstraintKind);
      }
      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      void VisitorSimpleEdge::visitEndMethodGenericInstance_HasArguments(const logical::MethodGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
        visitAllEdgeEnd (begin, end,&ac,acTypeArgumentConstraintKind);
      }
      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      void VisitorSimpleEdge::visitMethodGenericSpec_HasArguments(const logical::MethodGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
        visitAllEdge (begin, end,&ac,acTypeArgumentConstraintKind);
      }
      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      void VisitorSimpleEdge::visitEndMethodGenericSpec_HasArguments(const logical::MethodGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
        visitAllEdgeEnd (begin, end,&ac,acTypeArgumentConstraintKind);
      }
      /**
      * \brief Edge visitor for specialize edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethodGenericSpec_Specialize(const logical::MethodGenericSpec& begin, const logical::MethodGeneric& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for specialize edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethodGenericSpec_Specialize(const logical::MethodGenericSpec& begin, const logical::MethodGeneric& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitParameter_HasType(const logical::Parameter& begin, const type::Type& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndParameter_HasType(const logical::Parameter& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasMember edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitScope_HasMember(const logical::Scope& begin, const logical::Member& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasMember edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndScope_HasMember(const logical::Scope& begin, const logical::Member& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasComment edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFile_HasComment(const physical::File& begin, const base::Comment& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasComment edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFile_HasComment(const physical::File& begin, const base::Comment& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for includes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFile_Includes(const physical::File& begin, const physical::File& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for includes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFile_Includes(const physical::File& begin, const physical::File& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge  visitor for hasFSEntry edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFileSystem_HasFSEntry(const physical::FileSystem& begin, const physical::FSEntry& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge end visitor for hasFSEntry edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFileSystem_HasFSEntry(const physical::FileSystem& begin, const physical::FSEntry& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge  visitor for contains edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFolder_Contains(const physical::Folder& begin, const physical::FSEntry& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge end visitor for contains edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFolder_Contains(const physical::Folder& begin, const physical::FSEntry& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasTypeFormer edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitType_HasTypeFormer(const type::Type& begin, const type::TypeFormer& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasTypeFormer edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndType_HasTypeFormer(const type::Type& begin, const type::TypeFormer& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasParameterType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      void VisitorSimpleEdge::visitTypeFormerMethod_HasParameterType(const type::TypeFormerMethod& begin, const type::Type& end, ParameterKind ac) {
        visitAllEdge (begin, end,&ac,acParameterKind);
      }
      /**
      * \brief Edge visitor for hasParameterType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      void VisitorSimpleEdge::visitEndTypeFormerMethod_HasParameterType(const type::TypeFormerMethod& begin, const type::Type& end, ParameterKind ac) {
        visitAllEdgeEnd (begin, end,&ac,acParameterKind);
      }
      /**
      * \brief Edge visitor for hasReturnType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeFormerMethod_HasReturnType(const type::TypeFormerMethod& begin, const type::Type& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for hasReturnType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeFormerMethod_HasReturnType(const type::TypeFormerMethod& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeFormerType_RefersTo(const type::TypeFormerType& begin, const base::Base& end) {
        visitAllEdge (begin, end,NULL,acNone);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeFormerType_RefersTo(const type::TypeFormerType& begin, const base::Base& end) {
        visitAllEdgeEnd (begin, end,NULL,acNone);
      }

}}}
