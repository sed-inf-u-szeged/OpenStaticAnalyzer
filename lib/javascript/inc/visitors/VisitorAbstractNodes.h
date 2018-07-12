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

#ifndef _JAVASCRIPT_VISITORABSTRACTNODES_H_
#define _JAVASCRIPT_VISITORABSTRACTNODES_H_

#include "javascript/inc/javascript.h"

/**
* \file VisitorAbstractNodes.h
* \brief Contains declaration of VisitorAbstractNodes class.
*/

namespace columbus { namespace javascript { namespace asg {
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
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Named,..) of the base::Program node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const base::Program& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Named,..) of the base::Program node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const base::Program& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Base,..) of the base::System node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const base::System& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Base,..) of the base::System node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const base::System& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (declaration::Declaration,..) of the declaration::ClassDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const declaration::ClassDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (declaration::Declaration,..) of the declaration::ClassDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const declaration::ClassDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Statement,..) of the declaration::Declaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const declaration::Declaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Statement,..) of the declaration::Declaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const declaration::Declaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (declaration::Declaration,..) of the declaration::ExportAllDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const declaration::ExportAllDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (declaration::Declaration,..) of the declaration::ExportAllDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const declaration::ExportAllDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (declaration::Declaration,..) of the declaration::ExportDefaultDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const declaration::ExportDefaultDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (declaration::Declaration,..) of the declaration::ExportDefaultDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const declaration::ExportDefaultDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (declaration::ModuleDeclaration,..) of the declaration::ExportNamedDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const declaration::ExportNamedDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (declaration::ModuleDeclaration,..) of the declaration::ExportNamedDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const declaration::ExportNamedDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Function,..) of the declaration::FunctionDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const declaration::FunctionDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Function,..) of the declaration::FunctionDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const declaration::FunctionDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (declaration::ModuleDeclaration,..) of the declaration::ImportDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const declaration::ImportDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (declaration::ModuleDeclaration,..) of the declaration::ImportDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const declaration::ImportDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the declaration::ModuleDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const declaration::ModuleDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the declaration::ModuleDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const declaration::ModuleDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (declaration::Declaration,..) of the declaration::VariableDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const declaration::VariableDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (declaration::Declaration,..) of the declaration::VariableDeclaration node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const declaration::VariableDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the declaration::VariableDeclarator node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const declaration::VariableDeclarator& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the declaration::VariableDeclarator node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const declaration::VariableDeclarator& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::ArrayExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ArrayExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::ArrayExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ArrayExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::ArrowFunctionExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ArrowFunctionExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::ArrowFunctionExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ArrowFunctionExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::AssignmentExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::AssignmentExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::AssignmentExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::AssignmentExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Property,..) of the expression::AssignmentProperty node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::AssignmentProperty& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Property,..) of the expression::AssignmentProperty node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::AssignmentProperty& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::AwaitExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::AwaitExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::AwaitExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::AwaitExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::BinaryExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::BinaryExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::BinaryExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::BinaryExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Literal,..) of the expression::BooleanLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::BooleanLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Literal,..) of the expression::BooleanLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::BooleanLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::CallExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::CallExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::CallExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::CallExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::ClassExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ClassExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::ClassExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ClassExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::ConditionalExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ConditionalExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::ConditionalExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ConditionalExpression& node , bool callVirtualBase = true);

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
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::FunctionExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::FunctionExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::FunctionExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::FunctionExpression& node , bool callVirtualBase = true);

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
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the expression::Literal node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Literal& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the expression::Literal node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Literal& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::LogicalExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::LogicalExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::LogicalExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::LogicalExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::MemberExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::MemberExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::MemberExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::MemberExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::MetaProperty node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::MetaProperty& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::MetaProperty node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::MetaProperty& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::NewExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::NewExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::NewExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::NewExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Literal,..) of the expression::NullLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::NullLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Literal,..) of the expression::NullLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::NullLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Literal,..) of the expression::NumberLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::NumberLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Literal,..) of the expression::NumberLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::NumberLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::ObjectExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ObjectExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::ObjectExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ObjectExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the expression::Property node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Property& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the expression::Property node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Property& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Literal,..) of the expression::RegExpLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::RegExpLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Literal,..) of the expression::RegExpLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::RegExpLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::SequenceExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::SequenceExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::SequenceExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::SequenceExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the expression::SpreadElement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::SpreadElement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the expression::SpreadElement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::SpreadElement& node , bool callVirtualBase = true);

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
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the expression::Super node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::Super& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the expression::Super node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::Super& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::TaggedTemplateExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::TaggedTemplateExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::TaggedTemplateExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::TaggedTemplateExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the expression::TemplateElement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::TemplateElement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the expression::TemplateElement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::TemplateElement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::TemplateLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::TemplateLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::TemplateLiteral node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::TemplateLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::ThisExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::ThisExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::ThisExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::ThisExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::UnaryExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::UnaryExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::UnaryExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::UnaryExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (expression::Expression,..) of the expression::UpdateExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const expression::UpdateExpression& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (expression::Expression,..) of the expression::UpdateExpression node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const expression::UpdateExpression& node , bool callVirtualBase = true);

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
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Pattern,..) of the statement::ArrayPattern node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::ArrayPattern& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Pattern,..) of the statement::ArrayPattern node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::ArrayPattern& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Pattern,..) of the statement::AssignmentPattern node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::AssignmentPattern& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Pattern,..) of the statement::AssignmentPattern node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::AssignmentPattern& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Statement,..) of the statement::BlockStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::BlockStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Statement,..) of the statement::BlockStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::BlockStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Statement,..) of the statement::BreakStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::BreakStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Statement,..) of the statement::BreakStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::BreakStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the statement::CatchClause node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::CatchClause& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the statement::CatchClause node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::CatchClause& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Statement,..) of the statement::ContinueStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::ContinueStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Statement,..) of the statement::ContinueStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::ContinueStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Statement,..) of the statement::DebuggerStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::DebuggerStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Statement,..) of the statement::DebuggerStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::DebuggerStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::WhileStatement,..) of the statement::DoWhileStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::DoWhileStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::WhileStatement,..) of the statement::DoWhileStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::DoWhileStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Statement,..) of the statement::EmptyStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::EmptyStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Statement,..) of the statement::EmptyStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::EmptyStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Statement,..) of the statement::ExpressionStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::ExpressionStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Statement,..) of the statement::ExpressionStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::ExpressionStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Statement,..) of the statement::ForInStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::ForInStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Statement,..) of the statement::ForInStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::ForInStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::ForInStatement,..) of the statement::ForOfStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::ForOfStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::ForInStatement,..) of the statement::ForOfStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::ForOfStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Statement,..) of the statement::ForStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::ForStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Statement,..) of the statement::ForStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::ForStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the statement::Function node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Function& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the statement::Function node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Function& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Statement,..) of the statement::IfStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::IfStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Statement,..) of the statement::IfStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::IfStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Statement,..) of the statement::LabeledStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::LabeledStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Statement,..) of the statement::LabeledStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::LabeledStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Pattern,..) of the statement::ObjectPattern node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::ObjectPattern& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Pattern,..) of the statement::ObjectPattern node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::ObjectPattern& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the statement::Pattern node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::Pattern& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the statement::Pattern node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::Pattern& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Pattern,..) of the statement::RestElement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::RestElement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Pattern,..) of the statement::RestElement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::RestElement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Statement,..) of the statement::ReturnStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::ReturnStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Statement,..) of the statement::ReturnStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::ReturnStatement& node , bool callVirtualBase = true);

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
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the statement::SwitchCase node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::SwitchCase& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the statement::SwitchCase node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::SwitchCase& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Statement,..) of the statement::SwitchStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::SwitchStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Statement,..) of the statement::SwitchStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::SwitchStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Statement,..) of the statement::ThrowStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::ThrowStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Statement,..) of the statement::ThrowStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::ThrowStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Statement,..) of the statement::TryStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::TryStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Statement,..) of the statement::TryStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::TryStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Statement,..) of the statement::WhileStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::WhileStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Statement,..) of the statement::WhileStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::WhileStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (statement::Statement,..) of the statement::WithStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const statement::WithStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (statement::Statement,..) of the statement::WithStatement node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const statement::WithStatement& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::Class node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::Class& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::Class node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::Class& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::ClassBody node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ClassBody& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::ClassBody node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ClassBody& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::ModuleSpecifier,..) of the structure::ExportSpecifier node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ExportSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::ModuleSpecifier,..) of the structure::ExportSpecifier node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ExportSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::ModuleSpecifier,..) of the structure::ImpSpecifier node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ImpSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::ModuleSpecifier,..) of the structure::ImpSpecifier node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ImpSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::ImpSpecifier,..) of the structure::ImportDefaultSpecifier node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ImportDefaultSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::ImpSpecifier,..) of the structure::ImportDefaultSpecifier node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ImportDefaultSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::ImpSpecifier,..) of the structure::ImportNamespaceSpecifier node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ImportNamespaceSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::ImpSpecifier,..) of the structure::ImportNamespaceSpecifier node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ImportNamespaceSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (structure::ImpSpecifier,..) of the structure::ImportSpecifier node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ImportSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (structure::ImpSpecifier,..) of the structure::ImportSpecifier node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ImportSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::MethodDefinition node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::MethodDefinition& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::MethodDefinition node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::MethodDefinition& node , bool callVirtualBase = true);

      /**
      * \brief Abstract visitor, which calls the visitor of the base class(es) (base::Positioned,..) of the structure::ModuleSpecifier node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visit(const structure::ModuleSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Abstract end visitor, which calls the end visitor of the base class (base::Positioned,..) of the structure::ModuleSpecifier node.
      * \param node            [in] The node which is visited.
      * \param callVirtualBase [in] This technically flag is help the call a multiple heritage call the virtual base or not.(the none virtual base is called directly).
      */
      virtual void visitEnd(const structure::ModuleSpecifier& node , bool callVirtualBase = true);

  }; // VisitorAbstractNodes


}}}
#endif

