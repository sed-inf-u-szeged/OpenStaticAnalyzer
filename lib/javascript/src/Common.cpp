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
#include "javascript/inc/messages.h"
#include <sstream>

namespace columbus { namespace javascript { namespace asg {
namespace Common {

bool getIsComment(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkComment;
}

bool getIsNamed(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNamed ||
    ndk == ndkProgram ||
    ndk == ndkIdentifier ||
    ndk == ndkPrivateIdentifier;
}

bool getIsPositioned(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPositioned ||
    ndk == ndkComment ||
    ndk == ndkProgram ||
    ndk == ndkIdentifier ||
    ndk == ndkPrivateIdentifier ||
    ndk == ndkModuleDeclaration ||
    ndk == ndkExportNamedDeclaration ||
    ndk == ndkImportDeclaration ||
    ndk == ndkVariableDeclarator ||
    ndk == ndkChainElement ||
    ndk == ndkCallExpression ||
    ndk == ndkMemberExpression ||
    ndk == ndkArrayExpression ||
    ndk == ndkArrowFunctionExpression ||
    ndk == ndkAssignmentExpression ||
    ndk == ndkAwaitExpression ||
    ndk == ndkBinaryExpression ||
    ndk == ndkChainExpression ||
    ndk == ndkClassExpression ||
    ndk == ndkConditionalExpression ||
    ndk == ndkFunctionExpression ||
    ndk == ndkImportExpression ||
    ndk == ndkBigIntLiteral ||
    ndk == ndkBooleanLiteral ||
    ndk == ndkNullLiteral ||
    ndk == ndkNumberLiteral ||
    ndk == ndkRegExpLiteral ||
    ndk == ndkStringLiteral ||
    ndk == ndkLogicalExpression ||
    ndk == ndkMetaProperty ||
    ndk == ndkNewExpression ||
    ndk == ndkObjectExpression ||
    ndk == ndkSequenceExpression ||
    ndk == ndkTaggedTemplateExpression ||
    ndk == ndkTemplateLiteral ||
    ndk == ndkThisExpression ||
    ndk == ndkUnaryExpression ||
    ndk == ndkUpdateExpression ||
    ndk == ndkYieldExpression ||
    ndk == ndkProperty ||
    ndk == ndkSpreadElement ||
    ndk == ndkSuper ||
    ndk == ndkTemplateElement ||
    ndk == ndkCatchClause ||
    ndk == ndkFunction ||
    ndk == ndkFunctionDeclaration ||
    ndk == ndkArrayPattern ||
    ndk == ndkAssignmentPattern ||
    ndk == ndkObjectPattern ||
    ndk == ndkRestElement ||
    ndk == ndkClassDeclaration ||
    ndk == ndkExportAllDeclaration ||
    ndk == ndkExportDefaultDeclaration ||
    ndk == ndkVariableDeclaration ||
    ndk == ndkBlockStatement ||
    ndk == ndkBreakStatement ||
    ndk == ndkContinueStatement ||
    ndk == ndkDebuggerStatement ||
    ndk == ndkEmptyStatement ||
    ndk == ndkExpressionStatement ||
    ndk == ndkForInStatement ||
    ndk == ndkForOfStatement ||
    ndk == ndkForStatement ||
    ndk == ndkIfStatement ||
    ndk == ndkLabeledStatement ||
    ndk == ndkReturnStatement ||
    ndk == ndkSwitchStatement ||
    ndk == ndkThrowStatement ||
    ndk == ndkTryStatement ||
    ndk == ndkWhileStatement ||
    ndk == ndkDoWhileStatement ||
    ndk == ndkWithStatement ||
    ndk == ndkSwitchCase ||
    ndk == ndkClassBody ||
    ndk == ndkMethodDefinition ||
    ndk == ndkExportSpecifier ||
    ndk == ndkImportDefaultSpecifier ||
    ndk == ndkImportNamespaceSpecifier ||
    ndk == ndkImportSpecifier ||
    ndk == ndkPropertyDefinition;
}

bool getIsProgram(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkProgram;
}

bool getIsSystem(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSystem;
}

bool getIsClassDeclaration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkClassDeclaration;
}

bool getIsDeclaration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkDeclaration ||
    ndk == ndkClassDeclaration ||
    ndk == ndkExportAllDeclaration ||
    ndk == ndkExportDefaultDeclaration ||
    ndk == ndkFunctionDeclaration ||
    ndk == ndkVariableDeclaration;
}

bool getIsExportAllDeclaration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkExportAllDeclaration;
}

bool getIsExportDefaultDeclaration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkExportDefaultDeclaration;
}

bool getIsExportNamedDeclaration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkExportNamedDeclaration;
}

bool getIsFunctionDeclaration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFunctionDeclaration;
}

bool getIsImportDeclaration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkImportDeclaration;
}

bool getIsModuleDeclaration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkModuleDeclaration ||
    ndk == ndkExportNamedDeclaration ||
    ndk == ndkImportDeclaration;
}

bool getIsVariableDeclaration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkVariableDeclaration;
}

bool getIsVariableDeclarator(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkVariableDeclarator;
}

bool getIsArrayExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkArrayExpression;
}

bool getIsArrowFunctionExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkArrowFunctionExpression;
}

bool getIsAssignmentExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAssignmentExpression;
}

bool getIsAwaitExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAwaitExpression;
}

bool getIsBigIntLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBigIntLiteral;
}

bool getIsBinaryExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBinaryExpression;
}

bool getIsBooleanLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBooleanLiteral;
}

bool getIsCallExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCallExpression;
}

bool getIsChainElement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkChainElement ||
    ndk == ndkCallExpression ||
    ndk == ndkMemberExpression;
}

bool getIsChainExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkChainExpression;
}

bool getIsClassExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkClassExpression;
}

bool getIsConditionalExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkConditionalExpression;
}

bool getIsExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkExpression ||
    ndk == ndkArrayExpression ||
    ndk == ndkArrowFunctionExpression ||
    ndk == ndkAssignmentExpression ||
    ndk == ndkAwaitExpression ||
    ndk == ndkBinaryExpression ||
    ndk == ndkCallExpression ||
    ndk == ndkChainExpression ||
    ndk == ndkClassExpression ||
    ndk == ndkConditionalExpression ||
    ndk == ndkFunctionExpression ||
    ndk == ndkIdentifier ||
    ndk == ndkImportExpression ||
    ndk == ndkBigIntLiteral ||
    ndk == ndkBooleanLiteral ||
    ndk == ndkNullLiteral ||
    ndk == ndkNumberLiteral ||
    ndk == ndkRegExpLiteral ||
    ndk == ndkStringLiteral ||
    ndk == ndkLogicalExpression ||
    ndk == ndkMemberExpression ||
    ndk == ndkMetaProperty ||
    ndk == ndkNewExpression ||
    ndk == ndkObjectExpression ||
    ndk == ndkSequenceExpression ||
    ndk == ndkTaggedTemplateExpression ||
    ndk == ndkTemplateLiteral ||
    ndk == ndkThisExpression ||
    ndk == ndkUnaryExpression ||
    ndk == ndkUpdateExpression ||
    ndk == ndkYieldExpression;
}

bool getIsFunctionExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFunctionExpression;
}

bool getIsIdentifier(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIdentifier;
}

bool getIsImportExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkImportExpression;
}

bool getIsLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkLiteral ||
    ndk == ndkBigIntLiteral ||
    ndk == ndkBooleanLiteral ||
    ndk == ndkNullLiteral ||
    ndk == ndkNumberLiteral ||
    ndk == ndkRegExpLiteral ||
    ndk == ndkStringLiteral;
}

bool getIsLogicalExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkLogicalExpression;
}

bool getIsMemberExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMemberExpression;
}

bool getIsMetaProperty(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMetaProperty;
}

bool getIsNewExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNewExpression;
}

bool getIsNullLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNullLiteral;
}

bool getIsNumberLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNumberLiteral;
}

bool getIsObjectExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkObjectExpression;
}

bool getIsPrivateIdentifier(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPrivateIdentifier;
}

bool getIsProperty(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkProperty;
}

bool getIsRegExpLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkRegExpLiteral;
}

bool getIsSequenceExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSequenceExpression;
}

bool getIsSpreadElement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSpreadElement;
}

bool getIsStringLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkStringLiteral;
}

bool getIsSuper(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSuper;
}

bool getIsTaggedTemplateExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTaggedTemplateExpression;
}

bool getIsTemplateElement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTemplateElement;
}

bool getIsTemplateLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTemplateLiteral;
}

bool getIsThisExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkThisExpression;
}

bool getIsUnaryExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkUnaryExpression;
}

bool getIsUpdateExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkUpdateExpression;
}

bool getIsYieldExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkYieldExpression;
}

bool getIsArrayPattern(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkArrayPattern;
}

bool getIsAssignmentPattern(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAssignmentPattern;
}

bool getIsBlockStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBlockStatement;
}

bool getIsBreakStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBreakStatement;
}

bool getIsCatchClause(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCatchClause;
}

bool getIsContinueStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkContinueStatement;
}

bool getIsDebuggerStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkDebuggerStatement;
}

bool getIsDoWhileStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkDoWhileStatement;
}

bool getIsEmptyStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkEmptyStatement;
}

bool getIsExpressionStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkExpressionStatement;
}

bool getIsForInStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkForInStatement ||
    ndk == ndkForOfStatement;
}

bool getIsForOfStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkForOfStatement;
}

bool getIsForStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkForStatement;
}

bool getIsFunction(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFunction ||
    ndk == ndkFunctionDeclaration ||
    ndk == ndkArrowFunctionExpression ||
    ndk == ndkFunctionExpression;
}

bool getIsIfStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIfStatement;
}

bool getIsLabeledStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkLabeledStatement;
}

bool getIsObjectPattern(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkObjectPattern;
}

bool getIsPattern(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPattern ||
    ndk == ndkIdentifier ||
    ndk == ndkMemberExpression ||
    ndk == ndkArrayPattern ||
    ndk == ndkAssignmentPattern ||
    ndk == ndkObjectPattern ||
    ndk == ndkRestElement;
}

bool getIsRestElement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkRestElement;
}

bool getIsReturnStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkReturnStatement;
}

bool getIsStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkStatement ||
    ndk == ndkClassDeclaration ||
    ndk == ndkExportAllDeclaration ||
    ndk == ndkExportDefaultDeclaration ||
    ndk == ndkFunctionDeclaration ||
    ndk == ndkVariableDeclaration ||
    ndk == ndkBlockStatement ||
    ndk == ndkBreakStatement ||
    ndk == ndkContinueStatement ||
    ndk == ndkDebuggerStatement ||
    ndk == ndkEmptyStatement ||
    ndk == ndkExpressionStatement ||
    ndk == ndkForInStatement ||
    ndk == ndkForOfStatement ||
    ndk == ndkForStatement ||
    ndk == ndkIfStatement ||
    ndk == ndkLabeledStatement ||
    ndk == ndkReturnStatement ||
    ndk == ndkSwitchStatement ||
    ndk == ndkThrowStatement ||
    ndk == ndkTryStatement ||
    ndk == ndkWhileStatement ||
    ndk == ndkDoWhileStatement ||
    ndk == ndkWithStatement;
}

bool getIsSwitchCase(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSwitchCase;
}

bool getIsSwitchStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSwitchStatement;
}

bool getIsThrowStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkThrowStatement;
}

bool getIsTryStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTryStatement;
}

bool getIsWhileStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkWhileStatement ||
    ndk == ndkDoWhileStatement;
}

bool getIsWithStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkWithStatement;
}

bool getIsClass(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkClass ||
    ndk == ndkClassDeclaration ||
    ndk == ndkClassExpression;
}

bool getIsClassBody(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkClassBody;
}

bool getIsExportSpecifier(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkExportSpecifier;
}

bool getIsImpSpecifier(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkImpSpecifier ||
    ndk == ndkImportDefaultSpecifier ||
    ndk == ndkImportNamespaceSpecifier ||
    ndk == ndkImportSpecifier;
}

bool getIsImportDefaultSpecifier(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkImportDefaultSpecifier;
}

bool getIsImportNamespaceSpecifier(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkImportNamespaceSpecifier;
}

bool getIsImportSpecifier(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkImportSpecifier;
}

bool getIsMethodDefinition(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMethodDefinition;
}

bool getIsModuleSpecifier(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkModuleSpecifier ||
    ndk == ndkExportSpecifier ||
    ndk == ndkImportDefaultSpecifier ||
    ndk == ndkImportNamespaceSpecifier ||
    ndk == ndkImportSpecifier;
}

bool getIsPropertyDefinition(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPropertyDefinition;
}

bool getIsComposite(const base::Base& node) {
  return !getIsNotComposite(node);
}

bool getIsNotComposite(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkComment ||
    ndk == ndkIdentifier ||
    ndk == ndkPrivateIdentifier ||
    ndk == ndkModuleDeclaration ||
    ndk == ndkChainElement ||
    ndk == ndkBigIntLiteral ||
    ndk == ndkBooleanLiteral ||
    ndk == ndkNullLiteral ||
    ndk == ndkNumberLiteral ||
    ndk == ndkRegExpLiteral ||
    ndk == ndkStringLiteral ||
    ndk == ndkThisExpression ||
    ndk == ndkSuper ||
    ndk == ndkTemplateElement ||
    ndk == ndkDebuggerStatement ||
    ndk == ndkEmptyStatement;
}

const std::string toString(NodeId id) {
  std::stringstream s;
  s << id;
  return s.str();
}

bool getIsBaseClassKind(NodeKind what, NodeKind base) {
  NodeKind type = what;
  if (type == base)
    return true;
  switch (type) {
      case ndkBase:
        return false;
      case ndkComment:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkNamed:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkPositioned:
        return getIsBaseClassKind(ndkBase, base);
      case ndkProgram:
        return getIsBaseClassKind(ndkNamed, base);
      case ndkSystem:
        return getIsBaseClassKind(ndkBase, base);
      case ndkClassDeclaration:
        return getIsBaseClassKind(ndkDeclaration, base) ||
          getIsBaseClassKind(ndkClass, base);
      case ndkDeclaration:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkExportAllDeclaration:
        return getIsBaseClassKind(ndkDeclaration, base);
      case ndkExportDefaultDeclaration:
        return getIsBaseClassKind(ndkDeclaration, base);
      case ndkExportNamedDeclaration:
        return getIsBaseClassKind(ndkModuleDeclaration, base);
      case ndkFunctionDeclaration:
        return getIsBaseClassKind(ndkFunction, base) ||
          getIsBaseClassKind(ndkDeclaration, base);
      case ndkImportDeclaration:
        return getIsBaseClassKind(ndkModuleDeclaration, base);
      case ndkModuleDeclaration:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkVariableDeclaration:
        return getIsBaseClassKind(ndkDeclaration, base);
      case ndkVariableDeclarator:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkArrayExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkArrowFunctionExpression:
        return getIsBaseClassKind(ndkExpression, base) ||
          getIsBaseClassKind(ndkFunction, base);
      case ndkAssignmentExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkAwaitExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkBigIntLiteral:
        return getIsBaseClassKind(ndkLiteral, base);
      case ndkBinaryExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkBooleanLiteral:
        return getIsBaseClassKind(ndkLiteral, base);
      case ndkCallExpression:
        return getIsBaseClassKind(ndkExpression, base) ||
          getIsBaseClassKind(ndkChainElement, base);
      case ndkChainElement:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkChainExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkClassExpression:
        return getIsBaseClassKind(ndkExpression, base) ||
          getIsBaseClassKind(ndkClass, base);
      case ndkConditionalExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkExpression:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkFunctionExpression:
        return getIsBaseClassKind(ndkExpression, base) ||
          getIsBaseClassKind(ndkFunction, base);
      case ndkIdentifier:
        return getIsBaseClassKind(ndkExpression, base) ||
          getIsBaseClassKind(ndkPattern, base) ||
          getIsBaseClassKind(ndkNamed, base);
      case ndkImportExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkLiteral:
        return getIsBaseClassKind(ndkPositioned, base) ||
          getIsBaseClassKind(ndkExpression, base);
      case ndkLogicalExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkMemberExpression:
        return getIsBaseClassKind(ndkExpression, base) ||
          getIsBaseClassKind(ndkPattern, base) ||
          getIsBaseClassKind(ndkChainElement, base);
      case ndkMetaProperty:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkNewExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkNullLiteral:
        return getIsBaseClassKind(ndkLiteral, base);
      case ndkNumberLiteral:
        return getIsBaseClassKind(ndkLiteral, base);
      case ndkObjectExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkPrivateIdentifier:
        return getIsBaseClassKind(ndkPositioned, base) ||
          getIsBaseClassKind(ndkNamed, base);
      case ndkProperty:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkRegExpLiteral:
        return getIsBaseClassKind(ndkLiteral, base);
      case ndkSequenceExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkSpreadElement:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkStringLiteral:
        return getIsBaseClassKind(ndkLiteral, base);
      case ndkSuper:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkTaggedTemplateExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkTemplateElement:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkTemplateLiteral:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkThisExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkUnaryExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkUpdateExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkYieldExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkArrayPattern:
        return getIsBaseClassKind(ndkPattern, base);
      case ndkAssignmentPattern:
        return getIsBaseClassKind(ndkPattern, base);
      case ndkBlockStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkBreakStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkCatchClause:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkContinueStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkDebuggerStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkDoWhileStatement:
        return getIsBaseClassKind(ndkWhileStatement, base);
      case ndkEmptyStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkExpressionStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkForInStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkForOfStatement:
        return getIsBaseClassKind(ndkForInStatement, base);
      case ndkForStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkFunction:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkIfStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkLabeledStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkObjectPattern:
        return getIsBaseClassKind(ndkPattern, base);
      case ndkPattern:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkRestElement:
        return getIsBaseClassKind(ndkPattern, base);
      case ndkReturnStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkStatement:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkSwitchCase:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkSwitchStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkThrowStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkTryStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkWhileStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkWithStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkClass:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkClassBody:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkExportSpecifier:
        return getIsBaseClassKind(ndkModuleSpecifier, base);
      case ndkImpSpecifier:
        return getIsBaseClassKind(ndkModuleSpecifier, base);
      case ndkImportDefaultSpecifier:
        return getIsBaseClassKind(ndkImpSpecifier, base);
      case ndkImportNamespaceSpecifier:
        return getIsBaseClassKind(ndkImpSpecifier, base);
      case ndkImportSpecifier:
        return getIsBaseClassKind(ndkImpSpecifier, base);
      case ndkMethodDefinition:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkModuleSpecifier:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkPropertyDefinition:
        return getIsBaseClassKind(ndkPositioned, base);
      default:
        return false;
  }
  return false;
}

const std::string toString(AssignmentOperator kind) {
  switch (kind) {
    case asoAssign: return "asoAssign";
    case asoAdd: return "asoAdd";
    case asoSubtract: return "asoSubtract";
    case asoMultiplication: return "asoMultiplication";
    case asoDivision: return "asoDivision";
    case asoModulus: return "asoModulus";
    case asoLeftShift: return "asoLeftShift";
    case asoRightShift: return "asoRightShift";
    case asoFillNullRightShift: return "asoFillNullRightShift";
    case asoBitwiseOr: return "asoBitwiseOr";
    case asoBitwiseXor: return "asoBitwiseXor";
    case asoBitwiseAnd: return "asoBitwiseAnd";
    case asoExponentiation: return "asoExponentiation";
    case asoAnd: return "asoAnd";
    case asoOr: return "asoOr";
    case asoNullishCoalescing: return "asoNullishCoalescing";
    default: throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(BinaryOperator kind) {
  switch (kind) {
    case bioEqualTo: return "bioEqualTo";
    case bioNotEqual: return "bioNotEqual";
    case bioEqualValueAndType: return "bioEqualValueAndType";
    case bioNotEqualValueAndType: return "bioNotEqualValueAndType";
    case bioLessThan: return "bioLessThan";
    case bioGreaterThan: return "bioGreaterThan";
    case bioGreaterThanEqual: return "bioGreaterThanEqual";
    case bioLessThanEqual: return "bioLessThanEqual";
    case bioLeftShift: return "bioLeftShift";
    case bioRightShift: return "bioRightShift";
    case bioFillNullRightShift: return "bioFillNullRightShift";
    case bioAddition: return "bioAddition";
    case bioSubtraction: return "bioSubtraction";
    case bioMultiplication: return "bioMultiplication";
    case bioDivision: return "bioDivision";
    case bioModulus: return "bioModulus";
    case bioOr: return "bioOr";
    case bioXor: return "bioXor";
    case bioAnd: return "bioAnd";
    case bioIn: return "bioIn";
    case bioInstanceOf: return "bioInstanceOf";
    case bioExponentiation: return "bioExponentiation";
    default: throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(CommentLocation kind) {
  switch (kind) {
    case clTrailing: return "clTrailing";
    case clLeading: return "clLeading";
    default: throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(CommentType kind) {
  switch (kind) {
    case ctLine: return "ctLine";
    case ctBlock: return "ctBlock";
    default: throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(DeclarationKind kind) {
  switch (kind) {
    case dkVar: return "dkVar";
    case dkLet: return "dkLet";
    case dkConst: return "dkConst";
    default: throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(LogicalOperator kind) {
  switch (kind) {
    case looAnd: return "looAnd";
    case looOr: return "looOr";
    case looNullishCoalescing: return "looNullishCoalescing";
    default: throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(MethodDefinitionKind kind) {
  switch (kind) {
    case mdkConstructor: return "mdkConstructor";
    case mdkMethod: return "mdkMethod";
    case mdkGet: return "mdkGet";
    case mdkSet: return "mdkSet";
    default: throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(ProgramSourceType kind) {
  switch (kind) {
    case pstScript: return "pstScript";
    case pstModule: return "pstModule";
    default: throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(PropertyKind kind) {
  switch (kind) {
    case pkInit: return "pkInit";
    case pkGet: return "pkGet";
    case pkSet: return "pkSet";
    default: throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(UnaryOperator kind) {
  switch (kind) {
    case unoMinus: return "unoMinus";
    case unoPlus: return "unoPlus";
    case unoNot: return "unoNot";
    case unoTypeOf: return "unoTypeOf";
    case unoVoid: return "unoVoid";
    case unoDelete: return "unoDelete";
    case unoBitwiseNot: return "unoBitwiseNot";
    default: throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(UpdateOperator kind) {
  switch (kind) {
    case upoIncrement: return "upoIncrement";
    case upoDecrement: return "upoDecrement";
    default: throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(NodeKind kind) {
  switch (kind) {
    case ndkBase: return "ndkBase";
    case ndkComment: return "ndkComment";
    case ndkNamed: return "ndkNamed";
    case ndkPositioned: return "ndkPositioned";
    case ndkProgram: return "ndkProgram";
    case ndkSystem: return "ndkSystem";
    case ndkClassDeclaration: return "ndkClassDeclaration";
    case ndkDeclaration: return "ndkDeclaration";
    case ndkExportAllDeclaration: return "ndkExportAllDeclaration";
    case ndkExportDefaultDeclaration: return "ndkExportDefaultDeclaration";
    case ndkExportNamedDeclaration: return "ndkExportNamedDeclaration";
    case ndkFunctionDeclaration: return "ndkFunctionDeclaration";
    case ndkImportDeclaration: return "ndkImportDeclaration";
    case ndkModuleDeclaration: return "ndkModuleDeclaration";
    case ndkVariableDeclaration: return "ndkVariableDeclaration";
    case ndkVariableDeclarator: return "ndkVariableDeclarator";
    case ndkArrayExpression: return "ndkArrayExpression";
    case ndkArrowFunctionExpression: return "ndkArrowFunctionExpression";
    case ndkAssignmentExpression: return "ndkAssignmentExpression";
    case ndkAwaitExpression: return "ndkAwaitExpression";
    case ndkBigIntLiteral: return "ndkBigIntLiteral";
    case ndkBinaryExpression: return "ndkBinaryExpression";
    case ndkBooleanLiteral: return "ndkBooleanLiteral";
    case ndkCallExpression: return "ndkCallExpression";
    case ndkChainElement: return "ndkChainElement";
    case ndkChainExpression: return "ndkChainExpression";
    case ndkClassExpression: return "ndkClassExpression";
    case ndkConditionalExpression: return "ndkConditionalExpression";
    case ndkExpression: return "ndkExpression";
    case ndkFunctionExpression: return "ndkFunctionExpression";
    case ndkIdentifier: return "ndkIdentifier";
    case ndkImportExpression: return "ndkImportExpression";
    case ndkLiteral: return "ndkLiteral";
    case ndkLogicalExpression: return "ndkLogicalExpression";
    case ndkMemberExpression: return "ndkMemberExpression";
    case ndkMetaProperty: return "ndkMetaProperty";
    case ndkNewExpression: return "ndkNewExpression";
    case ndkNullLiteral: return "ndkNullLiteral";
    case ndkNumberLiteral: return "ndkNumberLiteral";
    case ndkObjectExpression: return "ndkObjectExpression";
    case ndkPrivateIdentifier: return "ndkPrivateIdentifier";
    case ndkProperty: return "ndkProperty";
    case ndkRegExpLiteral: return "ndkRegExpLiteral";
    case ndkSequenceExpression: return "ndkSequenceExpression";
    case ndkSpreadElement: return "ndkSpreadElement";
    case ndkStringLiteral: return "ndkStringLiteral";
    case ndkSuper: return "ndkSuper";
    case ndkTaggedTemplateExpression: return "ndkTaggedTemplateExpression";
    case ndkTemplateElement: return "ndkTemplateElement";
    case ndkTemplateLiteral: return "ndkTemplateLiteral";
    case ndkThisExpression: return "ndkThisExpression";
    case ndkUnaryExpression: return "ndkUnaryExpression";
    case ndkUpdateExpression: return "ndkUpdateExpression";
    case ndkYieldExpression: return "ndkYieldExpression";
    case ndkArrayPattern: return "ndkArrayPattern";
    case ndkAssignmentPattern: return "ndkAssignmentPattern";
    case ndkBlockStatement: return "ndkBlockStatement";
    case ndkBreakStatement: return "ndkBreakStatement";
    case ndkCatchClause: return "ndkCatchClause";
    case ndkContinueStatement: return "ndkContinueStatement";
    case ndkDebuggerStatement: return "ndkDebuggerStatement";
    case ndkDoWhileStatement: return "ndkDoWhileStatement";
    case ndkEmptyStatement: return "ndkEmptyStatement";
    case ndkExpressionStatement: return "ndkExpressionStatement";
    case ndkForInStatement: return "ndkForInStatement";
    case ndkForOfStatement: return "ndkForOfStatement";
    case ndkForStatement: return "ndkForStatement";
    case ndkFunction: return "ndkFunction";
    case ndkIfStatement: return "ndkIfStatement";
    case ndkLabeledStatement: return "ndkLabeledStatement";
    case ndkObjectPattern: return "ndkObjectPattern";
    case ndkPattern: return "ndkPattern";
    case ndkRestElement: return "ndkRestElement";
    case ndkReturnStatement: return "ndkReturnStatement";
    case ndkStatement: return "ndkStatement";
    case ndkSwitchCase: return "ndkSwitchCase";
    case ndkSwitchStatement: return "ndkSwitchStatement";
    case ndkThrowStatement: return "ndkThrowStatement";
    case ndkTryStatement: return "ndkTryStatement";
    case ndkWhileStatement: return "ndkWhileStatement";
    case ndkWithStatement: return "ndkWithStatement";
    case ndkClass: return "ndkClass";
    case ndkClassBody: return "ndkClassBody";
    case ndkExportSpecifier: return "ndkExportSpecifier";
    case ndkImpSpecifier: return "ndkImpSpecifier";
    case ndkImportDefaultSpecifier: return "ndkImportDefaultSpecifier";
    case ndkImportNamespaceSpecifier: return "ndkImportNamespaceSpecifier";
    case ndkImportSpecifier: return "ndkImportSpecifier";
    case ndkMethodDefinition: return "ndkMethodDefinition";
    case ndkModuleSpecifier: return "ndkModuleSpecifier";
    case ndkPropertyDefinition: return "ndkPropertyDefinition";
    default: throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(EdgeKind kind) {
  switch (kind) {
    case edkPositioned_Comments: return "edkPositioned_Comments";
    case edkProgram_HasBody: return "edkProgram_HasBody";
    case edkSystem_HasPrograms: return "edkSystem_HasPrograms";
    case edkExportAllDeclaration_HasSource: return "edkExportAllDeclaration_HasSource";
    case edkExportAllDeclaration_HasExported: return "edkExportAllDeclaration_HasExported";
    case edkExportDefaultDeclaration_HasDeclaration: return "edkExportDefaultDeclaration_HasDeclaration";
    case edkExportNamedDeclaration_HasDeclaration: return "edkExportNamedDeclaration_HasDeclaration";
    case edkExportNamedDeclaration_HasSpecifiers: return "edkExportNamedDeclaration_HasSpecifiers";
    case edkExportNamedDeclaration_HasSource: return "edkExportNamedDeclaration_HasSource";
    case edkImportDeclaration_HasSpecifiers: return "edkImportDeclaration_HasSpecifiers";
    case edkImportDeclaration_HasSource: return "edkImportDeclaration_HasSource";
    case edkVariableDeclaration_HasDeclarations: return "edkVariableDeclaration_HasDeclarations";
    case edkVariableDeclarator_HasIdentifier: return "edkVariableDeclarator_HasIdentifier";
    case edkVariableDeclarator_HasInit: return "edkVariableDeclarator_HasInit";
    case edkArrayExpression_HasElements: return "edkArrayExpression_HasElements";
    case edkAssignmentExpression_HasLeft: return "edkAssignmentExpression_HasLeft";
    case edkAssignmentExpression_HasRight: return "edkAssignmentExpression_HasRight";
    case edkAwaitExpression_HasArgument: return "edkAwaitExpression_HasArgument";
    case edkBinaryExpression_HasLeft: return "edkBinaryExpression_HasLeft";
    case edkBinaryExpression_HasRight: return "edkBinaryExpression_HasRight";
    case edkCallExpression_HasCallee: return "edkCallExpression_HasCallee";
    case edkCallExpression_HasArguments: return "edkCallExpression_HasArguments";
    case edkCallExpression_Calls: return "edkCallExpression_Calls";
    case edkChainExpression_HasExpression: return "edkChainExpression_HasExpression";
    case edkConditionalExpression_HasAlternate: return "edkConditionalExpression_HasAlternate";
    case edkConditionalExpression_HasConsequent: return "edkConditionalExpression_HasConsequent";
    case edkConditionalExpression_HasTest: return "edkConditionalExpression_HasTest";
    case edkIdentifier_RefersTo: return "edkIdentifier_RefersTo";
    case edkImportExpression_HasSource: return "edkImportExpression_HasSource";
    case edkLogicalExpression_HasLeft: return "edkLogicalExpression_HasLeft";
    case edkLogicalExpression_HasRight: return "edkLogicalExpression_HasRight";
    case edkMemberExpression_HasProperty: return "edkMemberExpression_HasProperty";
    case edkMemberExpression_HasObject: return "edkMemberExpression_HasObject";
    case edkMetaProperty_HasMeta: return "edkMetaProperty_HasMeta";
    case edkMetaProperty_HasProperty: return "edkMetaProperty_HasProperty";
    case edkNewExpression_HasCallee: return "edkNewExpression_HasCallee";
    case edkNewExpression_HasArguments: return "edkNewExpression_HasArguments";
    case edkNewExpression_Calls: return "edkNewExpression_Calls";
    case edkObjectExpression_HasProperties: return "edkObjectExpression_HasProperties";
    case edkProperty_HasValue: return "edkProperty_HasValue";
    case edkProperty_HasKey: return "edkProperty_HasKey";
    case edkSequenceExpression_HasExpressions: return "edkSequenceExpression_HasExpressions";
    case edkSpreadElement_HasArgument: return "edkSpreadElement_HasArgument";
    case edkTaggedTemplateExpression_HasTag: return "edkTaggedTemplateExpression_HasTag";
    case edkTaggedTemplateExpression_HasQuasi: return "edkTaggedTemplateExpression_HasQuasi";
    case edkTemplateLiteral_HasQuasis: return "edkTemplateLiteral_HasQuasis";
    case edkTemplateLiteral_HasExpressions: return "edkTemplateLiteral_HasExpressions";
    case edkUnaryExpression_HasArgument: return "edkUnaryExpression_HasArgument";
    case edkUpdateExpression_HasArgument: return "edkUpdateExpression_HasArgument";
    case edkYieldExpression_HasArgument: return "edkYieldExpression_HasArgument";
    case edkArrayPattern_HasElements: return "edkArrayPattern_HasElements";
    case edkAssignmentPattern_HasLeft: return "edkAssignmentPattern_HasLeft";
    case edkAssignmentPattern_HasRight: return "edkAssignmentPattern_HasRight";
    case edkBlockStatement_HasBody: return "edkBlockStatement_HasBody";
    case edkBreakStatement_HasLabel: return "edkBreakStatement_HasLabel";
    case edkCatchClause_HasParam: return "edkCatchClause_HasParam";
    case edkCatchClause_HasBody: return "edkCatchClause_HasBody";
    case edkContinueStatement_HasLabel: return "edkContinueStatement_HasLabel";
    case edkExpressionStatement_HasExpression: return "edkExpressionStatement_HasExpression";
    case edkForInStatement_HasRight: return "edkForInStatement_HasRight";
    case edkForInStatement_HasBody: return "edkForInStatement_HasBody";
    case edkForInStatement_HasLeft: return "edkForInStatement_HasLeft";
    case edkForStatement_HasBody: return "edkForStatement_HasBody";
    case edkForStatement_HasTest: return "edkForStatement_HasTest";
    case edkForStatement_HasUpdate: return "edkForStatement_HasUpdate";
    case edkForStatement_HasInit: return "edkForStatement_HasInit";
    case edkFunction_HasParams: return "edkFunction_HasParams";
    case edkFunction_HasBody: return "edkFunction_HasBody";
    case edkFunction_HasIdentifier: return "edkFunction_HasIdentifier";
    case edkIfStatement_HasTest: return "edkIfStatement_HasTest";
    case edkIfStatement_HasConsequent: return "edkIfStatement_HasConsequent";
    case edkIfStatement_HasAlternate: return "edkIfStatement_HasAlternate";
    case edkLabeledStatement_HasLabel: return "edkLabeledStatement_HasLabel";
    case edkLabeledStatement_HasBody: return "edkLabeledStatement_HasBody";
    case edkObjectPattern_HasProperties: return "edkObjectPattern_HasProperties";
    case edkRestElement_HasArgument: return "edkRestElement_HasArgument";
    case edkReturnStatement_HasArgument: return "edkReturnStatement_HasArgument";
    case edkSwitchCase_HasTest: return "edkSwitchCase_HasTest";
    case edkSwitchCase_HasConsequent: return "edkSwitchCase_HasConsequent";
    case edkSwitchStatement_HasDiscriminant: return "edkSwitchStatement_HasDiscriminant";
    case edkSwitchStatement_HasCases: return "edkSwitchStatement_HasCases";
    case edkThrowStatement_HasArgument: return "edkThrowStatement_HasArgument";
    case edkTryStatement_HasBlock: return "edkTryStatement_HasBlock";
    case edkTryStatement_HasFinalizer: return "edkTryStatement_HasFinalizer";
    case edkTryStatement_HasHandler: return "edkTryStatement_HasHandler";
    case edkWhileStatement_HasBody: return "edkWhileStatement_HasBody";
    case edkWhileStatement_HasTest: return "edkWhileStatement_HasTest";
    case edkWithStatement_HasObject: return "edkWithStatement_HasObject";
    case edkWithStatement_HasBody: return "edkWithStatement_HasBody";
    case edkClass_HasBody: return "edkClass_HasBody";
    case edkClass_HasSuperClass: return "edkClass_HasSuperClass";
    case edkClass_HasIdentifier: return "edkClass_HasIdentifier";
    case edkClassBody_HasBody: return "edkClassBody_HasBody";
    case edkExportSpecifier_HasExported: return "edkExportSpecifier_HasExported";
    case edkImportSpecifier_HasImported: return "edkImportSpecifier_HasImported";
    case edkMethodDefinition_HasKey: return "edkMethodDefinition_HasKey";
    case edkMethodDefinition_HasValue: return "edkMethodDefinition_HasValue";
    case edkModuleSpecifier_HasLocal: return "edkModuleSpecifier_HasLocal";
    case edkPropertyDefinition_HasKey: return "edkPropertyDefinition_HasKey";
    case edkPropertyDefinition_HasValue: return "edkPropertyDefinition_HasValue";
    default: throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

bool getIsValid(NodeId id) {
  return id > 1;
}

double SimilarityMinimum = 0.1;

double getSimilarityMinimum() {
  return SimilarityMinimum;
}

void setSimilarityMinimum(double value) {
  SimilarityMinimum = value;
}

double SimilarityMinForStrings = 0.0;

double getSimilarityMinForStrings() {
  return SimilarityMinForStrings;
}

void setSimilarityMinForStrings(double value) {
  SimilarityMinForStrings = value;
}

double SimilarityMinForEdges = 0.0;

double getSimilarityMinForEdges() {
  return SimilarityMinForEdges;
}

void setSimilarityMinForEdges(double value) {
  SimilarityMinForEdges = value;
}



std::string getLongName(const base::Base& node) {
    std::string name("[");

    if (getIsPositioned(node)) {
        auto& positioned = dynamic_cast<const asg::base::Positioned&>(node).getPosition();

        name += positioned.getPath();
        name += ":" + std::to_string(positioned.getLine()) + ":" + std::to_string(positioned.getCol());
        name += "<";
        name += javascript::asg::Common::toString(node.getNodeKind());
        name += ">";
    }
    else {
        name += "UNKNOWN ";
        name += std::to_string(node.getId());
    }

    name += "]";

    return name;
}
} // Common 

}}}
