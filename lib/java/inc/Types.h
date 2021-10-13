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

#ifndef _JAVA_TYPES_H_
#define _JAVA_TYPES_H_

/**
* \file Types.h
* \brief Contains declaration of internal types.
*/

namespace columbus { namespace java { namespace asg {
  enum AccessibilityKind {
    ackNone,
    ackPublic,
    ackProtected,
    ackPrivate,
    ackLAST
  };

  enum AssignmentOperatorKind {
    askAssign,
    askPlusAssign,
    askMinusAssign,
    askTimesAssign,
    askDivideAssign,
    askRemainderAssign,
    askAndAssign,
    askOrAssign,
    askXorAssign,
    askLeftShiftAssign,
    askSignedRightShiftAssign,
    askUnsignedRightShiftAssign,
    askLAST
  };

  enum InfixOperatorKind {
    iokPlus,
    iokMinus,
    iokTimes,
    iokDivide,
    iokRemainder,
    iokLeftShift,
    iokSignedRightShift,
    iokUnsignedRightShift,
    iokBitwiseAndLogicalAnd,
    iokBitwiseAndLogicalOr,
    iokBitwiseAndLogicalXor,
    iokLessThan,
    iokGreaterThan,
    iokLessThanOrEqualTo,
    iokGreaterThanOrEqualTo,
    iokEqualTo,
    iokNotEqualTo,
    iokConditionalAnd,
    iokConditionalOr,
    iokLAST
  };

  enum LambdaBodyKind {
    lbkExpression,
    lbkStatement,
    lbkLAST
  };

  enum LambdaParameterKind {
    lpkImplicit,
    lpkExplicit,
    lpkLAST
  };

  enum MemberReferenceKind {
    mrkSuper,
    mrkUnbound,
    mrkStatic,
    mrkBound,
    mrkImplicitInner,
    mrkToplevel,
    mrkArrayCtor,
    mrkLAST
  };

  enum MemberReferenceModeKind {
    mrmkInvoke,
    mrmkNew,
    mrmkLAST
  };

  enum MemberReferenceOverloadKind {
    mrokOverloaded,
    mrokUnoverloaded,
    mrokLAST
  };

  enum MethodKind {
    mekNormal,
    mekConstructor,
    mekGeneratedDefaultConstructor,
    mekGeneratedAnonymousClassConstructor,
    mekLAST
  };

  enum ModuleKind {
    mkOpen,
    mkStrong,
    mkLAST
  };

  enum PolyExpressionKind {
    pekStandalone,
    pekPoly,
    pekLAST
  };

  enum PostfixOperatorKind {
    pookIncrement,
    pookDecrement,
    pookLAST
  };

  enum PrefixOperatorKind {
    peokIncrement,
    peokDecrement,
    peokPlus,
    peokMinus,
    peokComplement,
    peokNot,
    peokLAST
  };

  enum PrimitiveTypeKind {
    ptkVoid,
    ptkBoolean,
    ptkChar,
    ptkByte,
    ptkShort,
    ptkInt,
    ptkLong,
    ptkFloat,
    ptkDouble,
    ptkLAST
  };

  enum TypeBoundKind {
    tbkWildcard,
    tbkExtends,
    tbkSuper,
    tbkLAST
  };

  enum NodeKind {
    ndkBase,
    ndkBlockComment,
    ndkComment,
    ndkCommentable,
    ndkJavadocComment,
    ndkLineComment,
    ndkNamed,
    ndkNonJavadocComment,
    ndkPositioned,
    ndkPositionedWithoutComment,
    ndkAnnotatedTypeExpression,
    ndkAnnotation,
    ndkArrayAccess,
    ndkArrayTypeExpression,
    ndkAssignment,
    ndkBinary,
    ndkBooleanLiteral,
    ndkCharacterLiteral,
    ndkClassLiteral,
    ndkConditional,
    ndkDoubleLiteral,
    ndkErroneous,
    ndkErroneousTypeExpression,
    ndkExpression,
    ndkExternalTypeExpression,
    ndkFieldAccess,
    ndkFloatLiteral,
    ndkFunctionalExpression,
    ndkIdentifier,
    ndkInfixExpression,
    ndkInstanceOf,
    ndkIntegerLiteral,
    ndkLambda,
    ndkLiteral,
    ndkLongLiteral,
    ndkMarkerAnnotation,
    ndkMemberReference,
    ndkMethodInvocation,
    ndkNewArray,
    ndkNewClass,
    ndkNormalAnnotation,
    ndkNullLiteral,
    ndkNumberLiteral,
    ndkParenthesizedExpression,
    ndkPolyExpression,
    ndkPostfixExpression,
    ndkPrefixExpression,
    ndkPrimitiveTypeExpression,
    ndkQualifiedTypeExpression,
    ndkSimpleTypeExpression,
    ndkSingleElementAnnotation,
    ndkStringLiteral,
    ndkSuper,
    ndkThis,
    ndkTypeApplyExpression,
    ndkTypeCast,
    ndkTypeExpression,
    ndkTypeIntersectionExpression,
    ndkTypeUnionExpression,
    ndkUnary,
    ndkWildcardExpression,
    ndkExports,
    ndkModuleDirective,
    ndkOpens,
    ndkProvides,
    ndkRequires,
    ndkUses,
    ndkAssert,
    ndkBasicFor,
    ndkBlock,
    ndkBreak,
    ndkCase,
    ndkContinue,
    ndkDefault,
    ndkDo,
    ndkEmpty,
    ndkEnhancedFor,
    ndkExpressionStatement,
    ndkFor,
    ndkHandler,
    ndkIf,
    ndkIteration,
    ndkJump,
    ndkLabeledStatement,
    ndkReturn,
    ndkSelection,
    ndkStatement,
    ndkSwitch,
    ndkSwitchLabel,
    ndkSynchronized,
    ndkThrow,
    ndkTry,
    ndkWhile,
    ndkAnnotatedElement,
    ndkAnnotationType,
    ndkAnnotationTypeElement,
    ndkAnonymousClass,
    ndkClass,
    ndkClassDeclaration,
    ndkClassGeneric,
    ndkCompilationUnit,
    ndkDeclaration,
    ndkEnum,
    ndkEnumConstant,
    ndkGenericDeclaration,
    ndkImport,
    ndkInitializerBlock,
    ndkInstanceInitializerBlock,
    ndkInterface,
    ndkInterfaceDeclaration,
    ndkInterfaceGeneric,
    ndkMember,
    ndkMethod,
    ndkMethodDeclaration,
    ndkMethodGeneric,
    ndkModule,
    ndkModuleDeclaration,
    ndkNamedDeclaration,
    ndkNormalMethod,
    ndkPackage,
    ndkPackageDeclaration,
    ndkParameter,
    ndkScope,
    ndkStaticInitializerBlock,
    ndkTypeDeclaration,
    ndkTypeParameter,
    ndkVariable,
    ndkVariableDeclaration,
    ndkArrayType,
    ndkBooleanType,
    ndkBoundedWildcardType,
    ndkByteType,
    ndkCharType,
    ndkClassType,
    ndkDoubleType,
    ndkErrorType,
    ndkFloatType,
    ndkIntType,
    ndkIntersectionType,
    ndkLongType,
    ndkLowerBoundedWildcardType,
    ndkMethodType,
    ndkModuleType,
    ndkNoType,
    ndkNullType,
    ndkPackageType,
    ndkParameterizedType,
    ndkPrimitiveType,
    ndkScopedType,
    ndkShortType,
    ndkType,
    ndkTypeVariable,
    ndkUnboundedWildcardType,
    ndkUnionType,
    ndkUpperBoundedWildcardType,
    ndkVoidType,
    ndkWildcardType,
    ndkLAST
  };

  enum EdgeKind {
    edkCommentable_Comments,
    edkAnnotatedTypeExpression_HasAnnotations,
    edkAnnotatedTypeExpression_HasUnderlyingType,
    edkAnnotation_HasAnnotationName,
    edkArrayTypeExpression_HasComponentType,
    edkBinary_HasLeftOperand,
    edkBinary_HasRightOperand,
    edkClassLiteral_HasComponentType,
    edkConditional_HasCondition,
    edkConditional_HasTrueExpression,
    edkConditional_HasFalseExpression,
    edkErroneous_HasErrors,
    edkErroneousTypeExpression_HasErrors,
    edkExpression_Type,
    edkFunctionalExpression_Target,
    edkIdentifier_RefersTo,
    edkInstanceOf_HasTypeOperand,
    edkLambda_HasParameters,
    edkLambda_HasBody,
    edkMemberReference_HasQualifierExpression,
    edkMemberReference_HasTypeArguments,
    edkMemberReference_ReferredMethod,
    edkMethodInvocation_HasTypeArguments,
    edkMethodInvocation_HasArguments,
    edkMethodInvocation_Invokes,
    edkNewArray_HasComponentType,
    edkNewArray_HasDimensions,
    edkNewArray_HasInitializers,
    edkNewClass_HasEnclosingExpression,
    edkNewClass_HasTypeArguments,
    edkNewClass_HasTypeName,
    edkNewClass_HasArguments,
    edkNewClass_HasAnonymousClass,
    edkNewClass_Constructor,
    edkNormalAnnotation_HasArguments,
    edkQualifiedTypeExpression_HasQualifierType,
    edkQualifiedTypeExpression_HasSimpleType,
    edkSingleElementAnnotation_HasArgument,
    edkTypeApplyExpression_HasRawType,
    edkTypeApplyExpression_HasTypeArguments,
    edkTypeCast_HasTypeOperand,
    edkTypeIntersectionExpression_HasBounds,
    edkTypeUnionExpression_HasAlternatives,
    edkUnary_HasOperand,
    edkWildcardExpression_HasBound,
    edkExports_HasPackageName,
    edkExports_HasModuleNames,
    edkOpens_HasPackageName,
    edkOpens_HasModuleNames,
    edkProvides_HasServiceName,
    edkProvides_HasImplementationNames,
    edkRequires_HasModuleName,
    edkUses_HasServiceName,
    edkAssert_HasCondition,
    edkAssert_HasDetail,
    edkBasicFor_HasInitializers,
    edkBasicFor_HasCondition,
    edkBasicFor_HasUpdates,
    edkBlock_HasStatements,
    edkCase_HasExpression,
    edkDo_HasCondition,
    edkEnhancedFor_HasParameter,
    edkEnhancedFor_HasExpression,
    edkExpressionStatement_HasExpression,
    edkHandler_HasParameter,
    edkHandler_HasBlock,
    edkIf_HasSubstatement,
    edkIf_HasFalseSubstatement,
    edkIteration_HasSubstatement,
    edkJump_Target,
    edkLabeledStatement_HasStatement,
    edkReturn_HasExpression,
    edkSelection_HasCondition,
    edkSwitch_HasCases,
    edkSwitchLabel_HasStatements,
    edkSynchronized_HasLock,
    edkSynchronized_HasBlock,
    edkThrow_HasExpression,
    edkTry_HasResources,
    edkTry_HasBlock,
    edkTry_HasHandlers,
    edkTry_HasFinallyBlock,
    edkWhile_HasCondition,
    edkAnnotatedElement_HasAnnotations,
    edkAnnotationTypeElement_HasDefaultValue,
    edkCompilationUnit_HasPackageDeclaration,
    edkCompilationUnit_HasImports,
    edkCompilationUnit_HasOthers,
    edkCompilationUnit_HasModuleDeclaration,
    edkCompilationUnit_TypeDeclarations,
    edkCompilationUnit_IsInModule,
    edkEnumConstant_HasNewClass,
    edkGenericDeclaration_HasTypeParameters,
    edkImport_HasTarget,
    edkInitializerBlock_HasBody,
    edkMethodDeclaration_HasReturnType,
    edkMethodDeclaration_MethodType,
    edkMethodDeclaration_Overrides,
    edkModule_Packages,
    edkModuleDeclaration_HasName,
    edkModuleDeclaration_HasDirectives,
    edkModuleDeclaration_ModuleType,
    edkModuleDeclaration_RefersTo,
    edkNormalMethod_HasParameters,
    edkNormalMethod_HasBody,
    edkNormalMethod_HasThrownExceptions,
    edkPackage_HasCompilationUnits,
    edkPackage_IsInModule,
    edkPackageDeclaration_HasPackageName,
    edkPackageDeclaration_RefersTo,
    edkScope_HasMembers,
    edkTypeDeclaration_HasSuperClass,
    edkTypeDeclaration_HasSuperInterfaces,
    edkTypeDeclaration_HasOthers,
    edkTypeDeclaration_IsInCompilationUnit,
    edkTypeDeclaration_IsInModule,
    edkTypeParameter_HasBounds,
    edkVariable_HasInitialValue,
    edkVariableDeclaration_HasType,
    edkArrayType_ComponentType,
    edkClassType_RefersTo,
    edkIntersectionType_Bounds,
    edkMethodType_ReturnType,
    edkMethodType_ParameterTypes,
    edkMethodType_ThrownTypes,
    edkModuleType_RefersTo,
    edkPackageType_RefersTo,
    edkParameterizedType_RawType,
    edkParameterizedType_ArgumentTypes,
    edkScopedType_Owner,
    edkTypeVariable_RefersTo,
    edkUnionType_Alternatives,
    edkWildcardType_Bound,
    edkLAST
  };


}}}
#endif

