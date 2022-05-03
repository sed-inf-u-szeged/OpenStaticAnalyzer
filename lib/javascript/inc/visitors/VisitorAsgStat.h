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

#ifndef _JAVASCRIPT_VISITORASGSTAT_H_
#define _JAVASCRIPT_VISITORASGSTAT_H_

#include "javascript/inc/javascript.h"

/**
* \file VisitorAsgStat.h
* \brief Contains declaration of VisitorAsgStat class.
*/

namespace columbus { namespace javascript { namespace asg {
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
      * \brief Visitor to create statistics about base::Comment node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Comment& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about base::Named node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Named& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about base::Positioned node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Positioned& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about base::Program node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Program& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about base::System node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::System& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about declaration::ClassDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::ClassDeclaration& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about declaration::Declaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::Declaration& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about declaration::ExportAllDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::ExportAllDeclaration& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about declaration::ExportDefaultDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::ExportDefaultDeclaration& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about declaration::ExportNamedDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::ExportNamedDeclaration& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about declaration::FunctionDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::FunctionDeclaration& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about declaration::ImportDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::ImportDeclaration& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about declaration::ModuleDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::ModuleDeclaration& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about declaration::VariableDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::VariableDeclaration& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about declaration::VariableDeclarator node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::VariableDeclarator& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::ArrayExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ArrayExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::ArrowFunctionExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ArrowFunctionExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::AssignmentExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AssignmentExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::AwaitExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AwaitExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::BigIntLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::BigIntLiteral& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::BinaryExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::BinaryExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::BooleanLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::BooleanLiteral& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::CallExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::CallExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::ChainElement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ChainElement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::ChainExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ChainExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::ClassExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ClassExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::ConditionalExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ConditionalExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::Expression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Expression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::FunctionExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::FunctionExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::Identifier node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Identifier& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::ImportExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ImportExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::Literal node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Literal& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::LogicalExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::LogicalExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::MemberExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::MemberExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::MetaProperty node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::MetaProperty& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::NewExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::NewExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::NullLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::NullLiteral& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::NumberLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::NumberLiteral& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::ObjectExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ObjectExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::PrivateIdentifier node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::PrivateIdentifier& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::Property node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Property& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::RegExpLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::RegExpLiteral& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::SequenceExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::SequenceExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::SpreadElement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::SpreadElement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::StringLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::StringLiteral& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::Super node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Super& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::TaggedTemplateExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::TaggedTemplateExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::TemplateElement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::TemplateElement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::TemplateLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::TemplateLiteral& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::ThisExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ThisExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::UnaryExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::UnaryExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::UpdateExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::UpdateExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about expression::YieldExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::YieldExpression& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::ArrayPattern node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ArrayPattern& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::AssignmentPattern node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::AssignmentPattern& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::BlockStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::BlockStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::BreakStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::BreakStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::CatchClause node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::CatchClause& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::ContinueStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ContinueStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::DebuggerStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::DebuggerStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::DoWhileStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::DoWhileStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::EmptyStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::EmptyStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::ExpressionStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ExpressionStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::ForInStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ForInStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::ForOfStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ForOfStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::ForStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ForStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::Function node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Function& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::IfStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::IfStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::LabeledStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::LabeledStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::ObjectPattern node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ObjectPattern& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::Pattern node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Pattern& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::RestElement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::RestElement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::ReturnStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ReturnStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::Statement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Statement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::SwitchCase node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::SwitchCase& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::SwitchStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::SwitchStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::ThrowStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ThrowStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::TryStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::TryStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::WhileStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::WhileStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about statement::WithStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::WithStatement& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about structure::Class node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::Class& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about structure::ClassBody node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ClassBody& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about structure::ExportSpecifier node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ExportSpecifier& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about structure::ImpSpecifier node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ImpSpecifier& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about structure::ImportDefaultSpecifier node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ImportDefaultSpecifier& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about structure::ImportNamespaceSpecifier node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ImportNamespaceSpecifier& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about structure::ImportSpecifier node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ImportSpecifier& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about structure::MethodDefinition node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::MethodDefinition& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about structure::ModuleSpecifier node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ModuleSpecifier& node,bool callVirtualBase = true);

      /**
      * \brief Visitor to create statistics about structure::PropertyDefinition node.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::PropertyDefinition& node,bool callVirtualBase = true);

      /**
      * \brief Edge visitor for comments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPositioned_Comments(const base::Positioned& begin, const base::Comment& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitProgram_HasBody(const base::Program& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasPrograms edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSystem_HasPrograms(const base::System& begin, const base::Program& end);

      /**
      * \brief Edge  visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportAllDeclaration_HasSource(const declaration::ExportAllDeclaration& begin, const expression::Literal& end);

      /**
      * \brief Edge  visitor for hasExported edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportAllDeclaration_HasExported(const declaration::ExportAllDeclaration& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportDefaultDeclaration_HasDeclaration(const declaration::ExportDefaultDeclaration& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportNamedDeclaration_HasDeclaration(const declaration::ExportNamedDeclaration& begin, const declaration::Declaration& end);

      /**
      * \brief Edge  visitor for hasSpecifiers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportNamedDeclaration_HasSpecifiers(const declaration::ExportNamedDeclaration& begin, const structure::ExportSpecifier& end);

      /**
      * \brief Edge  visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportNamedDeclaration_HasSource(const declaration::ExportNamedDeclaration& begin, const expression::Literal& end);

      /**
      * \brief Edge  visitor for hasSpecifiers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImportDeclaration_HasSpecifiers(const declaration::ImportDeclaration& begin, const structure::ImpSpecifier& end);

      /**
      * \brief Edge  visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImportDeclaration_HasSource(const declaration::ImportDeclaration& begin, const expression::Literal& end);

      /**
      * \brief Edge  visitor for hasDeclarations edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclaration_HasDeclarations(const declaration::VariableDeclaration& begin, const declaration::VariableDeclarator& end);

      /**
      * \brief Edge  visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclarator_HasIdentifier(const declaration::VariableDeclarator& begin, const statement::Pattern& end);

      /**
      * \brief Edge  visitor for hasInit edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclarator_HasInit(const declaration::VariableDeclarator& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasElements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayExpression_HasElements(const expression::ArrayExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentExpression_HasLeft(const expression::AssignmentExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentExpression_HasRight(const expression::AssignmentExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAwaitExpression_HasArgument(const expression::AwaitExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinaryExpression_HasLeft(const expression::BinaryExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinaryExpression_HasRight(const expression::BinaryExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasCallee edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCallExpression_HasCallee(const expression::CallExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCallExpression_HasArguments(const expression::CallExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCallExpression_Calls(const expression::CallExpression& begin, const statement::Function& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitChainExpression_HasExpression(const expression::ChainExpression& begin, const expression::ChainElement& end);

      /**
      * \brief Edge  visitor for hasAlternate edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalExpression_HasAlternate(const expression::ConditionalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasConsequent edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalExpression_HasConsequent(const expression::ConditionalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalExpression_HasTest(const expression::ConditionalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIdentifier_RefersTo(const expression::Identifier& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImportExpression_HasSource(const expression::ImportExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLogicalExpression_HasLeft(const expression::LogicalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLogicalExpression_HasRight(const expression::LogicalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasProperty edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMemberExpression_HasProperty(const expression::MemberExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMemberExpression_HasObject(const expression::MemberExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasMeta edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMetaProperty_HasMeta(const expression::MetaProperty& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasProperty edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMetaProperty_HasProperty(const expression::MetaProperty& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasCallee edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewExpression_HasCallee(const expression::NewExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewExpression_HasArguments(const expression::NewExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewExpression_Calls(const expression::NewExpression& begin, const statement::Function& end);

      /**
      * \brief Edge  visitor for hasProperties edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObjectExpression_HasProperties(const expression::ObjectExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitProperty_HasValue(const expression::Property& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitProperty_HasKey(const expression::Property& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpressions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSequenceExpression_HasExpressions(const expression::SequenceExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSpreadElement_HasArgument(const expression::SpreadElement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTaggedTemplateExpression_HasTag(const expression::TaggedTemplateExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasQuasi edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTaggedTemplateExpression_HasQuasi(const expression::TaggedTemplateExpression& begin, const expression::TemplateLiteral& end);

      /**
      * \brief Edge  visitor for hasQuasis edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTemplateLiteral_HasQuasis(const expression::TemplateLiteral& begin, const expression::TemplateElement& end);

      /**
      * \brief Edge  visitor for hasExpressions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTemplateLiteral_HasExpressions(const expression::TemplateLiteral& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUnaryExpression_HasArgument(const expression::UnaryExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUpdateExpression_HasArgument(const expression::UpdateExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitYieldExpression_HasArgument(const expression::YieldExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasElements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayPattern_HasElements(const statement::ArrayPattern& begin, const statement::Pattern& end);

      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentPattern_HasLeft(const statement::AssignmentPattern& begin, const statement::Pattern& end);

      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentPattern_HasRight(const statement::AssignmentPattern& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBlockStatement_HasBody(const statement::BlockStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasLabel edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBreakStatement_HasLabel(const statement::BreakStatement& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasParam edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchClause_HasParam(const statement::CatchClause& begin, const statement::Pattern& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchClause_HasBody(const statement::CatchClause& begin, const statement::BlockStatement& end);

      /**
      * \brief Edge  visitor for hasLabel edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitContinueStatement_HasLabel(const statement::ContinueStatement& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExpressionStatement_HasExpression(const statement::ExpressionStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForInStatement_HasRight(const statement::ForInStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForInStatement_HasBody(const statement::ForInStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForInStatement_HasLeft(const statement::ForInStatement& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatement_HasBody(const statement::ForStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatement_HasTest(const statement::ForStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasUpdate edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatement_HasUpdate(const statement::ForStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasInit edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatement_HasInit(const statement::ForStatement& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasParams edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunction_HasParams(const statement::Function& begin, const statement::Pattern& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunction_HasBody(const statement::Function& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunction_HasIdentifier(const statement::Function& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfStatement_HasTest(const statement::IfStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasConsequent edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfStatement_HasConsequent(const statement::IfStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasAlternate edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfStatement_HasAlternate(const statement::IfStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasLabel edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLabeledStatement_HasLabel(const statement::LabeledStatement& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLabeledStatement_HasBody(const statement::LabeledStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasProperties edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObjectPattern_HasProperties(const statement::ObjectPattern& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitRestElement_HasArgument(const statement::RestElement& begin, const statement::Pattern& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitReturnStatement_HasArgument(const statement::ReturnStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchCase_HasTest(const statement::SwitchCase& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasConsequent edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchCase_HasConsequent(const statement::SwitchCase& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasDiscriminant edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchStatement_HasDiscriminant(const statement::SwitchStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasCases edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchStatement_HasCases(const statement::SwitchStatement& begin, const statement::SwitchCase& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitThrowStatement_HasArgument(const statement::ThrowStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryStatement_HasBlock(const statement::TryStatement& begin, const statement::BlockStatement& end);

      /**
      * \brief Edge  visitor for hasFinalizer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryStatement_HasFinalizer(const statement::TryStatement& begin, const statement::BlockStatement& end);

      /**
      * \brief Edge  visitor for hasHandler edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryStatement_HasHandler(const statement::TryStatement& begin, const statement::CatchClause& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhileStatement_HasBody(const statement::WhileStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhileStatement_HasTest(const statement::WhileStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWithStatement_HasObject(const statement::WithStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWithStatement_HasBody(const statement::WithStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClass_HasBody(const structure::Class& begin, const structure::ClassBody& end);

      /**
      * \brief Edge  visitor for hasSuperClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClass_HasSuperClass(const structure::Class& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClass_HasIdentifier(const structure::Class& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassBody_HasBody(const structure::ClassBody& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasExported edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportSpecifier_HasExported(const structure::ExportSpecifier& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasImported edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImportSpecifier_HasImported(const structure::ImportSpecifier& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDefinition_HasKey(const structure::MethodDefinition& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDefinition_HasValue(const structure::MethodDefinition& begin, const expression::FunctionExpression& end);

      /**
      * \brief Edge  visitor for hasLocal edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitModuleSpecifier_HasLocal(const structure::ModuleSpecifier& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPropertyDefinition_HasKey(const structure::PropertyDefinition& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPropertyDefinition_HasValue(const structure::PropertyDefinition& begin, const expression::Expression& end);

    protected:
      /** \internal \brief Contains statistics about nodes. */
      unsigned int nodeStatSimple[91];

      /** \internal \brief Contains statistics about nodes (where the node is counted in all parents statistic). */
      unsigned int nodeStatParent[91];

      /** \internal \brief Contains statistics about edges. */
      unsigned int edgeStat[100];

      friend class Factory;

      /** \internal \brief Contains the scoped names of the nodes. */
      static const char* nodeNames[];
      /** \internal \brief Contains the size of the nodes. */
      static const unsigned short nodeSizes[];
  }; // Visitor


}}}
#endif

