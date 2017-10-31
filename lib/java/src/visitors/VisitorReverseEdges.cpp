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

#include "java/inc/java.h"

namespace columbus { namespace java { namespace asg {
VisitorReverseEdges::VisitorReverseEdges(ReverseEdges *reverseEdges) : VisitorAbstractNodes(), revEdges(reverseEdges) {
}

VisitorReverseEdges::~VisitorReverseEdges() {
}

void VisitorReverseEdges::visit(const base::Base &node, bool callVirtualBase ) {
  NodeId id = node.getId();
  if (!revEdges->reContainer[id])
    revEdges->reContainer[id] = new ReverseEdges::NodeEdgesType();
}

void VisitorReverseEdges::visitCommentable_Comments(const base::Commentable& begin, const base::Comment& end) {
  revEdges->insertEdge(&end, &begin, edkCommentable_Comments);
}

void VisitorReverseEdges::visitAnnotation_HasAnnotationName(const expr::Annotation& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkAnnotation_HasAnnotationName);
}

void VisitorReverseEdges::visitArrayTypeExpression_HasComponentType(const expr::ArrayTypeExpression& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkArrayTypeExpression_HasComponentType);
}

void VisitorReverseEdges::visitBinary_HasLeftOperand(const expr::Binary& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkBinary_HasLeftOperand);
}

void VisitorReverseEdges::visitBinary_HasRightOperand(const expr::Binary& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkBinary_HasRightOperand);
}

void VisitorReverseEdges::visitClassLiteral_HasComponentType(const expr::ClassLiteral& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkClassLiteral_HasComponentType);
}

void VisitorReverseEdges::visitConditional_HasCondition(const expr::Conditional& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkConditional_HasCondition);
}

void VisitorReverseEdges::visitConditional_HasTrueExpression(const expr::Conditional& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkConditional_HasTrueExpression);
}

void VisitorReverseEdges::visitConditional_HasFalseExpression(const expr::Conditional& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkConditional_HasFalseExpression);
}

void VisitorReverseEdges::visitErroneous_HasErrors(const expr::Erroneous& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkErroneous_HasErrors);
}

void VisitorReverseEdges::visitErroneousTypeExpression_HasErrors(const expr::ErroneousTypeExpression& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkErroneousTypeExpression_HasErrors);
}

void VisitorReverseEdges::visitExpression_Type(const expr::Expression& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkExpression_Type);
}

void VisitorReverseEdges::visitIdentifier_RefersTo(const expr::Identifier& begin, const base::Named& end) {
  revEdges->insertEdge(&end, &begin, edkIdentifier_RefersTo);
}

void VisitorReverseEdges::visitInstanceOf_HasTypeOperand(const expr::InstanceOf& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkInstanceOf_HasTypeOperand);
}

void VisitorReverseEdges::visitMethodInvocation_HasTypeArguments(const expr::MethodInvocation& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkMethodInvocation_HasTypeArguments);
}

void VisitorReverseEdges::visitMethodInvocation_HasArguments(const expr::MethodInvocation& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkMethodInvocation_HasArguments);
}

void VisitorReverseEdges::visitMethodInvocation_Invokes(const expr::MethodInvocation& begin, const struc::MethodDeclaration& end) {
  revEdges->insertEdge(&end, &begin, edkMethodInvocation_Invokes);
}

void VisitorReverseEdges::visitNewArray_HasComponentType(const expr::NewArray& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkNewArray_HasComponentType);
}

void VisitorReverseEdges::visitNewArray_HasDimensions(const expr::NewArray& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkNewArray_HasDimensions);
}

void VisitorReverseEdges::visitNewArray_HasInitializers(const expr::NewArray& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkNewArray_HasInitializers);
}

void VisitorReverseEdges::visitNewClass_HasEnclosingExpression(const expr::NewClass& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkNewClass_HasEnclosingExpression);
}

void VisitorReverseEdges::visitNewClass_HasTypeArguments(const expr::NewClass& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkNewClass_HasTypeArguments);
}

void VisitorReverseEdges::visitNewClass_HasTypeName(const expr::NewClass& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkNewClass_HasTypeName);
}

void VisitorReverseEdges::visitNewClass_HasArguments(const expr::NewClass& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkNewClass_HasArguments);
}

void VisitorReverseEdges::visitNewClass_HasAnonymousClass(const expr::NewClass& begin, const struc::AnonymousClass& end) {
  revEdges->insertEdge(&end, &begin, edkNewClass_HasAnonymousClass);
}

void VisitorReverseEdges::visitNewClass_Constructor(const expr::NewClass& begin, const struc::NormalMethod& end) {
  revEdges->insertEdge(&end, &begin, edkNewClass_Constructor);
}

void VisitorReverseEdges::visitNormalAnnotation_HasArguments(const expr::NormalAnnotation& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkNormalAnnotation_HasArguments);
}

void VisitorReverseEdges::visitQualifiedTypeExpression_HasQualifierType(const expr::QualifiedTypeExpression& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkQualifiedTypeExpression_HasQualifierType);
}

void VisitorReverseEdges::visitQualifiedTypeExpression_HasSimpleType(const expr::QualifiedTypeExpression& begin, const expr::SimpleTypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkQualifiedTypeExpression_HasSimpleType);
}

void VisitorReverseEdges::visitSingleElementAnnotation_HasArgument(const expr::SingleElementAnnotation& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkSingleElementAnnotation_HasArgument);
}

void VisitorReverseEdges::visitTypeApplyExpression_HasRawType(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkTypeApplyExpression_HasRawType);
}

void VisitorReverseEdges::visitTypeApplyExpression_HasTypeArguments(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkTypeApplyExpression_HasTypeArguments);
}

void VisitorReverseEdges::visitTypeCast_HasTypeOperand(const expr::TypeCast& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkTypeCast_HasTypeOperand);
}

void VisitorReverseEdges::visitTypeUnionExpression_HasAlternatives(const expr::TypeUnionExpression& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkTypeUnionExpression_HasAlternatives);
}

void VisitorReverseEdges::visitUnary_HasOperand(const expr::Unary& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkUnary_HasOperand);
}

void VisitorReverseEdges::visitWildcardExpression_HasBound(const expr::WildcardExpression& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkWildcardExpression_HasBound);
}

void VisitorReverseEdges::visitAssert_HasCondition(const statm::Assert& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkAssert_HasCondition);
}

void VisitorReverseEdges::visitAssert_HasDetail(const statm::Assert& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkAssert_HasDetail);
}

void VisitorReverseEdges::visitBasicFor_HasInitializers(const statm::BasicFor& begin, const statm::Statement& end) {
  revEdges->insertEdge(&end, &begin, edkBasicFor_HasInitializers);
}

void VisitorReverseEdges::visitBasicFor_HasCondition(const statm::BasicFor& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkBasicFor_HasCondition);
}

void VisitorReverseEdges::visitBasicFor_HasUpdates(const statm::BasicFor& begin, const statm::Statement& end) {
  revEdges->insertEdge(&end, &begin, edkBasicFor_HasUpdates);
}

void VisitorReverseEdges::visitBlock_HasStatements(const statm::Block& begin, const statm::Statement& end) {
  revEdges->insertEdge(&end, &begin, edkBlock_HasStatements);
}

void VisitorReverseEdges::visitCase_HasExpression(const statm::Case& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkCase_HasExpression);
}

void VisitorReverseEdges::visitDo_HasCondition(const statm::Do& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkDo_HasCondition);
}

void VisitorReverseEdges::visitEnhancedFor_HasParameter(const statm::EnhancedFor& begin, const struc::Parameter& end) {
  revEdges->insertEdge(&end, &begin, edkEnhancedFor_HasParameter);
}

void VisitorReverseEdges::visitEnhancedFor_HasExpression(const statm::EnhancedFor& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkEnhancedFor_HasExpression);
}

void VisitorReverseEdges::visitExpressionStatement_HasExpression(const statm::ExpressionStatement& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkExpressionStatement_HasExpression);
}

void VisitorReverseEdges::visitHandler_HasParameter(const statm::Handler& begin, const struc::Parameter& end) {
  revEdges->insertEdge(&end, &begin, edkHandler_HasParameter);
}

void VisitorReverseEdges::visitHandler_HasBlock(const statm::Handler& begin, const statm::Block& end) {
  revEdges->insertEdge(&end, &begin, edkHandler_HasBlock);
}

void VisitorReverseEdges::visitIf_HasSubstatement(const statm::If& begin, const statm::Statement& end) {
  revEdges->insertEdge(&end, &begin, edkIf_HasSubstatement);
}

void VisitorReverseEdges::visitIf_HasFalseSubstatement(const statm::If& begin, const statm::Statement& end) {
  revEdges->insertEdge(&end, &begin, edkIf_HasFalseSubstatement);
}

void VisitorReverseEdges::visitIteration_HasSubstatement(const statm::Iteration& begin, const statm::Statement& end) {
  revEdges->insertEdge(&end, &begin, edkIteration_HasSubstatement);
}

void VisitorReverseEdges::visitJump_Target(const statm::Jump& begin, const statm::Statement& end) {
  revEdges->insertEdge(&end, &begin, edkJump_Target);
}

void VisitorReverseEdges::visitLabeledStatement_HasStatement(const statm::LabeledStatement& begin, const statm::Statement& end) {
  revEdges->insertEdge(&end, &begin, edkLabeledStatement_HasStatement);
}

void VisitorReverseEdges::visitReturn_HasExpression(const statm::Return& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkReturn_HasExpression);
}

void VisitorReverseEdges::visitSelection_HasCondition(const statm::Selection& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkSelection_HasCondition);
}

void VisitorReverseEdges::visitSwitch_HasCases(const statm::Switch& begin, const statm::SwitchLabel& end) {
  revEdges->insertEdge(&end, &begin, edkSwitch_HasCases);
}

void VisitorReverseEdges::visitSwitchLabel_HasStatements(const statm::SwitchLabel& begin, const statm::Statement& end) {
  revEdges->insertEdge(&end, &begin, edkSwitchLabel_HasStatements);
}

void VisitorReverseEdges::visitSynchronized_HasLock(const statm::Synchronized& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkSynchronized_HasLock);
}

void VisitorReverseEdges::visitSynchronized_HasBlock(const statm::Synchronized& begin, const statm::Block& end) {
  revEdges->insertEdge(&end, &begin, edkSynchronized_HasBlock);
}

void VisitorReverseEdges::visitThrow_HasExpression(const statm::Throw& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkThrow_HasExpression);
}

void VisitorReverseEdges::visitTry_HasResources(const statm::Try& begin, const struc::Variable& end) {
  revEdges->insertEdge(&end, &begin, edkTry_HasResources);
}

void VisitorReverseEdges::visitTry_HasBlock(const statm::Try& begin, const statm::Block& end) {
  revEdges->insertEdge(&end, &begin, edkTry_HasBlock);
}

void VisitorReverseEdges::visitTry_HasHandlers(const statm::Try& begin, const statm::Handler& end) {
  revEdges->insertEdge(&end, &begin, edkTry_HasHandlers);
}

void VisitorReverseEdges::visitTry_HasFinallyBlock(const statm::Try& begin, const statm::Block& end) {
  revEdges->insertEdge(&end, &begin, edkTry_HasFinallyBlock);
}

void VisitorReverseEdges::visitWhile_HasCondition(const statm::While& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkWhile_HasCondition);
}

void VisitorReverseEdges::visitAnnotatedElement_HasAnnotations(const struc::AnnotatedElement& begin, const expr::Annotation& end) {
  revEdges->insertEdge(&end, &begin, edkAnnotatedElement_HasAnnotations);
}

void VisitorReverseEdges::visitAnnotationTypeElement_HasDefaultValue(const struc::AnnotationTypeElement& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkAnnotationTypeElement_HasDefaultValue);
}

void VisitorReverseEdges::visitCompilationUnit_HasPackageDeclaration(const struc::CompilationUnit& begin, const struc::PackageDeclaration& end) {
  revEdges->insertEdge(&end, &begin, edkCompilationUnit_HasPackageDeclaration);
}

void VisitorReverseEdges::visitCompilationUnit_HasImports(const struc::CompilationUnit& begin, const struc::Import& end) {
  revEdges->insertEdge(&end, &begin, edkCompilationUnit_HasImports);
}

void VisitorReverseEdges::visitCompilationUnit_TypeDeclarations(const struc::CompilationUnit& begin, const struc::TypeDeclaration& end) {
  revEdges->insertEdge(&end, &begin, edkCompilationUnit_TypeDeclarations);
}

void VisitorReverseEdges::visitCompilationUnit_HasOthers(const struc::CompilationUnit& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkCompilationUnit_HasOthers);
}

void VisitorReverseEdges::visitEnumConstant_HasNewClass(const struc::EnumConstant& begin, const expr::NewClass& end) {
  revEdges->insertEdge(&end, &begin, edkEnumConstant_HasNewClass);
}

void VisitorReverseEdges::visitGenericDeclaration_HasTypeParameters(const struc::GenericDeclaration& begin, const struc::TypeParameter& end) {
  revEdges->insertEdge(&end, &begin, edkGenericDeclaration_HasTypeParameters);
}

void VisitorReverseEdges::visitImport_HasTarget(const struc::Import& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkImport_HasTarget);
}

void VisitorReverseEdges::visitInitializerBlock_HasBody(const struc::InitializerBlock& begin, const statm::Block& end) {
  revEdges->insertEdge(&end, &begin, edkInitializerBlock_HasBody);
}

void VisitorReverseEdges::visitMethodDeclaration_HasReturnType(const struc::MethodDeclaration& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkMethodDeclaration_HasReturnType);
}

void VisitorReverseEdges::visitMethodDeclaration_MethodType(const struc::MethodDeclaration& begin, const type::MethodType& end) {
  revEdges->insertEdge(&end, &begin, edkMethodDeclaration_MethodType);
}

void VisitorReverseEdges::visitMethodDeclaration_Overrides(const struc::MethodDeclaration& begin, const struc::MethodDeclaration& end) {
  revEdges->insertEdge(&end, &begin, edkMethodDeclaration_Overrides);
}

void VisitorReverseEdges::visitNormalMethod_HasParameters(const struc::NormalMethod& begin, const struc::Parameter& end) {
  revEdges->insertEdge(&end, &begin, edkNormalMethod_HasParameters);
}

void VisitorReverseEdges::visitNormalMethod_HasBody(const struc::NormalMethod& begin, const statm::Block& end) {
  revEdges->insertEdge(&end, &begin, edkNormalMethod_HasBody);
}

void VisitorReverseEdges::visitNormalMethod_HasThrownExceptions(const struc::NormalMethod& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkNormalMethod_HasThrownExceptions);
}

void VisitorReverseEdges::visitPackage_HasCompilationUnits(const struc::Package& begin, const struc::CompilationUnit& end) {
  revEdges->insertEdge(&end, &begin, edkPackage_HasCompilationUnits);
}

void VisitorReverseEdges::visitPackageDeclaration_HasPackageName(const struc::PackageDeclaration& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkPackageDeclaration_HasPackageName);
}

void VisitorReverseEdges::visitPackageDeclaration_RefersTo(const struc::PackageDeclaration& begin, const struc::Package& end) {
  revEdges->insertEdge(&end, &begin, edkPackageDeclaration_RefersTo);
}

void VisitorReverseEdges::visitScope_HasMembers(const struc::Scope& begin, const struc::Member& end) {
  revEdges->insertEdge(&end, &begin, edkScope_HasMembers);
}

void VisitorReverseEdges::visitTypeDeclaration_IsInCompilationUnit(const struc::TypeDeclaration& begin, const struc::CompilationUnit& end) {
  revEdges->insertEdge(&end, &begin, edkTypeDeclaration_IsInCompilationUnit);
}

void VisitorReverseEdges::visitTypeDeclaration_HasSuperClass(const struc::TypeDeclaration& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkTypeDeclaration_HasSuperClass);
}

void VisitorReverseEdges::visitTypeDeclaration_HasSuperInterfaces(const struc::TypeDeclaration& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkTypeDeclaration_HasSuperInterfaces);
}

void VisitorReverseEdges::visitTypeDeclaration_HasOthers(const struc::TypeDeclaration& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkTypeDeclaration_HasOthers);
}

void VisitorReverseEdges::visitTypeParameter_HasBounds(const struc::TypeParameter& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkTypeParameter_HasBounds);
}

void VisitorReverseEdges::visitVariable_HasInitialValue(const struc::Variable& begin, const expr::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkVariable_HasInitialValue);
}

void VisitorReverseEdges::visitVariableDeclaration_HasType(const struc::VariableDeclaration& begin, const expr::TypeExpression& end) {
  revEdges->insertEdge(&end, &begin, edkVariableDeclaration_HasType);
}

void VisitorReverseEdges::visitArrayType_ComponentType(const type::ArrayType& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkArrayType_ComponentType);
}

void VisitorReverseEdges::visitClassType_RefersTo(const type::ClassType& begin, const struc::TypeDeclaration& end) {
  revEdges->insertEdge(&end, &begin, edkClassType_RefersTo);
}

void VisitorReverseEdges::visitMethodType_ReturnType(const type::MethodType& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkMethodType_ReturnType);
}

void VisitorReverseEdges::visitMethodType_ParameterTypes(const type::MethodType& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkMethodType_ParameterTypes);
}

void VisitorReverseEdges::visitMethodType_ThrownTypes(const type::MethodType& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkMethodType_ThrownTypes);
}

void VisitorReverseEdges::visitPackageType_RefersTo(const type::PackageType& begin, const struc::Package& end) {
  revEdges->insertEdge(&end, &begin, edkPackageType_RefersTo);
}

void VisitorReverseEdges::visitParameterizedType_RawType(const type::ParameterizedType& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkParameterizedType_RawType);
}

void VisitorReverseEdges::visitParameterizedType_ArgumentTypes(const type::ParameterizedType& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkParameterizedType_ArgumentTypes);
}

void VisitorReverseEdges::visitScopedType_Owner(const type::ScopedType& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkScopedType_Owner);
}

void VisitorReverseEdges::visitTypeVariable_RefersTo(const type::TypeVariable& begin, const struc::TypeParameter& end) {
  revEdges->insertEdge(&end, &begin, edkTypeVariable_RefersTo);
}

void VisitorReverseEdges::visitUnionType_Alternatives(const type::UnionType& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkUnionType_Alternatives);
}

void VisitorReverseEdges::visitWildcardType_Bound(const type::WildcardType& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkWildcardType_Bound);
}


}}}
