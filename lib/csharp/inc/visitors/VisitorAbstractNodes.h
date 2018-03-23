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

#ifndef _CSHARP_VISITORABSTRACTNODES_H_
#define _CSHARP_VISITORABSTRACTNODES_H_

#include "csharp/inc/csharp.h"

/**
* \file VisitorAbstractNodes.h
* \brief Contains declaration of VisitorAbstractNodes class.
*/

namespace columbus { namespace csharp { namespace asg {
  /**
  * \brief Visitor class for all edges and nodes (including abstract nodes as well).
  */
  class VisitorAbstractNodes : public Visitor {
    public:
      /**
      * \brief Virtual destructor.
      */
      virtual ~VisitorAbstractNodes();

      /**
      * \brief Empty abstract visitor for base::Base node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const base::Base& node , bool callVirtualBase = true);

      /**
      * \brief Empty abstract end visitor for base::Base node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const base::Base& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Base,..) of the base::Positioned node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const base::Positioned& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Base,..) of the base::Positioned node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const base::Positioned& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::NameSyntax,..) of the expression::AliasQualifiedNameSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::AliasQualifiedNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::NameSyntax,..) of the expression::AliasQualifiedNameSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::AliasQualifiedNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::AnonymousFunctionExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::AnonymousFunctionExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::AnonymousFunctionExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::AnonymousFunctionExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::AnonymousFunctionExpressionSyntax,..) of the expression::AnonymousMethodExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::AnonymousMethodExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::AnonymousFunctionExpressionSyntax,..) of the expression::AnonymousMethodExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::AnonymousMethodExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::AnonymousObjectCreationExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::AnonymousObjectCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::AnonymousObjectCreationExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::AnonymousObjectCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::ArrayCreationExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::ArrayCreationExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::TypeSyntax,..) of the expression::ArrayTypeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ArrayTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::TypeSyntax,..) of the expression::ArrayTypeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ArrayTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::AssignmentExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::AssignmentExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::AssignmentExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::AssignmentExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::AwaitExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::AwaitExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::AwaitExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::AwaitExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::InstanceExpressionSyntax,..) of the expression::BaseExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::BaseExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::InstanceExpressionSyntax,..) of the expression::BaseExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::BaseExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::BinaryExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::BinaryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::BinaryExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::BinaryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::CastExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::CastExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::CastExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::CastExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::CheckedExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::CheckedExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::CheckedExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::CheckedExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::ConditionalAccessExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ConditionalAccessExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::ConditionalAccessExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ConditionalAccessExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::ConditionalExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ConditionalExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::ConditionalExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ConditionalExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::DefaultExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::DefaultExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::DefaultExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::DefaultExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::ElementAccessExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ElementAccessExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::ElementAccessExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ElementAccessExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::ElementBindingExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ElementBindingExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::ElementBindingExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ElementBindingExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the expression::ExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the expression::ExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::SimpleNameSyntax,..) of the expression::GenericNameSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::GenericNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::SimpleNameSyntax,..) of the expression::GenericNameSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::GenericNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::SimpleNameSyntax,..) of the expression::IdentifierNameSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::IdentifierNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::SimpleNameSyntax,..) of the expression::IdentifierNameSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::IdentifierNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::ImplicitArrayCreationExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ImplicitArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::ImplicitArrayCreationExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ImplicitArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::ImplicitElementAccessSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ImplicitElementAccessSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::ImplicitElementAccessSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ImplicitElementAccessSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::InitializerExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::InitializerExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::InitializerExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::InitializerExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::InstanceExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::InstanceExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::InstanceExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::InstanceExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::InterpolatedStringExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::InterpolatedStringExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::InterpolatedStringExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::InterpolatedStringExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::InvocationExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::InvocationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::InvocationExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::InvocationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::AnonymousFunctionExpressionSyntax,..) of the expression::LambdaExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::LambdaExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::AnonymousFunctionExpressionSyntax,..) of the expression::LambdaExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::LambdaExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::LiteralExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::LiteralExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::LiteralExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::LiteralExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::MakeRefExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::MakeRefExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::MakeRefExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::MakeRefExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::MemberAccessExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::MemberAccessExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::MemberAccessExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::MemberAccessExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::MemberBindingExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::MemberBindingExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::MemberBindingExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::MemberBindingExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::TypeSyntax,..) of the expression::NameSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::NameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::TypeSyntax,..) of the expression::NameSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::NameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::TypeSyntax,..) of the expression::NullableTypeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::NullableTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::TypeSyntax,..) of the expression::NullableTypeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::NullableTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::ObjectCreationExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ObjectCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::ObjectCreationExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ObjectCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::OmittedArraySizeExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::OmittedArraySizeExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::OmittedArraySizeExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::OmittedArraySizeExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::TypeSyntax,..) of the expression::OmittedTypeArgumentSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::OmittedTypeArgumentSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::TypeSyntax,..) of the expression::OmittedTypeArgumentSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::OmittedTypeArgumentSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::ParenthesizedExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ParenthesizedExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::ParenthesizedExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ParenthesizedExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::LambdaExpressionSyntax,..) of the expression::ParenthesizedLambdaExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ParenthesizedLambdaExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::LambdaExpressionSyntax,..) of the expression::ParenthesizedLambdaExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ParenthesizedLambdaExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::TypeSyntax,..) of the expression::PointerTypeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::PointerTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::TypeSyntax,..) of the expression::PointerTypeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::PointerTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::PostfixUnaryExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::PostfixUnaryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::PostfixUnaryExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::PostfixUnaryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::TypeSyntax,..) of the expression::PredefinedTypeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::PredefinedTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::TypeSyntax,..) of the expression::PredefinedTypeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::PredefinedTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::PrefixUnaryExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::PrefixUnaryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::PrefixUnaryExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::PrefixUnaryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::NameSyntax,..) of the expression::QualifiedNameSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::QualifiedNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::NameSyntax,..) of the expression::QualifiedNameSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::QualifiedNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::QueryExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::QueryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::QueryExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::QueryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::RefTypeExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::RefTypeExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::RefTypeExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::RefTypeExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::RefValueExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::RefValueExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::RefValueExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::RefValueExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::LambdaExpressionSyntax,..) of the expression::SimpleLambdaExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::SimpleLambdaExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::LambdaExpressionSyntax,..) of the expression::SimpleLambdaExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::SimpleLambdaExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::NameSyntax,..) of the expression::SimpleNameSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::SimpleNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::NameSyntax,..) of the expression::SimpleNameSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::SimpleNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::SizeOfExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::SizeOfExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::SizeOfExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::SizeOfExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::StackAllocArrayCreationExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::StackAllocArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::StackAllocArrayCreationExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::StackAllocArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::InstanceExpressionSyntax,..) of the expression::ThisExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ThisExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::InstanceExpressionSyntax,..) of the expression::ThisExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ThisExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::TypeOfExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::TypeOfExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::TypeOfExpressionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::TypeOfExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::ExpressionSyntax,..) of the expression::TypeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::TypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::ExpressionSyntax,..) of the expression::TypeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::TypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::BlockSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::BlockSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::BlockSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::BlockSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::BreakStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::BreakStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::BreakStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::BreakStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::CheckedStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::CheckedStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::CheckedStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::CheckedStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::ContinueStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::ContinueStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::ContinueStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::ContinueStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::DoStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::DoStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::DoStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::DoStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::EmptyStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::EmptyStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::EmptyStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::EmptyStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::ExpressionStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::ExpressionStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::ExpressionStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::ExpressionStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::FixedStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::FixedStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::FixedStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::FixedStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::ForEachStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::ForEachStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::ForEachStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::ForEachStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::ForStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::ForStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::ForStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::ForStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::GotoStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::GotoStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::GotoStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::GotoStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::IfStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::IfStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::IfStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::IfStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::LabeledStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::LabeledStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::LabeledStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::LabeledStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::LocalDeclarationStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::LocalDeclarationStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::LocalDeclarationStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::LocalDeclarationStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::LockStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::LockStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::LockStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::LockStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::ReturnStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::ReturnStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::ReturnStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::ReturnStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the statement::StatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::StatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the statement::StatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::StatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::SwitchStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::SwitchStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::SwitchStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::SwitchStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::ThrowStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::ThrowStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::ThrowStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::ThrowStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::TryStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::TryStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::TryStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::TryStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::UnsafeStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::UnsafeStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::UnsafeStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::UnsafeStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::UsingStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::UsingStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::UsingStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::UsingStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::WhileStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::WhileStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::WhileStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::WhileStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::StatementSyntax,..) of the statement::YieldStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::YieldStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::StatementSyntax,..) of the statement::YieldStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::YieldStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::AccessorDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::AccessorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::AccessorDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::AccessorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::AccessorListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::AccessorListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::AccessorListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::AccessorListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::AnonymousObjectMemberDeclaratorSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::AnonymousObjectMemberDeclaratorSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::AnonymousObjectMemberDeclaratorSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::AnonymousObjectMemberDeclaratorSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::BaseArgumentListSyntax,..) of the structure::ArgumentListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::BaseArgumentListSyntax,..) of the structure::ArgumentListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::ArgumentSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ArgumentSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::ArgumentSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ArgumentSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::ArrayRankSpecifierSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ArrayRankSpecifierSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::ArrayRankSpecifierSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ArrayRankSpecifierSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::ArrowExpressionClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ArrowExpressionClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::ArrowExpressionClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ArrowExpressionClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::AttributeArgumentListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::AttributeArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::AttributeArgumentListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::AttributeArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::AttributeArgumentSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::AttributeArgumentSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::AttributeArgumentSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::AttributeArgumentSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::AttributeListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::AttributeListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::AttributeListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::AttributeListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::AttributeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::AttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::AttributeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::AttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::AttributeTargetSpecifierSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::AttributeTargetSpecifierSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::AttributeTargetSpecifierSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::AttributeTargetSpecifierSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::BaseArgumentListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::BaseArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::BaseArgumentListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::BaseArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::BaseCrefParameterListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::BaseCrefParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::BaseCrefParameterListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::BaseCrefParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::MemberDeclarationSyntax,..) of the structure::BaseFieldDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::BaseFieldDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::MemberDeclarationSyntax,..) of the structure::BaseFieldDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::BaseFieldDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::BaseListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::BaseListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::BaseListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::BaseListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::MemberDeclarationSyntax,..) of the structure::BaseMethodDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::BaseMethodDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::MemberDeclarationSyntax,..) of the structure::BaseMethodDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::BaseMethodDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::BaseParameterListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::BaseParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::BaseParameterListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::BaseParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::MemberDeclarationSyntax,..) of the structure::BasePropertyDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::BasePropertyDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::MemberDeclarationSyntax,..) of the structure::BasePropertyDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::BasePropertyDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::MemberDeclarationSyntax,..) of the structure::BaseTypeDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::BaseTypeDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::MemberDeclarationSyntax,..) of the structure::BaseTypeDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::BaseTypeDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::BaseTypeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::BaseTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::BaseTypeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::BaseTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::BaseArgumentListSyntax,..) of the structure::BracketedArgumentListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::BracketedArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::BaseArgumentListSyntax,..) of the structure::BracketedArgumentListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::BracketedArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::BaseParameterListSyntax,..) of the structure::BracketedParameterListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::BracketedParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::BaseParameterListSyntax,..) of the structure::BracketedParameterListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::BracketedParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::SwitchLabelSyntax,..) of the structure::CaseSwitchLabelSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::CaseSwitchLabelSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::SwitchLabelSyntax,..) of the structure::CaseSwitchLabelSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::CaseSwitchLabelSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::CatchClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::CatchClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::CatchClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::CatchClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::CatchDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::CatchDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::CatchDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::CatchDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::CatchFilterClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::CatchFilterClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::CatchFilterClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::CatchFilterClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::TypeDeclarationSyntax,..) of the structure::ClassDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ClassDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::TypeDeclarationSyntax,..) of the structure::ClassDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ClassDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::TypeParameterConstraintSyntax,..) of the structure::ClassOrStructConstraintSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ClassOrStructConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::TypeParameterConstraintSyntax,..) of the structure::ClassOrStructConstraintSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ClassOrStructConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::CompilationUnitSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::CompilationUnitSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::CompilationUnitSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::CompilationUnitSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::TypeParameterConstraintSyntax,..) of the structure::ConstructorConstraintSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ConstructorConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::TypeParameterConstraintSyntax,..) of the structure::ConstructorConstraintSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ConstructorConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::BaseMethodDeclarationSyntax,..) of the structure::ConstructorDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ConstructorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::BaseMethodDeclarationSyntax,..) of the structure::ConstructorDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ConstructorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::ConstructorInitializerSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ConstructorInitializerSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::ConstructorInitializerSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ConstructorInitializerSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::BaseMethodDeclarationSyntax,..) of the structure::ConversionOperatorDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ConversionOperatorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::BaseMethodDeclarationSyntax,..) of the structure::ConversionOperatorDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ConversionOperatorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::MemberCrefSyntax,..) of the structure::ConversionOperatorMemberCrefSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ConversionOperatorMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::MemberCrefSyntax,..) of the structure::ConversionOperatorMemberCrefSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ConversionOperatorMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::BaseCrefParameterListSyntax,..) of the structure::CrefBracketedParameterListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::CrefBracketedParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::BaseCrefParameterListSyntax,..) of the structure::CrefBracketedParameterListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::CrefBracketedParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::BaseCrefParameterListSyntax,..) of the structure::CrefParameterListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::CrefParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::BaseCrefParameterListSyntax,..) of the structure::CrefParameterListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::CrefParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::CrefParameterSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::CrefParameterSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::CrefParameterSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::CrefParameterSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::CrefSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::CrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::CrefSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::CrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::SwitchLabelSyntax,..) of the structure::DefaultSwitchLabelSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::DefaultSwitchLabelSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::SwitchLabelSyntax,..) of the structure::DefaultSwitchLabelSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::DefaultSwitchLabelSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::MemberDeclarationSyntax,..) of the structure::DelegateDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::DelegateDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::MemberDeclarationSyntax,..) of the structure::DelegateDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::DelegateDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::BaseMethodDeclarationSyntax,..) of the structure::DestructorDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::DestructorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::BaseMethodDeclarationSyntax,..) of the structure::DestructorDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::DestructorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::ElseClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ElseClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::ElseClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ElseClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::BaseTypeDeclarationSyntax,..) of the structure::EnumDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::EnumDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::BaseTypeDeclarationSyntax,..) of the structure::EnumDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::EnumDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::MemberDeclarationSyntax,..) of the structure::EnumMemberDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::EnumMemberDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::MemberDeclarationSyntax,..) of the structure::EnumMemberDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::EnumMemberDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::EqualsValueClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::EqualsValueClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::EqualsValueClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::EqualsValueClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::BasePropertyDeclarationSyntax,..) of the structure::EventDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::EventDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::BasePropertyDeclarationSyntax,..) of the structure::EventDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::EventDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::BaseFieldDeclarationSyntax,..) of the structure::EventFieldDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::EventFieldDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::BaseFieldDeclarationSyntax,..) of the structure::EventFieldDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::EventFieldDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::ExplicitInterfaceSpecifierSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ExplicitInterfaceSpecifierSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::ExplicitInterfaceSpecifierSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ExplicitInterfaceSpecifierSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::ExternAliasDirectiveSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ExternAliasDirectiveSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::ExternAliasDirectiveSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ExternAliasDirectiveSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::BaseFieldDeclarationSyntax,..) of the structure::FieldDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::FieldDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::BaseFieldDeclarationSyntax,..) of the structure::FieldDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::FieldDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::FinallyClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::FinallyClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::FinallyClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::FinallyClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::QueryClauseSyntax,..) of the structure::FromClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::FromClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::QueryClauseSyntax,..) of the structure::FromClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::FromClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::MemberDeclarationSyntax,..) of the structure::GlobalStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::GlobalStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::MemberDeclarationSyntax,..) of the structure::GlobalStatementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::GlobalStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::SelectOrGroupClauseSyntax,..) of the structure::GroupClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::GroupClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::SelectOrGroupClauseSyntax,..) of the structure::GroupClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::GroupClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::MemberDeclarationSyntax,..) of the structure::IncompleteMemberSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::IncompleteMemberSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::MemberDeclarationSyntax,..) of the structure::IncompleteMemberSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::IncompleteMemberSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::BasePropertyDeclarationSyntax,..) of the structure::IndexerDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::IndexerDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::BasePropertyDeclarationSyntax,..) of the structure::IndexerDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::IndexerDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::MemberCrefSyntax,..) of the structure::IndexerMemberCrefSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::IndexerMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::MemberCrefSyntax,..) of the structure::IndexerMemberCrefSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::IndexerMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::TypeDeclarationSyntax,..) of the structure::InterfaceDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::InterfaceDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::TypeDeclarationSyntax,..) of the structure::InterfaceDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::InterfaceDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::InterpolatedStringContentSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::InterpolatedStringContentSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::InterpolatedStringContentSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::InterpolatedStringContentSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::InterpolatedStringContentSyntax,..) of the structure::InterpolatedStringTextSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::InterpolatedStringTextSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::InterpolatedStringContentSyntax,..) of the structure::InterpolatedStringTextSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::InterpolatedStringTextSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::InterpolationAlignmentClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::InterpolationAlignmentClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::InterpolationAlignmentClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::InterpolationAlignmentClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::InterpolationFormatClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::InterpolationFormatClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::InterpolationFormatClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::InterpolationFormatClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::InterpolatedStringContentSyntax,..) of the structure::InterpolationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::InterpolationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::InterpolatedStringContentSyntax,..) of the structure::InterpolationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::InterpolationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::QueryClauseSyntax,..) of the structure::JoinClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::JoinClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::QueryClauseSyntax,..) of the structure::JoinClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::JoinClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::JoinIntoClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::JoinIntoClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::JoinIntoClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::JoinIntoClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::QueryClauseSyntax,..) of the structure::LetClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::LetClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::QueryClauseSyntax,..) of the structure::LetClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::LetClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::CrefSyntax,..) of the structure::MemberCrefSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::MemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::CrefSyntax,..) of the structure::MemberCrefSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::MemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::MemberDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::MemberDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::MemberDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::MemberDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::BaseMethodDeclarationSyntax,..) of the structure::MethodDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::MethodDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::BaseMethodDeclarationSyntax,..) of the structure::MethodDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::MethodDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::NameColonSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::NameColonSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::NameColonSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::NameColonSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::NameEqualsSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::NameEqualsSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::NameEqualsSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::NameEqualsSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::MemberCrefSyntax,..) of the structure::NameMemberCrefSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::NameMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::MemberCrefSyntax,..) of the structure::NameMemberCrefSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::NameMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::MemberDeclarationSyntax,..) of the structure::NamespaceDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::NamespaceDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::MemberDeclarationSyntax,..) of the structure::NamespaceDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::NamespaceDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::BaseMethodDeclarationSyntax,..) of the structure::OperatorDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::OperatorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::BaseMethodDeclarationSyntax,..) of the structure::OperatorDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::OperatorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::MemberCrefSyntax,..) of the structure::OperatorMemberCrefSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::OperatorMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::MemberCrefSyntax,..) of the structure::OperatorMemberCrefSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::OperatorMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::QueryClauseSyntax,..) of the structure::OrderByClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::OrderByClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::QueryClauseSyntax,..) of the structure::OrderByClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::OrderByClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::OrderingSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::OrderingSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::OrderingSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::OrderingSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::BaseParameterListSyntax,..) of the structure::ParameterListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::BaseParameterListSyntax,..) of the structure::ParameterListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::ParameterSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ParameterSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::ParameterSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ParameterSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::BasePropertyDeclarationSyntax,..) of the structure::PropertyDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::PropertyDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::BasePropertyDeclarationSyntax,..) of the structure::PropertyDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::PropertyDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::CrefSyntax,..) of the structure::QualifiedCrefSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::QualifiedCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::CrefSyntax,..) of the structure::QualifiedCrefSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::QualifiedCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::QueryBodySyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::QueryBodySyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::QueryBodySyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::QueryBodySyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::QueryClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::QueryClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::QueryClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::QueryClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::QueryContinuationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::QueryContinuationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::QueryContinuationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::QueryContinuationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::SelectOrGroupClauseSyntax,..) of the structure::SelectClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::SelectClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::SelectOrGroupClauseSyntax,..) of the structure::SelectClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::SelectClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::SelectOrGroupClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::SelectOrGroupClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::SelectOrGroupClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::SelectOrGroupClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::BaseTypeSyntax,..) of the structure::SimpleBaseTypeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::SimpleBaseTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::BaseTypeSyntax,..) of the structure::SimpleBaseTypeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::SimpleBaseTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::TypeDeclarationSyntax,..) of the structure::StructDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::StructDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::TypeDeclarationSyntax,..) of the structure::StructDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::StructDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::SwitchLabelSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::SwitchLabelSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::SwitchLabelSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::SwitchLabelSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::SwitchSectionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::SwitchSectionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::SwitchSectionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::SwitchSectionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::SyntaxToken node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::SyntaxToken& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::SyntaxToken node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::SyntaxToken& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::TypeArgumentListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::TypeArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::TypeArgumentListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::TypeArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::TypeParameterConstraintSyntax,..) of the structure::TypeConstraintSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::TypeConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::TypeParameterConstraintSyntax,..) of the structure::TypeConstraintSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::TypeConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::CrefSyntax,..) of the structure::TypeCrefSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::TypeCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::CrefSyntax,..) of the structure::TypeCrefSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::TypeCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::BaseTypeDeclarationSyntax,..) of the structure::TypeDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::TypeDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::BaseTypeDeclarationSyntax,..) of the structure::TypeDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::TypeDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::TypeParameterConstraintClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::TypeParameterConstraintClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::TypeParameterConstraintClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::TypeParameterConstraintClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::TypeParameterConstraintSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::TypeParameterConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::TypeParameterConstraintSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::TypeParameterConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::TypeParameterListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::TypeParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::TypeParameterListSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::TypeParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::TypeParameterSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::TypeParameterSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::TypeParameterSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::TypeParameterSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::UsingDirectiveSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::UsingDirectiveSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::UsingDirectiveSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::UsingDirectiveSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::VariableDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::VariableDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::VariableDeclarationSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::VariableDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::VariableDeclaratorSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::VariableDeclaratorSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::VariableDeclaratorSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::VariableDeclaratorSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::QueryClauseSyntax,..) of the structure::WhereClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::WhereClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::QueryClauseSyntax,..) of the structure::WhereClauseSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::WhereClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::XmlAttributeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::XmlAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::XmlAttributeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::XmlAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::XmlNodeSyntax,..) of the structure::XmlCDataSectionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::XmlCDataSectionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::XmlNodeSyntax,..) of the structure::XmlCDataSectionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::XmlCDataSectionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::XmlNodeSyntax,..) of the structure::XmlCommentSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::XmlCommentSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::XmlNodeSyntax,..) of the structure::XmlCommentSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::XmlCommentSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::XmlAttributeSyntax,..) of the structure::XmlCrefAttributeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::XmlCrefAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::XmlAttributeSyntax,..) of the structure::XmlCrefAttributeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::XmlCrefAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::XmlElementEndTagSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::XmlElementEndTagSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::XmlElementEndTagSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::XmlElementEndTagSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::XmlElementStartTagSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::XmlElementStartTagSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::XmlElementStartTagSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::XmlElementStartTagSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::XmlNodeSyntax,..) of the structure::XmlElementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::XmlElementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::XmlNodeSyntax,..) of the structure::XmlElementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::XmlElementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::XmlNodeSyntax,..) of the structure::XmlEmptyElementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::XmlEmptyElementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::XmlNodeSyntax,..) of the structure::XmlEmptyElementSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::XmlEmptyElementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::XmlAttributeSyntax,..) of the structure::XmlNameAttributeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::XmlNameAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::XmlAttributeSyntax,..) of the structure::XmlNameAttributeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::XmlNameAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::XmlNameSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::XmlNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::XmlNameSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::XmlNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::XmlNodeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::XmlNodeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::XmlNodeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::XmlNodeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::XmlPrefixSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::XmlPrefixSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::XmlPrefixSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::XmlPrefixSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::XmlNodeSyntax,..) of the structure::XmlProcessingInstructionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::XmlProcessingInstructionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::XmlNodeSyntax,..) of the structure::XmlProcessingInstructionSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::XmlProcessingInstructionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::XmlAttributeSyntax,..) of the structure::XmlTextAttributeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::XmlTextAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::XmlAttributeSyntax,..) of the structure::XmlTextAttributeSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::XmlTextAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::XmlNodeSyntax,..) of the structure::XmlTextSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::XmlTextSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::XmlNodeSyntax,..) of the structure::XmlTextSyntax node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::XmlTextSyntax& node , bool callVirtualBase = true);

  }; // VisitorAbstractNodes


}}}
#endif

