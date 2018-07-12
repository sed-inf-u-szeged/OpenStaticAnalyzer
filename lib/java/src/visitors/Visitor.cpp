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
Visitor::Visitor(): depth(0) {
}

Visitor::~Visitor() {
}

unsigned Visitor::getDepth() const {
  return depth;
}

void Visitor::incDepth() {
  ++depth;
}

void Visitor::decDepth() {
  --depth;
}

void Visitor::beginVisit() {
}

void Visitor::finishVisit() {
}

void Visitor::visit(const base::BlockComment& node , bool callVirtualBase) {}

void Visitor::visitEnd(const base::BlockComment& node , bool callVirtualBase) { }

void Visitor::visit(const base::JavadocComment& node , bool callVirtualBase) {}

void Visitor::visitEnd(const base::JavadocComment& node , bool callVirtualBase) { }

void Visitor::visit(const base::LineComment& node , bool callVirtualBase) {}

void Visitor::visitEnd(const base::LineComment& node , bool callVirtualBase) { }

void Visitor::visit(const expr::ArrayAccess& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::ArrayAccess& node , bool callVirtualBase) { }

void Visitor::visit(const expr::ArrayTypeExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::ArrayTypeExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expr::Assignment& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::Assignment& node , bool callVirtualBase) { }

void Visitor::visit(const expr::BooleanLiteral& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::BooleanLiteral& node , bool callVirtualBase) { }

void Visitor::visit(const expr::CharacterLiteral& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::CharacterLiteral& node , bool callVirtualBase) { }

void Visitor::visit(const expr::ClassLiteral& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::ClassLiteral& node , bool callVirtualBase) { }

void Visitor::visit(const expr::Conditional& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::Conditional& node , bool callVirtualBase) { }

void Visitor::visit(const expr::DoubleLiteral& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::DoubleLiteral& node , bool callVirtualBase) { }

void Visitor::visit(const expr::Erroneous& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::Erroneous& node , bool callVirtualBase) { }

void Visitor::visit(const expr::ErroneousTypeExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::ErroneousTypeExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expr::ExternalTypeExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::ExternalTypeExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expr::FieldAccess& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::FieldAccess& node , bool callVirtualBase) { }

void Visitor::visit(const expr::FloatLiteral& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::FloatLiteral& node , bool callVirtualBase) { }

void Visitor::visit(const expr::Identifier& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::Identifier& node , bool callVirtualBase) { }

void Visitor::visit(const expr::InfixExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::InfixExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expr::InstanceOf& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::InstanceOf& node , bool callVirtualBase) { }

void Visitor::visit(const expr::IntegerLiteral& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::IntegerLiteral& node , bool callVirtualBase) { }

void Visitor::visit(const expr::LongLiteral& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::LongLiteral& node , bool callVirtualBase) { }

void Visitor::visit(const expr::MarkerAnnotation& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::MarkerAnnotation& node , bool callVirtualBase) { }

void Visitor::visit(const expr::MethodInvocation& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::MethodInvocation& node , bool callVirtualBase) { }

void Visitor::visit(const expr::NewArray& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::NewArray& node , bool callVirtualBase) { }

void Visitor::visit(const expr::NewClass& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::NewClass& node , bool callVirtualBase) { }

void Visitor::visit(const expr::NormalAnnotation& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::NormalAnnotation& node , bool callVirtualBase) { }

void Visitor::visit(const expr::NullLiteral& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::NullLiteral& node , bool callVirtualBase) { }

void Visitor::visit(const expr::ParenthesizedExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::ParenthesizedExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expr::PostfixExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::PostfixExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expr::PrefixExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::PrefixExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expr::PrimitiveTypeExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::PrimitiveTypeExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expr::QualifiedTypeExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::QualifiedTypeExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expr::SimpleTypeExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::SimpleTypeExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expr::SingleElementAnnotation& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::SingleElementAnnotation& node , bool callVirtualBase) { }

void Visitor::visit(const expr::StringLiteral& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::StringLiteral& node , bool callVirtualBase) { }

void Visitor::visit(const expr::Super& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::Super& node , bool callVirtualBase) { }

void Visitor::visit(const expr::This& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::This& node , bool callVirtualBase) { }

void Visitor::visit(const expr::TypeApplyExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::TypeApplyExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expr::TypeCast& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::TypeCast& node , bool callVirtualBase) { }

void Visitor::visit(const expr::TypeUnionExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::TypeUnionExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expr::WildcardExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expr::WildcardExpression& node , bool callVirtualBase) { }

void Visitor::visit(const statm::Assert& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::Assert& node , bool callVirtualBase) { }

void Visitor::visit(const statm::BasicFor& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::BasicFor& node , bool callVirtualBase) { }

void Visitor::visit(const statm::Block& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::Block& node , bool callVirtualBase) { }

void Visitor::visit(const statm::Break& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::Break& node , bool callVirtualBase) { }

void Visitor::visit(const statm::Case& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::Case& node , bool callVirtualBase) { }

void Visitor::visit(const statm::Continue& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::Continue& node , bool callVirtualBase) { }

void Visitor::visit(const statm::Default& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::Default& node , bool callVirtualBase) { }

void Visitor::visit(const statm::Do& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::Do& node , bool callVirtualBase) { }

void Visitor::visit(const statm::Empty& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::Empty& node , bool callVirtualBase) { }

void Visitor::visit(const statm::EnhancedFor& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::EnhancedFor& node , bool callVirtualBase) { }

void Visitor::visit(const statm::ExpressionStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::ExpressionStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statm::Handler& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::Handler& node , bool callVirtualBase) { }

void Visitor::visit(const statm::If& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::If& node , bool callVirtualBase) { }

void Visitor::visit(const statm::LabeledStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::LabeledStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statm::Return& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::Return& node , bool callVirtualBase) { }

void Visitor::visit(const statm::Switch& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::Switch& node , bool callVirtualBase) { }

void Visitor::visit(const statm::Synchronized& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::Synchronized& node , bool callVirtualBase) { }

void Visitor::visit(const statm::Throw& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::Throw& node , bool callVirtualBase) { }

void Visitor::visit(const statm::Try& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::Try& node , bool callVirtualBase) { }

void Visitor::visit(const statm::While& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statm::While& node , bool callVirtualBase) { }

void Visitor::visit(const struc::AnnotationType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::AnnotationType& node , bool callVirtualBase) { }

void Visitor::visit(const struc::AnnotationTypeElement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::AnnotationTypeElement& node , bool callVirtualBase) { }

void Visitor::visit(const struc::AnonymousClass& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::AnonymousClass& node , bool callVirtualBase) { }

void Visitor::visit(const struc::Class& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::Class& node , bool callVirtualBase) { }

void Visitor::visit(const struc::ClassGeneric& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::ClassGeneric& node , bool callVirtualBase) { }

void Visitor::visit(const struc::CompilationUnit& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::CompilationUnit& node , bool callVirtualBase) { }

void Visitor::visit(const struc::Enum& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::Enum& node , bool callVirtualBase) { }

void Visitor::visit(const struc::EnumConstant& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::EnumConstant& node , bool callVirtualBase) { }

void Visitor::visit(const struc::Import& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::Import& node , bool callVirtualBase) { }

void Visitor::visit(const struc::InstanceInitializerBlock& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::InstanceInitializerBlock& node , bool callVirtualBase) { }

void Visitor::visit(const struc::Interface& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::Interface& node , bool callVirtualBase) { }

void Visitor::visit(const struc::InterfaceGeneric& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::InterfaceGeneric& node , bool callVirtualBase) { }

void Visitor::visit(const struc::Method& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::Method& node , bool callVirtualBase) { }

void Visitor::visit(const struc::MethodGeneric& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::MethodGeneric& node , bool callVirtualBase) { }

void Visitor::visit(const struc::Package& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::Package& node , bool callVirtualBase) { }

void Visitor::visit(const struc::PackageDeclaration& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::PackageDeclaration& node , bool callVirtualBase) { }

void Visitor::visit(const struc::Parameter& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::Parameter& node , bool callVirtualBase) { }

void Visitor::visit(const struc::StaticInitializerBlock& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::StaticInitializerBlock& node , bool callVirtualBase) { }

void Visitor::visit(const struc::TypeParameter& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::TypeParameter& node , bool callVirtualBase) { }

void Visitor::visit(const struc::Variable& node , bool callVirtualBase) {}

void Visitor::visitEnd(const struc::Variable& node , bool callVirtualBase) { }

void Visitor::visit(const type::ArrayType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::ArrayType& node , bool callVirtualBase) { }

void Visitor::visit(const type::BooleanType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::BooleanType& node , bool callVirtualBase) { }

void Visitor::visit(const type::ByteType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::ByteType& node , bool callVirtualBase) { }

void Visitor::visit(const type::CharType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::CharType& node , bool callVirtualBase) { }

void Visitor::visit(const type::ClassType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::ClassType& node , bool callVirtualBase) { }

void Visitor::visit(const type::DoubleType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::DoubleType& node , bool callVirtualBase) { }

void Visitor::visit(const type::ErrorType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::ErrorType& node , bool callVirtualBase) { }

void Visitor::visit(const type::FloatType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::FloatType& node , bool callVirtualBase) { }

void Visitor::visit(const type::IntType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::IntType& node , bool callVirtualBase) { }

void Visitor::visit(const type::LongType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::LongType& node , bool callVirtualBase) { }

void Visitor::visit(const type::LowerBoundedWildcardType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::LowerBoundedWildcardType& node , bool callVirtualBase) { }

void Visitor::visit(const type::MethodType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::MethodType& node , bool callVirtualBase) { }

void Visitor::visit(const type::NoType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::NoType& node , bool callVirtualBase) { }

void Visitor::visit(const type::NullType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::NullType& node , bool callVirtualBase) { }

void Visitor::visit(const type::PackageType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::PackageType& node , bool callVirtualBase) { }

void Visitor::visit(const type::ParameterizedType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::ParameterizedType& node , bool callVirtualBase) { }

void Visitor::visit(const type::ShortType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::ShortType& node , bool callVirtualBase) { }

void Visitor::visit(const type::TypeVariable& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::TypeVariable& node , bool callVirtualBase) { }

void Visitor::visit(const type::UnboundedWildcardType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::UnboundedWildcardType& node , bool callVirtualBase) { }

void Visitor::visit(const type::UnionType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::UnionType& node , bool callVirtualBase) { }

void Visitor::visit(const type::UpperBoundedWildcardType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::UpperBoundedWildcardType& node , bool callVirtualBase) { }

void Visitor::visit(const type::VoidType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::VoidType& node , bool callVirtualBase) { }

void Visitor::visitCommentable_Comments(const base::Commentable& begin, const base::Comment& end) { }

void Visitor::visitEndCommentable_Comments(const base::Commentable& begin, const base::Comment& end) { }

void Visitor::visitAnnotation_HasAnnotationName(const expr::Annotation& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndAnnotation_HasAnnotationName(const expr::Annotation& begin, const expr::TypeExpression& end) { }

void Visitor::visitArrayTypeExpression_HasComponentType(const expr::ArrayTypeExpression& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndArrayTypeExpression_HasComponentType(const expr::ArrayTypeExpression& begin, const expr::TypeExpression& end) { }

void Visitor::visitBinary_HasLeftOperand(const expr::Binary& begin, const expr::Expression& end) { }

void Visitor::visitEndBinary_HasLeftOperand(const expr::Binary& begin, const expr::Expression& end) { }

void Visitor::visitBinary_HasRightOperand(const expr::Binary& begin, const expr::Expression& end) { }

void Visitor::visitEndBinary_HasRightOperand(const expr::Binary& begin, const expr::Expression& end) { }

void Visitor::visitClassLiteral_HasComponentType(const expr::ClassLiteral& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndClassLiteral_HasComponentType(const expr::ClassLiteral& begin, const expr::TypeExpression& end) { }

void Visitor::visitConditional_HasCondition(const expr::Conditional& begin, const expr::Expression& end) { }

void Visitor::visitEndConditional_HasCondition(const expr::Conditional& begin, const expr::Expression& end) { }

void Visitor::visitConditional_HasTrueExpression(const expr::Conditional& begin, const expr::Expression& end) { }

void Visitor::visitEndConditional_HasTrueExpression(const expr::Conditional& begin, const expr::Expression& end) { }

void Visitor::visitConditional_HasFalseExpression(const expr::Conditional& begin, const expr::Expression& end) { }

void Visitor::visitEndConditional_HasFalseExpression(const expr::Conditional& begin, const expr::Expression& end) { }

void Visitor::visitErroneous_HasErrors(const expr::Erroneous& begin, const base::Positioned& end) { }

void Visitor::visitEndErroneous_HasErrors(const expr::Erroneous& begin, const base::Positioned& end) { }

void Visitor::visitErroneousTypeExpression_HasErrors(const expr::ErroneousTypeExpression& begin, const base::Positioned& end) { }

void Visitor::visitEndErroneousTypeExpression_HasErrors(const expr::ErroneousTypeExpression& begin, const base::Positioned& end) { }

void Visitor::visitExpression_Type(const expr::Expression& begin, const type::Type& end) { }

void Visitor::visitEndExpression_Type(const expr::Expression& begin, const type::Type& end) { }

void Visitor::visitIdentifier_RefersTo(const expr::Identifier& begin, const base::Named& end) { }

void Visitor::visitEndIdentifier_RefersTo(const expr::Identifier& begin, const base::Named& end) { }

void Visitor::visitInstanceOf_HasTypeOperand(const expr::InstanceOf& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndInstanceOf_HasTypeOperand(const expr::InstanceOf& begin, const expr::TypeExpression& end) { }

void Visitor::visitMethodInvocation_HasTypeArguments(const expr::MethodInvocation& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndMethodInvocation_HasTypeArguments(const expr::MethodInvocation& begin, const expr::TypeExpression& end) { }

void Visitor::visitMethodInvocation_HasArguments(const expr::MethodInvocation& begin, const expr::Expression& end) { }

void Visitor::visitEndMethodInvocation_HasArguments(const expr::MethodInvocation& begin, const expr::Expression& end) { }

void Visitor::visitMethodInvocation_Invokes(const expr::MethodInvocation& begin, const struc::MethodDeclaration& end) { }

void Visitor::visitEndMethodInvocation_Invokes(const expr::MethodInvocation& begin, const struc::MethodDeclaration& end) { }

void Visitor::visitNewArray_HasComponentType(const expr::NewArray& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndNewArray_HasComponentType(const expr::NewArray& begin, const expr::TypeExpression& end) { }

void Visitor::visitNewArray_HasDimensions(const expr::NewArray& begin, const expr::Expression& end) { }

void Visitor::visitEndNewArray_HasDimensions(const expr::NewArray& begin, const expr::Expression& end) { }

void Visitor::visitNewArray_HasInitializers(const expr::NewArray& begin, const expr::Expression& end) { }

void Visitor::visitEndNewArray_HasInitializers(const expr::NewArray& begin, const expr::Expression& end) { }

void Visitor::visitNewClass_HasEnclosingExpression(const expr::NewClass& begin, const expr::Expression& end) { }

void Visitor::visitEndNewClass_HasEnclosingExpression(const expr::NewClass& begin, const expr::Expression& end) { }

void Visitor::visitNewClass_HasTypeArguments(const expr::NewClass& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndNewClass_HasTypeArguments(const expr::NewClass& begin, const expr::TypeExpression& end) { }

void Visitor::visitNewClass_HasTypeName(const expr::NewClass& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndNewClass_HasTypeName(const expr::NewClass& begin, const expr::TypeExpression& end) { }

void Visitor::visitNewClass_HasArguments(const expr::NewClass& begin, const expr::Expression& end) { }

void Visitor::visitEndNewClass_HasArguments(const expr::NewClass& begin, const expr::Expression& end) { }

void Visitor::visitNewClass_HasAnonymousClass(const expr::NewClass& begin, const struc::AnonymousClass& end) { }

void Visitor::visitEndNewClass_HasAnonymousClass(const expr::NewClass& begin, const struc::AnonymousClass& end) { }

void Visitor::visitNewClass_Constructor(const expr::NewClass& begin, const struc::NormalMethod& end) { }

void Visitor::visitEndNewClass_Constructor(const expr::NewClass& begin, const struc::NormalMethod& end) { }

void Visitor::visitNormalAnnotation_HasArguments(const expr::NormalAnnotation& begin, const expr::Expression& end) { }

void Visitor::visitEndNormalAnnotation_HasArguments(const expr::NormalAnnotation& begin, const expr::Expression& end) { }

void Visitor::visitQualifiedTypeExpression_HasQualifierType(const expr::QualifiedTypeExpression& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndQualifiedTypeExpression_HasQualifierType(const expr::QualifiedTypeExpression& begin, const expr::TypeExpression& end) { }

void Visitor::visitQualifiedTypeExpression_HasSimpleType(const expr::QualifiedTypeExpression& begin, const expr::SimpleTypeExpression& end) { }

void Visitor::visitEndQualifiedTypeExpression_HasSimpleType(const expr::QualifiedTypeExpression& begin, const expr::SimpleTypeExpression& end) { }

void Visitor::visitSingleElementAnnotation_HasArgument(const expr::SingleElementAnnotation& begin, const expr::Expression& end) { }

void Visitor::visitEndSingleElementAnnotation_HasArgument(const expr::SingleElementAnnotation& begin, const expr::Expression& end) { }

void Visitor::visitTypeApplyExpression_HasRawType(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndTypeApplyExpression_HasRawType(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end) { }

void Visitor::visitTypeApplyExpression_HasTypeArguments(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndTypeApplyExpression_HasTypeArguments(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end) { }

void Visitor::visitTypeCast_HasTypeOperand(const expr::TypeCast& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndTypeCast_HasTypeOperand(const expr::TypeCast& begin, const expr::TypeExpression& end) { }

void Visitor::visitTypeUnionExpression_HasAlternatives(const expr::TypeUnionExpression& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndTypeUnionExpression_HasAlternatives(const expr::TypeUnionExpression& begin, const expr::TypeExpression& end) { }

void Visitor::visitUnary_HasOperand(const expr::Unary& begin, const expr::Expression& end) { }

void Visitor::visitEndUnary_HasOperand(const expr::Unary& begin, const expr::Expression& end) { }

void Visitor::visitWildcardExpression_HasBound(const expr::WildcardExpression& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndWildcardExpression_HasBound(const expr::WildcardExpression& begin, const expr::TypeExpression& end) { }

void Visitor::visitAssert_HasCondition(const statm::Assert& begin, const expr::Expression& end) { }

void Visitor::visitEndAssert_HasCondition(const statm::Assert& begin, const expr::Expression& end) { }

void Visitor::visitAssert_HasDetail(const statm::Assert& begin, const expr::Expression& end) { }

void Visitor::visitEndAssert_HasDetail(const statm::Assert& begin, const expr::Expression& end) { }

void Visitor::visitBasicFor_HasInitializers(const statm::BasicFor& begin, const statm::Statement& end) { }

void Visitor::visitEndBasicFor_HasInitializers(const statm::BasicFor& begin, const statm::Statement& end) { }

void Visitor::visitBasicFor_HasCondition(const statm::BasicFor& begin, const expr::Expression& end) { }

void Visitor::visitEndBasicFor_HasCondition(const statm::BasicFor& begin, const expr::Expression& end) { }

void Visitor::visitBasicFor_HasUpdates(const statm::BasicFor& begin, const statm::Statement& end) { }

void Visitor::visitEndBasicFor_HasUpdates(const statm::BasicFor& begin, const statm::Statement& end) { }

void Visitor::visitBlock_HasStatements(const statm::Block& begin, const statm::Statement& end) { }

void Visitor::visitEndBlock_HasStatements(const statm::Block& begin, const statm::Statement& end) { }

void Visitor::visitCase_HasExpression(const statm::Case& begin, const expr::Expression& end) { }

void Visitor::visitEndCase_HasExpression(const statm::Case& begin, const expr::Expression& end) { }

void Visitor::visitDo_HasCondition(const statm::Do& begin, const expr::Expression& end) { }

void Visitor::visitEndDo_HasCondition(const statm::Do& begin, const expr::Expression& end) { }

void Visitor::visitEnhancedFor_HasParameter(const statm::EnhancedFor& begin, const struc::Parameter& end) { }

void Visitor::visitEndEnhancedFor_HasParameter(const statm::EnhancedFor& begin, const struc::Parameter& end) { }

void Visitor::visitEnhancedFor_HasExpression(const statm::EnhancedFor& begin, const expr::Expression& end) { }

void Visitor::visitEndEnhancedFor_HasExpression(const statm::EnhancedFor& begin, const expr::Expression& end) { }

void Visitor::visitExpressionStatement_HasExpression(const statm::ExpressionStatement& begin, const expr::Expression& end) { }

void Visitor::visitEndExpressionStatement_HasExpression(const statm::ExpressionStatement& begin, const expr::Expression& end) { }

void Visitor::visitHandler_HasParameter(const statm::Handler& begin, const struc::Parameter& end) { }

void Visitor::visitEndHandler_HasParameter(const statm::Handler& begin, const struc::Parameter& end) { }

void Visitor::visitHandler_HasBlock(const statm::Handler& begin, const statm::Block& end) { }

void Visitor::visitEndHandler_HasBlock(const statm::Handler& begin, const statm::Block& end) { }

void Visitor::visitIf_HasSubstatement(const statm::If& begin, const statm::Statement& end) { }

void Visitor::visitEndIf_HasSubstatement(const statm::If& begin, const statm::Statement& end) { }

void Visitor::visitIf_HasFalseSubstatement(const statm::If& begin, const statm::Statement& end) { }

void Visitor::visitEndIf_HasFalseSubstatement(const statm::If& begin, const statm::Statement& end) { }

void Visitor::visitIteration_HasSubstatement(const statm::Iteration& begin, const statm::Statement& end) { }

void Visitor::visitEndIteration_HasSubstatement(const statm::Iteration& begin, const statm::Statement& end) { }

void Visitor::visitJump_Target(const statm::Jump& begin, const statm::Statement& end) { }

void Visitor::visitEndJump_Target(const statm::Jump& begin, const statm::Statement& end) { }

void Visitor::visitLabeledStatement_HasStatement(const statm::LabeledStatement& begin, const statm::Statement& end) { }

void Visitor::visitEndLabeledStatement_HasStatement(const statm::LabeledStatement& begin, const statm::Statement& end) { }

void Visitor::visitReturn_HasExpression(const statm::Return& begin, const expr::Expression& end) { }

void Visitor::visitEndReturn_HasExpression(const statm::Return& begin, const expr::Expression& end) { }

void Visitor::visitSelection_HasCondition(const statm::Selection& begin, const expr::Expression& end) { }

void Visitor::visitEndSelection_HasCondition(const statm::Selection& begin, const expr::Expression& end) { }

void Visitor::visitSwitch_HasCases(const statm::Switch& begin, const statm::SwitchLabel& end) { }

void Visitor::visitEndSwitch_HasCases(const statm::Switch& begin, const statm::SwitchLabel& end) { }

void Visitor::visitSwitchLabel_HasStatements(const statm::SwitchLabel& begin, const statm::Statement& end) { }

void Visitor::visitEndSwitchLabel_HasStatements(const statm::SwitchLabel& begin, const statm::Statement& end) { }

void Visitor::visitSynchronized_HasLock(const statm::Synchronized& begin, const expr::Expression& end) { }

void Visitor::visitEndSynchronized_HasLock(const statm::Synchronized& begin, const expr::Expression& end) { }

void Visitor::visitSynchronized_HasBlock(const statm::Synchronized& begin, const statm::Block& end) { }

void Visitor::visitEndSynchronized_HasBlock(const statm::Synchronized& begin, const statm::Block& end) { }

void Visitor::visitThrow_HasExpression(const statm::Throw& begin, const expr::Expression& end) { }

void Visitor::visitEndThrow_HasExpression(const statm::Throw& begin, const expr::Expression& end) { }

void Visitor::visitTry_HasResources(const statm::Try& begin, const struc::Variable& end) { }

void Visitor::visitEndTry_HasResources(const statm::Try& begin, const struc::Variable& end) { }

void Visitor::visitTry_HasBlock(const statm::Try& begin, const statm::Block& end) { }

void Visitor::visitEndTry_HasBlock(const statm::Try& begin, const statm::Block& end) { }

void Visitor::visitTry_HasHandlers(const statm::Try& begin, const statm::Handler& end) { }

void Visitor::visitEndTry_HasHandlers(const statm::Try& begin, const statm::Handler& end) { }

void Visitor::visitTry_HasFinallyBlock(const statm::Try& begin, const statm::Block& end) { }

void Visitor::visitEndTry_HasFinallyBlock(const statm::Try& begin, const statm::Block& end) { }

void Visitor::visitWhile_HasCondition(const statm::While& begin, const expr::Expression& end) { }

void Visitor::visitEndWhile_HasCondition(const statm::While& begin, const expr::Expression& end) { }

void Visitor::visitAnnotatedElement_HasAnnotations(const struc::AnnotatedElement& begin, const expr::Annotation& end) { }

void Visitor::visitEndAnnotatedElement_HasAnnotations(const struc::AnnotatedElement& begin, const expr::Annotation& end) { }

void Visitor::visitAnnotationTypeElement_HasDefaultValue(const struc::AnnotationTypeElement& begin, const expr::Expression& end) { }

void Visitor::visitEndAnnotationTypeElement_HasDefaultValue(const struc::AnnotationTypeElement& begin, const expr::Expression& end) { }

void Visitor::visitCompilationUnit_HasPackageDeclaration(const struc::CompilationUnit& begin, const struc::PackageDeclaration& end) { }

void Visitor::visitEndCompilationUnit_HasPackageDeclaration(const struc::CompilationUnit& begin, const struc::PackageDeclaration& end) { }

void Visitor::visitCompilationUnit_HasImports(const struc::CompilationUnit& begin, const struc::Import& end) { }

void Visitor::visitEndCompilationUnit_HasImports(const struc::CompilationUnit& begin, const struc::Import& end) { }

void Visitor::visitCompilationUnit_TypeDeclarations(const struc::CompilationUnit& begin, const struc::TypeDeclaration& end) { }

void Visitor::visitEndCompilationUnit_TypeDeclarations(const struc::CompilationUnit& begin, const struc::TypeDeclaration& end) { }

void Visitor::visitCompilationUnit_HasOthers(const struc::CompilationUnit& begin, const base::Positioned& end) { }

void Visitor::visitEndCompilationUnit_HasOthers(const struc::CompilationUnit& begin, const base::Positioned& end) { }

void Visitor::visitEnumConstant_HasNewClass(const struc::EnumConstant& begin, const expr::NewClass& end) { }

void Visitor::visitEndEnumConstant_HasNewClass(const struc::EnumConstant& begin, const expr::NewClass& end) { }

void Visitor::visitGenericDeclaration_HasTypeParameters(const struc::GenericDeclaration& begin, const struc::TypeParameter& end) { }

void Visitor::visitEndGenericDeclaration_HasTypeParameters(const struc::GenericDeclaration& begin, const struc::TypeParameter& end) { }

void Visitor::visitImport_HasTarget(const struc::Import& begin, const expr::Expression& end) { }

void Visitor::visitEndImport_HasTarget(const struc::Import& begin, const expr::Expression& end) { }

void Visitor::visitInitializerBlock_HasBody(const struc::InitializerBlock& begin, const statm::Block& end) { }

void Visitor::visitEndInitializerBlock_HasBody(const struc::InitializerBlock& begin, const statm::Block& end) { }

void Visitor::visitMethodDeclaration_HasReturnType(const struc::MethodDeclaration& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndMethodDeclaration_HasReturnType(const struc::MethodDeclaration& begin, const expr::TypeExpression& end) { }

void Visitor::visitMethodDeclaration_MethodType(const struc::MethodDeclaration& begin, const type::MethodType& end) { }

void Visitor::visitEndMethodDeclaration_MethodType(const struc::MethodDeclaration& begin, const type::MethodType& end) { }

void Visitor::visitMethodDeclaration_Overrides(const struc::MethodDeclaration& begin, const struc::MethodDeclaration& end) { }

void Visitor::visitEndMethodDeclaration_Overrides(const struc::MethodDeclaration& begin, const struc::MethodDeclaration& end) { }

void Visitor::visitNormalMethod_HasParameters(const struc::NormalMethod& begin, const struc::Parameter& end) { }

void Visitor::visitEndNormalMethod_HasParameters(const struc::NormalMethod& begin, const struc::Parameter& end) { }

void Visitor::visitNormalMethod_HasBody(const struc::NormalMethod& begin, const statm::Block& end) { }

void Visitor::visitEndNormalMethod_HasBody(const struc::NormalMethod& begin, const statm::Block& end) { }

void Visitor::visitNormalMethod_HasThrownExceptions(const struc::NormalMethod& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndNormalMethod_HasThrownExceptions(const struc::NormalMethod& begin, const expr::TypeExpression& end) { }

void Visitor::visitPackage_HasCompilationUnits(const struc::Package& begin, const struc::CompilationUnit& end) { }

void Visitor::visitEndPackage_HasCompilationUnits(const struc::Package& begin, const struc::CompilationUnit& end) { }

void Visitor::visitPackageDeclaration_HasPackageName(const struc::PackageDeclaration& begin, const expr::Expression& end) { }

void Visitor::visitEndPackageDeclaration_HasPackageName(const struc::PackageDeclaration& begin, const expr::Expression& end) { }

void Visitor::visitPackageDeclaration_RefersTo(const struc::PackageDeclaration& begin, const struc::Package& end) { }

void Visitor::visitEndPackageDeclaration_RefersTo(const struc::PackageDeclaration& begin, const struc::Package& end) { }

void Visitor::visitScope_HasMembers(const struc::Scope& begin, const struc::Member& end) { }

void Visitor::visitEndScope_HasMembers(const struc::Scope& begin, const struc::Member& end) { }

void Visitor::visitTypeDeclaration_IsInCompilationUnit(const struc::TypeDeclaration& begin, const struc::CompilationUnit& end) { }

void Visitor::visitEndTypeDeclaration_IsInCompilationUnit(const struc::TypeDeclaration& begin, const struc::CompilationUnit& end) { }

void Visitor::visitTypeDeclaration_HasSuperClass(const struc::TypeDeclaration& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndTypeDeclaration_HasSuperClass(const struc::TypeDeclaration& begin, const expr::TypeExpression& end) { }

void Visitor::visitTypeDeclaration_HasSuperInterfaces(const struc::TypeDeclaration& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndTypeDeclaration_HasSuperInterfaces(const struc::TypeDeclaration& begin, const expr::TypeExpression& end) { }

void Visitor::visitTypeDeclaration_HasOthers(const struc::TypeDeclaration& begin, const base::Positioned& end) { }

void Visitor::visitEndTypeDeclaration_HasOthers(const struc::TypeDeclaration& begin, const base::Positioned& end) { }

void Visitor::visitTypeParameter_HasBounds(const struc::TypeParameter& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndTypeParameter_HasBounds(const struc::TypeParameter& begin, const expr::TypeExpression& end) { }

void Visitor::visitVariable_HasInitialValue(const struc::Variable& begin, const expr::Expression& end) { }

void Visitor::visitEndVariable_HasInitialValue(const struc::Variable& begin, const expr::Expression& end) { }

void Visitor::visitVariableDeclaration_HasType(const struc::VariableDeclaration& begin, const expr::TypeExpression& end) { }

void Visitor::visitEndVariableDeclaration_HasType(const struc::VariableDeclaration& begin, const expr::TypeExpression& end) { }

void Visitor::visitArrayType_ComponentType(const type::ArrayType& begin, const type::Type& end) { }

void Visitor::visitEndArrayType_ComponentType(const type::ArrayType& begin, const type::Type& end) { }

void Visitor::visitClassType_RefersTo(const type::ClassType& begin, const struc::TypeDeclaration& end) { }

void Visitor::visitEndClassType_RefersTo(const type::ClassType& begin, const struc::TypeDeclaration& end) { }

void Visitor::visitMethodType_ReturnType(const type::MethodType& begin, const type::Type& end) { }

void Visitor::visitEndMethodType_ReturnType(const type::MethodType& begin, const type::Type& end) { }

void Visitor::visitMethodType_ParameterTypes(const type::MethodType& begin, const type::Type& end) { }

void Visitor::visitEndMethodType_ParameterTypes(const type::MethodType& begin, const type::Type& end) { }

void Visitor::visitMethodType_ThrownTypes(const type::MethodType& begin, const type::Type& end) { }

void Visitor::visitEndMethodType_ThrownTypes(const type::MethodType& begin, const type::Type& end) { }

void Visitor::visitPackageType_RefersTo(const type::PackageType& begin, const struc::Package& end) { }

void Visitor::visitEndPackageType_RefersTo(const type::PackageType& begin, const struc::Package& end) { }

void Visitor::visitParameterizedType_RawType(const type::ParameterizedType& begin, const type::Type& end) { }

void Visitor::visitEndParameterizedType_RawType(const type::ParameterizedType& begin, const type::Type& end) { }

void Visitor::visitParameterizedType_ArgumentTypes(const type::ParameterizedType& begin, const type::Type& end) { }

void Visitor::visitEndParameterizedType_ArgumentTypes(const type::ParameterizedType& begin, const type::Type& end) { }

void Visitor::visitScopedType_Owner(const type::ScopedType& begin, const type::Type& end) { }

void Visitor::visitEndScopedType_Owner(const type::ScopedType& begin, const type::Type& end) { }

void Visitor::visitTypeVariable_RefersTo(const type::TypeVariable& begin, const struc::TypeParameter& end) { }

void Visitor::visitEndTypeVariable_RefersTo(const type::TypeVariable& begin, const struc::TypeParameter& end) { }

void Visitor::visitUnionType_Alternatives(const type::UnionType& begin, const type::Type& end) { }

void Visitor::visitEndUnionType_Alternatives(const type::UnionType& begin, const type::Type& end) { }

void Visitor::visitWildcardType_Bound(const type::WildcardType& begin, const type::Type& end) { }

void Visitor::visitEndWildcardType_Bound(const type::WildcardType& begin, const type::Type& end) { }


}}}
