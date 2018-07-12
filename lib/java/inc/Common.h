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

#ifndef _JAVA_Common_H_
#define _JAVA_Common_H_

#include "java/inc/java.h"

/**
* \file Common.h
* \brief Contains declaration of Common namespace.
*/

namespace columbus { namespace java { namespace asg {
  typedef unsigned int NodeHashType;
  /**
  * \brief Common contains general graph algorithms and common functions
  */
  namespace Common {
      /**
      * \brief Decides whether the node is base::BlockComment or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::BlockComment.
      */
      bool getIsBlockComment(const base::Base& node);

      /**
      * \brief Decides whether the node is base::Comment or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::Comment.
      */
      bool getIsComment(const base::Base& node);

      /**
      * \brief Decides whether the node is base::Commentable or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::Commentable.
      */
      bool getIsCommentable(const base::Base& node);

      /**
      * \brief Decides whether the node is base::JavadocComment or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::JavadocComment.
      */
      bool getIsJavadocComment(const base::Base& node);

      /**
      * \brief Decides whether the node is base::LineComment or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::LineComment.
      */
      bool getIsLineComment(const base::Base& node);

      /**
      * \brief Decides whether the node is base::Named or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::Named.
      */
      bool getIsNamed(const base::Base& node);

      /**
      * \brief Decides whether the node is base::NonJavadocComment or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::NonJavadocComment.
      */
      bool getIsNonJavadocComment(const base::Base& node);

      /**
      * \brief Decides whether the node is base::Positioned or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::Positioned.
      */
      bool getIsPositioned(const base::Base& node);

      /**
      * \brief Decides whether the node is base::PositionedWithoutComment or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::PositionedWithoutComment.
      */
      bool getIsPositionedWithoutComment(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::Annotation or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::Annotation.
      */
      bool getIsAnnotation(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::ArrayAccess or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::ArrayAccess.
      */
      bool getIsArrayAccess(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::ArrayTypeExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::ArrayTypeExpression.
      */
      bool getIsArrayTypeExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::Assignment or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::Assignment.
      */
      bool getIsAssignment(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::Binary or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::Binary.
      */
      bool getIsBinary(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::BooleanLiteral or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::BooleanLiteral.
      */
      bool getIsBooleanLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::CharacterLiteral or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::CharacterLiteral.
      */
      bool getIsCharacterLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::ClassLiteral or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::ClassLiteral.
      */
      bool getIsClassLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::Conditional or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::Conditional.
      */
      bool getIsConditional(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::DoubleLiteral or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::DoubleLiteral.
      */
      bool getIsDoubleLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::Erroneous or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::Erroneous.
      */
      bool getIsErroneous(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::ErroneousTypeExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::ErroneousTypeExpression.
      */
      bool getIsErroneousTypeExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::Expression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::Expression.
      */
      bool getIsExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::ExternalTypeExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::ExternalTypeExpression.
      */
      bool getIsExternalTypeExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::FieldAccess or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::FieldAccess.
      */
      bool getIsFieldAccess(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::FloatLiteral or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::FloatLiteral.
      */
      bool getIsFloatLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::Identifier or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::Identifier.
      */
      bool getIsIdentifier(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::InfixExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::InfixExpression.
      */
      bool getIsInfixExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::InstanceOf or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::InstanceOf.
      */
      bool getIsInstanceOf(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::IntegerLiteral or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::IntegerLiteral.
      */
      bool getIsIntegerLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::Literal or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::Literal.
      */
      bool getIsLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::LongLiteral or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::LongLiteral.
      */
      bool getIsLongLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::MarkerAnnotation or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::MarkerAnnotation.
      */
      bool getIsMarkerAnnotation(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::MethodInvocation or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::MethodInvocation.
      */
      bool getIsMethodInvocation(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::NewArray or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::NewArray.
      */
      bool getIsNewArray(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::NewClass or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::NewClass.
      */
      bool getIsNewClass(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::NormalAnnotation or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::NormalAnnotation.
      */
      bool getIsNormalAnnotation(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::NullLiteral or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::NullLiteral.
      */
      bool getIsNullLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::NumberLiteral or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::NumberLiteral.
      */
      bool getIsNumberLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::ParenthesizedExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::ParenthesizedExpression.
      */
      bool getIsParenthesizedExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::PostfixExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::PostfixExpression.
      */
      bool getIsPostfixExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::PrefixExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::PrefixExpression.
      */
      bool getIsPrefixExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::PrimitiveTypeExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::PrimitiveTypeExpression.
      */
      bool getIsPrimitiveTypeExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::QualifiedTypeExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::QualifiedTypeExpression.
      */
      bool getIsQualifiedTypeExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::SimpleTypeExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::SimpleTypeExpression.
      */
      bool getIsSimpleTypeExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::SingleElementAnnotation or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::SingleElementAnnotation.
      */
      bool getIsSingleElementAnnotation(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::StringLiteral or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::StringLiteral.
      */
      bool getIsStringLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::Super or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::Super.
      */
      bool getIsSuper(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::This or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::This.
      */
      bool getIsThis(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::TypeApplyExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::TypeApplyExpression.
      */
      bool getIsTypeApplyExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::TypeCast or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::TypeCast.
      */
      bool getIsTypeCast(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::TypeExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::TypeExpression.
      */
      bool getIsTypeExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::TypeUnionExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::TypeUnionExpression.
      */
      bool getIsTypeUnionExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::Unary or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::Unary.
      */
      bool getIsUnary(const base::Base& node);

      /**
      * \brief Decides whether the node is expr::WildcardExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expr::WildcardExpression.
      */
      bool getIsWildcardExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::Assert or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::Assert.
      */
      bool getIsAssert(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::BasicFor or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::BasicFor.
      */
      bool getIsBasicFor(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::Block or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::Block.
      */
      bool getIsBlock(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::Break or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::Break.
      */
      bool getIsBreak(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::Case or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::Case.
      */
      bool getIsCase(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::Continue or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::Continue.
      */
      bool getIsContinue(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::Default or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::Default.
      */
      bool getIsDefault(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::Do or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::Do.
      */
      bool getIsDo(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::Empty or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::Empty.
      */
      bool getIsEmpty(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::EnhancedFor or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::EnhancedFor.
      */
      bool getIsEnhancedFor(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::ExpressionStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::ExpressionStatement.
      */
      bool getIsExpressionStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::For or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::For.
      */
      bool getIsFor(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::Handler or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::Handler.
      */
      bool getIsHandler(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::If or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::If.
      */
      bool getIsIf(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::Iteration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::Iteration.
      */
      bool getIsIteration(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::Jump or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::Jump.
      */
      bool getIsJump(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::LabeledStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::LabeledStatement.
      */
      bool getIsLabeledStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::Return or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::Return.
      */
      bool getIsReturn(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::Selection or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::Selection.
      */
      bool getIsSelection(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::Statement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::Statement.
      */
      bool getIsStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::Switch or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::Switch.
      */
      bool getIsSwitch(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::SwitchLabel or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::SwitchLabel.
      */
      bool getIsSwitchLabel(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::Synchronized or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::Synchronized.
      */
      bool getIsSynchronized(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::Throw or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::Throw.
      */
      bool getIsThrow(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::Try or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::Try.
      */
      bool getIsTry(const base::Base& node);

      /**
      * \brief Decides whether the node is statm::While or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statm::While.
      */
      bool getIsWhile(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::AnnotatedElement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::AnnotatedElement.
      */
      bool getIsAnnotatedElement(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::AnnotationType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::AnnotationType.
      */
      bool getIsAnnotationType(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::AnnotationTypeElement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::AnnotationTypeElement.
      */
      bool getIsAnnotationTypeElement(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::AnonymousClass or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::AnonymousClass.
      */
      bool getIsAnonymousClass(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::Class or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::Class.
      */
      bool getIsClass(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::ClassDeclaration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::ClassDeclaration.
      */
      bool getIsClassDeclaration(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::ClassGeneric or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::ClassGeneric.
      */
      bool getIsClassGeneric(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::CompilationUnit or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::CompilationUnit.
      */
      bool getIsCompilationUnit(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::Declaration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::Declaration.
      */
      bool getIsDeclaration(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::Enum or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::Enum.
      */
      bool getIsEnum(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::EnumConstant or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::EnumConstant.
      */
      bool getIsEnumConstant(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::GenericDeclaration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::GenericDeclaration.
      */
      bool getIsGenericDeclaration(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::Import or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::Import.
      */
      bool getIsImport(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::InitializerBlock or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::InitializerBlock.
      */
      bool getIsInitializerBlock(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::InstanceInitializerBlock or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::InstanceInitializerBlock.
      */
      bool getIsInstanceInitializerBlock(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::Interface or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::Interface.
      */
      bool getIsInterface(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::InterfaceDeclaration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::InterfaceDeclaration.
      */
      bool getIsInterfaceDeclaration(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::InterfaceGeneric or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::InterfaceGeneric.
      */
      bool getIsInterfaceGeneric(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::Member or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::Member.
      */
      bool getIsMember(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::Method or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::Method.
      */
      bool getIsMethod(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::MethodDeclaration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::MethodDeclaration.
      */
      bool getIsMethodDeclaration(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::MethodGeneric or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::MethodGeneric.
      */
      bool getIsMethodGeneric(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::NamedDeclaration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::NamedDeclaration.
      */
      bool getIsNamedDeclaration(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::NormalMethod or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::NormalMethod.
      */
      bool getIsNormalMethod(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::Package or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::Package.
      */
      bool getIsPackage(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::PackageDeclaration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::PackageDeclaration.
      */
      bool getIsPackageDeclaration(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::Parameter or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::Parameter.
      */
      bool getIsParameter(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::Scope or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::Scope.
      */
      bool getIsScope(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::StaticInitializerBlock or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::StaticInitializerBlock.
      */
      bool getIsStaticInitializerBlock(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::TypeDeclaration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::TypeDeclaration.
      */
      bool getIsTypeDeclaration(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::TypeParameter or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::TypeParameter.
      */
      bool getIsTypeParameter(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::Variable or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::Variable.
      */
      bool getIsVariable(const base::Base& node);

      /**
      * \brief Decides whether the node is struc::VariableDeclaration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is struc::VariableDeclaration.
      */
      bool getIsVariableDeclaration(const base::Base& node);

      /**
      * \brief Decides whether the node is type::ArrayType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::ArrayType.
      */
      bool getIsArrayType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::BooleanType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::BooleanType.
      */
      bool getIsBooleanType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::BoundedWildcardType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::BoundedWildcardType.
      */
      bool getIsBoundedWildcardType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::ByteType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::ByteType.
      */
      bool getIsByteType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::CharType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::CharType.
      */
      bool getIsCharType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::ClassType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::ClassType.
      */
      bool getIsClassType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::DoubleType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::DoubleType.
      */
      bool getIsDoubleType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::ErrorType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::ErrorType.
      */
      bool getIsErrorType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::FloatType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::FloatType.
      */
      bool getIsFloatType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::IntType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::IntType.
      */
      bool getIsIntType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::LongType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::LongType.
      */
      bool getIsLongType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::LowerBoundedWildcardType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::LowerBoundedWildcardType.
      */
      bool getIsLowerBoundedWildcardType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::MethodType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::MethodType.
      */
      bool getIsMethodType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::NoType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::NoType.
      */
      bool getIsNoType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::NullType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::NullType.
      */
      bool getIsNullType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::PackageType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::PackageType.
      */
      bool getIsPackageType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::ParameterizedType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::ParameterizedType.
      */
      bool getIsParameterizedType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::PrimitiveType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::PrimitiveType.
      */
      bool getIsPrimitiveType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::ScopedType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::ScopedType.
      */
      bool getIsScopedType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::ShortType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::ShortType.
      */
      bool getIsShortType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::Type or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::Type.
      */
      bool getIsType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::TypeVariable or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::TypeVariable.
      */
      bool getIsTypeVariable(const base::Base& node);

      /**
      * \brief Decides whether the node is type::UnboundedWildcardType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::UnboundedWildcardType.
      */
      bool getIsUnboundedWildcardType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::UnionType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::UnionType.
      */
      bool getIsUnionType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::UpperBoundedWildcardType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::UpperBoundedWildcardType.
      */
      bool getIsUpperBoundedWildcardType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::VoidType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::VoidType.
      */
      bool getIsVoidType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::WildcardType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::WildcardType.
      */
      bool getIsWildcardType(const base::Base& node);

      /**
      * \brief Decides whether the node is AP spec node or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is AP spec node.
      */
      bool getIsAPSpecNode(const base::Base& node);

      /**
      * \brief Decides whether the 'base' is one of the base kinds (transitive) of 'what'.
      * \param what [in] The examined node kind.
      * \param base [in] The base node kind.
      * \return Returns true if 'base' is a base kind of 'what'.
      */
      bool getIsBaseClassKind(NodeKind what, NodeKind base);

      /**
      * \brief Decides whether the node is composite or not.
      * \param node [in] The node which is being examined.
      * \return Returns true if the node is composite.
      */
      bool getIsComposite(const base::Base& node);

      /**
      * \brief Decides whether the node is composite or not.
      * \param node [in] The node which is being examined.
      * \return Returns true if the node is not composite.
      */
      bool getIsNotComposite(const base::Base& node);

      /**
      * \brief Gives back the string representation of the NodeId.
      * \param nodeId [in] The NodeId.
      * \return The string representation of the nodeId given in the parameter.
      */
      const std::string toString(NodeId nodeId);

      /**
      * \brief Gives back the string representation of the AccessibilityKind kind.
      * \param kind          [in] The AccessibilityKind.
      * \throw JavaException If the kind is not "valid" JavaException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(AccessibilityKind kind);

      /**
      * \brief Gives back the string representation of the AssignmentOperatorKind kind.
      * \param kind          [in] The AssignmentOperatorKind.
      * \throw JavaException If the kind is not "valid" JavaException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(AssignmentOperatorKind kind);

      /**
      * \brief Gives back the string representation of the InfixOperatorKind kind.
      * \param kind          [in] The InfixOperatorKind.
      * \throw JavaException If the kind is not "valid" JavaException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(InfixOperatorKind kind);

      /**
      * \brief Gives back the string representation of the MethodKind kind.
      * \param kind          [in] The MethodKind.
      * \throw JavaException If the kind is not "valid" JavaException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(MethodKind kind);

      /**
      * \brief Gives back the string representation of the PostfixOperatorKind kind.
      * \param kind          [in] The PostfixOperatorKind.
      * \throw JavaException If the kind is not "valid" JavaException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(PostfixOperatorKind kind);

      /**
      * \brief Gives back the string representation of the PrefixOperatorKind kind.
      * \param kind          [in] The PrefixOperatorKind.
      * \throw JavaException If the kind is not "valid" JavaException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(PrefixOperatorKind kind);

      /**
      * \brief Gives back the string representation of the PrimitiveTypeKind kind.
      * \param kind          [in] The PrimitiveTypeKind.
      * \throw JavaException If the kind is not "valid" JavaException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(PrimitiveTypeKind kind);

      /**
      * \brief Gives back the string representation of the TypeBoundKind kind.
      * \param kind          [in] The TypeBoundKind.
      * \throw JavaException If the kind is not "valid" JavaException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(TypeBoundKind kind);

      /**
      * \brief Gives back the string representation of the NodeKind kind.
      * \param kind          [in] The NodeKind.
      * \throw JavaException If the kind is not "valid" JavaException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(NodeKind kind);

      /**
      * \brief Gives back the string representation of the EdgeKind kind.
      * \param kind          [in] The EdgeKind.
      * \throw JavaException If the kind is not "valid" JavaException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(EdgeKind kind);

      /**
      * \brief Returns true if the node exists and is not filtered out.
      * \param id [in] The examined node ID.
      * \return True if the node exists and is not filtered out.
      */
      bool getIsValid(NodeId id);

      /**
      * \brief Minimum of same type node similarity.
      */
      extern double SimilarityMinimum;

      /**
      * \brief Returns the minimum similarity value of same type nodes.
      * \return Minimum of same type node similarity.
      */
      double getSimilarityMinimum();

      /**
      * \brief Sets the minimum similarity value of same type nodes.
      * \param value [in] Minimum of same type node similarity.
      */
      void setSimilarityMinimum(double value);

      /**
      * \brief Minimum similarity for string type attributes.
      */
      extern double SimilarityMinForStrings;

      /**
      * \brief Returns the minimum similarity value for string type attributes.
      * \return Minimum similarity for string type attributes.
      */
      double getSimilarityMinForStrings();

      /**
      * \brief Sets the minimum similarity value for string type attributes.
      * \param value [in] Minimum similarity for string type attributes.
      */
      void setSimilarityMinForStrings(double value);

      /**
      * \brief Minimum similarity for AP spec edges.
      */
      extern double SimilarityMinForEdges;

      /**
      * \brief Returns the minimum similarity value for AP spec edges.
      * \return Minimum similarity for AP spec edges.
      */
      double getSimilarityMinForEdges();

      /**
      * \brief Sets the minimum similarity value for AP spec edges.
      * \param value [in] Minimum similarity for AP spec edges.
      */
      void setSimilarityMinForEdges(double value);

      /**
      * \brief Get unique name for a Base.
      * \param node [in] The base node.
      * \return The unique name of the node.
      */
      std::string getUniqueNameForBase(const base::Base &node);

      /**
      * \brief Get unique name for a Type.
      * \param node [in] The type node.
      * \return The unique name of the node.
      */
      std::string getUniqueNameForType(const type::Type &node);

      /**
      * \brief Returns the enclosing Scope or MethodDeclaration parent of the given node.
      * \param node [in] The base node.
      * \return The enclosing Scope or MethodDeclaration parent of the node.
      */
      base::Base* getScopeOrMethodDeclarationParent(const base::Base& node);

      /**
      * \brief Get unique name for sorting Member nodes.
      * \param node [in] The base node.
      * \return A unique name for the node.
      */
      std::string getUniqueStringForSorting(const base::Base& node);

      /**
      * \brief Sets whether to generate generic or non generic unique name for methods.
      * \param value [in] The value.
      */
      void setGenerateNonGenericSignatureForMethods(bool value);

      /**
      * \brief Get name for Base nodes.
      * \param node [in] The base node.
      * \return A name for the node.
      */
      std::string getName(const base::Base& node);
      /**
      * \brief Get long name for Base nodes.
      * \param node [in] The base node.
      * \return A name for the node.
      */
      std::string getLongName(const base::Base& node);

	  
	  /**
      * \brief Get the suffix for instance init blocks
	  * \return The suffix
	  */
	  std::string getInstanceInitBlockSuffix();
	  
	  
	  /**
      * \brief Get the suffix for static init blocks
	  * \return The suffix
	  */
	  std::string getStaticInitBlockSuffix();
	  
	  
	  /**
      * \brief Get the name for instance init blocks
	  * \return The name
	  */
	  std::string getInstanceInitBlockName();
	  
	  
	  /**
      * \brief Get the name for static init blocks
	  * \return The name
	  */
	  std::string getStaticInitBlockName();
	  
  } // Common


}}}
#endif

