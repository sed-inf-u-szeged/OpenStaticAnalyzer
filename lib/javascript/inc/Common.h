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

#ifndef _JAVASCRIPT_Common_H_
#define _JAVASCRIPT_Common_H_

#include "javascript/inc/javascript.h"

/**
* \file Common.h
* \brief Contains declaration of Common namespace.
*/

namespace columbus { namespace javascript { namespace asg {
  typedef unsigned int NodeHashType;
  /**
  * \brief Common contains general graph algorithms and common functions
  */
  namespace Common {
      /**
      * \brief Decides whether the node is base::Comment or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::Comment.
      */
      bool getIsComment(const base::Base& node);

      /**
      * \brief Decides whether the node is base::Named or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::Named.
      */
      bool getIsNamed(const base::Base& node);

      /**
      * \brief Decides whether the node is base::Positioned or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::Positioned.
      */
      bool getIsPositioned(const base::Base& node);

      /**
      * \brief Decides whether the node is base::Program or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::Program.
      */
      bool getIsProgram(const base::Base& node);

      /**
      * \brief Decides whether the node is base::System or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::System.
      */
      bool getIsSystem(const base::Base& node);

      /**
      * \brief Decides whether the node is declaration::ClassDeclaration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is declaration::ClassDeclaration.
      */
      bool getIsClassDeclaration(const base::Base& node);

      /**
      * \brief Decides whether the node is declaration::Declaration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is declaration::Declaration.
      */
      bool getIsDeclaration(const base::Base& node);

      /**
      * \brief Decides whether the node is declaration::ExportAllDeclaration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is declaration::ExportAllDeclaration.
      */
      bool getIsExportAllDeclaration(const base::Base& node);

      /**
      * \brief Decides whether the node is declaration::ExportDefaultDeclaration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is declaration::ExportDefaultDeclaration.
      */
      bool getIsExportDefaultDeclaration(const base::Base& node);

      /**
      * \brief Decides whether the node is declaration::ExportNamedDeclaration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is declaration::ExportNamedDeclaration.
      */
      bool getIsExportNamedDeclaration(const base::Base& node);

      /**
      * \brief Decides whether the node is declaration::FunctionDeclaration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is declaration::FunctionDeclaration.
      */
      bool getIsFunctionDeclaration(const base::Base& node);

      /**
      * \brief Decides whether the node is declaration::ImportDeclaration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is declaration::ImportDeclaration.
      */
      bool getIsImportDeclaration(const base::Base& node);

      /**
      * \brief Decides whether the node is declaration::ModuleDeclaration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is declaration::ModuleDeclaration.
      */
      bool getIsModuleDeclaration(const base::Base& node);

      /**
      * \brief Decides whether the node is declaration::VariableDeclaration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is declaration::VariableDeclaration.
      */
      bool getIsVariableDeclaration(const base::Base& node);

      /**
      * \brief Decides whether the node is declaration::VariableDeclarator or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is declaration::VariableDeclarator.
      */
      bool getIsVariableDeclarator(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ArrayExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ArrayExpression.
      */
      bool getIsArrayExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ArrowFunctionExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ArrowFunctionExpression.
      */
      bool getIsArrowFunctionExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::AssignmentExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::AssignmentExpression.
      */
      bool getIsAssignmentExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::AssignmentProperty or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::AssignmentProperty.
      */
      bool getIsAssignmentProperty(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::AwaitExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::AwaitExpression.
      */
      bool getIsAwaitExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::BinaryExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::BinaryExpression.
      */
      bool getIsBinaryExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::BooleanLiteral or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::BooleanLiteral.
      */
      bool getIsBooleanLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::CallExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::CallExpression.
      */
      bool getIsCallExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ClassExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ClassExpression.
      */
      bool getIsClassExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ConditionalExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ConditionalExpression.
      */
      bool getIsConditionalExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Expression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Expression.
      */
      bool getIsExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::FunctionExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::FunctionExpression.
      */
      bool getIsFunctionExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Identifier or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Identifier.
      */
      bool getIsIdentifier(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Literal or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Literal.
      */
      bool getIsLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::LogicalExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::LogicalExpression.
      */
      bool getIsLogicalExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::MemberExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::MemberExpression.
      */
      bool getIsMemberExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::MetaProperty or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::MetaProperty.
      */
      bool getIsMetaProperty(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::NewExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::NewExpression.
      */
      bool getIsNewExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::NullLiteral or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::NullLiteral.
      */
      bool getIsNullLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::NumberLiteral or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::NumberLiteral.
      */
      bool getIsNumberLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ObjectExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ObjectExpression.
      */
      bool getIsObjectExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Property or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Property.
      */
      bool getIsProperty(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::RegExpLiteral or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::RegExpLiteral.
      */
      bool getIsRegExpLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::SequenceExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::SequenceExpression.
      */
      bool getIsSequenceExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::SpreadElement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::SpreadElement.
      */
      bool getIsSpreadElement(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::StringLiteral or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::StringLiteral.
      */
      bool getIsStringLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Super or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Super.
      */
      bool getIsSuper(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::TaggedTemplateExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::TaggedTemplateExpression.
      */
      bool getIsTaggedTemplateExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::TemplateElement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::TemplateElement.
      */
      bool getIsTemplateElement(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::TemplateLiteral or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::TemplateLiteral.
      */
      bool getIsTemplateLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ThisExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ThisExpression.
      */
      bool getIsThisExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::UnaryExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::UnaryExpression.
      */
      bool getIsUnaryExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::UpdateExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::UpdateExpression.
      */
      bool getIsUpdateExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::YieldExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::YieldExpression.
      */
      bool getIsYieldExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::ArrayPattern or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::ArrayPattern.
      */
      bool getIsArrayPattern(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::AssignmentPattern or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::AssignmentPattern.
      */
      bool getIsAssignmentPattern(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::BlockStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::BlockStatement.
      */
      bool getIsBlockStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::BreakStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::BreakStatement.
      */
      bool getIsBreakStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::CatchClause or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::CatchClause.
      */
      bool getIsCatchClause(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::ContinueStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::ContinueStatement.
      */
      bool getIsContinueStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::DebuggerStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::DebuggerStatement.
      */
      bool getIsDebuggerStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::DoWhileStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::DoWhileStatement.
      */
      bool getIsDoWhileStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::EmptyStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::EmptyStatement.
      */
      bool getIsEmptyStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::ExpressionStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::ExpressionStatement.
      */
      bool getIsExpressionStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::ForInStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::ForInStatement.
      */
      bool getIsForInStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::ForOfStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::ForOfStatement.
      */
      bool getIsForOfStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::ForStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::ForStatement.
      */
      bool getIsForStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Function or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Function.
      */
      bool getIsFunction(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::IfStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::IfStatement.
      */
      bool getIsIfStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::LabeledStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::LabeledStatement.
      */
      bool getIsLabeledStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::ObjectPattern or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::ObjectPattern.
      */
      bool getIsObjectPattern(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Pattern or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Pattern.
      */
      bool getIsPattern(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::RestElement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::RestElement.
      */
      bool getIsRestElement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::ReturnStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::ReturnStatement.
      */
      bool getIsReturnStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Statement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Statement.
      */
      bool getIsStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::SwitchCase or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::SwitchCase.
      */
      bool getIsSwitchCase(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::SwitchStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::SwitchStatement.
      */
      bool getIsSwitchStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::ThrowStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::ThrowStatement.
      */
      bool getIsThrowStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::TryStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::TryStatement.
      */
      bool getIsTryStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::WhileStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::WhileStatement.
      */
      bool getIsWhileStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::WithStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::WithStatement.
      */
      bool getIsWithStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::Class or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::Class.
      */
      bool getIsClass(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ClassBody or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ClassBody.
      */
      bool getIsClassBody(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ExportSpecifier or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ExportSpecifier.
      */
      bool getIsExportSpecifier(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ImpSpecifier or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ImpSpecifier.
      */
      bool getIsImpSpecifier(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ImportDefaultSpecifier or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ImportDefaultSpecifier.
      */
      bool getIsImportDefaultSpecifier(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ImportNamespaceSpecifier or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ImportNamespaceSpecifier.
      */
      bool getIsImportNamespaceSpecifier(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ImportSpecifier or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ImportSpecifier.
      */
      bool getIsImportSpecifier(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::MethodDefinition or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::MethodDefinition.
      */
      bool getIsMethodDefinition(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ModuleSpecifier or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ModuleSpecifier.
      */
      bool getIsModuleSpecifier(const base::Base& node);

      /**
      * \brief Decides whether the 'base' is one of the base kinds (transitive) of 'what'.
      * \param what [in] The examined node kind.
      * \param base [in] The base node kind.
      * \return Returns true if 'base' is a base kind of 'what'.
      */
      bool getIsBaseClassKind(NodeKind what, NodeKind base);

      /**
      * \brief Decides whether the node is composite or not.
      * \param node [in] The node which is being examined.
      * \return Returns true if the node is composite.
      */
      bool getIsComposite(const base::Base& node);

      /**
      * \brief Decides whether the node is composite or not.
      * \param node [in] The node which is being examined.
      * \return Returns true if the node is not composite.
      */
      bool getIsNotComposite(const base::Base& node);

      /**
      * \brief Gives back the string representation of the NodeId.
      * \param nodeId [in] The NodeId.
      * \return The string representation of the nodeId given in the parameter.
      */
      const std::string toString(NodeId nodeId);

      /**
      * \brief Gives back the string representation of the AssignmentOperator kind.
      * \param kind                [in] The AssignmentOperator.
      * \throw JavaScriptException If the kind is not "valid" JavaScriptException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(AssignmentOperator kind);

      /**
      * \brief Gives back the string representation of the BinaryOperator kind.
      * \param kind                [in] The BinaryOperator.
      * \throw JavaScriptException If the kind is not "valid" JavaScriptException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(BinaryOperator kind);

      /**
      * \brief Gives back the string representation of the CommentLocation kind.
      * \param kind                [in] The CommentLocation.
      * \throw JavaScriptException If the kind is not "valid" JavaScriptException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(CommentLocation kind);

      /**
      * \brief Gives back the string representation of the CommentType kind.
      * \param kind                [in] The CommentType.
      * \throw JavaScriptException If the kind is not "valid" JavaScriptException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(CommentType kind);

      /**
      * \brief Gives back the string representation of the DeclarationKind kind.
      * \param kind                [in] The DeclarationKind.
      * \throw JavaScriptException If the kind is not "valid" JavaScriptException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(DeclarationKind kind);

      /**
      * \brief Gives back the string representation of the LogicalOperator kind.
      * \param kind                [in] The LogicalOperator.
      * \throw JavaScriptException If the kind is not "valid" JavaScriptException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(LogicalOperator kind);

      /**
      * \brief Gives back the string representation of the MethodDefinitionKind kind.
      * \param kind                [in] The MethodDefinitionKind.
      * \throw JavaScriptException If the kind is not "valid" JavaScriptException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(MethodDefinitionKind kind);

      /**
      * \brief Gives back the string representation of the ProgramSourceType kind.
      * \param kind                [in] The ProgramSourceType.
      * \throw JavaScriptException If the kind is not "valid" JavaScriptException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(ProgramSourceType kind);

      /**
      * \brief Gives back the string representation of the PropertyKind kind.
      * \param kind                [in] The PropertyKind.
      * \throw JavaScriptException If the kind is not "valid" JavaScriptException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(PropertyKind kind);

      /**
      * \brief Gives back the string representation of the UnaryOperator kind.
      * \param kind                [in] The UnaryOperator.
      * \throw JavaScriptException If the kind is not "valid" JavaScriptException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(UnaryOperator kind);

      /**
      * \brief Gives back the string representation of the UpdateOperator kind.
      * \param kind                [in] The UpdateOperator.
      * \throw JavaScriptException If the kind is not "valid" JavaScriptException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(UpdateOperator kind);

      /**
      * \brief Gives back the string representation of the NodeKind kind.
      * \param kind                [in] The NodeKind.
      * \throw JavaScriptException If the kind is not "valid" JavaScriptException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(NodeKind kind);

      /**
      * \brief Gives back the string representation of the EdgeKind kind.
      * \param kind                [in] The EdgeKind.
      * \throw JavaScriptException If the kind is not "valid" JavaScriptException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(EdgeKind kind);

      /**
      * \brief Returns true if the node exists and is not filtered out.
      * \param id [in] The examined node ID.
      * \return True if the node exists and is not filtered out.
      */
      bool getIsValid(NodeId id);

      /**
      * \brief Minimum of same type node similarity.
      */
      extern double SimilarityMinimum;

      /**
      * \brief Returns the minimum similarity value of same type nodes.
      * \return Minimum of same type node similarity.
      */
      double getSimilarityMinimum();

      /**
      * \brief Sets the minimum similarity value of same type nodes.
      * \param value [in] Minimum of same type node similarity.
      */
      void setSimilarityMinimum(double value);

      /**
      * \brief Minimum similarity for string type attributes.
      */
      extern double SimilarityMinForStrings;

      /**
      * \brief Returns the minimum similarity value for string type attributes.
      * \return Minimum similarity for string type attributes.
      */
      double getSimilarityMinForStrings();

      /**
      * \brief Sets the minimum similarity value for string type attributes.
      * \param value [in] Minimum similarity for string type attributes.
      */
      void setSimilarityMinForStrings(double value);

      /**
      * \brief Minimum similarity for AP spec edges.
      */
      extern double SimilarityMinForEdges;

      /**
      * \brief Returns the minimum similarity value for AP spec edges.
      * \return Minimum similarity for AP spec edges.
      */
      double getSimilarityMinForEdges();

      /**
      * \brief Sets the minimum similarity value for AP spec edges.
      * \param value [in] Minimum similarity for AP spec edges.
      */
      void setSimilarityMinForEdges(double value);


  } // Common


}}}
#endif

