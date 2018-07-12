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

using namespace std;


namespace columbus { namespace javascript { namespace asg {
VisitorJAVASCRIPTML::VisitorJAVASCRIPTML(std::ofstream& targetStream,
                                         const std::string& _projectName,
                                         bool _noId,
                                         bool _noLineInfo) : ofs(targetStream), noId(_noId), noLineInfo(_noLineInfo), projectName(_projectName)
{
}

VisitorJAVASCRIPTML::~VisitorJAVASCRIPTML() {
}

void VisitorJAVASCRIPTML::beginVisit() {
  ofs << "<?xml version='1.0' encoding=\"utf-8\"?>\n";
  ofs << "<!DOCTYPE Project SYSTEM 'javascript-0.1.10.dtd'>\n";
  ofs << "<Project name='" << projectName << "'"
      << " xmlns:base='columbus_javascript_schema/base'"
      << " xmlns:declaration='columbus_javascript_schema/declaration'"
      << " xmlns:expression='columbus_javascript_schema/expression'"
      << " xmlns:statement='columbus_javascript_schema/statement'"
      << " xmlns:structure='columbus_javascript_schema/structure'"
      << ">\n";
}

void VisitorJAVASCRIPTML::finishVisit() {
  ofs << "<Filtered id='id1'/>\n";
  ofs << "</Project>\n";
}

void VisitorJAVASCRIPTML::visit(const base::Comment& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<base:Comment";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const base::Comment& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</base:Comment>\n";
}

void VisitorJAVASCRIPTML::visit(const base::Program& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<base:Program";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const base::Program& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</base:Program>\n";
}

void VisitorJAVASCRIPTML::visit(const base::System& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<base:System";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const base::System& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</base:System>\n";
}

void VisitorJAVASCRIPTML::visit(const declaration::ClassDeclaration& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<declaration:ClassDeclaration";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const declaration::ClassDeclaration& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</declaration:ClassDeclaration>\n";
}

void VisitorJAVASCRIPTML::visit(const declaration::ExportAllDeclaration& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<declaration:ExportAllDeclaration";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const declaration::ExportAllDeclaration& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</declaration:ExportAllDeclaration>\n";
}

void VisitorJAVASCRIPTML::visit(const declaration::ExportDefaultDeclaration& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<declaration:ExportDefaultDeclaration";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const declaration::ExportDefaultDeclaration& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</declaration:ExportDefaultDeclaration>\n";
}

void VisitorJAVASCRIPTML::visit(const declaration::ExportNamedDeclaration& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<declaration:ExportNamedDeclaration";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const declaration::ExportNamedDeclaration& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</declaration:ExportNamedDeclaration>\n";
}

void VisitorJAVASCRIPTML::visit(const declaration::FunctionDeclaration& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<declaration:FunctionDeclaration";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const declaration::FunctionDeclaration& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</declaration:FunctionDeclaration>\n";
}

void VisitorJAVASCRIPTML::visit(const declaration::ImportDeclaration& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<declaration:ImportDeclaration";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const declaration::ImportDeclaration& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</declaration:ImportDeclaration>\n";
}

void VisitorJAVASCRIPTML::visit(const declaration::ModuleDeclaration& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<declaration:ModuleDeclaration";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const declaration::ModuleDeclaration& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</declaration:ModuleDeclaration>\n";
}

void VisitorJAVASCRIPTML::visit(const declaration::VariableDeclaration& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<declaration:VariableDeclaration";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const declaration::VariableDeclaration& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</declaration:VariableDeclaration>\n";
}

void VisitorJAVASCRIPTML::visit(const declaration::VariableDeclarator& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<declaration:VariableDeclarator";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const declaration::VariableDeclarator& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</declaration:VariableDeclarator>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::ArrayExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ArrayExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::ArrayExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ArrayExpression>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::ArrowFunctionExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ArrowFunctionExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::ArrowFunctionExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ArrowFunctionExpression>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::AssignmentExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:AssignmentExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::AssignmentExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:AssignmentExpression>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::AssignmentProperty& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:AssignmentProperty";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::AssignmentProperty& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:AssignmentProperty>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::AwaitExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:AwaitExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::AwaitExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:AwaitExpression>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::BinaryExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:BinaryExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::BinaryExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:BinaryExpression>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::BooleanLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:BooleanLiteral";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::BooleanLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:BooleanLiteral>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::CallExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:CallExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::CallExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:CallExpression>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::ClassExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ClassExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::ClassExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ClassExpression>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::ConditionalExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ConditionalExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::ConditionalExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ConditionalExpression>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::FunctionExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:FunctionExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::FunctionExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:FunctionExpression>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::Identifier& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:Identifier";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::Identifier& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:Identifier>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::LogicalExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:LogicalExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::LogicalExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:LogicalExpression>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::MemberExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:MemberExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::MemberExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:MemberExpression>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::MetaProperty& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:MetaProperty";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::MetaProperty& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:MetaProperty>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::NewExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:NewExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::NewExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:NewExpression>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::NullLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:NullLiteral";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::NullLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:NullLiteral>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::NumberLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:NumberLiteral";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::NumberLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:NumberLiteral>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::ObjectExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ObjectExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::ObjectExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ObjectExpression>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::Property& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:Property";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::Property& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:Property>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::RegExpLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:RegExpLiteral";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::RegExpLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:RegExpLiteral>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::SequenceExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:SequenceExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::SequenceExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:SequenceExpression>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::SpreadElement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:SpreadElement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::SpreadElement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:SpreadElement>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::StringLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:StringLiteral";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::StringLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:StringLiteral>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::Super& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:Super";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::Super& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:Super>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::TaggedTemplateExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:TaggedTemplateExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::TaggedTemplateExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:TaggedTemplateExpression>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::TemplateElement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:TemplateElement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::TemplateElement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:TemplateElement>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::TemplateLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:TemplateLiteral";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::TemplateLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:TemplateLiteral>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::ThisExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ThisExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::ThisExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ThisExpression>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::UnaryExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:UnaryExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::UnaryExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:UnaryExpression>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::UpdateExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:UpdateExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::UpdateExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:UpdateExpression>\n";
}

void VisitorJAVASCRIPTML::visit(const expression::YieldExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:YieldExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const expression::YieldExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:YieldExpression>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::ArrayPattern& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:ArrayPattern";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::ArrayPattern& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:ArrayPattern>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::AssignmentPattern& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:AssignmentPattern";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::AssignmentPattern& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:AssignmentPattern>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::BlockStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:BlockStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::BlockStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:BlockStatement>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::BreakStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:BreakStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::BreakStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:BreakStatement>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::CatchClause& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:CatchClause";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::CatchClause& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:CatchClause>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::ContinueStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:ContinueStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::ContinueStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:ContinueStatement>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::DebuggerStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:DebuggerStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::DebuggerStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:DebuggerStatement>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::DoWhileStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:DoWhileStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::DoWhileStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:DoWhileStatement>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::EmptyStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:EmptyStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::EmptyStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:EmptyStatement>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::ExpressionStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:ExpressionStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::ExpressionStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:ExpressionStatement>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::ForInStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:ForInStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::ForInStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:ForInStatement>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::ForOfStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:ForOfStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::ForOfStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:ForOfStatement>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::ForStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:ForStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::ForStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:ForStatement>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::Function& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:Function";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::Function& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:Function>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::IfStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:IfStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::IfStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:IfStatement>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::LabeledStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:LabeledStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::LabeledStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:LabeledStatement>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::ObjectPattern& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:ObjectPattern";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::ObjectPattern& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:ObjectPattern>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::RestElement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:RestElement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::RestElement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:RestElement>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::ReturnStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:ReturnStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::ReturnStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:ReturnStatement>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::SwitchCase& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:SwitchCase";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::SwitchCase& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:SwitchCase>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::SwitchStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:SwitchStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::SwitchStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:SwitchStatement>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::ThrowStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:ThrowStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::ThrowStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:ThrowStatement>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::TryStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:TryStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::TryStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:TryStatement>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::WhileStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:WhileStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::WhileStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:WhileStatement>\n";
}

void VisitorJAVASCRIPTML::visit(const statement::WithStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:WithStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const statement::WithStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:WithStatement>\n";
}

void VisitorJAVASCRIPTML::visit(const structure::ClassBody& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ClassBody";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const structure::ClassBody& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ClassBody>\n";
}

void VisitorJAVASCRIPTML::visit(const structure::ExportSpecifier& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ExportSpecifier";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const structure::ExportSpecifier& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ExportSpecifier>\n";
}

void VisitorJAVASCRIPTML::visit(const structure::ImportDefaultSpecifier& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ImportDefaultSpecifier";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const structure::ImportDefaultSpecifier& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ImportDefaultSpecifier>\n";
}

void VisitorJAVASCRIPTML::visit(const structure::ImportNamespaceSpecifier& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ImportNamespaceSpecifier";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const structure::ImportNamespaceSpecifier& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ImportNamespaceSpecifier>\n";
}

void VisitorJAVASCRIPTML::visit(const structure::ImportSpecifier& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ImportSpecifier";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const structure::ImportSpecifier& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ImportSpecifier>\n";
}

void VisitorJAVASCRIPTML::visit(const structure::MethodDefinition& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:MethodDefinition";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVASCRIPTML::visitEnd(const structure::MethodDefinition& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:MethodDefinition>\n";
}

void VisitorJAVASCRIPTML::visitPositioned_Comments(const base::Positioned& begin, const base::Comment& end) {
  createIndentation();
  ofs << "<Positioned_Comments ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVASCRIPTML::visitEndPositioned_Comments(const base::Positioned& begin, const base::Comment& end) {
}

void VisitorJAVASCRIPTML::visitProgram_HasBody(const base::Program& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<Program_HasBody>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndProgram_HasBody(const base::Program& begin, const base::Positioned& end) {
  decDepth();
  createIndentation();
  ofs << "</Program_HasBody>\n";
}

void VisitorJAVASCRIPTML::visitSystem_HasPrograms(const base::System& begin, const base::Program& end) {
  createIndentation();
  ofs << "<System_HasPrograms>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndSystem_HasPrograms(const base::System& begin, const base::Program& end) {
  decDepth();
  createIndentation();
  ofs << "</System_HasPrograms>\n";
}

void VisitorJAVASCRIPTML::visitExportAllDeclaration_HasSource(const declaration::ExportAllDeclaration& begin, const expression::Literal& end) {
  createIndentation();
  ofs << "<ExportAllDeclaration_HasSource>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndExportAllDeclaration_HasSource(const declaration::ExportAllDeclaration& begin, const expression::Literal& end) {
  decDepth();
  createIndentation();
  ofs << "</ExportAllDeclaration_HasSource>\n";
}

void VisitorJAVASCRIPTML::visitExportDefaultDeclaration_HasDeclaration(const declaration::ExportDefaultDeclaration& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<ExportDefaultDeclaration_HasDeclaration>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndExportDefaultDeclaration_HasDeclaration(const declaration::ExportDefaultDeclaration& begin, const base::Positioned& end) {
  decDepth();
  createIndentation();
  ofs << "</ExportDefaultDeclaration_HasDeclaration>\n";
}

void VisitorJAVASCRIPTML::visitExportNamedDeclaration_HasDeclaration(const declaration::ExportNamedDeclaration& begin, const declaration::Declaration& end) {
  createIndentation();
  ofs << "<ExportNamedDeclaration_HasDeclaration>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndExportNamedDeclaration_HasDeclaration(const declaration::ExportNamedDeclaration& begin, const declaration::Declaration& end) {
  decDepth();
  createIndentation();
  ofs << "</ExportNamedDeclaration_HasDeclaration>\n";
}

void VisitorJAVASCRIPTML::visitExportNamedDeclaration_HasSpecifiers(const declaration::ExportNamedDeclaration& begin, const structure::ExportSpecifier& end) {
  createIndentation();
  ofs << "<ExportNamedDeclaration_HasSpecifiers>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndExportNamedDeclaration_HasSpecifiers(const declaration::ExportNamedDeclaration& begin, const structure::ExportSpecifier& end) {
  decDepth();
  createIndentation();
  ofs << "</ExportNamedDeclaration_HasSpecifiers>\n";
}

void VisitorJAVASCRIPTML::visitExportNamedDeclaration_HasSource(const declaration::ExportNamedDeclaration& begin, const expression::Literal& end) {
  createIndentation();
  ofs << "<ExportNamedDeclaration_HasSource>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndExportNamedDeclaration_HasSource(const declaration::ExportNamedDeclaration& begin, const expression::Literal& end) {
  decDepth();
  createIndentation();
  ofs << "</ExportNamedDeclaration_HasSource>\n";
}

void VisitorJAVASCRIPTML::visitImportDeclaration_HasSpecifiers(const declaration::ImportDeclaration& begin, const structure::ImpSpecifier& end) {
  createIndentation();
  ofs << "<ImportDeclaration_HasSpecifiers>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndImportDeclaration_HasSpecifiers(const declaration::ImportDeclaration& begin, const structure::ImpSpecifier& end) {
  decDepth();
  createIndentation();
  ofs << "</ImportDeclaration_HasSpecifiers>\n";
}

void VisitorJAVASCRIPTML::visitImportDeclaration_HasSource(const declaration::ImportDeclaration& begin, const expression::Literal& end) {
  createIndentation();
  ofs << "<ImportDeclaration_HasSource>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndImportDeclaration_HasSource(const declaration::ImportDeclaration& begin, const expression::Literal& end) {
  decDepth();
  createIndentation();
  ofs << "</ImportDeclaration_HasSource>\n";
}

void VisitorJAVASCRIPTML::visitVariableDeclaration_HasDeclarations(const declaration::VariableDeclaration& begin, const declaration::VariableDeclarator& end) {
  createIndentation();
  ofs << "<VariableDeclaration_HasDeclarations>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndVariableDeclaration_HasDeclarations(const declaration::VariableDeclaration& begin, const declaration::VariableDeclarator& end) {
  decDepth();
  createIndentation();
  ofs << "</VariableDeclaration_HasDeclarations>\n";
}

void VisitorJAVASCRIPTML::visitVariableDeclarator_HasIdentifier(const declaration::VariableDeclarator& begin, const statement::Pattern& end) {
  createIndentation();
  ofs << "<VariableDeclarator_HasIdentifier>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndVariableDeclarator_HasIdentifier(const declaration::VariableDeclarator& begin, const statement::Pattern& end) {
  decDepth();
  createIndentation();
  ofs << "</VariableDeclarator_HasIdentifier>\n";
}

void VisitorJAVASCRIPTML::visitVariableDeclarator_HasInit(const declaration::VariableDeclarator& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<VariableDeclarator_HasInit>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndVariableDeclarator_HasInit(const declaration::VariableDeclarator& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</VariableDeclarator_HasInit>\n";
}

void VisitorJAVASCRIPTML::visitArrayExpression_HasElements(const expression::ArrayExpression& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<ArrayExpression_HasElements>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndArrayExpression_HasElements(const expression::ArrayExpression& begin, const base::Positioned& end) {
  decDepth();
  createIndentation();
  ofs << "</ArrayExpression_HasElements>\n";
}

void VisitorJAVASCRIPTML::visitAssignmentExpression_HasLeft(const expression::AssignmentExpression& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<AssignmentExpression_HasLeft>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndAssignmentExpression_HasLeft(const expression::AssignmentExpression& begin, const base::Positioned& end) {
  decDepth();
  createIndentation();
  ofs << "</AssignmentExpression_HasLeft>\n";
}

void VisitorJAVASCRIPTML::visitAssignmentExpression_HasRight(const expression::AssignmentExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<AssignmentExpression_HasRight>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndAssignmentExpression_HasRight(const expression::AssignmentExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</AssignmentExpression_HasRight>\n";
}

void VisitorJAVASCRIPTML::visitAwaitExpression_HasArgument(const expression::AwaitExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<AwaitExpression_HasArgument>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndAwaitExpression_HasArgument(const expression::AwaitExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</AwaitExpression_HasArgument>\n";
}

void VisitorJAVASCRIPTML::visitBinaryExpression_HasLeft(const expression::BinaryExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<BinaryExpression_HasLeft>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndBinaryExpression_HasLeft(const expression::BinaryExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</BinaryExpression_HasLeft>\n";
}

void VisitorJAVASCRIPTML::visitBinaryExpression_HasRight(const expression::BinaryExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<BinaryExpression_HasRight>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndBinaryExpression_HasRight(const expression::BinaryExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</BinaryExpression_HasRight>\n";
}

void VisitorJAVASCRIPTML::visitCallExpression_HasCallee(const expression::CallExpression& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<CallExpression_HasCallee>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndCallExpression_HasCallee(const expression::CallExpression& begin, const base::Positioned& end) {
  decDepth();
  createIndentation();
  ofs << "</CallExpression_HasCallee>\n";
}

void VisitorJAVASCRIPTML::visitCallExpression_HasArguments(const expression::CallExpression& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<CallExpression_HasArguments>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndCallExpression_HasArguments(const expression::CallExpression& begin, const base::Positioned& end) {
  decDepth();
  createIndentation();
  ofs << "</CallExpression_HasArguments>\n";
}

void VisitorJAVASCRIPTML::visitConditionalExpression_HasAlternate(const expression::ConditionalExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<ConditionalExpression_HasAlternate>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndConditionalExpression_HasAlternate(const expression::ConditionalExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</ConditionalExpression_HasAlternate>\n";
}

void VisitorJAVASCRIPTML::visitConditionalExpression_HasConsequent(const expression::ConditionalExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<ConditionalExpression_HasConsequent>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndConditionalExpression_HasConsequent(const expression::ConditionalExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</ConditionalExpression_HasConsequent>\n";
}

void VisitorJAVASCRIPTML::visitConditionalExpression_HasTest(const expression::ConditionalExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<ConditionalExpression_HasTest>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndConditionalExpression_HasTest(const expression::ConditionalExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</ConditionalExpression_HasTest>\n";
}

void VisitorJAVASCRIPTML::visitIdentifier_RefersTo(const expression::Identifier& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<Identifier_RefersTo ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVASCRIPTML::visitEndIdentifier_RefersTo(const expression::Identifier& begin, const base::Positioned& end) {
}

void VisitorJAVASCRIPTML::visitLogicalExpression_HasLeft(const expression::LogicalExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<LogicalExpression_HasLeft>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndLogicalExpression_HasLeft(const expression::LogicalExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</LogicalExpression_HasLeft>\n";
}

void VisitorJAVASCRIPTML::visitLogicalExpression_HasRight(const expression::LogicalExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<LogicalExpression_HasRight>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndLogicalExpression_HasRight(const expression::LogicalExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</LogicalExpression_HasRight>\n";
}

void VisitorJAVASCRIPTML::visitMemberExpression_HasProperty(const expression::MemberExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<MemberExpression_HasProperty>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndMemberExpression_HasProperty(const expression::MemberExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</MemberExpression_HasProperty>\n";
}

void VisitorJAVASCRIPTML::visitMemberExpression_HasObject(const expression::MemberExpression& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<MemberExpression_HasObject>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndMemberExpression_HasObject(const expression::MemberExpression& begin, const base::Positioned& end) {
  decDepth();
  createIndentation();
  ofs << "</MemberExpression_HasObject>\n";
}

void VisitorJAVASCRIPTML::visitMetaProperty_HasMeta(const expression::MetaProperty& begin, const expression::Identifier& end) {
  createIndentation();
  ofs << "<MetaProperty_HasMeta>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndMetaProperty_HasMeta(const expression::MetaProperty& begin, const expression::Identifier& end) {
  decDepth();
  createIndentation();
  ofs << "</MetaProperty_HasMeta>\n";
}

void VisitorJAVASCRIPTML::visitMetaProperty_HasProperty(const expression::MetaProperty& begin, const expression::Identifier& end) {
  createIndentation();
  ofs << "<MetaProperty_HasProperty>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndMetaProperty_HasProperty(const expression::MetaProperty& begin, const expression::Identifier& end) {
  decDepth();
  createIndentation();
  ofs << "</MetaProperty_HasProperty>\n";
}

void VisitorJAVASCRIPTML::visitNewExpression_HasCallee(const expression::NewExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<NewExpression_HasCallee>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndNewExpression_HasCallee(const expression::NewExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</NewExpression_HasCallee>\n";
}

void VisitorJAVASCRIPTML::visitNewExpression_HasArguments(const expression::NewExpression& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<NewExpression_HasArguments>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndNewExpression_HasArguments(const expression::NewExpression& begin, const base::Positioned& end) {
  decDepth();
  createIndentation();
  ofs << "</NewExpression_HasArguments>\n";
}

void VisitorJAVASCRIPTML::visitObjectExpression_HasProperties(const expression::ObjectExpression& begin, const expression::Property& end) {
  createIndentation();
  ofs << "<ObjectExpression_HasProperties>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndObjectExpression_HasProperties(const expression::ObjectExpression& begin, const expression::Property& end) {
  decDepth();
  createIndentation();
  ofs << "</ObjectExpression_HasProperties>\n";
}

void VisitorJAVASCRIPTML::visitProperty_HasValue(const expression::Property& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<Property_HasValue>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndProperty_HasValue(const expression::Property& begin, const base::Positioned& end) {
  decDepth();
  createIndentation();
  ofs << "</Property_HasValue>\n";
}

void VisitorJAVASCRIPTML::visitProperty_HasKey(const expression::Property& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Property_HasKey>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndProperty_HasKey(const expression::Property& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Property_HasKey>\n";
}

void VisitorJAVASCRIPTML::visitSequenceExpression_HasExpressions(const expression::SequenceExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<SequenceExpression_HasExpressions>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndSequenceExpression_HasExpressions(const expression::SequenceExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</SequenceExpression_HasExpressions>\n";
}

void VisitorJAVASCRIPTML::visitSpreadElement_HasArgument(const expression::SpreadElement& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<SpreadElement_HasArgument>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndSpreadElement_HasArgument(const expression::SpreadElement& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</SpreadElement_HasArgument>\n";
}

void VisitorJAVASCRIPTML::visitTaggedTemplateExpression_HasTag(const expression::TaggedTemplateExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<TaggedTemplateExpression_HasTag>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndTaggedTemplateExpression_HasTag(const expression::TaggedTemplateExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</TaggedTemplateExpression_HasTag>\n";
}

void VisitorJAVASCRIPTML::visitTaggedTemplateExpression_HasQuasi(const expression::TaggedTemplateExpression& begin, const expression::TemplateLiteral& end) {
  createIndentation();
  ofs << "<TaggedTemplateExpression_HasQuasi>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndTaggedTemplateExpression_HasQuasi(const expression::TaggedTemplateExpression& begin, const expression::TemplateLiteral& end) {
  decDepth();
  createIndentation();
  ofs << "</TaggedTemplateExpression_HasQuasi>\n";
}

void VisitorJAVASCRIPTML::visitTemplateLiteral_HasQuasis(const expression::TemplateLiteral& begin, const expression::TemplateElement& end) {
  createIndentation();
  ofs << "<TemplateLiteral_HasQuasis>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndTemplateLiteral_HasQuasis(const expression::TemplateLiteral& begin, const expression::TemplateElement& end) {
  decDepth();
  createIndentation();
  ofs << "</TemplateLiteral_HasQuasis>\n";
}

void VisitorJAVASCRIPTML::visitTemplateLiteral_HasExpressions(const expression::TemplateLiteral& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<TemplateLiteral_HasExpressions>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndTemplateLiteral_HasExpressions(const expression::TemplateLiteral& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</TemplateLiteral_HasExpressions>\n";
}

void VisitorJAVASCRIPTML::visitUnaryExpression_HasArgument(const expression::UnaryExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<UnaryExpression_HasArgument>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndUnaryExpression_HasArgument(const expression::UnaryExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</UnaryExpression_HasArgument>\n";
}

void VisitorJAVASCRIPTML::visitUpdateExpression_HasArgument(const expression::UpdateExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<UpdateExpression_HasArgument>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndUpdateExpression_HasArgument(const expression::UpdateExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</UpdateExpression_HasArgument>\n";
}

void VisitorJAVASCRIPTML::visitYieldExpression_HasArgument(const expression::YieldExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<YieldExpression_HasArgument>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndYieldExpression_HasArgument(const expression::YieldExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</YieldExpression_HasArgument>\n";
}

void VisitorJAVASCRIPTML::visitArrayPattern_HasElements(const statement::ArrayPattern& begin, const statement::Pattern& end) {
  createIndentation();
  ofs << "<ArrayPattern_HasElements>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndArrayPattern_HasElements(const statement::ArrayPattern& begin, const statement::Pattern& end) {
  decDepth();
  createIndentation();
  ofs << "</ArrayPattern_HasElements>\n";
}

void VisitorJAVASCRIPTML::visitAssignmentPattern_HasLeft(const statement::AssignmentPattern& begin, const statement::Pattern& end) {
  createIndentation();
  ofs << "<AssignmentPattern_HasLeft>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndAssignmentPattern_HasLeft(const statement::AssignmentPattern& begin, const statement::Pattern& end) {
  decDepth();
  createIndentation();
  ofs << "</AssignmentPattern_HasLeft>\n";
}

void VisitorJAVASCRIPTML::visitAssignmentPattern_HasRight(const statement::AssignmentPattern& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<AssignmentPattern_HasRight>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndAssignmentPattern_HasRight(const statement::AssignmentPattern& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</AssignmentPattern_HasRight>\n";
}

void VisitorJAVASCRIPTML::visitBlockStatement_HasBody(const statement::BlockStatement& begin, const statement::Statement& end) {
  createIndentation();
  ofs << "<BlockStatement_HasBody>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndBlockStatement_HasBody(const statement::BlockStatement& begin, const statement::Statement& end) {
  decDepth();
  createIndentation();
  ofs << "</BlockStatement_HasBody>\n";
}

void VisitorJAVASCRIPTML::visitBreakStatement_HasLabel(const statement::BreakStatement& begin, const expression::Identifier& end) {
  createIndentation();
  ofs << "<BreakStatement_HasLabel>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndBreakStatement_HasLabel(const statement::BreakStatement& begin, const expression::Identifier& end) {
  decDepth();
  createIndentation();
  ofs << "</BreakStatement_HasLabel>\n";
}

void VisitorJAVASCRIPTML::visitCatchClause_HasParam(const statement::CatchClause& begin, const statement::Pattern& end) {
  createIndentation();
  ofs << "<CatchClause_HasParam>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndCatchClause_HasParam(const statement::CatchClause& begin, const statement::Pattern& end) {
  decDepth();
  createIndentation();
  ofs << "</CatchClause_HasParam>\n";
}

void VisitorJAVASCRIPTML::visitCatchClause_HasBody(const statement::CatchClause& begin, const statement::BlockStatement& end) {
  createIndentation();
  ofs << "<CatchClause_HasBody>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndCatchClause_HasBody(const statement::CatchClause& begin, const statement::BlockStatement& end) {
  decDepth();
  createIndentation();
  ofs << "</CatchClause_HasBody>\n";
}

void VisitorJAVASCRIPTML::visitContinueStatement_HasLabel(const statement::ContinueStatement& begin, const expression::Identifier& end) {
  createIndentation();
  ofs << "<ContinueStatement_HasLabel>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndContinueStatement_HasLabel(const statement::ContinueStatement& begin, const expression::Identifier& end) {
  decDepth();
  createIndentation();
  ofs << "</ContinueStatement_HasLabel>\n";
}

void VisitorJAVASCRIPTML::visitExpressionStatement_HasExpression(const statement::ExpressionStatement& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<ExpressionStatement_HasExpression>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndExpressionStatement_HasExpression(const statement::ExpressionStatement& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</ExpressionStatement_HasExpression>\n";
}

void VisitorJAVASCRIPTML::visitForInStatement_HasRight(const statement::ForInStatement& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<ForInStatement_HasRight>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndForInStatement_HasRight(const statement::ForInStatement& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</ForInStatement_HasRight>\n";
}

void VisitorJAVASCRIPTML::visitForInStatement_HasBody(const statement::ForInStatement& begin, const statement::Statement& end) {
  createIndentation();
  ofs << "<ForInStatement_HasBody>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndForInStatement_HasBody(const statement::ForInStatement& begin, const statement::Statement& end) {
  decDepth();
  createIndentation();
  ofs << "</ForInStatement_HasBody>\n";
}

void VisitorJAVASCRIPTML::visitForInStatement_HasLeft(const statement::ForInStatement& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<ForInStatement_HasLeft>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndForInStatement_HasLeft(const statement::ForInStatement& begin, const base::Positioned& end) {
  decDepth();
  createIndentation();
  ofs << "</ForInStatement_HasLeft>\n";
}

void VisitorJAVASCRIPTML::visitForStatement_HasBody(const statement::ForStatement& begin, const statement::Statement& end) {
  createIndentation();
  ofs << "<ForStatement_HasBody>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndForStatement_HasBody(const statement::ForStatement& begin, const statement::Statement& end) {
  decDepth();
  createIndentation();
  ofs << "</ForStatement_HasBody>\n";
}

void VisitorJAVASCRIPTML::visitForStatement_HasTest(const statement::ForStatement& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<ForStatement_HasTest>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndForStatement_HasTest(const statement::ForStatement& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</ForStatement_HasTest>\n";
}

void VisitorJAVASCRIPTML::visitForStatement_HasUpdate(const statement::ForStatement& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<ForStatement_HasUpdate>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndForStatement_HasUpdate(const statement::ForStatement& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</ForStatement_HasUpdate>\n";
}

void VisitorJAVASCRIPTML::visitForStatement_HasInit(const statement::ForStatement& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<ForStatement_HasInit>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndForStatement_HasInit(const statement::ForStatement& begin, const base::Positioned& end) {
  decDepth();
  createIndentation();
  ofs << "</ForStatement_HasInit>\n";
}

void VisitorJAVASCRIPTML::visitFunction_HasParams(const statement::Function& begin, const statement::Pattern& end) {
  createIndentation();
  ofs << "<Function_HasParams>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndFunction_HasParams(const statement::Function& begin, const statement::Pattern& end) {
  decDepth();
  createIndentation();
  ofs << "</Function_HasParams>\n";
}

void VisitorJAVASCRIPTML::visitFunction_HasBody(const statement::Function& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<Function_HasBody>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndFunction_HasBody(const statement::Function& begin, const base::Positioned& end) {
  decDepth();
  createIndentation();
  ofs << "</Function_HasBody>\n";
}

void VisitorJAVASCRIPTML::visitFunction_HasIdentifier(const statement::Function& begin, const expression::Identifier& end) {
  createIndentation();
  ofs << "<Function_HasIdentifier>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndFunction_HasIdentifier(const statement::Function& begin, const expression::Identifier& end) {
  decDepth();
  createIndentation();
  ofs << "</Function_HasIdentifier>\n";
}

void VisitorJAVASCRIPTML::visitIfStatement_HasTest(const statement::IfStatement& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<IfStatement_HasTest>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndIfStatement_HasTest(const statement::IfStatement& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</IfStatement_HasTest>\n";
}

void VisitorJAVASCRIPTML::visitIfStatement_HasConsequent(const statement::IfStatement& begin, const statement::Statement& end) {
  createIndentation();
  ofs << "<IfStatement_HasConsequent>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndIfStatement_HasConsequent(const statement::IfStatement& begin, const statement::Statement& end) {
  decDepth();
  createIndentation();
  ofs << "</IfStatement_HasConsequent>\n";
}

void VisitorJAVASCRIPTML::visitIfStatement_HasAlternate(const statement::IfStatement& begin, const statement::Statement& end) {
  createIndentation();
  ofs << "<IfStatement_HasAlternate>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndIfStatement_HasAlternate(const statement::IfStatement& begin, const statement::Statement& end) {
  decDepth();
  createIndentation();
  ofs << "</IfStatement_HasAlternate>\n";
}

void VisitorJAVASCRIPTML::visitLabeledStatement_HasLabel(const statement::LabeledStatement& begin, const expression::Identifier& end) {
  createIndentation();
  ofs << "<LabeledStatement_HasLabel>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndLabeledStatement_HasLabel(const statement::LabeledStatement& begin, const expression::Identifier& end) {
  decDepth();
  createIndentation();
  ofs << "</LabeledStatement_HasLabel>\n";
}

void VisitorJAVASCRIPTML::visitLabeledStatement_HasBody(const statement::LabeledStatement& begin, const statement::Statement& end) {
  createIndentation();
  ofs << "<LabeledStatement_HasBody>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndLabeledStatement_HasBody(const statement::LabeledStatement& begin, const statement::Statement& end) {
  decDepth();
  createIndentation();
  ofs << "</LabeledStatement_HasBody>\n";
}

void VisitorJAVASCRIPTML::visitObjectPattern_HasProperties(const statement::ObjectPattern& begin, const expression::Property& end) {
  createIndentation();
  ofs << "<ObjectPattern_HasProperties>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndObjectPattern_HasProperties(const statement::ObjectPattern& begin, const expression::Property& end) {
  decDepth();
  createIndentation();
  ofs << "</ObjectPattern_HasProperties>\n";
}

void VisitorJAVASCRIPTML::visitRestElement_HasArgument(const statement::RestElement& begin, const statement::Pattern& end) {
  createIndentation();
  ofs << "<RestElement_HasArgument>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndRestElement_HasArgument(const statement::RestElement& begin, const statement::Pattern& end) {
  decDepth();
  createIndentation();
  ofs << "</RestElement_HasArgument>\n";
}

void VisitorJAVASCRIPTML::visitReturnStatement_HasArgument(const statement::ReturnStatement& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<ReturnStatement_HasArgument>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndReturnStatement_HasArgument(const statement::ReturnStatement& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</ReturnStatement_HasArgument>\n";
}

void VisitorJAVASCRIPTML::visitSwitchCase_HasTest(const statement::SwitchCase& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<SwitchCase_HasTest>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndSwitchCase_HasTest(const statement::SwitchCase& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</SwitchCase_HasTest>\n";
}

void VisitorJAVASCRIPTML::visitSwitchCase_HasConsequent(const statement::SwitchCase& begin, const statement::Statement& end) {
  createIndentation();
  ofs << "<SwitchCase_HasConsequent>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndSwitchCase_HasConsequent(const statement::SwitchCase& begin, const statement::Statement& end) {
  decDepth();
  createIndentation();
  ofs << "</SwitchCase_HasConsequent>\n";
}

void VisitorJAVASCRIPTML::visitSwitchStatement_HasDiscriminant(const statement::SwitchStatement& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<SwitchStatement_HasDiscriminant>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndSwitchStatement_HasDiscriminant(const statement::SwitchStatement& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</SwitchStatement_HasDiscriminant>\n";
}

void VisitorJAVASCRIPTML::visitSwitchStatement_HasCases(const statement::SwitchStatement& begin, const statement::SwitchCase& end) {
  createIndentation();
  ofs << "<SwitchStatement_HasCases>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndSwitchStatement_HasCases(const statement::SwitchStatement& begin, const statement::SwitchCase& end) {
  decDepth();
  createIndentation();
  ofs << "</SwitchStatement_HasCases>\n";
}

void VisitorJAVASCRIPTML::visitThrowStatement_HasArgument(const statement::ThrowStatement& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<ThrowStatement_HasArgument>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndThrowStatement_HasArgument(const statement::ThrowStatement& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</ThrowStatement_HasArgument>\n";
}

void VisitorJAVASCRIPTML::visitTryStatement_HasBlock(const statement::TryStatement& begin, const statement::BlockStatement& end) {
  createIndentation();
  ofs << "<TryStatement_HasBlock>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndTryStatement_HasBlock(const statement::TryStatement& begin, const statement::BlockStatement& end) {
  decDepth();
  createIndentation();
  ofs << "</TryStatement_HasBlock>\n";
}

void VisitorJAVASCRIPTML::visitTryStatement_HasFinalizer(const statement::TryStatement& begin, const statement::BlockStatement& end) {
  createIndentation();
  ofs << "<TryStatement_HasFinalizer>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndTryStatement_HasFinalizer(const statement::TryStatement& begin, const statement::BlockStatement& end) {
  decDepth();
  createIndentation();
  ofs << "</TryStatement_HasFinalizer>\n";
}

void VisitorJAVASCRIPTML::visitTryStatement_HasHandler(const statement::TryStatement& begin, const statement::CatchClause& end) {
  createIndentation();
  ofs << "<TryStatement_HasHandler>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndTryStatement_HasHandler(const statement::TryStatement& begin, const statement::CatchClause& end) {
  decDepth();
  createIndentation();
  ofs << "</TryStatement_HasHandler>\n";
}

void VisitorJAVASCRIPTML::visitWhileStatement_HasBody(const statement::WhileStatement& begin, const statement::Statement& end) {
  createIndentation();
  ofs << "<WhileStatement_HasBody>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndWhileStatement_HasBody(const statement::WhileStatement& begin, const statement::Statement& end) {
  decDepth();
  createIndentation();
  ofs << "</WhileStatement_HasBody>\n";
}

void VisitorJAVASCRIPTML::visitWhileStatement_HasTest(const statement::WhileStatement& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<WhileStatement_HasTest>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndWhileStatement_HasTest(const statement::WhileStatement& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</WhileStatement_HasTest>\n";
}

void VisitorJAVASCRIPTML::visitWithStatement_HasObject(const statement::WithStatement& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<WithStatement_HasObject>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndWithStatement_HasObject(const statement::WithStatement& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</WithStatement_HasObject>\n";
}

void VisitorJAVASCRIPTML::visitWithStatement_HasBody(const statement::WithStatement& begin, const statement::Statement& end) {
  createIndentation();
  ofs << "<WithStatement_HasBody>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndWithStatement_HasBody(const statement::WithStatement& begin, const statement::Statement& end) {
  decDepth();
  createIndentation();
  ofs << "</WithStatement_HasBody>\n";
}

void VisitorJAVASCRIPTML::visitClass_HasBody(const structure::Class& begin, const structure::ClassBody& end) {
  createIndentation();
  ofs << "<Class_HasBody>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndClass_HasBody(const structure::Class& begin, const structure::ClassBody& end) {
  decDepth();
  createIndentation();
  ofs << "</Class_HasBody>\n";
}

void VisitorJAVASCRIPTML::visitClass_HasSuperClass(const structure::Class& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Class_HasSuperClass>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndClass_HasSuperClass(const structure::Class& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Class_HasSuperClass>\n";
}

void VisitorJAVASCRIPTML::visitClass_HasIdentifier(const structure::Class& begin, const expression::Identifier& end) {
  createIndentation();
  ofs << "<Class_HasIdentifier>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndClass_HasIdentifier(const structure::Class& begin, const expression::Identifier& end) {
  decDepth();
  createIndentation();
  ofs << "</Class_HasIdentifier>\n";
}

void VisitorJAVASCRIPTML::visitClassBody_HasBody(const structure::ClassBody& begin, const structure::MethodDefinition& end) {
  createIndentation();
  ofs << "<ClassBody_HasBody>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndClassBody_HasBody(const structure::ClassBody& begin, const structure::MethodDefinition& end) {
  decDepth();
  createIndentation();
  ofs << "</ClassBody_HasBody>\n";
}

void VisitorJAVASCRIPTML::visitExportSpecifier_HasExported(const structure::ExportSpecifier& begin, const expression::Identifier& end) {
  createIndentation();
  ofs << "<ExportSpecifier_HasExported>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndExportSpecifier_HasExported(const structure::ExportSpecifier& begin, const expression::Identifier& end) {
  decDepth();
  createIndentation();
  ofs << "</ExportSpecifier_HasExported>\n";
}

void VisitorJAVASCRIPTML::visitImportSpecifier_HasImported(const structure::ImportSpecifier& begin, const expression::Identifier& end) {
  createIndentation();
  ofs << "<ImportSpecifier_HasImported>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndImportSpecifier_HasImported(const structure::ImportSpecifier& begin, const expression::Identifier& end) {
  decDepth();
  createIndentation();
  ofs << "</ImportSpecifier_HasImported>\n";
}

void VisitorJAVASCRIPTML::visitMethodDefinition_HasKey(const structure::MethodDefinition& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<MethodDefinition_HasKey>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndMethodDefinition_HasKey(const structure::MethodDefinition& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</MethodDefinition_HasKey>\n";
}

void VisitorJAVASCRIPTML::visitMethodDefinition_HasValue(const structure::MethodDefinition& begin, const expression::FunctionExpression& end) {
  createIndentation();
  ofs << "<MethodDefinition_HasValue>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndMethodDefinition_HasValue(const structure::MethodDefinition& begin, const expression::FunctionExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</MethodDefinition_HasValue>\n";
}

void VisitorJAVASCRIPTML::visitModuleSpecifier_HasLocal(const structure::ModuleSpecifier& begin, const expression::Identifier& end) {
  createIndentation();
  ofs << "<ModuleSpecifier_HasLocal>\n";
  incDepth();
}

void VisitorJAVASCRIPTML::visitEndModuleSpecifier_HasLocal(const structure::ModuleSpecifier& begin, const expression::Identifier& end) {
  decDepth();
  createIndentation();
  ofs << "</ModuleSpecifier_HasLocal>\n";
}

void VisitorJAVASCRIPTML::createIndentation() {
  if (depth)
    ofs << std::string(depth, '\t');
}

string VisitorJAVASCRIPTML::chk(string s) {
  string::size_type pos = (string::size_type)-1;
  while ((pos = s.find("&", pos + 1)) != string::npos)
    s.replace(pos, 1, "&amp;");

  while ((pos = s.find("<", pos + 1)) != string::npos)
    s.replace(pos,1, "&lt;");

  while ((pos = s.find(">", pos + 1)) != string::npos)
    s.replace(pos,1, "&gt;");

  while ((pos = s.find("'", pos + 1)) != string::npos)
    s.replace(pos,1,"&apos;");

  while ((pos = s.find("\"", pos + 1)) != string::npos)
    s.replace(pos,1,"&quot;");

  while ((pos = s.find("\r", pos + 1)) != string::npos)
    s.replace(pos,1, "&#13;");

  while ((pos = s.find("\n", pos + 1)) != string::npos)
    s.replace(pos,1, "&#10;");

  while ((pos = s.find("\t", pos + 1)) != string::npos)
    s.replace(pos,1, "&#09;");

  return s;
}

void VisitorJAVASCRIPTML::writeRange(const char *name, const Range &range) {
  if(noLineInfo) return;
  incDepth();
  createIndentation();
  ofs << "<" << name << " path='" << chk(range.getPath()) << "'";
  ofs << " line='" << range.getLine() << "'";
  ofs << " col='" << range.getCol() << "'";
  ofs << " endLine='" << range.getEndLine() << "'";
  ofs << " endCol='" << range.getEndCol() << "'";
  ofs << " wideLine='" << range.getWideLine() << "'";
  ofs << " wideCol='" << range.getWideCol() << "'";
  ofs << " wideEndLine='" << range.getWideEndLine() << "'";
  ofs << " wideEndCol='" << range.getWideEndCol() << "'";
  ofs << "/>\n";
  decDepth();
}

void VisitorJAVASCRIPTML::writeAttributes(const base::Base& node,bool composite, bool bWithParent /*= true*/ ) {
  if (!composite) {
    ofs << " id='";
    if (!noId)
      ofs << "id" << node.getId();
    ofs << "'";

  }
  if (!composite) {
    ofs << " parent='";
    if (!noId)
      ofs << "id" << (node.getParent() ? node.getParent()->getId() : 0);
    ofs << "'";

  }
  if (!composite) {
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const base::Comment& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

  if (!composite) {
    ofs << " text='" << chk(node.getText()) << "'";
  }
  if (!composite) {
    ofs << " type='" << Common::toString(node.getType()) << "'";
  }
  if (!composite) {
    ofs << " location='" << Common::toString(node.getLocation()) << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const base::Named& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  if (!composite) {
    ofs << " name='" << chk(node.getName()) << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const base::Positioned& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Base&)node,composite,false);

  if (composite) {
    writeRange("Position", node.getPosition());
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const base::Program& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((base::Named&)node,composite,false);

  if (!composite) {
    ofs << " sourceType='" << Common::toString(node.getSourceType()) << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const base::System& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Base&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const declaration::ClassDeclaration& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((declaration::Declaration&)node,composite,false);

  writeAttributes((structure::Class&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const declaration::Declaration& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const declaration::ExportAllDeclaration& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((declaration::Declaration&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const declaration::ExportDefaultDeclaration& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((declaration::Declaration&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const declaration::ExportNamedDeclaration& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((declaration::ModuleDeclaration&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const declaration::FunctionDeclaration& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Function&)node,composite,false);

  writeAttributes((declaration::Declaration&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const declaration::ImportDeclaration& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((declaration::ModuleDeclaration&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const declaration::ModuleDeclaration& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const declaration::VariableDeclaration& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((declaration::Declaration&)node,composite,false);

  if (!composite) {
    ofs << " kind='" << Common::toString(node.getKind()) << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const declaration::VariableDeclarator& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const expression::ArrayExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const expression::ArrowFunctionExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

  writeAttributes((statement::Function&)node,composite,false);

  if (!composite) {
    ofs << " expression='" << (node.getExpression() ? "true" : "false") << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const expression::AssignmentExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

  if (!composite) {
    ofs << " operator='" << Common::toString(node.getOperator()) << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const expression::AssignmentProperty& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Property&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const expression::AwaitExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const expression::BinaryExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

  if (!composite) {
    ofs << " operator='" << Common::toString(node.getOperator()) << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const expression::BooleanLiteral& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Literal&)node,composite,false);

  if (!composite) {
    ofs << " value='" << (node.getValue() ? "true" : "false") << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const expression::CallExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const expression::ClassExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

  writeAttributes((structure::Class&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const expression::ConditionalExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const expression::Expression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const expression::FunctionExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

  writeAttributes((statement::Function&)node,composite,false);

  if (!composite) {
    ofs << " expression='" << (node.getExpression() ? "true" : "false") << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const expression::Identifier& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

  writeAttributes((statement::Pattern&)node,composite,false);

  writeAttributes((base::Named&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const expression::Literal& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

  if (!composite) {
    ofs << " raw='" << chk(node.getRaw()) << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const expression::LogicalExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

  if (!composite) {
    ofs << " operator='" << Common::toString(node.getOperator()) << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const expression::MemberExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

  writeAttributes((statement::Pattern&)node,composite,false);

  if (!composite) {
    ofs << " computed='" << (node.getComputed() ? "true" : "false") << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const expression::MetaProperty& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const expression::NewExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const expression::NullLiteral& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Literal&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const expression::NumberLiteral& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Literal&)node,composite,false);

  if (!composite) {
    ofs << " value='" << node.getValue() << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const expression::ObjectExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const expression::Property& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

  if (!composite) {
    ofs << " kind='" << Common::toString(node.getKind()) << "'";
  }
  if (!composite) {
    ofs << " method='" << (node.getMethod() ? "true" : "false") << "'";
  }
  if (!composite) {
    ofs << " shorthand='" << (node.getShorthand() ? "true" : "false") << "'";
  }
  if (!composite) {
    ofs << " computed='" << (node.getComputed() ? "true" : "false") << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const expression::RegExpLiteral& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Literal&)node,composite,false);

  if (!composite) {
    ofs << " pattern='" << chk(node.getPattern()) << "'";
  }
  if (!composite) {
    ofs << " flags='" << chk(node.getFlags()) << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const expression::SequenceExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const expression::SpreadElement& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const expression::StringLiteral& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Literal&)node,composite,false);

  if (!composite) {
    ofs << " value='" << chk(node.getValue()) << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const expression::Super& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const expression::TaggedTemplateExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const expression::TemplateElement& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

  if (!composite) {
    ofs << " tail='" << (node.getTail() ? "true" : "false") << "'";
  }
  if (!composite) {
    ofs << " cooked='" << chk(node.getCooked()) << "'";
  }
  if (!composite) {
    ofs << " value='" << chk(node.getValue()) << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const expression::TemplateLiteral& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const expression::ThisExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const expression::UnaryExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

  if (!composite) {
    ofs << " operator='" << Common::toString(node.getOperator()) << "'";
  }
  if (!composite) {
    ofs << " prefix='" << (node.getPrefix() ? "true" : "false") << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const expression::UpdateExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

  if (!composite) {
    ofs << " operator='" << Common::toString(node.getOperator()) << "'";
  }
  if (!composite) {
    ofs << " prefix='" << (node.getPrefix() ? "true" : "false") << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const expression::YieldExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((expression::Expression&)node,composite,false);

  if (!composite) {
    ofs << " delegate='" << (node.getDelegate() ? "true" : "false") << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const statement::ArrayPattern& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Pattern&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::AssignmentPattern& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Pattern&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::BlockStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::BreakStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::CatchClause& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::ContinueStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::DebuggerStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::DoWhileStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::WhileStatement&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::EmptyStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::ExpressionStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::ForInStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::ForOfStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::ForInStatement&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::ForStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::Function& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  if (!composite) {
    ofs << " generator='" << (node.getGenerator() ? "true" : "false") << "'";
  }
  if (!composite) {
    ofs << " async='" << (node.getAsync() ? "true" : "false") << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const statement::IfStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::LabeledStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::ObjectPattern& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Pattern&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::Pattern& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::RestElement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Pattern&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::ReturnStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::Statement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::SwitchCase& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::SwitchStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::ThrowStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::TryStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::WhileStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const statement::WithStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const structure::Class& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const structure::ClassBody& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const structure::ExportSpecifier& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::ModuleSpecifier&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const structure::ImpSpecifier& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::ModuleSpecifier&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const structure::ImportDefaultSpecifier& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::ImpSpecifier&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const structure::ImportNamespaceSpecifier& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::ImpSpecifier&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const structure::ImportSpecifier& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::ImpSpecifier&)node,composite,false);

}

void VisitorJAVASCRIPTML::writeAttributes(const structure::MethodDefinition& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

  if (!composite) {
    ofs << " kind='" << Common::toString(node.getKind()) << "'";
  }
  if (!composite) {
    ofs << " computed='" << (node.getComputed() ? "true" : "false") << "'";
  }
  if (!composite) {
    ofs << " static='" << (node.getStatic() ? "true" : "false") << "'";
  }
}

void VisitorJAVASCRIPTML::writeAttributes(const structure::ModuleSpecifier& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}


}}}
