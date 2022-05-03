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

#include "javascript/inc/javascript.h"


namespace columbus { namespace javascript { namespace asg {
VisitorFilter::VisitorFilter(bool filter) : Visitor() ,selector( filter?&Factory::setFilteredThisNodeOnly : &Factory::setNotFilteredThisNodeOnly) {
}

VisitorFilter::~VisitorFilter() {
}

void VisitorFilter::visitEnd(const base::Comment& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const base::Program& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const base::System& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const declaration::ClassDeclaration& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const declaration::ExportAllDeclaration& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const declaration::ExportDefaultDeclaration& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const declaration::ExportNamedDeclaration& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const declaration::FunctionDeclaration& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const declaration::ImportDeclaration& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const declaration::ModuleDeclaration& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const declaration::VariableDeclaration& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const declaration::VariableDeclarator& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ArrayExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ArrowFunctionExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::AssignmentExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::AwaitExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::BigIntLiteral& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::BinaryExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::BooleanLiteral& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::CallExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ChainElement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ChainExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ClassExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ConditionalExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::FunctionExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::Identifier& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ImportExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::LogicalExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::MemberExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::MetaProperty& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::NewExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::NullLiteral& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::NumberLiteral& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ObjectExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::PrivateIdentifier& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::Property& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::RegExpLiteral& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::SequenceExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::SpreadElement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::StringLiteral& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::Super& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::TaggedTemplateExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::TemplateElement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::TemplateLiteral& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ThisExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::UnaryExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::UpdateExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::YieldExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::ArrayPattern& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::AssignmentPattern& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::BlockStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::BreakStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::CatchClause& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::ContinueStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::DebuggerStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::DoWhileStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::EmptyStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::ExpressionStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::ForInStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::ForOfStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::ForStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::Function& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::IfStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::LabeledStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::ObjectPattern& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::RestElement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::ReturnStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::SwitchCase& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::SwitchStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::ThrowStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::TryStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::WhileStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::WithStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ClassBody& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ExportSpecifier& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ImportDefaultSpecifier& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ImportNamespaceSpecifier& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ImportSpecifier& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::MethodDefinition& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::PropertyDefinition& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}


}}}
