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

#ifndef _PYTHON_TYPES_H_
#define _PYTHON_TYPES_H_

/**
* \file Types.h
* \brief Contains declaration of internal types.
*/

namespace columbus { namespace python { namespace asg {
  enum AssignmentKind {
    askAdd,
    askSub,
    askMult,
    askDiv,
    askMod,
    askPow,
    askLShift,
    askRShift,
    askBitOr,
    askBitXor,
    askBitAnd,
    askFloorDiv,
    askLAST
  };

  enum BinaryArithmeticKind {
    bakMultiplication,
    bakDivision,
    bakFloorDivision,
    bakModulo,
    bakAddition,
    bakSubtraction,
    bakPow,
    bakLShift,
    bakRShift,
    bakBitOr,
    bakBitXor,
    bakBitAnd,
    bakLAST
  };

  enum BinaryLogicalKind {
    blkEq,
    blkNotEq,
    blkLt,
    blkLtE,
    blkGt,
    blkGtE,
    blkIs,
    blkIsNot,
    blkIn,
    blkNotIn,
    blkAnd,
    blkOr,
    blkLAST
  };

  enum OriginKind {
    orkAnalyzer,
    orkGenerator,
    orkLAST
  };

  enum ParameterKind {
    pmkNormal,
    pmkKwarg,
    pmkVararg,
    pmkLAST
  };

  enum SequenceTypeKind {
    sekString,
    sekList,
    sekTuple,
    sekLAST
  };

  enum SimpleTypeKind {
    stkInteger,
    stkLong,
    stkFloat,
    stkImaginary,
    stkBoolean,
    stkNone,
    stkUnknown,
    stkLAST
  };

  enum UnaryKind {
    unkInvert,
    unkNot,
    unkPlus,
    unkMinus,
    unkLAST
  };

  enum NodeKind {
    ndkBase,
    ndkComment,
    ndkDocstring,
    ndkNamed,
    ndkPositioned,
    ndkArgumentList,
    ndkAttributeRef,
    ndkBinary,
    ndkBinaryArithmetic,
    ndkBinaryLogical,
    ndkCall,
    ndkDictComp,
    ndkDictionary,
    ndkEllipsis,
    ndkExpression,
    ndkExpressionList,
    ndkExtSlice,
    ndkFloatNumber,
    ndkGenerator,
    ndkGeneratorExpression,
    ndkIdentifier,
    ndkIfExpression,
    ndkImagNumber,
    ndkIndex,
    ndkIntegerLiteral,
    ndkKeyValue,
    ndkKeyword,
    ndkLambda,
    ndkList,
    ndkListComp,
    ndkLiteral,
    ndkLongInteger,
    ndkSet,
    ndkSetComp,
    ndkSlice,
    ndkSlicing,
    ndkStringConversion,
    ndkStringLiteral,
    ndkSubscription,
    ndkUnary,
    ndkUnaryOperation,
    ndkYieldExpression,
    ndkModule,
    ndkObject,
    ndkPackage,
    ndkAlias,
    ndkAssert,
    ndkAssign,
    ndkAugAssign,
    ndkBaseSpecifier,
    ndkBreak,
    ndkClassDef,
    ndkCompoundStatement,
    ndkContinue,
    ndkDelete,
    ndkExec,
    ndkFor,
    ndkFunctionDef,
    ndkGlobal,
    ndkHandler,
    ndkIf,
    ndkImportFrom,
    ndkImportStatement,
    ndkIteration,
    ndkParameter,
    ndkPass,
    ndkPrint,
    ndkRaise,
    ndkReturn,
    ndkSimpleStatement,
    ndkStatement,
    ndkSuite,
    ndkTargetList,
    ndkTry,
    ndkTryExcept,
    ndkTryFinal,
    ndkWhile,
    ndkWith,
    ndkDictType,
    ndkReferenceType,
    ndkSequenceType,
    ndkSimpleType,
    ndkType,
    ndkLAST
  };

  enum EdgeKind {
    edkPositioned_Comments,
    edkArgumentList_HasPositionalArguments,
    edkArgumentList_HasDictionary,
    edkArgumentList_HasKeyword,
    edkArgumentList_HasTuple,
    edkBinary_HasLeftExpression,
    edkBinary_HasRightExpression,
    edkCall_HasArgumentList,
    edkCall_RefersTo,
    edkDictComp_HasKeyValue,
    edkDictComp_HasGenerator,
    edkDictionary_HasKeyValue,
    edkExpression_HasType,
    edkExpressionList_HasExpression,
    edkExtSlice_HasItem,
    edkGenerator_HasCondition,
    edkGenerator_HasIter,
    edkGenerator_HasTarget,
    edkGeneratorExpression_HasExpression,
    edkGeneratorExpression_HasGenerator,
    edkIdentifier_RefersTo,
    edkIfExpression_HasBody,
    edkIfExpression_HasElseBody,
    edkIfExpression_HasTest,
    edkKeyValue_HasKey,
    edkKeyValue_HasValue,
    edkKeyword_HasKey,
    edkKeyword_HasValue,
    edkLambda_HasObject,
    edkLambda_HasParameter,
    edkLambda_HasExpression,
    edkList_HasExpression,
    edkListComp_HasExpression,
    edkListComp_HasGenerator,
    edkSet_HasExpression,
    edkSetComp_HasExpression,
    edkSetComp_HasGenerator,
    edkSlice_HasLowerBound,
    edkSlice_HasStride,
    edkSlice_HasUpperBound,
    edkStringConversion_HasExpressionList,
    edkSubscription_HasSlicing,
    edkUnary_HasExpression,
    edkYieldExpression_HasYieldExpression,
    edkModule_HasObject,
    edkModule_HasStatement,
    edkModule_Docstring,
    edkObject_RefersTo,
    edkObject_HasType,
    edkPackage_HasModule,
    edkPackage_HasPackage,
    edkAlias_RefersTo,
    edkAssert_HasMsgExpression,
    edkAssert_HasTestExpression,
    edkAssign_HasExpression,
    edkAssign_HasTargetList,
    edkBaseSpecifier_HasName,
    edkBaseSpecifier_DerivesFrom,
    edkClassDef_HasObject,
    edkClassDef_HasBaseSpecifier,
    edkClassDef_HasDecorator,
    edkClassDef_RefersTo,
    edkClassDef_Docstring,
    edkCompoundStatement_HasBody,
    edkDelete_HasTargetList,
    edkExec_HasExpression,
    edkExec_HasGlobals,
    edkExec_HasLocals,
    edkFor_HasExpressionList,
    edkFor_HasTargetList,
    edkFunctionDef_HasDecorator,
    edkFunctionDef_HasObject,
    edkFunctionDef_HasParameter,
    edkFunctionDef_RefersTo,
    edkFunctionDef_ReturnType,
    edkFunctionDef_Docstring,
    edkGlobal_HasIdentifier,
    edkHandler_HasName,
    edkHandler_HasExceptBody,
    edkHandler_HasType,
    edkIf_HasElseBody,
    edkIf_HasTestExpression,
    edkImportStatement_HasAlias,
    edkIteration_HasElseBody,
    edkParameter_HasDefaultValue,
    edkParameter_RefersTo,
    edkPrint_HasExpressionList,
    edkPrint_HasDestination,
    edkRaise_HasTracebackExpression,
    edkRaise_HasTypeExpression,
    edkRaise_HasValueExpression,
    edkReturn_HasExpression,
    edkSuite_HasStatement,
    edkTargetList_HasTarget,
    edkTryExcept_HasElseBody,
    edkTryExcept_HasHandler,
    edkTryExcept_HasFinallyBody,
    edkTryFinal_HasFinallyBody,
    edkWhile_HasTestExpression,
    edkWith_HasExpression,
    edkWith_HasTargetList,
    edkReferenceType_RefersTo,
    edkLAST
  };


}}}
#endif

