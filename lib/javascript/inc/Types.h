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

#ifndef _JAVASCRIPT_TYPES_H_
#define _JAVASCRIPT_TYPES_H_

/**
* \file Types.h
* \brief Contains declaration of internal types.
*/

namespace columbus { namespace javascript { namespace asg {
  enum AssignmentOperator {
    asoAssign,
    asoAdd,
    asoSubtract,
    asoMultiplication,
    asoDivision,
    asoModulus,
    asoLeftShift,
    asoRightShift,
    asoFillNullRightShift,
    asoBitwiseOr,
    asoBitwiseXor,
    asoBitwiseAnd,
    asoExponentiation,
    asoAnd,
    asoOr,
    asoNullishCoalescing,
    asoLAST
  };

  enum BinaryOperator {
    bioEqualTo,
    bioNotEqual,
    bioEqualValueAndType,
    bioNotEqualValueAndType,
    bioLessThan,
    bioGreaterThan,
    bioGreaterThanEqual,
    bioLessThanEqual,
    bioLeftShift,
    bioRightShift,
    bioFillNullRightShift,
    bioAddition,
    bioSubtraction,
    bioMultiplication,
    bioDivision,
    bioModulus,
    bioOr,
    bioXor,
    bioAnd,
    bioIn,
    bioInstanceOf,
    bioExponentiation,
    bioLAST
  };

  enum CommentLocation {
    clTrailing,
    clLeading,
    clLAST
  };

  enum CommentType {
    ctLine,
    ctBlock,
    ctLAST
  };

  enum DeclarationKind {
    dkVar,
    dkLet,
    dkConst,
    dkLAST
  };

  enum LogicalOperator {
    looAnd,
    looOr,
    looNullishCoalescing,
    looLAST
  };

  enum MethodDefinitionKind {
    mdkConstructor,
    mdkMethod,
    mdkGet,
    mdkSet,
    mdkLAST
  };

  enum ProgramSourceType {
    pstScript,
    pstModule,
    pstLAST
  };

  enum PropertyKind {
    pkInit,
    pkGet,
    pkSet,
    pkLAST
  };

  enum UnaryOperator {
    unoMinus,
    unoPlus,
    unoNot,
    unoTypeOf,
    unoVoid,
    unoDelete,
    unoBitwiseNot,
    unoLAST
  };

  enum UpdateOperator {
    upoIncrement,
    upoDecrement,
    upoLAST
  };

  enum NodeKind {
    ndkBase,
    ndkComment,
    ndkNamed,
    ndkPositioned,
    ndkProgram,
    ndkSystem,
    ndkClassDeclaration,
    ndkDeclaration,
    ndkExportAllDeclaration,
    ndkExportDefaultDeclaration,
    ndkExportNamedDeclaration,
    ndkFunctionDeclaration,
    ndkImportDeclaration,
    ndkModuleDeclaration,
    ndkVariableDeclaration,
    ndkVariableDeclarator,
    ndkArrayExpression,
    ndkArrowFunctionExpression,
    ndkAssignmentExpression,
    ndkAwaitExpression,
    ndkBigIntLiteral,
    ndkBinaryExpression,
    ndkBooleanLiteral,
    ndkCallExpression,
    ndkChainElement,
    ndkChainExpression,
    ndkClassExpression,
    ndkConditionalExpression,
    ndkExpression,
    ndkFunctionExpression,
    ndkIdentifier,
    ndkImportExpression,
    ndkLiteral,
    ndkLogicalExpression,
    ndkMemberExpression,
    ndkMetaProperty,
    ndkNewExpression,
    ndkNullLiteral,
    ndkNumberLiteral,
    ndkObjectExpression,
    ndkPrivateIdentifier,
    ndkProperty,
    ndkRegExpLiteral,
    ndkSequenceExpression,
    ndkSpreadElement,
    ndkStringLiteral,
    ndkSuper,
    ndkTaggedTemplateExpression,
    ndkTemplateElement,
    ndkTemplateLiteral,
    ndkThisExpression,
    ndkUnaryExpression,
    ndkUpdateExpression,
    ndkYieldExpression,
    ndkArrayPattern,
    ndkAssignmentPattern,
    ndkBlockStatement,
    ndkBreakStatement,
    ndkCatchClause,
    ndkContinueStatement,
    ndkDebuggerStatement,
    ndkDoWhileStatement,
    ndkEmptyStatement,
    ndkExpressionStatement,
    ndkForInStatement,
    ndkForOfStatement,
    ndkForStatement,
    ndkFunction,
    ndkIfStatement,
    ndkLabeledStatement,
    ndkObjectPattern,
    ndkPattern,
    ndkRestElement,
    ndkReturnStatement,
    ndkStatement,
    ndkSwitchCase,
    ndkSwitchStatement,
    ndkThrowStatement,
    ndkTryStatement,
    ndkWhileStatement,
    ndkWithStatement,
    ndkClass,
    ndkClassBody,
    ndkExportSpecifier,
    ndkImpSpecifier,
    ndkImportDefaultSpecifier,
    ndkImportNamespaceSpecifier,
    ndkImportSpecifier,
    ndkMethodDefinition,
    ndkModuleSpecifier,
    ndkPropertyDefinition,
    ndkLAST
  };

  enum EdgeKind {
    edkPositioned_Comments,
    edkProgram_HasBody,
    edkSystem_HasPrograms,
    edkExportAllDeclaration_HasSource,
    edkExportAllDeclaration_HasExported,
    edkExportDefaultDeclaration_HasDeclaration,
    edkExportNamedDeclaration_HasDeclaration,
    edkExportNamedDeclaration_HasSpecifiers,
    edkExportNamedDeclaration_HasSource,
    edkImportDeclaration_HasSpecifiers,
    edkImportDeclaration_HasSource,
    edkVariableDeclaration_HasDeclarations,
    edkVariableDeclarator_HasIdentifier,
    edkVariableDeclarator_HasInit,
    edkArrayExpression_HasElements,
    edkAssignmentExpression_HasLeft,
    edkAssignmentExpression_HasRight,
    edkAwaitExpression_HasArgument,
    edkBinaryExpression_HasLeft,
    edkBinaryExpression_HasRight,
    edkCallExpression_HasCallee,
    edkCallExpression_HasArguments,
    edkCallExpression_Calls,
    edkChainExpression_HasExpression,
    edkConditionalExpression_HasAlternate,
    edkConditionalExpression_HasConsequent,
    edkConditionalExpression_HasTest,
    edkIdentifier_RefersTo,
    edkImportExpression_HasSource,
    edkLogicalExpression_HasLeft,
    edkLogicalExpression_HasRight,
    edkMemberExpression_HasProperty,
    edkMemberExpression_HasObject,
    edkMetaProperty_HasMeta,
    edkMetaProperty_HasProperty,
    edkNewExpression_HasCallee,
    edkNewExpression_HasArguments,
    edkNewExpression_Calls,
    edkObjectExpression_HasProperties,
    edkProperty_HasValue,
    edkProperty_HasKey,
    edkSequenceExpression_HasExpressions,
    edkSpreadElement_HasArgument,
    edkTaggedTemplateExpression_HasTag,
    edkTaggedTemplateExpression_HasQuasi,
    edkTemplateLiteral_HasQuasis,
    edkTemplateLiteral_HasExpressions,
    edkUnaryExpression_HasArgument,
    edkUpdateExpression_HasArgument,
    edkYieldExpression_HasArgument,
    edkArrayPattern_HasElements,
    edkAssignmentPattern_HasLeft,
    edkAssignmentPattern_HasRight,
    edkBlockStatement_HasBody,
    edkBreakStatement_HasLabel,
    edkCatchClause_HasParam,
    edkCatchClause_HasBody,
    edkContinueStatement_HasLabel,
    edkExpressionStatement_HasExpression,
    edkForInStatement_HasRight,
    edkForInStatement_HasBody,
    edkForInStatement_HasLeft,
    edkForStatement_HasBody,
    edkForStatement_HasTest,
    edkForStatement_HasUpdate,
    edkForStatement_HasInit,
    edkFunction_HasParams,
    edkFunction_HasBody,
    edkFunction_HasIdentifier,
    edkIfStatement_HasTest,
    edkIfStatement_HasConsequent,
    edkIfStatement_HasAlternate,
    edkLabeledStatement_HasLabel,
    edkLabeledStatement_HasBody,
    edkObjectPattern_HasProperties,
    edkRestElement_HasArgument,
    edkReturnStatement_HasArgument,
    edkSwitchCase_HasTest,
    edkSwitchCase_HasConsequent,
    edkSwitchStatement_HasDiscriminant,
    edkSwitchStatement_HasCases,
    edkThrowStatement_HasArgument,
    edkTryStatement_HasBlock,
    edkTryStatement_HasFinalizer,
    edkTryStatement_HasHandler,
    edkWhileStatement_HasBody,
    edkWhileStatement_HasTest,
    edkWithStatement_HasObject,
    edkWithStatement_HasBody,
    edkClass_HasBody,
    edkClass_HasSuperClass,
    edkClass_HasIdentifier,
    edkClassBody_HasBody,
    edkExportSpecifier_HasExported,
    edkImportSpecifier_HasImported,
    edkMethodDefinition_HasKey,
    edkMethodDefinition_HasValue,
    edkModuleSpecifier_HasLocal,
    edkPropertyDefinition_HasKey,
    edkPropertyDefinition_HasValue,
    edkLAST
  };


}}}
#endif

