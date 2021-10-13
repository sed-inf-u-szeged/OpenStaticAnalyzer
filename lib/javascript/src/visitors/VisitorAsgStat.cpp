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

const char* VisitorAsgStat::nodeNames[] = {
        "base::Base",
        "base::Comment",
        "base::Named",
        "base::Positioned",
        "base::Program",
        "base::System",
        "declaration::ClassDeclaration",
        "declaration::Declaration",
        "declaration::ExportAllDeclaration",
        "declaration::ExportDefaultDeclaration",
        "declaration::ExportNamedDeclaration",
        "declaration::FunctionDeclaration",
        "declaration::ImportDeclaration",
        "declaration::ModuleDeclaration",
        "declaration::VariableDeclaration",
        "declaration::VariableDeclarator",
        "expression::ArrayExpression",
        "expression::ArrowFunctionExpression",
        "expression::AssignmentExpression",
        "expression::AssignmentProperty",
        "expression::AwaitExpression",
        "expression::BinaryExpression",
        "expression::BooleanLiteral",
        "expression::CallExpression",
        "expression::ClassExpression",
        "expression::ConditionalExpression",
        "expression::Expression",
        "expression::FunctionExpression",
        "expression::Identifier",
        "expression::Literal",
        "expression::LogicalExpression",
        "expression::MemberExpression",
        "expression::MetaProperty",
        "expression::NewExpression",
        "expression::NullLiteral",
        "expression::NumberLiteral",
        "expression::ObjectExpression",
        "expression::Property",
        "expression::RegExpLiteral",
        "expression::SequenceExpression",
        "expression::SpreadElement",
        "expression::StringLiteral",
        "expression::Super",
        "expression::TaggedTemplateExpression",
        "expression::TemplateElement",
        "expression::TemplateLiteral",
        "expression::ThisExpression",
        "expression::UnaryExpression",
        "expression::UpdateExpression",
        "expression::YieldExpression",
        "statement::ArrayPattern",
        "statement::AssignmentPattern",
        "statement::BlockStatement",
        "statement::BreakStatement",
        "statement::CatchClause",
        "statement::ContinueStatement",
        "statement::DebuggerStatement",
        "statement::DoWhileStatement",
        "statement::EmptyStatement",
        "statement::ExpressionStatement",
        "statement::ForInStatement",
        "statement::ForOfStatement",
        "statement::ForStatement",
        "statement::Function",
        "statement::IfStatement",
        "statement::LabeledStatement",
        "statement::ObjectPattern",
        "statement::Pattern",
        "statement::RestElement",
        "statement::ReturnStatement",
        "statement::Statement",
        "statement::SwitchCase",
        "statement::SwitchStatement",
        "statement::ThrowStatement",
        "statement::TryStatement",
        "statement::WhileStatement",
        "statement::WithStatement",
        "structure::Class",
        "structure::ClassBody",
        "structure::ExportSpecifier",
        "structure::ImpSpecifier",
        "structure::ImportDefaultSpecifier",
        "structure::ImportNamespaceSpecifier",
        "structure::ImportSpecifier",
        "structure::MethodDefinition",
        "structure::ModuleSpecifier",
};

const unsigned short VisitorAsgStat::nodeSizes[] = {
        sizeof(base::Base),
        sizeof(base::Comment),
        sizeof(base::Named),
        sizeof(base::Positioned),
        sizeof(base::Program),
        sizeof(base::System),
        sizeof(declaration::ClassDeclaration),
        sizeof(declaration::Declaration),
        sizeof(declaration::ExportAllDeclaration),
        sizeof(declaration::ExportDefaultDeclaration),
        sizeof(declaration::ExportNamedDeclaration),
        sizeof(declaration::FunctionDeclaration),
        sizeof(declaration::ImportDeclaration),
        sizeof(declaration::ModuleDeclaration),
        sizeof(declaration::VariableDeclaration),
        sizeof(declaration::VariableDeclarator),
        sizeof(expression::ArrayExpression),
        sizeof(expression::ArrowFunctionExpression),
        sizeof(expression::AssignmentExpression),
        sizeof(expression::AssignmentProperty),
        sizeof(expression::AwaitExpression),
        sizeof(expression::BinaryExpression),
        sizeof(expression::BooleanLiteral),
        sizeof(expression::CallExpression),
        sizeof(expression::ClassExpression),
        sizeof(expression::ConditionalExpression),
        sizeof(expression::Expression),
        sizeof(expression::FunctionExpression),
        sizeof(expression::Identifier),
        sizeof(expression::Literal),
        sizeof(expression::LogicalExpression),
        sizeof(expression::MemberExpression),
        sizeof(expression::MetaProperty),
        sizeof(expression::NewExpression),
        sizeof(expression::NullLiteral),
        sizeof(expression::NumberLiteral),
        sizeof(expression::ObjectExpression),
        sizeof(expression::Property),
        sizeof(expression::RegExpLiteral),
        sizeof(expression::SequenceExpression),
        sizeof(expression::SpreadElement),
        sizeof(expression::StringLiteral),
        sizeof(expression::Super),
        sizeof(expression::TaggedTemplateExpression),
        sizeof(expression::TemplateElement),
        sizeof(expression::TemplateLiteral),
        sizeof(expression::ThisExpression),
        sizeof(expression::UnaryExpression),
        sizeof(expression::UpdateExpression),
        sizeof(expression::YieldExpression),
        sizeof(statement::ArrayPattern),
        sizeof(statement::AssignmentPattern),
        sizeof(statement::BlockStatement),
        sizeof(statement::BreakStatement),
        sizeof(statement::CatchClause),
        sizeof(statement::ContinueStatement),
        sizeof(statement::DebuggerStatement),
        sizeof(statement::DoWhileStatement),
        sizeof(statement::EmptyStatement),
        sizeof(statement::ExpressionStatement),
        sizeof(statement::ForInStatement),
        sizeof(statement::ForOfStatement),
        sizeof(statement::ForStatement),
        sizeof(statement::Function),
        sizeof(statement::IfStatement),
        sizeof(statement::LabeledStatement),
        sizeof(statement::ObjectPattern),
        sizeof(statement::Pattern),
        sizeof(statement::RestElement),
        sizeof(statement::ReturnStatement),
        sizeof(statement::Statement),
        sizeof(statement::SwitchCase),
        sizeof(statement::SwitchStatement),
        sizeof(statement::ThrowStatement),
        sizeof(statement::TryStatement),
        sizeof(statement::WhileStatement),
        sizeof(statement::WithStatement),
        sizeof(structure::Class),
        sizeof(structure::ClassBody),
        sizeof(structure::ExportSpecifier),
        sizeof(structure::ImpSpecifier),
        sizeof(structure::ImportDefaultSpecifier),
        sizeof(structure::ImportNamespaceSpecifier),
        sizeof(structure::ImportSpecifier),
        sizeof(structure::MethodDefinition),
        sizeof(structure::ModuleSpecifier),
};

  VisitorAsgStat::VisitorAsgStat() : VisitorAbstractNodes() {
    for (int i = 0; i < 86; ++i)
      nodeStatSimple[i] = 0;

    for (int i = 0; i < 86; ++i)
      nodeStatParent[i] = 0;

    for (int i = 0; i < 95; ++i)
      edgeStat[i] = 0;

  }

  VisitorAsgStat::~VisitorAsgStat() {
  }

  void VisitorAsgStat::visit(const base::Base& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkBase];
    if (node.getNodeKind() == ndkBase)
      ++nodeStatSimple[ndkBase];
  }

  void VisitorAsgStat::visit(const base::Comment& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkComment];
    if (node.getNodeKind() == ndkComment)
      ++nodeStatSimple[ndkComment];
  }

  void VisitorAsgStat::visit(const base::Named& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkNamed];
    if (node.getNodeKind() == ndkNamed)
      ++nodeStatSimple[ndkNamed];
  }

  void VisitorAsgStat::visit(const base::Positioned& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkPositioned];
    if (node.getNodeKind() == ndkPositioned)
      ++nodeStatSimple[ndkPositioned];
  }

  void VisitorAsgStat::visit(const base::Program& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkProgram];
    if (node.getNodeKind() == ndkProgram)
      ++nodeStatSimple[ndkProgram];
  }

  void VisitorAsgStat::visit(const base::System& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkSystem];
    if (node.getNodeKind() == ndkSystem)
      ++nodeStatSimple[ndkSystem];
  }

  void VisitorAsgStat::visit(const declaration::ClassDeclaration& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkClassDeclaration];
    if (node.getNodeKind() == ndkClassDeclaration)
      ++nodeStatSimple[ndkClassDeclaration];
  }

  void VisitorAsgStat::visit(const declaration::Declaration& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkDeclaration];
    if (node.getNodeKind() == ndkDeclaration)
      ++nodeStatSimple[ndkDeclaration];
  }

  void VisitorAsgStat::visit(const declaration::ExportAllDeclaration& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkExportAllDeclaration];
    if (node.getNodeKind() == ndkExportAllDeclaration)
      ++nodeStatSimple[ndkExportAllDeclaration];
  }

  void VisitorAsgStat::visit(const declaration::ExportDefaultDeclaration& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkExportDefaultDeclaration];
    if (node.getNodeKind() == ndkExportDefaultDeclaration)
      ++nodeStatSimple[ndkExportDefaultDeclaration];
  }

  void VisitorAsgStat::visit(const declaration::ExportNamedDeclaration& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkExportNamedDeclaration];
    if (node.getNodeKind() == ndkExportNamedDeclaration)
      ++nodeStatSimple[ndkExportNamedDeclaration];
  }

  void VisitorAsgStat::visit(const declaration::FunctionDeclaration& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkFunctionDeclaration];
    if (node.getNodeKind() == ndkFunctionDeclaration)
      ++nodeStatSimple[ndkFunctionDeclaration];
  }

  void VisitorAsgStat::visit(const declaration::ImportDeclaration& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkImportDeclaration];
    if (node.getNodeKind() == ndkImportDeclaration)
      ++nodeStatSimple[ndkImportDeclaration];
  }

  void VisitorAsgStat::visit(const declaration::ModuleDeclaration& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkModuleDeclaration];
    if (node.getNodeKind() == ndkModuleDeclaration)
      ++nodeStatSimple[ndkModuleDeclaration];
  }

  void VisitorAsgStat::visit(const declaration::VariableDeclaration& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkVariableDeclaration];
    if (node.getNodeKind() == ndkVariableDeclaration)
      ++nodeStatSimple[ndkVariableDeclaration];
  }

  void VisitorAsgStat::visit(const declaration::VariableDeclarator& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkVariableDeclarator];
    if (node.getNodeKind() == ndkVariableDeclarator)
      ++nodeStatSimple[ndkVariableDeclarator];
  }

  void VisitorAsgStat::visit(const expression::ArrayExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkArrayExpression];
    if (node.getNodeKind() == ndkArrayExpression)
      ++nodeStatSimple[ndkArrayExpression];
  }

  void VisitorAsgStat::visit(const expression::ArrowFunctionExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkArrowFunctionExpression];
    if (node.getNodeKind() == ndkArrowFunctionExpression)
      ++nodeStatSimple[ndkArrowFunctionExpression];
  }

  void VisitorAsgStat::visit(const expression::AssignmentExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkAssignmentExpression];
    if (node.getNodeKind() == ndkAssignmentExpression)
      ++nodeStatSimple[ndkAssignmentExpression];
  }

  void VisitorAsgStat::visit(const expression::AssignmentProperty& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkAssignmentProperty];
    if (node.getNodeKind() == ndkAssignmentProperty)
      ++nodeStatSimple[ndkAssignmentProperty];
  }

  void VisitorAsgStat::visit(const expression::AwaitExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkAwaitExpression];
    if (node.getNodeKind() == ndkAwaitExpression)
      ++nodeStatSimple[ndkAwaitExpression];
  }

  void VisitorAsgStat::visit(const expression::BinaryExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkBinaryExpression];
    if (node.getNodeKind() == ndkBinaryExpression)
      ++nodeStatSimple[ndkBinaryExpression];
  }

  void VisitorAsgStat::visit(const expression::BooleanLiteral& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkBooleanLiteral];
    if (node.getNodeKind() == ndkBooleanLiteral)
      ++nodeStatSimple[ndkBooleanLiteral];
  }

  void VisitorAsgStat::visit(const expression::CallExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkCallExpression];
    if (node.getNodeKind() == ndkCallExpression)
      ++nodeStatSimple[ndkCallExpression];
  }

  void VisitorAsgStat::visit(const expression::ClassExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkClassExpression];
    if (node.getNodeKind() == ndkClassExpression)
      ++nodeStatSimple[ndkClassExpression];
  }

  void VisitorAsgStat::visit(const expression::ConditionalExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkConditionalExpression];
    if (node.getNodeKind() == ndkConditionalExpression)
      ++nodeStatSimple[ndkConditionalExpression];
  }

  void VisitorAsgStat::visit(const expression::Expression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkExpression];
    if (node.getNodeKind() == ndkExpression)
      ++nodeStatSimple[ndkExpression];
  }

  void VisitorAsgStat::visit(const expression::FunctionExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkFunctionExpression];
    if (node.getNodeKind() == ndkFunctionExpression)
      ++nodeStatSimple[ndkFunctionExpression];
  }

  void VisitorAsgStat::visit(const expression::Identifier& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkIdentifier];
    if (node.getNodeKind() == ndkIdentifier)
      ++nodeStatSimple[ndkIdentifier];
  }

  void VisitorAsgStat::visit(const expression::Literal& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkLiteral];
    if (node.getNodeKind() == ndkLiteral)
      ++nodeStatSimple[ndkLiteral];
  }

  void VisitorAsgStat::visit(const expression::LogicalExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkLogicalExpression];
    if (node.getNodeKind() == ndkLogicalExpression)
      ++nodeStatSimple[ndkLogicalExpression];
  }

  void VisitorAsgStat::visit(const expression::MemberExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkMemberExpression];
    if (node.getNodeKind() == ndkMemberExpression)
      ++nodeStatSimple[ndkMemberExpression];
  }

  void VisitorAsgStat::visit(const expression::MetaProperty& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkMetaProperty];
    if (node.getNodeKind() == ndkMetaProperty)
      ++nodeStatSimple[ndkMetaProperty];
  }

  void VisitorAsgStat::visit(const expression::NewExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkNewExpression];
    if (node.getNodeKind() == ndkNewExpression)
      ++nodeStatSimple[ndkNewExpression];
  }

  void VisitorAsgStat::visit(const expression::NullLiteral& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkNullLiteral];
    if (node.getNodeKind() == ndkNullLiteral)
      ++nodeStatSimple[ndkNullLiteral];
  }

  void VisitorAsgStat::visit(const expression::NumberLiteral& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkNumberLiteral];
    if (node.getNodeKind() == ndkNumberLiteral)
      ++nodeStatSimple[ndkNumberLiteral];
  }

  void VisitorAsgStat::visit(const expression::ObjectExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkObjectExpression];
    if (node.getNodeKind() == ndkObjectExpression)
      ++nodeStatSimple[ndkObjectExpression];
  }

  void VisitorAsgStat::visit(const expression::Property& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkProperty];
    if (node.getNodeKind() == ndkProperty)
      ++nodeStatSimple[ndkProperty];
  }

  void VisitorAsgStat::visit(const expression::RegExpLiteral& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkRegExpLiteral];
    if (node.getNodeKind() == ndkRegExpLiteral)
      ++nodeStatSimple[ndkRegExpLiteral];
  }

  void VisitorAsgStat::visit(const expression::SequenceExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkSequenceExpression];
    if (node.getNodeKind() == ndkSequenceExpression)
      ++nodeStatSimple[ndkSequenceExpression];
  }

  void VisitorAsgStat::visit(const expression::SpreadElement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkSpreadElement];
    if (node.getNodeKind() == ndkSpreadElement)
      ++nodeStatSimple[ndkSpreadElement];
  }

  void VisitorAsgStat::visit(const expression::StringLiteral& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkStringLiteral];
    if (node.getNodeKind() == ndkStringLiteral)
      ++nodeStatSimple[ndkStringLiteral];
  }

  void VisitorAsgStat::visit(const expression::Super& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkSuper];
    if (node.getNodeKind() == ndkSuper)
      ++nodeStatSimple[ndkSuper];
  }

  void VisitorAsgStat::visit(const expression::TaggedTemplateExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkTaggedTemplateExpression];
    if (node.getNodeKind() == ndkTaggedTemplateExpression)
      ++nodeStatSimple[ndkTaggedTemplateExpression];
  }

  void VisitorAsgStat::visit(const expression::TemplateElement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkTemplateElement];
    if (node.getNodeKind() == ndkTemplateElement)
      ++nodeStatSimple[ndkTemplateElement];
  }

  void VisitorAsgStat::visit(const expression::TemplateLiteral& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkTemplateLiteral];
    if (node.getNodeKind() == ndkTemplateLiteral)
      ++nodeStatSimple[ndkTemplateLiteral];
  }

  void VisitorAsgStat::visit(const expression::ThisExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkThisExpression];
    if (node.getNodeKind() == ndkThisExpression)
      ++nodeStatSimple[ndkThisExpression];
  }

  void VisitorAsgStat::visit(const expression::UnaryExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkUnaryExpression];
    if (node.getNodeKind() == ndkUnaryExpression)
      ++nodeStatSimple[ndkUnaryExpression];
  }

  void VisitorAsgStat::visit(const expression::UpdateExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkUpdateExpression];
    if (node.getNodeKind() == ndkUpdateExpression)
      ++nodeStatSimple[ndkUpdateExpression];
  }

  void VisitorAsgStat::visit(const expression::YieldExpression& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkYieldExpression];
    if (node.getNodeKind() == ndkYieldExpression)
      ++nodeStatSimple[ndkYieldExpression];
  }

  void VisitorAsgStat::visit(const statement::ArrayPattern& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkArrayPattern];
    if (node.getNodeKind() == ndkArrayPattern)
      ++nodeStatSimple[ndkArrayPattern];
  }

  void VisitorAsgStat::visit(const statement::AssignmentPattern& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkAssignmentPattern];
    if (node.getNodeKind() == ndkAssignmentPattern)
      ++nodeStatSimple[ndkAssignmentPattern];
  }

  void VisitorAsgStat::visit(const statement::BlockStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkBlockStatement];
    if (node.getNodeKind() == ndkBlockStatement)
      ++nodeStatSimple[ndkBlockStatement];
  }

  void VisitorAsgStat::visit(const statement::BreakStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkBreakStatement];
    if (node.getNodeKind() == ndkBreakStatement)
      ++nodeStatSimple[ndkBreakStatement];
  }

  void VisitorAsgStat::visit(const statement::CatchClause& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkCatchClause];
    if (node.getNodeKind() == ndkCatchClause)
      ++nodeStatSimple[ndkCatchClause];
  }

  void VisitorAsgStat::visit(const statement::ContinueStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkContinueStatement];
    if (node.getNodeKind() == ndkContinueStatement)
      ++nodeStatSimple[ndkContinueStatement];
  }

  void VisitorAsgStat::visit(const statement::DebuggerStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkDebuggerStatement];
    if (node.getNodeKind() == ndkDebuggerStatement)
      ++nodeStatSimple[ndkDebuggerStatement];
  }

  void VisitorAsgStat::visit(const statement::DoWhileStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkDoWhileStatement];
    if (node.getNodeKind() == ndkDoWhileStatement)
      ++nodeStatSimple[ndkDoWhileStatement];
  }

  void VisitorAsgStat::visit(const statement::EmptyStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkEmptyStatement];
    if (node.getNodeKind() == ndkEmptyStatement)
      ++nodeStatSimple[ndkEmptyStatement];
  }

  void VisitorAsgStat::visit(const statement::ExpressionStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkExpressionStatement];
    if (node.getNodeKind() == ndkExpressionStatement)
      ++nodeStatSimple[ndkExpressionStatement];
  }

  void VisitorAsgStat::visit(const statement::ForInStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkForInStatement];
    if (node.getNodeKind() == ndkForInStatement)
      ++nodeStatSimple[ndkForInStatement];
  }

  void VisitorAsgStat::visit(const statement::ForOfStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkForOfStatement];
    if (node.getNodeKind() == ndkForOfStatement)
      ++nodeStatSimple[ndkForOfStatement];
  }

  void VisitorAsgStat::visit(const statement::ForStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkForStatement];
    if (node.getNodeKind() == ndkForStatement)
      ++nodeStatSimple[ndkForStatement];
  }

  void VisitorAsgStat::visit(const statement::Function& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkFunction];
    if (node.getNodeKind() == ndkFunction)
      ++nodeStatSimple[ndkFunction];
  }

  void VisitorAsgStat::visit(const statement::IfStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkIfStatement];
    if (node.getNodeKind() == ndkIfStatement)
      ++nodeStatSimple[ndkIfStatement];
  }

  void VisitorAsgStat::visit(const statement::LabeledStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkLabeledStatement];
    if (node.getNodeKind() == ndkLabeledStatement)
      ++nodeStatSimple[ndkLabeledStatement];
  }

  void VisitorAsgStat::visit(const statement::ObjectPattern& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkObjectPattern];
    if (node.getNodeKind() == ndkObjectPattern)
      ++nodeStatSimple[ndkObjectPattern];
  }

  void VisitorAsgStat::visit(const statement::Pattern& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkPattern];
    if (node.getNodeKind() == ndkPattern)
      ++nodeStatSimple[ndkPattern];
  }

  void VisitorAsgStat::visit(const statement::RestElement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkRestElement];
    if (node.getNodeKind() == ndkRestElement)
      ++nodeStatSimple[ndkRestElement];
  }

  void VisitorAsgStat::visit(const statement::ReturnStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkReturnStatement];
    if (node.getNodeKind() == ndkReturnStatement)
      ++nodeStatSimple[ndkReturnStatement];
  }

  void VisitorAsgStat::visit(const statement::Statement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkStatement];
    if (node.getNodeKind() == ndkStatement)
      ++nodeStatSimple[ndkStatement];
  }

  void VisitorAsgStat::visit(const statement::SwitchCase& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkSwitchCase];
    if (node.getNodeKind() == ndkSwitchCase)
      ++nodeStatSimple[ndkSwitchCase];
  }

  void VisitorAsgStat::visit(const statement::SwitchStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkSwitchStatement];
    if (node.getNodeKind() == ndkSwitchStatement)
      ++nodeStatSimple[ndkSwitchStatement];
  }

  void VisitorAsgStat::visit(const statement::ThrowStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkThrowStatement];
    if (node.getNodeKind() == ndkThrowStatement)
      ++nodeStatSimple[ndkThrowStatement];
  }

  void VisitorAsgStat::visit(const statement::TryStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkTryStatement];
    if (node.getNodeKind() == ndkTryStatement)
      ++nodeStatSimple[ndkTryStatement];
  }

  void VisitorAsgStat::visit(const statement::WhileStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkWhileStatement];
    if (node.getNodeKind() == ndkWhileStatement)
      ++nodeStatSimple[ndkWhileStatement];
  }

  void VisitorAsgStat::visit(const statement::WithStatement& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkWithStatement];
    if (node.getNodeKind() == ndkWithStatement)
      ++nodeStatSimple[ndkWithStatement];
  }

  void VisitorAsgStat::visit(const structure::Class& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkClass];
    if (node.getNodeKind() == ndkClass)
      ++nodeStatSimple[ndkClass];
  }

  void VisitorAsgStat::visit(const structure::ClassBody& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkClassBody];
    if (node.getNodeKind() == ndkClassBody)
      ++nodeStatSimple[ndkClassBody];
  }

  void VisitorAsgStat::visit(const structure::ExportSpecifier& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkExportSpecifier];
    if (node.getNodeKind() == ndkExportSpecifier)
      ++nodeStatSimple[ndkExportSpecifier];
  }

  void VisitorAsgStat::visit(const structure::ImpSpecifier& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkImpSpecifier];
    if (node.getNodeKind() == ndkImpSpecifier)
      ++nodeStatSimple[ndkImpSpecifier];
  }

  void VisitorAsgStat::visit(const structure::ImportDefaultSpecifier& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkImportDefaultSpecifier];
    if (node.getNodeKind() == ndkImportDefaultSpecifier)
      ++nodeStatSimple[ndkImportDefaultSpecifier];
  }

  void VisitorAsgStat::visit(const structure::ImportNamespaceSpecifier& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkImportNamespaceSpecifier];
    if (node.getNodeKind() == ndkImportNamespaceSpecifier)
      ++nodeStatSimple[ndkImportNamespaceSpecifier];
  }

  void VisitorAsgStat::visit(const structure::ImportSpecifier& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkImportSpecifier];
    if (node.getNodeKind() == ndkImportSpecifier)
      ++nodeStatSimple[ndkImportSpecifier];
  }

  void VisitorAsgStat::visit(const structure::MethodDefinition& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkMethodDefinition];
    if (node.getNodeKind() == ndkMethodDefinition)
      ++nodeStatSimple[ndkMethodDefinition];
  }

  void VisitorAsgStat::visit(const structure::ModuleSpecifier& node,bool callVirtualBase ) {
    VisitorAbstractNodes::visit(node,callVirtualBase);

    ++nodeStatParent[ndkModuleSpecifier];
    if (node.getNodeKind() == ndkModuleSpecifier)
      ++nodeStatSimple[ndkModuleSpecifier];
  }

  void VisitorAsgStat::visitPositioned_Comments(const base::Positioned& begin, const base::Comment& end) {
    ++edgeStat[edkPositioned_Comments];
  }

  void VisitorAsgStat::visitProgram_HasBody(const base::Program& begin, const base::Positioned& end) {
    ++edgeStat[edkProgram_HasBody];
  }

  void VisitorAsgStat::visitSystem_HasPrograms(const base::System& begin, const base::Program& end) {
    ++edgeStat[edkSystem_HasPrograms];
  }

  void VisitorAsgStat::visitExportAllDeclaration_HasSource(const declaration::ExportAllDeclaration& begin, const expression::Literal& end) {
    ++edgeStat[edkExportAllDeclaration_HasSource];
  }

  void VisitorAsgStat::visitExportDefaultDeclaration_HasDeclaration(const declaration::ExportDefaultDeclaration& begin, const base::Positioned& end) {
    ++edgeStat[edkExportDefaultDeclaration_HasDeclaration];
  }

  void VisitorAsgStat::visitExportNamedDeclaration_HasDeclaration(const declaration::ExportNamedDeclaration& begin, const declaration::Declaration& end) {
    ++edgeStat[edkExportNamedDeclaration_HasDeclaration];
  }

  void VisitorAsgStat::visitExportNamedDeclaration_HasSpecifiers(const declaration::ExportNamedDeclaration& begin, const structure::ExportSpecifier& end) {
    ++edgeStat[edkExportNamedDeclaration_HasSpecifiers];
  }

  void VisitorAsgStat::visitExportNamedDeclaration_HasSource(const declaration::ExportNamedDeclaration& begin, const expression::Literal& end) {
    ++edgeStat[edkExportNamedDeclaration_HasSource];
  }

  void VisitorAsgStat::visitImportDeclaration_HasSpecifiers(const declaration::ImportDeclaration& begin, const structure::ImpSpecifier& end) {
    ++edgeStat[edkImportDeclaration_HasSpecifiers];
  }

  void VisitorAsgStat::visitImportDeclaration_HasSource(const declaration::ImportDeclaration& begin, const expression::Literal& end) {
    ++edgeStat[edkImportDeclaration_HasSource];
  }

  void VisitorAsgStat::visitVariableDeclaration_HasDeclarations(const declaration::VariableDeclaration& begin, const declaration::VariableDeclarator& end) {
    ++edgeStat[edkVariableDeclaration_HasDeclarations];
  }

  void VisitorAsgStat::visitVariableDeclarator_HasIdentifier(const declaration::VariableDeclarator& begin, const statement::Pattern& end) {
    ++edgeStat[edkVariableDeclarator_HasIdentifier];
  }

  void VisitorAsgStat::visitVariableDeclarator_HasInit(const declaration::VariableDeclarator& begin, const expression::Expression& end) {
    ++edgeStat[edkVariableDeclarator_HasInit];
  }

  void VisitorAsgStat::visitArrayExpression_HasElements(const expression::ArrayExpression& begin, const base::Positioned& end) {
    ++edgeStat[edkArrayExpression_HasElements];
  }

  void VisitorAsgStat::visitAssignmentExpression_HasLeft(const expression::AssignmentExpression& begin, const base::Positioned& end) {
    ++edgeStat[edkAssignmentExpression_HasLeft];
  }

  void VisitorAsgStat::visitAssignmentExpression_HasRight(const expression::AssignmentExpression& begin, const expression::Expression& end) {
    ++edgeStat[edkAssignmentExpression_HasRight];
  }

  void VisitorAsgStat::visitAwaitExpression_HasArgument(const expression::AwaitExpression& begin, const expression::Expression& end) {
    ++edgeStat[edkAwaitExpression_HasArgument];
  }

  void VisitorAsgStat::visitBinaryExpression_HasLeft(const expression::BinaryExpression& begin, const expression::Expression& end) {
    ++edgeStat[edkBinaryExpression_HasLeft];
  }

  void VisitorAsgStat::visitBinaryExpression_HasRight(const expression::BinaryExpression& begin, const expression::Expression& end) {
    ++edgeStat[edkBinaryExpression_HasRight];
  }

  void VisitorAsgStat::visitCallExpression_HasCallee(const expression::CallExpression& begin, const base::Positioned& end) {
    ++edgeStat[edkCallExpression_HasCallee];
  }

  void VisitorAsgStat::visitCallExpression_HasArguments(const expression::CallExpression& begin, const base::Positioned& end) {
    ++edgeStat[edkCallExpression_HasArguments];
  }

  void VisitorAsgStat::visitCallExpression_Calls(const expression::CallExpression& begin, const statement::Function& end) {
    ++edgeStat[edkCallExpression_Calls];
  }

  void VisitorAsgStat::visitConditionalExpression_HasAlternate(const expression::ConditionalExpression& begin, const expression::Expression& end) {
    ++edgeStat[edkConditionalExpression_HasAlternate];
  }

  void VisitorAsgStat::visitConditionalExpression_HasConsequent(const expression::ConditionalExpression& begin, const expression::Expression& end) {
    ++edgeStat[edkConditionalExpression_HasConsequent];
  }

  void VisitorAsgStat::visitConditionalExpression_HasTest(const expression::ConditionalExpression& begin, const expression::Expression& end) {
    ++edgeStat[edkConditionalExpression_HasTest];
  }

  void VisitorAsgStat::visitIdentifier_RefersTo(const expression::Identifier& begin, const base::Positioned& end) {
    ++edgeStat[edkIdentifier_RefersTo];
  }

  void VisitorAsgStat::visitLogicalExpression_HasLeft(const expression::LogicalExpression& begin, const expression::Expression& end) {
    ++edgeStat[edkLogicalExpression_HasLeft];
  }

  void VisitorAsgStat::visitLogicalExpression_HasRight(const expression::LogicalExpression& begin, const expression::Expression& end) {
    ++edgeStat[edkLogicalExpression_HasRight];
  }

  void VisitorAsgStat::visitMemberExpression_HasProperty(const expression::MemberExpression& begin, const expression::Expression& end) {
    ++edgeStat[edkMemberExpression_HasProperty];
  }

  void VisitorAsgStat::visitMemberExpression_HasObject(const expression::MemberExpression& begin, const base::Positioned& end) {
    ++edgeStat[edkMemberExpression_HasObject];
  }

  void VisitorAsgStat::visitMetaProperty_HasMeta(const expression::MetaProperty& begin, const expression::Identifier& end) {
    ++edgeStat[edkMetaProperty_HasMeta];
  }

  void VisitorAsgStat::visitMetaProperty_HasProperty(const expression::MetaProperty& begin, const expression::Identifier& end) {
    ++edgeStat[edkMetaProperty_HasProperty];
  }

  void VisitorAsgStat::visitNewExpression_HasCallee(const expression::NewExpression& begin, const expression::Expression& end) {
    ++edgeStat[edkNewExpression_HasCallee];
  }

  void VisitorAsgStat::visitNewExpression_HasArguments(const expression::NewExpression& begin, const base::Positioned& end) {
    ++edgeStat[edkNewExpression_HasArguments];
  }

  void VisitorAsgStat::visitNewExpression_Calls(const expression::NewExpression& begin, const statement::Function& end) {
    ++edgeStat[edkNewExpression_Calls];
  }

  void VisitorAsgStat::visitObjectExpression_HasProperties(const expression::ObjectExpression& begin, const base::Positioned& end) {
    ++edgeStat[edkObjectExpression_HasProperties];
  }

  void VisitorAsgStat::visitProperty_HasValue(const expression::Property& begin, const base::Positioned& end) {
    ++edgeStat[edkProperty_HasValue];
  }

  void VisitorAsgStat::visitProperty_HasKey(const expression::Property& begin, const expression::Expression& end) {
    ++edgeStat[edkProperty_HasKey];
  }

  void VisitorAsgStat::visitSequenceExpression_HasExpressions(const expression::SequenceExpression& begin, const expression::Expression& end) {
    ++edgeStat[edkSequenceExpression_HasExpressions];
  }

  void VisitorAsgStat::visitSpreadElement_HasArgument(const expression::SpreadElement& begin, const expression::Expression& end) {
    ++edgeStat[edkSpreadElement_HasArgument];
  }

  void VisitorAsgStat::visitTaggedTemplateExpression_HasTag(const expression::TaggedTemplateExpression& begin, const expression::Expression& end) {
    ++edgeStat[edkTaggedTemplateExpression_HasTag];
  }

  void VisitorAsgStat::visitTaggedTemplateExpression_HasQuasi(const expression::TaggedTemplateExpression& begin, const expression::TemplateLiteral& end) {
    ++edgeStat[edkTaggedTemplateExpression_HasQuasi];
  }

  void VisitorAsgStat::visitTemplateLiteral_HasQuasis(const expression::TemplateLiteral& begin, const expression::TemplateElement& end) {
    ++edgeStat[edkTemplateLiteral_HasQuasis];
  }

  void VisitorAsgStat::visitTemplateLiteral_HasExpressions(const expression::TemplateLiteral& begin, const expression::Expression& end) {
    ++edgeStat[edkTemplateLiteral_HasExpressions];
  }

  void VisitorAsgStat::visitUnaryExpression_HasArgument(const expression::UnaryExpression& begin, const expression::Expression& end) {
    ++edgeStat[edkUnaryExpression_HasArgument];
  }

  void VisitorAsgStat::visitUpdateExpression_HasArgument(const expression::UpdateExpression& begin, const expression::Expression& end) {
    ++edgeStat[edkUpdateExpression_HasArgument];
  }

  void VisitorAsgStat::visitYieldExpression_HasArgument(const expression::YieldExpression& begin, const expression::Expression& end) {
    ++edgeStat[edkYieldExpression_HasArgument];
  }

  void VisitorAsgStat::visitArrayPattern_HasElements(const statement::ArrayPattern& begin, const statement::Pattern& end) {
    ++edgeStat[edkArrayPattern_HasElements];
  }

  void VisitorAsgStat::visitAssignmentPattern_HasLeft(const statement::AssignmentPattern& begin, const statement::Pattern& end) {
    ++edgeStat[edkAssignmentPattern_HasLeft];
  }

  void VisitorAsgStat::visitAssignmentPattern_HasRight(const statement::AssignmentPattern& begin, const expression::Expression& end) {
    ++edgeStat[edkAssignmentPattern_HasRight];
  }

  void VisitorAsgStat::visitBlockStatement_HasBody(const statement::BlockStatement& begin, const statement::Statement& end) {
    ++edgeStat[edkBlockStatement_HasBody];
  }

  void VisitorAsgStat::visitBreakStatement_HasLabel(const statement::BreakStatement& begin, const expression::Identifier& end) {
    ++edgeStat[edkBreakStatement_HasLabel];
  }

  void VisitorAsgStat::visitCatchClause_HasParam(const statement::CatchClause& begin, const statement::Pattern& end) {
    ++edgeStat[edkCatchClause_HasParam];
  }

  void VisitorAsgStat::visitCatchClause_HasBody(const statement::CatchClause& begin, const statement::BlockStatement& end) {
    ++edgeStat[edkCatchClause_HasBody];
  }

  void VisitorAsgStat::visitContinueStatement_HasLabel(const statement::ContinueStatement& begin, const expression::Identifier& end) {
    ++edgeStat[edkContinueStatement_HasLabel];
  }

  void VisitorAsgStat::visitExpressionStatement_HasExpression(const statement::ExpressionStatement& begin, const expression::Expression& end) {
    ++edgeStat[edkExpressionStatement_HasExpression];
  }

  void VisitorAsgStat::visitForInStatement_HasRight(const statement::ForInStatement& begin, const expression::Expression& end) {
    ++edgeStat[edkForInStatement_HasRight];
  }

  void VisitorAsgStat::visitForInStatement_HasBody(const statement::ForInStatement& begin, const statement::Statement& end) {
    ++edgeStat[edkForInStatement_HasBody];
  }

  void VisitorAsgStat::visitForInStatement_HasLeft(const statement::ForInStatement& begin, const base::Positioned& end) {
    ++edgeStat[edkForInStatement_HasLeft];
  }

  void VisitorAsgStat::visitForStatement_HasBody(const statement::ForStatement& begin, const statement::Statement& end) {
    ++edgeStat[edkForStatement_HasBody];
  }

  void VisitorAsgStat::visitForStatement_HasTest(const statement::ForStatement& begin, const expression::Expression& end) {
    ++edgeStat[edkForStatement_HasTest];
  }

  void VisitorAsgStat::visitForStatement_HasUpdate(const statement::ForStatement& begin, const expression::Expression& end) {
    ++edgeStat[edkForStatement_HasUpdate];
  }

  void VisitorAsgStat::visitForStatement_HasInit(const statement::ForStatement& begin, const base::Positioned& end) {
    ++edgeStat[edkForStatement_HasInit];
  }

  void VisitorAsgStat::visitFunction_HasParams(const statement::Function& begin, const statement::Pattern& end) {
    ++edgeStat[edkFunction_HasParams];
  }

  void VisitorAsgStat::visitFunction_HasBody(const statement::Function& begin, const base::Positioned& end) {
    ++edgeStat[edkFunction_HasBody];
  }

  void VisitorAsgStat::visitFunction_HasIdentifier(const statement::Function& begin, const expression::Identifier& end) {
    ++edgeStat[edkFunction_HasIdentifier];
  }

  void VisitorAsgStat::visitIfStatement_HasTest(const statement::IfStatement& begin, const expression::Expression& end) {
    ++edgeStat[edkIfStatement_HasTest];
  }

  void VisitorAsgStat::visitIfStatement_HasConsequent(const statement::IfStatement& begin, const statement::Statement& end) {
    ++edgeStat[edkIfStatement_HasConsequent];
  }

  void VisitorAsgStat::visitIfStatement_HasAlternate(const statement::IfStatement& begin, const statement::Statement& end) {
    ++edgeStat[edkIfStatement_HasAlternate];
  }

  void VisitorAsgStat::visitLabeledStatement_HasLabel(const statement::LabeledStatement& begin, const expression::Identifier& end) {
    ++edgeStat[edkLabeledStatement_HasLabel];
  }

  void VisitorAsgStat::visitLabeledStatement_HasBody(const statement::LabeledStatement& begin, const statement::Statement& end) {
    ++edgeStat[edkLabeledStatement_HasBody];
  }

  void VisitorAsgStat::visitObjectPattern_HasProperties(const statement::ObjectPattern& begin, const base::Positioned& end) {
    ++edgeStat[edkObjectPattern_HasProperties];
  }

  void VisitorAsgStat::visitRestElement_HasArgument(const statement::RestElement& begin, const statement::Pattern& end) {
    ++edgeStat[edkRestElement_HasArgument];
  }

  void VisitorAsgStat::visitReturnStatement_HasArgument(const statement::ReturnStatement& begin, const expression::Expression& end) {
    ++edgeStat[edkReturnStatement_HasArgument];
  }

  void VisitorAsgStat::visitSwitchCase_HasTest(const statement::SwitchCase& begin, const expression::Expression& end) {
    ++edgeStat[edkSwitchCase_HasTest];
  }

  void VisitorAsgStat::visitSwitchCase_HasConsequent(const statement::SwitchCase& begin, const statement::Statement& end) {
    ++edgeStat[edkSwitchCase_HasConsequent];
  }

  void VisitorAsgStat::visitSwitchStatement_HasDiscriminant(const statement::SwitchStatement& begin, const expression::Expression& end) {
    ++edgeStat[edkSwitchStatement_HasDiscriminant];
  }

  void VisitorAsgStat::visitSwitchStatement_HasCases(const statement::SwitchStatement& begin, const statement::SwitchCase& end) {
    ++edgeStat[edkSwitchStatement_HasCases];
  }

  void VisitorAsgStat::visitThrowStatement_HasArgument(const statement::ThrowStatement& begin, const expression::Expression& end) {
    ++edgeStat[edkThrowStatement_HasArgument];
  }

  void VisitorAsgStat::visitTryStatement_HasBlock(const statement::TryStatement& begin, const statement::BlockStatement& end) {
    ++edgeStat[edkTryStatement_HasBlock];
  }

  void VisitorAsgStat::visitTryStatement_HasFinalizer(const statement::TryStatement& begin, const statement::BlockStatement& end) {
    ++edgeStat[edkTryStatement_HasFinalizer];
  }

  void VisitorAsgStat::visitTryStatement_HasHandler(const statement::TryStatement& begin, const statement::CatchClause& end) {
    ++edgeStat[edkTryStatement_HasHandler];
  }

  void VisitorAsgStat::visitWhileStatement_HasBody(const statement::WhileStatement& begin, const statement::Statement& end) {
    ++edgeStat[edkWhileStatement_HasBody];
  }

  void VisitorAsgStat::visitWhileStatement_HasTest(const statement::WhileStatement& begin, const expression::Expression& end) {
    ++edgeStat[edkWhileStatement_HasTest];
  }

  void VisitorAsgStat::visitWithStatement_HasObject(const statement::WithStatement& begin, const expression::Expression& end) {
    ++edgeStat[edkWithStatement_HasObject];
  }

  void VisitorAsgStat::visitWithStatement_HasBody(const statement::WithStatement& begin, const statement::Statement& end) {
    ++edgeStat[edkWithStatement_HasBody];
  }

  void VisitorAsgStat::visitClass_HasBody(const structure::Class& begin, const structure::ClassBody& end) {
    ++edgeStat[edkClass_HasBody];
  }

  void VisitorAsgStat::visitClass_HasSuperClass(const structure::Class& begin, const expression::Expression& end) {
    ++edgeStat[edkClass_HasSuperClass];
  }

  void VisitorAsgStat::visitClass_HasIdentifier(const structure::Class& begin, const expression::Identifier& end) {
    ++edgeStat[edkClass_HasIdentifier];
  }

  void VisitorAsgStat::visitClassBody_HasBody(const structure::ClassBody& begin, const structure::MethodDefinition& end) {
    ++edgeStat[edkClassBody_HasBody];
  }

  void VisitorAsgStat::visitExportSpecifier_HasExported(const structure::ExportSpecifier& begin, const expression::Identifier& end) {
    ++edgeStat[edkExportSpecifier_HasExported];
  }

  void VisitorAsgStat::visitImportSpecifier_HasImported(const structure::ImportSpecifier& begin, const expression::Identifier& end) {
    ++edgeStat[edkImportSpecifier_HasImported];
  }

  void VisitorAsgStat::visitMethodDefinition_HasKey(const structure::MethodDefinition& begin, const expression::Expression& end) {
    ++edgeStat[edkMethodDefinition_HasKey];
  }

  void VisitorAsgStat::visitMethodDefinition_HasValue(const structure::MethodDefinition& begin, const expression::FunctionExpression& end) {
    ++edgeStat[edkMethodDefinition_HasValue];
  }

  void VisitorAsgStat::visitModuleSpecifier_HasLocal(const structure::ModuleSpecifier& begin, const expression::Identifier& end) {
    ++edgeStat[edkModuleSpecifier_HasLocal];
  }


}}}
