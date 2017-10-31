/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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

#ifndef _JAVA_VISITORFILTER_H_
#define _JAVA_VISITORFILTER_H_

#include "java/inc/java.h"

/**
* \file VisitorFilter.h
* \brief Contains declaration of VisitorFilter class.
*/

namespace columbus { namespace java { namespace asg {
  /**
  * \brief VisitorFilter class filters out nodes from the ASG.
  */
  class VisitorFilter : public Visitor {
    protected:
      /** \internal \brief Pointer to the set(Not)FilteredThisNodeOnly() method. */
      void (Factory::*selector)(NodeId id);

    public:
      /**
      * \brief Constructor for VisitorFilter.
      * \param filter [in] If this parameter is true then the visitor will filter the nodes out. If it is false then it set the nodes to not filtered.
      */
      VisitorFilter(bool filter = true);

      /**
      * \brief Destructor.
      */
      virtual ~VisitorFilter();

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::BlockComment& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::JavadocComment& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::LineComment& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::ArrayAccess& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::ArrayTypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::Assignment& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::BooleanLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::CharacterLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::ClassLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::Conditional& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::DoubleLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::Erroneous& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::ErroneousTypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::ExternalTypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::FieldAccess& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::FloatLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::Identifier& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::InfixExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::InstanceOf& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::IntegerLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::LongLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::MarkerAnnotation& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::MethodInvocation& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::NewArray& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::NewClass& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::NormalAnnotation& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::NullLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::ParenthesizedExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::PostfixExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::PrefixExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::PrimitiveTypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::QualifiedTypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::SimpleTypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::SingleElementAnnotation& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::StringLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::Super& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::This& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::TypeApplyExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::TypeCast& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::TypeUnionExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::WildcardExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Assert& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::BasicFor& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Block& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Break& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Case& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Continue& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Default& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Do& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Empty& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::EnhancedFor& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::ExpressionStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Handler& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::If& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::LabeledStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Return& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Switch& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Synchronized& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Throw& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Try& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::While& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::AnnotationType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::AnnotationTypeElement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::AnonymousClass& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::Class& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::ClassGeneric& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::CompilationUnit& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::Enum& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::EnumConstant& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::Import& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::InstanceInitializerBlock& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::Interface& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::InterfaceGeneric& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::Method& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::MethodGeneric& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::Package& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::PackageDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::Parameter& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::StaticInitializerBlock& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::TypeParameter& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::Variable& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::ArrayType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::BooleanType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::ByteType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::CharType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::ClassType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::DoubleType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::ErrorType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::FloatType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::IntType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::LongType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::LowerBoundedWildcardType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::MethodType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::NoType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::NullType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::PackageType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::ParameterizedType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::ShortType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::TypeVariable& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::UnboundedWildcardType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::UnionType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::UpperBoundedWildcardType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::VoidType& node , bool callVirtualBase = true);

  }; // VisitorFilter


}}}
#endif

