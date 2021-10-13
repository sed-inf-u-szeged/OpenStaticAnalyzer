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
    askMatMult,
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
    bakMatrixMultiplication,
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
    pmkKwonlyarg,
    pmkPosonlyarg,
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
    ndkAwait,
    ndkBinary,
    ndkBinaryArithmetic,
    ndkBinaryLogical,
    ndkBytesLiteral,
    ndkCall,
    ndkDictComp,
    ndkDictionary,
    ndkEllipsis,
    ndkExpression,
    ndkExpressionList,
    ndkExtSlice,
    ndkFloatNumber,
    ndkFormattedValue,
    ndkGenerator,
    ndkGeneratorExpression,
    ndkIdentifier,
    ndkIfExpression,
    ndkImagNumber,
    ndkIndex,
    ndkIntegerLiteral,
    ndkJoinedStr,
    ndkKeyValue,
    ndkKeyword,
    ndkLambda,
    ndkList,
    ndkListComp,
    ndkLiteral,
    ndkLongInteger,
    ndkNamedExpr,
    ndkSet,
    ndkSetComp,
    ndkSlice,
    ndkSlicing,
    ndkStarred,
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
    ndkAnnAssign,
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
    ndkNonlocal,
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
    ndkWhile,
    ndkWith,
    ndkWithItem,
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
    edkAwait_HasValue,
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
    edkFormattedValue_HasValue,
    edkFormattedValue_HasFormatSpec,
    edkGenerator_HasCondition,
    edkGenerator_HasIter,
    edkGenerator_HasTarget,
    edkGeneratorExpression_HasExpression,
    edkGeneratorExpression_HasGenerator,
    edkIdentifier_RefersTo,
    edkIfExpression_HasBody,
    edkIfExpression_HasElseBody,
    edkIfExpression_HasTest,
    edkJoinedStr_HasValue,
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
    edkNamedExpr_HasTarget,
    edkNamedExpr_HasValue,
    edkSet_HasExpression,
    edkSetComp_HasExpression,
    edkSetComp_HasGenerator,
    edkSlice_HasLowerBound,
    edkSlice_HasStride,
    edkSlice_HasUpperBound,
    edkStarred_HasValue,
    edkStringConversion_HasExpressionList,
    edkSubscription_HasSlicing,
    edkUnary_HasExpression,
    edkYieldExpression_HasExpression,
    edkModule_HasObject,
    edkModule_HasStatement,
    edkModule_Docstring,
    edkObject_RefersTo,
    edkObject_HasType,
    edkPackage_HasModule,
    edkPackage_HasPackage,
    edkAlias_RefersTo,
    edkAnnAssign_HasAnnotation,
    edkAssert_HasMsgExpression,
    edkAssert_HasTestExpression,
    edkAssign_HasExpression,
    edkAssign_HasTargetList,
    edkBaseSpecifier_HasName,
    edkBaseSpecifier_DerivesFrom,
    edkClassDef_HasObject,
    edkClassDef_HasBaseSpecifier,
    edkClassDef_HasKeyword,
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
    edkFunctionDef_HasReturnAnnotation,
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
    edkNonlocal_HasIdentifier,
    edkParameter_HasDefaultValue,
    edkParameter_HasAnnotation,
    edkParameter_RefersTo,
    edkPrint_HasExpressionList,
    edkPrint_HasDestination,
    edkRaise_HasType,
    edkRaise_HasValue,
    edkRaise_HasTraceback,
    edkRaise_HasException,
    edkRaise_HasCause,
    edkReturn_HasExpression,
    edkSuite_HasStatement,
    edkTargetList_HasTarget,
    edkTry_HasHandler,
    edkTry_HasElseBody,
    edkTry_HasFinallyBody,
    edkWhile_HasTestExpression,
    edkWith_HasWithItem,
    edkWithItem_HasContext,
    edkWithItem_HasTarget,
    edkReferenceType_RefersTo,
    edkLAST
  };


}}}
#endif

