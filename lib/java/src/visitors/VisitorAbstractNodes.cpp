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


namespace columbus { namespace java { namespace asg {
VisitorAbstractNodes::~VisitorAbstractNodes() { }

void VisitorAbstractNodes::visit   (const base::Base& node , bool callVirtualBase) { }
void VisitorAbstractNodes::visitEnd(const base::Base& node , bool callVirtualBase) { }

void VisitorAbstractNodes::visit(const base::BlockComment& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  visit   ((base::NonJavadocComment&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::BlockComment& node , bool callVirtualBase) {
  visitEnd   ((base::NonJavadocComment&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const base::Comment& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  visit   ((base::PositionedWithoutComment&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::Comment& node , bool callVirtualBase) {
  visitEnd   ((base::PositionedWithoutComment&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const base::Commentable& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::Commentable& node , bool callVirtualBase) {
  if (callVirtualBase)
    visitEnd((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const base::JavadocComment& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  visit   ((base::Comment&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::JavadocComment& node , bool callVirtualBase) {
  visitEnd   ((base::Comment&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const base::LineComment& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  visit   ((base::NonJavadocComment&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::LineComment& node , bool callVirtualBase) {
  visitEnd   ((base::NonJavadocComment&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const base::Named& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::Named& node , bool callVirtualBase) {
  if (callVirtualBase)
    visitEnd((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const base::NonJavadocComment& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  visit   ((base::Comment&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::NonJavadocComment& node , bool callVirtualBase) {
  visitEnd   ((base::Comment&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const base::Positioned& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit((base::Commentable&)node,false); 
  visit   ((base::PositionedWithoutComment&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::Positioned& node , bool callVirtualBase) {
  if (callVirtualBase)
    visitEnd((base::Commentable&)node,false); 
  visitEnd   ((base::PositionedWithoutComment&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const base::PositionedWithoutComment& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::PositionedWithoutComment& node , bool callVirtualBase) {
  if (callVirtualBase)
    visitEnd((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::Annotation& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::Annotation& node , bool callVirtualBase) {
  visitEnd   ((expr::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::ArrayAccess& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Binary&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::ArrayAccess& node , bool callVirtualBase) {
  visitEnd   ((expr::Binary&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::ArrayTypeExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::TypeExpression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::ArrayTypeExpression& node , bool callVirtualBase) {
  visitEnd   ((expr::TypeExpression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::Assignment& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Binary&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::Assignment& node , bool callVirtualBase) {
  visitEnd   ((expr::Binary&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::Binary& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::Binary& node , bool callVirtualBase) {
  visitEnd   ((expr::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::BooleanLiteral& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Literal&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::BooleanLiteral& node , bool callVirtualBase) {
  visitEnd   ((expr::Literal&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::CharacterLiteral& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Literal&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::CharacterLiteral& node , bool callVirtualBase) {
  visitEnd   ((expr::Literal&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::ClassLiteral& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Literal&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::ClassLiteral& node , bool callVirtualBase) {
  visitEnd   ((expr::Literal&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::Conditional& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::Conditional& node , bool callVirtualBase) {
  visitEnd   ((expr::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::DoubleLiteral& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::NumberLiteral&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::DoubleLiteral& node , bool callVirtualBase) {
  visitEnd   ((expr::NumberLiteral&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::Erroneous& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::Erroneous& node , bool callVirtualBase) {
  visitEnd   ((expr::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::ErroneousTypeExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::TypeExpression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::ErroneousTypeExpression& node , bool callVirtualBase) {
  visitEnd   ((expr::TypeExpression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::Expression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::Expression& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::ExternalTypeExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::TypeExpression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::ExternalTypeExpression& node , bool callVirtualBase) {
  visitEnd   ((expr::TypeExpression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::FieldAccess& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Binary&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::FieldAccess& node , bool callVirtualBase) {
  visitEnd   ((expr::Binary&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::FloatLiteral& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::NumberLiteral&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::FloatLiteral& node , bool callVirtualBase) {
  visitEnd   ((expr::NumberLiteral&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::Identifier& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::Identifier& node , bool callVirtualBase) {
  visitEnd   ((expr::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::InfixExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Binary&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::InfixExpression& node , bool callVirtualBase) {
  visitEnd   ((expr::Binary&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::InstanceOf& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Unary&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::InstanceOf& node , bool callVirtualBase) {
  visitEnd   ((expr::Unary&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::IntegerLiteral& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::NumberLiteral&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::IntegerLiteral& node , bool callVirtualBase) {
  visitEnd   ((expr::NumberLiteral&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::Literal& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::Literal& node , bool callVirtualBase) {
  visitEnd   ((expr::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::LongLiteral& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::NumberLiteral&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::LongLiteral& node , bool callVirtualBase) {
  visitEnd   ((expr::NumberLiteral&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::MarkerAnnotation& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Annotation&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::MarkerAnnotation& node , bool callVirtualBase) {
  visitEnd   ((expr::Annotation&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::MethodInvocation& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Unary&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::MethodInvocation& node , bool callVirtualBase) {
  visitEnd   ((expr::Unary&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::NewArray& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::NewArray& node , bool callVirtualBase) {
  visitEnd   ((expr::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::NewClass& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::NewClass& node , bool callVirtualBase) {
  visitEnd   ((expr::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::NormalAnnotation& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Annotation&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::NormalAnnotation& node , bool callVirtualBase) {
  visitEnd   ((expr::Annotation&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::NullLiteral& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Literal&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::NullLiteral& node , bool callVirtualBase) {
  visitEnd   ((expr::Literal&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::NumberLiteral& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Literal&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::NumberLiteral& node , bool callVirtualBase) {
  visitEnd   ((expr::Literal&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::ParenthesizedExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Unary&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::ParenthesizedExpression& node , bool callVirtualBase) {
  visitEnd   ((expr::Unary&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::PostfixExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Unary&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::PostfixExpression& node , bool callVirtualBase) {
  visitEnd   ((expr::Unary&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::PrefixExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Unary&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::PrefixExpression& node , bool callVirtualBase) {
  visitEnd   ((expr::Unary&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::PrimitiveTypeExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::TypeExpression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::PrimitiveTypeExpression& node , bool callVirtualBase) {
  visitEnd   ((expr::TypeExpression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::QualifiedTypeExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::TypeExpression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::QualifiedTypeExpression& node , bool callVirtualBase) {
  visitEnd   ((expr::TypeExpression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::SimpleTypeExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::TypeExpression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::SimpleTypeExpression& node , bool callVirtualBase) {
  visitEnd   ((expr::TypeExpression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::SingleElementAnnotation& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Annotation&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::SingleElementAnnotation& node , bool callVirtualBase) {
  visitEnd   ((expr::Annotation&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::StringLiteral& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Literal&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::StringLiteral& node , bool callVirtualBase) {
  visitEnd   ((expr::Literal&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::Super& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::Super& node , bool callVirtualBase) {
  visitEnd   ((expr::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::This& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::This& node , bool callVirtualBase) {
  visitEnd   ((expr::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::TypeApplyExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::TypeExpression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::TypeApplyExpression& node , bool callVirtualBase) {
  visitEnd   ((expr::TypeExpression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::TypeCast& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Unary&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::TypeCast& node , bool callVirtualBase) {
  visitEnd   ((expr::Unary&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::TypeExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::TypeExpression& node , bool callVirtualBase) {
  visitEnd   ((expr::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::TypeUnionExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::TypeExpression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::TypeUnionExpression& node , bool callVirtualBase) {
  visitEnd   ((expr::TypeExpression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::Unary& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::Unary& node , bool callVirtualBase) {
  visitEnd   ((expr::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const expr::WildcardExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((expr::TypeExpression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expr::WildcardExpression& node , bool callVirtualBase) {
  visitEnd   ((expr::TypeExpression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::Assert& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::Assert& node , bool callVirtualBase) {
  visitEnd   ((statm::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::BasicFor& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::For&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::BasicFor& node , bool callVirtualBase) {
  visitEnd   ((statm::For&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::Block& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::Block& node , bool callVirtualBase) {
  visitEnd   ((statm::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::Break& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::Jump&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::Break& node , bool callVirtualBase) {
  visitEnd   ((statm::Jump&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::Case& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::SwitchLabel&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::Case& node , bool callVirtualBase) {
  visitEnd   ((statm::SwitchLabel&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::Continue& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::Jump&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::Continue& node , bool callVirtualBase) {
  visitEnd   ((statm::Jump&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::Default& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::SwitchLabel&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::Default& node , bool callVirtualBase) {
  visitEnd   ((statm::SwitchLabel&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::Do& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::Iteration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::Do& node , bool callVirtualBase) {
  visitEnd   ((statm::Iteration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::Empty& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::Empty& node , bool callVirtualBase) {
  visitEnd   ((statm::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::EnhancedFor& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::For&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::EnhancedFor& node , bool callVirtualBase) {
  visitEnd   ((statm::For&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::ExpressionStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::ExpressionStatement& node , bool callVirtualBase) {
  visitEnd   ((statm::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::For& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::Iteration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::For& node , bool callVirtualBase) {
  visitEnd   ((statm::Iteration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::Handler& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::Handler& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::If& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::Selection&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::If& node , bool callVirtualBase) {
  visitEnd   ((statm::Selection&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::Iteration& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::Iteration& node , bool callVirtualBase) {
  visitEnd   ((statm::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::Jump& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::Jump& node , bool callVirtualBase) {
  visitEnd   ((statm::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::LabeledStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::LabeledStatement& node , bool callVirtualBase) {
  visitEnd   ((statm::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::Return& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::Return& node , bool callVirtualBase) {
  visitEnd   ((statm::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::Selection& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::Selection& node , bool callVirtualBase) {
  visitEnd   ((statm::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::Statement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::Statement& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::Switch& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::Selection&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::Switch& node , bool callVirtualBase) {
  visitEnd   ((statm::Selection&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::SwitchLabel& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::SwitchLabel& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::Synchronized& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::Synchronized& node , bool callVirtualBase) {
  visitEnd   ((statm::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::Throw& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::Throw& node , bool callVirtualBase) {
  visitEnd   ((statm::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::Try& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::Try& node , bool callVirtualBase) {
  visitEnd   ((statm::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const statm::While& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((statm::Iteration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statm::While& node , bool callVirtualBase) {
  visitEnd   ((statm::Iteration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::AnnotatedElement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::AnnotatedElement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visitEnd((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::AnnotationType& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::TypeDeclaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::AnnotationType& node , bool callVirtualBase) {
  visitEnd   ((struc::TypeDeclaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::AnnotationTypeElement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::MethodDeclaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::AnnotationTypeElement& node , bool callVirtualBase) {
  visitEnd   ((struc::MethodDeclaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::AnonymousClass& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::ClassDeclaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::AnonymousClass& node , bool callVirtualBase) {
  visitEnd   ((struc::ClassDeclaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::Class& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::ClassDeclaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::Class& node , bool callVirtualBase) {
  visitEnd   ((struc::ClassDeclaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::ClassDeclaration& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::TypeDeclaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::ClassDeclaration& node , bool callVirtualBase) {
  visitEnd   ((struc::TypeDeclaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::ClassGeneric& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::ClassDeclaration&)node,false); 
  visit   ((struc::GenericDeclaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::ClassGeneric& node , bool callVirtualBase) {
  visitEnd   ((struc::ClassDeclaration&)node,false); 
  visitEnd   ((struc::GenericDeclaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::CompilationUnit& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  visit   ((base::PositionedWithoutComment&)node,false); 
  visit   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::CompilationUnit& node , bool callVirtualBase) {
  visitEnd   ((base::PositionedWithoutComment&)node,false); 
  visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::Declaration& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit((struc::Member&)node,false); 
  visit   ((statm::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::Declaration& node , bool callVirtualBase) {
  if (callVirtualBase)
    visitEnd((struc::Member&)node,false); 
  visitEnd   ((statm::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::Enum& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::TypeDeclaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::Enum& node , bool callVirtualBase) {
  visitEnd   ((struc::TypeDeclaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::EnumConstant& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::VariableDeclaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::EnumConstant& node , bool callVirtualBase) {
  visitEnd   ((struc::VariableDeclaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::GenericDeclaration& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::GenericDeclaration& node , bool callVirtualBase) {
  if (callVirtualBase)
    visitEnd((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::Import& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::Import& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::InitializerBlock& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::Declaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::InitializerBlock& node , bool callVirtualBase) {
  visitEnd   ((struc::Declaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::InstanceInitializerBlock& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::InitializerBlock&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::InstanceInitializerBlock& node , bool callVirtualBase) {
  visitEnd   ((struc::InitializerBlock&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::Interface& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::InterfaceDeclaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::Interface& node , bool callVirtualBase) {
  visitEnd   ((struc::InterfaceDeclaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::InterfaceDeclaration& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::TypeDeclaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::InterfaceDeclaration& node , bool callVirtualBase) {
  visitEnd   ((struc::TypeDeclaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::InterfaceGeneric& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::InterfaceDeclaration&)node,false); 
  visit   ((struc::GenericDeclaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::InterfaceGeneric& node , bool callVirtualBase) {
  visitEnd   ((struc::InterfaceDeclaration&)node,false); 
  visitEnd   ((struc::GenericDeclaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::Member& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit((base::Commentable&)node,false); 
  visit   ((struc::AnnotatedElement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::Member& node , bool callVirtualBase) {
  if (callVirtualBase)
    visitEnd((base::Commentable&)node,false); 
  visitEnd   ((struc::AnnotatedElement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::Method& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::NormalMethod&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::Method& node , bool callVirtualBase) {
  visitEnd   ((struc::NormalMethod&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::MethodDeclaration& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::NamedDeclaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::MethodDeclaration& node , bool callVirtualBase) {
  visitEnd   ((struc::NamedDeclaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::MethodGeneric& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::NormalMethod&)node,false); 
  visit   ((struc::GenericDeclaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::MethodGeneric& node , bool callVirtualBase) {
  visitEnd   ((struc::NormalMethod&)node,false); 
  visitEnd   ((struc::GenericDeclaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::NamedDeclaration& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::Declaration&)node,false); 
  visit   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::NamedDeclaration& node , bool callVirtualBase) {
  visitEnd   ((struc::Declaration&)node,false); 
  visitEnd   ((base::Named&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::NormalMethod& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::MethodDeclaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::NormalMethod& node , bool callVirtualBase) {
  visitEnd   ((struc::MethodDeclaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::Package& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((base::Named&)node,false); 
  visit   ((struc::Scope&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::Package& node , bool callVirtualBase) {
  visitEnd   ((base::Named&)node,false); 
  visitEnd   ((struc::Scope&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::PackageDeclaration& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::PackageDeclaration& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::Parameter& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::VariableDeclaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::Parameter& node , bool callVirtualBase) {
  visitEnd   ((struc::VariableDeclaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::Scope& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::Scope& node , bool callVirtualBase) {
  if (callVirtualBase)
    visitEnd((struc::Member&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::StaticInitializerBlock& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::InitializerBlock&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::StaticInitializerBlock& node , bool callVirtualBase) {
  visitEnd   ((struc::InitializerBlock&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::TypeDeclaration& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::NamedDeclaration&)node,false); 
  visit   ((struc::Scope&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::TypeDeclaration& node , bool callVirtualBase) {
  visitEnd   ((struc::NamedDeclaration&)node,false); 
  visitEnd   ((struc::Scope&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::TypeParameter& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  visit   ((base::Positioned&)node,false); 
  visit   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::TypeParameter& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
  visitEnd   ((base::Named&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::Variable& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::VariableDeclaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::Variable& node , bool callVirtualBase) {
  visitEnd   ((struc::VariableDeclaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const struc::VariableDeclaration& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Base&)node,false); 
  if (callVirtualBase)
    visit   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visit   ((struc::Member&)node,false); 
  visit   ((struc::NamedDeclaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const struc::VariableDeclaration& node , bool callVirtualBase) {
  visitEnd   ((struc::NamedDeclaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Base&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Commentable&)node,false); 
  if (callVirtualBase)
    visitEnd   ((struc::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const type::ArrayType& node , bool callVirtualBase) {
  visit   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::ArrayType& node , bool callVirtualBase) {
  visitEnd   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visit(const type::BooleanType& node , bool callVirtualBase) {
  visit   ((type::PrimitiveType&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::BooleanType& node , bool callVirtualBase) {
  visitEnd   ((type::PrimitiveType&)node,false); 
}

void VisitorAbstractNodes::visit(const type::BoundedWildcardType& node , bool callVirtualBase) {
  visit   ((type::WildcardType&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::BoundedWildcardType& node , bool callVirtualBase) {
  visitEnd   ((type::WildcardType&)node,false); 
}

void VisitorAbstractNodes::visit(const type::ByteType& node , bool callVirtualBase) {
  visit   ((type::PrimitiveType&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::ByteType& node , bool callVirtualBase) {
  visitEnd   ((type::PrimitiveType&)node,false); 
}

void VisitorAbstractNodes::visit(const type::CharType& node , bool callVirtualBase) {
  visit   ((type::PrimitiveType&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::CharType& node , bool callVirtualBase) {
  visitEnd   ((type::PrimitiveType&)node,false); 
}

void VisitorAbstractNodes::visit(const type::ClassType& node , bool callVirtualBase) {
  visit   ((type::ScopedType&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::ClassType& node , bool callVirtualBase) {
  visitEnd   ((type::ScopedType&)node,false); 
}

void VisitorAbstractNodes::visit(const type::DoubleType& node , bool callVirtualBase) {
  visit   ((type::PrimitiveType&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::DoubleType& node , bool callVirtualBase) {
  visitEnd   ((type::PrimitiveType&)node,false); 
}

void VisitorAbstractNodes::visit(const type::ErrorType& node , bool callVirtualBase) {
  visit   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::ErrorType& node , bool callVirtualBase) {
  visitEnd   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visit(const type::FloatType& node , bool callVirtualBase) {
  visit   ((type::PrimitiveType&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::FloatType& node , bool callVirtualBase) {
  visitEnd   ((type::PrimitiveType&)node,false); 
}

void VisitorAbstractNodes::visit(const type::IntType& node , bool callVirtualBase) {
  visit   ((type::PrimitiveType&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::IntType& node , bool callVirtualBase) {
  visitEnd   ((type::PrimitiveType&)node,false); 
}

void VisitorAbstractNodes::visit(const type::LongType& node , bool callVirtualBase) {
  visit   ((type::PrimitiveType&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::LongType& node , bool callVirtualBase) {
  visitEnd   ((type::PrimitiveType&)node,false); 
}

void VisitorAbstractNodes::visit(const type::LowerBoundedWildcardType& node , bool callVirtualBase) {
  visit   ((type::BoundedWildcardType&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::LowerBoundedWildcardType& node , bool callVirtualBase) {
  visitEnd   ((type::BoundedWildcardType&)node,false); 
}

void VisitorAbstractNodes::visit(const type::MethodType& node , bool callVirtualBase) {
  visit   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::MethodType& node , bool callVirtualBase) {
  visitEnd   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visit(const type::NoType& node , bool callVirtualBase) {
  visit   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::NoType& node , bool callVirtualBase) {
  visitEnd   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visit(const type::NullType& node , bool callVirtualBase) {
  visit   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::NullType& node , bool callVirtualBase) {
  visitEnd   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visit(const type::PackageType& node , bool callVirtualBase) {
  visit   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::PackageType& node , bool callVirtualBase) {
  visitEnd   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visit(const type::ParameterizedType& node , bool callVirtualBase) {
  visit   ((type::ScopedType&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::ParameterizedType& node , bool callVirtualBase) {
  visitEnd   ((type::ScopedType&)node,false); 
}

void VisitorAbstractNodes::visit(const type::PrimitiveType& node , bool callVirtualBase) {
  visit   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::PrimitiveType& node , bool callVirtualBase) {
  visitEnd   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visit(const type::ScopedType& node , bool callVirtualBase) {
  visit   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::ScopedType& node , bool callVirtualBase) {
  visitEnd   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visit(const type::ShortType& node , bool callVirtualBase) {
  visit   ((type::PrimitiveType&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::ShortType& node , bool callVirtualBase) {
  visitEnd   ((type::PrimitiveType&)node,false); 
}

void VisitorAbstractNodes::visit(const type::Type& node , bool callVirtualBase) {
  visit   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::Type& node , bool callVirtualBase) {
  visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const type::TypeVariable& node , bool callVirtualBase) {
  visit   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::TypeVariable& node , bool callVirtualBase) {
  visitEnd   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visit(const type::UnboundedWildcardType& node , bool callVirtualBase) {
  visit   ((type::WildcardType&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::UnboundedWildcardType& node , bool callVirtualBase) {
  visitEnd   ((type::WildcardType&)node,false); 
}

void VisitorAbstractNodes::visit(const type::UnionType& node , bool callVirtualBase) {
  visit   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::UnionType& node , bool callVirtualBase) {
  visitEnd   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visit(const type::UpperBoundedWildcardType& node , bool callVirtualBase) {
  visit   ((type::BoundedWildcardType&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::UpperBoundedWildcardType& node , bool callVirtualBase) {
  visitEnd   ((type::BoundedWildcardType&)node,false); 
}

void VisitorAbstractNodes::visit(const type::VoidType& node , bool callVirtualBase) {
  visit   ((type::PrimitiveType&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::VoidType& node , bool callVirtualBase) {
  visitEnd   ((type::PrimitiveType&)node,false); 
}

void VisitorAbstractNodes::visit(const type::WildcardType& node , bool callVirtualBase) {
  visit   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::WildcardType& node , bool callVirtualBase) {
  visitEnd   ((type::Type&)node,false); 
}


}}}
