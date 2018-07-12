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

#include "java/inc/java.h"

/**
* \file VisitorSimpleEdge.cpp
* \brief Contains declaration of VisitorSimpleEdge class.
*/

namespace columbus { namespace java { namespace asg {
      VisitorSimpleEdge::~VisitorSimpleEdge(){};

      /**
      * \brief Edge visitor for comments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCommentable_Comments(const base::Commentable& begin, const base::Comment& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for comments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCommentable_Comments(const base::Commentable& begin, const base::Comment& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasAnnotationName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAnnotation_HasAnnotationName(const expr::Annotation& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasAnnotationName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAnnotation_HasAnnotationName(const expr::Annotation& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitArrayTypeExpression_HasComponentType(const expr::ArrayTypeExpression& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndArrayTypeExpression_HasComponentType(const expr::ArrayTypeExpression& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasLeftOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBinary_HasLeftOperand(const expr::Binary& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasLeftOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBinary_HasLeftOperand(const expr::Binary& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasRightOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBinary_HasRightOperand(const expr::Binary& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasRightOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBinary_HasRightOperand(const expr::Binary& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitClassLiteral_HasComponentType(const expr::ClassLiteral& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndClassLiteral_HasComponentType(const expr::ClassLiteral& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitConditional_HasCondition(const expr::Conditional& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndConditional_HasCondition(const expr::Conditional& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTrueExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitConditional_HasTrueExpression(const expr::Conditional& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTrueExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndConditional_HasTrueExpression(const expr::Conditional& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasFalseExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitConditional_HasFalseExpression(const expr::Conditional& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasFalseExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndConditional_HasFalseExpression(const expr::Conditional& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasErrors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitErroneous_HasErrors(const expr::Erroneous& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasErrors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndErroneous_HasErrors(const expr::Erroneous& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasErrors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitErroneousTypeExpression_HasErrors(const expr::ErroneousTypeExpression& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasErrors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndErroneousTypeExpression_HasErrors(const expr::ErroneousTypeExpression& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for type edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitExpression_Type(const expr::Expression& begin, const type::Type& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for type edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndExpression_Type(const expr::Expression& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIdentifier_RefersTo(const expr::Identifier& begin, const base::Named& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIdentifier_RefersTo(const expr::Identifier& begin, const base::Named& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTypeOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitInstanceOf_HasTypeOperand(const expr::InstanceOf& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTypeOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndInstanceOf_HasTypeOperand(const expr::InstanceOf& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethodInvocation_HasTypeArguments(const expr::MethodInvocation& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethodInvocation_HasTypeArguments(const expr::MethodInvocation& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethodInvocation_HasArguments(const expr::MethodInvocation& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethodInvocation_HasArguments(const expr::MethodInvocation& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for invokes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethodInvocation_Invokes(const expr::MethodInvocation& begin, const struc::MethodDeclaration& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for invokes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethodInvocation_Invokes(const expr::MethodInvocation& begin, const struc::MethodDeclaration& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNewArray_HasComponentType(const expr::NewArray& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNewArray_HasComponentType(const expr::NewArray& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasDimensions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNewArray_HasDimensions(const expr::NewArray& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasDimensions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNewArray_HasDimensions(const expr::NewArray& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasInitializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNewArray_HasInitializers(const expr::NewArray& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasInitializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNewArray_HasInitializers(const expr::NewArray& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasEnclosingExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNewClass_HasEnclosingExpression(const expr::NewClass& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasEnclosingExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNewClass_HasEnclosingExpression(const expr::NewClass& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNewClass_HasTypeArguments(const expr::NewClass& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNewClass_HasTypeArguments(const expr::NewClass& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTypeName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNewClass_HasTypeName(const expr::NewClass& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTypeName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNewClass_HasTypeName(const expr::NewClass& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNewClass_HasArguments(const expr::NewClass& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNewClass_HasArguments(const expr::NewClass& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasAnonymousClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNewClass_HasAnonymousClass(const expr::NewClass& begin, const struc::AnonymousClass& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasAnonymousClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNewClass_HasAnonymousClass(const expr::NewClass& begin, const struc::AnonymousClass& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for constructor edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNewClass_Constructor(const expr::NewClass& begin, const struc::NormalMethod& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for constructor edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNewClass_Constructor(const expr::NewClass& begin, const struc::NormalMethod& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNormalAnnotation_HasArguments(const expr::NormalAnnotation& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNormalAnnotation_HasArguments(const expr::NormalAnnotation& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasQualifierType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitQualifiedTypeExpression_HasQualifierType(const expr::QualifiedTypeExpression& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasQualifierType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndQualifiedTypeExpression_HasQualifierType(const expr::QualifiedTypeExpression& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasSimpleType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitQualifiedTypeExpression_HasSimpleType(const expr::QualifiedTypeExpression& begin, const expr::SimpleTypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasSimpleType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndQualifiedTypeExpression_HasSimpleType(const expr::QualifiedTypeExpression& begin, const expr::SimpleTypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSingleElementAnnotation_HasArgument(const expr::SingleElementAnnotation& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSingleElementAnnotation_HasArgument(const expr::SingleElementAnnotation& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasRawType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeApplyExpression_HasRawType(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasRawType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeApplyExpression_HasRawType(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeApplyExpression_HasTypeArguments(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeApplyExpression_HasTypeArguments(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTypeOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeCast_HasTypeOperand(const expr::TypeCast& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTypeOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeCast_HasTypeOperand(const expr::TypeCast& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasAlternatives edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeUnionExpression_HasAlternatives(const expr::TypeUnionExpression& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasAlternatives edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeUnionExpression_HasAlternatives(const expr::TypeUnionExpression& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitUnary_HasOperand(const expr::Unary& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndUnary_HasOperand(const expr::Unary& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBound edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitWildcardExpression_HasBound(const expr::WildcardExpression& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBound edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndWildcardExpression_HasBound(const expr::WildcardExpression& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAssert_HasCondition(const statm::Assert& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAssert_HasCondition(const statm::Assert& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasDetail edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAssert_HasDetail(const statm::Assert& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasDetail edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAssert_HasDetail(const statm::Assert& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasInitializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBasicFor_HasInitializers(const statm::BasicFor& begin, const statm::Statement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasInitializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBasicFor_HasInitializers(const statm::BasicFor& begin, const statm::Statement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBasicFor_HasCondition(const statm::BasicFor& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBasicFor_HasCondition(const statm::BasicFor& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasUpdates edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBasicFor_HasUpdates(const statm::BasicFor& begin, const statm::Statement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasUpdates edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBasicFor_HasUpdates(const statm::BasicFor& begin, const statm::Statement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasStatements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBlock_HasStatements(const statm::Block& begin, const statm::Statement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasStatements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBlock_HasStatements(const statm::Block& begin, const statm::Statement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCase_HasExpression(const statm::Case& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCase_HasExpression(const statm::Case& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDo_HasCondition(const statm::Do& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDo_HasCondition(const statm::Do& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEnhancedFor_HasParameter(const statm::EnhancedFor& begin, const struc::Parameter& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndEnhancedFor_HasParameter(const statm::EnhancedFor& begin, const struc::Parameter& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEnhancedFor_HasExpression(const statm::EnhancedFor& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndEnhancedFor_HasExpression(const statm::EnhancedFor& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitExpressionStatement_HasExpression(const statm::ExpressionStatement& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndExpressionStatement_HasExpression(const statm::ExpressionStatement& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitHandler_HasParameter(const statm::Handler& begin, const struc::Parameter& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndHandler_HasParameter(const statm::Handler& begin, const struc::Parameter& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitHandler_HasBlock(const statm::Handler& begin, const statm::Block& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndHandler_HasBlock(const statm::Handler& begin, const statm::Block& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIf_HasSubstatement(const statm::If& begin, const statm::Statement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIf_HasSubstatement(const statm::If& begin, const statm::Statement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasFalseSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIf_HasFalseSubstatement(const statm::If& begin, const statm::Statement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasFalseSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIf_HasFalseSubstatement(const statm::If& begin, const statm::Statement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIteration_HasSubstatement(const statm::Iteration& begin, const statm::Statement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIteration_HasSubstatement(const statm::Iteration& begin, const statm::Statement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for target edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitJump_Target(const statm::Jump& begin, const statm::Statement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for target edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndJump_Target(const statm::Jump& begin, const statm::Statement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasStatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitLabeledStatement_HasStatement(const statm::LabeledStatement& begin, const statm::Statement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasStatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndLabeledStatement_HasStatement(const statm::LabeledStatement& begin, const statm::Statement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitReturn_HasExpression(const statm::Return& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndReturn_HasExpression(const statm::Return& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSelection_HasCondition(const statm::Selection& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSelection_HasCondition(const statm::Selection& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasCases edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSwitch_HasCases(const statm::Switch& begin, const statm::SwitchLabel& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasCases edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSwitch_HasCases(const statm::Switch& begin, const statm::SwitchLabel& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasStatements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSwitchLabel_HasStatements(const statm::SwitchLabel& begin, const statm::Statement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasStatements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSwitchLabel_HasStatements(const statm::SwitchLabel& begin, const statm::Statement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasLock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSynchronized_HasLock(const statm::Synchronized& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasLock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSynchronized_HasLock(const statm::Synchronized& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSynchronized_HasBlock(const statm::Synchronized& begin, const statm::Block& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSynchronized_HasBlock(const statm::Synchronized& begin, const statm::Block& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitThrow_HasExpression(const statm::Throw& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndThrow_HasExpression(const statm::Throw& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasResources edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTry_HasResources(const statm::Try& begin, const struc::Variable& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasResources edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTry_HasResources(const statm::Try& begin, const struc::Variable& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTry_HasBlock(const statm::Try& begin, const statm::Block& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTry_HasBlock(const statm::Try& begin, const statm::Block& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasHandlers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTry_HasHandlers(const statm::Try& begin, const statm::Handler& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasHandlers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTry_HasHandlers(const statm::Try& begin, const statm::Handler& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasFinallyBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTry_HasFinallyBlock(const statm::Try& begin, const statm::Block& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasFinallyBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTry_HasFinallyBlock(const statm::Try& begin, const statm::Block& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitWhile_HasCondition(const statm::While& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndWhile_HasCondition(const statm::While& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasAnnotations edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAnnotatedElement_HasAnnotations(const struc::AnnotatedElement& begin, const expr::Annotation& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasAnnotations edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAnnotatedElement_HasAnnotations(const struc::AnnotatedElement& begin, const expr::Annotation& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasDefaultValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAnnotationTypeElement_HasDefaultValue(const struc::AnnotationTypeElement& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasDefaultValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAnnotationTypeElement_HasDefaultValue(const struc::AnnotationTypeElement& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasPackageDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCompilationUnit_HasPackageDeclaration(const struc::CompilationUnit& begin, const struc::PackageDeclaration& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasPackageDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCompilationUnit_HasPackageDeclaration(const struc::CompilationUnit& begin, const struc::PackageDeclaration& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasImports edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCompilationUnit_HasImports(const struc::CompilationUnit& begin, const struc::Import& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasImports edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCompilationUnit_HasImports(const struc::CompilationUnit& begin, const struc::Import& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for typeDeclarations edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCompilationUnit_TypeDeclarations(const struc::CompilationUnit& begin, const struc::TypeDeclaration& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for typeDeclarations edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCompilationUnit_TypeDeclarations(const struc::CompilationUnit& begin, const struc::TypeDeclaration& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasOthers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCompilationUnit_HasOthers(const struc::CompilationUnit& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasOthers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCompilationUnit_HasOthers(const struc::CompilationUnit& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasNewClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEnumConstant_HasNewClass(const struc::EnumConstant& begin, const expr::NewClass& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasNewClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndEnumConstant_HasNewClass(const struc::EnumConstant& begin, const expr::NewClass& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTypeParameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitGenericDeclaration_HasTypeParameters(const struc::GenericDeclaration& begin, const struc::TypeParameter& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTypeParameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndGenericDeclaration_HasTypeParameters(const struc::GenericDeclaration& begin, const struc::TypeParameter& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTarget edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitImport_HasTarget(const struc::Import& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTarget edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndImport_HasTarget(const struc::Import& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitInitializerBlock_HasBody(const struc::InitializerBlock& begin, const statm::Block& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndInitializerBlock_HasBody(const struc::InitializerBlock& begin, const statm::Block& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethodDeclaration_HasReturnType(const struc::MethodDeclaration& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethodDeclaration_HasReturnType(const struc::MethodDeclaration& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for methodType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethodDeclaration_MethodType(const struc::MethodDeclaration& begin, const type::MethodType& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for methodType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethodDeclaration_MethodType(const struc::MethodDeclaration& begin, const type::MethodType& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for overrides edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethodDeclaration_Overrides(const struc::MethodDeclaration& begin, const struc::MethodDeclaration& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for overrides edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethodDeclaration_Overrides(const struc::MethodDeclaration& begin, const struc::MethodDeclaration& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasParameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNormalMethod_HasParameters(const struc::NormalMethod& begin, const struc::Parameter& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasParameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNormalMethod_HasParameters(const struc::NormalMethod& begin, const struc::Parameter& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNormalMethod_HasBody(const struc::NormalMethod& begin, const statm::Block& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNormalMethod_HasBody(const struc::NormalMethod& begin, const statm::Block& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasThrownExceptions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNormalMethod_HasThrownExceptions(const struc::NormalMethod& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasThrownExceptions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNormalMethod_HasThrownExceptions(const struc::NormalMethod& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasCompilationUnits edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitPackage_HasCompilationUnits(const struc::Package& begin, const struc::CompilationUnit& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasCompilationUnits edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndPackage_HasCompilationUnits(const struc::Package& begin, const struc::CompilationUnit& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasPackageName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitPackageDeclaration_HasPackageName(const struc::PackageDeclaration& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasPackageName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndPackageDeclaration_HasPackageName(const struc::PackageDeclaration& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitPackageDeclaration_RefersTo(const struc::PackageDeclaration& begin, const struc::Package& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndPackageDeclaration_RefersTo(const struc::PackageDeclaration& begin, const struc::Package& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasMembers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitScope_HasMembers(const struc::Scope& begin, const struc::Member& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasMembers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndScope_HasMembers(const struc::Scope& begin, const struc::Member& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for isInCompilationUnit edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeDeclaration_IsInCompilationUnit(const struc::TypeDeclaration& begin, const struc::CompilationUnit& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for isInCompilationUnit edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeDeclaration_IsInCompilationUnit(const struc::TypeDeclaration& begin, const struc::CompilationUnit& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasSuperClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeDeclaration_HasSuperClass(const struc::TypeDeclaration& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasSuperClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeDeclaration_HasSuperClass(const struc::TypeDeclaration& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasSuperInterfaces edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeDeclaration_HasSuperInterfaces(const struc::TypeDeclaration& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasSuperInterfaces edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeDeclaration_HasSuperInterfaces(const struc::TypeDeclaration& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasOthers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeDeclaration_HasOthers(const struc::TypeDeclaration& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasOthers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeDeclaration_HasOthers(const struc::TypeDeclaration& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBounds edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeParameter_HasBounds(const struc::TypeParameter& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBounds edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeParameter_HasBounds(const struc::TypeParameter& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasInitialValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitVariable_HasInitialValue(const struc::Variable& begin, const expr::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasInitialValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndVariable_HasInitialValue(const struc::Variable& begin, const expr::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitVariableDeclaration_HasType(const struc::VariableDeclaration& begin, const expr::TypeExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndVariableDeclaration_HasType(const struc::VariableDeclaration& begin, const expr::TypeExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for componentType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitArrayType_ComponentType(const type::ArrayType& begin, const type::Type& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for componentType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndArrayType_ComponentType(const type::ArrayType& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitClassType_RefersTo(const type::ClassType& begin, const struc::TypeDeclaration& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndClassType_RefersTo(const type::ClassType& begin, const struc::TypeDeclaration& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for returnType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethodType_ReturnType(const type::MethodType& begin, const type::Type& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for returnType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethodType_ReturnType(const type::MethodType& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for parameterTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethodType_ParameterTypes(const type::MethodType& begin, const type::Type& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for parameterTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethodType_ParameterTypes(const type::MethodType& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for thrownTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethodType_ThrownTypes(const type::MethodType& begin, const type::Type& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for thrownTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethodType_ThrownTypes(const type::MethodType& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitPackageType_RefersTo(const type::PackageType& begin, const struc::Package& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndPackageType_RefersTo(const type::PackageType& begin, const struc::Package& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for rawType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitParameterizedType_RawType(const type::ParameterizedType& begin, const type::Type& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for rawType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndParameterizedType_RawType(const type::ParameterizedType& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for argumentTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitParameterizedType_ArgumentTypes(const type::ParameterizedType& begin, const type::Type& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for argumentTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndParameterizedType_ArgumentTypes(const type::ParameterizedType& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for owner edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitScopedType_Owner(const type::ScopedType& begin, const type::Type& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for owner edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndScopedType_Owner(const type::ScopedType& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTypeVariable_RefersTo(const type::TypeVariable& begin, const struc::TypeParameter& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTypeVariable_RefersTo(const type::TypeVariable& begin, const struc::TypeParameter& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for alternatives edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitUnionType_Alternatives(const type::UnionType& begin, const type::Type& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for alternatives edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndUnionType_Alternatives(const type::UnionType& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for bound edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitWildcardType_Bound(const type::WildcardType& begin, const type::Type& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for bound edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndWildcardType_Bound(const type::WildcardType& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end);
      }

}}}
