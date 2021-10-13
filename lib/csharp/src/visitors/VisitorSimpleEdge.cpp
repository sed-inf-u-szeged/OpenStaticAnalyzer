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

#include "csharp/inc/csharp.h"

/**
* \file VisitorSimpleEdge.cpp
* \brief Contains declaration of VisitorSimpleEdge class.
*/

namespace columbus { namespace csharp { namespace asg {
      VisitorSimpleEdge::~VisitorSimpleEdge(){};

      /**
      * \brief Edge  visitor for Alias edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAliasQualifiedNameSyntax_Alias(const expression::AliasQualifiedNameSyntax& begin, const expression::IdentifierNameSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Alias edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAliasQualifiedNameSyntax_Alias(const expression::AliasQualifiedNameSyntax& begin, const expression::IdentifierNameSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAliasQualifiedNameSyntax_Name(const expression::AliasQualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAliasQualifiedNameSyntax_Name(const expression::AliasQualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAnonymousFunctionExpressionSyntax_Block(const expression::AnonymousFunctionExpressionSyntax& begin, const statement::BlockSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAnonymousFunctionExpressionSyntax_Block(const expression::AnonymousFunctionExpressionSyntax& begin, const statement::BlockSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAnonymousFunctionExpressionSyntax_ExpressionBody(const expression::AnonymousFunctionExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAnonymousFunctionExpressionSyntax_ExpressionBody(const expression::AnonymousFunctionExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAnonymousMethodExpressionSyntax_ParameterList(const expression::AnonymousMethodExpressionSyntax& begin, const structure::ParameterListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAnonymousMethodExpressionSyntax_ParameterList(const expression::AnonymousMethodExpressionSyntax& begin, const structure::ParameterListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Initializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAnonymousObjectCreationExpressionSyntax_Initializers(const expression::AnonymousObjectCreationExpressionSyntax& begin, const structure::AnonymousObjectMemberDeclaratorSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Initializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAnonymousObjectCreationExpressionSyntax_Initializers(const expression::AnonymousObjectCreationExpressionSyntax& begin, const structure::AnonymousObjectMemberDeclaratorSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitArrayCreationExpressionSyntax_Initializer(const expression::ArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndArrayCreationExpressionSyntax_Initializer(const expression::ArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitArrayCreationExpressionSyntax_Type(const expression::ArrayCreationExpressionSyntax& begin, const expression::ArrayTypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndArrayCreationExpressionSyntax_Type(const expression::ArrayCreationExpressionSyntax& begin, const expression::ArrayTypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitArrayTypeSyntax_ElementType(const expression::ArrayTypeSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndArrayTypeSyntax_ElementType(const expression::ArrayTypeSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for RankSpecifiers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitArrayTypeSyntax_RankSpecifiers(const expression::ArrayTypeSyntax& begin, const structure::ArrayRankSpecifierSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for RankSpecifiers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndArrayTypeSyntax_RankSpecifiers(const expression::ArrayTypeSyntax& begin, const structure::ArrayRankSpecifierSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for EventAccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAssignmentExpressionSyntax_EventAccessorCall(const expression::AssignmentExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for EventAccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAssignmentExpressionSyntax_EventAccessorCall(const expression::AssignmentExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAssignmentExpressionSyntax_Left(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAssignmentExpressionSyntax_Left(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAssignmentExpressionSyntax_OverloadedOperatorCall(const expression::AssignmentExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAssignmentExpressionSyntax_OverloadedOperatorCall(const expression::AssignmentExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAssignmentExpressionSyntax_Right(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAssignmentExpressionSyntax_Right(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAwaitExpressionSyntax_Expression(const expression::AwaitExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAwaitExpressionSyntax_Expression(const expression::AwaitExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBinaryExpressionSyntax_Left(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBinaryExpressionSyntax_Left(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBinaryExpressionSyntax_OverloadedOperatorCall(const expression::BinaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBinaryExpressionSyntax_OverloadedOperatorCall(const expression::BinaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBinaryExpressionSyntax_Right(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBinaryExpressionSyntax_Right(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for ConversionOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCastExpressionSyntax_ConversionOperatorCall(const expression::CastExpressionSyntax& begin, const structure::ConversionOperatorDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for ConversionOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCastExpressionSyntax_ConversionOperatorCall(const expression::CastExpressionSyntax& begin, const structure::ConversionOperatorDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCastExpressionSyntax_Expression(const expression::CastExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCastExpressionSyntax_Expression(const expression::CastExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCastExpressionSyntax_Type(const expression::CastExpressionSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCastExpressionSyntax_Type(const expression::CastExpressionSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCheckedExpressionSyntax_Expression(const expression::CheckedExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCheckedExpressionSyntax_Expression(const expression::CheckedExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitConditionalAccessExpressionSyntax_Expression(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndConditionalAccessExpressionSyntax_Expression(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for WhenNotNull edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitConditionalAccessExpressionSyntax_WhenNotNull(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for WhenNotNull edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndConditionalAccessExpressionSyntax_WhenNotNull(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitConditionalExpressionSyntax_Condition(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndConditionalExpressionSyntax_Condition(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for WhenFalse edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitConditionalExpressionSyntax_WhenFalse(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for WhenFalse edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndConditionalExpressionSyntax_WhenFalse(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for WhenTrue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitConditionalExpressionSyntax_WhenTrue(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for WhenTrue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndConditionalExpressionSyntax_WhenTrue(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Designation edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDeclarationExpressionSyntax_Designation(const expression::DeclarationExpressionSyntax& begin, const structure::VariableDesignationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Designation edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDeclarationExpressionSyntax_Designation(const expression::DeclarationExpressionSyntax& begin, const structure::VariableDesignationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDeclarationExpressionSyntax_Type(const expression::DeclarationExpressionSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDeclarationExpressionSyntax_Type(const expression::DeclarationExpressionSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDefaultExpressionSyntax_Type(const expression::DefaultExpressionSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDefaultExpressionSyntax_Type(const expression::DefaultExpressionSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for AccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitElementAccessExpressionSyntax_AccessorCall(const expression::ElementAccessExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for AccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndElementAccessExpressionSyntax_AccessorCall(const expression::ElementAccessExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitElementAccessExpressionSyntax_ArgumentList(const expression::ElementAccessExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndElementAccessExpressionSyntax_ArgumentList(const expression::ElementAccessExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitElementAccessExpressionSyntax_Expression(const expression::ElementAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndElementAccessExpressionSyntax_Expression(const expression::ElementAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitElementBindingExpressionSyntax_ArgumentList(const expression::ElementBindingExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndElementBindingExpressionSyntax_ArgumentList(const expression::ElementBindingExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for TypeArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitGenericNameSyntax_TypeArgumentList(const expression::GenericNameSyntax& begin, const structure::TypeArgumentListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for TypeArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndGenericNameSyntax_TypeArgumentList(const expression::GenericNameSyntax& begin, const structure::TypeArgumentListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for AccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIdentifierNameSyntax_AccessorCall(const expression::IdentifierNameSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for AccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIdentifierNameSyntax_AccessorCall(const expression::IdentifierNameSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for Declaration edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIdentifierNameSyntax_Declaration(const expression::IdentifierNameSyntax& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for Declaration edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIdentifierNameSyntax_Declaration(const expression::IdentifierNameSyntax& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitImplicitArrayCreationExpressionSyntax_Initializer(const expression::ImplicitArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndImplicitArrayCreationExpressionSyntax_Initializer(const expression::ImplicitArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitImplicitElementAccessSyntax_ArgumentList(const expression::ImplicitElementAccessSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndImplicitElementAccessSyntax_ArgumentList(const expression::ImplicitElementAccessSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitImplicitStackAllocArrayCreationExpressionSyntax_Initializer(const expression::ImplicitStackAllocArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndImplicitStackAllocArrayCreationExpressionSyntax_Initializer(const expression::ImplicitStackAllocArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expressions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitInitializerExpressionSyntax_Expressions(const expression::InitializerExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expressions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndInitializerExpressionSyntax_Expressions(const expression::InitializerExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Contents edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitInterpolatedStringExpressionSyntax_Contents(const expression::InterpolatedStringExpressionSyntax& begin, const structure::InterpolatedStringContentSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Contents edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndInterpolatedStringExpressionSyntax_Contents(const expression::InterpolatedStringExpressionSyntax& begin, const structure::InterpolatedStringContentSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitInvocationExpressionSyntax_ArgumentList(const expression::InvocationExpressionSyntax& begin, const structure::ArgumentListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndInvocationExpressionSyntax_ArgumentList(const expression::InvocationExpressionSyntax& begin, const structure::ArgumentListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitInvocationExpressionSyntax_Expression(const expression::InvocationExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndInvocationExpressionSyntax_Expression(const expression::InvocationExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for LocalFunctionCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitInvocationExpressionSyntax_LocalFunctionCall(const expression::InvocationExpressionSyntax& begin, const statement::LocalFunctionStatementSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for LocalFunctionCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndInvocationExpressionSyntax_LocalFunctionCall(const expression::InvocationExpressionSyntax& begin, const statement::LocalFunctionStatementSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for MethodCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitInvocationExpressionSyntax_MethodCall(const expression::InvocationExpressionSyntax& begin, const structure::MethodDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for MethodCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndInvocationExpressionSyntax_MethodCall(const expression::InvocationExpressionSyntax& begin, const structure::MethodDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIsPatternExpressionSyntax_Expression(const expression::IsPatternExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIsPatternExpressionSyntax_Expression(const expression::IsPatternExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Pattern edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIsPatternExpressionSyntax_Pattern(const expression::IsPatternExpressionSyntax& begin, const structure::PatternSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Pattern edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIsPatternExpressionSyntax_Pattern(const expression::IsPatternExpressionSyntax& begin, const structure::PatternSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMakeRefExpressionSyntax_Expression(const expression::MakeRefExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMakeRefExpressionSyntax_Expression(const expression::MakeRefExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMemberAccessExpressionSyntax_Expression(const expression::MemberAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMemberAccessExpressionSyntax_Expression(const expression::MemberAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMemberAccessExpressionSyntax_Name(const expression::MemberAccessExpressionSyntax& begin, const expression::SimpleNameSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMemberAccessExpressionSyntax_Name(const expression::MemberAccessExpressionSyntax& begin, const expression::SimpleNameSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMemberBindingExpressionSyntax_Name(const expression::MemberBindingExpressionSyntax& begin, const expression::SimpleNameSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMemberBindingExpressionSyntax_Name(const expression::MemberBindingExpressionSyntax& begin, const expression::SimpleNameSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNullableTypeSyntax_ElementType(const expression::NullableTypeSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNullableTypeSyntax_ElementType(const expression::NullableTypeSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitObjectCreationExpressionSyntax_ArgumentList(const expression::ObjectCreationExpressionSyntax& begin, const structure::ArgumentListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndObjectCreationExpressionSyntax_ArgumentList(const expression::ObjectCreationExpressionSyntax& begin, const structure::ArgumentListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for ConstructorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitObjectCreationExpressionSyntax_ConstructorCall(const expression::ObjectCreationExpressionSyntax& begin, const structure::ConstructorDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for ConstructorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndObjectCreationExpressionSyntax_ConstructorCall(const expression::ObjectCreationExpressionSyntax& begin, const structure::ConstructorDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitObjectCreationExpressionSyntax_Initializer(const expression::ObjectCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndObjectCreationExpressionSyntax_Initializer(const expression::ObjectCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitObjectCreationExpressionSyntax_Type(const expression::ObjectCreationExpressionSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndObjectCreationExpressionSyntax_Type(const expression::ObjectCreationExpressionSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitParenthesizedExpressionSyntax_Expression(const expression::ParenthesizedExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndParenthesizedExpressionSyntax_Expression(const expression::ParenthesizedExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitParenthesizedLambdaExpressionSyntax_ParameterList(const expression::ParenthesizedLambdaExpressionSyntax& begin, const structure::ParameterListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndParenthesizedLambdaExpressionSyntax_ParameterList(const expression::ParenthesizedLambdaExpressionSyntax& begin, const structure::ParameterListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitPointerTypeSyntax_ElementType(const expression::PointerTypeSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndPointerTypeSyntax_ElementType(const expression::PointerTypeSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Operand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitPostfixUnaryExpressionSyntax_Operand(const expression::PostfixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Operand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndPostfixUnaryExpressionSyntax_Operand(const expression::PostfixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitPostfixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PostfixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndPostfixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PostfixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Operand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitPrefixUnaryExpressionSyntax_Operand(const expression::PrefixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Operand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndPrefixUnaryExpressionSyntax_Operand(const expression::PrefixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitPrefixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PrefixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndPrefixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PrefixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitQualifiedNameSyntax_Left(const expression::QualifiedNameSyntax& begin, const expression::NameSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndQualifiedNameSyntax_Left(const expression::QualifiedNameSyntax& begin, const expression::NameSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitQualifiedNameSyntax_Right(const expression::QualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndQualifiedNameSyntax_Right(const expression::QualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitQueryExpressionSyntax_Body(const expression::QueryExpressionSyntax& begin, const structure::QueryBodySyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndQueryExpressionSyntax_Body(const expression::QueryExpressionSyntax& begin, const structure::QueryBodySyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for FromClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitQueryExpressionSyntax_FromClause(const expression::QueryExpressionSyntax& begin, const structure::FromClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for FromClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndQueryExpressionSyntax_FromClause(const expression::QueryExpressionSyntax& begin, const structure::FromClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for LeftOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitRangeExpressionSyntax_LeftOperand(const expression::RangeExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for LeftOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndRangeExpressionSyntax_LeftOperand(const expression::RangeExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for RightOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitRangeExpressionSyntax_RightOperand(const expression::RangeExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for RightOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndRangeExpressionSyntax_RightOperand(const expression::RangeExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitRefExpressionSyntax_Expression(const expression::RefExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndRefExpressionSyntax_Expression(const expression::RefExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitRefTypeExpressionSyntax_Expression(const expression::RefTypeExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndRefTypeExpressionSyntax_Expression(const expression::RefTypeExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitRefTypeSyntax_Type(const expression::RefTypeSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndRefTypeSyntax_Type(const expression::RefTypeSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitRefValueExpressionSyntax_Expression(const expression::RefValueExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndRefValueExpressionSyntax_Expression(const expression::RefValueExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitRefValueExpressionSyntax_Type(const expression::RefValueExpressionSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndRefValueExpressionSyntax_Type(const expression::RefValueExpressionSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Parameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSimpleLambdaExpressionSyntax_Parameter(const expression::SimpleLambdaExpressionSyntax& begin, const structure::ParameterSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Parameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSimpleLambdaExpressionSyntax_Parameter(const expression::SimpleLambdaExpressionSyntax& begin, const structure::ParameterSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSizeOfExpressionSyntax_Type(const expression::SizeOfExpressionSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSizeOfExpressionSyntax_Type(const expression::SizeOfExpressionSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitStackAllocArrayCreationExpressionSyntax_Initializer(const expression::StackAllocArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndStackAllocArrayCreationExpressionSyntax_Initializer(const expression::StackAllocArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitStackAllocArrayCreationExpressionSyntax_Type(const expression::StackAllocArrayCreationExpressionSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndStackAllocArrayCreationExpressionSyntax_Type(const expression::StackAllocArrayCreationExpressionSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Arms edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSwitchExpressionSyntax_Arms(const expression::SwitchExpressionSyntax& begin, const structure::SwitchExpressionArmSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Arms edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSwitchExpressionSyntax_Arms(const expression::SwitchExpressionSyntax& begin, const structure::SwitchExpressionArmSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for GoverningExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSwitchExpressionSyntax_GoverningExpression(const expression::SwitchExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for GoverningExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSwitchExpressionSyntax_GoverningExpression(const expression::SwitchExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitThrowExpressionSyntax_Expression(const expression::ThrowExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndThrowExpressionSyntax_Expression(const expression::ThrowExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTupleExpressionSyntax_Arguments(const expression::TupleExpressionSyntax& begin, const structure::ArgumentSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTupleExpressionSyntax_Arguments(const expression::TupleExpressionSyntax& begin, const structure::ArgumentSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Elements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTupleTypeSyntax_Elements(const expression::TupleTypeSyntax& begin, const structure::TupleElementSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Elements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTupleTypeSyntax_Elements(const expression::TupleTypeSyntax& begin, const structure::TupleElementSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeOfExpressionSyntax_Type(const expression::TypeOfExpressionSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeOfExpressionSyntax_Type(const expression::TypeOfExpressionSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for OriginalDefinition edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeSyntax_OriginalDefinition(const expression::TypeSyntax& begin, const structure::MemberDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for OriginalDefinition edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeSyntax_OriginalDefinition(const expression::TypeSyntax& begin, const structure::MemberDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Statements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBlockSyntax_Statements(const statement::BlockSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Statements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBlockSyntax_Statements(const statement::BlockSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCheckedStatementSyntax_Block(const statement::CheckedStatementSyntax& begin, const statement::BlockSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCheckedStatementSyntax_Block(const statement::CheckedStatementSyntax& begin, const statement::BlockSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCommonForEachStatementSyntax_Expression(const statement::CommonForEachStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCommonForEachStatementSyntax_Expression(const statement::CommonForEachStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCommonForEachStatementSyntax_Statement(const statement::CommonForEachStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCommonForEachStatementSyntax_Statement(const statement::CommonForEachStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDoStatementSyntax_Condition(const statement::DoStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDoStatementSyntax_Condition(const statement::DoStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDoStatementSyntax_Statement(const statement::DoStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDoStatementSyntax_Statement(const statement::DoStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitExpressionStatementSyntax_Expression(const statement::ExpressionStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndExpressionStatementSyntax_Expression(const statement::ExpressionStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFixedStatementSyntax_Declaration(const statement::FixedStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFixedStatementSyntax_Declaration(const statement::FixedStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFixedStatementSyntax_Statement(const statement::FixedStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFixedStatementSyntax_Statement(const statement::FixedStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitForEachStatementSyntax_Type(const statement::ForEachStatementSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndForEachStatementSyntax_Type(const statement::ForEachStatementSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Variable edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitForEachVariableStatementSyntax_Variable(const statement::ForEachVariableStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Variable edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndForEachVariableStatementSyntax_Variable(const statement::ForEachVariableStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitForStatementSyntax_Condition(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndForStatementSyntax_Condition(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitForStatementSyntax_Declaration(const statement::ForStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndForStatementSyntax_Declaration(const statement::ForStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Incrementors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitForStatementSyntax_Incrementors(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Incrementors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndForStatementSyntax_Incrementors(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Initializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitForStatementSyntax_Initializers(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Initializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndForStatementSyntax_Initializers(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitForStatementSyntax_Statement(const statement::ForStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndForStatementSyntax_Statement(const statement::ForStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitGotoStatementSyntax_Expression(const statement::GotoStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndGotoStatementSyntax_Expression(const statement::GotoStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIfStatementSyntax_Condition(const statement::IfStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIfStatementSyntax_Condition(const statement::IfStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Else edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIfStatementSyntax_Else(const statement::IfStatementSyntax& begin, const structure::ElseClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Else edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIfStatementSyntax_Else(const statement::IfStatementSyntax& begin, const structure::ElseClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIfStatementSyntax_Statement(const statement::IfStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIfStatementSyntax_Statement(const statement::IfStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitLabeledStatementSyntax_Statement(const statement::LabeledStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndLabeledStatementSyntax_Statement(const statement::LabeledStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitLocalDeclarationStatementSyntax_Declaration(const statement::LocalDeclarationStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndLocalDeclarationStatementSyntax_Declaration(const statement::LocalDeclarationStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitLocalFunctionStatementSyntax_Body(const statement::LocalFunctionStatementSyntax& begin, const statement::BlockSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndLocalFunctionStatementSyntax_Body(const statement::LocalFunctionStatementSyntax& begin, const statement::BlockSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitLocalFunctionStatementSyntax_ConstraintClauses(const statement::LocalFunctionStatementSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndLocalFunctionStatementSyntax_ConstraintClauses(const statement::LocalFunctionStatementSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitLocalFunctionStatementSyntax_ExpressionBody(const statement::LocalFunctionStatementSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndLocalFunctionStatementSyntax_ExpressionBody(const statement::LocalFunctionStatementSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitLocalFunctionStatementSyntax_ParameterList(const statement::LocalFunctionStatementSyntax& begin, const structure::ParameterListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndLocalFunctionStatementSyntax_ParameterList(const statement::LocalFunctionStatementSyntax& begin, const structure::ParameterListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitLocalFunctionStatementSyntax_ReturnType(const statement::LocalFunctionStatementSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndLocalFunctionStatementSyntax_ReturnType(const statement::LocalFunctionStatementSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for TypeParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitLocalFunctionStatementSyntax_TypeParameterList(const statement::LocalFunctionStatementSyntax& begin, const structure::TypeParameterListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for TypeParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndLocalFunctionStatementSyntax_TypeParameterList(const statement::LocalFunctionStatementSyntax& begin, const structure::TypeParameterListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitLockStatementSyntax_Expression(const statement::LockStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndLockStatementSyntax_Expression(const statement::LockStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitLockStatementSyntax_Statement(const statement::LockStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndLockStatementSyntax_Statement(const statement::LockStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitReturnStatementSyntax_Expression(const statement::ReturnStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndReturnStatementSyntax_Expression(const statement::ReturnStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitStatementSyntax_AttributeLists(const statement::StatementSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndStatementSyntax_AttributeLists(const statement::StatementSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSwitchStatementSyntax_Expression(const statement::SwitchStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSwitchStatementSyntax_Expression(const statement::SwitchStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Sections edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSwitchStatementSyntax_Sections(const statement::SwitchStatementSyntax& begin, const structure::SwitchSectionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Sections edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSwitchStatementSyntax_Sections(const statement::SwitchStatementSyntax& begin, const structure::SwitchSectionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitThrowStatementSyntax_Expression(const statement::ThrowStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndThrowStatementSyntax_Expression(const statement::ThrowStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTryStatementSyntax_Block(const statement::TryStatementSyntax& begin, const statement::BlockSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTryStatementSyntax_Block(const statement::TryStatementSyntax& begin, const statement::BlockSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Catches edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTryStatementSyntax_Catches(const statement::TryStatementSyntax& begin, const structure::CatchClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Catches edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTryStatementSyntax_Catches(const statement::TryStatementSyntax& begin, const structure::CatchClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Finally edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTryStatementSyntax_Finally(const statement::TryStatementSyntax& begin, const structure::FinallyClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Finally edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTryStatementSyntax_Finally(const statement::TryStatementSyntax& begin, const structure::FinallyClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitUnsafeStatementSyntax_Block(const statement::UnsafeStatementSyntax& begin, const statement::BlockSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndUnsafeStatementSyntax_Block(const statement::UnsafeStatementSyntax& begin, const statement::BlockSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitUsingStatementSyntax_Declaration(const statement::UsingStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndUsingStatementSyntax_Declaration(const statement::UsingStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitUsingStatementSyntax_Expression(const statement::UsingStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndUsingStatementSyntax_Expression(const statement::UsingStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitUsingStatementSyntax_Statement(const statement::UsingStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndUsingStatementSyntax_Statement(const statement::UsingStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitWhileStatementSyntax_Condition(const statement::WhileStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndWhileStatementSyntax_Condition(const statement::WhileStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitWhileStatementSyntax_Statement(const statement::WhileStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndWhileStatementSyntax_Statement(const statement::WhileStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitYieldStatementSyntax_Expression(const statement::YieldStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndYieldStatementSyntax_Expression(const statement::YieldStatementSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAccessorDeclarationSyntax_AttributeLists(const structure::AccessorDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAccessorDeclarationSyntax_AttributeLists(const structure::AccessorDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAccessorDeclarationSyntax_Body(const structure::AccessorDeclarationSyntax& begin, const statement::BlockSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAccessorDeclarationSyntax_Body(const structure::AccessorDeclarationSyntax& begin, const statement::BlockSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAccessorDeclarationSyntax_ExpressionBody(const structure::AccessorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAccessorDeclarationSyntax_ExpressionBody(const structure::AccessorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Accessors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAccessorListSyntax_Accessors(const structure::AccessorListSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Accessors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAccessorListSyntax_Accessors(const structure::AccessorListSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAnonymousObjectMemberDeclaratorSyntax_Expression(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAnonymousObjectMemberDeclaratorSyntax_Expression(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for NameEquals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAnonymousObjectMemberDeclaratorSyntax_NameEquals(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const structure::NameEqualsSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for NameEquals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAnonymousObjectMemberDeclaratorSyntax_NameEquals(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const structure::NameEqualsSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitArgumentSyntax_Expression(const structure::ArgumentSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndArgumentSyntax_Expression(const structure::ArgumentSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for NameColon edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitArgumentSyntax_NameColon(const structure::ArgumentSyntax& begin, const structure::NameColonSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for NameColon edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndArgumentSyntax_NameColon(const structure::ArgumentSyntax& begin, const structure::NameColonSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Sizes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitArrayRankSpecifierSyntax_Sizes(const structure::ArrayRankSpecifierSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Sizes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndArrayRankSpecifierSyntax_Sizes(const structure::ArrayRankSpecifierSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitArrowExpressionClauseSyntax_Expression(const structure::ArrowExpressionClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndArrowExpressionClauseSyntax_Expression(const structure::ArrowExpressionClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAttributeArgumentListSyntax_Arguments(const structure::AttributeArgumentListSyntax& begin, const structure::AttributeArgumentSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAttributeArgumentListSyntax_Arguments(const structure::AttributeArgumentListSyntax& begin, const structure::AttributeArgumentSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAttributeArgumentSyntax_Expression(const structure::AttributeArgumentSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAttributeArgumentSyntax_Expression(const structure::AttributeArgumentSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for NameColon edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAttributeArgumentSyntax_NameColon(const structure::AttributeArgumentSyntax& begin, const structure::NameColonSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for NameColon edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAttributeArgumentSyntax_NameColon(const structure::AttributeArgumentSyntax& begin, const structure::NameColonSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for NameEquals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAttributeArgumentSyntax_NameEquals(const structure::AttributeArgumentSyntax& begin, const structure::NameEqualsSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for NameEquals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAttributeArgumentSyntax_NameEquals(const structure::AttributeArgumentSyntax& begin, const structure::NameEqualsSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAttributeListSyntax_Attributes(const structure::AttributeListSyntax& begin, const structure::AttributeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAttributeListSyntax_Attributes(const structure::AttributeListSyntax& begin, const structure::AttributeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Target edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAttributeListSyntax_Target(const structure::AttributeListSyntax& begin, const structure::AttributeTargetSpecifierSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Target edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAttributeListSyntax_Target(const structure::AttributeListSyntax& begin, const structure::AttributeTargetSpecifierSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAttributeSyntax_ArgumentList(const structure::AttributeSyntax& begin, const structure::AttributeArgumentListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAttributeSyntax_ArgumentList(const structure::AttributeSyntax& begin, const structure::AttributeArgumentListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAttributeSyntax_Name(const structure::AttributeSyntax& begin, const expression::NameSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAttributeSyntax_Name(const structure::AttributeSyntax& begin, const expression::NameSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBaseArgumentListSyntax_Arguments(const structure::BaseArgumentListSyntax& begin, const structure::ArgumentSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBaseArgumentListSyntax_Arguments(const structure::BaseArgumentListSyntax& begin, const structure::ArgumentSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBaseCrefParameterListSyntax_Parameters(const structure::BaseCrefParameterListSyntax& begin, const structure::CrefParameterSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBaseCrefParameterListSyntax_Parameters(const structure::BaseCrefParameterListSyntax& begin, const structure::CrefParameterSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBaseFieldDeclarationSyntax_AttributeLists(const structure::BaseFieldDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBaseFieldDeclarationSyntax_AttributeLists(const structure::BaseFieldDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBaseFieldDeclarationSyntax_Declaration(const structure::BaseFieldDeclarationSyntax& begin, const structure::VariableDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBaseFieldDeclarationSyntax_Declaration(const structure::BaseFieldDeclarationSyntax& begin, const structure::VariableDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Types edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBaseListSyntax_Types(const structure::BaseListSyntax& begin, const structure::BaseTypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Types edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBaseListSyntax_Types(const structure::BaseListSyntax& begin, const structure::BaseTypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for AccessedEnumMembers edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBaseMethodDeclarationSyntax_AccessedEnumMembers(const structure::BaseMethodDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for AccessedEnumMembers edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBaseMethodDeclarationSyntax_AccessedEnumMembers(const structure::BaseMethodDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBaseMethodDeclarationSyntax_AttributeLists(const structure::BaseMethodDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBaseMethodDeclarationSyntax_AttributeLists(const structure::BaseMethodDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBaseMethodDeclarationSyntax_Body(const structure::BaseMethodDeclarationSyntax& begin, const statement::BlockSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBaseMethodDeclarationSyntax_Body(const structure::BaseMethodDeclarationSyntax& begin, const statement::BlockSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBaseMethodDeclarationSyntax_ExpressionBody(const structure::BaseMethodDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBaseMethodDeclarationSyntax_ExpressionBody(const structure::BaseMethodDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBaseMethodDeclarationSyntax_ParameterList(const structure::BaseMethodDeclarationSyntax& begin, const structure::ParameterListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBaseMethodDeclarationSyntax_ParameterList(const structure::BaseMethodDeclarationSyntax& begin, const structure::ParameterListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBaseParameterListSyntax_Parameters(const structure::BaseParameterListSyntax& begin, const structure::ParameterSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBaseParameterListSyntax_Parameters(const structure::BaseParameterListSyntax& begin, const structure::ParameterSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for AccessorList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBasePropertyDeclarationSyntax_AccessorList(const structure::BasePropertyDeclarationSyntax& begin, const structure::AccessorListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for AccessorList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBasePropertyDeclarationSyntax_AccessorList(const structure::BasePropertyDeclarationSyntax& begin, const structure::AccessorListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBasePropertyDeclarationSyntax_AttributeLists(const structure::BasePropertyDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBasePropertyDeclarationSyntax_AttributeLists(const structure::BasePropertyDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ExplicitInterfaceSpecifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::BasePropertyDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ExplicitInterfaceSpecifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::BasePropertyDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBasePropertyDeclarationSyntax_Type(const structure::BasePropertyDeclarationSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBasePropertyDeclarationSyntax_Type(const structure::BasePropertyDeclarationSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBaseTypeDeclarationSyntax_AttributeLists(const structure::BaseTypeDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBaseTypeDeclarationSyntax_AttributeLists(const structure::BaseTypeDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for BaseList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBaseTypeDeclarationSyntax_BaseList(const structure::BaseTypeDeclarationSyntax& begin, const structure::BaseListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for BaseList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBaseTypeDeclarationSyntax_BaseList(const structure::BaseTypeDeclarationSyntax& begin, const structure::BaseListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBaseTypeSyntax_Type(const structure::BaseTypeSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBaseTypeSyntax_Type(const structure::BaseTypeSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Pattern edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCasePatternSwitchLabelSyntax_Pattern(const structure::CasePatternSwitchLabelSyntax& begin, const structure::PatternSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Pattern edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCasePatternSwitchLabelSyntax_Pattern(const structure::CasePatternSwitchLabelSyntax& begin, const structure::PatternSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for WhenClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCasePatternSwitchLabelSyntax_WhenClause(const structure::CasePatternSwitchLabelSyntax& begin, const structure::WhenClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for WhenClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCasePatternSwitchLabelSyntax_WhenClause(const structure::CasePatternSwitchLabelSyntax& begin, const structure::WhenClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCaseSwitchLabelSyntax_Value(const structure::CaseSwitchLabelSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCaseSwitchLabelSyntax_Value(const structure::CaseSwitchLabelSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCatchClauseSyntax_Block(const structure::CatchClauseSyntax& begin, const statement::BlockSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCatchClauseSyntax_Block(const structure::CatchClauseSyntax& begin, const statement::BlockSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCatchClauseSyntax_Declaration(const structure::CatchClauseSyntax& begin, const structure::CatchDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCatchClauseSyntax_Declaration(const structure::CatchClauseSyntax& begin, const structure::CatchDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Filter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCatchClauseSyntax_Filter(const structure::CatchClauseSyntax& begin, const structure::CatchFilterClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Filter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCatchClauseSyntax_Filter(const structure::CatchClauseSyntax& begin, const structure::CatchFilterClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCatchDeclarationSyntax_Type(const structure::CatchDeclarationSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCatchDeclarationSyntax_Type(const structure::CatchDeclarationSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for FilterExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCatchFilterClauseSyntax_FilterExpression(const structure::CatchFilterClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for FilterExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCatchFilterClauseSyntax_FilterExpression(const structure::CatchFilterClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCompilationUnitSyntax_AttributeLists(const structure::CompilationUnitSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCompilationUnitSyntax_AttributeLists(const structure::CompilationUnitSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Externs edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCompilationUnitSyntax_Externs(const structure::CompilationUnitSyntax& begin, const structure::ExternAliasDirectiveSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Externs edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCompilationUnitSyntax_Externs(const structure::CompilationUnitSyntax& begin, const structure::ExternAliasDirectiveSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCompilationUnitSyntax_Members(const structure::CompilationUnitSyntax& begin, const structure::MemberDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCompilationUnitSyntax_Members(const structure::CompilationUnitSyntax& begin, const structure::MemberDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Usings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCompilationUnitSyntax_Usings(const structure::CompilationUnitSyntax& begin, const structure::UsingDirectiveSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Usings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCompilationUnitSyntax_Usings(const structure::CompilationUnitSyntax& begin, const structure::UsingDirectiveSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitConstantPatternSyntax_Expression(const structure::ConstantPatternSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndConstantPatternSyntax_Expression(const structure::ConstantPatternSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitConstructorDeclarationSyntax_Initializer(const structure::ConstructorDeclarationSyntax& begin, const structure::ConstructorInitializerSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndConstructorDeclarationSyntax_Initializer(const structure::ConstructorDeclarationSyntax& begin, const structure::ConstructorInitializerSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitConstructorInitializerSyntax_ArgumentList(const structure::ConstructorInitializerSyntax& begin, const structure::ArgumentListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndConstructorInitializerSyntax_ArgumentList(const structure::ConstructorInitializerSyntax& begin, const structure::ArgumentListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for ConstructorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitConstructorInitializerSyntax_ConstructorCall(const structure::ConstructorInitializerSyntax& begin, const structure::ConstructorDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for ConstructorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndConstructorInitializerSyntax_ConstructorCall(const structure::ConstructorInitializerSyntax& begin, const structure::ConstructorDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitConversionOperatorDeclarationSyntax_Type(const structure::ConversionOperatorDeclarationSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndConversionOperatorDeclarationSyntax_Type(const structure::ConversionOperatorDeclarationSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitConversionOperatorMemberCrefSyntax_Parameters(const structure::ConversionOperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndConversionOperatorMemberCrefSyntax_Parameters(const structure::ConversionOperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitConversionOperatorMemberCrefSyntax_Type(const structure::ConversionOperatorMemberCrefSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndConversionOperatorMemberCrefSyntax_Type(const structure::ConversionOperatorMemberCrefSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCrefParameterSyntax_Type(const structure::CrefParameterSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCrefParameterSyntax_Type(const structure::CrefParameterSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Designation edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDeclarationPatternSyntax_Designation(const structure::DeclarationPatternSyntax& begin, const structure::VariableDesignationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Designation edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDeclarationPatternSyntax_Designation(const structure::DeclarationPatternSyntax& begin, const structure::VariableDesignationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDeclarationPatternSyntax_Type(const structure::DeclarationPatternSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDeclarationPatternSyntax_Type(const structure::DeclarationPatternSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDelegateDeclarationSyntax_AttributeLists(const structure::DelegateDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDelegateDeclarationSyntax_AttributeLists(const structure::DelegateDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDelegateDeclarationSyntax_ConstraintClauses(const structure::DelegateDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDelegateDeclarationSyntax_ConstraintClauses(const structure::DelegateDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDelegateDeclarationSyntax_ParameterList(const structure::DelegateDeclarationSyntax& begin, const structure::ParameterListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDelegateDeclarationSyntax_ParameterList(const structure::DelegateDeclarationSyntax& begin, const structure::ParameterListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDelegateDeclarationSyntax_ReturnType(const structure::DelegateDeclarationSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDelegateDeclarationSyntax_ReturnType(const structure::DelegateDeclarationSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitElseClauseSyntax_Statement(const structure::ElseClauseSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndElseClauseSyntax_Statement(const structure::ElseClauseSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEnumDeclarationSyntax_Members(const structure::EnumDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndEnumDeclarationSyntax_Members(const structure::EnumDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEnumMemberDeclarationSyntax_AttributeLists(const structure::EnumMemberDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndEnumMemberDeclarationSyntax_AttributeLists(const structure::EnumMemberDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for EqualsValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEnumMemberDeclarationSyntax_EqualsValue(const structure::EnumMemberDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for EqualsValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndEnumMemberDeclarationSyntax_EqualsValue(const structure::EnumMemberDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEqualsValueClauseSyntax_Value(const structure::EqualsValueClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndEqualsValueClauseSyntax_Value(const structure::EqualsValueClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitExplicitInterfaceSpecifierSyntax_Name(const structure::ExplicitInterfaceSpecifierSyntax& begin, const expression::NameSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndExplicitInterfaceSpecifierSyntax_Name(const structure::ExplicitInterfaceSpecifierSyntax& begin, const expression::NameSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFinallyClauseSyntax_Block(const structure::FinallyClauseSyntax& begin, const statement::BlockSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFinallyClauseSyntax_Block(const structure::FinallyClauseSyntax& begin, const statement::BlockSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFromClauseSyntax_Expression(const structure::FromClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFromClauseSyntax_Expression(const structure::FromClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFromClauseSyntax_Type(const structure::FromClauseSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFromClauseSyntax_Type(const structure::FromClauseSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitGlobalStatementSyntax_Statement(const structure::GlobalStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndGlobalStatementSyntax_Statement(const structure::GlobalStatementSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ByExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitGroupClauseSyntax_ByExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ByExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndGroupClauseSyntax_ByExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for GroupExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitGroupClauseSyntax_GroupExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for GroupExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndGroupClauseSyntax_GroupExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIncompleteMemberSyntax_AttributeLists(const structure::IncompleteMemberSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIncompleteMemberSyntax_AttributeLists(const structure::IncompleteMemberSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIncompleteMemberSyntax_Type(const structure::IncompleteMemberSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIncompleteMemberSyntax_Type(const structure::IncompleteMemberSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIndexerDeclarationSyntax_ExpressionBody(const structure::IndexerDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIndexerDeclarationSyntax_ExpressionBody(const structure::IndexerDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIndexerDeclarationSyntax_ParameterList(const structure::IndexerDeclarationSyntax& begin, const structure::BracketedParameterListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIndexerDeclarationSyntax_ParameterList(const structure::IndexerDeclarationSyntax& begin, const structure::BracketedParameterListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIndexerMemberCrefSyntax_Parameters(const structure::IndexerMemberCrefSyntax& begin, const structure::CrefBracketedParameterListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIndexerMemberCrefSyntax_Parameters(const structure::IndexerMemberCrefSyntax& begin, const structure::CrefBracketedParameterListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitInterpolationAlignmentClauseSyntax_Value(const structure::InterpolationAlignmentClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndInterpolationAlignmentClauseSyntax_Value(const structure::InterpolationAlignmentClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for AlignmentClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitInterpolationSyntax_AlignmentClause(const structure::InterpolationSyntax& begin, const structure::InterpolationAlignmentClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for AlignmentClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndInterpolationSyntax_AlignmentClause(const structure::InterpolationSyntax& begin, const structure::InterpolationAlignmentClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitInterpolationSyntax_Expression(const structure::InterpolationSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndInterpolationSyntax_Expression(const structure::InterpolationSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for FormatClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitInterpolationSyntax_FormatClause(const structure::InterpolationSyntax& begin, const structure::InterpolationFormatClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for FormatClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndInterpolationSyntax_FormatClause(const structure::InterpolationSyntax& begin, const structure::InterpolationFormatClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for InExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitJoinClauseSyntax_InExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for InExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndJoinClauseSyntax_InExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Into edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitJoinClauseSyntax_Into(const structure::JoinClauseSyntax& begin, const structure::JoinIntoClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Into edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndJoinClauseSyntax_Into(const structure::JoinClauseSyntax& begin, const structure::JoinIntoClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for LeftExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitJoinClauseSyntax_LeftExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for LeftExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndJoinClauseSyntax_LeftExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for RightExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitJoinClauseSyntax_RightExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for RightExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndJoinClauseSyntax_RightExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitJoinClauseSyntax_Type(const structure::JoinClauseSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndJoinClauseSyntax_Type(const structure::JoinClauseSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitLetClauseSyntax_Expression(const structure::LetClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndLetClauseSyntax_Expression(const structure::LetClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethodDeclarationSyntax_ConstraintClauses(const structure::MethodDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethodDeclarationSyntax_ConstraintClauses(const structure::MethodDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ExplicitInterfaceSpecifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethodDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::MethodDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ExplicitInterfaceSpecifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethodDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::MethodDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethodDeclarationSyntax_ReturnType(const structure::MethodDeclarationSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethodDeclarationSyntax_ReturnType(const structure::MethodDeclarationSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNameColonSyntax_Name(const structure::NameColonSyntax& begin, const expression::IdentifierNameSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNameColonSyntax_Name(const structure::NameColonSyntax& begin, const expression::IdentifierNameSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNameEqualsSyntax_Name(const structure::NameEqualsSyntax& begin, const expression::IdentifierNameSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNameEqualsSyntax_Name(const structure::NameEqualsSyntax& begin, const expression::IdentifierNameSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNameMemberCrefSyntax_Name(const structure::NameMemberCrefSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNameMemberCrefSyntax_Name(const structure::NameMemberCrefSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNameMemberCrefSyntax_Parameters(const structure::NameMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNameMemberCrefSyntax_Parameters(const structure::NameMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Externs edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNamespaceDeclarationSyntax_Externs(const structure::NamespaceDeclarationSyntax& begin, const structure::ExternAliasDirectiveSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Externs edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNamespaceDeclarationSyntax_Externs(const structure::NamespaceDeclarationSyntax& begin, const structure::ExternAliasDirectiveSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNamespaceDeclarationSyntax_Members(const structure::NamespaceDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNamespaceDeclarationSyntax_Members(const structure::NamespaceDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNamespaceDeclarationSyntax_Name(const structure::NamespaceDeclarationSyntax& begin, const expression::NameSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNamespaceDeclarationSyntax_Name(const structure::NamespaceDeclarationSyntax& begin, const expression::NameSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Usings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNamespaceDeclarationSyntax_Usings(const structure::NamespaceDeclarationSyntax& begin, const structure::UsingDirectiveSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Usings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNamespaceDeclarationSyntax_Usings(const structure::NamespaceDeclarationSyntax& begin, const structure::UsingDirectiveSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitOperatorDeclarationSyntax_ReturnType(const structure::OperatorDeclarationSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndOperatorDeclarationSyntax_ReturnType(const structure::OperatorDeclarationSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitOperatorMemberCrefSyntax_Parameters(const structure::OperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndOperatorMemberCrefSyntax_Parameters(const structure::OperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Orderings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitOrderByClauseSyntax_Orderings(const structure::OrderByClauseSyntax& begin, const structure::OrderingSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Orderings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndOrderByClauseSyntax_Orderings(const structure::OrderByClauseSyntax& begin, const structure::OrderingSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitOrderingSyntax_Expression(const structure::OrderingSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndOrderingSyntax_Expression(const structure::OrderingSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitParameterSyntax_AttributeLists(const structure::ParameterSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndParameterSyntax_AttributeLists(const structure::ParameterSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Default edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitParameterSyntax_Default(const structure::ParameterSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Default edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndParameterSyntax_Default(const structure::ParameterSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitParameterSyntax_Type(const structure::ParameterSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndParameterSyntax_Type(const structure::ParameterSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Variables edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitParenthesizedVariableDesignationSyntax_Variables(const structure::ParenthesizedVariableDesignationSyntax& begin, const structure::VariableDesignationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Variables edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndParenthesizedVariableDesignationSyntax_Variables(const structure::ParenthesizedVariableDesignationSyntax& begin, const structure::VariableDesignationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Subpatterns edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitPositionalPatternClauseSyntax_Subpatterns(const structure::PositionalPatternClauseSyntax& begin, const structure::SubpatternSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Subpatterns edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndPositionalPatternClauseSyntax_Subpatterns(const structure::PositionalPatternClauseSyntax& begin, const structure::SubpatternSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitPropertyDeclarationSyntax_ExpressionBody(const structure::PropertyDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndPropertyDeclarationSyntax_ExpressionBody(const structure::PropertyDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitPropertyDeclarationSyntax_Initializer(const structure::PropertyDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndPropertyDeclarationSyntax_Initializer(const structure::PropertyDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Subpatterns edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitPropertyPatternClauseSyntax_Subpatterns(const structure::PropertyPatternClauseSyntax& begin, const structure::SubpatternSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Subpatterns edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndPropertyPatternClauseSyntax_Subpatterns(const structure::PropertyPatternClauseSyntax& begin, const structure::SubpatternSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Container edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitQualifiedCrefSyntax_Container(const structure::QualifiedCrefSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Container edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndQualifiedCrefSyntax_Container(const structure::QualifiedCrefSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Member edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitQualifiedCrefSyntax_Member(const structure::QualifiedCrefSyntax& begin, const structure::MemberCrefSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Member edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndQualifiedCrefSyntax_Member(const structure::QualifiedCrefSyntax& begin, const structure::MemberCrefSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Clauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitQueryBodySyntax_Clauses(const structure::QueryBodySyntax& begin, const structure::QueryClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Clauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndQueryBodySyntax_Clauses(const structure::QueryBodySyntax& begin, const structure::QueryClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Continuation edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitQueryBodySyntax_Continuation(const structure::QueryBodySyntax& begin, const structure::QueryContinuationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Continuation edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndQueryBodySyntax_Continuation(const structure::QueryBodySyntax& begin, const structure::QueryContinuationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for SelectOrGroup edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitQueryBodySyntax_SelectOrGroup(const structure::QueryBodySyntax& begin, const structure::SelectOrGroupClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for SelectOrGroup edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndQueryBodySyntax_SelectOrGroup(const structure::QueryBodySyntax& begin, const structure::SelectOrGroupClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitQueryContinuationSyntax_Body(const structure::QueryContinuationSyntax& begin, const structure::QueryBodySyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndQueryContinuationSyntax_Body(const structure::QueryContinuationSyntax& begin, const structure::QueryBodySyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Designation edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitRecursivePatternSyntax_Designation(const structure::RecursivePatternSyntax& begin, const structure::VariableDesignationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Designation edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndRecursivePatternSyntax_Designation(const structure::RecursivePatternSyntax& begin, const structure::VariableDesignationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for PositionalPatternClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitRecursivePatternSyntax_PositionalPatternClause(const structure::RecursivePatternSyntax& begin, const structure::PositionalPatternClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for PositionalPatternClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndRecursivePatternSyntax_PositionalPatternClause(const structure::RecursivePatternSyntax& begin, const structure::PositionalPatternClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for PropertyPatternClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitRecursivePatternSyntax_PropertyPatternClause(const structure::RecursivePatternSyntax& begin, const structure::PropertyPatternClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for PropertyPatternClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndRecursivePatternSyntax_PropertyPatternClause(const structure::RecursivePatternSyntax& begin, const structure::PropertyPatternClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitRecursivePatternSyntax_Type(const structure::RecursivePatternSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndRecursivePatternSyntax_Type(const structure::RecursivePatternSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSelectClauseSyntax_Expression(const structure::SelectClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSelectClauseSyntax_Expression(const structure::SelectClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Pattern edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSubpatternSyntax_Pattern(const structure::SubpatternSyntax& begin, const structure::PatternSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Pattern edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSubpatternSyntax_Pattern(const structure::SubpatternSyntax& begin, const structure::PatternSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSwitchExpressionArmSyntax_Expression(const structure::SwitchExpressionArmSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSwitchExpressionArmSyntax_Expression(const structure::SwitchExpressionArmSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Pattern edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSwitchExpressionArmSyntax_Pattern(const structure::SwitchExpressionArmSyntax& begin, const structure::PatternSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Pattern edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSwitchExpressionArmSyntax_Pattern(const structure::SwitchExpressionArmSyntax& begin, const structure::PatternSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for WhenClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSwitchExpressionArmSyntax_WhenClause(const structure::SwitchExpressionArmSyntax& begin, const structure::WhenClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for WhenClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSwitchExpressionArmSyntax_WhenClause(const structure::SwitchExpressionArmSyntax& begin, const structure::WhenClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Labels edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSwitchSectionSyntax_Labels(const structure::SwitchSectionSyntax& begin, const structure::SwitchLabelSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Labels edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSwitchSectionSyntax_Labels(const structure::SwitchSectionSyntax& begin, const structure::SwitchLabelSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Statements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSwitchSectionSyntax_Statements(const structure::SwitchSectionSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Statements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSwitchSectionSyntax_Statements(const structure::SwitchSectionSyntax& begin, const statement::StatementSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTupleElementSyntax_Type(const structure::TupleElementSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTupleElementSyntax_Type(const structure::TupleElementSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeArgumentListSyntax_Arguments(const structure::TypeArgumentListSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeArgumentListSyntax_Arguments(const structure::TypeArgumentListSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeConstraintSyntax_Type(const structure::TypeConstraintSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeConstraintSyntax_Type(const structure::TypeConstraintSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeCrefSyntax_Type(const structure::TypeCrefSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeCrefSyntax_Type(const structure::TypeCrefSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeDeclarationSyntax_ConstraintClauses(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeDeclarationSyntax_ConstraintClauses(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeDeclarationSyntax_Members(const structure::TypeDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeDeclarationSyntax_Members(const structure::TypeDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for TypeParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeDeclarationSyntax_TypeParameterList(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for TypeParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeDeclarationSyntax_TypeParameterList(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Constraints edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeParameterConstraintClauseSyntax_Constraints(const structure::TypeParameterConstraintClauseSyntax& begin, const structure::TypeParameterConstraintSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Constraints edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeParameterConstraintClauseSyntax_Constraints(const structure::TypeParameterConstraintClauseSyntax& begin, const structure::TypeParameterConstraintSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeParameterConstraintClauseSyntax_Name(const structure::TypeParameterConstraintClauseSyntax& begin, const expression::IdentifierNameSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeParameterConstraintClauseSyntax_Name(const structure::TypeParameterConstraintClauseSyntax& begin, const expression::IdentifierNameSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeParameterListSyntax_Parameters(const structure::TypeParameterListSyntax& begin, const structure::TypeParameterSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeParameterListSyntax_Parameters(const structure::TypeParameterListSyntax& begin, const structure::TypeParameterSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeParameterSyntax_AttributeLists(const structure::TypeParameterSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeParameterSyntax_AttributeLists(const structure::TypeParameterSyntax& begin, const structure::AttributeListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Alias edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitUsingDirectiveSyntax_Alias(const structure::UsingDirectiveSyntax& begin, const structure::NameEqualsSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Alias edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndUsingDirectiveSyntax_Alias(const structure::UsingDirectiveSyntax& begin, const structure::NameEqualsSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitUsingDirectiveSyntax_Name(const structure::UsingDirectiveSyntax& begin, const expression::NameSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndUsingDirectiveSyntax_Name(const structure::UsingDirectiveSyntax& begin, const expression::NameSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Designation edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitVarPatternSyntax_Designation(const structure::VarPatternSyntax& begin, const structure::VariableDesignationSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Designation edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndVarPatternSyntax_Designation(const structure::VarPatternSyntax& begin, const structure::VariableDesignationSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitVariableDeclarationSyntax_Type(const structure::VariableDeclarationSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndVariableDeclarationSyntax_Type(const structure::VariableDeclarationSyntax& begin, const expression::TypeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Variables edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitVariableDeclarationSyntax_Variables(const structure::VariableDeclarationSyntax& begin, const structure::VariableDeclaratorSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Variables edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndVariableDeclarationSyntax_Variables(const structure::VariableDeclarationSyntax& begin, const structure::VariableDeclaratorSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitVariableDeclaratorSyntax_ArgumentList(const structure::VariableDeclaratorSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndVariableDeclaratorSyntax_ArgumentList(const structure::VariableDeclaratorSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitVariableDeclaratorSyntax_Initializer(const structure::VariableDeclaratorSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndVariableDeclaratorSyntax_Initializer(const structure::VariableDeclaratorSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitWhenClauseSyntax_Condition(const structure::WhenClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndWhenClauseSyntax_Condition(const structure::WhenClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitWhereClauseSyntax_Condition(const structure::WhereClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndWhereClauseSyntax_Condition(const structure::WhereClauseSyntax& begin, const expression::ExpressionSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitXmlAttributeSyntax_Name(const structure::XmlAttributeSyntax& begin, const structure::XmlNameSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndXmlAttributeSyntax_Name(const structure::XmlAttributeSyntax& begin, const structure::XmlNameSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Cref edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitXmlCrefAttributeSyntax_Cref(const structure::XmlCrefAttributeSyntax& begin, const structure::CrefSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Cref edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndXmlCrefAttributeSyntax_Cref(const structure::XmlCrefAttributeSyntax& begin, const structure::CrefSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitXmlElementEndTagSyntax_Name(const structure::XmlElementEndTagSyntax& begin, const structure::XmlNameSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndXmlElementEndTagSyntax_Name(const structure::XmlElementEndTagSyntax& begin, const structure::XmlNameSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitXmlElementStartTagSyntax_Attributes(const structure::XmlElementStartTagSyntax& begin, const structure::XmlAttributeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndXmlElementStartTagSyntax_Attributes(const structure::XmlElementStartTagSyntax& begin, const structure::XmlAttributeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitXmlElementStartTagSyntax_Name(const structure::XmlElementStartTagSyntax& begin, const structure::XmlNameSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndXmlElementStartTagSyntax_Name(const structure::XmlElementStartTagSyntax& begin, const structure::XmlNameSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Content edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitXmlElementSyntax_Content(const structure::XmlElementSyntax& begin, const structure::XmlNodeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Content edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndXmlElementSyntax_Content(const structure::XmlElementSyntax& begin, const structure::XmlNodeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for EndTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitXmlElementSyntax_EndTag(const structure::XmlElementSyntax& begin, const structure::XmlElementEndTagSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for EndTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndXmlElementSyntax_EndTag(const structure::XmlElementSyntax& begin, const structure::XmlElementEndTagSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for StartTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitXmlElementSyntax_StartTag(const structure::XmlElementSyntax& begin, const structure::XmlElementStartTagSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for StartTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndXmlElementSyntax_StartTag(const structure::XmlElementSyntax& begin, const structure::XmlElementStartTagSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitXmlEmptyElementSyntax_Attributes(const structure::XmlEmptyElementSyntax& begin, const structure::XmlAttributeSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndXmlEmptyElementSyntax_Attributes(const structure::XmlEmptyElementSyntax& begin, const structure::XmlAttributeSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitXmlEmptyElementSyntax_Name(const structure::XmlEmptyElementSyntax& begin, const structure::XmlNameSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndXmlEmptyElementSyntax_Name(const structure::XmlEmptyElementSyntax& begin, const structure::XmlNameSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Identifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitXmlNameAttributeSyntax_Identifier(const structure::XmlNameAttributeSyntax& begin, const expression::IdentifierNameSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Identifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndXmlNameAttributeSyntax_Identifier(const structure::XmlNameAttributeSyntax& begin, const expression::IdentifierNameSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Prefix edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitXmlNameSyntax_Prefix(const structure::XmlNameSyntax& begin, const structure::XmlPrefixSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Prefix edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndXmlNameSyntax_Prefix(const structure::XmlNameSyntax& begin, const structure::XmlPrefixSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitXmlProcessingInstructionSyntax_Name(const structure::XmlProcessingInstructionSyntax& begin, const structure::XmlNameSyntax& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndXmlProcessingInstructionSyntax_Name(const structure::XmlProcessingInstructionSyntax& begin, const structure::XmlNameSyntax& end) {
        visitAllEdgeEnd (begin, end);
      }

}}}
