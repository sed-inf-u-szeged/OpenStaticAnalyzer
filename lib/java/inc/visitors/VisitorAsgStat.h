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

#ifndef _JAVA_VISITORASGSTAT_H_
#define _JAVA_VISITORASGSTAT_H_

#include "java/inc/java.h"

/**
* \file VisitorAsgStat.h
* \brief Contains declaration of VisitorAsgStat class.
*/

namespace columbus { namespace java { namespace asg {
  /**
  * \brief Visitor to create statistics about the ASG.
  */
  class VisitorAsgStat : public VisitorAbstractNodes {
    protected:
      /**
      * \internal
      * \brief Constructor for VisitorAsgStat.
      */
      VisitorAsgStat();

      /**
      * \internal
      * \brief Destructor.
      */
      virtual ~VisitorAsgStat();

    public:
      /**
      * \brief Visitor to create statistics about base::Base node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Base& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about base::BlockComment node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::BlockComment& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about base::Comment node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Comment& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about base::Commentable node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Commentable& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about base::JavadocComment node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::JavadocComment& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about base::LineComment node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::LineComment& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about base::Named node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Named& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about base::NonJavadocComment node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::NonJavadocComment& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about base::Positioned node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Positioned& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about base::PositionedWithoutComment node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::PositionedWithoutComment& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::Annotation node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::Annotation& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::ArrayAccess node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::ArrayAccess& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::ArrayTypeExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::ArrayTypeExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::Assignment node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::Assignment& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::Binary node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::Binary& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::BooleanLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::BooleanLiteral& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::CharacterLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::CharacterLiteral& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::ClassLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::ClassLiteral& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::Conditional node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::Conditional& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::DoubleLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::DoubleLiteral& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::Erroneous node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::Erroneous& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::ErroneousTypeExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::ErroneousTypeExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::Expression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::Expression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::ExternalTypeExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::ExternalTypeExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::FieldAccess node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::FieldAccess& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::FloatLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::FloatLiteral& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::Identifier node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::Identifier& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::InfixExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::InfixExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::InstanceOf node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::InstanceOf& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::IntegerLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::IntegerLiteral& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::Literal node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::Literal& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::LongLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::LongLiteral& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::MarkerAnnotation node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::MarkerAnnotation& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::MethodInvocation node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::MethodInvocation& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::NewArray node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::NewArray& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::NewClass node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::NewClass& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::NormalAnnotation node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::NormalAnnotation& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::NullLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::NullLiteral& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::NumberLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::NumberLiteral& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::ParenthesizedExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::ParenthesizedExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::PostfixExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::PostfixExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::PrefixExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::PrefixExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::PrimitiveTypeExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::PrimitiveTypeExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::QualifiedTypeExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::QualifiedTypeExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::SimpleTypeExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::SimpleTypeExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::SingleElementAnnotation node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::SingleElementAnnotation& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::StringLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::StringLiteral& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::Super node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::Super& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::This node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::This& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::TypeApplyExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::TypeApplyExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::TypeCast node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::TypeCast& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::TypeExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::TypeExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::TypeUnionExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::TypeUnionExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::Unary node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::Unary& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expr::WildcardExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::WildcardExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::Assert node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Assert& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::BasicFor node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::BasicFor& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::Block node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Block& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::Break node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Break& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::Case node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Case& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::Continue node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Continue& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::Default node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Default& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::Do node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Do& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::Empty node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Empty& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::EnhancedFor node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::EnhancedFor& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::ExpressionStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::ExpressionStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::For node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::For& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::Handler node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Handler& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::If node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::If& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::Iteration node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Iteration& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::Jump node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Jump& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::LabeledStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::LabeledStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::Return node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Return& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::Selection node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Selection& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::Statement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Statement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::Switch node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Switch& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::SwitchLabel node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::SwitchLabel& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::Synchronized node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Synchronized& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::Throw node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Throw& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::Try node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Try& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statm::While node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::While& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::AnnotatedElement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::AnnotatedElement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::AnnotationType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::AnnotationType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::AnnotationTypeElement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::AnnotationTypeElement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::AnonymousClass node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::AnonymousClass& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::Class node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::Class& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::ClassDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::ClassDeclaration& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::ClassGeneric node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::ClassGeneric& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::CompilationUnit node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::CompilationUnit& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::Declaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::Declaration& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::Enum node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::Enum& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::EnumConstant node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::EnumConstant& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::GenericDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::GenericDeclaration& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::Import node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::Import& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::InitializerBlock node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::InitializerBlock& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::InstanceInitializerBlock node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::InstanceInitializerBlock& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::Interface node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::Interface& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::InterfaceDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::InterfaceDeclaration& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::InterfaceGeneric node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::InterfaceGeneric& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::Member node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::Member& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::Method node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::Method& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::MethodDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::MethodDeclaration& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::MethodGeneric node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::MethodGeneric& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::NamedDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::NamedDeclaration& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::NormalMethod node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::NormalMethod& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::Package node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::Package& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::PackageDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::PackageDeclaration& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::Parameter node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::Parameter& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::Scope node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::Scope& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::StaticInitializerBlock node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::StaticInitializerBlock& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::TypeDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::TypeDeclaration& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::TypeParameter node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::TypeParameter& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::Variable node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::Variable& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about struc::VariableDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::VariableDeclaration& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::ArrayType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::ArrayType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::BooleanType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::BooleanType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::BoundedWildcardType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::BoundedWildcardType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::ByteType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::ByteType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::CharType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::CharType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::ClassType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::ClassType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::DoubleType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::DoubleType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::ErrorType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::ErrorType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::FloatType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::FloatType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::IntType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::IntType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::LongType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::LongType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::LowerBoundedWildcardType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::LowerBoundedWildcardType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::MethodType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::MethodType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::NoType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::NoType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::NullType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::NullType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::PackageType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::PackageType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::ParameterizedType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::ParameterizedType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::PrimitiveType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::PrimitiveType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::ScopedType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::ScopedType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::ShortType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::ShortType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::Type node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::Type& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::TypeVariable node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::TypeVariable& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::UnboundedWildcardType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::UnboundedWildcardType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::UnionType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::UnionType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::UpperBoundedWildcardType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::UpperBoundedWildcardType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::VoidType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::VoidType& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about type::WildcardType node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::WildcardType& node,bool callVirtualBase = true);

      /**
      * \brief Edge visitor for comments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCommentable_Comments(const base::Commentable& begin, const base::Comment& end);

      /**
      * \brief Edge  visitor for hasAnnotationName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnnotation_HasAnnotationName(const expr::Annotation& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayTypeExpression_HasComponentType(const expr::ArrayTypeExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasLeftOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinary_HasLeftOperand(const expr::Binary& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasRightOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinary_HasRightOperand(const expr::Binary& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassLiteral_HasComponentType(const expr::ClassLiteral& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditional_HasCondition(const expr::Conditional& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasTrueExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditional_HasTrueExpression(const expr::Conditional& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasFalseExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditional_HasFalseExpression(const expr::Conditional& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasErrors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitErroneous_HasErrors(const expr::Erroneous& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasErrors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitErroneousTypeExpression_HasErrors(const expr::ErroneousTypeExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge visitor for type edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExpression_Type(const expr::Expression& begin, const type::Type& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIdentifier_RefersTo(const expr::Identifier& begin, const base::Named& end);

      /**
      * \brief Edge  visitor for hasTypeOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInstanceOf_HasTypeOperand(const expr::InstanceOf& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodInvocation_HasTypeArguments(const expr::MethodInvocation& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodInvocation_HasArguments(const expr::MethodInvocation& begin, const expr::Expression& end);

      /**
      * \brief Edge visitor for invokes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodInvocation_Invokes(const expr::MethodInvocation& begin, const struc::MethodDeclaration& end);

      /**
      * \brief Edge  visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewArray_HasComponentType(const expr::NewArray& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasDimensions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewArray_HasDimensions(const expr::NewArray& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasInitializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewArray_HasInitializers(const expr::NewArray& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasEnclosingExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewClass_HasEnclosingExpression(const expr::NewClass& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewClass_HasTypeArguments(const expr::NewClass& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasTypeName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewClass_HasTypeName(const expr::NewClass& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewClass_HasArguments(const expr::NewClass& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasAnonymousClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewClass_HasAnonymousClass(const expr::NewClass& begin, const struc::AnonymousClass& end);

      /**
      * \brief Edge visitor for constructor edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewClass_Constructor(const expr::NewClass& begin, const struc::NormalMethod& end);

      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNormalAnnotation_HasArguments(const expr::NormalAnnotation& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasQualifierType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQualifiedTypeExpression_HasQualifierType(const expr::QualifiedTypeExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasSimpleType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQualifiedTypeExpression_HasSimpleType(const expr::QualifiedTypeExpression& begin, const expr::SimpleTypeExpression& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSingleElementAnnotation_HasArgument(const expr::SingleElementAnnotation& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasRawType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeApplyExpression_HasRawType(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeApplyExpression_HasTypeArguments(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasTypeOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeCast_HasTypeOperand(const expr::TypeCast& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasAlternatives edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeUnionExpression_HasAlternatives(const expr::TypeUnionExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUnary_HasOperand(const expr::Unary& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasBound edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWildcardExpression_HasBound(const expr::WildcardExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssert_HasCondition(const statm::Assert& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasDetail edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssert_HasDetail(const statm::Assert& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasInitializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasicFor_HasInitializers(const statm::BasicFor& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasicFor_HasCondition(const statm::BasicFor& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasUpdates edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasicFor_HasUpdates(const statm::BasicFor& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasStatements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBlock_HasStatements(const statm::Block& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCase_HasExpression(const statm::Case& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDo_HasCondition(const statm::Do& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEnhancedFor_HasParameter(const statm::EnhancedFor& begin, const struc::Parameter& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEnhancedFor_HasExpression(const statm::EnhancedFor& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExpressionStatement_HasExpression(const statm::ExpressionStatement& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitHandler_HasParameter(const statm::Handler& begin, const struc::Parameter& end);

      /**
      * \brief Edge  visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitHandler_HasBlock(const statm::Handler& begin, const statm::Block& end);

      /**
      * \brief Edge  visitor for hasSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIf_HasSubstatement(const statm::If& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasFalseSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIf_HasFalseSubstatement(const statm::If& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIteration_HasSubstatement(const statm::Iteration& begin, const statm::Statement& end);

      /**
      * \brief Edge visitor for target edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitJump_Target(const statm::Jump& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasStatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLabeledStatement_HasStatement(const statm::LabeledStatement& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitReturn_HasExpression(const statm::Return& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSelection_HasCondition(const statm::Selection& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasCases edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitch_HasCases(const statm::Switch& begin, const statm::SwitchLabel& end);

      /**
      * \brief Edge  visitor for hasStatements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchLabel_HasStatements(const statm::SwitchLabel& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasLock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSynchronized_HasLock(const statm::Synchronized& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSynchronized_HasBlock(const statm::Synchronized& begin, const statm::Block& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitThrow_HasExpression(const statm::Throw& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasResources edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTry_HasResources(const statm::Try& begin, const struc::Variable& end);

      /**
      * \brief Edge  visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTry_HasBlock(const statm::Try& begin, const statm::Block& end);

      /**
      * \brief Edge  visitor for hasHandlers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTry_HasHandlers(const statm::Try& begin, const statm::Handler& end);

      /**
      * \brief Edge  visitor for hasFinallyBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTry_HasFinallyBlock(const statm::Try& begin, const statm::Block& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhile_HasCondition(const statm::While& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasAnnotations edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnnotatedElement_HasAnnotations(const struc::AnnotatedElement& begin, const expr::Annotation& end);

      /**
      * \brief Edge  visitor for hasDefaultValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnnotationTypeElement_HasDefaultValue(const struc::AnnotationTypeElement& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasPackageDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnit_HasPackageDeclaration(const struc::CompilationUnit& begin, const struc::PackageDeclaration& end);

      /**
      * \brief Edge  visitor for hasImports edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnit_HasImports(const struc::CompilationUnit& begin, const struc::Import& end);

      /**
      * \brief Edge visitor for typeDeclarations edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnit_TypeDeclarations(const struc::CompilationUnit& begin, const struc::TypeDeclaration& end);

      /**
      * \brief Edge  visitor for hasOthers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnit_HasOthers(const struc::CompilationUnit& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasNewClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEnumConstant_HasNewClass(const struc::EnumConstant& begin, const expr::NewClass& end);

      /**
      * \brief Edge  visitor for hasTypeParameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGenericDeclaration_HasTypeParameters(const struc::GenericDeclaration& begin, const struc::TypeParameter& end);

      /**
      * \brief Edge  visitor for hasTarget edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImport_HasTarget(const struc::Import& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInitializerBlock_HasBody(const struc::InitializerBlock& begin, const statm::Block& end);

      /**
      * \brief Edge  visitor for hasReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclaration_HasReturnType(const struc::MethodDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge visitor for methodType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclaration_MethodType(const struc::MethodDeclaration& begin, const type::MethodType& end);

      /**
      * \brief Edge visitor for overrides edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclaration_Overrides(const struc::MethodDeclaration& begin, const struc::MethodDeclaration& end);

      /**
      * \brief Edge  visitor for hasParameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNormalMethod_HasParameters(const struc::NormalMethod& begin, const struc::Parameter& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNormalMethod_HasBody(const struc::NormalMethod& begin, const statm::Block& end);

      /**
      * \brief Edge  visitor for hasThrownExceptions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNormalMethod_HasThrownExceptions(const struc::NormalMethod& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasCompilationUnits edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPackage_HasCompilationUnits(const struc::Package& begin, const struc::CompilationUnit& end);

      /**
      * \brief Edge  visitor for hasPackageName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPackageDeclaration_HasPackageName(const struc::PackageDeclaration& begin, const expr::Expression& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPackageDeclaration_RefersTo(const struc::PackageDeclaration& begin, const struc::Package& end);

      /**
      * \brief Edge  visitor for hasMembers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitScope_HasMembers(const struc::Scope& begin, const struc::Member& end);

      /**
      * \brief Edge visitor for isInCompilationUnit edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclaration_IsInCompilationUnit(const struc::TypeDeclaration& begin, const struc::CompilationUnit& end);

      /**
      * \brief Edge  visitor for hasSuperClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclaration_HasSuperClass(const struc::TypeDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasSuperInterfaces edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclaration_HasSuperInterfaces(const struc::TypeDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasOthers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclaration_HasOthers(const struc::TypeDeclaration& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasBounds edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeParameter_HasBounds(const struc::TypeParameter& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasInitialValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariable_HasInitialValue(const struc::Variable& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclaration_HasType(const struc::VariableDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge visitor for componentType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayType_ComponentType(const type::ArrayType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassType_RefersTo(const type::ClassType& begin, const struc::TypeDeclaration& end);

      /**
      * \brief Edge visitor for returnType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodType_ReturnType(const type::MethodType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for parameterTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodType_ParameterTypes(const type::MethodType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for thrownTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodType_ThrownTypes(const type::MethodType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPackageType_RefersTo(const type::PackageType& begin, const struc::Package& end);

      /**
      * \brief Edge visitor for rawType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameterizedType_RawType(const type::ParameterizedType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for argumentTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameterizedType_ArgumentTypes(const type::ParameterizedType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for owner edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitScopedType_Owner(const type::ScopedType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeVariable_RefersTo(const type::TypeVariable& begin, const struc::TypeParameter& end);

      /**
      * \brief Edge visitor for alternatives edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUnionType_Alternatives(const type::UnionType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for bound edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWildcardType_Bound(const type::WildcardType& begin, const type::Type& end);

    protected:
      /** \internal \brief Contains statistics about nodes. */
      unsigned int nodeStatSimple[141];

      /** \internal \brief Contains statistics about nodes (where the node is counted in all parents statistic). */
      unsigned int nodeStatParent[141];

      /** \internal \brief Contains statistics about edges. */
      unsigned int edgeStat[105];

      friend class Factory;

      /** \internal \brief Contains the scoped names of the nodes. */
      static const char* nodeNames[];
      /** \internal \brief Contains the size of the nodes. */
      static const unsigned short nodeSizes[];
  }; // Visitor


}}}
#endif

