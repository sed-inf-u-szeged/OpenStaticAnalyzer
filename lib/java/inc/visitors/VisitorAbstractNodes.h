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

#ifndef _JAVA_VISITORABSTRACTNODES_H_
#define _JAVA_VISITORABSTRACTNODES_H_

#include "java/inc/java.h"

/**
* \file VisitorAbstractNodes.h
* \brief Contains declaration of VisitorAbstractNodes class.
*/

namespace columbus { namespace java { namespace asg {
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
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::NonJavadocComment,..) of the base::BlockComment node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const base::BlockComment& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::NonJavadocComment,..) of the base::BlockComment node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const base::BlockComment& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::PositionedWithoutComment,..) of the base::Comment node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const base::Comment& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::PositionedWithoutComment,..) of the base::Comment node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const base::Comment& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Base,..) of the base::Commentable node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const base::Commentable& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Base,..) of the base::Commentable node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const base::Commentable& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Comment,..) of the base::JavadocComment node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const base::JavadocComment& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Comment,..) of the base::JavadocComment node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const base::JavadocComment& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::NonJavadocComment,..) of the base::LineComment node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const base::LineComment& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::NonJavadocComment,..) of the base::LineComment node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const base::LineComment& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Base,..) of the base::Named node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const base::Named& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Base,..) of the base::Named node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const base::Named& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Comment,..) of the base::NonJavadocComment node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const base::NonJavadocComment& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Comment,..) of the base::NonJavadocComment node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const base::NonJavadocComment& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Commentable,..) of the base::Positioned node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const base::Positioned& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Commentable,..) of the base::Positioned node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const base::Positioned& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Base,..) of the base::PositionedWithoutComment node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const base::PositionedWithoutComment& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Base,..) of the base::PositionedWithoutComment node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const base::PositionedWithoutComment& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Expression,..) of the expr::Annotation node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::Annotation& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Expression,..) of the expr::Annotation node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::Annotation& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Binary,..) of the expr::ArrayAccess node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::ArrayAccess& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Binary,..) of the expr::ArrayAccess node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::ArrayAccess& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::TypeExpression,..) of the expr::ArrayTypeExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::ArrayTypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::TypeExpression,..) of the expr::ArrayTypeExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::ArrayTypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Binary,..) of the expr::Assignment node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::Assignment& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Binary,..) of the expr::Assignment node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::Assignment& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Expression,..) of the expr::Binary node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::Binary& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Expression,..) of the expr::Binary node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::Binary& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Literal,..) of the expr::BooleanLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::BooleanLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Literal,..) of the expr::BooleanLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::BooleanLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Literal,..) of the expr::CharacterLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::CharacterLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Literal,..) of the expr::CharacterLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::CharacterLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Literal,..) of the expr::ClassLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::ClassLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Literal,..) of the expr::ClassLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::ClassLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Expression,..) of the expr::Conditional node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::Conditional& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Expression,..) of the expr::Conditional node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::Conditional& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::NumberLiteral,..) of the expr::DoubleLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::DoubleLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::NumberLiteral,..) of the expr::DoubleLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::DoubleLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Expression,..) of the expr::Erroneous node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::Erroneous& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Expression,..) of the expr::Erroneous node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::Erroneous& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::TypeExpression,..) of the expr::ErroneousTypeExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::ErroneousTypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::TypeExpression,..) of the expr::ErroneousTypeExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::ErroneousTypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the expr::Expression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::Expression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the expr::Expression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::Expression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::TypeExpression,..) of the expr::ExternalTypeExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::ExternalTypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::TypeExpression,..) of the expr::ExternalTypeExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::ExternalTypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Binary,..) of the expr::FieldAccess node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::FieldAccess& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Binary,..) of the expr::FieldAccess node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::FieldAccess& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::NumberLiteral,..) of the expr::FloatLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::FloatLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::NumberLiteral,..) of the expr::FloatLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::FloatLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Expression,..) of the expr::Identifier node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::Identifier& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Expression,..) of the expr::Identifier node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::Identifier& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Binary,..) of the expr::InfixExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::InfixExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Binary,..) of the expr::InfixExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::InfixExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Unary,..) of the expr::InstanceOf node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::InstanceOf& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Unary,..) of the expr::InstanceOf node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::InstanceOf& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::NumberLiteral,..) of the expr::IntegerLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::IntegerLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::NumberLiteral,..) of the expr::IntegerLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::IntegerLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Expression,..) of the expr::Literal node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::Literal& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Expression,..) of the expr::Literal node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::Literal& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::NumberLiteral,..) of the expr::LongLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::LongLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::NumberLiteral,..) of the expr::LongLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::LongLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Annotation,..) of the expr::MarkerAnnotation node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::MarkerAnnotation& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Annotation,..) of the expr::MarkerAnnotation node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::MarkerAnnotation& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Unary,..) of the expr::MethodInvocation node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::MethodInvocation& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Unary,..) of the expr::MethodInvocation node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::MethodInvocation& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Expression,..) of the expr::NewArray node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::NewArray& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Expression,..) of the expr::NewArray node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::NewArray& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Expression,..) of the expr::NewClass node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::NewClass& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Expression,..) of the expr::NewClass node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::NewClass& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Annotation,..) of the expr::NormalAnnotation node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::NormalAnnotation& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Annotation,..) of the expr::NormalAnnotation node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::NormalAnnotation& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Literal,..) of the expr::NullLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::NullLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Literal,..) of the expr::NullLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::NullLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Literal,..) of the expr::NumberLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::NumberLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Literal,..) of the expr::NumberLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::NumberLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Unary,..) of the expr::ParenthesizedExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::ParenthesizedExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Unary,..) of the expr::ParenthesizedExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::ParenthesizedExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Unary,..) of the expr::PostfixExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::PostfixExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Unary,..) of the expr::PostfixExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::PostfixExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Unary,..) of the expr::PrefixExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::PrefixExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Unary,..) of the expr::PrefixExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::PrefixExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::TypeExpression,..) of the expr::PrimitiveTypeExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::PrimitiveTypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::TypeExpression,..) of the expr::PrimitiveTypeExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::PrimitiveTypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::TypeExpression,..) of the expr::QualifiedTypeExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::QualifiedTypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::TypeExpression,..) of the expr::QualifiedTypeExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::QualifiedTypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::TypeExpression,..) of the expr::SimpleTypeExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::SimpleTypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::TypeExpression,..) of the expr::SimpleTypeExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::SimpleTypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Annotation,..) of the expr::SingleElementAnnotation node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::SingleElementAnnotation& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Annotation,..) of the expr::SingleElementAnnotation node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::SingleElementAnnotation& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Literal,..) of the expr::StringLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::StringLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Literal,..) of the expr::StringLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::StringLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Expression,..) of the expr::Super node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::Super& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Expression,..) of the expr::Super node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::Super& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Expression,..) of the expr::This node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::This& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Expression,..) of the expr::This node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::This& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::TypeExpression,..) of the expr::TypeApplyExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::TypeApplyExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::TypeExpression,..) of the expr::TypeApplyExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::TypeApplyExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Unary,..) of the expr::TypeCast node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::TypeCast& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Unary,..) of the expr::TypeCast node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::TypeCast& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Expression,..) of the expr::TypeExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::TypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Expression,..) of the expr::TypeExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::TypeExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::TypeExpression,..) of the expr::TypeUnionExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::TypeUnionExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::TypeExpression,..) of the expr::TypeUnionExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::TypeUnionExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::Expression,..) of the expr::Unary node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::Unary& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::Expression,..) of the expr::Unary node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::Unary& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expr::TypeExpression,..) of the expr::WildcardExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expr::WildcardExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expr::TypeExpression,..) of the expr::WildcardExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expr::WildcardExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::Statement,..) of the statm::Assert node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::Assert& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::Statement,..) of the statm::Assert node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::Assert& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::For,..) of the statm::BasicFor node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::BasicFor& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::For,..) of the statm::BasicFor node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::BasicFor& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::Statement,..) of the statm::Block node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::Block& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::Statement,..) of the statm::Block node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::Block& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::Jump,..) of the statm::Break node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::Break& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::Jump,..) of the statm::Break node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::Break& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::SwitchLabel,..) of the statm::Case node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::Case& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::SwitchLabel,..) of the statm::Case node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::Case& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::Jump,..) of the statm::Continue node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::Continue& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::Jump,..) of the statm::Continue node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::Continue& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::SwitchLabel,..) of the statm::Default node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::Default& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::SwitchLabel,..) of the statm::Default node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::Default& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::Iteration,..) of the statm::Do node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::Do& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::Iteration,..) of the statm::Do node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::Do& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::Statement,..) of the statm::Empty node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::Empty& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::Statement,..) of the statm::Empty node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::Empty& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::For,..) of the statm::EnhancedFor node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::EnhancedFor& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::For,..) of the statm::EnhancedFor node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::EnhancedFor& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::Statement,..) of the statm::ExpressionStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::ExpressionStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::Statement,..) of the statm::ExpressionStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::ExpressionStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::Iteration,..) of the statm::For node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::For& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::Iteration,..) of the statm::For node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::For& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the statm::Handler node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::Handler& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the statm::Handler node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::Handler& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::Selection,..) of the statm::If node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::If& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::Selection,..) of the statm::If node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::If& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::Statement,..) of the statm::Iteration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::Iteration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::Statement,..) of the statm::Iteration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::Iteration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::Statement,..) of the statm::Jump node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::Jump& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::Statement,..) of the statm::Jump node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::Jump& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::Statement,..) of the statm::LabeledStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::LabeledStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::Statement,..) of the statm::LabeledStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::LabeledStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::Statement,..) of the statm::Return node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::Return& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::Statement,..) of the statm::Return node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::Return& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::Statement,..) of the statm::Selection node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::Selection& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::Statement,..) of the statm::Selection node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::Selection& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the statm::Statement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::Statement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the statm::Statement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::Statement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::Selection,..) of the statm::Switch node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::Switch& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::Selection,..) of the statm::Switch node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::Switch& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the statm::SwitchLabel node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::SwitchLabel& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the statm::SwitchLabel node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::SwitchLabel& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::Statement,..) of the statm::Synchronized node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::Synchronized& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::Statement,..) of the statm::Synchronized node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::Synchronized& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::Statement,..) of the statm::Throw node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::Throw& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::Statement,..) of the statm::Throw node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::Throw& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::Statement,..) of the statm::Try node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::Try& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::Statement,..) of the statm::Try node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::Try& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statm::Iteration,..) of the statm::While node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statm::While& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statm::Iteration,..) of the statm::While node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statm::While& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Base,..) of the struc::AnnotatedElement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::AnnotatedElement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Base,..) of the struc::AnnotatedElement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::AnnotatedElement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::TypeDeclaration,..) of the struc::AnnotationType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::AnnotationType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::TypeDeclaration,..) of the struc::AnnotationType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::AnnotationType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::MethodDeclaration,..) of the struc::AnnotationTypeElement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::AnnotationTypeElement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::MethodDeclaration,..) of the struc::AnnotationTypeElement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::AnnotationTypeElement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::ClassDeclaration,..) of the struc::AnonymousClass node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::AnonymousClass& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::ClassDeclaration,..) of the struc::AnonymousClass node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::AnonymousClass& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::ClassDeclaration,..) of the struc::Class node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::Class& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::ClassDeclaration,..) of the struc::Class node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::Class& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::TypeDeclaration,..) of the struc::ClassDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::ClassDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::TypeDeclaration,..) of the struc::ClassDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::ClassDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::ClassDeclaration,..) of the struc::ClassGeneric node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::ClassGeneric& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::ClassDeclaration,..) of the struc::ClassGeneric node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::ClassGeneric& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::PositionedWithoutComment,..) of the struc::CompilationUnit node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::CompilationUnit& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::PositionedWithoutComment,..) of the struc::CompilationUnit node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::CompilationUnit& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::Member,..) of the struc::Declaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::Declaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::Member,..) of the struc::Declaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::Declaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::TypeDeclaration,..) of the struc::Enum node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::Enum& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::TypeDeclaration,..) of the struc::Enum node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::Enum& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::VariableDeclaration,..) of the struc::EnumConstant node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::EnumConstant& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::VariableDeclaration,..) of the struc::EnumConstant node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::EnumConstant& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Base,..) of the struc::GenericDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::GenericDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Base,..) of the struc::GenericDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::GenericDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the struc::Import node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::Import& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the struc::Import node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::Import& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::Declaration,..) of the struc::InitializerBlock node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::InitializerBlock& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::Declaration,..) of the struc::InitializerBlock node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::InitializerBlock& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::InitializerBlock,..) of the struc::InstanceInitializerBlock node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::InstanceInitializerBlock& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::InitializerBlock,..) of the struc::InstanceInitializerBlock node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::InstanceInitializerBlock& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::InterfaceDeclaration,..) of the struc::Interface node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::Interface& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::InterfaceDeclaration,..) of the struc::Interface node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::Interface& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::TypeDeclaration,..) of the struc::InterfaceDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::InterfaceDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::TypeDeclaration,..) of the struc::InterfaceDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::InterfaceDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::InterfaceDeclaration,..) of the struc::InterfaceGeneric node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::InterfaceGeneric& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::InterfaceDeclaration,..) of the struc::InterfaceGeneric node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::InterfaceGeneric& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Commentable,..) of the struc::Member node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::Member& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Commentable,..) of the struc::Member node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::Member& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::NormalMethod,..) of the struc::Method node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::Method& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::NormalMethod,..) of the struc::Method node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::Method& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::NamedDeclaration,..) of the struc::MethodDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::MethodDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::NamedDeclaration,..) of the struc::MethodDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::MethodDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::NormalMethod,..) of the struc::MethodGeneric node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::MethodGeneric& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::NormalMethod,..) of the struc::MethodGeneric node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::MethodGeneric& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::Declaration,..) of the struc::NamedDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::NamedDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::Declaration,..) of the struc::NamedDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::NamedDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::MethodDeclaration,..) of the struc::NormalMethod node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::NormalMethod& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::MethodDeclaration,..) of the struc::NormalMethod node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::NormalMethod& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Named,..) of the struc::Package node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::Package& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Named,..) of the struc::Package node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::Package& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the struc::PackageDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::PackageDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the struc::PackageDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::PackageDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::VariableDeclaration,..) of the struc::Parameter node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::Parameter& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::VariableDeclaration,..) of the struc::Parameter node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::Parameter& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::Member,..) of the struc::Scope node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::Scope& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::Member,..) of the struc::Scope node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::Scope& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::InitializerBlock,..) of the struc::StaticInitializerBlock node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::StaticInitializerBlock& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::InitializerBlock,..) of the struc::StaticInitializerBlock node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::StaticInitializerBlock& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::NamedDeclaration,..) of the struc::TypeDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::TypeDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::NamedDeclaration,..) of the struc::TypeDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::TypeDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the struc::TypeParameter node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::TypeParameter& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the struc::TypeParameter node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::TypeParameter& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::VariableDeclaration,..) of the struc::Variable node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::Variable& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::VariableDeclaration,..) of the struc::Variable node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::Variable& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (struc::NamedDeclaration,..) of the struc::VariableDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const struc::VariableDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (struc::NamedDeclaration,..) of the struc::VariableDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const struc::VariableDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::Type,..) of the type::ArrayType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::ArrayType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::Type,..) of the type::ArrayType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::ArrayType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::PrimitiveType,..) of the type::BooleanType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::BooleanType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::PrimitiveType,..) of the type::BooleanType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::BooleanType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::WildcardType,..) of the type::BoundedWildcardType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::BoundedWildcardType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::WildcardType,..) of the type::BoundedWildcardType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::BoundedWildcardType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::PrimitiveType,..) of the type::ByteType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::ByteType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::PrimitiveType,..) of the type::ByteType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::ByteType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::PrimitiveType,..) of the type::CharType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::CharType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::PrimitiveType,..) of the type::CharType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::CharType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::ScopedType,..) of the type::ClassType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::ClassType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::ScopedType,..) of the type::ClassType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::ClassType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::PrimitiveType,..) of the type::DoubleType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::DoubleType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::PrimitiveType,..) of the type::DoubleType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::DoubleType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::Type,..) of the type::ErrorType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::ErrorType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::Type,..) of the type::ErrorType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::ErrorType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::PrimitiveType,..) of the type::FloatType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::FloatType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::PrimitiveType,..) of the type::FloatType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::FloatType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::PrimitiveType,..) of the type::IntType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::IntType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::PrimitiveType,..) of the type::IntType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::IntType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::PrimitiveType,..) of the type::LongType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::LongType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::PrimitiveType,..) of the type::LongType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::LongType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::BoundedWildcardType,..) of the type::LowerBoundedWildcardType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::LowerBoundedWildcardType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::BoundedWildcardType,..) of the type::LowerBoundedWildcardType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::LowerBoundedWildcardType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::Type,..) of the type::MethodType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::MethodType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::Type,..) of the type::MethodType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::MethodType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::Type,..) of the type::NoType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::NoType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::Type,..) of the type::NoType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::NoType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::Type,..) of the type::NullType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::NullType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::Type,..) of the type::NullType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::NullType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::Type,..) of the type::PackageType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::PackageType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::Type,..) of the type::PackageType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::PackageType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::ScopedType,..) of the type::ParameterizedType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::ParameterizedType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::ScopedType,..) of the type::ParameterizedType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::ParameterizedType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::Type,..) of the type::PrimitiveType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::PrimitiveType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::Type,..) of the type::PrimitiveType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::PrimitiveType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::Type,..) of the type::ScopedType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::ScopedType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::Type,..) of the type::ScopedType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::ScopedType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::PrimitiveType,..) of the type::ShortType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::ShortType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::PrimitiveType,..) of the type::ShortType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::ShortType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Base,..) of the type::Type node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::Type& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Base,..) of the type::Type node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::Type& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::Type,..) of the type::TypeVariable node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::TypeVariable& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::Type,..) of the type::TypeVariable node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::TypeVariable& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::WildcardType,..) of the type::UnboundedWildcardType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::UnboundedWildcardType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::WildcardType,..) of the type::UnboundedWildcardType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::UnboundedWildcardType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::Type,..) of the type::UnionType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::UnionType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::Type,..) of the type::UnionType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::UnionType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::BoundedWildcardType,..) of the type::UpperBoundedWildcardType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::UpperBoundedWildcardType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::BoundedWildcardType,..) of the type::UpperBoundedWildcardType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::UpperBoundedWildcardType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::PrimitiveType,..) of the type::VoidType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::VoidType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::PrimitiveType,..) of the type::VoidType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::VoidType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::Type,..) of the type::WildcardType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::WildcardType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::Type,..) of the type::WildcardType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::WildcardType& node , bool callVirtualBase = true);

  }; // VisitorAbstractNodes


}}}
#endif

