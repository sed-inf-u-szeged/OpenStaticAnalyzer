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

const char* VisitorAsgStat::nodeNames[] = {
        "base::Base",
        "base::BlockComment",
        "base::Comment",
        "base::Commentable",
        "base::JavadocComment",
        "base::LineComment",
        "base::Named",
        "base::NonJavadocComment",
        "base::Positioned",
        "base::PositionedWithoutComment",
        "expr::Annotation",
        "expr::ArrayAccess",
        "expr::ArrayTypeExpression",
        "expr::Assignment",
        "expr::Binary",
        "expr::BooleanLiteral",
        "expr::CharacterLiteral",
        "expr::ClassLiteral",
        "expr::Conditional",
        "expr::DoubleLiteral",
        "expr::Erroneous",
        "expr::ErroneousTypeExpression",
        "expr::Expression",
        "expr::ExternalTypeExpression",
        "expr::FieldAccess",
        "expr::FloatLiteral",
        "expr::Identifier",
        "expr::InfixExpression",
        "expr::InstanceOf",
        "expr::IntegerLiteral",
        "expr::Literal",
        "expr::LongLiteral",
        "expr::MarkerAnnotation",
        "expr::MethodInvocation",
        "expr::NewArray",
        "expr::NewClass",
        "expr::NormalAnnotation",
        "expr::NullLiteral",
        "expr::NumberLiteral",
        "expr::ParenthesizedExpression",
        "expr::PostfixExpression",
        "expr::PrefixExpression",
        "expr::PrimitiveTypeExpression",
        "expr::QualifiedTypeExpression",
        "expr::SimpleTypeExpression",
        "expr::SingleElementAnnotation",
        "expr::StringLiteral",
        "expr::Super",
        "expr::This",
        "expr::TypeApplyExpression",
        "expr::TypeCast",
        "expr::TypeExpression",
        "expr::TypeUnionExpression",
        "expr::Unary",
        "expr::WildcardExpression",
        "statm::Assert",
        "statm::BasicFor",
        "statm::Block",
        "statm::Break",
        "statm::Case",
        "statm::Continue",
        "statm::Default",
        "statm::Do",
        "statm::Empty",
        "statm::EnhancedFor",
        "statm::ExpressionStatement",
        "statm::For",
        "statm::Handler",
        "statm::If",
        "statm::Iteration",
        "statm::Jump",
        "statm::LabeledStatement",
        "statm::Return",
        "statm::Selection",
        "statm::Statement",
        "statm::Switch",
        "statm::SwitchLabel",
        "statm::Synchronized",
        "statm::Throw",
        "statm::Try",
        "statm::While",
        "struc::AnnotatedElement",
        "struc::AnnotationType",
        "struc::AnnotationTypeElement",
        "struc::AnonymousClass",
        "struc::Class",
        "struc::ClassDeclaration",
        "struc::ClassGeneric",
        "struc::CompilationUnit",
        "struc::Declaration",
        "struc::Enum",
        "struc::EnumConstant",
        "struc::GenericDeclaration",
        "struc::Import",
        "struc::InitializerBlock",
        "struc::InstanceInitializerBlock",
        "struc::Interface",
        "struc::InterfaceDeclaration",
        "struc::InterfaceGeneric",
        "struc::Member",
        "struc::Method",
        "struc::MethodDeclaration",
        "struc::MethodGeneric",
        "struc::NamedDeclaration",
        "struc::NormalMethod",
        "struc::Package",
        "struc::PackageDeclaration",
        "struc::Parameter",
        "struc::Scope",
        "struc::StaticInitializerBlock",
        "struc::TypeDeclaration",
        "struc::TypeParameter",
        "struc::Variable",
        "struc::VariableDeclaration",
        "type::ArrayType",
        "type::BooleanType",
        "type::BoundedWildcardType",
        "type::ByteType",
        "type::CharType",
        "type::ClassType",
        "type::DoubleType",
        "type::ErrorType",
        "type::FloatType",
        "type::IntType",
        "type::LongType",
        "type::LowerBoundedWildcardType",
        "type::MethodType",
        "type::NoType",
        "type::NullType",
        "type::PackageType",
        "type::ParameterizedType",
        "type::PrimitiveType",
        "type::ScopedType",
        "type::ShortType",
        "type::Type",
        "type::TypeVariable",
        "type::UnboundedWildcardType",
        "type::UnionType",
        "type::UpperBoundedWildcardType",
        "type::VoidType",
        "type::WildcardType",
};

const unsigned short VisitorAsgStat::nodeSizes[] = {
        sizeof(base::Base),
        sizeof(base::BlockComment),
        sizeof(base::Comment),
        sizeof(base::Commentable),
        sizeof(base::JavadocComment),
        sizeof(base::LineComment),
        sizeof(base::Named),
        sizeof(base::NonJavadocComment),
        sizeof(base::Positioned),
        sizeof(base::PositionedWithoutComment),
        sizeof(expr::Annotation),
        sizeof(expr::ArrayAccess),
        sizeof(expr::ArrayTypeExpression),
        sizeof(expr::Assignment),
        sizeof(expr::Binary),
        sizeof(expr::BooleanLiteral),
        sizeof(expr::CharacterLiteral),
        sizeof(expr::ClassLiteral),
        sizeof(expr::Conditional),
        sizeof(expr::DoubleLiteral),
        sizeof(expr::Erroneous),
        sizeof(expr::ErroneousTypeExpression),
        sizeof(expr::Expression),
        sizeof(expr::ExternalTypeExpression),
        sizeof(expr::FieldAccess),
        sizeof(expr::FloatLiteral),
        sizeof(expr::Identifier),
        sizeof(expr::InfixExpression),
        sizeof(expr::InstanceOf),
        sizeof(expr::IntegerLiteral),
        sizeof(expr::Literal),
        sizeof(expr::LongLiteral),
        sizeof(expr::MarkerAnnotation),
        sizeof(expr::MethodInvocation),
        sizeof(expr::NewArray),
        sizeof(expr::NewClass),
        sizeof(expr::NormalAnnotation),
        sizeof(expr::NullLiteral),
        sizeof(expr::NumberLiteral),
        sizeof(expr::ParenthesizedExpression),
        sizeof(expr::PostfixExpression),
        sizeof(expr::PrefixExpression),
        sizeof(expr::PrimitiveTypeExpression),
        sizeof(expr::QualifiedTypeExpression),
        sizeof(expr::SimpleTypeExpression),
        sizeof(expr::SingleElementAnnotation),
        sizeof(expr::StringLiteral),
        sizeof(expr::Super),
        sizeof(expr::This),
        sizeof(expr::TypeApplyExpression),
        sizeof(expr::TypeCast),
        sizeof(expr::TypeExpression),
        sizeof(expr::TypeUnionExpression),
        sizeof(expr::Unary),
        sizeof(expr::WildcardExpression),
        sizeof(statm::Assert),
        sizeof(statm::BasicFor),
        sizeof(statm::Block),
        sizeof(statm::Break),
        sizeof(statm::Case),
        sizeof(statm::Continue),
        sizeof(statm::Default),
        sizeof(statm::Do),
        sizeof(statm::Empty),
        sizeof(statm::EnhancedFor),
        sizeof(statm::ExpressionStatement),
        sizeof(statm::For),
        sizeof(statm::Handler),
        sizeof(statm::If),
        sizeof(statm::Iteration),
        sizeof(statm::Jump),
        sizeof(statm::LabeledStatement),
        sizeof(statm::Return),
        sizeof(statm::Selection),
        sizeof(statm::Statement),
        sizeof(statm::Switch),
        sizeof(statm::SwitchLabel),
        sizeof(statm::Synchronized),
        sizeof(statm::Throw),
        sizeof(statm::Try),
        sizeof(statm::While),
        sizeof(struc::AnnotatedElement),
        sizeof(struc::AnnotationType),
        sizeof(struc::AnnotationTypeElement),
        sizeof(struc::AnonymousClass),
        sizeof(struc::Class),
        sizeof(struc::ClassDeclaration),
        sizeof(struc::ClassGeneric),
        sizeof(struc::CompilationUnit),
        sizeof(struc::Declaration),
        sizeof(struc::Enum),
        sizeof(struc::EnumConstant),
        sizeof(struc::GenericDeclaration),
        sizeof(struc::Import),
        sizeof(struc::InitializerBlock),
        sizeof(struc::InstanceInitializerBlock),
        sizeof(struc::Interface),
        sizeof(struc::InterfaceDeclaration),
        sizeof(struc::InterfaceGeneric),
        sizeof(struc::Member),
        sizeof(struc::Method),
        sizeof(struc::MethodDeclaration),
        sizeof(struc::MethodGeneric),
        sizeof(struc::NamedDeclaration),
        sizeof(struc::NormalMethod),
        sizeof(struc::Package),
        sizeof(struc::PackageDeclaration),
        sizeof(struc::Parameter),
        sizeof(struc::Scope),
        sizeof(struc::StaticInitializerBlock),
        sizeof(struc::TypeDeclaration),
        sizeof(struc::TypeParameter),
        sizeof(struc::Variable),
        sizeof(struc::VariableDeclaration),
        sizeof(type::ArrayType),
        sizeof(type::BooleanType),
        sizeof(type::BoundedWildcardType),
        sizeof(type::ByteType),
        sizeof(type::CharType),
        sizeof(type::ClassType),
        sizeof(type::DoubleType),
        sizeof(type::ErrorType),
        sizeof(type::FloatType),
        sizeof(type::IntType),
        sizeof(type::LongType),
        sizeof(type::LowerBoundedWildcardType),
        sizeof(type::MethodType),
        sizeof(type::NoType),
        sizeof(type::NullType),
        sizeof(type::PackageType),
        sizeof(type::ParameterizedType),
        sizeof(type::PrimitiveType),
        sizeof(type::ScopedType),
        sizeof(type::ShortType),
        sizeof(type::Type),
        sizeof(type::TypeVariable),
        sizeof(type::UnboundedWildcardType),
        sizeof(type::UnionType),
        sizeof(type::UpperBoundedWildcardType),
        sizeof(type::VoidType),
        sizeof(type::WildcardType),
};

  VisitorAsgStat::VisitorAsgStat() : VisitorAbstractNodes() {
    for (int i = 0; i < 141; ++i)
      nodeStatSimple[i] = 0;

    for (int i = 0; i < 141; ++i)
      nodeStatParent[i] = 0;

    for (int i = 0; i < 105; ++i)
      edgeStat[i] = 0;

  }

  VisitorAsgStat::~VisitorAsgStat() {
  }

  void VisitorAsgStat::visit(const base::Base& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkBase];
    if (node.getNodeKind() == ndkBase)
      ++nodeStatSimple[ndkBase];
  }

  void VisitorAsgStat::visit(const base::BlockComment& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkBlockComment];
    if (node.getNodeKind() == ndkBlockComment)
      ++nodeStatSimple[ndkBlockComment];
  }

  void VisitorAsgStat::visit(const base::Comment& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkComment];
    if (node.getNodeKind() == ndkComment)
      ++nodeStatSimple[ndkComment];
  }

  void VisitorAsgStat::visit(const base::Commentable& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkCommentable];
    if (node.getNodeKind() == ndkCommentable)
      ++nodeStatSimple[ndkCommentable];
  }

  void VisitorAsgStat::visit(const base::JavadocComment& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkJavadocComment];
    if (node.getNodeKind() == ndkJavadocComment)
      ++nodeStatSimple[ndkJavadocComment];
  }

  void VisitorAsgStat::visit(const base::LineComment& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkLineComment];
    if (node.getNodeKind() == ndkLineComment)
      ++nodeStatSimple[ndkLineComment];
  }

  void VisitorAsgStat::visit(const base::Named& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkNamed];
    if (node.getNodeKind() == ndkNamed)
      ++nodeStatSimple[ndkNamed];
  }

  void VisitorAsgStat::visit(const base::NonJavadocComment& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkNonJavadocComment];
    if (node.getNodeKind() == ndkNonJavadocComment)
      ++nodeStatSimple[ndkNonJavadocComment];
  }

  void VisitorAsgStat::visit(const base::Positioned& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkPositioned];
    if (node.getNodeKind() == ndkPositioned)
      ++nodeStatSimple[ndkPositioned];
  }

  void VisitorAsgStat::visit(const base::PositionedWithoutComment& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkPositionedWithoutComment];
    if (node.getNodeKind() == ndkPositionedWithoutComment)
      ++nodeStatSimple[ndkPositionedWithoutComment];
  }

  void VisitorAsgStat::visit(const expr::Annotation& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkAnnotation];
    if (node.getNodeKind() == ndkAnnotation)
      ++nodeStatSimple[ndkAnnotation];
  }

  void VisitorAsgStat::visit(const expr::ArrayAccess& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkArrayAccess];
    if (node.getNodeKind() == ndkArrayAccess)
      ++nodeStatSimple[ndkArrayAccess];
  }

  void VisitorAsgStat::visit(const expr::ArrayTypeExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkArrayTypeExpression];
    if (node.getNodeKind() == ndkArrayTypeExpression)
      ++nodeStatSimple[ndkArrayTypeExpression];
  }

  void VisitorAsgStat::visit(const expr::Assignment& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkAssignment];
    if (node.getNodeKind() == ndkAssignment)
      ++nodeStatSimple[ndkAssignment];
  }

  void VisitorAsgStat::visit(const expr::Binary& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkBinary];
    if (node.getNodeKind() == ndkBinary)
      ++nodeStatSimple[ndkBinary];
  }

  void VisitorAsgStat::visit(const expr::BooleanLiteral& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkBooleanLiteral];
    if (node.getNodeKind() == ndkBooleanLiteral)
      ++nodeStatSimple[ndkBooleanLiteral];
  }

  void VisitorAsgStat::visit(const expr::CharacterLiteral& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkCharacterLiteral];
    if (node.getNodeKind() == ndkCharacterLiteral)
      ++nodeStatSimple[ndkCharacterLiteral];
  }

  void VisitorAsgStat::visit(const expr::ClassLiteral& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkClassLiteral];
    if (node.getNodeKind() == ndkClassLiteral)
      ++nodeStatSimple[ndkClassLiteral];
  }

  void VisitorAsgStat::visit(const expr::Conditional& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkConditional];
    if (node.getNodeKind() == ndkConditional)
      ++nodeStatSimple[ndkConditional];
  }

  void VisitorAsgStat::visit(const expr::DoubleLiteral& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkDoubleLiteral];
    if (node.getNodeKind() == ndkDoubleLiteral)
      ++nodeStatSimple[ndkDoubleLiteral];
  }

  void VisitorAsgStat::visit(const expr::Erroneous& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkErroneous];
    if (node.getNodeKind() == ndkErroneous)
      ++nodeStatSimple[ndkErroneous];
  }

  void VisitorAsgStat::visit(const expr::ErroneousTypeExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkErroneousTypeExpression];
    if (node.getNodeKind() == ndkErroneousTypeExpression)
      ++nodeStatSimple[ndkErroneousTypeExpression];
  }

  void VisitorAsgStat::visit(const expr::Expression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkExpression];
    if (node.getNodeKind() == ndkExpression)
      ++nodeStatSimple[ndkExpression];
  }

  void VisitorAsgStat::visit(const expr::ExternalTypeExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkExternalTypeExpression];
    if (node.getNodeKind() == ndkExternalTypeExpression)
      ++nodeStatSimple[ndkExternalTypeExpression];
  }

  void VisitorAsgStat::visit(const expr::FieldAccess& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkFieldAccess];
    if (node.getNodeKind() == ndkFieldAccess)
      ++nodeStatSimple[ndkFieldAccess];
  }

  void VisitorAsgStat::visit(const expr::FloatLiteral& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkFloatLiteral];
    if (node.getNodeKind() == ndkFloatLiteral)
      ++nodeStatSimple[ndkFloatLiteral];
  }

  void VisitorAsgStat::visit(const expr::Identifier& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkIdentifier];
    if (node.getNodeKind() == ndkIdentifier)
      ++nodeStatSimple[ndkIdentifier];
  }

  void VisitorAsgStat::visit(const expr::InfixExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkInfixExpression];
    if (node.getNodeKind() == ndkInfixExpression)
      ++nodeStatSimple[ndkInfixExpression];
  }

  void VisitorAsgStat::visit(const expr::InstanceOf& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkInstanceOf];
    if (node.getNodeKind() == ndkInstanceOf)
      ++nodeStatSimple[ndkInstanceOf];
  }

  void VisitorAsgStat::visit(const expr::IntegerLiteral& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkIntegerLiteral];
    if (node.getNodeKind() == ndkIntegerLiteral)
      ++nodeStatSimple[ndkIntegerLiteral];
  }

  void VisitorAsgStat::visit(const expr::Literal& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkLiteral];
    if (node.getNodeKind() == ndkLiteral)
      ++nodeStatSimple[ndkLiteral];
  }

  void VisitorAsgStat::visit(const expr::LongLiteral& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkLongLiteral];
    if (node.getNodeKind() == ndkLongLiteral)
      ++nodeStatSimple[ndkLongLiteral];
  }

  void VisitorAsgStat::visit(const expr::MarkerAnnotation& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkMarkerAnnotation];
    if (node.getNodeKind() == ndkMarkerAnnotation)
      ++nodeStatSimple[ndkMarkerAnnotation];
  }

  void VisitorAsgStat::visit(const expr::MethodInvocation& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkMethodInvocation];
    if (node.getNodeKind() == ndkMethodInvocation)
      ++nodeStatSimple[ndkMethodInvocation];
  }

  void VisitorAsgStat::visit(const expr::NewArray& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkNewArray];
    if (node.getNodeKind() == ndkNewArray)
      ++nodeStatSimple[ndkNewArray];
  }

  void VisitorAsgStat::visit(const expr::NewClass& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkNewClass];
    if (node.getNodeKind() == ndkNewClass)
      ++nodeStatSimple[ndkNewClass];
  }

  void VisitorAsgStat::visit(const expr::NormalAnnotation& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkNormalAnnotation];
    if (node.getNodeKind() == ndkNormalAnnotation)
      ++nodeStatSimple[ndkNormalAnnotation];
  }

  void VisitorAsgStat::visit(const expr::NullLiteral& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkNullLiteral];
    if (node.getNodeKind() == ndkNullLiteral)
      ++nodeStatSimple[ndkNullLiteral];
  }

  void VisitorAsgStat::visit(const expr::NumberLiteral& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkNumberLiteral];
    if (node.getNodeKind() == ndkNumberLiteral)
      ++nodeStatSimple[ndkNumberLiteral];
  }

  void VisitorAsgStat::visit(const expr::ParenthesizedExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkParenthesizedExpression];
    if (node.getNodeKind() == ndkParenthesizedExpression)
      ++nodeStatSimple[ndkParenthesizedExpression];
  }

  void VisitorAsgStat::visit(const expr::PostfixExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkPostfixExpression];
    if (node.getNodeKind() == ndkPostfixExpression)
      ++nodeStatSimple[ndkPostfixExpression];
  }

  void VisitorAsgStat::visit(const expr::PrefixExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkPrefixExpression];
    if (node.getNodeKind() == ndkPrefixExpression)
      ++nodeStatSimple[ndkPrefixExpression];
  }

  void VisitorAsgStat::visit(const expr::PrimitiveTypeExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkPrimitiveTypeExpression];
    if (node.getNodeKind() == ndkPrimitiveTypeExpression)
      ++nodeStatSimple[ndkPrimitiveTypeExpression];
  }

  void VisitorAsgStat::visit(const expr::QualifiedTypeExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkQualifiedTypeExpression];
    if (node.getNodeKind() == ndkQualifiedTypeExpression)
      ++nodeStatSimple[ndkQualifiedTypeExpression];
  }

  void VisitorAsgStat::visit(const expr::SimpleTypeExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkSimpleTypeExpression];
    if (node.getNodeKind() == ndkSimpleTypeExpression)
      ++nodeStatSimple[ndkSimpleTypeExpression];
  }

  void VisitorAsgStat::visit(const expr::SingleElementAnnotation& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkSingleElementAnnotation];
    if (node.getNodeKind() == ndkSingleElementAnnotation)
      ++nodeStatSimple[ndkSingleElementAnnotation];
  }

  void VisitorAsgStat::visit(const expr::StringLiteral& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkStringLiteral];
    if (node.getNodeKind() == ndkStringLiteral)
      ++nodeStatSimple[ndkStringLiteral];
  }

  void VisitorAsgStat::visit(const expr::Super& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkSuper];
    if (node.getNodeKind() == ndkSuper)
      ++nodeStatSimple[ndkSuper];
  }

  void VisitorAsgStat::visit(const expr::This& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkThis];
    if (node.getNodeKind() == ndkThis)
      ++nodeStatSimple[ndkThis];
  }

  void VisitorAsgStat::visit(const expr::TypeApplyExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkTypeApplyExpression];
    if (node.getNodeKind() == ndkTypeApplyExpression)
      ++nodeStatSimple[ndkTypeApplyExpression];
  }

  void VisitorAsgStat::visit(const expr::TypeCast& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkTypeCast];
    if (node.getNodeKind() == ndkTypeCast)
      ++nodeStatSimple[ndkTypeCast];
  }

  void VisitorAsgStat::visit(const expr::TypeExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkTypeExpression];
    if (node.getNodeKind() == ndkTypeExpression)
      ++nodeStatSimple[ndkTypeExpression];
  }

  void VisitorAsgStat::visit(const expr::TypeUnionExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkTypeUnionExpression];
    if (node.getNodeKind() == ndkTypeUnionExpression)
      ++nodeStatSimple[ndkTypeUnionExpression];
  }

  void VisitorAsgStat::visit(const expr::Unary& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkUnary];
    if (node.getNodeKind() == ndkUnary)
      ++nodeStatSimple[ndkUnary];
  }

  void VisitorAsgStat::visit(const expr::WildcardExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkWildcardExpression];
    if (node.getNodeKind() == ndkWildcardExpression)
      ++nodeStatSimple[ndkWildcardExpression];
  }

  void VisitorAsgStat::visit(const statm::Assert& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkAssert];
    if (node.getNodeKind() == ndkAssert)
      ++nodeStatSimple[ndkAssert];
  }

  void VisitorAsgStat::visit(const statm::BasicFor& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkBasicFor];
    if (node.getNodeKind() == ndkBasicFor)
      ++nodeStatSimple[ndkBasicFor];
  }

  void VisitorAsgStat::visit(const statm::Block& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkBlock];
    if (node.getNodeKind() == ndkBlock)
      ++nodeStatSimple[ndkBlock];
  }

  void VisitorAsgStat::visit(const statm::Break& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkBreak];
    if (node.getNodeKind() == ndkBreak)
      ++nodeStatSimple[ndkBreak];
  }

  void VisitorAsgStat::visit(const statm::Case& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkCase];
    if (node.getNodeKind() == ndkCase)
      ++nodeStatSimple[ndkCase];
  }

  void VisitorAsgStat::visit(const statm::Continue& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkContinue];
    if (node.getNodeKind() == ndkContinue)
      ++nodeStatSimple[ndkContinue];
  }

  void VisitorAsgStat::visit(const statm::Default& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkDefault];
    if (node.getNodeKind() == ndkDefault)
      ++nodeStatSimple[ndkDefault];
  }

  void VisitorAsgStat::visit(const statm::Do& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkDo];
    if (node.getNodeKind() == ndkDo)
      ++nodeStatSimple[ndkDo];
  }

  void VisitorAsgStat::visit(const statm::Empty& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkEmpty];
    if (node.getNodeKind() == ndkEmpty)
      ++nodeStatSimple[ndkEmpty];
  }

  void VisitorAsgStat::visit(const statm::EnhancedFor& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkEnhancedFor];
    if (node.getNodeKind() == ndkEnhancedFor)
      ++nodeStatSimple[ndkEnhancedFor];
  }

  void VisitorAsgStat::visit(const statm::ExpressionStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkExpressionStatement];
    if (node.getNodeKind() == ndkExpressionStatement)
      ++nodeStatSimple[ndkExpressionStatement];
  }

  void VisitorAsgStat::visit(const statm::For& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkFor];
    if (node.getNodeKind() == ndkFor)
      ++nodeStatSimple[ndkFor];
  }

  void VisitorAsgStat::visit(const statm::Handler& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkHandler];
    if (node.getNodeKind() == ndkHandler)
      ++nodeStatSimple[ndkHandler];
  }

  void VisitorAsgStat::visit(const statm::If& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkIf];
    if (node.getNodeKind() == ndkIf)
      ++nodeStatSimple[ndkIf];
  }

  void VisitorAsgStat::visit(const statm::Iteration& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkIteration];
    if (node.getNodeKind() == ndkIteration)
      ++nodeStatSimple[ndkIteration];
  }

  void VisitorAsgStat::visit(const statm::Jump& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkJump];
    if (node.getNodeKind() == ndkJump)
      ++nodeStatSimple[ndkJump];
  }

  void VisitorAsgStat::visit(const statm::LabeledStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkLabeledStatement];
    if (node.getNodeKind() == ndkLabeledStatement)
      ++nodeStatSimple[ndkLabeledStatement];
  }

  void VisitorAsgStat::visit(const statm::Return& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkReturn];
    if (node.getNodeKind() == ndkReturn)
      ++nodeStatSimple[ndkReturn];
  }

  void VisitorAsgStat::visit(const statm::Selection& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkSelection];
    if (node.getNodeKind() == ndkSelection)
      ++nodeStatSimple[ndkSelection];
  }

  void VisitorAsgStat::visit(const statm::Statement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkStatement];
    if (node.getNodeKind() == ndkStatement)
      ++nodeStatSimple[ndkStatement];
  }

  void VisitorAsgStat::visit(const statm::Switch& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkSwitch];
    if (node.getNodeKind() == ndkSwitch)
      ++nodeStatSimple[ndkSwitch];
  }

  void VisitorAsgStat::visit(const statm::SwitchLabel& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkSwitchLabel];
    if (node.getNodeKind() == ndkSwitchLabel)
      ++nodeStatSimple[ndkSwitchLabel];
  }

  void VisitorAsgStat::visit(const statm::Synchronized& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkSynchronized];
    if (node.getNodeKind() == ndkSynchronized)
      ++nodeStatSimple[ndkSynchronized];
  }

  void VisitorAsgStat::visit(const statm::Throw& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkThrow];
    if (node.getNodeKind() == ndkThrow)
      ++nodeStatSimple[ndkThrow];
  }

  void VisitorAsgStat::visit(const statm::Try& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkTry];
    if (node.getNodeKind() == ndkTry)
      ++nodeStatSimple[ndkTry];
  }

  void VisitorAsgStat::visit(const statm::While& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkWhile];
    if (node.getNodeKind() == ndkWhile)
      ++nodeStatSimple[ndkWhile];
  }

  void VisitorAsgStat::visit(const struc::AnnotatedElement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkAnnotatedElement];
    if (node.getNodeKind() == ndkAnnotatedElement)
      ++nodeStatSimple[ndkAnnotatedElement];
  }

  void VisitorAsgStat::visit(const struc::AnnotationType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkAnnotationType];
    if (node.getNodeKind() == ndkAnnotationType)
      ++nodeStatSimple[ndkAnnotationType];
  }

  void VisitorAsgStat::visit(const struc::AnnotationTypeElement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkAnnotationTypeElement];
    if (node.getNodeKind() == ndkAnnotationTypeElement)
      ++nodeStatSimple[ndkAnnotationTypeElement];
  }

  void VisitorAsgStat::visit(const struc::AnonymousClass& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkAnonymousClass];
    if (node.getNodeKind() == ndkAnonymousClass)
      ++nodeStatSimple[ndkAnonymousClass];
  }

  void VisitorAsgStat::visit(const struc::Class& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkClass];
    if (node.getNodeKind() == ndkClass)
      ++nodeStatSimple[ndkClass];
  }

  void VisitorAsgStat::visit(const struc::ClassDeclaration& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkClassDeclaration];
    if (node.getNodeKind() == ndkClassDeclaration)
      ++nodeStatSimple[ndkClassDeclaration];
  }

  void VisitorAsgStat::visit(const struc::ClassGeneric& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkClassGeneric];
    if (node.getNodeKind() == ndkClassGeneric)
      ++nodeStatSimple[ndkClassGeneric];
  }

  void VisitorAsgStat::visit(const struc::CompilationUnit& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkCompilationUnit];
    if (node.getNodeKind() == ndkCompilationUnit)
      ++nodeStatSimple[ndkCompilationUnit];
  }

  void VisitorAsgStat::visit(const struc::Declaration& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkDeclaration];
    if (node.getNodeKind() == ndkDeclaration)
      ++nodeStatSimple[ndkDeclaration];
  }

  void VisitorAsgStat::visit(const struc::Enum& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkEnum];
    if (node.getNodeKind() == ndkEnum)
      ++nodeStatSimple[ndkEnum];
  }

  void VisitorAsgStat::visit(const struc::EnumConstant& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkEnumConstant];
    if (node.getNodeKind() == ndkEnumConstant)
      ++nodeStatSimple[ndkEnumConstant];
  }

  void VisitorAsgStat::visit(const struc::GenericDeclaration& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkGenericDeclaration];
    if (node.getNodeKind() == ndkGenericDeclaration)
      ++nodeStatSimple[ndkGenericDeclaration];
  }

  void VisitorAsgStat::visit(const struc::Import& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkImport];
    if (node.getNodeKind() == ndkImport)
      ++nodeStatSimple[ndkImport];
  }

  void VisitorAsgStat::visit(const struc::InitializerBlock& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkInitializerBlock];
    if (node.getNodeKind() == ndkInitializerBlock)
      ++nodeStatSimple[ndkInitializerBlock];
  }

  void VisitorAsgStat::visit(const struc::InstanceInitializerBlock& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkInstanceInitializerBlock];
    if (node.getNodeKind() == ndkInstanceInitializerBlock)
      ++nodeStatSimple[ndkInstanceInitializerBlock];
  }

  void VisitorAsgStat::visit(const struc::Interface& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkInterface];
    if (node.getNodeKind() == ndkInterface)
      ++nodeStatSimple[ndkInterface];
  }

  void VisitorAsgStat::visit(const struc::InterfaceDeclaration& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkInterfaceDeclaration];
    if (node.getNodeKind() == ndkInterfaceDeclaration)
      ++nodeStatSimple[ndkInterfaceDeclaration];
  }

  void VisitorAsgStat::visit(const struc::InterfaceGeneric& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkInterfaceGeneric];
    if (node.getNodeKind() == ndkInterfaceGeneric)
      ++nodeStatSimple[ndkInterfaceGeneric];
  }

  void VisitorAsgStat::visit(const struc::Member& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkMember];
    if (node.getNodeKind() == ndkMember)
      ++nodeStatSimple[ndkMember];
  }

  void VisitorAsgStat::visit(const struc::Method& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkMethod];
    if (node.getNodeKind() == ndkMethod)
      ++nodeStatSimple[ndkMethod];
  }

  void VisitorAsgStat::visit(const struc::MethodDeclaration& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkMethodDeclaration];
    if (node.getNodeKind() == ndkMethodDeclaration)
      ++nodeStatSimple[ndkMethodDeclaration];
  }

  void VisitorAsgStat::visit(const struc::MethodGeneric& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkMethodGeneric];
    if (node.getNodeKind() == ndkMethodGeneric)
      ++nodeStatSimple[ndkMethodGeneric];
  }

  void VisitorAsgStat::visit(const struc::NamedDeclaration& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkNamedDeclaration];
    if (node.getNodeKind() == ndkNamedDeclaration)
      ++nodeStatSimple[ndkNamedDeclaration];
  }

  void VisitorAsgStat::visit(const struc::NormalMethod& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkNormalMethod];
    if (node.getNodeKind() == ndkNormalMethod)
      ++nodeStatSimple[ndkNormalMethod];
  }

  void VisitorAsgStat::visit(const struc::Package& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkPackage];
    if (node.getNodeKind() == ndkPackage)
      ++nodeStatSimple[ndkPackage];
  }

  void VisitorAsgStat::visit(const struc::PackageDeclaration& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkPackageDeclaration];
    if (node.getNodeKind() == ndkPackageDeclaration)
      ++nodeStatSimple[ndkPackageDeclaration];
  }

  void VisitorAsgStat::visit(const struc::Parameter& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkParameter];
    if (node.getNodeKind() == ndkParameter)
      ++nodeStatSimple[ndkParameter];
  }

  void VisitorAsgStat::visit(const struc::Scope& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkScope];
    if (node.getNodeKind() == ndkScope)
      ++nodeStatSimple[ndkScope];
  }

  void VisitorAsgStat::visit(const struc::StaticInitializerBlock& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkStaticInitializerBlock];
    if (node.getNodeKind() == ndkStaticInitializerBlock)
      ++nodeStatSimple[ndkStaticInitializerBlock];
  }

  void VisitorAsgStat::visit(const struc::TypeDeclaration& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkTypeDeclaration];
    if (node.getNodeKind() == ndkTypeDeclaration)
      ++nodeStatSimple[ndkTypeDeclaration];
  }

  void VisitorAsgStat::visit(const struc::TypeParameter& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkTypeParameter];
    if (node.getNodeKind() == ndkTypeParameter)
      ++nodeStatSimple[ndkTypeParameter];
  }

  void VisitorAsgStat::visit(const struc::Variable& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkVariable];
    if (node.getNodeKind() == ndkVariable)
      ++nodeStatSimple[ndkVariable];
  }

  void VisitorAsgStat::visit(const struc::VariableDeclaration& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkVariableDeclaration];
    if (node.getNodeKind() == ndkVariableDeclaration)
      ++nodeStatSimple[ndkVariableDeclaration];
  }

  void VisitorAsgStat::visit(const type::ArrayType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkArrayType];
    if (node.getNodeKind() == ndkArrayType)
      ++nodeStatSimple[ndkArrayType];
  }

  void VisitorAsgStat::visit(const type::BooleanType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkBooleanType];
    if (node.getNodeKind() == ndkBooleanType)
      ++nodeStatSimple[ndkBooleanType];
  }

  void VisitorAsgStat::visit(const type::BoundedWildcardType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkBoundedWildcardType];
    if (node.getNodeKind() == ndkBoundedWildcardType)
      ++nodeStatSimple[ndkBoundedWildcardType];
  }

  void VisitorAsgStat::visit(const type::ByteType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkByteType];
    if (node.getNodeKind() == ndkByteType)
      ++nodeStatSimple[ndkByteType];
  }

  void VisitorAsgStat::visit(const type::CharType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkCharType];
    if (node.getNodeKind() == ndkCharType)
      ++nodeStatSimple[ndkCharType];
  }

  void VisitorAsgStat::visit(const type::ClassType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkClassType];
    if (node.getNodeKind() == ndkClassType)
      ++nodeStatSimple[ndkClassType];
  }

  void VisitorAsgStat::visit(const type::DoubleType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkDoubleType];
    if (node.getNodeKind() == ndkDoubleType)
      ++nodeStatSimple[ndkDoubleType];
  }

  void VisitorAsgStat::visit(const type::ErrorType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkErrorType];
    if (node.getNodeKind() == ndkErrorType)
      ++nodeStatSimple[ndkErrorType];
  }

  void VisitorAsgStat::visit(const type::FloatType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkFloatType];
    if (node.getNodeKind() == ndkFloatType)
      ++nodeStatSimple[ndkFloatType];
  }

  void VisitorAsgStat::visit(const type::IntType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkIntType];
    if (node.getNodeKind() == ndkIntType)
      ++nodeStatSimple[ndkIntType];
  }

  void VisitorAsgStat::visit(const type::LongType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkLongType];
    if (node.getNodeKind() == ndkLongType)
      ++nodeStatSimple[ndkLongType];
  }

  void VisitorAsgStat::visit(const type::LowerBoundedWildcardType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkLowerBoundedWildcardType];
    if (node.getNodeKind() == ndkLowerBoundedWildcardType)
      ++nodeStatSimple[ndkLowerBoundedWildcardType];
  }

  void VisitorAsgStat::visit(const type::MethodType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkMethodType];
    if (node.getNodeKind() == ndkMethodType)
      ++nodeStatSimple[ndkMethodType];
  }

  void VisitorAsgStat::visit(const type::NoType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkNoType];
    if (node.getNodeKind() == ndkNoType)
      ++nodeStatSimple[ndkNoType];
  }

  void VisitorAsgStat::visit(const type::NullType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkNullType];
    if (node.getNodeKind() == ndkNullType)
      ++nodeStatSimple[ndkNullType];
  }

  void VisitorAsgStat::visit(const type::PackageType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkPackageType];
    if (node.getNodeKind() == ndkPackageType)
      ++nodeStatSimple[ndkPackageType];
  }

  void VisitorAsgStat::visit(const type::ParameterizedType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkParameterizedType];
    if (node.getNodeKind() == ndkParameterizedType)
      ++nodeStatSimple[ndkParameterizedType];
  }

  void VisitorAsgStat::visit(const type::PrimitiveType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkPrimitiveType];
    if (node.getNodeKind() == ndkPrimitiveType)
      ++nodeStatSimple[ndkPrimitiveType];
  }

  void VisitorAsgStat::visit(const type::ScopedType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkScopedType];
    if (node.getNodeKind() == ndkScopedType)
      ++nodeStatSimple[ndkScopedType];
  }

  void VisitorAsgStat::visit(const type::ShortType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkShortType];
    if (node.getNodeKind() == ndkShortType)
      ++nodeStatSimple[ndkShortType];
  }

  void VisitorAsgStat::visit(const type::Type& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkType];
    if (node.getNodeKind() == ndkType)
      ++nodeStatSimple[ndkType];
  }

  void VisitorAsgStat::visit(const type::TypeVariable& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkTypeVariable];
    if (node.getNodeKind() == ndkTypeVariable)
      ++nodeStatSimple[ndkTypeVariable];
  }

  void VisitorAsgStat::visit(const type::UnboundedWildcardType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkUnboundedWildcardType];
    if (node.getNodeKind() == ndkUnboundedWildcardType)
      ++nodeStatSimple[ndkUnboundedWildcardType];
  }

  void VisitorAsgStat::visit(const type::UnionType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkUnionType];
    if (node.getNodeKind() == ndkUnionType)
      ++nodeStatSimple[ndkUnionType];
  }

  void VisitorAsgStat::visit(const type::UpperBoundedWildcardType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkUpperBoundedWildcardType];
    if (node.getNodeKind() == ndkUpperBoundedWildcardType)
      ++nodeStatSimple[ndkUpperBoundedWildcardType];
  }

  void VisitorAsgStat::visit(const type::VoidType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkVoidType];
    if (node.getNodeKind() == ndkVoidType)
      ++nodeStatSimple[ndkVoidType];
  }

  void VisitorAsgStat::visit(const type::WildcardType& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkWildcardType];
    if (node.getNodeKind() == ndkWildcardType)
      ++nodeStatSimple[ndkWildcardType];
  }

  void VisitorAsgStat::visitCommentable_Comments(const base::Commentable& begin, const base::Comment& end) {
    ++edgeStat[edkCommentable_Comments];
  }

  void VisitorAsgStat::visitAnnotation_HasAnnotationName(const expr::Annotation& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkAnnotation_HasAnnotationName];
  }

  void VisitorAsgStat::visitArrayTypeExpression_HasComponentType(const expr::ArrayTypeExpression& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkArrayTypeExpression_HasComponentType];
  }

  void VisitorAsgStat::visitBinary_HasLeftOperand(const expr::Binary& begin, const expr::Expression& end) {
    ++edgeStat[edkBinary_HasLeftOperand];
  }

  void VisitorAsgStat::visitBinary_HasRightOperand(const expr::Binary& begin, const expr::Expression& end) {
    ++edgeStat[edkBinary_HasRightOperand];
  }

  void VisitorAsgStat::visitClassLiteral_HasComponentType(const expr::ClassLiteral& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkClassLiteral_HasComponentType];
  }

  void VisitorAsgStat::visitConditional_HasCondition(const expr::Conditional& begin, const expr::Expression& end) {
    ++edgeStat[edkConditional_HasCondition];
  }

  void VisitorAsgStat::visitConditional_HasTrueExpression(const expr::Conditional& begin, const expr::Expression& end) {
    ++edgeStat[edkConditional_HasTrueExpression];
  }

  void VisitorAsgStat::visitConditional_HasFalseExpression(const expr::Conditional& begin, const expr::Expression& end) {
    ++edgeStat[edkConditional_HasFalseExpression];
  }

  void VisitorAsgStat::visitErroneous_HasErrors(const expr::Erroneous& begin, const base::Positioned& end) {
    ++edgeStat[edkErroneous_HasErrors];
  }

  void VisitorAsgStat::visitErroneousTypeExpression_HasErrors(const expr::ErroneousTypeExpression& begin, const base::Positioned& end) {
    ++edgeStat[edkErroneousTypeExpression_HasErrors];
  }

  void VisitorAsgStat::visitExpression_Type(const expr::Expression& begin, const type::Type& end) {
    ++edgeStat[edkExpression_Type];
  }

  void VisitorAsgStat::visitIdentifier_RefersTo(const expr::Identifier& begin, const base::Named& end) {
    ++edgeStat[edkIdentifier_RefersTo];
  }

  void VisitorAsgStat::visitInstanceOf_HasTypeOperand(const expr::InstanceOf& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkInstanceOf_HasTypeOperand];
  }

  void VisitorAsgStat::visitMethodInvocation_HasTypeArguments(const expr::MethodInvocation& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkMethodInvocation_HasTypeArguments];
  }

  void VisitorAsgStat::visitMethodInvocation_HasArguments(const expr::MethodInvocation& begin, const expr::Expression& end) {
    ++edgeStat[edkMethodInvocation_HasArguments];
  }

  void VisitorAsgStat::visitMethodInvocation_Invokes(const expr::MethodInvocation& begin, const struc::MethodDeclaration& end) {
    ++edgeStat[edkMethodInvocation_Invokes];
  }

  void VisitorAsgStat::visitNewArray_HasComponentType(const expr::NewArray& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkNewArray_HasComponentType];
  }

  void VisitorAsgStat::visitNewArray_HasDimensions(const expr::NewArray& begin, const expr::Expression& end) {
    ++edgeStat[edkNewArray_HasDimensions];
  }

  void VisitorAsgStat::visitNewArray_HasInitializers(const expr::NewArray& begin, const expr::Expression& end) {
    ++edgeStat[edkNewArray_HasInitializers];
  }

  void VisitorAsgStat::visitNewClass_HasEnclosingExpression(const expr::NewClass& begin, const expr::Expression& end) {
    ++edgeStat[edkNewClass_HasEnclosingExpression];
  }

  void VisitorAsgStat::visitNewClass_HasTypeArguments(const expr::NewClass& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkNewClass_HasTypeArguments];
  }

  void VisitorAsgStat::visitNewClass_HasTypeName(const expr::NewClass& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkNewClass_HasTypeName];
  }

  void VisitorAsgStat::visitNewClass_HasArguments(const expr::NewClass& begin, const expr::Expression& end) {
    ++edgeStat[edkNewClass_HasArguments];
  }

  void VisitorAsgStat::visitNewClass_HasAnonymousClass(const expr::NewClass& begin, const struc::AnonymousClass& end) {
    ++edgeStat[edkNewClass_HasAnonymousClass];
  }

  void VisitorAsgStat::visitNewClass_Constructor(const expr::NewClass& begin, const struc::NormalMethod& end) {
    ++edgeStat[edkNewClass_Constructor];
  }

  void VisitorAsgStat::visitNormalAnnotation_HasArguments(const expr::NormalAnnotation& begin, const expr::Expression& end) {
    ++edgeStat[edkNormalAnnotation_HasArguments];
  }

  void VisitorAsgStat::visitQualifiedTypeExpression_HasQualifierType(const expr::QualifiedTypeExpression& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkQualifiedTypeExpression_HasQualifierType];
  }

  void VisitorAsgStat::visitQualifiedTypeExpression_HasSimpleType(const expr::QualifiedTypeExpression& begin, const expr::SimpleTypeExpression& end) {
    ++edgeStat[edkQualifiedTypeExpression_HasSimpleType];
  }

  void VisitorAsgStat::visitSingleElementAnnotation_HasArgument(const expr::SingleElementAnnotation& begin, const expr::Expression& end) {
    ++edgeStat[edkSingleElementAnnotation_HasArgument];
  }

  void VisitorAsgStat::visitTypeApplyExpression_HasRawType(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkTypeApplyExpression_HasRawType];
  }

  void VisitorAsgStat::visitTypeApplyExpression_HasTypeArguments(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkTypeApplyExpression_HasTypeArguments];
  }

  void VisitorAsgStat::visitTypeCast_HasTypeOperand(const expr::TypeCast& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkTypeCast_HasTypeOperand];
  }

  void VisitorAsgStat::visitTypeUnionExpression_HasAlternatives(const expr::TypeUnionExpression& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkTypeUnionExpression_HasAlternatives];
  }

  void VisitorAsgStat::visitUnary_HasOperand(const expr::Unary& begin, const expr::Expression& end) {
    ++edgeStat[edkUnary_HasOperand];
  }

  void VisitorAsgStat::visitWildcardExpression_HasBound(const expr::WildcardExpression& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkWildcardExpression_HasBound];
  }

  void VisitorAsgStat::visitAssert_HasCondition(const statm::Assert& begin, const expr::Expression& end) {
    ++edgeStat[edkAssert_HasCondition];
  }

  void VisitorAsgStat::visitAssert_HasDetail(const statm::Assert& begin, const expr::Expression& end) {
    ++edgeStat[edkAssert_HasDetail];
  }

  void VisitorAsgStat::visitBasicFor_HasInitializers(const statm::BasicFor& begin, const statm::Statement& end) {
    ++edgeStat[edkBasicFor_HasInitializers];
  }

  void VisitorAsgStat::visitBasicFor_HasCondition(const statm::BasicFor& begin, const expr::Expression& end) {
    ++edgeStat[edkBasicFor_HasCondition];
  }

  void VisitorAsgStat::visitBasicFor_HasUpdates(const statm::BasicFor& begin, const statm::Statement& end) {
    ++edgeStat[edkBasicFor_HasUpdates];
  }

  void VisitorAsgStat::visitBlock_HasStatements(const statm::Block& begin, const statm::Statement& end) {
    ++edgeStat[edkBlock_HasStatements];
  }

  void VisitorAsgStat::visitCase_HasExpression(const statm::Case& begin, const expr::Expression& end) {
    ++edgeStat[edkCase_HasExpression];
  }

  void VisitorAsgStat::visitDo_HasCondition(const statm::Do& begin, const expr::Expression& end) {
    ++edgeStat[edkDo_HasCondition];
  }

  void VisitorAsgStat::visitEnhancedFor_HasParameter(const statm::EnhancedFor& begin, const struc::Parameter& end) {
    ++edgeStat[edkEnhancedFor_HasParameter];
  }

  void VisitorAsgStat::visitEnhancedFor_HasExpression(const statm::EnhancedFor& begin, const expr::Expression& end) {
    ++edgeStat[edkEnhancedFor_HasExpression];
  }

  void VisitorAsgStat::visitExpressionStatement_HasExpression(const statm::ExpressionStatement& begin, const expr::Expression& end) {
    ++edgeStat[edkExpressionStatement_HasExpression];
  }

  void VisitorAsgStat::visitHandler_HasParameter(const statm::Handler& begin, const struc::Parameter& end) {
    ++edgeStat[edkHandler_HasParameter];
  }

  void VisitorAsgStat::visitHandler_HasBlock(const statm::Handler& begin, const statm::Block& end) {
    ++edgeStat[edkHandler_HasBlock];
  }

  void VisitorAsgStat::visitIf_HasSubstatement(const statm::If& begin, const statm::Statement& end) {
    ++edgeStat[edkIf_HasSubstatement];
  }

  void VisitorAsgStat::visitIf_HasFalseSubstatement(const statm::If& begin, const statm::Statement& end) {
    ++edgeStat[edkIf_HasFalseSubstatement];
  }

  void VisitorAsgStat::visitIteration_HasSubstatement(const statm::Iteration& begin, const statm::Statement& end) {
    ++edgeStat[edkIteration_HasSubstatement];
  }

  void VisitorAsgStat::visitJump_Target(const statm::Jump& begin, const statm::Statement& end) {
    ++edgeStat[edkJump_Target];
  }

  void VisitorAsgStat::visitLabeledStatement_HasStatement(const statm::LabeledStatement& begin, const statm::Statement& end) {
    ++edgeStat[edkLabeledStatement_HasStatement];
  }

  void VisitorAsgStat::visitReturn_HasExpression(const statm::Return& begin, const expr::Expression& end) {
    ++edgeStat[edkReturn_HasExpression];
  }

  void VisitorAsgStat::visitSelection_HasCondition(const statm::Selection& begin, const expr::Expression& end) {
    ++edgeStat[edkSelection_HasCondition];
  }

  void VisitorAsgStat::visitSwitch_HasCases(const statm::Switch& begin, const statm::SwitchLabel& end) {
    ++edgeStat[edkSwitch_HasCases];
  }

  void VisitorAsgStat::visitSwitchLabel_HasStatements(const statm::SwitchLabel& begin, const statm::Statement& end) {
    ++edgeStat[edkSwitchLabel_HasStatements];
  }

  void VisitorAsgStat::visitSynchronized_HasLock(const statm::Synchronized& begin, const expr::Expression& end) {
    ++edgeStat[edkSynchronized_HasLock];
  }

  void VisitorAsgStat::visitSynchronized_HasBlock(const statm::Synchronized& begin, const statm::Block& end) {
    ++edgeStat[edkSynchronized_HasBlock];
  }

  void VisitorAsgStat::visitThrow_HasExpression(const statm::Throw& begin, const expr::Expression& end) {
    ++edgeStat[edkThrow_HasExpression];
  }

  void VisitorAsgStat::visitTry_HasResources(const statm::Try& begin, const struc::Variable& end) {
    ++edgeStat[edkTry_HasResources];
  }

  void VisitorAsgStat::visitTry_HasBlock(const statm::Try& begin, const statm::Block& end) {
    ++edgeStat[edkTry_HasBlock];
  }

  void VisitorAsgStat::visitTry_HasHandlers(const statm::Try& begin, const statm::Handler& end) {
    ++edgeStat[edkTry_HasHandlers];
  }

  void VisitorAsgStat::visitTry_HasFinallyBlock(const statm::Try& begin, const statm::Block& end) {
    ++edgeStat[edkTry_HasFinallyBlock];
  }

  void VisitorAsgStat::visitWhile_HasCondition(const statm::While& begin, const expr::Expression& end) {
    ++edgeStat[edkWhile_HasCondition];
  }

  void VisitorAsgStat::visitAnnotatedElement_HasAnnotations(const struc::AnnotatedElement& begin, const expr::Annotation& end) {
    ++edgeStat[edkAnnotatedElement_HasAnnotations];
  }

  void VisitorAsgStat::visitAnnotationTypeElement_HasDefaultValue(const struc::AnnotationTypeElement& begin, const expr::Expression& end) {
    ++edgeStat[edkAnnotationTypeElement_HasDefaultValue];
  }

  void VisitorAsgStat::visitCompilationUnit_HasPackageDeclaration(const struc::CompilationUnit& begin, const struc::PackageDeclaration& end) {
    ++edgeStat[edkCompilationUnit_HasPackageDeclaration];
  }

  void VisitorAsgStat::visitCompilationUnit_HasImports(const struc::CompilationUnit& begin, const struc::Import& end) {
    ++edgeStat[edkCompilationUnit_HasImports];
  }

  void VisitorAsgStat::visitCompilationUnit_TypeDeclarations(const struc::CompilationUnit& begin, const struc::TypeDeclaration& end) {
    ++edgeStat[edkCompilationUnit_TypeDeclarations];
  }

  void VisitorAsgStat::visitCompilationUnit_HasOthers(const struc::CompilationUnit& begin, const base::Positioned& end) {
    ++edgeStat[edkCompilationUnit_HasOthers];
  }

  void VisitorAsgStat::visitEnumConstant_HasNewClass(const struc::EnumConstant& begin, const expr::NewClass& end) {
    ++edgeStat[edkEnumConstant_HasNewClass];
  }

  void VisitorAsgStat::visitGenericDeclaration_HasTypeParameters(const struc::GenericDeclaration& begin, const struc::TypeParameter& end) {
    ++edgeStat[edkGenericDeclaration_HasTypeParameters];
  }

  void VisitorAsgStat::visitImport_HasTarget(const struc::Import& begin, const expr::Expression& end) {
    ++edgeStat[edkImport_HasTarget];
  }

  void VisitorAsgStat::visitInitializerBlock_HasBody(const struc::InitializerBlock& begin, const statm::Block& end) {
    ++edgeStat[edkInitializerBlock_HasBody];
  }

  void VisitorAsgStat::visitMethodDeclaration_HasReturnType(const struc::MethodDeclaration& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkMethodDeclaration_HasReturnType];
  }

  void VisitorAsgStat::visitMethodDeclaration_MethodType(const struc::MethodDeclaration& begin, const type::MethodType& end) {
    ++edgeStat[edkMethodDeclaration_MethodType];
  }

  void VisitorAsgStat::visitMethodDeclaration_Overrides(const struc::MethodDeclaration& begin, const struc::MethodDeclaration& end) {
    ++edgeStat[edkMethodDeclaration_Overrides];
  }

  void VisitorAsgStat::visitNormalMethod_HasParameters(const struc::NormalMethod& begin, const struc::Parameter& end) {
    ++edgeStat[edkNormalMethod_HasParameters];
  }

  void VisitorAsgStat::visitNormalMethod_HasBody(const struc::NormalMethod& begin, const statm::Block& end) {
    ++edgeStat[edkNormalMethod_HasBody];
  }

  void VisitorAsgStat::visitNormalMethod_HasThrownExceptions(const struc::NormalMethod& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkNormalMethod_HasThrownExceptions];
  }

  void VisitorAsgStat::visitPackage_HasCompilationUnits(const struc::Package& begin, const struc::CompilationUnit& end) {
    ++edgeStat[edkPackage_HasCompilationUnits];
  }

  void VisitorAsgStat::visitPackageDeclaration_HasPackageName(const struc::PackageDeclaration& begin, const expr::Expression& end) {
    ++edgeStat[edkPackageDeclaration_HasPackageName];
  }

  void VisitorAsgStat::visitPackageDeclaration_RefersTo(const struc::PackageDeclaration& begin, const struc::Package& end) {
    ++edgeStat[edkPackageDeclaration_RefersTo];
  }

  void VisitorAsgStat::visitScope_HasMembers(const struc::Scope& begin, const struc::Member& end) {
    ++edgeStat[edkScope_HasMembers];
  }

  void VisitorAsgStat::visitTypeDeclaration_IsInCompilationUnit(const struc::TypeDeclaration& begin, const struc::CompilationUnit& end) {
    ++edgeStat[edkTypeDeclaration_IsInCompilationUnit];
  }

  void VisitorAsgStat::visitTypeDeclaration_HasSuperClass(const struc::TypeDeclaration& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkTypeDeclaration_HasSuperClass];
  }

  void VisitorAsgStat::visitTypeDeclaration_HasSuperInterfaces(const struc::TypeDeclaration& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkTypeDeclaration_HasSuperInterfaces];
  }

  void VisitorAsgStat::visitTypeDeclaration_HasOthers(const struc::TypeDeclaration& begin, const base::Positioned& end) {
    ++edgeStat[edkTypeDeclaration_HasOthers];
  }

  void VisitorAsgStat::visitTypeParameter_HasBounds(const struc::TypeParameter& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkTypeParameter_HasBounds];
  }

  void VisitorAsgStat::visitVariable_HasInitialValue(const struc::Variable& begin, const expr::Expression& end) {
    ++edgeStat[edkVariable_HasInitialValue];
  }

  void VisitorAsgStat::visitVariableDeclaration_HasType(const struc::VariableDeclaration& begin, const expr::TypeExpression& end) {
    ++edgeStat[edkVariableDeclaration_HasType];
  }

  void VisitorAsgStat::visitArrayType_ComponentType(const type::ArrayType& begin, const type::Type& end) {
    ++edgeStat[edkArrayType_ComponentType];
  }

  void VisitorAsgStat::visitClassType_RefersTo(const type::ClassType& begin, const struc::TypeDeclaration& end) {
    ++edgeStat[edkClassType_RefersTo];
  }

  void VisitorAsgStat::visitMethodType_ReturnType(const type::MethodType& begin, const type::Type& end) {
    ++edgeStat[edkMethodType_ReturnType];
  }

  void VisitorAsgStat::visitMethodType_ParameterTypes(const type::MethodType& begin, const type::Type& end) {
    ++edgeStat[edkMethodType_ParameterTypes];
  }

  void VisitorAsgStat::visitMethodType_ThrownTypes(const type::MethodType& begin, const type::Type& end) {
    ++edgeStat[edkMethodType_ThrownTypes];
  }

  void VisitorAsgStat::visitPackageType_RefersTo(const type::PackageType& begin, const struc::Package& end) {
    ++edgeStat[edkPackageType_RefersTo];
  }

  void VisitorAsgStat::visitParameterizedType_RawType(const type::ParameterizedType& begin, const type::Type& end) {
    ++edgeStat[edkParameterizedType_RawType];
  }

  void VisitorAsgStat::visitParameterizedType_ArgumentTypes(const type::ParameterizedType& begin, const type::Type& end) {
    ++edgeStat[edkParameterizedType_ArgumentTypes];
  }

  void VisitorAsgStat::visitScopedType_Owner(const type::ScopedType& begin, const type::Type& end) {
    ++edgeStat[edkScopedType_Owner];
  }

  void VisitorAsgStat::visitTypeVariable_RefersTo(const type::TypeVariable& begin, const struc::TypeParameter& end) {
    ++edgeStat[edkTypeVariable_RefersTo];
  }

  void VisitorAsgStat::visitUnionType_Alternatives(const type::UnionType& begin, const type::Type& end) {
    ++edgeStat[edkUnionType_Alternatives];
  }

  void VisitorAsgStat::visitWildcardType_Bound(const type::WildcardType& begin, const type::Type& end) {
    ++edgeStat[edkWildcardType_Bound];
  }


}}}
