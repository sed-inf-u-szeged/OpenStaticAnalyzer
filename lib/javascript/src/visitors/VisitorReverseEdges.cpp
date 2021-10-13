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
VisitorReverseEdges::VisitorReverseEdges(ReverseEdges *reverseEdges) : VisitorAbstractNodes(), revEdges(reverseEdges) {
}

VisitorReverseEdges::~VisitorReverseEdges() {
}

void VisitorReverseEdges::visit(const base::Base &node, bool callVirtualBase ) {
  NodeId id = node.getId();
  if (!revEdges->reContainer[id])
    revEdges->reContainer[id] = new ReverseEdges::NodeEdgesType();
}

void VisitorReverseEdges::visitPositioned_Comments(const base::Positioned& begin, const base::Comment& end) {
  revEdges->insertEdge(&end, &begin, edkPositioned_Comments);
}

void VisitorReverseEdges::visitProgram_HasBody(const base::Program& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkProgram_HasBody);
}

void VisitorReverseEdges::visitSystem_HasPrograms(const base::System& begin, const base::Program& end) {
  revEdges->insertEdge(&end, &begin, edkSystem_HasPrograms);
}

void VisitorReverseEdges::visitExportAllDeclaration_HasSource(const declaration::ExportAllDeclaration& begin, const expression::Literal& end) {
  revEdges->insertEdge(&end, &begin, edkExportAllDeclaration_HasSource);
}

void VisitorReverseEdges::visitExportDefaultDeclaration_HasDeclaration(const declaration::ExportDefaultDeclaration& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkExportDefaultDeclaration_HasDeclaration);
}

void VisitorReverseEdges::visitExportNamedDeclaration_HasDeclaration(const declaration::ExportNamedDeclaration& begin, const declaration::Declaration& end) {
  revEdges->insertEdge(&end, &begin, edkExportNamedDeclaration_HasDeclaration);
}

void VisitorReverseEdges::visitExportNamedDeclaration_HasSpecifiers(const declaration::ExportNamedDeclaration& begin, const structure::ExportSpecifier& end) {
  revEdges->insertEdge(&end, &begin, edkExportNamedDeclaration_HasSpecifiers);
}

void VisitorReverseEdges::visitExportNamedDeclaration_HasSource(const declaration::ExportNamedDeclaration& begin, const expression::Literal& end) {
  revEdges->insertEdge(&end, &begin, edkExportNamedDeclaration_HasSource);
}

void VisitorReverseEdges::visitImportDeclaration_HasSpecifiers(const declaration::ImportDeclaration& begin, const structure::ImpSpecifier& end) {
  revEdges->insertEdge(&end, &begin, edkImportDeclaration_HasSpecifiers);
}

void VisitorReverseEdges::visitImportDeclaration_HasSource(const declaration::ImportDeclaration& begin, const expression::Literal& end) {
  revEdges->insertEdge(&end, &begin, edkImportDeclaration_HasSource);
}

void VisitorReverseEdges::visitVariableDeclaration_HasDeclarations(const declaration::VariableDeclaration& begin, const declaration::VariableDeclarator& end) {
  revEdges->insertEdge(&end, &begin, edkVariableDeclaration_HasDeclarations);
}

void VisitorReverseEdges::visitVariableDeclarator_HasIdentifier(const declaration::VariableDeclarator& begin, const statement::Pattern& end) {
  revEdges->insertEdge(&end, &begin, edkVariableDeclarator_HasIdentifier);
}

void VisitorReverseEdges::visitVariableDeclarator_HasInit(const declaration::VariableDeclarator& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkVariableDeclarator_HasInit);
}

void VisitorReverseEdges::visitArrayExpression_HasElements(const expression::ArrayExpression& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkArrayExpression_HasElements);
}

void VisitorReverseEdges::visitAssignmentExpression_HasLeft(const expression::AssignmentExpression& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkAssignmentExpression_HasLeft);
}

void VisitorReverseEdges::visitAssignmentExpression_HasRight(const expression::AssignmentExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkAssignmentExpression_HasRight);
}

void VisitorReverseEdges::visitAwaitExpression_HasArgument(const expression::AwaitExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkAwaitExpression_HasArgument);
}

void VisitorReverseEdges::visitBinaryExpression_HasLeft(const expression::BinaryExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkBinaryExpression_HasLeft);
}

void VisitorReverseEdges::visitBinaryExpression_HasRight(const expression::BinaryExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkBinaryExpression_HasRight);
}

void VisitorReverseEdges::visitCallExpression_HasCallee(const expression::CallExpression& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkCallExpression_HasCallee);
}

void VisitorReverseEdges::visitCallExpression_HasArguments(const expression::CallExpression& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkCallExpression_HasArguments);
}

void VisitorReverseEdges::visitCallExpression_Calls(const expression::CallExpression& begin, const statement::Function& end) {
  revEdges->insertEdge(&end, &begin, edkCallExpression_Calls);
}

void VisitorReverseEdges::visitConditionalExpression_HasAlternate(const expression::ConditionalExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkConditionalExpression_HasAlternate);
}

void VisitorReverseEdges::visitConditionalExpression_HasConsequent(const expression::ConditionalExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkConditionalExpression_HasConsequent);
}

void VisitorReverseEdges::visitConditionalExpression_HasTest(const expression::ConditionalExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkConditionalExpression_HasTest);
}

void VisitorReverseEdges::visitIdentifier_RefersTo(const expression::Identifier& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkIdentifier_RefersTo);
}

void VisitorReverseEdges::visitLogicalExpression_HasLeft(const expression::LogicalExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkLogicalExpression_HasLeft);
}

void VisitorReverseEdges::visitLogicalExpression_HasRight(const expression::LogicalExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkLogicalExpression_HasRight);
}

void VisitorReverseEdges::visitMemberExpression_HasProperty(const expression::MemberExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkMemberExpression_HasProperty);
}

void VisitorReverseEdges::visitMemberExpression_HasObject(const expression::MemberExpression& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkMemberExpression_HasObject);
}

void VisitorReverseEdges::visitMetaProperty_HasMeta(const expression::MetaProperty& begin, const expression::Identifier& end) {
  revEdges->insertEdge(&end, &begin, edkMetaProperty_HasMeta);
}

void VisitorReverseEdges::visitMetaProperty_HasProperty(const expression::MetaProperty& begin, const expression::Identifier& end) {
  revEdges->insertEdge(&end, &begin, edkMetaProperty_HasProperty);
}

void VisitorReverseEdges::visitNewExpression_HasCallee(const expression::NewExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkNewExpression_HasCallee);
}

void VisitorReverseEdges::visitNewExpression_HasArguments(const expression::NewExpression& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkNewExpression_HasArguments);
}

void VisitorReverseEdges::visitNewExpression_Calls(const expression::NewExpression& begin, const statement::Function& end) {
  revEdges->insertEdge(&end, &begin, edkNewExpression_Calls);
}

void VisitorReverseEdges::visitObjectExpression_HasProperties(const expression::ObjectExpression& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkObjectExpression_HasProperties);
}

void VisitorReverseEdges::visitProperty_HasValue(const expression::Property& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkProperty_HasValue);
}

void VisitorReverseEdges::visitProperty_HasKey(const expression::Property& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkProperty_HasKey);
}

void VisitorReverseEdges::visitSequenceExpression_HasExpressions(const expression::SequenceExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkSequenceExpression_HasExpressions);
}

void VisitorReverseEdges::visitSpreadElement_HasArgument(const expression::SpreadElement& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkSpreadElement_HasArgument);
}

void VisitorReverseEdges::visitTaggedTemplateExpression_HasTag(const expression::TaggedTemplateExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkTaggedTemplateExpression_HasTag);
}

void VisitorReverseEdges::visitTaggedTemplateExpression_HasQuasi(const expression::TaggedTemplateExpression& begin, const expression::TemplateLiteral& end) {
  revEdges->insertEdge(&end, &begin, edkTaggedTemplateExpression_HasQuasi);
}

void VisitorReverseEdges::visitTemplateLiteral_HasQuasis(const expression::TemplateLiteral& begin, const expression::TemplateElement& end) {
  revEdges->insertEdge(&end, &begin, edkTemplateLiteral_HasQuasis);
}

void VisitorReverseEdges::visitTemplateLiteral_HasExpressions(const expression::TemplateLiteral& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkTemplateLiteral_HasExpressions);
}

void VisitorReverseEdges::visitUnaryExpression_HasArgument(const expression::UnaryExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkUnaryExpression_HasArgument);
}

void VisitorReverseEdges::visitUpdateExpression_HasArgument(const expression::UpdateExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkUpdateExpression_HasArgument);
}

void VisitorReverseEdges::visitYieldExpression_HasArgument(const expression::YieldExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkYieldExpression_HasArgument);
}

void VisitorReverseEdges::visitArrayPattern_HasElements(const statement::ArrayPattern& begin, const statement::Pattern& end) {
  revEdges->insertEdge(&end, &begin, edkArrayPattern_HasElements);
}

void VisitorReverseEdges::visitAssignmentPattern_HasLeft(const statement::AssignmentPattern& begin, const statement::Pattern& end) {
  revEdges->insertEdge(&end, &begin, edkAssignmentPattern_HasLeft);
}

void VisitorReverseEdges::visitAssignmentPattern_HasRight(const statement::AssignmentPattern& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkAssignmentPattern_HasRight);
}

void VisitorReverseEdges::visitBlockStatement_HasBody(const statement::BlockStatement& begin, const statement::Statement& end) {
  revEdges->insertEdge(&end, &begin, edkBlockStatement_HasBody);
}

void VisitorReverseEdges::visitBreakStatement_HasLabel(const statement::BreakStatement& begin, const expression::Identifier& end) {
  revEdges->insertEdge(&end, &begin, edkBreakStatement_HasLabel);
}

void VisitorReverseEdges::visitCatchClause_HasParam(const statement::CatchClause& begin, const statement::Pattern& end) {
  revEdges->insertEdge(&end, &begin, edkCatchClause_HasParam);
}

void VisitorReverseEdges::visitCatchClause_HasBody(const statement::CatchClause& begin, const statement::BlockStatement& end) {
  revEdges->insertEdge(&end, &begin, edkCatchClause_HasBody);
}

void VisitorReverseEdges::visitContinueStatement_HasLabel(const statement::ContinueStatement& begin, const expression::Identifier& end) {
  revEdges->insertEdge(&end, &begin, edkContinueStatement_HasLabel);
}

void VisitorReverseEdges::visitExpressionStatement_HasExpression(const statement::ExpressionStatement& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkExpressionStatement_HasExpression);
}

void VisitorReverseEdges::visitForInStatement_HasRight(const statement::ForInStatement& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkForInStatement_HasRight);
}

void VisitorReverseEdges::visitForInStatement_HasBody(const statement::ForInStatement& begin, const statement::Statement& end) {
  revEdges->insertEdge(&end, &begin, edkForInStatement_HasBody);
}

void VisitorReverseEdges::visitForInStatement_HasLeft(const statement::ForInStatement& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkForInStatement_HasLeft);
}

void VisitorReverseEdges::visitForStatement_HasBody(const statement::ForStatement& begin, const statement::Statement& end) {
  revEdges->insertEdge(&end, &begin, edkForStatement_HasBody);
}

void VisitorReverseEdges::visitForStatement_HasTest(const statement::ForStatement& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkForStatement_HasTest);
}

void VisitorReverseEdges::visitForStatement_HasUpdate(const statement::ForStatement& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkForStatement_HasUpdate);
}

void VisitorReverseEdges::visitForStatement_HasInit(const statement::ForStatement& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkForStatement_HasInit);
}

void VisitorReverseEdges::visitFunction_HasParams(const statement::Function& begin, const statement::Pattern& end) {
  revEdges->insertEdge(&end, &begin, edkFunction_HasParams);
}

void VisitorReverseEdges::visitFunction_HasBody(const statement::Function& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkFunction_HasBody);
}

void VisitorReverseEdges::visitFunction_HasIdentifier(const statement::Function& begin, const expression::Identifier& end) {
  revEdges->insertEdge(&end, &begin, edkFunction_HasIdentifier);
}

void VisitorReverseEdges::visitIfStatement_HasTest(const statement::IfStatement& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkIfStatement_HasTest);
}

void VisitorReverseEdges::visitIfStatement_HasConsequent(const statement::IfStatement& begin, const statement::Statement& end) {
  revEdges->insertEdge(&end, &begin, edkIfStatement_HasConsequent);
}

void VisitorReverseEdges::visitIfStatement_HasAlternate(const statement::IfStatement& begin, const statement::Statement& end) {
  revEdges->insertEdge(&end, &begin, edkIfStatement_HasAlternate);
}

void VisitorReverseEdges::visitLabeledStatement_HasLabel(const statement::LabeledStatement& begin, const expression::Identifier& end) {
  revEdges->insertEdge(&end, &begin, edkLabeledStatement_HasLabel);
}

void VisitorReverseEdges::visitLabeledStatement_HasBody(const statement::LabeledStatement& begin, const statement::Statement& end) {
  revEdges->insertEdge(&end, &begin, edkLabeledStatement_HasBody);
}

void VisitorReverseEdges::visitObjectPattern_HasProperties(const statement::ObjectPattern& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkObjectPattern_HasProperties);
}

void VisitorReverseEdges::visitRestElement_HasArgument(const statement::RestElement& begin, const statement::Pattern& end) {
  revEdges->insertEdge(&end, &begin, edkRestElement_HasArgument);
}

void VisitorReverseEdges::visitReturnStatement_HasArgument(const statement::ReturnStatement& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkReturnStatement_HasArgument);
}

void VisitorReverseEdges::visitSwitchCase_HasTest(const statement::SwitchCase& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkSwitchCase_HasTest);
}

void VisitorReverseEdges::visitSwitchCase_HasConsequent(const statement::SwitchCase& begin, const statement::Statement& end) {
  revEdges->insertEdge(&end, &begin, edkSwitchCase_HasConsequent);
}

void VisitorReverseEdges::visitSwitchStatement_HasDiscriminant(const statement::SwitchStatement& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkSwitchStatement_HasDiscriminant);
}

void VisitorReverseEdges::visitSwitchStatement_HasCases(const statement::SwitchStatement& begin, const statement::SwitchCase& end) {
  revEdges->insertEdge(&end, &begin, edkSwitchStatement_HasCases);
}

void VisitorReverseEdges::visitThrowStatement_HasArgument(const statement::ThrowStatement& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkThrowStatement_HasArgument);
}

void VisitorReverseEdges::visitTryStatement_HasBlock(const statement::TryStatement& begin, const statement::BlockStatement& end) {
  revEdges->insertEdge(&end, &begin, edkTryStatement_HasBlock);
}

void VisitorReverseEdges::visitTryStatement_HasFinalizer(const statement::TryStatement& begin, const statement::BlockStatement& end) {
  revEdges->insertEdge(&end, &begin, edkTryStatement_HasFinalizer);
}

void VisitorReverseEdges::visitTryStatement_HasHandler(const statement::TryStatement& begin, const statement::CatchClause& end) {
  revEdges->insertEdge(&end, &begin, edkTryStatement_HasHandler);
}

void VisitorReverseEdges::visitWhileStatement_HasBody(const statement::WhileStatement& begin, const statement::Statement& end) {
  revEdges->insertEdge(&end, &begin, edkWhileStatement_HasBody);
}

void VisitorReverseEdges::visitWhileStatement_HasTest(const statement::WhileStatement& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkWhileStatement_HasTest);
}

void VisitorReverseEdges::visitWithStatement_HasObject(const statement::WithStatement& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkWithStatement_HasObject);
}

void VisitorReverseEdges::visitWithStatement_HasBody(const statement::WithStatement& begin, const statement::Statement& end) {
  revEdges->insertEdge(&end, &begin, edkWithStatement_HasBody);
}

void VisitorReverseEdges::visitClass_HasBody(const structure::Class& begin, const structure::ClassBody& end) {
  revEdges->insertEdge(&end, &begin, edkClass_HasBody);
}

void VisitorReverseEdges::visitClass_HasSuperClass(const structure::Class& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkClass_HasSuperClass);
}

void VisitorReverseEdges::visitClass_HasIdentifier(const structure::Class& begin, const expression::Identifier& end) {
  revEdges->insertEdge(&end, &begin, edkClass_HasIdentifier);
}

void VisitorReverseEdges::visitClassBody_HasBody(const structure::ClassBody& begin, const structure::MethodDefinition& end) {
  revEdges->insertEdge(&end, &begin, edkClassBody_HasBody);
}

void VisitorReverseEdges::visitExportSpecifier_HasExported(const structure::ExportSpecifier& begin, const expression::Identifier& end) {
  revEdges->insertEdge(&end, &begin, edkExportSpecifier_HasExported);
}

void VisitorReverseEdges::visitImportSpecifier_HasImported(const structure::ImportSpecifier& begin, const expression::Identifier& end) {
  revEdges->insertEdge(&end, &begin, edkImportSpecifier_HasImported);
}

void VisitorReverseEdges::visitMethodDefinition_HasKey(const structure::MethodDefinition& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkMethodDefinition_HasKey);
}

void VisitorReverseEdges::visitMethodDefinition_HasValue(const structure::MethodDefinition& begin, const expression::FunctionExpression& end) {
  revEdges->insertEdge(&end, &begin, edkMethodDefinition_HasValue);
}

void VisitorReverseEdges::visitModuleSpecifier_HasLocal(const structure::ModuleSpecifier& begin, const expression::Identifier& end) {
  revEdges->insertEdge(&end, &begin, edkModuleSpecifier_HasLocal);
}


}}}
