/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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

package columbus.java.asg.enums;

public enum EdgeKind {

	edkCommentable_Comments,
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
	edkIdentifier_RefersTo,
	edkInstanceOf_HasTypeOperand,
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
	edkTypeUnionExpression_HasAlternatives,
	edkUnary_HasOperand,
	edkWildcardExpression_HasBound,
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
	edkCompilationUnit_TypeDeclarations,
	edkCompilationUnit_HasOthers,
	edkEnumConstant_HasNewClass,
	edkGenericDeclaration_HasTypeParameters,
	edkImport_HasTarget,
	edkInitializerBlock_HasBody,
	edkMethodDeclaration_HasReturnType,
	edkMethodDeclaration_MethodType,
	edkMethodDeclaration_Overrides,
	edkNormalMethod_HasParameters,
	edkNormalMethod_HasBody,
	edkNormalMethod_HasThrownExceptions,
	edkPackage_HasCompilationUnits,
	edkPackageDeclaration_HasPackageName,
	edkPackageDeclaration_RefersTo,
	edkScope_HasMembers,
	edkTypeDeclaration_IsInCompilationUnit,
	edkTypeDeclaration_HasSuperClass,
	edkTypeDeclaration_HasSuperInterfaces,
	edkTypeDeclaration_HasOthers,
	edkTypeParameter_HasBounds,
	edkVariable_HasInitialValue,
	edkVariableDeclaration_HasType,
	edkArrayType_ComponentType,
	edkClassType_RefersTo,
	edkMethodType_ReturnType,
	edkMethodType_ParameterTypes,
	edkMethodType_ThrownTypes,
	edkPackageType_RefersTo,
	edkParameterizedType_RawType,
	edkParameterizedType_ArgumentTypes,
	edkScopedType_Owner,
	edkTypeVariable_RefersTo,
	edkUnionType_Alternatives,
	edkWildcardType_Bound;

}
