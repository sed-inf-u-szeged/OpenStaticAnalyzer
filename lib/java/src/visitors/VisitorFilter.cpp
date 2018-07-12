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
VisitorFilter::VisitorFilter(bool filter) : Visitor() ,selector( filter?&Factory::setFilteredThisNodeOnly : &Factory::setNotFilteredThisNodeOnly) {
}

VisitorFilter::~VisitorFilter() {
}

void VisitorFilter::visitEnd(const base::BlockComment& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const base::JavadocComment& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const base::LineComment& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::ArrayAccess& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::ArrayTypeExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::Assignment& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::BooleanLiteral& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::CharacterLiteral& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::ClassLiteral& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::Conditional& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::DoubleLiteral& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::Erroneous& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::ErroneousTypeExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::ExternalTypeExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::FieldAccess& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::FloatLiteral& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::Identifier& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::InfixExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::InstanceOf& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::IntegerLiteral& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::LongLiteral& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::MarkerAnnotation& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::MethodInvocation& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::NewArray& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::NewClass& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::NormalAnnotation& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::NullLiteral& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::ParenthesizedExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::PostfixExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::PrefixExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::PrimitiveTypeExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::QualifiedTypeExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::SimpleTypeExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::SingleElementAnnotation& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::StringLiteral& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::Super& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::This& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::TypeApplyExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::TypeCast& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::TypeUnionExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expr::WildcardExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::Assert& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::BasicFor& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::Block& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::Break& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::Case& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::Continue& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::Default& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::Do& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::Empty& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::EnhancedFor& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::ExpressionStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::Handler& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::If& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::LabeledStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::Return& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::Switch& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::Synchronized& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::Throw& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::Try& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statm::While& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::AnnotationType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::AnnotationTypeElement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::AnonymousClass& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::Class& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::ClassGeneric& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::CompilationUnit& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::Enum& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::EnumConstant& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::Import& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::InstanceInitializerBlock& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::Interface& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::InterfaceGeneric& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::Method& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::MethodGeneric& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::Package& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::PackageDeclaration& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::Parameter& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::StaticInitializerBlock& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::TypeParameter& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const struc::Variable& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::ArrayType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::BooleanType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::ByteType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::CharType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::ClassType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::DoubleType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::ErrorType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::FloatType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::IntType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::LongType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::LowerBoundedWildcardType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::MethodType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::NoType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::NullType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::PackageType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::ParameterizedType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::ShortType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::TypeVariable& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::UnboundedWildcardType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::UnionType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::UpperBoundedWildcardType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::VoidType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}


}}}
