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

#ifndef _JAVA_VISITORSIMPLEEDGE_H_
#define _JAVA_VISITORSIMPLEEDGE_H_

#include "java/inc/java.h"

/**
* \file VisitorSimpleEdge.h
* \brief Contains declaration of VisitorSimpleEdge class.
*/

namespace columbus { namespace java { namespace asg {
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
      * \brief Edge visitor for comments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCommentable_Comments(const base::Commentable& begin, const base::Comment& end);

      /**
      * \brief Edge visitor for comments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCommentable_Comments(const base::Commentable& begin, const base::Comment& end);

      /**
      * \brief Edge  visitor for hasAnnotations edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnnotatedTypeExpression_HasAnnotations(const expr::AnnotatedTypeExpression& begin, const expr::Annotation& end);

      /**
      * \brief Edge end visitor for hasAnnotations edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAnnotatedTypeExpression_HasAnnotations(const expr::AnnotatedTypeExpression& begin, const expr::Annotation& end);

      /**
      * \brief Edge  visitor for hasUnderlyingType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnnotatedTypeExpression_HasUnderlyingType(const expr::AnnotatedTypeExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasUnderlyingType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAnnotatedTypeExpression_HasUnderlyingType(const expr::AnnotatedTypeExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasAnnotationName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnnotation_HasAnnotationName(const expr::Annotation& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasAnnotationName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAnnotation_HasAnnotationName(const expr::Annotation& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayTypeExpression_HasComponentType(const expr::ArrayTypeExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArrayTypeExpression_HasComponentType(const expr::ArrayTypeExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasLeftOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinary_HasLeftOperand(const expr::Binary& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasLeftOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBinary_HasLeftOperand(const expr::Binary& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasRightOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinary_HasRightOperand(const expr::Binary& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasRightOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBinary_HasRightOperand(const expr::Binary& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassLiteral_HasComponentType(const expr::ClassLiteral& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndClassLiteral_HasComponentType(const expr::ClassLiteral& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditional_HasCondition(const expr::Conditional& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConditional_HasCondition(const expr::Conditional& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasTrueExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditional_HasTrueExpression(const expr::Conditional& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasTrueExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConditional_HasTrueExpression(const expr::Conditional& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasFalseExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditional_HasFalseExpression(const expr::Conditional& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasFalseExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConditional_HasFalseExpression(const expr::Conditional& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasErrors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitErroneous_HasErrors(const expr::Erroneous& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasErrors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndErroneous_HasErrors(const expr::Erroneous& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasErrors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitErroneousTypeExpression_HasErrors(const expr::ErroneousTypeExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasErrors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndErroneousTypeExpression_HasErrors(const expr::ErroneousTypeExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge visitor for type edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExpression_Type(const expr::Expression& begin, const type::Type& end);

      /**
      * \brief Edge visitor for type edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExpression_Type(const expr::Expression& begin, const type::Type& end);

      /**
      * \brief Edge visitor for target edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunctionalExpression_Target(const expr::FunctionalExpression& begin, const type::Type& end);

      /**
      * \brief Edge visitor for target edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFunctionalExpression_Target(const expr::FunctionalExpression& begin, const type::Type& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIdentifier_RefersTo(const expr::Identifier& begin, const base::Named& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIdentifier_RefersTo(const expr::Identifier& begin, const base::Named& end);

      /**
      * \brief Edge  visitor for hasTypeOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInstanceOf_HasTypeOperand(const expr::InstanceOf& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasTypeOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInstanceOf_HasTypeOperand(const expr::InstanceOf& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasParameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLambda_HasParameters(const expr::Lambda& begin, const struc::Parameter& end);

      /**
      * \brief Edge end visitor for hasParameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLambda_HasParameters(const expr::Lambda& begin, const struc::Parameter& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLambda_HasBody(const expr::Lambda& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLambda_HasBody(const expr::Lambda& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasQualifierExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMemberReference_HasQualifierExpression(const expr::MemberReference& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasQualifierExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMemberReference_HasQualifierExpression(const expr::MemberReference& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMemberReference_HasTypeArguments(const expr::MemberReference& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMemberReference_HasTypeArguments(const expr::MemberReference& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge visitor for referredMethod edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMemberReference_ReferredMethod(const expr::MemberReference& begin, const struc::MethodDeclaration& end);

      /**
      * \brief Edge visitor for referredMethod edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMemberReference_ReferredMethod(const expr::MemberReference& begin, const struc::MethodDeclaration& end);

      /**
      * \brief Edge  visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodInvocation_HasTypeArguments(const expr::MethodInvocation& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodInvocation_HasTypeArguments(const expr::MethodInvocation& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodInvocation_HasArguments(const expr::MethodInvocation& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodInvocation_HasArguments(const expr::MethodInvocation& begin, const expr::Expression& end);

      /**
      * \brief Edge visitor for invokes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodInvocation_Invokes(const expr::MethodInvocation& begin, const struc::MethodDeclaration& end);

      /**
      * \brief Edge visitor for invokes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodInvocation_Invokes(const expr::MethodInvocation& begin, const struc::MethodDeclaration& end);

      /**
      * \brief Edge  visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewArray_HasComponentType(const expr::NewArray& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewArray_HasComponentType(const expr::NewArray& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasDimensions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewArray_HasDimensions(const expr::NewArray& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasDimensions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewArray_HasDimensions(const expr::NewArray& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasInitializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewArray_HasInitializers(const expr::NewArray& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasInitializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewArray_HasInitializers(const expr::NewArray& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasEnclosingExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewClass_HasEnclosingExpression(const expr::NewClass& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasEnclosingExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewClass_HasEnclosingExpression(const expr::NewClass& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewClass_HasTypeArguments(const expr::NewClass& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewClass_HasTypeArguments(const expr::NewClass& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasTypeName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewClass_HasTypeName(const expr::NewClass& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasTypeName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewClass_HasTypeName(const expr::NewClass& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewClass_HasArguments(const expr::NewClass& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewClass_HasArguments(const expr::NewClass& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasAnonymousClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewClass_HasAnonymousClass(const expr::NewClass& begin, const struc::AnonymousClass& end);

      /**
      * \brief Edge end visitor for hasAnonymousClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewClass_HasAnonymousClass(const expr::NewClass& begin, const struc::AnonymousClass& end);

      /**
      * \brief Edge visitor for constructor edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewClass_Constructor(const expr::NewClass& begin, const struc::NormalMethod& end);

      /**
      * \brief Edge visitor for constructor edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewClass_Constructor(const expr::NewClass& begin, const struc::NormalMethod& end);

      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNormalAnnotation_HasArguments(const expr::NormalAnnotation& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNormalAnnotation_HasArguments(const expr::NormalAnnotation& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasQualifierType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQualifiedTypeExpression_HasQualifierType(const expr::QualifiedTypeExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasQualifierType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQualifiedTypeExpression_HasQualifierType(const expr::QualifiedTypeExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasSimpleType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQualifiedTypeExpression_HasSimpleType(const expr::QualifiedTypeExpression& begin, const expr::SimpleTypeExpression& end);

      /**
      * \brief Edge end visitor for hasSimpleType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQualifiedTypeExpression_HasSimpleType(const expr::QualifiedTypeExpression& begin, const expr::SimpleTypeExpression& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSingleElementAnnotation_HasArgument(const expr::SingleElementAnnotation& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSingleElementAnnotation_HasArgument(const expr::SingleElementAnnotation& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasRawType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeApplyExpression_HasRawType(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasRawType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeApplyExpression_HasRawType(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeApplyExpression_HasTypeArguments(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeApplyExpression_HasTypeArguments(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasTypeOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeCast_HasTypeOperand(const expr::TypeCast& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasTypeOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeCast_HasTypeOperand(const expr::TypeCast& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasBounds edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeIntersectionExpression_HasBounds(const expr::TypeIntersectionExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasBounds edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeIntersectionExpression_HasBounds(const expr::TypeIntersectionExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasAlternatives edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeUnionExpression_HasAlternatives(const expr::TypeUnionExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasAlternatives edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeUnionExpression_HasAlternatives(const expr::TypeUnionExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUnary_HasOperand(const expr::Unary& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUnary_HasOperand(const expr::Unary& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasBound edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWildcardExpression_HasBound(const expr::WildcardExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasBound edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndWildcardExpression_HasBound(const expr::WildcardExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasPackageName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExports_HasPackageName(const module::Exports& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasPackageName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExports_HasPackageName(const module::Exports& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasModuleNames edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExports_HasModuleNames(const module::Exports& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasModuleNames edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExports_HasModuleNames(const module::Exports& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasPackageName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitOpens_HasPackageName(const module::Opens& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasPackageName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndOpens_HasPackageName(const module::Opens& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasModuleNames edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitOpens_HasModuleNames(const module::Opens& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasModuleNames edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndOpens_HasModuleNames(const module::Opens& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasServiceName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitProvides_HasServiceName(const module::Provides& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasServiceName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndProvides_HasServiceName(const module::Provides& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasImplementationNames edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitProvides_HasImplementationNames(const module::Provides& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasImplementationNames edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndProvides_HasImplementationNames(const module::Provides& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasModuleName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitRequires_HasModuleName(const module::Requires& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasModuleName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndRequires_HasModuleName(const module::Requires& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasServiceName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUses_HasServiceName(const module::Uses& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasServiceName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUses_HasServiceName(const module::Uses& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssert_HasCondition(const statm::Assert& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssert_HasCondition(const statm::Assert& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasDetail edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssert_HasDetail(const statm::Assert& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasDetail edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssert_HasDetail(const statm::Assert& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasInitializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasicFor_HasInitializers(const statm::BasicFor& begin, const statm::Statement& end);

      /**
      * \brief Edge end visitor for hasInitializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBasicFor_HasInitializers(const statm::BasicFor& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasicFor_HasCondition(const statm::BasicFor& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBasicFor_HasCondition(const statm::BasicFor& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasUpdates edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasicFor_HasUpdates(const statm::BasicFor& begin, const statm::Statement& end);

      /**
      * \brief Edge end visitor for hasUpdates edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBasicFor_HasUpdates(const statm::BasicFor& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasStatements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBlock_HasStatements(const statm::Block& begin, const statm::Statement& end);

      /**
      * \brief Edge end visitor for hasStatements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBlock_HasStatements(const statm::Block& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCase_HasExpression(const statm::Case& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCase_HasExpression(const statm::Case& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDo_HasCondition(const statm::Do& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDo_HasCondition(const statm::Do& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEnhancedFor_HasParameter(const statm::EnhancedFor& begin, const struc::Parameter& end);

      /**
      * \brief Edge end visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndEnhancedFor_HasParameter(const statm::EnhancedFor& begin, const struc::Parameter& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEnhancedFor_HasExpression(const statm::EnhancedFor& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndEnhancedFor_HasExpression(const statm::EnhancedFor& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExpressionStatement_HasExpression(const statm::ExpressionStatement& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExpressionStatement_HasExpression(const statm::ExpressionStatement& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitHandler_HasParameter(const statm::Handler& begin, const struc::Parameter& end);

      /**
      * \brief Edge end visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndHandler_HasParameter(const statm::Handler& begin, const struc::Parameter& end);

      /**
      * \brief Edge  visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitHandler_HasBlock(const statm::Handler& begin, const statm::Block& end);

      /**
      * \brief Edge end visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndHandler_HasBlock(const statm::Handler& begin, const statm::Block& end);

      /**
      * \brief Edge  visitor for hasSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIf_HasSubstatement(const statm::If& begin, const statm::Statement& end);

      /**
      * \brief Edge end visitor for hasSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIf_HasSubstatement(const statm::If& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasFalseSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIf_HasFalseSubstatement(const statm::If& begin, const statm::Statement& end);

      /**
      * \brief Edge end visitor for hasFalseSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIf_HasFalseSubstatement(const statm::If& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIteration_HasSubstatement(const statm::Iteration& begin, const statm::Statement& end);

      /**
      * \brief Edge end visitor for hasSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIteration_HasSubstatement(const statm::Iteration& begin, const statm::Statement& end);

      /**
      * \brief Edge visitor for target edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitJump_Target(const statm::Jump& begin, const statm::Statement& end);

      /**
      * \brief Edge visitor for target edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndJump_Target(const statm::Jump& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasStatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLabeledStatement_HasStatement(const statm::LabeledStatement& begin, const statm::Statement& end);

      /**
      * \brief Edge end visitor for hasStatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLabeledStatement_HasStatement(const statm::LabeledStatement& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitReturn_HasExpression(const statm::Return& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndReturn_HasExpression(const statm::Return& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSelection_HasCondition(const statm::Selection& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSelection_HasCondition(const statm::Selection& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasCases edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitch_HasCases(const statm::Switch& begin, const statm::SwitchLabel& end);

      /**
      * \brief Edge end visitor for hasCases edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSwitch_HasCases(const statm::Switch& begin, const statm::SwitchLabel& end);

      /**
      * \brief Edge  visitor for hasStatements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchLabel_HasStatements(const statm::SwitchLabel& begin, const statm::Statement& end);

      /**
      * \brief Edge end visitor for hasStatements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSwitchLabel_HasStatements(const statm::SwitchLabel& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasLock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSynchronized_HasLock(const statm::Synchronized& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasLock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSynchronized_HasLock(const statm::Synchronized& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSynchronized_HasBlock(const statm::Synchronized& begin, const statm::Block& end);

      /**
      * \brief Edge end visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSynchronized_HasBlock(const statm::Synchronized& begin, const statm::Block& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitThrow_HasExpression(const statm::Throw& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndThrow_HasExpression(const statm::Throw& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasResources edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTry_HasResources(const statm::Try& begin, const base::Base& end);

      /**
      * \brief Edge end visitor for hasResources edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTry_HasResources(const statm::Try& begin, const base::Base& end);

      /**
      * \brief Edge  visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTry_HasBlock(const statm::Try& begin, const statm::Block& end);

      /**
      * \brief Edge end visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTry_HasBlock(const statm::Try& begin, const statm::Block& end);

      /**
      * \brief Edge  visitor for hasHandlers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTry_HasHandlers(const statm::Try& begin, const statm::Handler& end);

      /**
      * \brief Edge end visitor for hasHandlers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTry_HasHandlers(const statm::Try& begin, const statm::Handler& end);

      /**
      * \brief Edge  visitor for hasFinallyBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTry_HasFinallyBlock(const statm::Try& begin, const statm::Block& end);

      /**
      * \brief Edge end visitor for hasFinallyBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTry_HasFinallyBlock(const statm::Try& begin, const statm::Block& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhile_HasCondition(const statm::While& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndWhile_HasCondition(const statm::While& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasAnnotations edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnnotatedElement_HasAnnotations(const struc::AnnotatedElement& begin, const expr::Annotation& end);

      /**
      * \brief Edge end visitor for hasAnnotations edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAnnotatedElement_HasAnnotations(const struc::AnnotatedElement& begin, const expr::Annotation& end);

      /**
      * \brief Edge  visitor for hasDefaultValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnnotationTypeElement_HasDefaultValue(const struc::AnnotationTypeElement& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasDefaultValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAnnotationTypeElement_HasDefaultValue(const struc::AnnotationTypeElement& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasPackageDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnit_HasPackageDeclaration(const struc::CompilationUnit& begin, const struc::PackageDeclaration& end);

      /**
      * \brief Edge end visitor for hasPackageDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCompilationUnit_HasPackageDeclaration(const struc::CompilationUnit& begin, const struc::PackageDeclaration& end);

      /**
      * \brief Edge  visitor for hasImports edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnit_HasImports(const struc::CompilationUnit& begin, const struc::Import& end);

      /**
      * \brief Edge end visitor for hasImports edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCompilationUnit_HasImports(const struc::CompilationUnit& begin, const struc::Import& end);

      /**
      * \brief Edge  visitor for hasOthers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnit_HasOthers(const struc::CompilationUnit& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasOthers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCompilationUnit_HasOthers(const struc::CompilationUnit& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasModuleDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnit_HasModuleDeclaration(const struc::CompilationUnit& begin, const struc::ModuleDeclaration& end);

      /**
      * \brief Edge end visitor for hasModuleDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCompilationUnit_HasModuleDeclaration(const struc::CompilationUnit& begin, const struc::ModuleDeclaration& end);

      /**
      * \brief Edge visitor for typeDeclarations edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnit_TypeDeclarations(const struc::CompilationUnit& begin, const struc::TypeDeclaration& end);

      /**
      * \brief Edge visitor for typeDeclarations edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCompilationUnit_TypeDeclarations(const struc::CompilationUnit& begin, const struc::TypeDeclaration& end);

      /**
      * \brief Edge visitor for isInModule edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnit_IsInModule(const struc::CompilationUnit& begin, const struc::Module& end);

      /**
      * \brief Edge visitor for isInModule edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCompilationUnit_IsInModule(const struc::CompilationUnit& begin, const struc::Module& end);

      /**
      * \brief Edge  visitor for hasNewClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEnumConstant_HasNewClass(const struc::EnumConstant& begin, const expr::NewClass& end);

      /**
      * \brief Edge end visitor for hasNewClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndEnumConstant_HasNewClass(const struc::EnumConstant& begin, const expr::NewClass& end);

      /**
      * \brief Edge  visitor for hasTypeParameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGenericDeclaration_HasTypeParameters(const struc::GenericDeclaration& begin, const struc::TypeParameter& end);

      /**
      * \brief Edge end visitor for hasTypeParameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndGenericDeclaration_HasTypeParameters(const struc::GenericDeclaration& begin, const struc::TypeParameter& end);

      /**
      * \brief Edge  visitor for hasTarget edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImport_HasTarget(const struc::Import& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasTarget edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndImport_HasTarget(const struc::Import& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInitializerBlock_HasBody(const struc::InitializerBlock& begin, const statm::Block& end);

      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInitializerBlock_HasBody(const struc::InitializerBlock& begin, const statm::Block& end);

      /**
      * \brief Edge  visitor for hasReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclaration_HasReturnType(const struc::MethodDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodDeclaration_HasReturnType(const struc::MethodDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge visitor for methodType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclaration_MethodType(const struc::MethodDeclaration& begin, const type::MethodType& end);

      /**
      * \brief Edge visitor for methodType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodDeclaration_MethodType(const struc::MethodDeclaration& begin, const type::MethodType& end);

      /**
      * \brief Edge visitor for overrides edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclaration_Overrides(const struc::MethodDeclaration& begin, const struc::MethodDeclaration& end);

      /**
      * \brief Edge visitor for overrides edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodDeclaration_Overrides(const struc::MethodDeclaration& begin, const struc::MethodDeclaration& end);

      /**
      * \brief Edge visitor for packages edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitModule_Packages(const struc::Module& begin, const struc::Package& end);

      /**
      * \brief Edge visitor for packages edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndModule_Packages(const struc::Module& begin, const struc::Package& end);

      /**
      * \brief Edge  visitor for hasName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitModuleDeclaration_HasName(const struc::ModuleDeclaration& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndModuleDeclaration_HasName(const struc::ModuleDeclaration& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasDirectives edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitModuleDeclaration_HasDirectives(const struc::ModuleDeclaration& begin, const module::ModuleDirective& end);

      /**
      * \brief Edge end visitor for hasDirectives edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndModuleDeclaration_HasDirectives(const struc::ModuleDeclaration& begin, const module::ModuleDirective& end);

      /**
      * \brief Edge visitor for moduleType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitModuleDeclaration_ModuleType(const struc::ModuleDeclaration& begin, const type::ModuleType& end);

      /**
      * \brief Edge visitor for moduleType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndModuleDeclaration_ModuleType(const struc::ModuleDeclaration& begin, const type::ModuleType& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitModuleDeclaration_RefersTo(const struc::ModuleDeclaration& begin, const struc::Module& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndModuleDeclaration_RefersTo(const struc::ModuleDeclaration& begin, const struc::Module& end);

      /**
      * \brief Edge  visitor for hasParameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNormalMethod_HasParameters(const struc::NormalMethod& begin, const struc::Parameter& end);

      /**
      * \brief Edge end visitor for hasParameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNormalMethod_HasParameters(const struc::NormalMethod& begin, const struc::Parameter& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNormalMethod_HasBody(const struc::NormalMethod& begin, const statm::Block& end);

      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNormalMethod_HasBody(const struc::NormalMethod& begin, const statm::Block& end);

      /**
      * \brief Edge  visitor for hasThrownExceptions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNormalMethod_HasThrownExceptions(const struc::NormalMethod& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasThrownExceptions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNormalMethod_HasThrownExceptions(const struc::NormalMethod& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasCompilationUnits edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPackage_HasCompilationUnits(const struc::Package& begin, const struc::CompilationUnit& end);

      /**
      * \brief Edge end visitor for hasCompilationUnits edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPackage_HasCompilationUnits(const struc::Package& begin, const struc::CompilationUnit& end);

      /**
      * \brief Edge visitor for isInModule edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPackage_IsInModule(const struc::Package& begin, const struc::Module& end);

      /**
      * \brief Edge visitor for isInModule edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPackage_IsInModule(const struc::Package& begin, const struc::Module& end);

      /**
      * \brief Edge  visitor for hasPackageName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPackageDeclaration_HasPackageName(const struc::PackageDeclaration& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasPackageName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPackageDeclaration_HasPackageName(const struc::PackageDeclaration& begin, const expr::Expression& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPackageDeclaration_RefersTo(const struc::PackageDeclaration& begin, const struc::Package& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPackageDeclaration_RefersTo(const struc::PackageDeclaration& begin, const struc::Package& end);

      /**
      * \brief Edge  visitor for hasMembers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitScope_HasMembers(const struc::Scope& begin, const struc::Member& end);

      /**
      * \brief Edge end visitor for hasMembers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndScope_HasMembers(const struc::Scope& begin, const struc::Member& end);

      /**
      * \brief Edge  visitor for hasSuperClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclaration_HasSuperClass(const struc::TypeDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasSuperClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeDeclaration_HasSuperClass(const struc::TypeDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasSuperInterfaces edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclaration_HasSuperInterfaces(const struc::TypeDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasSuperInterfaces edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeDeclaration_HasSuperInterfaces(const struc::TypeDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasOthers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclaration_HasOthers(const struc::TypeDeclaration& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasOthers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeDeclaration_HasOthers(const struc::TypeDeclaration& begin, const base::Positioned& end);

      /**
      * \brief Edge visitor for isInCompilationUnit edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclaration_IsInCompilationUnit(const struc::TypeDeclaration& begin, const struc::CompilationUnit& end);

      /**
      * \brief Edge visitor for isInCompilationUnit edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeDeclaration_IsInCompilationUnit(const struc::TypeDeclaration& begin, const struc::CompilationUnit& end);

      /**
      * \brief Edge visitor for isInModule edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclaration_IsInModule(const struc::TypeDeclaration& begin, const struc::Module& end);

      /**
      * \brief Edge visitor for isInModule edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeDeclaration_IsInModule(const struc::TypeDeclaration& begin, const struc::Module& end);

      /**
      * \brief Edge  visitor for hasBounds edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeParameter_HasBounds(const struc::TypeParameter& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasBounds edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeParameter_HasBounds(const struc::TypeParameter& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasInitialValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariable_HasInitialValue(const struc::Variable& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasInitialValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndVariable_HasInitialValue(const struc::Variable& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclaration_HasType(const struc::VariableDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndVariableDeclaration_HasType(const struc::VariableDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge visitor for componentType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayType_ComponentType(const type::ArrayType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for componentType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArrayType_ComponentType(const type::ArrayType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassType_RefersTo(const type::ClassType& begin, const struc::TypeDeclaration& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndClassType_RefersTo(const type::ClassType& begin, const struc::TypeDeclaration& end);

      /**
      * \brief Edge visitor for bounds edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIntersectionType_Bounds(const type::IntersectionType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for bounds edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIntersectionType_Bounds(const type::IntersectionType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for returnType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodType_ReturnType(const type::MethodType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for returnType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodType_ReturnType(const type::MethodType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for parameterTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodType_ParameterTypes(const type::MethodType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for parameterTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodType_ParameterTypes(const type::MethodType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for thrownTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodType_ThrownTypes(const type::MethodType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for thrownTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodType_ThrownTypes(const type::MethodType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitModuleType_RefersTo(const type::ModuleType& begin, const struc::Module& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndModuleType_RefersTo(const type::ModuleType& begin, const struc::Module& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPackageType_RefersTo(const type::PackageType& begin, const struc::Package& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPackageType_RefersTo(const type::PackageType& begin, const struc::Package& end);

      /**
      * \brief Edge visitor for rawType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameterizedType_RawType(const type::ParameterizedType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for rawType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndParameterizedType_RawType(const type::ParameterizedType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for argumentTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameterizedType_ArgumentTypes(const type::ParameterizedType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for argumentTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndParameterizedType_ArgumentTypes(const type::ParameterizedType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for owner edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitScopedType_Owner(const type::ScopedType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for owner edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndScopedType_Owner(const type::ScopedType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeVariable_RefersTo(const type::TypeVariable& begin, const struc::TypeParameter& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeVariable_RefersTo(const type::TypeVariable& begin, const struc::TypeParameter& end);

      /**
      * \brief Edge visitor for alternatives edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUnionType_Alternatives(const type::UnionType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for alternatives edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUnionType_Alternatives(const type::UnionType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for bound edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWildcardType_Bound(const type::WildcardType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for bound edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndWildcardType_Bound(const type::WildcardType& begin, const type::Type& end);

      /**
      * \brief Edge  visitor for all edge which is called when the subtree of this edge is finished.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      * \param kind  [in] The kind of the association class.
      */
      virtual void visitAllEdge(const base::Base& begin, const base::Base& end) = 0;

      /**
      * \brief Edge end visitor for all edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      * \param kind  [in] The kind of the association class.
      */
      virtual void visitAllEdgeEnd(const base::Base& begin, const base::Base& end) = 0;

  }; // VisitorSimpleEdge


}}}
#endif
