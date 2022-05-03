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
Visitor::Visitor(): depth(0) {
}

Visitor::~Visitor() {
}

unsigned Visitor::getDepth() const {
  return depth;
}

void Visitor::incDepth() {
  ++depth;
}

void Visitor::decDepth() {
  --depth;
}

void Visitor::beginVisit() {
}

void Visitor::finishVisit() {
}

void Visitor::visit(const base::Comment& node , bool callVirtualBase) {}

void Visitor::visitEnd(const base::Comment& node , bool callVirtualBase) { }

void Visitor::visit(const base::Program& node , bool callVirtualBase) {}

void Visitor::visitEnd(const base::Program& node , bool callVirtualBase) { }

void Visitor::visit(const base::System& node , bool callVirtualBase) {}

void Visitor::visitEnd(const base::System& node , bool callVirtualBase) { }

void Visitor::visit(const declaration::ClassDeclaration& node , bool callVirtualBase) {}

void Visitor::visitEnd(const declaration::ClassDeclaration& node , bool callVirtualBase) { }

void Visitor::visit(const declaration::ExportAllDeclaration& node , bool callVirtualBase) {}

void Visitor::visitEnd(const declaration::ExportAllDeclaration& node , bool callVirtualBase) { }

void Visitor::visit(const declaration::ExportDefaultDeclaration& node , bool callVirtualBase) {}

void Visitor::visitEnd(const declaration::ExportDefaultDeclaration& node , bool callVirtualBase) { }

void Visitor::visit(const declaration::ExportNamedDeclaration& node , bool callVirtualBase) {}

void Visitor::visitEnd(const declaration::ExportNamedDeclaration& node , bool callVirtualBase) { }

void Visitor::visit(const declaration::FunctionDeclaration& node , bool callVirtualBase) {}

void Visitor::visitEnd(const declaration::FunctionDeclaration& node , bool callVirtualBase) { }

void Visitor::visit(const declaration::ImportDeclaration& node , bool callVirtualBase) {}

void Visitor::visitEnd(const declaration::ImportDeclaration& node , bool callVirtualBase) { }

void Visitor::visit(const declaration::ModuleDeclaration& node , bool callVirtualBase) {}

void Visitor::visitEnd(const declaration::ModuleDeclaration& node , bool callVirtualBase) { }

void Visitor::visit(const declaration::VariableDeclaration& node , bool callVirtualBase) {}

void Visitor::visitEnd(const declaration::VariableDeclaration& node , bool callVirtualBase) { }

void Visitor::visit(const declaration::VariableDeclarator& node , bool callVirtualBase) {}

void Visitor::visitEnd(const declaration::VariableDeclarator& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ArrayExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ArrayExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ArrowFunctionExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ArrowFunctionExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::AssignmentExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::AssignmentExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::AwaitExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::AwaitExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::BigIntLiteral& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::BigIntLiteral& node , bool callVirtualBase) { }

void Visitor::visit(const expression::BinaryExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::BinaryExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::BooleanLiteral& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::BooleanLiteral& node , bool callVirtualBase) { }

void Visitor::visit(const expression::CallExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::CallExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ChainElement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ChainElement& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ChainExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ChainExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ClassExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ClassExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ConditionalExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ConditionalExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::FunctionExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::FunctionExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::Identifier& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::Identifier& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ImportExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ImportExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::LogicalExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::LogicalExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::MemberExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::MemberExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::MetaProperty& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::MetaProperty& node , bool callVirtualBase) { }

void Visitor::visit(const expression::NewExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::NewExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::NullLiteral& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::NullLiteral& node , bool callVirtualBase) { }

void Visitor::visit(const expression::NumberLiteral& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::NumberLiteral& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ObjectExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ObjectExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::PrivateIdentifier& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::PrivateIdentifier& node , bool callVirtualBase) { }

void Visitor::visit(const expression::Property& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::Property& node , bool callVirtualBase) { }

void Visitor::visit(const expression::RegExpLiteral& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::RegExpLiteral& node , bool callVirtualBase) { }

void Visitor::visit(const expression::SequenceExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::SequenceExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::SpreadElement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::SpreadElement& node , bool callVirtualBase) { }

void Visitor::visit(const expression::StringLiteral& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::StringLiteral& node , bool callVirtualBase) { }

void Visitor::visit(const expression::Super& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::Super& node , bool callVirtualBase) { }

void Visitor::visit(const expression::TaggedTemplateExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::TaggedTemplateExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::TemplateElement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::TemplateElement& node , bool callVirtualBase) { }

void Visitor::visit(const expression::TemplateLiteral& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::TemplateLiteral& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ThisExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ThisExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::UnaryExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::UnaryExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::UpdateExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::UpdateExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::YieldExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::YieldExpression& node , bool callVirtualBase) { }

void Visitor::visit(const statement::ArrayPattern& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::ArrayPattern& node , bool callVirtualBase) { }

void Visitor::visit(const statement::AssignmentPattern& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::AssignmentPattern& node , bool callVirtualBase) { }

void Visitor::visit(const statement::BlockStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::BlockStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statement::BreakStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::BreakStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statement::CatchClause& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::CatchClause& node , bool callVirtualBase) { }

void Visitor::visit(const statement::ContinueStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::ContinueStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statement::DebuggerStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::DebuggerStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statement::DoWhileStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::DoWhileStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statement::EmptyStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::EmptyStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statement::ExpressionStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::ExpressionStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statement::ForInStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::ForInStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statement::ForOfStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::ForOfStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statement::ForStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::ForStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statement::Function& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::Function& node , bool callVirtualBase) { }

void Visitor::visit(const statement::IfStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::IfStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statement::LabeledStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::LabeledStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statement::ObjectPattern& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::ObjectPattern& node , bool callVirtualBase) { }

void Visitor::visit(const statement::RestElement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::RestElement& node , bool callVirtualBase) { }

void Visitor::visit(const statement::ReturnStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::ReturnStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statement::SwitchCase& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::SwitchCase& node , bool callVirtualBase) { }

void Visitor::visit(const statement::SwitchStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::SwitchStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statement::ThrowStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::ThrowStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statement::TryStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::TryStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statement::WhileStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::WhileStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statement::WithStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::WithStatement& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ClassBody& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ClassBody& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ExportSpecifier& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ExportSpecifier& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ImportDefaultSpecifier& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ImportDefaultSpecifier& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ImportNamespaceSpecifier& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ImportNamespaceSpecifier& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ImportSpecifier& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ImportSpecifier& node , bool callVirtualBase) { }

void Visitor::visit(const structure::MethodDefinition& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::MethodDefinition& node , bool callVirtualBase) { }

void Visitor::visit(const structure::PropertyDefinition& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::PropertyDefinition& node , bool callVirtualBase) { }

void Visitor::visitPositioned_Comments(const base::Positioned& begin, const base::Comment& end) { }

void Visitor::visitEndPositioned_Comments(const base::Positioned& begin, const base::Comment& end) { }

void Visitor::visitProgram_HasBody(const base::Program& begin, const base::Positioned& end) { }

void Visitor::visitEndProgram_HasBody(const base::Program& begin, const base::Positioned& end) { }

void Visitor::visitSystem_HasPrograms(const base::System& begin, const base::Program& end) { }

void Visitor::visitEndSystem_HasPrograms(const base::System& begin, const base::Program& end) { }

void Visitor::visitExportAllDeclaration_HasSource(const declaration::ExportAllDeclaration& begin, const expression::Literal& end) { }

void Visitor::visitEndExportAllDeclaration_HasSource(const declaration::ExportAllDeclaration& begin, const expression::Literal& end) { }

void Visitor::visitExportAllDeclaration_HasExported(const declaration::ExportAllDeclaration& begin, const expression::Identifier& end) { }

void Visitor::visitEndExportAllDeclaration_HasExported(const declaration::ExportAllDeclaration& begin, const expression::Identifier& end) { }

void Visitor::visitExportDefaultDeclaration_HasDeclaration(const declaration::ExportDefaultDeclaration& begin, const base::Positioned& end) { }

void Visitor::visitEndExportDefaultDeclaration_HasDeclaration(const declaration::ExportDefaultDeclaration& begin, const base::Positioned& end) { }

void Visitor::visitExportNamedDeclaration_HasDeclaration(const declaration::ExportNamedDeclaration& begin, const declaration::Declaration& end) { }

void Visitor::visitEndExportNamedDeclaration_HasDeclaration(const declaration::ExportNamedDeclaration& begin, const declaration::Declaration& end) { }

void Visitor::visitExportNamedDeclaration_HasSpecifiers(const declaration::ExportNamedDeclaration& begin, const structure::ExportSpecifier& end) { }

void Visitor::visitEndExportNamedDeclaration_HasSpecifiers(const declaration::ExportNamedDeclaration& begin, const structure::ExportSpecifier& end) { }

void Visitor::visitExportNamedDeclaration_HasSource(const declaration::ExportNamedDeclaration& begin, const expression::Literal& end) { }

void Visitor::visitEndExportNamedDeclaration_HasSource(const declaration::ExportNamedDeclaration& begin, const expression::Literal& end) { }

void Visitor::visitImportDeclaration_HasSpecifiers(const declaration::ImportDeclaration& begin, const structure::ImpSpecifier& end) { }

void Visitor::visitEndImportDeclaration_HasSpecifiers(const declaration::ImportDeclaration& begin, const structure::ImpSpecifier& end) { }

void Visitor::visitImportDeclaration_HasSource(const declaration::ImportDeclaration& begin, const expression::Literal& end) { }

void Visitor::visitEndImportDeclaration_HasSource(const declaration::ImportDeclaration& begin, const expression::Literal& end) { }

void Visitor::visitVariableDeclaration_HasDeclarations(const declaration::VariableDeclaration& begin, const declaration::VariableDeclarator& end) { }

void Visitor::visitEndVariableDeclaration_HasDeclarations(const declaration::VariableDeclaration& begin, const declaration::VariableDeclarator& end) { }

void Visitor::visitVariableDeclarator_HasIdentifier(const declaration::VariableDeclarator& begin, const statement::Pattern& end) { }

void Visitor::visitEndVariableDeclarator_HasIdentifier(const declaration::VariableDeclarator& begin, const statement::Pattern& end) { }

void Visitor::visitVariableDeclarator_HasInit(const declaration::VariableDeclarator& begin, const expression::Expression& end) { }

void Visitor::visitEndVariableDeclarator_HasInit(const declaration::VariableDeclarator& begin, const expression::Expression& end) { }

void Visitor::visitArrayExpression_HasElements(const expression::ArrayExpression& begin, const base::Positioned& end) { }

void Visitor::visitEndArrayExpression_HasElements(const expression::ArrayExpression& begin, const base::Positioned& end) { }

void Visitor::visitAssignmentExpression_HasLeft(const expression::AssignmentExpression& begin, const base::Positioned& end) { }

void Visitor::visitEndAssignmentExpression_HasLeft(const expression::AssignmentExpression& begin, const base::Positioned& end) { }

void Visitor::visitAssignmentExpression_HasRight(const expression::AssignmentExpression& begin, const expression::Expression& end) { }

void Visitor::visitEndAssignmentExpression_HasRight(const expression::AssignmentExpression& begin, const expression::Expression& end) { }

void Visitor::visitAwaitExpression_HasArgument(const expression::AwaitExpression& begin, const expression::Expression& end) { }

void Visitor::visitEndAwaitExpression_HasArgument(const expression::AwaitExpression& begin, const expression::Expression& end) { }

void Visitor::visitBinaryExpression_HasLeft(const expression::BinaryExpression& begin, const base::Positioned& end) { }

void Visitor::visitEndBinaryExpression_HasLeft(const expression::BinaryExpression& begin, const base::Positioned& end) { }

void Visitor::visitBinaryExpression_HasRight(const expression::BinaryExpression& begin, const expression::Expression& end) { }

void Visitor::visitEndBinaryExpression_HasRight(const expression::BinaryExpression& begin, const expression::Expression& end) { }

void Visitor::visitCallExpression_HasCallee(const expression::CallExpression& begin, const base::Positioned& end) { }

void Visitor::visitEndCallExpression_HasCallee(const expression::CallExpression& begin, const base::Positioned& end) { }

void Visitor::visitCallExpression_HasArguments(const expression::CallExpression& begin, const base::Positioned& end) { }

void Visitor::visitEndCallExpression_HasArguments(const expression::CallExpression& begin, const base::Positioned& end) { }

void Visitor::visitCallExpression_Calls(const expression::CallExpression& begin, const statement::Function& end) { }

void Visitor::visitEndCallExpression_Calls(const expression::CallExpression& begin, const statement::Function& end) { }

void Visitor::visitChainExpression_HasExpression(const expression::ChainExpression& begin, const expression::ChainElement& end) { }

void Visitor::visitEndChainExpression_HasExpression(const expression::ChainExpression& begin, const expression::ChainElement& end) { }

void Visitor::visitConditionalExpression_HasAlternate(const expression::ConditionalExpression& begin, const expression::Expression& end) { }

void Visitor::visitEndConditionalExpression_HasAlternate(const expression::ConditionalExpression& begin, const expression::Expression& end) { }

void Visitor::visitConditionalExpression_HasConsequent(const expression::ConditionalExpression& begin, const expression::Expression& end) { }

void Visitor::visitEndConditionalExpression_HasConsequent(const expression::ConditionalExpression& begin, const expression::Expression& end) { }

void Visitor::visitConditionalExpression_HasTest(const expression::ConditionalExpression& begin, const expression::Expression& end) { }

void Visitor::visitEndConditionalExpression_HasTest(const expression::ConditionalExpression& begin, const expression::Expression& end) { }

void Visitor::visitIdentifier_RefersTo(const expression::Identifier& begin, const base::Positioned& end) { }

void Visitor::visitEndIdentifier_RefersTo(const expression::Identifier& begin, const base::Positioned& end) { }

void Visitor::visitImportExpression_HasSource(const expression::ImportExpression& begin, const expression::Expression& end) { }

void Visitor::visitEndImportExpression_HasSource(const expression::ImportExpression& begin, const expression::Expression& end) { }

void Visitor::visitLogicalExpression_HasLeft(const expression::LogicalExpression& begin, const expression::Expression& end) { }

void Visitor::visitEndLogicalExpression_HasLeft(const expression::LogicalExpression& begin, const expression::Expression& end) { }

void Visitor::visitLogicalExpression_HasRight(const expression::LogicalExpression& begin, const expression::Expression& end) { }

void Visitor::visitEndLogicalExpression_HasRight(const expression::LogicalExpression& begin, const expression::Expression& end) { }

void Visitor::visitMemberExpression_HasProperty(const expression::MemberExpression& begin, const base::Positioned& end) { }

void Visitor::visitEndMemberExpression_HasProperty(const expression::MemberExpression& begin, const base::Positioned& end) { }

void Visitor::visitMemberExpression_HasObject(const expression::MemberExpression& begin, const base::Positioned& end) { }

void Visitor::visitEndMemberExpression_HasObject(const expression::MemberExpression& begin, const base::Positioned& end) { }

void Visitor::visitMetaProperty_HasMeta(const expression::MetaProperty& begin, const expression::Identifier& end) { }

void Visitor::visitEndMetaProperty_HasMeta(const expression::MetaProperty& begin, const expression::Identifier& end) { }

void Visitor::visitMetaProperty_HasProperty(const expression::MetaProperty& begin, const expression::Identifier& end) { }

void Visitor::visitEndMetaProperty_HasProperty(const expression::MetaProperty& begin, const expression::Identifier& end) { }

void Visitor::visitNewExpression_HasCallee(const expression::NewExpression& begin, const expression::Expression& end) { }

void Visitor::visitEndNewExpression_HasCallee(const expression::NewExpression& begin, const expression::Expression& end) { }

void Visitor::visitNewExpression_HasArguments(const expression::NewExpression& begin, const base::Positioned& end) { }

void Visitor::visitEndNewExpression_HasArguments(const expression::NewExpression& begin, const base::Positioned& end) { }

void Visitor::visitNewExpression_Calls(const expression::NewExpression& begin, const statement::Function& end) { }

void Visitor::visitEndNewExpression_Calls(const expression::NewExpression& begin, const statement::Function& end) { }

void Visitor::visitObjectExpression_HasProperties(const expression::ObjectExpression& begin, const base::Positioned& end) { }

void Visitor::visitEndObjectExpression_HasProperties(const expression::ObjectExpression& begin, const base::Positioned& end) { }

void Visitor::visitProperty_HasValue(const expression::Property& begin, const base::Positioned& end) { }

void Visitor::visitEndProperty_HasValue(const expression::Property& begin, const base::Positioned& end) { }

void Visitor::visitProperty_HasKey(const expression::Property& begin, const expression::Expression& end) { }

void Visitor::visitEndProperty_HasKey(const expression::Property& begin, const expression::Expression& end) { }

void Visitor::visitSequenceExpression_HasExpressions(const expression::SequenceExpression& begin, const expression::Expression& end) { }

void Visitor::visitEndSequenceExpression_HasExpressions(const expression::SequenceExpression& begin, const expression::Expression& end) { }

void Visitor::visitSpreadElement_HasArgument(const expression::SpreadElement& begin, const expression::Expression& end) { }

void Visitor::visitEndSpreadElement_HasArgument(const expression::SpreadElement& begin, const expression::Expression& end) { }

void Visitor::visitTaggedTemplateExpression_HasTag(const expression::TaggedTemplateExpression& begin, const expression::Expression& end) { }

void Visitor::visitEndTaggedTemplateExpression_HasTag(const expression::TaggedTemplateExpression& begin, const expression::Expression& end) { }

void Visitor::visitTaggedTemplateExpression_HasQuasi(const expression::TaggedTemplateExpression& begin, const expression::TemplateLiteral& end) { }

void Visitor::visitEndTaggedTemplateExpression_HasQuasi(const expression::TaggedTemplateExpression& begin, const expression::TemplateLiteral& end) { }

void Visitor::visitTemplateLiteral_HasQuasis(const expression::TemplateLiteral& begin, const expression::TemplateElement& end) { }

void Visitor::visitEndTemplateLiteral_HasQuasis(const expression::TemplateLiteral& begin, const expression::TemplateElement& end) { }

void Visitor::visitTemplateLiteral_HasExpressions(const expression::TemplateLiteral& begin, const expression::Expression& end) { }

void Visitor::visitEndTemplateLiteral_HasExpressions(const expression::TemplateLiteral& begin, const expression::Expression& end) { }

void Visitor::visitUnaryExpression_HasArgument(const expression::UnaryExpression& begin, const expression::Expression& end) { }

void Visitor::visitEndUnaryExpression_HasArgument(const expression::UnaryExpression& begin, const expression::Expression& end) { }

void Visitor::visitUpdateExpression_HasArgument(const expression::UpdateExpression& begin, const expression::Expression& end) { }

void Visitor::visitEndUpdateExpression_HasArgument(const expression::UpdateExpression& begin, const expression::Expression& end) { }

void Visitor::visitYieldExpression_HasArgument(const expression::YieldExpression& begin, const expression::Expression& end) { }

void Visitor::visitEndYieldExpression_HasArgument(const expression::YieldExpression& begin, const expression::Expression& end) { }

void Visitor::visitArrayPattern_HasElements(const statement::ArrayPattern& begin, const statement::Pattern& end) { }

void Visitor::visitEndArrayPattern_HasElements(const statement::ArrayPattern& begin, const statement::Pattern& end) { }

void Visitor::visitAssignmentPattern_HasLeft(const statement::AssignmentPattern& begin, const statement::Pattern& end) { }

void Visitor::visitEndAssignmentPattern_HasLeft(const statement::AssignmentPattern& begin, const statement::Pattern& end) { }

void Visitor::visitAssignmentPattern_HasRight(const statement::AssignmentPattern& begin, const expression::Expression& end) { }

void Visitor::visitEndAssignmentPattern_HasRight(const statement::AssignmentPattern& begin, const expression::Expression& end) { }

void Visitor::visitBlockStatement_HasBody(const statement::BlockStatement& begin, const statement::Statement& end) { }

void Visitor::visitEndBlockStatement_HasBody(const statement::BlockStatement& begin, const statement::Statement& end) { }

void Visitor::visitBreakStatement_HasLabel(const statement::BreakStatement& begin, const expression::Identifier& end) { }

void Visitor::visitEndBreakStatement_HasLabel(const statement::BreakStatement& begin, const expression::Identifier& end) { }

void Visitor::visitCatchClause_HasParam(const statement::CatchClause& begin, const statement::Pattern& end) { }

void Visitor::visitEndCatchClause_HasParam(const statement::CatchClause& begin, const statement::Pattern& end) { }

void Visitor::visitCatchClause_HasBody(const statement::CatchClause& begin, const statement::BlockStatement& end) { }

void Visitor::visitEndCatchClause_HasBody(const statement::CatchClause& begin, const statement::BlockStatement& end) { }

void Visitor::visitContinueStatement_HasLabel(const statement::ContinueStatement& begin, const expression::Identifier& end) { }

void Visitor::visitEndContinueStatement_HasLabel(const statement::ContinueStatement& begin, const expression::Identifier& end) { }

void Visitor::visitExpressionStatement_HasExpression(const statement::ExpressionStatement& begin, const expression::Expression& end) { }

void Visitor::visitEndExpressionStatement_HasExpression(const statement::ExpressionStatement& begin, const expression::Expression& end) { }

void Visitor::visitForInStatement_HasRight(const statement::ForInStatement& begin, const expression::Expression& end) { }

void Visitor::visitEndForInStatement_HasRight(const statement::ForInStatement& begin, const expression::Expression& end) { }

void Visitor::visitForInStatement_HasBody(const statement::ForInStatement& begin, const statement::Statement& end) { }

void Visitor::visitEndForInStatement_HasBody(const statement::ForInStatement& begin, const statement::Statement& end) { }

void Visitor::visitForInStatement_HasLeft(const statement::ForInStatement& begin, const base::Positioned& end) { }

void Visitor::visitEndForInStatement_HasLeft(const statement::ForInStatement& begin, const base::Positioned& end) { }

void Visitor::visitForStatement_HasBody(const statement::ForStatement& begin, const statement::Statement& end) { }

void Visitor::visitEndForStatement_HasBody(const statement::ForStatement& begin, const statement::Statement& end) { }

void Visitor::visitForStatement_HasTest(const statement::ForStatement& begin, const expression::Expression& end) { }

void Visitor::visitEndForStatement_HasTest(const statement::ForStatement& begin, const expression::Expression& end) { }

void Visitor::visitForStatement_HasUpdate(const statement::ForStatement& begin, const expression::Expression& end) { }

void Visitor::visitEndForStatement_HasUpdate(const statement::ForStatement& begin, const expression::Expression& end) { }

void Visitor::visitForStatement_HasInit(const statement::ForStatement& begin, const base::Positioned& end) { }

void Visitor::visitEndForStatement_HasInit(const statement::ForStatement& begin, const base::Positioned& end) { }

void Visitor::visitFunction_HasParams(const statement::Function& begin, const statement::Pattern& end) { }

void Visitor::visitEndFunction_HasParams(const statement::Function& begin, const statement::Pattern& end) { }

void Visitor::visitFunction_HasBody(const statement::Function& begin, const base::Positioned& end) { }

void Visitor::visitEndFunction_HasBody(const statement::Function& begin, const base::Positioned& end) { }

void Visitor::visitFunction_HasIdentifier(const statement::Function& begin, const expression::Identifier& end) { }

void Visitor::visitEndFunction_HasIdentifier(const statement::Function& begin, const expression::Identifier& end) { }

void Visitor::visitIfStatement_HasTest(const statement::IfStatement& begin, const expression::Expression& end) { }

void Visitor::visitEndIfStatement_HasTest(const statement::IfStatement& begin, const expression::Expression& end) { }

void Visitor::visitIfStatement_HasConsequent(const statement::IfStatement& begin, const statement::Statement& end) { }

void Visitor::visitEndIfStatement_HasConsequent(const statement::IfStatement& begin, const statement::Statement& end) { }

void Visitor::visitIfStatement_HasAlternate(const statement::IfStatement& begin, const statement::Statement& end) { }

void Visitor::visitEndIfStatement_HasAlternate(const statement::IfStatement& begin, const statement::Statement& end) { }

void Visitor::visitLabeledStatement_HasLabel(const statement::LabeledStatement& begin, const expression::Identifier& end) { }

void Visitor::visitEndLabeledStatement_HasLabel(const statement::LabeledStatement& begin, const expression::Identifier& end) { }

void Visitor::visitLabeledStatement_HasBody(const statement::LabeledStatement& begin, const statement::Statement& end) { }

void Visitor::visitEndLabeledStatement_HasBody(const statement::LabeledStatement& begin, const statement::Statement& end) { }

void Visitor::visitObjectPattern_HasProperties(const statement::ObjectPattern& begin, const base::Positioned& end) { }

void Visitor::visitEndObjectPattern_HasProperties(const statement::ObjectPattern& begin, const base::Positioned& end) { }

void Visitor::visitRestElement_HasArgument(const statement::RestElement& begin, const statement::Pattern& end) { }

void Visitor::visitEndRestElement_HasArgument(const statement::RestElement& begin, const statement::Pattern& end) { }

void Visitor::visitReturnStatement_HasArgument(const statement::ReturnStatement& begin, const expression::Expression& end) { }

void Visitor::visitEndReturnStatement_HasArgument(const statement::ReturnStatement& begin, const expression::Expression& end) { }

void Visitor::visitSwitchCase_HasTest(const statement::SwitchCase& begin, const expression::Expression& end) { }

void Visitor::visitEndSwitchCase_HasTest(const statement::SwitchCase& begin, const expression::Expression& end) { }

void Visitor::visitSwitchCase_HasConsequent(const statement::SwitchCase& begin, const statement::Statement& end) { }

void Visitor::visitEndSwitchCase_HasConsequent(const statement::SwitchCase& begin, const statement::Statement& end) { }

void Visitor::visitSwitchStatement_HasDiscriminant(const statement::SwitchStatement& begin, const expression::Expression& end) { }

void Visitor::visitEndSwitchStatement_HasDiscriminant(const statement::SwitchStatement& begin, const expression::Expression& end) { }

void Visitor::visitSwitchStatement_HasCases(const statement::SwitchStatement& begin, const statement::SwitchCase& end) { }

void Visitor::visitEndSwitchStatement_HasCases(const statement::SwitchStatement& begin, const statement::SwitchCase& end) { }

void Visitor::visitThrowStatement_HasArgument(const statement::ThrowStatement& begin, const expression::Expression& end) { }

void Visitor::visitEndThrowStatement_HasArgument(const statement::ThrowStatement& begin, const expression::Expression& end) { }

void Visitor::visitTryStatement_HasBlock(const statement::TryStatement& begin, const statement::BlockStatement& end) { }

void Visitor::visitEndTryStatement_HasBlock(const statement::TryStatement& begin, const statement::BlockStatement& end) { }

void Visitor::visitTryStatement_HasFinalizer(const statement::TryStatement& begin, const statement::BlockStatement& end) { }

void Visitor::visitEndTryStatement_HasFinalizer(const statement::TryStatement& begin, const statement::BlockStatement& end) { }

void Visitor::visitTryStatement_HasHandler(const statement::TryStatement& begin, const statement::CatchClause& end) { }

void Visitor::visitEndTryStatement_HasHandler(const statement::TryStatement& begin, const statement::CatchClause& end) { }

void Visitor::visitWhileStatement_HasBody(const statement::WhileStatement& begin, const statement::Statement& end) { }

void Visitor::visitEndWhileStatement_HasBody(const statement::WhileStatement& begin, const statement::Statement& end) { }

void Visitor::visitWhileStatement_HasTest(const statement::WhileStatement& begin, const expression::Expression& end) { }

void Visitor::visitEndWhileStatement_HasTest(const statement::WhileStatement& begin, const expression::Expression& end) { }

void Visitor::visitWithStatement_HasObject(const statement::WithStatement& begin, const expression::Expression& end) { }

void Visitor::visitEndWithStatement_HasObject(const statement::WithStatement& begin, const expression::Expression& end) { }

void Visitor::visitWithStatement_HasBody(const statement::WithStatement& begin, const statement::Statement& end) { }

void Visitor::visitEndWithStatement_HasBody(const statement::WithStatement& begin, const statement::Statement& end) { }

void Visitor::visitClass_HasBody(const structure::Class& begin, const structure::ClassBody& end) { }

void Visitor::visitEndClass_HasBody(const structure::Class& begin, const structure::ClassBody& end) { }

void Visitor::visitClass_HasSuperClass(const structure::Class& begin, const expression::Expression& end) { }

void Visitor::visitEndClass_HasSuperClass(const structure::Class& begin, const expression::Expression& end) { }

void Visitor::visitClass_HasIdentifier(const structure::Class& begin, const expression::Identifier& end) { }

void Visitor::visitEndClass_HasIdentifier(const structure::Class& begin, const expression::Identifier& end) { }

void Visitor::visitClassBody_HasBody(const structure::ClassBody& begin, const base::Positioned& end) { }

void Visitor::visitEndClassBody_HasBody(const structure::ClassBody& begin, const base::Positioned& end) { }

void Visitor::visitExportSpecifier_HasExported(const structure::ExportSpecifier& begin, const expression::Identifier& end) { }

void Visitor::visitEndExportSpecifier_HasExported(const structure::ExportSpecifier& begin, const expression::Identifier& end) { }

void Visitor::visitImportSpecifier_HasImported(const structure::ImportSpecifier& begin, const expression::Identifier& end) { }

void Visitor::visitEndImportSpecifier_HasImported(const structure::ImportSpecifier& begin, const expression::Identifier& end) { }

void Visitor::visitMethodDefinition_HasKey(const structure::MethodDefinition& begin, const base::Positioned& end) { }

void Visitor::visitEndMethodDefinition_HasKey(const structure::MethodDefinition& begin, const base::Positioned& end) { }

void Visitor::visitMethodDefinition_HasValue(const structure::MethodDefinition& begin, const expression::FunctionExpression& end) { }

void Visitor::visitEndMethodDefinition_HasValue(const structure::MethodDefinition& begin, const expression::FunctionExpression& end) { }

void Visitor::visitModuleSpecifier_HasLocal(const structure::ModuleSpecifier& begin, const expression::Identifier& end) { }

void Visitor::visitEndModuleSpecifier_HasLocal(const structure::ModuleSpecifier& begin, const expression::Identifier& end) { }

void Visitor::visitPropertyDefinition_HasKey(const structure::PropertyDefinition& begin, const base::Positioned& end) { }

void Visitor::visitEndPropertyDefinition_HasKey(const structure::PropertyDefinition& begin, const base::Positioned& end) { }

void Visitor::visitPropertyDefinition_HasValue(const structure::PropertyDefinition& begin, const expression::Expression& end) { }

void Visitor::visitEndPropertyDefinition_HasValue(const structure::PropertyDefinition& begin, const expression::Expression& end) { }


}}}
