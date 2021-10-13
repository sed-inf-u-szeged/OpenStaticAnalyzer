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

#include "java/inc/java.h"
#include "java/inc/messages.h"
#include <sstream>
#include <map>
#include <iomanip>
#include "common/inc/WriteMessage.h"

namespace columbus { namespace java { namespace asg {
namespace Common {

bool getIsBlockComment(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBlockComment;
}

bool getIsComment(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkComment ||
    ndk == ndkJavadocComment ||
    ndk == ndkBlockComment ||
    ndk == ndkLineComment;
}

bool getIsCommentable(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCommentable ||
    ndk == ndkMarkerAnnotation ||
    ndk == ndkNormalAnnotation ||
    ndk == ndkSingleElementAnnotation ||
    ndk == ndkArrayAccess ||
    ndk == ndkAssignment ||
    ndk == ndkFieldAccess ||
    ndk == ndkInfixExpression ||
    ndk == ndkConditional ||
    ndk == ndkErroneous ||
    ndk == ndkIdentifier ||
    ndk == ndkBooleanLiteral ||
    ndk == ndkCharacterLiteral ||
    ndk == ndkClassLiteral ||
    ndk == ndkNullLiteral ||
    ndk == ndkDoubleLiteral ||
    ndk == ndkFloatLiteral ||
    ndk == ndkIntegerLiteral ||
    ndk == ndkLongLiteral ||
    ndk == ndkStringLiteral ||
    ndk == ndkNewArray ||
    ndk == ndkNewClass ||
    ndk == ndkLambda ||
    ndk == ndkMemberReference ||
    ndk == ndkSuper ||
    ndk == ndkThis ||
    ndk == ndkAnnotatedTypeExpression ||
    ndk == ndkArrayTypeExpression ||
    ndk == ndkErroneousTypeExpression ||
    ndk == ndkExternalTypeExpression ||
    ndk == ndkPrimitiveTypeExpression ||
    ndk == ndkQualifiedTypeExpression ||
    ndk == ndkSimpleTypeExpression ||
    ndk == ndkTypeApplyExpression ||
    ndk == ndkTypeIntersectionExpression ||
    ndk == ndkTypeUnionExpression ||
    ndk == ndkWildcardExpression ||
    ndk == ndkInstanceOf ||
    ndk == ndkMethodInvocation ||
    ndk == ndkParenthesizedExpression ||
    ndk == ndkPostfixExpression ||
    ndk == ndkPrefixExpression ||
    ndk == ndkTypeCast ||
    ndk == ndkExports ||
    ndk == ndkOpens ||
    ndk == ndkProvides ||
    ndk == ndkRequires ||
    ndk == ndkUses ||
    ndk == ndkHandler ||
    ndk == ndkAssert ||
    ndk == ndkBlock ||
    ndk == ndkEmpty ||
    ndk == ndkExpressionStatement ||
    ndk == ndkDo ||
    ndk == ndkBasicFor ||
    ndk == ndkEnhancedFor ||
    ndk == ndkWhile ||
    ndk == ndkBreak ||
    ndk == ndkContinue ||
    ndk == ndkLabeledStatement ||
    ndk == ndkReturn ||
    ndk == ndkIf ||
    ndk == ndkSwitch ||
    ndk == ndkSynchronized ||
    ndk == ndkThrow ||
    ndk == ndkTry ||
    ndk == ndkInstanceInitializerBlock ||
    ndk == ndkStaticInitializerBlock ||
    ndk == ndkAnnotationTypeElement ||
    ndk == ndkMethod ||
    ndk == ndkMethodGeneric ||
    ndk == ndkAnnotationType ||
    ndk == ndkAnonymousClass ||
    ndk == ndkClass ||
    ndk == ndkClassGeneric ||
    ndk == ndkEnum ||
    ndk == ndkInterface ||
    ndk == ndkInterfaceGeneric ||
    ndk == ndkEnumConstant ||
    ndk == ndkParameter ||
    ndk == ndkVariable ||
    ndk == ndkCase ||
    ndk == ndkDefault ||
    ndk == ndkImport ||
    ndk == ndkModuleDeclaration ||
    ndk == ndkPackageDeclaration ||
    ndk == ndkTypeParameter ||
    ndk == ndkCompilationUnit ||
    ndk == ndkPackage;
}

bool getIsJavadocComment(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkJavadocComment;
}

bool getIsLineComment(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkLineComment;
}

bool getIsNamed(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNamed ||
    ndk == ndkModule ||
    ndk == ndkAnnotationTypeElement ||
    ndk == ndkMethod ||
    ndk == ndkMethodGeneric ||
    ndk == ndkAnnotationType ||
    ndk == ndkAnonymousClass ||
    ndk == ndkClass ||
    ndk == ndkClassGeneric ||
    ndk == ndkEnum ||
    ndk == ndkInterface ||
    ndk == ndkInterfaceGeneric ||
    ndk == ndkEnumConstant ||
    ndk == ndkParameter ||
    ndk == ndkVariable ||
    ndk == ndkPackage ||
    ndk == ndkTypeParameter;
}

bool getIsNonJavadocComment(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNonJavadocComment ||
    ndk == ndkBlockComment ||
    ndk == ndkLineComment;
}

bool getIsPositioned(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPositioned ||
    ndk == ndkMarkerAnnotation ||
    ndk == ndkNormalAnnotation ||
    ndk == ndkSingleElementAnnotation ||
    ndk == ndkArrayAccess ||
    ndk == ndkAssignment ||
    ndk == ndkFieldAccess ||
    ndk == ndkInfixExpression ||
    ndk == ndkConditional ||
    ndk == ndkErroneous ||
    ndk == ndkIdentifier ||
    ndk == ndkBooleanLiteral ||
    ndk == ndkCharacterLiteral ||
    ndk == ndkClassLiteral ||
    ndk == ndkNullLiteral ||
    ndk == ndkDoubleLiteral ||
    ndk == ndkFloatLiteral ||
    ndk == ndkIntegerLiteral ||
    ndk == ndkLongLiteral ||
    ndk == ndkStringLiteral ||
    ndk == ndkNewArray ||
    ndk == ndkNewClass ||
    ndk == ndkLambda ||
    ndk == ndkMemberReference ||
    ndk == ndkSuper ||
    ndk == ndkThis ||
    ndk == ndkAnnotatedTypeExpression ||
    ndk == ndkArrayTypeExpression ||
    ndk == ndkErroneousTypeExpression ||
    ndk == ndkExternalTypeExpression ||
    ndk == ndkPrimitiveTypeExpression ||
    ndk == ndkQualifiedTypeExpression ||
    ndk == ndkSimpleTypeExpression ||
    ndk == ndkTypeApplyExpression ||
    ndk == ndkTypeIntersectionExpression ||
    ndk == ndkTypeUnionExpression ||
    ndk == ndkWildcardExpression ||
    ndk == ndkInstanceOf ||
    ndk == ndkMethodInvocation ||
    ndk == ndkParenthesizedExpression ||
    ndk == ndkPostfixExpression ||
    ndk == ndkPrefixExpression ||
    ndk == ndkTypeCast ||
    ndk == ndkExports ||
    ndk == ndkOpens ||
    ndk == ndkProvides ||
    ndk == ndkRequires ||
    ndk == ndkUses ||
    ndk == ndkHandler ||
    ndk == ndkAssert ||
    ndk == ndkBlock ||
    ndk == ndkEmpty ||
    ndk == ndkExpressionStatement ||
    ndk == ndkDo ||
    ndk == ndkBasicFor ||
    ndk == ndkEnhancedFor ||
    ndk == ndkWhile ||
    ndk == ndkBreak ||
    ndk == ndkContinue ||
    ndk == ndkLabeledStatement ||
    ndk == ndkReturn ||
    ndk == ndkIf ||
    ndk == ndkSwitch ||
    ndk == ndkSynchronized ||
    ndk == ndkThrow ||
    ndk == ndkTry ||
    ndk == ndkInstanceInitializerBlock ||
    ndk == ndkStaticInitializerBlock ||
    ndk == ndkAnnotationTypeElement ||
    ndk == ndkMethod ||
    ndk == ndkMethodGeneric ||
    ndk == ndkAnnotationType ||
    ndk == ndkAnonymousClass ||
    ndk == ndkClass ||
    ndk == ndkClassGeneric ||
    ndk == ndkEnum ||
    ndk == ndkInterface ||
    ndk == ndkInterfaceGeneric ||
    ndk == ndkEnumConstant ||
    ndk == ndkParameter ||
    ndk == ndkVariable ||
    ndk == ndkCase ||
    ndk == ndkDefault ||
    ndk == ndkImport ||
    ndk == ndkModuleDeclaration ||
    ndk == ndkPackageDeclaration ||
    ndk == ndkTypeParameter;
}

bool getIsPositionedWithoutComment(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPositionedWithoutComment ||
    ndk == ndkJavadocComment ||
    ndk == ndkBlockComment ||
    ndk == ndkLineComment ||
    ndk == ndkMarkerAnnotation ||
    ndk == ndkNormalAnnotation ||
    ndk == ndkSingleElementAnnotation ||
    ndk == ndkArrayAccess ||
    ndk == ndkAssignment ||
    ndk == ndkFieldAccess ||
    ndk == ndkInfixExpression ||
    ndk == ndkConditional ||
    ndk == ndkErroneous ||
    ndk == ndkIdentifier ||
    ndk == ndkBooleanLiteral ||
    ndk == ndkCharacterLiteral ||
    ndk == ndkClassLiteral ||
    ndk == ndkNullLiteral ||
    ndk == ndkDoubleLiteral ||
    ndk == ndkFloatLiteral ||
    ndk == ndkIntegerLiteral ||
    ndk == ndkLongLiteral ||
    ndk == ndkStringLiteral ||
    ndk == ndkNewArray ||
    ndk == ndkNewClass ||
    ndk == ndkLambda ||
    ndk == ndkMemberReference ||
    ndk == ndkSuper ||
    ndk == ndkThis ||
    ndk == ndkAnnotatedTypeExpression ||
    ndk == ndkArrayTypeExpression ||
    ndk == ndkErroneousTypeExpression ||
    ndk == ndkExternalTypeExpression ||
    ndk == ndkPrimitiveTypeExpression ||
    ndk == ndkQualifiedTypeExpression ||
    ndk == ndkSimpleTypeExpression ||
    ndk == ndkTypeApplyExpression ||
    ndk == ndkTypeIntersectionExpression ||
    ndk == ndkTypeUnionExpression ||
    ndk == ndkWildcardExpression ||
    ndk == ndkInstanceOf ||
    ndk == ndkMethodInvocation ||
    ndk == ndkParenthesizedExpression ||
    ndk == ndkPostfixExpression ||
    ndk == ndkPrefixExpression ||
    ndk == ndkTypeCast ||
    ndk == ndkExports ||
    ndk == ndkOpens ||
    ndk == ndkProvides ||
    ndk == ndkRequires ||
    ndk == ndkUses ||
    ndk == ndkHandler ||
    ndk == ndkAssert ||
    ndk == ndkBlock ||
    ndk == ndkEmpty ||
    ndk == ndkExpressionStatement ||
    ndk == ndkDo ||
    ndk == ndkBasicFor ||
    ndk == ndkEnhancedFor ||
    ndk == ndkWhile ||
    ndk == ndkBreak ||
    ndk == ndkContinue ||
    ndk == ndkLabeledStatement ||
    ndk == ndkReturn ||
    ndk == ndkIf ||
    ndk == ndkSwitch ||
    ndk == ndkSynchronized ||
    ndk == ndkThrow ||
    ndk == ndkTry ||
    ndk == ndkInstanceInitializerBlock ||
    ndk == ndkStaticInitializerBlock ||
    ndk == ndkAnnotationTypeElement ||
    ndk == ndkMethod ||
    ndk == ndkMethodGeneric ||
    ndk == ndkAnnotationType ||
    ndk == ndkAnonymousClass ||
    ndk == ndkClass ||
    ndk == ndkClassGeneric ||
    ndk == ndkEnum ||
    ndk == ndkInterface ||
    ndk == ndkInterfaceGeneric ||
    ndk == ndkEnumConstant ||
    ndk == ndkParameter ||
    ndk == ndkVariable ||
    ndk == ndkCase ||
    ndk == ndkDefault ||
    ndk == ndkImport ||
    ndk == ndkModuleDeclaration ||
    ndk == ndkPackageDeclaration ||
    ndk == ndkTypeParameter ||
    ndk == ndkCompilationUnit;
}

bool getIsAnnotatedTypeExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAnnotatedTypeExpression;
}

bool getIsAnnotation(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAnnotation ||
    ndk == ndkMarkerAnnotation ||
    ndk == ndkNormalAnnotation ||
    ndk == ndkSingleElementAnnotation;
}

bool getIsArrayAccess(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkArrayAccess;
}

bool getIsArrayTypeExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkArrayTypeExpression;
}

bool getIsAssignment(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAssignment;
}

bool getIsBinary(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBinary ||
    ndk == ndkArrayAccess ||
    ndk == ndkAssignment ||
    ndk == ndkFieldAccess ||
    ndk == ndkInfixExpression;
}

bool getIsBooleanLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBooleanLiteral;
}

bool getIsCharacterLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCharacterLiteral;
}

bool getIsClassLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkClassLiteral;
}

bool getIsConditional(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkConditional;
}

bool getIsDoubleLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkDoubleLiteral;
}

bool getIsErroneous(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkErroneous;
}

bool getIsErroneousTypeExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkErroneousTypeExpression;
}

bool getIsExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkExpression ||
    ndk == ndkMarkerAnnotation ||
    ndk == ndkNormalAnnotation ||
    ndk == ndkSingleElementAnnotation ||
    ndk == ndkArrayAccess ||
    ndk == ndkAssignment ||
    ndk == ndkFieldAccess ||
    ndk == ndkInfixExpression ||
    ndk == ndkConditional ||
    ndk == ndkErroneous ||
    ndk == ndkIdentifier ||
    ndk == ndkBooleanLiteral ||
    ndk == ndkCharacterLiteral ||
    ndk == ndkClassLiteral ||
    ndk == ndkNullLiteral ||
    ndk == ndkDoubleLiteral ||
    ndk == ndkFloatLiteral ||
    ndk == ndkIntegerLiteral ||
    ndk == ndkLongLiteral ||
    ndk == ndkStringLiteral ||
    ndk == ndkNewArray ||
    ndk == ndkNewClass ||
    ndk == ndkLambda ||
    ndk == ndkMemberReference ||
    ndk == ndkSuper ||
    ndk == ndkThis ||
    ndk == ndkAnnotatedTypeExpression ||
    ndk == ndkArrayTypeExpression ||
    ndk == ndkErroneousTypeExpression ||
    ndk == ndkExternalTypeExpression ||
    ndk == ndkPrimitiveTypeExpression ||
    ndk == ndkQualifiedTypeExpression ||
    ndk == ndkSimpleTypeExpression ||
    ndk == ndkTypeApplyExpression ||
    ndk == ndkTypeIntersectionExpression ||
    ndk == ndkTypeUnionExpression ||
    ndk == ndkWildcardExpression ||
    ndk == ndkInstanceOf ||
    ndk == ndkMethodInvocation ||
    ndk == ndkParenthesizedExpression ||
    ndk == ndkPostfixExpression ||
    ndk == ndkPrefixExpression ||
    ndk == ndkTypeCast;
}

bool getIsExternalTypeExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkExternalTypeExpression;
}

bool getIsFieldAccess(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFieldAccess;
}

bool getIsFloatLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFloatLiteral;
}

bool getIsFunctionalExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFunctionalExpression ||
    ndk == ndkLambda ||
    ndk == ndkMemberReference;
}

bool getIsIdentifier(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIdentifier;
}

bool getIsInfixExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkInfixExpression;
}

bool getIsInstanceOf(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkInstanceOf;
}

bool getIsIntegerLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIntegerLiteral;
}

bool getIsLambda(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkLambda;
}

bool getIsLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkLiteral ||
    ndk == ndkBooleanLiteral ||
    ndk == ndkCharacterLiteral ||
    ndk == ndkClassLiteral ||
    ndk == ndkNullLiteral ||
    ndk == ndkDoubleLiteral ||
    ndk == ndkFloatLiteral ||
    ndk == ndkIntegerLiteral ||
    ndk == ndkLongLiteral ||
    ndk == ndkStringLiteral;
}

bool getIsLongLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkLongLiteral;
}

bool getIsMarkerAnnotation(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMarkerAnnotation;
}

bool getIsMemberReference(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMemberReference;
}

bool getIsMethodInvocation(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMethodInvocation;
}

bool getIsNewArray(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNewArray;
}

bool getIsNewClass(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNewClass;
}

bool getIsNormalAnnotation(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNormalAnnotation;
}

bool getIsNullLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNullLiteral;
}

bool getIsNumberLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNumberLiteral ||
    ndk == ndkDoubleLiteral ||
    ndk == ndkFloatLiteral ||
    ndk == ndkIntegerLiteral ||
    ndk == ndkLongLiteral;
}

bool getIsParenthesizedExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkParenthesizedExpression;
}

bool getIsPolyExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPolyExpression ||
    ndk == ndkLambda ||
    ndk == ndkMemberReference;
}

bool getIsPostfixExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPostfixExpression;
}

bool getIsPrefixExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPrefixExpression;
}

bool getIsPrimitiveTypeExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPrimitiveTypeExpression;
}

bool getIsQualifiedTypeExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkQualifiedTypeExpression;
}

bool getIsSimpleTypeExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSimpleTypeExpression;
}

bool getIsSingleElementAnnotation(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSingleElementAnnotation;
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

bool getIsThis(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkThis;
}

bool getIsTypeApplyExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeApplyExpression;
}

bool getIsTypeCast(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeCast;
}

bool getIsTypeExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeExpression ||
    ndk == ndkAnnotatedTypeExpression ||
    ndk == ndkArrayTypeExpression ||
    ndk == ndkErroneousTypeExpression ||
    ndk == ndkExternalTypeExpression ||
    ndk == ndkPrimitiveTypeExpression ||
    ndk == ndkQualifiedTypeExpression ||
    ndk == ndkSimpleTypeExpression ||
    ndk == ndkTypeApplyExpression ||
    ndk == ndkTypeIntersectionExpression ||
    ndk == ndkTypeUnionExpression ||
    ndk == ndkWildcardExpression;
}

bool getIsTypeIntersectionExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeIntersectionExpression;
}

bool getIsTypeUnionExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeUnionExpression;
}

bool getIsUnary(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkUnary ||
    ndk == ndkInstanceOf ||
    ndk == ndkMethodInvocation ||
    ndk == ndkParenthesizedExpression ||
    ndk == ndkPostfixExpression ||
    ndk == ndkPrefixExpression ||
    ndk == ndkTypeCast;
}

bool getIsWildcardExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkWildcardExpression;
}

bool getIsExports(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkExports;
}

bool getIsModuleDirective(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkModuleDirective ||
    ndk == ndkExports ||
    ndk == ndkOpens ||
    ndk == ndkProvides ||
    ndk == ndkRequires ||
    ndk == ndkUses;
}

bool getIsOpens(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkOpens;
}

bool getIsProvides(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkProvides;
}

bool getIsRequires(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkRequires;
}

bool getIsUses(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkUses;
}

bool getIsAssert(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAssert;
}

bool getIsBasicFor(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBasicFor;
}

bool getIsBlock(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBlock;
}

bool getIsBreak(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBreak;
}

bool getIsCase(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCase;
}

bool getIsContinue(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkContinue;
}

bool getIsDefault(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkDefault;
}

bool getIsDo(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkDo;
}

bool getIsEmpty(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkEmpty;
}

bool getIsEnhancedFor(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkEnhancedFor;
}

bool getIsExpressionStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkExpressionStatement;
}

bool getIsFor(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFor ||
    ndk == ndkBasicFor ||
    ndk == ndkEnhancedFor;
}

bool getIsHandler(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkHandler;
}

bool getIsIf(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIf;
}

bool getIsIteration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIteration ||
    ndk == ndkDo ||
    ndk == ndkBasicFor ||
    ndk == ndkEnhancedFor ||
    ndk == ndkWhile;
}

bool getIsJump(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkJump ||
    ndk == ndkBreak ||
    ndk == ndkContinue;
}

bool getIsLabeledStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkLabeledStatement;
}

bool getIsReturn(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkReturn;
}

bool getIsSelection(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSelection ||
    ndk == ndkIf ||
    ndk == ndkSwitch;
}

bool getIsStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkStatement ||
    ndk == ndkAssert ||
    ndk == ndkBlock ||
    ndk == ndkEmpty ||
    ndk == ndkExpressionStatement ||
    ndk == ndkDo ||
    ndk == ndkBasicFor ||
    ndk == ndkEnhancedFor ||
    ndk == ndkWhile ||
    ndk == ndkBreak ||
    ndk == ndkContinue ||
    ndk == ndkLabeledStatement ||
    ndk == ndkReturn ||
    ndk == ndkIf ||
    ndk == ndkSwitch ||
    ndk == ndkSynchronized ||
    ndk == ndkThrow ||
    ndk == ndkTry ||
    ndk == ndkInstanceInitializerBlock ||
    ndk == ndkStaticInitializerBlock ||
    ndk == ndkAnnotationTypeElement ||
    ndk == ndkMethod ||
    ndk == ndkMethodGeneric ||
    ndk == ndkAnnotationType ||
    ndk == ndkAnonymousClass ||
    ndk == ndkClass ||
    ndk == ndkClassGeneric ||
    ndk == ndkEnum ||
    ndk == ndkInterface ||
    ndk == ndkInterfaceGeneric ||
    ndk == ndkEnumConstant ||
    ndk == ndkParameter ||
    ndk == ndkVariable;
}

bool getIsSwitch(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSwitch;
}

bool getIsSwitchLabel(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSwitchLabel ||
    ndk == ndkCase ||
    ndk == ndkDefault;
}

bool getIsSynchronized(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSynchronized;
}

bool getIsThrow(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkThrow;
}

bool getIsTry(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTry;
}

bool getIsWhile(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkWhile;
}

bool getIsAnnotatedElement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAnnotatedElement ||
    ndk == ndkInstanceInitializerBlock ||
    ndk == ndkStaticInitializerBlock ||
    ndk == ndkAnnotationTypeElement ||
    ndk == ndkMethod ||
    ndk == ndkMethodGeneric ||
    ndk == ndkAnnotationType ||
    ndk == ndkAnonymousClass ||
    ndk == ndkClass ||
    ndk == ndkClassGeneric ||
    ndk == ndkEnum ||
    ndk == ndkInterface ||
    ndk == ndkInterfaceGeneric ||
    ndk == ndkEnumConstant ||
    ndk == ndkParameter ||
    ndk == ndkVariable ||
    ndk == ndkPackage;
}

bool getIsAnnotationType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAnnotationType;
}

bool getIsAnnotationTypeElement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAnnotationTypeElement;
}

bool getIsAnonymousClass(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAnonymousClass;
}

bool getIsClass(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkClass;
}

bool getIsClassDeclaration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkClassDeclaration ||
    ndk == ndkAnonymousClass ||
    ndk == ndkClass ||
    ndk == ndkClassGeneric;
}

bool getIsClassGeneric(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkClassGeneric;
}

bool getIsCompilationUnit(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCompilationUnit;
}

bool getIsDeclaration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkDeclaration ||
    ndk == ndkInstanceInitializerBlock ||
    ndk == ndkStaticInitializerBlock ||
    ndk == ndkAnnotationTypeElement ||
    ndk == ndkMethod ||
    ndk == ndkMethodGeneric ||
    ndk == ndkAnnotationType ||
    ndk == ndkAnonymousClass ||
    ndk == ndkClass ||
    ndk == ndkClassGeneric ||
    ndk == ndkEnum ||
    ndk == ndkInterface ||
    ndk == ndkInterfaceGeneric ||
    ndk == ndkEnumConstant ||
    ndk == ndkParameter ||
    ndk == ndkVariable;
}

bool getIsEnum(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkEnum;
}

bool getIsEnumConstant(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkEnumConstant;
}

bool getIsGenericDeclaration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkGenericDeclaration ||
    ndk == ndkClassGeneric ||
    ndk == ndkInterfaceGeneric ||
    ndk == ndkMethodGeneric;
}

bool getIsImport(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkImport;
}

bool getIsInitializerBlock(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkInitializerBlock ||
    ndk == ndkInstanceInitializerBlock ||
    ndk == ndkStaticInitializerBlock;
}

bool getIsInstanceInitializerBlock(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkInstanceInitializerBlock;
}

bool getIsInterface(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkInterface;
}

bool getIsInterfaceDeclaration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkInterfaceDeclaration ||
    ndk == ndkInterface ||
    ndk == ndkInterfaceGeneric;
}

bool getIsInterfaceGeneric(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkInterfaceGeneric;
}

bool getIsMember(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMember ||
    ndk == ndkInstanceInitializerBlock ||
    ndk == ndkStaticInitializerBlock ||
    ndk == ndkAnnotationTypeElement ||
    ndk == ndkMethod ||
    ndk == ndkMethodGeneric ||
    ndk == ndkAnnotationType ||
    ndk == ndkAnonymousClass ||
    ndk == ndkClass ||
    ndk == ndkClassGeneric ||
    ndk == ndkEnum ||
    ndk == ndkInterface ||
    ndk == ndkInterfaceGeneric ||
    ndk == ndkEnumConstant ||
    ndk == ndkParameter ||
    ndk == ndkVariable ||
    ndk == ndkPackage;
}

bool getIsMethod(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMethod;
}

bool getIsMethodDeclaration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMethodDeclaration ||
    ndk == ndkAnnotationTypeElement ||
    ndk == ndkMethod ||
    ndk == ndkMethodGeneric;
}

bool getIsMethodGeneric(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMethodGeneric;
}

bool getIsModule(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkModule;
}

bool getIsModuleDeclaration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkModuleDeclaration;
}

bool getIsNamedDeclaration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNamedDeclaration ||
    ndk == ndkAnnotationTypeElement ||
    ndk == ndkMethod ||
    ndk == ndkMethodGeneric ||
    ndk == ndkAnnotationType ||
    ndk == ndkAnonymousClass ||
    ndk == ndkClass ||
    ndk == ndkClassGeneric ||
    ndk == ndkEnum ||
    ndk == ndkInterface ||
    ndk == ndkInterfaceGeneric ||
    ndk == ndkEnumConstant ||
    ndk == ndkParameter ||
    ndk == ndkVariable;
}

bool getIsNormalMethod(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNormalMethod ||
    ndk == ndkMethod ||
    ndk == ndkMethodGeneric;
}

bool getIsPackage(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPackage;
}

bool getIsPackageDeclaration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPackageDeclaration;
}

bool getIsParameter(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkParameter;
}

bool getIsScope(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkScope ||
    ndk == ndkPackage ||
    ndk == ndkAnnotationType ||
    ndk == ndkAnonymousClass ||
    ndk == ndkClass ||
    ndk == ndkClassGeneric ||
    ndk == ndkEnum ||
    ndk == ndkInterface ||
    ndk == ndkInterfaceGeneric;
}

bool getIsStaticInitializerBlock(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkStaticInitializerBlock;
}

bool getIsTypeDeclaration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeDeclaration ||
    ndk == ndkAnnotationType ||
    ndk == ndkAnonymousClass ||
    ndk == ndkClass ||
    ndk == ndkClassGeneric ||
    ndk == ndkEnum ||
    ndk == ndkInterface ||
    ndk == ndkInterfaceGeneric;
}

bool getIsTypeParameter(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeParameter;
}

bool getIsVariable(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkVariable;
}

bool getIsVariableDeclaration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkVariableDeclaration ||
    ndk == ndkEnumConstant ||
    ndk == ndkParameter ||
    ndk == ndkVariable;
}

bool getIsArrayType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkArrayType;
}

bool getIsBooleanType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBooleanType;
}

bool getIsBoundedWildcardType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBoundedWildcardType ||
    ndk == ndkLowerBoundedWildcardType ||
    ndk == ndkUpperBoundedWildcardType;
}

bool getIsByteType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkByteType;
}

bool getIsCharType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCharType;
}

bool getIsClassType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkClassType;
}

bool getIsDoubleType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkDoubleType;
}

bool getIsErrorType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkErrorType;
}

bool getIsFloatType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFloatType;
}

bool getIsIntType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIntType;
}

bool getIsIntersectionType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIntersectionType;
}

bool getIsLongType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkLongType;
}

bool getIsLowerBoundedWildcardType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkLowerBoundedWildcardType;
}

bool getIsMethodType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMethodType;
}

bool getIsModuleType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkModuleType;
}

bool getIsNoType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNoType;
}

bool getIsNullType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNullType;
}

bool getIsPackageType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPackageType;
}

bool getIsParameterizedType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkParameterizedType;
}

bool getIsPrimitiveType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPrimitiveType ||
    ndk == ndkBooleanType ||
    ndk == ndkByteType ||
    ndk == ndkCharType ||
    ndk == ndkDoubleType ||
    ndk == ndkFloatType ||
    ndk == ndkIntType ||
    ndk == ndkLongType ||
    ndk == ndkShortType ||
    ndk == ndkVoidType;
}

bool getIsScopedType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkScopedType ||
    ndk == ndkClassType ||
    ndk == ndkParameterizedType;
}

bool getIsShortType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkShortType;
}

bool getIsType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkType ||
    ndk == ndkArrayType ||
    ndk == ndkErrorType ||
    ndk == ndkIntersectionType ||
    ndk == ndkMethodType ||
    ndk == ndkModuleType ||
    ndk == ndkNoType ||
    ndk == ndkNullType ||
    ndk == ndkPackageType ||
    ndk == ndkBooleanType ||
    ndk == ndkByteType ||
    ndk == ndkCharType ||
    ndk == ndkDoubleType ||
    ndk == ndkFloatType ||
    ndk == ndkIntType ||
    ndk == ndkLongType ||
    ndk == ndkShortType ||
    ndk == ndkVoidType ||
    ndk == ndkClassType ||
    ndk == ndkParameterizedType ||
    ndk == ndkTypeVariable ||
    ndk == ndkUnionType ||
    ndk == ndkLowerBoundedWildcardType ||
    ndk == ndkUpperBoundedWildcardType ||
    ndk == ndkUnboundedWildcardType;
}

bool getIsTypeVariable(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeVariable;
}

bool getIsUnboundedWildcardType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkUnboundedWildcardType;
}

bool getIsUnionType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkUnionType;
}

bool getIsUpperBoundedWildcardType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkUpperBoundedWildcardType;
}

bool getIsVoidType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkVoidType;
}

bool getIsWildcardType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkWildcardType ||
    ndk == ndkLowerBoundedWildcardType ||
    ndk == ndkUpperBoundedWildcardType ||
    ndk == ndkUnboundedWildcardType;
}

bool getIsAPSpecNode(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBlockComment ||
    ndk == ndkJavadocComment ||
    ndk == ndkLineComment ||
    ndk == ndkArrayType ||
    ndk == ndkBooleanType ||
    ndk == ndkByteType ||
    ndk == ndkCharType ||
    ndk == ndkClassType ||
    ndk == ndkDoubleType ||
    ndk == ndkErrorType ||
    ndk == ndkFloatType ||
    ndk == ndkIntType ||
    ndk == ndkLongType ||
    ndk == ndkLowerBoundedWildcardType ||
    ndk == ndkMethodType ||
    ndk == ndkNoType ||
    ndk == ndkNullType ||
    ndk == ndkPackageType ||
    ndk == ndkParameterizedType ||
    ndk == ndkShortType ||
    ndk == ndkTypeVariable ||
    ndk == ndkUnboundedWildcardType ||
    ndk == ndkUnionType ||
    ndk == ndkUpperBoundedWildcardType ||
    ndk == ndkVoidType;
}

bool getIsComposite(const base::Base& node) {
  return !getIsNotComposite(node);
}

bool getIsNotComposite(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIdentifier ||
    ndk == ndkBooleanLiteral ||
    ndk == ndkCharacterLiteral ||
    ndk == ndkNullLiteral ||
    ndk == ndkDoubleLiteral ||
    ndk == ndkFloatLiteral ||
    ndk == ndkIntegerLiteral ||
    ndk == ndkLongLiteral ||
    ndk == ndkStringLiteral ||
    ndk == ndkSuper ||
    ndk == ndkThis ||
    ndk == ndkExternalTypeExpression ||
    ndk == ndkPrimitiveTypeExpression ||
    ndk == ndkSimpleTypeExpression ||
    ndk == ndkEmpty ||
    ndk == ndkBreak ||
    ndk == ndkContinue ||
    ndk == ndkModule ||
    ndk == ndkJavadocComment ||
    ndk == ndkBlockComment ||
    ndk == ndkLineComment ||
    ndk == ndkArrayType ||
    ndk == ndkErrorType ||
    ndk == ndkIntersectionType ||
    ndk == ndkMethodType ||
    ndk == ndkModuleType ||
    ndk == ndkNoType ||
    ndk == ndkNullType ||
    ndk == ndkPackageType ||
    ndk == ndkBooleanType ||
    ndk == ndkByteType ||
    ndk == ndkCharType ||
    ndk == ndkDoubleType ||
    ndk == ndkFloatType ||
    ndk == ndkIntType ||
    ndk == ndkLongType ||
    ndk == ndkShortType ||
    ndk == ndkVoidType ||
    ndk == ndkClassType ||
    ndk == ndkParameterizedType ||
    ndk == ndkTypeVariable ||
    ndk == ndkUnionType ||
    ndk == ndkLowerBoundedWildcardType ||
    ndk == ndkUpperBoundedWildcardType ||
    ndk == ndkUnboundedWildcardType;
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
      case ndkBlockComment:
        return getIsBaseClassKind(ndkNonJavadocComment, base);
      case ndkComment:
        return getIsBaseClassKind(ndkPositionedWithoutComment, base);
      case ndkCommentable:
        return getIsBaseClassKind(ndkBase, base);
      case ndkJavadocComment:
        return getIsBaseClassKind(ndkComment, base);
      case ndkLineComment:
        return getIsBaseClassKind(ndkNonJavadocComment, base);
      case ndkNamed:
        return getIsBaseClassKind(ndkBase, base);
      case ndkNonJavadocComment:
        return getIsBaseClassKind(ndkComment, base);
      case ndkPositioned:
        return getIsBaseClassKind(ndkCommentable, base) ||
          getIsBaseClassKind(ndkPositionedWithoutComment, base);
      case ndkPositionedWithoutComment:
        return getIsBaseClassKind(ndkBase, base);
      case ndkAnnotatedTypeExpression:
        return getIsBaseClassKind(ndkTypeExpression, base);
      case ndkAnnotation:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkArrayAccess:
        return getIsBaseClassKind(ndkBinary, base);
      case ndkArrayTypeExpression:
        return getIsBaseClassKind(ndkTypeExpression, base);
      case ndkAssignment:
        return getIsBaseClassKind(ndkBinary, base);
      case ndkBinary:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkBooleanLiteral:
        return getIsBaseClassKind(ndkLiteral, base);
      case ndkCharacterLiteral:
        return getIsBaseClassKind(ndkLiteral, base);
      case ndkClassLiteral:
        return getIsBaseClassKind(ndkLiteral, base);
      case ndkConditional:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkDoubleLiteral:
        return getIsBaseClassKind(ndkNumberLiteral, base);
      case ndkErroneous:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkErroneousTypeExpression:
        return getIsBaseClassKind(ndkTypeExpression, base);
      case ndkExpression:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkExternalTypeExpression:
        return getIsBaseClassKind(ndkTypeExpression, base);
      case ndkFieldAccess:
        return getIsBaseClassKind(ndkBinary, base);
      case ndkFloatLiteral:
        return getIsBaseClassKind(ndkNumberLiteral, base);
      case ndkFunctionalExpression:
        return getIsBaseClassKind(ndkPolyExpression, base);
      case ndkIdentifier:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkInfixExpression:
        return getIsBaseClassKind(ndkBinary, base);
      case ndkInstanceOf:
        return getIsBaseClassKind(ndkUnary, base);
      case ndkIntegerLiteral:
        return getIsBaseClassKind(ndkNumberLiteral, base);
      case ndkLambda:
        return getIsBaseClassKind(ndkFunctionalExpression, base);
      case ndkLiteral:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkLongLiteral:
        return getIsBaseClassKind(ndkNumberLiteral, base);
      case ndkMarkerAnnotation:
        return getIsBaseClassKind(ndkAnnotation, base);
      case ndkMemberReference:
        return getIsBaseClassKind(ndkFunctionalExpression, base);
      case ndkMethodInvocation:
        return getIsBaseClassKind(ndkUnary, base);
      case ndkNewArray:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkNewClass:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkNormalAnnotation:
        return getIsBaseClassKind(ndkAnnotation, base);
      case ndkNullLiteral:
        return getIsBaseClassKind(ndkLiteral, base);
      case ndkNumberLiteral:
        return getIsBaseClassKind(ndkLiteral, base);
      case ndkParenthesizedExpression:
        return getIsBaseClassKind(ndkUnary, base);
      case ndkPolyExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkPostfixExpression:
        return getIsBaseClassKind(ndkUnary, base);
      case ndkPrefixExpression:
        return getIsBaseClassKind(ndkUnary, base);
      case ndkPrimitiveTypeExpression:
        return getIsBaseClassKind(ndkTypeExpression, base);
      case ndkQualifiedTypeExpression:
        return getIsBaseClassKind(ndkTypeExpression, base);
      case ndkSimpleTypeExpression:
        return getIsBaseClassKind(ndkTypeExpression, base);
      case ndkSingleElementAnnotation:
        return getIsBaseClassKind(ndkAnnotation, base);
      case ndkStringLiteral:
        return getIsBaseClassKind(ndkLiteral, base);
      case ndkSuper:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkThis:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkTypeApplyExpression:
        return getIsBaseClassKind(ndkTypeExpression, base);
      case ndkTypeCast:
        return getIsBaseClassKind(ndkUnary, base);
      case ndkTypeExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkTypeIntersectionExpression:
        return getIsBaseClassKind(ndkTypeExpression, base);
      case ndkTypeUnionExpression:
        return getIsBaseClassKind(ndkTypeExpression, base);
      case ndkUnary:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkWildcardExpression:
        return getIsBaseClassKind(ndkTypeExpression, base);
      case ndkExports:
        return getIsBaseClassKind(ndkModuleDirective, base);
      case ndkModuleDirective:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkOpens:
        return getIsBaseClassKind(ndkModuleDirective, base);
      case ndkProvides:
        return getIsBaseClassKind(ndkModuleDirective, base);
      case ndkRequires:
        return getIsBaseClassKind(ndkModuleDirective, base);
      case ndkUses:
        return getIsBaseClassKind(ndkModuleDirective, base);
      case ndkAssert:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkBasicFor:
        return getIsBaseClassKind(ndkFor, base);
      case ndkBlock:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkBreak:
        return getIsBaseClassKind(ndkJump, base);
      case ndkCase:
        return getIsBaseClassKind(ndkSwitchLabel, base);
      case ndkContinue:
        return getIsBaseClassKind(ndkJump, base);
      case ndkDefault:
        return getIsBaseClassKind(ndkSwitchLabel, base);
      case ndkDo:
        return getIsBaseClassKind(ndkIteration, base);
      case ndkEmpty:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkEnhancedFor:
        return getIsBaseClassKind(ndkFor, base);
      case ndkExpressionStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkFor:
        return getIsBaseClassKind(ndkIteration, base);
      case ndkHandler:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkIf:
        return getIsBaseClassKind(ndkSelection, base);
      case ndkIteration:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkJump:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkLabeledStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkReturn:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkSelection:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkStatement:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkSwitch:
        return getIsBaseClassKind(ndkSelection, base);
      case ndkSwitchLabel:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkSynchronized:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkThrow:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkTry:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkWhile:
        return getIsBaseClassKind(ndkIteration, base);
      case ndkAnnotatedElement:
        return getIsBaseClassKind(ndkBase, base);
      case ndkAnnotationType:
        return getIsBaseClassKind(ndkTypeDeclaration, base);
      case ndkAnnotationTypeElement:
        return getIsBaseClassKind(ndkMethodDeclaration, base);
      case ndkAnonymousClass:
        return getIsBaseClassKind(ndkClassDeclaration, base);
      case ndkClass:
        return getIsBaseClassKind(ndkClassDeclaration, base);
      case ndkClassDeclaration:
        return getIsBaseClassKind(ndkTypeDeclaration, base);
      case ndkClassGeneric:
        return getIsBaseClassKind(ndkClassDeclaration, base) ||
          getIsBaseClassKind(ndkGenericDeclaration, base);
      case ndkCompilationUnit:
        return getIsBaseClassKind(ndkPositionedWithoutComment, base) ||
          getIsBaseClassKind(ndkCommentable, base);
      case ndkDeclaration:
        return getIsBaseClassKind(ndkMember, base) ||
          getIsBaseClassKind(ndkStatement, base);
      case ndkEnum:
        return getIsBaseClassKind(ndkTypeDeclaration, base);
      case ndkEnumConstant:
        return getIsBaseClassKind(ndkVariableDeclaration, base);
      case ndkGenericDeclaration:
        return getIsBaseClassKind(ndkBase, base);
      case ndkImport:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkInitializerBlock:
        return getIsBaseClassKind(ndkDeclaration, base);
      case ndkInstanceInitializerBlock:
        return getIsBaseClassKind(ndkInitializerBlock, base);
      case ndkInterface:
        return getIsBaseClassKind(ndkInterfaceDeclaration, base);
      case ndkInterfaceDeclaration:
        return getIsBaseClassKind(ndkTypeDeclaration, base);
      case ndkInterfaceGeneric:
        return getIsBaseClassKind(ndkInterfaceDeclaration, base) ||
          getIsBaseClassKind(ndkGenericDeclaration, base);
      case ndkMember:
        return getIsBaseClassKind(ndkCommentable, base) ||
          getIsBaseClassKind(ndkAnnotatedElement, base);
      case ndkMethod:
        return getIsBaseClassKind(ndkNormalMethod, base);
      case ndkMethodDeclaration:
        return getIsBaseClassKind(ndkNamedDeclaration, base);
      case ndkMethodGeneric:
        return getIsBaseClassKind(ndkNormalMethod, base) ||
          getIsBaseClassKind(ndkGenericDeclaration, base);
      case ndkModule:
        return getIsBaseClassKind(ndkNamed, base);
      case ndkModuleDeclaration:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkNamedDeclaration:
        return getIsBaseClassKind(ndkDeclaration, base) ||
          getIsBaseClassKind(ndkNamed, base);
      case ndkNormalMethod:
        return getIsBaseClassKind(ndkMethodDeclaration, base);
      case ndkPackage:
        return getIsBaseClassKind(ndkNamed, base) ||
          getIsBaseClassKind(ndkScope, base);
      case ndkPackageDeclaration:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkParameter:
        return getIsBaseClassKind(ndkVariableDeclaration, base);
      case ndkScope:
        return getIsBaseClassKind(ndkMember, base);
      case ndkStaticInitializerBlock:
        return getIsBaseClassKind(ndkInitializerBlock, base);
      case ndkTypeDeclaration:
        return getIsBaseClassKind(ndkNamedDeclaration, base) ||
          getIsBaseClassKind(ndkScope, base);
      case ndkTypeParameter:
        return getIsBaseClassKind(ndkPositioned, base) ||
          getIsBaseClassKind(ndkNamed, base);
      case ndkVariable:
        return getIsBaseClassKind(ndkVariableDeclaration, base);
      case ndkVariableDeclaration:
        return getIsBaseClassKind(ndkNamedDeclaration, base);
      case ndkArrayType:
        return getIsBaseClassKind(ndkType, base);
      case ndkBooleanType:
        return getIsBaseClassKind(ndkPrimitiveType, base);
      case ndkBoundedWildcardType:
        return getIsBaseClassKind(ndkWildcardType, base);
      case ndkByteType:
        return getIsBaseClassKind(ndkPrimitiveType, base);
      case ndkCharType:
        return getIsBaseClassKind(ndkPrimitiveType, base);
      case ndkClassType:
        return getIsBaseClassKind(ndkScopedType, base);
      case ndkDoubleType:
        return getIsBaseClassKind(ndkPrimitiveType, base);
      case ndkErrorType:
        return getIsBaseClassKind(ndkType, base);
      case ndkFloatType:
        return getIsBaseClassKind(ndkPrimitiveType, base);
      case ndkIntType:
        return getIsBaseClassKind(ndkPrimitiveType, base);
      case ndkIntersectionType:
        return getIsBaseClassKind(ndkType, base);
      case ndkLongType:
        return getIsBaseClassKind(ndkPrimitiveType, base);
      case ndkLowerBoundedWildcardType:
        return getIsBaseClassKind(ndkBoundedWildcardType, base);
      case ndkMethodType:
        return getIsBaseClassKind(ndkType, base);
      case ndkModuleType:
        return getIsBaseClassKind(ndkType, base);
      case ndkNoType:
        return getIsBaseClassKind(ndkType, base);
      case ndkNullType:
        return getIsBaseClassKind(ndkType, base);
      case ndkPackageType:
        return getIsBaseClassKind(ndkType, base);
      case ndkParameterizedType:
        return getIsBaseClassKind(ndkScopedType, base);
      case ndkPrimitiveType:
        return getIsBaseClassKind(ndkType, base);
      case ndkScopedType:
        return getIsBaseClassKind(ndkType, base);
      case ndkShortType:
        return getIsBaseClassKind(ndkPrimitiveType, base);
      case ndkType:
        return getIsBaseClassKind(ndkBase, base);
      case ndkTypeVariable:
        return getIsBaseClassKind(ndkType, base);
      case ndkUnboundedWildcardType:
        return getIsBaseClassKind(ndkWildcardType, base);
      case ndkUnionType:
        return getIsBaseClassKind(ndkType, base);
      case ndkUpperBoundedWildcardType:
        return getIsBaseClassKind(ndkBoundedWildcardType, base);
      case ndkVoidType:
        return getIsBaseClassKind(ndkPrimitiveType, base);
      case ndkWildcardType:
        return getIsBaseClassKind(ndkType, base);
      default:
        return false;
  }
  return false;
}

const std::string toString(AccessibilityKind kind) {
  switch (kind) {
    case ackNone: return "ackNone";
    case ackPublic: return "ackPublic";
    case ackProtected: return "ackProtected";
    case ackPrivate: return "ackPrivate";
    default: throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(AssignmentOperatorKind kind) {
  switch (kind) {
    case askAssign: return "askAssign";
    case askPlusAssign: return "askPlusAssign";
    case askMinusAssign: return "askMinusAssign";
    case askTimesAssign: return "askTimesAssign";
    case askDivideAssign: return "askDivideAssign";
    case askRemainderAssign: return "askRemainderAssign";
    case askAndAssign: return "askAndAssign";
    case askOrAssign: return "askOrAssign";
    case askXorAssign: return "askXorAssign";
    case askLeftShiftAssign: return "askLeftShiftAssign";
    case askSignedRightShiftAssign: return "askSignedRightShiftAssign";
    case askUnsignedRightShiftAssign: return "askUnsignedRightShiftAssign";
    default: throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(InfixOperatorKind kind) {
  switch (kind) {
    case iokPlus: return "iokPlus";
    case iokMinus: return "iokMinus";
    case iokTimes: return "iokTimes";
    case iokDivide: return "iokDivide";
    case iokRemainder: return "iokRemainder";
    case iokLeftShift: return "iokLeftShift";
    case iokSignedRightShift: return "iokSignedRightShift";
    case iokUnsignedRightShift: return "iokUnsignedRightShift";
    case iokBitwiseAndLogicalAnd: return "iokBitwiseAndLogicalAnd";
    case iokBitwiseAndLogicalOr: return "iokBitwiseAndLogicalOr";
    case iokBitwiseAndLogicalXor: return "iokBitwiseAndLogicalXor";
    case iokLessThan: return "iokLessThan";
    case iokGreaterThan: return "iokGreaterThan";
    case iokLessThanOrEqualTo: return "iokLessThanOrEqualTo";
    case iokGreaterThanOrEqualTo: return "iokGreaterThanOrEqualTo";
    case iokEqualTo: return "iokEqualTo";
    case iokNotEqualTo: return "iokNotEqualTo";
    case iokConditionalAnd: return "iokConditionalAnd";
    case iokConditionalOr: return "iokConditionalOr";
    default: throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(LambdaBodyKind kind) {
  switch (kind) {
    case lbkExpression: return "lbkExpression";
    case lbkStatement: return "lbkStatement";
    default: throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(LambdaParameterKind kind) {
  switch (kind) {
    case lpkImplicit: return "lpkImplicit";
    case lpkExplicit: return "lpkExplicit";
    default: throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(MemberReferenceKind kind) {
  switch (kind) {
    case mrkSuper: return "mrkSuper";
    case mrkUnbound: return "mrkUnbound";
    case mrkStatic: return "mrkStatic";
    case mrkBound: return "mrkBound";
    case mrkImplicitInner: return "mrkImplicitInner";
    case mrkToplevel: return "mrkToplevel";
    case mrkArrayCtor: return "mrkArrayCtor";
    default: throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(MemberReferenceModeKind kind) {
  switch (kind) {
    case mrmkInvoke: return "mrmkInvoke";
    case mrmkNew: return "mrmkNew";
    default: throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(MemberReferenceOverloadKind kind) {
  switch (kind) {
    case mrokOverloaded: return "mrokOverloaded";
    case mrokUnoverloaded: return "mrokUnoverloaded";
    default: throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(MethodKind kind) {
  switch (kind) {
    case mekNormal: return "mekNormal";
    case mekConstructor: return "mekConstructor";
    case mekGeneratedDefaultConstructor: return "mekGeneratedDefaultConstructor";
    case mekGeneratedAnonymousClassConstructor: return "mekGeneratedAnonymousClassConstructor";
    default: throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(ModuleKind kind) {
  switch (kind) {
    case mkOpen: return "mkOpen";
    case mkStrong: return "mkStrong";
    default: throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(PolyExpressionKind kind) {
  switch (kind) {
    case pekStandalone: return "pekStandalone";
    case pekPoly: return "pekPoly";
    default: throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(PostfixOperatorKind kind) {
  switch (kind) {
    case pookIncrement: return "pookIncrement";
    case pookDecrement: return "pookDecrement";
    default: throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(PrefixOperatorKind kind) {
  switch (kind) {
    case peokIncrement: return "peokIncrement";
    case peokDecrement: return "peokDecrement";
    case peokPlus: return "peokPlus";
    case peokMinus: return "peokMinus";
    case peokComplement: return "peokComplement";
    case peokNot: return "peokNot";
    default: throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(PrimitiveTypeKind kind) {
  switch (kind) {
    case ptkVoid: return "ptkVoid";
    case ptkBoolean: return "ptkBoolean";
    case ptkChar: return "ptkChar";
    case ptkByte: return "ptkByte";
    case ptkShort: return "ptkShort";
    case ptkInt: return "ptkInt";
    case ptkLong: return "ptkLong";
    case ptkFloat: return "ptkFloat";
    case ptkDouble: return "ptkDouble";
    default: throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(TypeBoundKind kind) {
  switch (kind) {
    case tbkWildcard: return "tbkWildcard";
    case tbkExtends: return "tbkExtends";
    case tbkSuper: return "tbkSuper";
    default: throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(NodeKind kind) {
  switch (kind) {
    case ndkBase: return "ndkBase";
    case ndkBlockComment: return "ndkBlockComment";
    case ndkComment: return "ndkComment";
    case ndkCommentable: return "ndkCommentable";
    case ndkJavadocComment: return "ndkJavadocComment";
    case ndkLineComment: return "ndkLineComment";
    case ndkNamed: return "ndkNamed";
    case ndkNonJavadocComment: return "ndkNonJavadocComment";
    case ndkPositioned: return "ndkPositioned";
    case ndkPositionedWithoutComment: return "ndkPositionedWithoutComment";
    case ndkAnnotatedTypeExpression: return "ndkAnnotatedTypeExpression";
    case ndkAnnotation: return "ndkAnnotation";
    case ndkArrayAccess: return "ndkArrayAccess";
    case ndkArrayTypeExpression: return "ndkArrayTypeExpression";
    case ndkAssignment: return "ndkAssignment";
    case ndkBinary: return "ndkBinary";
    case ndkBooleanLiteral: return "ndkBooleanLiteral";
    case ndkCharacterLiteral: return "ndkCharacterLiteral";
    case ndkClassLiteral: return "ndkClassLiteral";
    case ndkConditional: return "ndkConditional";
    case ndkDoubleLiteral: return "ndkDoubleLiteral";
    case ndkErroneous: return "ndkErroneous";
    case ndkErroneousTypeExpression: return "ndkErroneousTypeExpression";
    case ndkExpression: return "ndkExpression";
    case ndkExternalTypeExpression: return "ndkExternalTypeExpression";
    case ndkFieldAccess: return "ndkFieldAccess";
    case ndkFloatLiteral: return "ndkFloatLiteral";
    case ndkFunctionalExpression: return "ndkFunctionalExpression";
    case ndkIdentifier: return "ndkIdentifier";
    case ndkInfixExpression: return "ndkInfixExpression";
    case ndkInstanceOf: return "ndkInstanceOf";
    case ndkIntegerLiteral: return "ndkIntegerLiteral";
    case ndkLambda: return "ndkLambda";
    case ndkLiteral: return "ndkLiteral";
    case ndkLongLiteral: return "ndkLongLiteral";
    case ndkMarkerAnnotation: return "ndkMarkerAnnotation";
    case ndkMemberReference: return "ndkMemberReference";
    case ndkMethodInvocation: return "ndkMethodInvocation";
    case ndkNewArray: return "ndkNewArray";
    case ndkNewClass: return "ndkNewClass";
    case ndkNormalAnnotation: return "ndkNormalAnnotation";
    case ndkNullLiteral: return "ndkNullLiteral";
    case ndkNumberLiteral: return "ndkNumberLiteral";
    case ndkParenthesizedExpression: return "ndkParenthesizedExpression";
    case ndkPolyExpression: return "ndkPolyExpression";
    case ndkPostfixExpression: return "ndkPostfixExpression";
    case ndkPrefixExpression: return "ndkPrefixExpression";
    case ndkPrimitiveTypeExpression: return "ndkPrimitiveTypeExpression";
    case ndkQualifiedTypeExpression: return "ndkQualifiedTypeExpression";
    case ndkSimpleTypeExpression: return "ndkSimpleTypeExpression";
    case ndkSingleElementAnnotation: return "ndkSingleElementAnnotation";
    case ndkStringLiteral: return "ndkStringLiteral";
    case ndkSuper: return "ndkSuper";
    case ndkThis: return "ndkThis";
    case ndkTypeApplyExpression: return "ndkTypeApplyExpression";
    case ndkTypeCast: return "ndkTypeCast";
    case ndkTypeExpression: return "ndkTypeExpression";
    case ndkTypeIntersectionExpression: return "ndkTypeIntersectionExpression";
    case ndkTypeUnionExpression: return "ndkTypeUnionExpression";
    case ndkUnary: return "ndkUnary";
    case ndkWildcardExpression: return "ndkWildcardExpression";
    case ndkExports: return "ndkExports";
    case ndkModuleDirective: return "ndkModuleDirective";
    case ndkOpens: return "ndkOpens";
    case ndkProvides: return "ndkProvides";
    case ndkRequires: return "ndkRequires";
    case ndkUses: return "ndkUses";
    case ndkAssert: return "ndkAssert";
    case ndkBasicFor: return "ndkBasicFor";
    case ndkBlock: return "ndkBlock";
    case ndkBreak: return "ndkBreak";
    case ndkCase: return "ndkCase";
    case ndkContinue: return "ndkContinue";
    case ndkDefault: return "ndkDefault";
    case ndkDo: return "ndkDo";
    case ndkEmpty: return "ndkEmpty";
    case ndkEnhancedFor: return "ndkEnhancedFor";
    case ndkExpressionStatement: return "ndkExpressionStatement";
    case ndkFor: return "ndkFor";
    case ndkHandler: return "ndkHandler";
    case ndkIf: return "ndkIf";
    case ndkIteration: return "ndkIteration";
    case ndkJump: return "ndkJump";
    case ndkLabeledStatement: return "ndkLabeledStatement";
    case ndkReturn: return "ndkReturn";
    case ndkSelection: return "ndkSelection";
    case ndkStatement: return "ndkStatement";
    case ndkSwitch: return "ndkSwitch";
    case ndkSwitchLabel: return "ndkSwitchLabel";
    case ndkSynchronized: return "ndkSynchronized";
    case ndkThrow: return "ndkThrow";
    case ndkTry: return "ndkTry";
    case ndkWhile: return "ndkWhile";
    case ndkAnnotatedElement: return "ndkAnnotatedElement";
    case ndkAnnotationType: return "ndkAnnotationType";
    case ndkAnnotationTypeElement: return "ndkAnnotationTypeElement";
    case ndkAnonymousClass: return "ndkAnonymousClass";
    case ndkClass: return "ndkClass";
    case ndkClassDeclaration: return "ndkClassDeclaration";
    case ndkClassGeneric: return "ndkClassGeneric";
    case ndkCompilationUnit: return "ndkCompilationUnit";
    case ndkDeclaration: return "ndkDeclaration";
    case ndkEnum: return "ndkEnum";
    case ndkEnumConstant: return "ndkEnumConstant";
    case ndkGenericDeclaration: return "ndkGenericDeclaration";
    case ndkImport: return "ndkImport";
    case ndkInitializerBlock: return "ndkInitializerBlock";
    case ndkInstanceInitializerBlock: return "ndkInstanceInitializerBlock";
    case ndkInterface: return "ndkInterface";
    case ndkInterfaceDeclaration: return "ndkInterfaceDeclaration";
    case ndkInterfaceGeneric: return "ndkInterfaceGeneric";
    case ndkMember: return "ndkMember";
    case ndkMethod: return "ndkMethod";
    case ndkMethodDeclaration: return "ndkMethodDeclaration";
    case ndkMethodGeneric: return "ndkMethodGeneric";
    case ndkModule: return "ndkModule";
    case ndkModuleDeclaration: return "ndkModuleDeclaration";
    case ndkNamedDeclaration: return "ndkNamedDeclaration";
    case ndkNormalMethod: return "ndkNormalMethod";
    case ndkPackage: return "ndkPackage";
    case ndkPackageDeclaration: return "ndkPackageDeclaration";
    case ndkParameter: return "ndkParameter";
    case ndkScope: return "ndkScope";
    case ndkStaticInitializerBlock: return "ndkStaticInitializerBlock";
    case ndkTypeDeclaration: return "ndkTypeDeclaration";
    case ndkTypeParameter: return "ndkTypeParameter";
    case ndkVariable: return "ndkVariable";
    case ndkVariableDeclaration: return "ndkVariableDeclaration";
    case ndkArrayType: return "ndkArrayType";
    case ndkBooleanType: return "ndkBooleanType";
    case ndkBoundedWildcardType: return "ndkBoundedWildcardType";
    case ndkByteType: return "ndkByteType";
    case ndkCharType: return "ndkCharType";
    case ndkClassType: return "ndkClassType";
    case ndkDoubleType: return "ndkDoubleType";
    case ndkErrorType: return "ndkErrorType";
    case ndkFloatType: return "ndkFloatType";
    case ndkIntType: return "ndkIntType";
    case ndkIntersectionType: return "ndkIntersectionType";
    case ndkLongType: return "ndkLongType";
    case ndkLowerBoundedWildcardType: return "ndkLowerBoundedWildcardType";
    case ndkMethodType: return "ndkMethodType";
    case ndkModuleType: return "ndkModuleType";
    case ndkNoType: return "ndkNoType";
    case ndkNullType: return "ndkNullType";
    case ndkPackageType: return "ndkPackageType";
    case ndkParameterizedType: return "ndkParameterizedType";
    case ndkPrimitiveType: return "ndkPrimitiveType";
    case ndkScopedType: return "ndkScopedType";
    case ndkShortType: return "ndkShortType";
    case ndkType: return "ndkType";
    case ndkTypeVariable: return "ndkTypeVariable";
    case ndkUnboundedWildcardType: return "ndkUnboundedWildcardType";
    case ndkUnionType: return "ndkUnionType";
    case ndkUpperBoundedWildcardType: return "ndkUpperBoundedWildcardType";
    case ndkVoidType: return "ndkVoidType";
    case ndkWildcardType: return "ndkWildcardType";
    default: throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(EdgeKind kind) {
  switch (kind) {
    case edkCommentable_Comments: return "edkCommentable_Comments";
    case edkAnnotatedTypeExpression_HasAnnotations: return "edkAnnotatedTypeExpression_HasAnnotations";
    case edkAnnotatedTypeExpression_HasUnderlyingType: return "edkAnnotatedTypeExpression_HasUnderlyingType";
    case edkAnnotation_HasAnnotationName: return "edkAnnotation_HasAnnotationName";
    case edkArrayTypeExpression_HasComponentType: return "edkArrayTypeExpression_HasComponentType";
    case edkBinary_HasLeftOperand: return "edkBinary_HasLeftOperand";
    case edkBinary_HasRightOperand: return "edkBinary_HasRightOperand";
    case edkClassLiteral_HasComponentType: return "edkClassLiteral_HasComponentType";
    case edkConditional_HasCondition: return "edkConditional_HasCondition";
    case edkConditional_HasTrueExpression: return "edkConditional_HasTrueExpression";
    case edkConditional_HasFalseExpression: return "edkConditional_HasFalseExpression";
    case edkErroneous_HasErrors: return "edkErroneous_HasErrors";
    case edkErroneousTypeExpression_HasErrors: return "edkErroneousTypeExpression_HasErrors";
    case edkExpression_Type: return "edkExpression_Type";
    case edkFunctionalExpression_Target: return "edkFunctionalExpression_Target";
    case edkIdentifier_RefersTo: return "edkIdentifier_RefersTo";
    case edkInstanceOf_HasTypeOperand: return "edkInstanceOf_HasTypeOperand";
    case edkLambda_HasParameters: return "edkLambda_HasParameters";
    case edkLambda_HasBody: return "edkLambda_HasBody";
    case edkMemberReference_HasQualifierExpression: return "edkMemberReference_HasQualifierExpression";
    case edkMemberReference_HasTypeArguments: return "edkMemberReference_HasTypeArguments";
    case edkMemberReference_ReferredMethod: return "edkMemberReference_ReferredMethod";
    case edkMethodInvocation_HasTypeArguments: return "edkMethodInvocation_HasTypeArguments";
    case edkMethodInvocation_HasArguments: return "edkMethodInvocation_HasArguments";
    case edkMethodInvocation_Invokes: return "edkMethodInvocation_Invokes";
    case edkNewArray_HasComponentType: return "edkNewArray_HasComponentType";
    case edkNewArray_HasDimensions: return "edkNewArray_HasDimensions";
    case edkNewArray_HasInitializers: return "edkNewArray_HasInitializers";
    case edkNewClass_HasEnclosingExpression: return "edkNewClass_HasEnclosingExpression";
    case edkNewClass_HasTypeArguments: return "edkNewClass_HasTypeArguments";
    case edkNewClass_HasTypeName: return "edkNewClass_HasTypeName";
    case edkNewClass_HasArguments: return "edkNewClass_HasArguments";
    case edkNewClass_HasAnonymousClass: return "edkNewClass_HasAnonymousClass";
    case edkNewClass_Constructor: return "edkNewClass_Constructor";
    case edkNormalAnnotation_HasArguments: return "edkNormalAnnotation_HasArguments";
    case edkQualifiedTypeExpression_HasQualifierType: return "edkQualifiedTypeExpression_HasQualifierType";
    case edkQualifiedTypeExpression_HasSimpleType: return "edkQualifiedTypeExpression_HasSimpleType";
    case edkSingleElementAnnotation_HasArgument: return "edkSingleElementAnnotation_HasArgument";
    case edkTypeApplyExpression_HasRawType: return "edkTypeApplyExpression_HasRawType";
    case edkTypeApplyExpression_HasTypeArguments: return "edkTypeApplyExpression_HasTypeArguments";
    case edkTypeCast_HasTypeOperand: return "edkTypeCast_HasTypeOperand";
    case edkTypeIntersectionExpression_HasBounds: return "edkTypeIntersectionExpression_HasBounds";
    case edkTypeUnionExpression_HasAlternatives: return "edkTypeUnionExpression_HasAlternatives";
    case edkUnary_HasOperand: return "edkUnary_HasOperand";
    case edkWildcardExpression_HasBound: return "edkWildcardExpression_HasBound";
    case edkExports_HasPackageName: return "edkExports_HasPackageName";
    case edkExports_HasModuleNames: return "edkExports_HasModuleNames";
    case edkOpens_HasPackageName: return "edkOpens_HasPackageName";
    case edkOpens_HasModuleNames: return "edkOpens_HasModuleNames";
    case edkProvides_HasServiceName: return "edkProvides_HasServiceName";
    case edkProvides_HasImplementationNames: return "edkProvides_HasImplementationNames";
    case edkRequires_HasModuleName: return "edkRequires_HasModuleName";
    case edkUses_HasServiceName: return "edkUses_HasServiceName";
    case edkAssert_HasCondition: return "edkAssert_HasCondition";
    case edkAssert_HasDetail: return "edkAssert_HasDetail";
    case edkBasicFor_HasInitializers: return "edkBasicFor_HasInitializers";
    case edkBasicFor_HasCondition: return "edkBasicFor_HasCondition";
    case edkBasicFor_HasUpdates: return "edkBasicFor_HasUpdates";
    case edkBlock_HasStatements: return "edkBlock_HasStatements";
    case edkCase_HasExpression: return "edkCase_HasExpression";
    case edkDo_HasCondition: return "edkDo_HasCondition";
    case edkEnhancedFor_HasParameter: return "edkEnhancedFor_HasParameter";
    case edkEnhancedFor_HasExpression: return "edkEnhancedFor_HasExpression";
    case edkExpressionStatement_HasExpression: return "edkExpressionStatement_HasExpression";
    case edkHandler_HasParameter: return "edkHandler_HasParameter";
    case edkHandler_HasBlock: return "edkHandler_HasBlock";
    case edkIf_HasSubstatement: return "edkIf_HasSubstatement";
    case edkIf_HasFalseSubstatement: return "edkIf_HasFalseSubstatement";
    case edkIteration_HasSubstatement: return "edkIteration_HasSubstatement";
    case edkJump_Target: return "edkJump_Target";
    case edkLabeledStatement_HasStatement: return "edkLabeledStatement_HasStatement";
    case edkReturn_HasExpression: return "edkReturn_HasExpression";
    case edkSelection_HasCondition: return "edkSelection_HasCondition";
    case edkSwitch_HasCases: return "edkSwitch_HasCases";
    case edkSwitchLabel_HasStatements: return "edkSwitchLabel_HasStatements";
    case edkSynchronized_HasLock: return "edkSynchronized_HasLock";
    case edkSynchronized_HasBlock: return "edkSynchronized_HasBlock";
    case edkThrow_HasExpression: return "edkThrow_HasExpression";
    case edkTry_HasResources: return "edkTry_HasResources";
    case edkTry_HasBlock: return "edkTry_HasBlock";
    case edkTry_HasHandlers: return "edkTry_HasHandlers";
    case edkTry_HasFinallyBlock: return "edkTry_HasFinallyBlock";
    case edkWhile_HasCondition: return "edkWhile_HasCondition";
    case edkAnnotatedElement_HasAnnotations: return "edkAnnotatedElement_HasAnnotations";
    case edkAnnotationTypeElement_HasDefaultValue: return "edkAnnotationTypeElement_HasDefaultValue";
    case edkCompilationUnit_HasPackageDeclaration: return "edkCompilationUnit_HasPackageDeclaration";
    case edkCompilationUnit_HasImports: return "edkCompilationUnit_HasImports";
    case edkCompilationUnit_HasOthers: return "edkCompilationUnit_HasOthers";
    case edkCompilationUnit_HasModuleDeclaration: return "edkCompilationUnit_HasModuleDeclaration";
    case edkCompilationUnit_TypeDeclarations: return "edkCompilationUnit_TypeDeclarations";
    case edkCompilationUnit_IsInModule: return "edkCompilationUnit_IsInModule";
    case edkEnumConstant_HasNewClass: return "edkEnumConstant_HasNewClass";
    case edkGenericDeclaration_HasTypeParameters: return "edkGenericDeclaration_HasTypeParameters";
    case edkImport_HasTarget: return "edkImport_HasTarget";
    case edkInitializerBlock_HasBody: return "edkInitializerBlock_HasBody";
    case edkMethodDeclaration_HasReturnType: return "edkMethodDeclaration_HasReturnType";
    case edkMethodDeclaration_MethodType: return "edkMethodDeclaration_MethodType";
    case edkMethodDeclaration_Overrides: return "edkMethodDeclaration_Overrides";
    case edkModule_Packages: return "edkModule_Packages";
    case edkModuleDeclaration_HasName: return "edkModuleDeclaration_HasName";
    case edkModuleDeclaration_HasDirectives: return "edkModuleDeclaration_HasDirectives";
    case edkModuleDeclaration_ModuleType: return "edkModuleDeclaration_ModuleType";
    case edkModuleDeclaration_RefersTo: return "edkModuleDeclaration_RefersTo";
    case edkNormalMethod_HasParameters: return "edkNormalMethod_HasParameters";
    case edkNormalMethod_HasBody: return "edkNormalMethod_HasBody";
    case edkNormalMethod_HasThrownExceptions: return "edkNormalMethod_HasThrownExceptions";
    case edkPackage_HasCompilationUnits: return "edkPackage_HasCompilationUnits";
    case edkPackage_IsInModule: return "edkPackage_IsInModule";
    case edkPackageDeclaration_HasPackageName: return "edkPackageDeclaration_HasPackageName";
    case edkPackageDeclaration_RefersTo: return "edkPackageDeclaration_RefersTo";
    case edkScope_HasMembers: return "edkScope_HasMembers";
    case edkTypeDeclaration_HasSuperClass: return "edkTypeDeclaration_HasSuperClass";
    case edkTypeDeclaration_HasSuperInterfaces: return "edkTypeDeclaration_HasSuperInterfaces";
    case edkTypeDeclaration_HasOthers: return "edkTypeDeclaration_HasOthers";
    case edkTypeDeclaration_IsInCompilationUnit: return "edkTypeDeclaration_IsInCompilationUnit";
    case edkTypeDeclaration_IsInModule: return "edkTypeDeclaration_IsInModule";
    case edkTypeParameter_HasBounds: return "edkTypeParameter_HasBounds";
    case edkVariable_HasInitialValue: return "edkVariable_HasInitialValue";
    case edkVariableDeclaration_HasType: return "edkVariableDeclaration_HasType";
    case edkArrayType_ComponentType: return "edkArrayType_ComponentType";
    case edkClassType_RefersTo: return "edkClassType_RefersTo";
    case edkIntersectionType_Bounds: return "edkIntersectionType_Bounds";
    case edkMethodType_ReturnType: return "edkMethodType_ReturnType";
    case edkMethodType_ParameterTypes: return "edkMethodType_ParameterTypes";
    case edkMethodType_ThrownTypes: return "edkMethodType_ThrownTypes";
    case edkModuleType_RefersTo: return "edkModuleType_RefersTo";
    case edkPackageType_RefersTo: return "edkPackageType_RefersTo";
    case edkParameterizedType_RawType: return "edkParameterizedType_RawType";
    case edkParameterizedType_ArgumentTypes: return "edkParameterizedType_ArgumentTypes";
    case edkScopedType_Owner: return "edkScopedType_Owner";
    case edkTypeVariable_RefersTo: return "edkTypeVariable_RefersTo";
    case edkUnionType_Alternatives: return "edkUnionType_Alternatives";
    case edkWildcardType_Bound: return "edkWildcardType_Bound";
    default: throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
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


char packageSeparator = '.';
//char packageSeparator = '/';
char subClassSeparator = '$';
char methodAndFieldSeparator = '.';
//bool storeUniqueNames = true;
// TODO egyelore ki van kapcsolva, ketfele nev lehet tobb helyen is (type erasure-os es anelkuli)
bool storeUniqueNames = false;
bool nonGenericMethodSignatures = false;

void setGenerateNonGenericSignatureForMethods(bool value) {
  nonGenericMethodSignatures = value;
}

const std::string initBlock = "<initblock>";
const std::string initBlockName = initBlock + "()";
const std::string initBlockSuffix = methodAndFieldSeparator + initBlockName;

const std::string clInit = "<clinit>";
const std::string clInitName = clInit + "()";
const std::string clInitSuffix = methodAndFieldSeparator + clInitName;

// TODO lambda name ???
const std::string lambda = "<lambda>";
const std::string lambdaName = lambda + "()";

std::string getInstanceInitBlockSuffix() { return initBlockSuffix; }

std::string getStaticInitBlockSuffix() { return clInitSuffix; }

std::string getInstanceInitBlockName() { return initBlockName; }

std::string getStaticInitBlockName() { return clInitName; }

//std::string getUniqueNameForTypeInternal(const type::Type &node, bool typeErasure);

//replace all occurence of c1 to c2 in str
void replace(std::string &str, char c1, char c2) {
  unsigned int i;
  if(c1 == c2) {
    return;
  }
  for(i=0; i<str.length(); i++) {
    if(str[i] == c1) {
      str[i] = c2;
    }
  }
}

static bool isStructuralItem(const base::Base &node) {
#if 1
  NodeKind ndk = node.getNodeKind();
  return
       ndk == ndkPackage
    || (Common::getIsMember(node) && ((ndk != ndkVariable || Common::getIsTypeDeclaration(*node.getParent())) && (ndk != ndkParameter || Common::getIsNormalMethod(*node.getParent()))))
    || ndk == ndkLambda;
#else
    if (n.getId()!=fact.getRoot()
          && n.getNodeKind()!=ndkPackage
          && (!getIsTypeDefinition(n) || (!getIsScope(fact.getRef(n.getParent())) &&
                fact.getRef(n.getParent()).getNodeKind()!=ndkEnumConst))
          && !getIsMethod(n)
          && n.getNodeKind()!=ndkAnnotationTypeElement
          && (n.getNodeKind()!=ndkVariable || !getIsTypeDefinition(fact.getRef(n.getParent())))
          && (n.getNodeKind()!=ndkEnumConst)
          && (n.getNodeKind()!=ndkParameter || !getIsMethod(fact.getRef(n.getParent())) || forcsv)
          && (n.getNodeKind()!=ndkTypeParameter || forcsv)
#endif
}

class NameGenerator {
      private:
        //base::Base *error;
        bool error ;
      private:
        std::string visitTypeExpr(const expr::TypeExpression *t, bool isLongName);
        std::string getTypeExpressionName(const expr::TypeExpression& node);
        std::string getTypeExpressionLongName(const expr::TypeExpression& node, bool first);
        std::string getTypeName(const type::Type& node, bool typeErasure);
        std::string getGenericDeclarationName(const struc::GenericDeclaration& node);
        std::string getTypeDeclarationName(const struc::TypeDeclaration& node, bool isLongName);
        std::string getNameInternal(const base::Base& node);
        std::string getLongNameInternal(const base::Base& node);

        std::string getUniqueNameForTypeInternal(const type::Type &node, bool typeErasure);

      public:
        NameGenerator() : error(false) {
        }

        std::string getUniqueNameForBase(const base::Base &node, bool qualified = true);
        std::string getUniqueNameForType(const type::Type &node);

        /**
        * \brief Get name for Base nodes.
        * \param node [in] The base node.
        * \return A name for the node.
        */
        std::string getName(const base::Base& node);
        /**
        * \brief Get long name for Base nodes.
        * \param node [in] The base node.
        * \return A name for the node.
        */
        std::string getLongName(const base::Base& node);
};

base::Base* getParent(const base::Base& node) {
  base::Base* parent = node.getParent();
  while(parent != NULL && !Common::getIsTypeDeclaration(*parent) && !Common::getIsPackage(*parent)) {
    parent = parent->getParent();
  }
  return parent;
}


std::string getUnknownName(const base::Base& node) {
  std::string name;
  if(Common::getIsAnonymousClass(node)) {
    name = "$";
  } else {
    name = ".";
  }
  name += Common::toString(node.getId()) + "#";
  return name;
}

std::string NameGenerator::getUniqueNameForBase(const base::Base &node, bool qualified /*= true*/) {
  //looking for already generated unique name
  /*Factory::UniqueNameMapType& uniqueNameMap = node.getFactory().uniqueNameMap;
  if (storeUniqueNames) {
    Factory::UniqueNameMapType::iterator it = uniqueNameMap.find(node.getId());
    if (it != uniqueNameMap.end()) {
      return it->second;
    }
  }*/

  Factory::TurnFilterOffSafely tfos(node.getFactory()); // TODO
  std::string str = "";

  if(getIsMethodDeclaration(node)) {
    const struc::MethodDeclaration &methodDeclaration = dynamic_cast<const struc::MethodDeclaration &>(node);
    if (node.getParent()) {
      str = getUniqueNameForBase(*node.getParent());
    }

    std::string methodName = "";
    if (Common::getIsNormalMethod(methodDeclaration) && dynamic_cast<const struc::NormalMethod&>(methodDeclaration).getMethodKind() != mekNormal) { // constructor
      methodName = "<init>";
    } else {
      methodName = methodDeclaration.getName();
    }
    str += methodAndFieldSeparator + methodName;

    std::string typeStr = "";

    if (methodDeclaration.getMethodType()) {
      //str += getUniqueNameForType(*methodDeclaration.getMethodType());
      //typeStr = getUniqueNameForTypeInternal(*methodDeclaration.getMethodType(), /*typeErasure =*/ nonGenericMethodSignatures);
      typeStr = getUniqueNameForTypeInternal(*methodDeclaration.getMethodType(), /*typeErasure =*/ true); // TODO pantos
    }

    if (!methodDeclaration.getMethodType() || NameGenerator::error) {
      //str += "<MissingMethodType>";

      //common::WriteMsg::write(common::WriteMsg::mlWarning, "Missing MethodType at node %u\n", node.getId());

      typeStr = "(";
      if(Common::getIsNormalMethod(methodDeclaration)) {
        const struc::NormalMethod &normalMethod = dynamic_cast<const struc::NormalMethod &>(methodDeclaration);
        ListIterator<struc::Parameter> it = normalMethod.getParametersListIteratorBegin();
        while(it != normalMethod.getParametersListIteratorEnd()) {
          typeStr += visitTypeExpr(it->getType(), true);
          ++it;
        }
      }
      typeStr += ")";
      if (Common::getIsAnnotationTypeElement(methodDeclaration) || (Common::getIsNormalMethod(methodDeclaration) && dynamic_cast<const struc::NormalMethod&>(methodDeclaration).getMethodKind() == mekNormal)) { // annotation member or non constuctor
        typeStr += visitTypeExpr(methodDeclaration.getReturnType(), true);
      } else {
        typeStr += "V";
      }
    }

    str += typeStr;

    //if (methodDeclaration.getMethodType()) {
    //  //str += getUniqueNameForType(*methodDeclaration.getMethodType());
    //  str += NameGenerator().getUniqueNameForTypeInternal(*methodDeclaration.getMethodType(), /*typeErasure =*/ nonGenericMethodSignatures);
    //} else {
    //  str += "<MissingMethodType>";
    //}
  } else if(getIsTypeDeclaration(node)) {
    str = dynamic_cast<const struc::TypeDeclaration &>(node).getBinaryName();
    //replace(str, '.', packageSeparator);
    //replace(str, '$', subClassSeparator);
    if (!qualified) {
      replace(str, '.', '/');
    }

  } else if (getIsVariableDeclaration(node) && ((node.getNodeKind() != ndkVariable || Common::getIsTypeDeclaration(*node.getParent())) && (node.getNodeKind() != ndkParameter || Common::getIsNormalMethod(*node.getParent())))) {
    str = getUniqueNameForBase(*node.getParent());
    str += methodAndFieldSeparator;
    str += dynamic_cast<const struc::VariableDeclaration &>(node).getName();

  } else if (getIsInitializerBlock(node)) { // FIXME kellene vmi rendes nev + ez a sorszamozas dolog sem az igazi
    str = getUniqueNameForBase(*node.getParent());
    str += methodAndFieldSeparator;
    if (node.getNodeKind() == ndkStaticInitializerBlock)
      str += clInit;
    else // ndkInitializerBlock
      str += initBlock;

    struc::TypeDeclaration& td = dynamic_cast<struc::TypeDeclaration&>(*node.getParent());
    unsigned int ordinal = 0;
    for (ListIterator<struc::Member> it = td.getMembersListIteratorBegin(); it != td.getMembersListIteratorEnd(); ++it) {
      if (it->getNodeKind() == node.getNodeKind())
        ++ordinal;
      if (it->getId() == node.getId())
        break;
    }
    str += "#" + Common::toString(ordinal);

  } else if (getIsLambda(node)) { // TODO vmi rendes nev ???
    str = getUniqueNameForBase(*node.getParent());
    str += methodAndFieldSeparator;
    str += lambda;
    str += "#" + Common::toString(dynamic_cast<const expr::Lambda&>(node).getPosition().getLine()); // FIXME

  } else {
    switch(node.getNodeKind()) {
    case ndkPackage:
      str = dynamic_cast<const struc::Package &>(node).getQualifiedName();
      //replace(str,'.',packageSeparator);
      break;

    default:
      base::Base *parent = node.getParent();

      //looking for a parent which have a unique name
      while (parent != NULL && !isStructuralItem(*parent)) {
        parent = parent->getParent();
      }

      if(parent == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_COMMON_EX_INVALID_NODE(node.getId(), node.getNodeKind()));
      } else {
        str = getUniqueNameForBase(*parent, qualified);
      }
      break;
    }
  }

  if(str == "") {
    base::Base *p = getParent(node);
    if(p != NULL) {
      str = getUniqueNameForBase(*p, qualified);
    }
    str += getUnknownName(node);
  }

  /*if (storeUniqueNames) {
    uniqueNameMap[node.getId()] = str;
  }*/

  return str;
}

std::string NameGenerator::getUniqueNameForType(const type::Type &node) {
  //looking for already generated unique name
  /*Factory::UniqueNameMapType& uniqueNameMap = node.getFactory().uniqueNameMap;
  if (storeUniqueNames) {
    Factory::UniqueNameMapType::iterator it = uniqueNameMap.find(node.getId());
    if (it != uniqueNameMap.end()) {
      return it->second;
    }
  }*/

  Factory::TurnFilterOffSafely tfos(node.getFactory()); // TODO

  std::string str = getUniqueNameForTypeInternal(node, false);

  /*if (storeUniqueNames) {
    uniqueNameMap[node.getId()] = str;
  }*/

  return str;
}

// TODO atnezni: JLS 4.6 Type Erasure
// TODO a kozvetlen getUniqueNameForTypeInternal hivasok miatt a cache nem mukodik
//      viszont a cache-el meg gond lehet a typeErasure-rel es nelkule keszult sztringekkel
std::string NameGenerator::getUniqueNameForTypeInternal(const type::Type &node, bool typeErasure) {
  std::string str = "";

  if(getIsBoundedWildcardType(node)) {
    if(node.getNodeKind() == ndkUpperBoundedWildcardType) {
      str = "+";
    } else {
      str = "-";
    }
    //str += getUniqueNameForType(*dynamic_cast<const type::BoundedWildcardType &>(node).getBound());
    //str += getUniqueNameForTypeInternal(*dynamic_cast<const type::BoundedWildcardType &>(node).getBound(), typeErasure);
    const type::BoundedWildcardType& boundedWcType = dynamic_cast<const type::BoundedWildcardType &>(node);
    if (boundedWcType.getBound()) {
      str += getUniqueNameForTypeInternal(*boundedWcType.getBound(), typeErasure);
    } else {
      common::WriteMsg::write(CMSG_COMMON_MISSING_EDGE, "BoundedWildcardType", node.getId(), "bound");
      str += "[MISSING_TYPE]";
      NameGenerator::error = true;
    }
  } else {
    switch(node.getNodeKind()) {
    case ndkByteType:
      str = "B";
      break;
    case ndkCharType:
      str = "C";
      break;
    case ndkDoubleType:
      str = "D";
      break;
    case ndkFloatType:
      str = "F";
      break;    
    case ndkIntType:
      str = "I";
      break;
    case ndkLongType:
      str = "J";
      break;
    case ndkShortType:
      str = "S";
      break;
    case ndkBooleanType:
      str = "Z";
      break;
    case ndkVoidType:
      str = "V";
      break;
    case ndkUnboundedWildcardType:
      str = "*";
      break;
    //not part of the specification
    case ndkNullType:
      str = "N";
      break;
    //not part of the specification
    case ndkErrorType:
      str = "E";
      NameGenerator::error=true;
      break;
    //not part of the specification
    case ndkNoType:
      str = "X";
      break;
    case ndkMethodType: {
      const type::MethodType &type = dynamic_cast<const type::MethodType &>(node);
      str = "(";
      ListIterator<type::Type> it = type.getParameterTypesListIteratorBegin();
      while(it != type.getParameterTypesListIteratorEnd()) {
        //str += getUniqueNameForType(*it);
        str += getUniqueNameForTypeInternal(*it, typeErasure);
        ++it;
      }
      //str += ")" + getUniqueNameForType(*type.getReturnType());
      //str += ")" + getUniqueNameForTypeInternal(*type.getReturnType(), typeErasure);
      str += ")";
      if (type.getReturnType()) {
        str += getUniqueNameForTypeInternal(*type.getReturnType(), typeErasure);
      } else {
        common::WriteMsg::write(CMSG_COMMON_MISSING_EDGE, "MethodType", node.getId(), "returnType");
        str += "[MISSING_TYPE]";
        NameGenerator::error = true;
      }
      break;
    }
    case ndkArrayType: {
      const type::ArrayType& arrayType = dynamic_cast<const type::ArrayType &>(node);
      str.insert(0, "[");
      //str += getUniqueNameForType(*dynamic_cast<const type::ArrayType &>(node).getComponentType());
      //str += getUniqueNameForTypeInternal(*dynamic_cast<const type::ArrayType &>(node).getComponentType(), typeErasure);
      if (arrayType.getComponentType()) {
        str += getUniqueNameForTypeInternal(*arrayType.getComponentType(), typeErasure);
      } else {
        common::WriteMsg::write(CMSG_COMMON_MISSING_EDGE, "ArrayType", node.getId(), "componentType");
        str += "[MISSING_TYPE]";
        NameGenerator::error = true;
      }
      break;
    }
    case ndkPackageType: {
      struc::Package* pkg = dynamic_cast<const type::PackageType&>(node).getRefersTo();
      if (pkg) {
        str = getUniqueNameForBase(*pkg);
      } else {
        common::WriteMsg::write(CMSG_COMMON_PACKAGETYPE_HAS_NO_REFERSTO, node.getId());
        str = "[WRONG_PACKAGETYPE]";
        NameGenerator::error = true;
      }
      break;
    }
    case ndkParameterizedType: {
      const type::ParameterizedType &parameterizedType = dynamic_cast<const type::ParameterizedType &>(node);

      //str += getUniqueNameForType(*parameterizedType.getRawType());
      str += getUniqueNameForTypeInternal(*parameterizedType.getRawType(), typeErasure);

      //for ';' at the end of ClassType name
      str.erase(str.size() - 1);

      if (!typeErasure) {
        str += "<";
        ListIterator<type::Type> it = parameterizedType.getArgumentTypesListIteratorBegin();
        while(it != parameterizedType.getArgumentTypesListIteratorEnd()) {
          //str += getUniqueNameForType(*it);
          str += getUniqueNameForTypeInternal(*it, typeErasure);
          ++it;
        }
        str += ">";
      }

      str += ";";
      break;
    }
    // TODO JAN hiba miatt hianyozhatnak keresztelek, tobbire is megcsinalni a hibakezelest
    case ndkClassType: {
      str = "L";
      struc::TypeDeclaration* td = dynamic_cast<const type::ClassType&>(node).getRefersTo();
      if (td) {
        str += getUniqueNameForBase(*td, /*qualified =*/ false);
      } else {
        common::WriteMsg::write(CMSG_COMMON_CLASSTYPE_HAS_NO_REFERSTO, node.getId());
        str += "[WRONG_CLASSTYPE]";
        NameGenerator::error = true;
      }
      str += ";";
      break;
    }
    //not part of the specification
    case ndkUnionType: {
      const type::UnionType &type = dynamic_cast<const type::UnionType &>(node);
      str = "U";
      ListIterator<type::Type> it = type.getAlternativesListIteratorBegin();
      while(it != type.getAlternativesListIteratorEnd()) {
        //str += getUniqueNameForType(*it);
        str += getUniqueNameForTypeInternal(*it, typeErasure);
        ++it;
      }
      str += ";";
      break;
    }
    case ndkTypeVariable: {
      str = "";
      if (!typeErasure) {
        str += "T";
      }
      struc::TypeParameter* tp = dynamic_cast<const type::TypeVariable &>(node).getRefersTo();
      if (tp) {
        if (!tp->getBoundsIsEmpty()) {
          //str += getUniqueNameForTypeInternal(*tp->getBoundsListIteratorBegin()->getType(), /*typeErasure =*/ true);
          const expr::TypeExpression &te = *tp->getBoundsListIteratorBegin();
          if (te.getType()) {
            str += getUniqueNameForTypeInternal(*te.getType(), /*typeErasure =*/ true);
          } else { // TODO pl linkelesnel kesobb allitodik be a keresztel
            common::WriteMsg::write(CMSG_COMMON_TYPEEXPR_HAS_NO_TYPE, te.getId(), Common::toString(te.getNodeKind()).c_str());
            //str += "[MISSING_TYPE]";
            NameGenerator::error = true;
          }
        } else {
          common::WriteMsg::write(CMSG_COMMON_TYPEVAR_HAS_NO_BOUND, tp->getId(), node.getId());
          str += tp->getName();
          NameGenerator::error = true;
        }
      } else {
        common::WriteMsg::write(CMSG_COMMON_TYPEVAR_HAS_NO_REFERSTO, node.getId());
        str += "?";
        NameGenerator::error = true;
      }
      if (!typeErasure) {
        str += ";";
      }
      break;
    }
    case ndkIntersectionType: {
      const type::IntersectionType &type = dynamic_cast<const type::IntersectionType &>(node);
      str = "I";
      ListIterator<type::Type> it = type.getBoundsListIteratorBegin();
      while(it != type.getBoundsListIteratorEnd()) {
        //str += getUniqueNameForType(*it);
        str += getUniqueNameForTypeInternal(*it, typeErasure);
        ++it;
      }
      str += ";";
      break;
    }
    default:
      NameGenerator::error = true;
      throw JavaException(COLUMBUS_LOCATION, CMSG_COMMON_EX_INVALID_NODE(node.getId(), node.getNodeKind()));
    }
  }

  if(str == "") {
    str += getUnknownName(node);
  }

  return str;
}

base::Base* getScopeOrMethodDeclarationParent(const base::Base& node) {
  Factory& fact = node.getFactory();
  if (&node == fact.getRoot())
    return NULL;

  base::Base* n = node.getParent();
  while (n) {
    if (getIsScope(*n) || getIsMethodDeclaration(*n)) {
      return n;
    }
    n = n->getParent();
  }

  return NULL;
}

std::string getUniqueStringForSorting(const base::Base& node) {
  if (node.getNodeKind() == ndkCompilationUnit)
    return dynamic_cast<const struc::CompilationUnit&>(node).getPosition().getPath();

  std::stringstream s;

  if (node.getFactory().getFilterState(node.getId()) == Filter::NotFiltered
    || (node.getParent() && node.getFactory().getFilterState(node.getParent()->getId()) == Filter::NotFiltered
        && Common::getIsNormalMethod(node) && dynamic_cast<const struc::NormalMethod&>(node).getMethodKind() == mekConstructor) // TODO JANLink bug
  ) {
    s << "F1#";
  } else {
    s << "F2#";
  }

  if (Common::getIsPositionedWithoutComment(node)) {
    const Range& r = dynamic_cast<const base::PositionedWithoutComment&>(node).getPosition();
    std::string path = r.getPath();
    if (!path.empty()) {
      s << "P2#";
      s << "{";
      s << path
        << std::setw(8) << r.getWideLine()
        << std::setw(8) << r.getWideCol()
        << std::setw(8) << r.getWideEndLine()
        << std::setw(8) << r.getWideEndCol();
      s << "}";
    } else {
      s << "P1#";
    }
  } else if (Common::getIsPackage(node)) {
    s << "P3#";
  }

  if (Common::isStructuralItem(node)) {
    s << getUniqueNameForBase(node);
  }

  return s.str();
}



std::string NameGenerator::getTypeName(const type::Type& node, bool typeErasure) {
  std::string str = "";

  if(getIsBoundedWildcardType(node)) {
    if(node.getNodeKind() == ndkUpperBoundedWildcardType) {
      str = "? extends ";
    } else {
      str = "? super ";
    }
    type::Type *t = dynamic_cast<const type::BoundedWildcardType &>(node).getBound();
    if(t) {
      str += getTypeName(*t, typeErasure);
    } else {
      NameGenerator::error = true;
    }
  } else {
    switch(node.getNodeKind()) {
    case ndkByteType:
      str = "byte";
      break;
    case ndkCharType:
      str = "char";
      break;
    case ndkDoubleType:
      str = "double";
      break;
    case ndkFloatType:
      str = "float";
      break;
    case ndkIntType:
      str = "int";
      break;
    case ndkLongType:
      str = "long";
      break;
    case ndkShortType:
      str = "short";
      break;
    case ndkBooleanType:
      str = "boolean";
      break;
    case ndkVoidType:
      str = "void";
      break;
    case ndkUnboundedWildcardType:
      str = "?";
      break;
    case ndkNullType:
      str = "null";
      break;
    case ndkErrorType:
      str = "<Error>";
      NameGenerator::error = true;
      break;
    case ndkNoType:
      str = "<NoType>";
      break;
    case ndkArrayType: {
      type::Type *t = dynamic_cast<const type::ArrayType &>(node).getComponentType();
      if(t) {
        str += getTypeName(*t, typeErasure) + "[]";
      } else {
        NameGenerator::error = true;
      }
      break;
    }
    case ndkParameterizedType: {
      const type::ParameterizedType &parameterizedType = dynamic_cast<const type::ParameterizedType &>(node);

      if (!typeErasure) {
        str += getTypeName(*parameterizedType.getRawType(), typeErasure);
        str += "<";
        ListIterator<type::Type> it = parameterizedType.getArgumentTypesListIteratorBegin();
        bool first = true;
        while(it != parameterizedType.getArgumentTypesListIteratorEnd()) {
          if(!first) {
            str += ", ";
          } else {
            first = false;
          }
          str += getTypeName(*it, typeErasure);
          ++it;
        }
        str += ">";
      }

      break;
    }
    // TODO JAN hiba miatt hianyozhatnak keresztelek, tobbire is megcsinalni a hibakezelest
    case ndkClassType: {
      struc::TypeDeclaration* td = dynamic_cast<const type::ClassType&>(node).getRefersTo();
      if (td) {
        str += td->getName();
      } else {
        common::WriteMsg::write(CMSG_COMMON_CLASSTYPE_HAS_NO_REFERSTO, node.getId());
        NameGenerator::error = true;
        str += "[WRONG_CLASSTYPE]";
      }
      break;
    }
    case ndkTypeVariable: {
      struc::TypeParameter* tp = dynamic_cast<const type::TypeVariable &>(node).getRefersTo();

      if (!typeErasure) {
        if (tp) {
          str += tp->getName();
        } else {
          str += "[WRONG_TYPEVARIABLE]";
          NameGenerator::error=true;
        }
      } else {
        if (tp) {
          if (!tp->getBoundsIsEmpty()) {
            str += getTypeName(*tp->getBoundsListIteratorBegin()->getType(), true);
          } else {
            common::WriteMsg::write(CMSG_COMMON_TYPEVAR_HAS_NO_BOUND, tp->getId(), node.getId());
            str += tp->getName();
            NameGenerator::error = true;
          }
        } else {
          common::WriteMsg::write(CMSG_COMMON_TYPEVAR_HAS_NO_REFERSTO, node.getId());
          NameGenerator::error=true;
          str += "?";
        }
      }
      break;
    }
    case ndkMethodType:
    case ndkPackageType:
    case ndkUnionType:
    case ndkIntersectionType:
    default:
      NameGenerator::error = true;
      throw JavaException(COLUMBUS_LOCATION, CMSG_COMMON_EX_INVALID_NODE(node.getId(), node.getNodeKind()));
    }
  }
  return str;
}

std::string NameGenerator::getTypeDeclarationName(const struc::TypeDeclaration& node, bool isLongName) {
  std::string name = node.getBinaryName();
  if(!isLongName) {
    size_t pos = name.find_last_of('.');
    if(pos != std::string::npos) {
      name.erase(0,pos+1);
    }
  }
  return name;
}

std::string NameGenerator::getGenericDeclarationName(const struc::GenericDeclaration& node) {
  std::string str;

  str += "<";
  ListIterator<struc::TypeParameter> it1 = node.getTypeParametersListIteratorBegin();
  bool firstTypeParam = true;
  while(it1 != node.getTypeParametersListIteratorEnd()) {
    if(!firstTypeParam) {
      str += ", ";
    } else {
      firstTypeParam = false;
    }
    bool firstBound = true;
    str += it1->getName();
    ListIterator<expr::TypeExpression> it2 = it1->getBoundsListIteratorBegin();
    while(it2 != it1->getBoundsListIteratorEnd()) {
      if(!firstBound) {
        str += " $ ";
      } else {
        str += " extends ";
        firstBound = false;
      }
      //str += getTypeName(*it2->getType(), false);
      str += visitTypeExpr(&*it2,false);
      ++it2;
    }
    ++it1;
  }
  str += ">";
  return str;
}

std::string NameGenerator::getName(const base::Base& node) {
  std::string name = getNameInternal(node);
  if(NameGenerator::error) {
    //name += "#ERROR";
  }
  return name;
}

std::string NameGenerator::getLongName(const base::Base& node) {
  std::string name = getLongNameInternal(node);
  if(NameGenerator::error) {
    //name += "#ERROR";
  }
  return name;
}


std::string NameGenerator::getTypeExpressionName(const expr::TypeExpression& node) {
  std::string str = "";
  switch(node.getNodeKind()) {
  case ndkArrayTypeExpression: {
    const expr::ArrayTypeExpression &arrayType = dynamic_cast<const expr::ArrayTypeExpression &>(node);
    str = getTypeExpressionName(*arrayType.getComponentType()) + "[]";
    break;
  }
  case ndkPrimitiveTypeExpression: {
    const expr::PrimitiveTypeExpression &primitive = dynamic_cast<const expr::PrimitiveTypeExpression &>(node);
    switch(primitive.getKind()) {
    case ptkBoolean:
      str = "boolean";
      break;
    case ptkByte:
      str = "byte";
      break;
    case ptkChar:
      str = "char";
      break;
    case ptkDouble:
      str = "double";
      break;
    case ptkFloat:
      str = "float";
      break;
    case ptkInt:
      str = "int";
      break;
    case ptkLong:
      str = "long";
      break;
    case ptkShort:
      str = "short";
      break;
    case ptkVoid:
      str = "void";
      break;
    default:
      throw JavaException(COLUMBUS_LOCATION, CMSG_COMMON_EX_INVALID_NODE(node.getId(), node.getNodeKind()));
    }
    break;
  }
  case ndkTypeApplyExpression: {
    const expr::TypeApplyExpression &typeApply = dynamic_cast<const expr::TypeApplyExpression &>(node);
    str = getTypeExpressionName(*typeApply.getRawType()) + "<";
    ListIterator<expr::TypeExpression > it = typeApply.getTypeArgumentsListIteratorBegin();
    bool first = true;
    while(it != typeApply.getTypeArgumentsListIteratorEnd()) {
      if(!first) {
        str += ", ";
      } else {
        first = false;
      }
      str += getTypeExpressionName(*it);
      ++it;
    }
    str += ">";
    break;
  }
  case ndkSimpleTypeExpression: {
    str = dynamic_cast<const expr::SimpleTypeExpression &>(node).getName();
    break;
  }
  case ndkQualifiedTypeExpression: {
    const expr::QualifiedTypeExpression &qualified = dynamic_cast<const expr::QualifiedTypeExpression &>(node);
    str = getTypeExpressionName(*qualified.getSimpleType());
    break;
  }
  case ndkErroneousTypeExpression:
    str = "[ERROR]";
    NameGenerator::error = true; // TODO kell ez ide?
    break;
  case ndkWildcardExpression: {
    const expr::WildcardExpression &wce = dynamic_cast<const expr::WildcardExpression &>(node);
    switch (wce.getKind()) {
      case tbkExtends:
        str += "? extends ";
        break;
      case tbkSuper:
        str += "? super ";
        break;
      case tbkWildcard:
      default:
        str += "?";
        break;
    }
    if (wce.getBound()) {
      str += getTypeExpressionName(*wce.getBound());
    }
    break;
  }
  case ndkExternalTypeExpression: {
    const expr::ExternalTypeExpression &external = dynamic_cast<const expr::ExternalTypeExpression &>(node);
    if (external.getType()) {
      str = getTypeName(*external.getType(), false);
    } else {
      str = "[MISSING_EXT_TYPE]";
      common::WriteMsg::write(CMSG_COMMON_TYPEEXPR_HAS_NO_TYPE, external.getId(), Common::toString(external.getNodeKind()).c_str());
      NameGenerator::error = true;
    }
    break;
  }
  case ndkAnnotatedTypeExpression: {
    const expr::AnnotatedTypeExpression &ate = dynamic_cast<const expr::AnnotatedTypeExpression &>(node);
    if (ate.getUnderlyingType() && ate.getUnderlyingType()->getType()) {
      str = getTypeName(*ate.getUnderlyingType()->getType(), false);
    } else {
      str = "[MISSING_EXT_TYPE]";
      common::WriteMsg::write(CMSG_COMMON_TYPEEXPR_HAS_NO_TYPE, ate.getId(), Common::toString(ate.getNodeKind()).c_str());
      NameGenerator::error = true;
    }
    break;
  }
  case ndkTypeIntersectionExpression: {
    const expr::TypeIntersectionExpression &tie = dynamic_cast<const expr::TypeIntersectionExpression &>(node);
    ListIterator<expr::TypeExpression > it = tie.getBoundsListIteratorBegin();
    bool first = true;
    while (it != tie.getBoundsListIteratorEnd()) {
      if (!first) {
        str += " & ";
      } else {
        first = false;
      }
      str += getTypeExpressionName(*it);
      ++it;
    }
    break;
  }
  case ndkTypeUnionExpression:
  default:
    throw JavaException(COLUMBUS_LOCATION, CMSG_COMMON_EX_INVALID_NODE(node.getId(), node.getNodeKind()));
  }
  return str;
}

std::string NameGenerator::getTypeExpressionLongName(const expr::TypeExpression& node, bool first) {
  std::string str = "";
  switch(node.getNodeKind()) {
  case ndkArrayTypeExpression: {
    const expr::ArrayTypeExpression &arrayType = dynamic_cast<const expr::ArrayTypeExpression &>(node);
    //str = "[" + getTypeExpressionName(*arrayType.getComponentType());
    str = "[" + getTypeExpressionLongName(*arrayType.getComponentType(), true); // TODO true/false ?
    break;
  }
  case ndkPrimitiveTypeExpression: {
    const expr::PrimitiveTypeExpression &primitive = dynamic_cast<const expr::PrimitiveTypeExpression &>(node);
    switch(primitive.getKind()) {
    case ptkBoolean:
      str = "Z";
      break;
    case ptkByte:
      str = "B";
      break;
    case ptkChar:
      str = "C";
      break;
    case ptkDouble:
      str = "D";
      break;
    case ptkFloat:
      str = "F";
      break;
    case ptkInt:
      str = "I";
      break;
    case ptkLong:
      str = "L";
      break;
    case ptkShort:
      str = "S";
      break;
    case ptkVoid:
      str = "V";
      break;
    default:
      throw JavaException(COLUMBUS_LOCATION, CMSG_COMMON_EX_INVALID_NODE(node.getId(), node.getNodeKind()));
    }
    break;
  }
  case ndkSimpleTypeExpression: {
    if(first) {
      str += "L";
    }
    str += dynamic_cast<const expr::SimpleTypeExpression &>(node).getName();
    if(first) {
      str += ";";
    }
    break;
  }
  case ndkQualifiedTypeExpression: {
    if(first) {
      str += "L";
    }
    const expr::QualifiedTypeExpression &qualified = dynamic_cast<const expr::QualifiedTypeExpression &>(node);
    str += getTypeExpressionLongName(*qualified.getQualifierType(), false) + "." + getTypeExpressionLongName(*qualified.getSimpleType(), false);
    if(first) {
      str += ";";
    }
    break;
  }

  case ndkTypeApplyExpression: {
    const expr::TypeApplyExpression &typeApply = dynamic_cast<const expr::TypeApplyExpression &>(node);
    //str = getTypeExpressionLongName(*typeApply.getRawType(),false);
    str = getTypeExpressionLongName(*typeApply.getRawType(), true); // TODO true/false ?
    /*+ "<";
    ListIterator<expr::TypeExpression > it = typeApply.getTypeArgumentsListIteratorBegin();
    bool first = true;
    while(it != typeApply.getTypeArgumentsListIteratorEnd()) {
      if(!first) {
        str += ",";
      } else {
        first = false;
      }
      str += getTypeExpressionName(*it);
      ++it;
    }
    str += ">";*/
    break;
  }
  case ndkErroneousTypeExpression:
    str = "[ERROR]";
    NameGenerator::error = true; // TODO kell ez ide?
    break;
  case ndkExternalTypeExpression: {
    const expr::ExternalTypeExpression &external = dynamic_cast<const expr::ExternalTypeExpression &>(node);
    if (external.getType()) {
      str = getUniqueNameForTypeInternal(*external.getType(), /*typeErasure =*/ true);
    } else {
      str = "[MISSING_EXT_TYPE]";
      common::WriteMsg::write(CMSG_COMMON_TYPEEXPR_HAS_NO_TYPE, external.getId(), Common::toString(external.getNodeKind()).c_str());
      NameGenerator::error = true;
    }
    //str = visitTypeExpr(dynamic_cast<const expr::ExternalTypeExpression&>(node).getType(), true);
    break;
  }
  case ndkAnnotatedTypeExpression: {
  const expr::AnnotatedTypeExpression &ate = dynamic_cast<const expr::AnnotatedTypeExpression &>(node);
    str = getTypeExpressionLongName(*ate.getUnderlyingType(), true);
    break;
  }
  case ndkTypeUnionExpression:
  case ndkWildcardExpression:
  default:
    throw JavaException(COLUMBUS_LOCATION, CMSG_COMMON_EX_INVALID_NODE(node.getId(), node.getNodeKind()));
  }
  return str;
}

std::string NameGenerator::visitTypeExpr(const expr::TypeExpression *t, bool isLongName) {
  std::string name = "";
  if(!t) {
    name = "[MISSING_TYPE]";
    NameGenerator::error = true;
  } else {
    if(t->getType()) {
      if(!isLongName) {
        name = getTypeName(*t->getType(), false);
      } else {
        //name = getUniqueNameForType(*t->getType());
        name = getUniqueNameForTypeInternal(*t->getType(), /*typeErasure =*/ true);
      }
    } else {
      NameGenerator::error = true;
    }
    if(NameGenerator::error) {
      if(isLongName) {
        name = getTypeExpressionLongName(*t, true);
      } else {
        name = getTypeExpressionName(*t);
      }
    }
  }
  return name;
}

std::string NameGenerator::getNameInternal(const base::Base& node) {
  Factory::TurnFilterOffSafely tfos(node.getFactory());
  std::string name = "";
  if(Common::getIsTypeDeclaration(node)) {
    const struc::TypeDeclaration &td = dynamic_cast<const struc::TypeDeclaration&>(node);
    if(getIsGenericDeclaration(node)) {
      name = getTypeDeclarationName(dynamic_cast<const struc::TypeDeclaration&>(td), false) + 
        getGenericDeclarationName(dynamic_cast<const struc::GenericDeclaration&>(td));
    } else {
      name = getTypeDeclarationName(td, false);
    }
  } else if(Common::getIsMethodDeclaration(node)) {
    const struc::MethodDeclaration &md = dynamic_cast<const struc::MethodDeclaration&>(node);
    if(Common::getIsGenericDeclaration(md)) {
      name = getGenericDeclarationName(dynamic_cast<const struc::GenericDeclaration&>(md)) + " ";
    }
    if (Common::getIsAnnotationTypeElement(md) || (Common::getIsNormalMethod(md) && dynamic_cast<const struc::NormalMethod&>(md).getMethodKind() == mekNormal)) { // annotation member or non constuctor
      name += visitTypeExpr(md.getReturnType(), false) + " ";
    }
    std::string methodName = md.getName();
    if (methodName.empty() && Common::getIsNormalMethod(md) && dynamic_cast<const struc::NormalMethod&>(md).getMethodKind() != mekNormal) { // anonymous constructor
      if (md.getParent() && Common::getIsTypeDeclaration(*md.getParent())) {
        std::string className = dynamic_cast<const struc::TypeDeclaration&>(*md.getParent()).getBinaryName();
        size_t pos = className.find_last_of('$');
        if (pos != std::string::npos) {
          methodName = className.substr(pos);
        }
      }
    }
    name += methodName;
    name += "(";
    if(Common::getIsNormalMethod(md)) {
      const struc::NormalMethod &normalMethod = dynamic_cast<const struc::NormalMethod &>(md);
      ListIterator<struc::Parameter> it = normalMethod.getParametersListIteratorBegin();
      bool first = true;
      while(it != normalMethod.getParametersListIteratorEnd()) {
        if(!first) {
          name += ", ";
        } else {
          first = false;
        }
        name += visitTypeExpr(it->getType(), false);
        name += " " + it->getName();
        ++it;
      }
    }
    name += ")";
  } else if(Common::getIsVariableDeclaration(node)) {
    const struc::VariableDeclaration &vd = dynamic_cast<const struc::VariableDeclaration&>(node);
    name = vd.getName();
  } else if(Common::getIsPackage(node)) {
    const struc::Package &package = dynamic_cast<const struc::Package&>(node);
    name = package.getName();
  } else if(Common::getIsInstanceInitializerBlock(node)) {
    name = initBlockName;
  } else if (Common::getIsStaticInitializerBlock(node)) {
    name = clInitName;
  } else if (Common::getIsLambda(node)) {
    name = lambdaName; // TODO
  } else {

  }
  if(name == "") {
    base::Base *p = getParent(node);
    if(p != NULL) {
      name = getName(*p);
    }
    name += getUnknownName(node);
  }

  return name;
}

std::string NameGenerator::getLongNameInternal(const base::Base& node) {
  Factory::TurnFilterOffSafely tfos(node.getFactory());
  std::string name = "";
  if(Common::getIsTypeDeclaration(node)) {
    const struc::TypeDeclaration &td = dynamic_cast<const struc::TypeDeclaration&>(node);
    name = getTypeDeclarationName(td, true);
  } else if(Common::getIsMethodDeclaration(node)) {
    name = getUniqueNameForBase(node);
  } else if(Common::getIsVariableDeclaration(node)) {
    const struc::VariableDeclaration &vd = dynamic_cast<const struc::VariableDeclaration&>(node);
    if(Common::getIsTypeDeclaration(*vd.getParent())) {
      name = getLongName(dynamic_cast<const struc::TypeDeclaration &>(*vd.getParent()));
      name += "." + vd.getName() + ";";
      std::string typeName = visitTypeExpr(vd.getType(), true);
      replace(typeName, '.', '/'); // FIXME hackelést kiszedni, ha jo lesz a getTypeName, vagy a uniqe nevben / legyen az elvalaszto . helyett
      name += typeName;
      //name += getTypeName(*vd.getType()->getType(), true, true);
    }
  } else if(Common::getIsPackage(node)) {
    const struc::Package &package = dynamic_cast<const struc::Package&>(node);
    name = package.getQualifiedName();
  } else if(Common::getIsInitializerBlock(node)) {
    name = getLongName(*node.getParent()) + ".";
    if(Common::getIsInstanceInitializerBlock(node)) {
      name += initBlockName;
    } else if (Common::getIsStaticInitializerBlock(node)){
      name += clInitName;
    }
  } else if (Common::getIsLambda(node)) { // TODO vmi rendes nev ???
    name = getUniqueNameForBase(*node.getParent());
    name += "." + lambda;
    name += "#" + Common::toString(dynamic_cast<const expr::Lambda&>(node).getPosition().getLine()); // FIXME
  } else {

  }
  if(name == "") {
    base::Base *p = getParent(node);
    if(p != NULL) {
      name = getLongName(*p);
    }
    name += getUnknownName(node);
  }

  return name;
}

std::string getName(const base::Base& node) {
  //return NameGenerator().getName(node);
  std::string name = NameGenerator().getName(node);
  //std::cout << "getName " << node.getId() << " " << Common::toString(node.getNodeKind()) << " " << name << std::endl;
  return name;
}

std::string getLongName(const base::Base& node) {
  //return NameGenerator().getLongName(node);
  std::string name = NameGenerator().getLongName(node);
  //std::cout << "getLongName " << node.getId() << " " << Common::toString(node.getNodeKind()) << " " << name << std::endl;
  return name;
}

std::string getUniqueNameForBase(const base::Base &node) {
  //return NameGenerator().getUniqueNameForBase(node);
  std::string name = NameGenerator().getUniqueNameForBase(node);
  //std::cout << "getUniqueNameForBase " << node.getId() << " " << Common::toString(node.getNodeKind()) << " " << name << std::endl;
  return name;
}

std::string getUniqueNameForType(const type::Type &node) {
  //return NameGenerator().getUniqueNameForType(node);
  std::string name = NameGenerator().getUniqueNameForType(node);
  //std::cout << "getUniqueNameForType " << node.getId() << " " << Common::toString(node.getNodeKind()) << " " << name << std::endl;
  return name;
}


} // Common 

}}}
