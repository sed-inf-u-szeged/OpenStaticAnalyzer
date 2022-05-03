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
VisitorAbstractNodes::~VisitorAbstractNodes() { }

void VisitorAbstractNodes::visit   (const base::Base& node , bool callVirtualBase) { }
void VisitorAbstractNodes::visitEnd(const base::Base& node , bool callVirtualBase) { }

void VisitorAbstractNodes::visit(const base::Comment& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::Comment& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const base::Named& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::Named& node , bool callVirtualBase) {
  if (callVirtualBase)
    visitEnd((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const base::Positioned& node , bool callVirtualBase) {
  visit   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::Positioned& node , bool callVirtualBase) {
  visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const base::Program& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::Program& node , bool callVirtualBase) {
  visitEnd   ((base::Named&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const base::System& node , bool callVirtualBase) {
  visit   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::System& node , bool callVirtualBase) {
  visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const declaration::ClassDeclaration& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((declaration::Declaration&)node,false); 
  visit   ((structure::Class&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const declaration::ClassDeclaration& node , bool callVirtualBase) {
  visitEnd   ((declaration::Declaration&)node,false); 
  visitEnd   ((structure::Class&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const declaration::Declaration& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const declaration::Declaration& node , bool callVirtualBase) {
  visitEnd   ((statement::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const declaration::ExportAllDeclaration& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((declaration::Declaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const declaration::ExportAllDeclaration& node , bool callVirtualBase) {
  visitEnd   ((declaration::Declaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const declaration::ExportDefaultDeclaration& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((declaration::Declaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const declaration::ExportDefaultDeclaration& node , bool callVirtualBase) {
  visitEnd   ((declaration::Declaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const declaration::ExportNamedDeclaration& node , bool callVirtualBase) {
  visit   ((declaration::ModuleDeclaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const declaration::ExportNamedDeclaration& node , bool callVirtualBase) {
  visitEnd   ((declaration::ModuleDeclaration&)node,false); 
}

void VisitorAbstractNodes::visit(const declaration::FunctionDeclaration& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Function&)node,false); 
  visit   ((declaration::Declaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const declaration::FunctionDeclaration& node , bool callVirtualBase) {
  visitEnd   ((statement::Function&)node,false); 
  visitEnd   ((declaration::Declaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const declaration::ImportDeclaration& node , bool callVirtualBase) {
  visit   ((declaration::ModuleDeclaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const declaration::ImportDeclaration& node , bool callVirtualBase) {
  visitEnd   ((declaration::ModuleDeclaration&)node,false); 
}

void VisitorAbstractNodes::visit(const declaration::ModuleDeclaration& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const declaration::ModuleDeclaration& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const declaration::VariableDeclaration& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((declaration::Declaration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const declaration::VariableDeclaration& node , bool callVirtualBase) {
  visitEnd   ((declaration::Declaration&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const declaration::VariableDeclarator& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const declaration::VariableDeclarator& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ArrayExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ArrayExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ArrowFunctionExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
  visit   ((statement::Function&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ArrowFunctionExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  visitEnd   ((statement::Function&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::AssignmentExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::AssignmentExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::AwaitExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::AwaitExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::BigIntLiteral& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::BigIntLiteral& node , bool callVirtualBase) {
  visitEnd   ((expression::Literal&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::BinaryExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::BinaryExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::BooleanLiteral& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::BooleanLiteral& node , bool callVirtualBase) {
  visitEnd   ((expression::Literal&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::CallExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
  visit   ((expression::ChainElement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::CallExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  visitEnd   ((expression::ChainElement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ChainElement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ChainElement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visitEnd((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ChainExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ChainExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ClassExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
  visit   ((structure::Class&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ClassExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  visitEnd   ((structure::Class&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ConditionalExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ConditionalExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Expression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Expression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visitEnd((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::FunctionExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
  visit   ((statement::Function&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::FunctionExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  visitEnd   ((statement::Function&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Identifier& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
  visit   ((statement::Pattern&)node,false); 
  visit   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Identifier& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  visitEnd   ((statement::Pattern&)node,false); 
  visitEnd   ((base::Named&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ImportExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ImportExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Literal& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Literal& node , bool callVirtualBase) {
  if (callVirtualBase)
    visitEnd((base::Positioned&)node,false); 
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::LogicalExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::LogicalExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::MemberExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
  visit   ((statement::Pattern&)node,false); 
  visit   ((expression::ChainElement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::MemberExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  visitEnd   ((statement::Pattern&)node,false); 
  visitEnd   ((expression::ChainElement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::MetaProperty& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::MetaProperty& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::NewExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::NewExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::NullLiteral& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::NullLiteral& node , bool callVirtualBase) {
  visitEnd   ((expression::Literal&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::NumberLiteral& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::NumberLiteral& node , bool callVirtualBase) {
  visitEnd   ((expression::Literal&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ObjectExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ObjectExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::PrivateIdentifier& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit((base::Positioned&)node,false); 
  visit   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::PrivateIdentifier& node , bool callVirtualBase) {
  if (callVirtualBase)
    visitEnd((base::Positioned&)node,false); 
  visitEnd   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Property& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Property& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::RegExpLiteral& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::RegExpLiteral& node , bool callVirtualBase) {
  visitEnd   ((expression::Literal&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::SequenceExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::SequenceExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::SpreadElement& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::SpreadElement& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::StringLiteral& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::StringLiteral& node , bool callVirtualBase) {
  visitEnd   ((expression::Literal&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Super& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Super& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::TaggedTemplateExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::TaggedTemplateExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::TemplateElement& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::TemplateElement& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::TemplateLiteral& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::TemplateLiteral& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ThisExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ThisExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::UnaryExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::UnaryExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::UpdateExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::UpdateExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::YieldExpression& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::YieldExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::ArrayPattern& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Pattern&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::ArrayPattern& node , bool callVirtualBase) {
  visitEnd   ((statement::Pattern&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::AssignmentPattern& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Pattern&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::AssignmentPattern& node , bool callVirtualBase) {
  visitEnd   ((statement::Pattern&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::BlockStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::BlockStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::BreakStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::BreakStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::CatchClause& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::CatchClause& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::ContinueStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::ContinueStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::DebuggerStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::DebuggerStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::DoWhileStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::WhileStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::DoWhileStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::WhileStatement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::EmptyStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::EmptyStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::ExpressionStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::ExpressionStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::ForInStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::ForInStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::ForOfStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::ForInStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::ForOfStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::ForInStatement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::ForStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::ForStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Function& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Function& node , bool callVirtualBase) {
  if (callVirtualBase)
    visitEnd((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::IfStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::IfStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::LabeledStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::LabeledStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::ObjectPattern& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Pattern&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::ObjectPattern& node , bool callVirtualBase) {
  visitEnd   ((statement::Pattern&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Pattern& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Pattern& node , bool callVirtualBase) {
  if (callVirtualBase)
    visitEnd((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::RestElement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Pattern&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::RestElement& node , bool callVirtualBase) {
  visitEnd   ((statement::Pattern&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::ReturnStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::ReturnStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Statement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Statement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visitEnd((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::SwitchCase& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::SwitchCase& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::SwitchStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::SwitchStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::ThrowStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::ThrowStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::TryStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::TryStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::WhileStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::WhileStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::WithStatement& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit   ((base::Positioned&)node,false); 
  visit   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::WithStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::Statement&)node,false); 
  if (callVirtualBase)
    visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::Class& node , bool callVirtualBase) {
  if (callVirtualBase)
    visit((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::Class& node , bool callVirtualBase) {
  if (callVirtualBase)
    visitEnd((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ClassBody& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ClassBody& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ExportSpecifier& node , bool callVirtualBase) {
  visit   ((structure::ModuleSpecifier&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ExportSpecifier& node , bool callVirtualBase) {
  visitEnd   ((structure::ModuleSpecifier&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ImpSpecifier& node , bool callVirtualBase) {
  visit   ((structure::ModuleSpecifier&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ImpSpecifier& node , bool callVirtualBase) {
  visitEnd   ((structure::ModuleSpecifier&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ImportDefaultSpecifier& node , bool callVirtualBase) {
  visit   ((structure::ImpSpecifier&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ImportDefaultSpecifier& node , bool callVirtualBase) {
  visitEnd   ((structure::ImpSpecifier&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ImportNamespaceSpecifier& node , bool callVirtualBase) {
  visit   ((structure::ImpSpecifier&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ImportNamespaceSpecifier& node , bool callVirtualBase) {
  visitEnd   ((structure::ImpSpecifier&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ImportSpecifier& node , bool callVirtualBase) {
  visit   ((structure::ImpSpecifier&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ImportSpecifier& node , bool callVirtualBase) {
  visitEnd   ((structure::ImpSpecifier&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::MethodDefinition& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::MethodDefinition& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ModuleSpecifier& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ModuleSpecifier& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::PropertyDefinition& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::PropertyDefinition& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}


}}}
