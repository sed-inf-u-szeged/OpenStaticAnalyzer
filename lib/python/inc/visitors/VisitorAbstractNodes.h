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

#ifndef _PYTHON_VISITORABSTRACTNODES_H_
#define _PYTHON_VISITORABSTRACTNODES_H_

#include "python/inc/python.h"

/**
* \file VisitorAbstractNodes.h
* \brief Contains declaration of VisitorAbstractNodes class.
*/

namespace columbus { namespace python { namespace asg {
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
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the base::Comment node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const base::Comment& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the base::Comment node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const base::Comment& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the base::Docstring node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const base::Docstring& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the base::Docstring node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const base::Docstring& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the base::Named node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const base::Named& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the base::Named node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const base::Named& node , bool callVirtualBase = true);

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
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the expression::ArgumentList node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ArgumentList& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the expression::ArgumentList node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ArgumentList& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Binary,..) of the expression::AttributeRef node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::AttributeRef& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Binary,..) of the expression::AttributeRef node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::AttributeRef& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::Await node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Await& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::Await node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Await& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::Binary node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Binary& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::Binary node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Binary& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Binary,..) of the expression::BinaryArithmetic node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::BinaryArithmetic& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Binary,..) of the expression::BinaryArithmetic node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::BinaryArithmetic& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Binary,..) of the expression::BinaryLogical node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::BinaryLogical& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Binary,..) of the expression::BinaryLogical node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::BinaryLogical& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Literal,..) of the expression::BytesLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::BytesLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Literal,..) of the expression::BytesLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::BytesLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Unary,..) of the expression::Call node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Call& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Unary,..) of the expression::Call node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Call& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::DictComp node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::DictComp& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::DictComp node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::DictComp& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::Dictionary node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Dictionary& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::Dictionary node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Dictionary& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Slicing,..) of the expression::Ellipsis node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Ellipsis& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Slicing,..) of the expression::Ellipsis node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Ellipsis& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the expression::Expression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Expression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the expression::Expression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Expression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::ExpressionList node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ExpressionList& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::ExpressionList node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ExpressionList& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Slicing,..) of the expression::ExtSlice node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ExtSlice& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Slicing,..) of the expression::ExtSlice node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ExtSlice& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Literal,..) of the expression::FloatNumber node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::FloatNumber& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Literal,..) of the expression::FloatNumber node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::FloatNumber& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Literal,..) of the expression::FormattedValue node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::FormattedValue& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Literal,..) of the expression::FormattedValue node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::FormattedValue& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the expression::Generator node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Generator& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the expression::Generator node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Generator& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::GeneratorExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::GeneratorExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::GeneratorExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::GeneratorExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::Identifier node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Identifier& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::Identifier node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Identifier& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::IfExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::IfExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::IfExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::IfExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Literal,..) of the expression::ImagNumber node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ImagNumber& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Literal,..) of the expression::ImagNumber node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ImagNumber& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Slicing,..) of the expression::Index node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Index& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Slicing,..) of the expression::Index node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Index& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Literal,..) of the expression::IntegerLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::IntegerLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Literal,..) of the expression::IntegerLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::IntegerLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::JoinedStr node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::JoinedStr& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::JoinedStr node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::JoinedStr& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the expression::KeyValue node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::KeyValue& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the expression::KeyValue node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::KeyValue& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the expression::Keyword node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Keyword& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the expression::Keyword node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Keyword& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::Lambda node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Lambda& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::Lambda node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Lambda& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::List node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::List& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::List node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::List& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::ListComp node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ListComp& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::ListComp node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ListComp& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::Literal node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Literal& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::Literal node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Literal& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Literal,..) of the expression::LongInteger node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::LongInteger& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Literal,..) of the expression::LongInteger node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::LongInteger& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::NamedExpr node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::NamedExpr& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::NamedExpr node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::NamedExpr& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::Set node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Set& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::Set node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Set& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::SetComp node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::SetComp& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::SetComp node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::SetComp& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Slicing,..) of the expression::Slice node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Slice& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Slicing,..) of the expression::Slice node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Slice& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Unary,..) of the expression::Slicing node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Slicing& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Unary,..) of the expression::Slicing node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Slicing& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::Starred node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Starred& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::Starred node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Starred& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::StringConversion node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::StringConversion& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::StringConversion node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::StringConversion& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Literal,..) of the expression::StringLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::StringLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Literal,..) of the expression::StringLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::StringLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Unary,..) of the expression::Subscription node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Subscription& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Unary,..) of the expression::Subscription node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Subscription& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::Unary node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Unary& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::Unary node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Unary& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Unary,..) of the expression::UnaryOperation node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::UnaryOperation& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Unary,..) of the expression::UnaryOperation node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::UnaryOperation& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::YieldExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::YieldExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::YieldExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::YieldExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Named,..) of the module::Module node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const module::Module& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Named,..) of the module::Module node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const module::Module& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Base,..) of the module::Object node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const module::Object& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Base,..) of the module::Object node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const module::Object& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Base,..) of the module::Package node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const module::Package& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Base,..) of the module::Package node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const module::Package& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Named,..) of the statement::Alias node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Alias& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Named,..) of the statement::Alias node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Alias& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Assign,..) of the statement::AnnAssign node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::AnnAssign& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Assign,..) of the statement::AnnAssign node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::AnnAssign& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::SimpleStatement,..) of the statement::Assert node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Assert& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::SimpleStatement,..) of the statement::Assert node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Assert& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::SimpleStatement,..) of the statement::Assign node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Assign& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::SimpleStatement,..) of the statement::Assign node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Assign& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Assign,..) of the statement::AugAssign node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::AugAssign& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Assign,..) of the statement::AugAssign node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::AugAssign& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the statement::BaseSpecifier node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::BaseSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the statement::BaseSpecifier node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::BaseSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::SimpleStatement,..) of the statement::Break node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Break& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::SimpleStatement,..) of the statement::Break node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Break& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::CompoundStatement,..) of the statement::ClassDef node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::ClassDef& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::CompoundStatement,..) of the statement::ClassDef node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::ClassDef& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Statement,..) of the statement::CompoundStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::CompoundStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Statement,..) of the statement::CompoundStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::CompoundStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::SimpleStatement,..) of the statement::Continue node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Continue& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::SimpleStatement,..) of the statement::Continue node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Continue& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::SimpleStatement,..) of the statement::Delete node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Delete& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::SimpleStatement,..) of the statement::Delete node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Delete& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::SimpleStatement,..) of the statement::Exec node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Exec& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::SimpleStatement,..) of the statement::Exec node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Exec& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Iteration,..) of the statement::For node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::For& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Iteration,..) of the statement::For node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::For& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::CompoundStatement,..) of the statement::FunctionDef node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::FunctionDef& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::CompoundStatement,..) of the statement::FunctionDef node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::FunctionDef& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::SimpleStatement,..) of the statement::Global node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Global& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::SimpleStatement,..) of the statement::Global node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Global& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the statement::Handler node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Handler& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the statement::Handler node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Handler& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::CompoundStatement,..) of the statement::If node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::If& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::CompoundStatement,..) of the statement::If node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::If& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::ImportStatement,..) of the statement::ImportFrom node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::ImportFrom& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::ImportStatement,..) of the statement::ImportFrom node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::ImportFrom& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::SimpleStatement,..) of the statement::ImportStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::ImportStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::SimpleStatement,..) of the statement::ImportStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::ImportStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::CompoundStatement,..) of the statement::Iteration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Iteration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::CompoundStatement,..) of the statement::Iteration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Iteration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::SimpleStatement,..) of the statement::Nonlocal node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Nonlocal& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::SimpleStatement,..) of the statement::Nonlocal node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Nonlocal& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Named,..) of the statement::Parameter node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Parameter& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Named,..) of the statement::Parameter node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Parameter& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::SimpleStatement,..) of the statement::Pass node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Pass& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::SimpleStatement,..) of the statement::Pass node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Pass& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::SimpleStatement,..) of the statement::Print node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Print& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::SimpleStatement,..) of the statement::Print node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Print& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::SimpleStatement,..) of the statement::Raise node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Raise& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::SimpleStatement,..) of the statement::Raise node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Raise& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::SimpleStatement,..) of the statement::Return node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Return& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::SimpleStatement,..) of the statement::Return node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Return& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Statement,..) of the statement::SimpleStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::SimpleStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Statement,..) of the statement::SimpleStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::SimpleStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the statement::Statement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Statement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the statement::Statement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Statement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the statement::Suite node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Suite& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the statement::Suite node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Suite& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the statement::TargetList node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::TargetList& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the statement::TargetList node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::TargetList& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::CompoundStatement,..) of the statement::Try node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Try& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::CompoundStatement,..) of the statement::Try node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Try& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Iteration,..) of the statement::While node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::While& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Iteration,..) of the statement::While node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::While& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::CompoundStatement,..) of the statement::With node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::With& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::CompoundStatement,..) of the statement::With node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::With& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the statement::WithItem node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::WithItem& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the statement::WithItem node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::WithItem& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::Type,..) of the type::DictType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::DictType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::Type,..) of the type::DictType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::DictType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::Type,..) of the type::ReferenceType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::ReferenceType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::Type,..) of the type::ReferenceType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::ReferenceType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::Type,..) of the type::SequenceType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::SequenceType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::Type,..) of the type::SequenceType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::SequenceType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (type::Type,..) of the type::SimpleType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const type::SimpleType& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (type::Type,..) of the type::SimpleType node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const type::SimpleType& node , bool callVirtualBase = true);

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

  }; // VisitorAbstractNodes


}}}
#endif

