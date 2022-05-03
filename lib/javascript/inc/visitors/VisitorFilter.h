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

#ifndef _JAVASCRIPT_VISITORFILTER_H_
#define _JAVASCRIPT_VISITORFILTER_H_

#include "javascript/inc/javascript.h"

/**
* \file VisitorFilter.h
* \brief Contains declaration of VisitorFilter class.
*/

namespace columbus { namespace javascript { namespace asg {
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
      virtual void visitEnd(const base::Comment& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::Program& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::System& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::ClassDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::ExportAllDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::ExportDefaultDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::ExportNamedDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::FunctionDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::ImportDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::ModuleDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::VariableDeclaration& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::VariableDeclarator& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ArrayExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ArrowFunctionExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AssignmentExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AwaitExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::BigIntLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::BinaryExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::BooleanLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::CallExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ChainElement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ChainExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ClassExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ConditionalExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::FunctionExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Identifier& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ImportExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::LogicalExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::MemberExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::MetaProperty& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::NewExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::NullLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::NumberLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ObjectExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::PrivateIdentifier& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Property& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::RegExpLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::SequenceExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::SpreadElement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::StringLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Super& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::TaggedTemplateExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::TemplateElement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::TemplateLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ThisExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::UnaryExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::UpdateExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::YieldExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ArrayPattern& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::AssignmentPattern& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::BlockStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::BreakStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::CatchClause& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ContinueStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::DebuggerStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::DoWhileStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::EmptyStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ExpressionStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ForInStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ForOfStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ForStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Function& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::IfStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::LabeledStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ObjectPattern& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::RestElement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ReturnStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::SwitchCase& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::SwitchStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ThrowStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::TryStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::WhileStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::WithStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ClassBody& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ExportSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ImportDefaultSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ImportNamespaceSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ImportSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::MethodDefinition& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::PropertyDefinition& node , bool callVirtualBase = true);

  }; // VisitorFilter


}}}
#endif

