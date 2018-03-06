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

#include "python/inc/python.h"

namespace columbus { namespace python { namespace asg {
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

void VisitorReverseEdges::visitArgumentList_HasPositionalArguments(const expression::ArgumentList& begin, const expression::ExpressionList& end) {
  revEdges->insertEdge(&end, &begin, edkArgumentList_HasPositionalArguments);
}

void VisitorReverseEdges::visitArgumentList_HasDictionary(const expression::ArgumentList& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkArgumentList_HasDictionary);
}

void VisitorReverseEdges::visitArgumentList_HasKeyword(const expression::ArgumentList& begin, const expression::Keyword& end) {
  revEdges->insertEdge(&end, &begin, edkArgumentList_HasKeyword);
}

void VisitorReverseEdges::visitArgumentList_HasTuple(const expression::ArgumentList& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkArgumentList_HasTuple);
}

void VisitorReverseEdges::visitBinary_HasLeftExpression(const expression::Binary& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkBinary_HasLeftExpression);
}

void VisitorReverseEdges::visitBinary_HasRightExpression(const expression::Binary& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkBinary_HasRightExpression);
}

void VisitorReverseEdges::visitCall_HasArgumentList(const expression::Call& begin, const expression::ArgumentList& end) {
  revEdges->insertEdge(&end, &begin, edkCall_HasArgumentList);
}

void VisitorReverseEdges::visitCall_RefersTo(const expression::Call& begin, const statement::CompoundStatement& end) {
  revEdges->insertEdge(&end, &begin, edkCall_RefersTo);
}

void VisitorReverseEdges::visitDictComp_HasKeyValue(const expression::DictComp& begin, const expression::KeyValue& end) {
  revEdges->insertEdge(&end, &begin, edkDictComp_HasKeyValue);
}

void VisitorReverseEdges::visitDictComp_HasGenerator(const expression::DictComp& begin, const expression::Generator& end) {
  revEdges->insertEdge(&end, &begin, edkDictComp_HasGenerator);
}

void VisitorReverseEdges::visitDictionary_HasKeyValue(const expression::Dictionary& begin, const expression::KeyValue& end) {
  revEdges->insertEdge(&end, &begin, edkDictionary_HasKeyValue);
}

void VisitorReverseEdges::visitExpression_HasType(const expression::Expression& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkExpression_HasType);
}

void VisitorReverseEdges::visitExpressionList_HasExpression(const expression::ExpressionList& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkExpressionList_HasExpression);
}

void VisitorReverseEdges::visitExtSlice_HasItem(const expression::ExtSlice& begin, const expression::Slicing& end) {
  revEdges->insertEdge(&end, &begin, edkExtSlice_HasItem);
}

void VisitorReverseEdges::visitGenerator_HasCondition(const expression::Generator& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkGenerator_HasCondition);
}

void VisitorReverseEdges::visitGenerator_HasIter(const expression::Generator& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkGenerator_HasIter);
}

void VisitorReverseEdges::visitGenerator_HasTarget(const expression::Generator& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkGenerator_HasTarget);
}

void VisitorReverseEdges::visitGeneratorExpression_HasExpression(const expression::GeneratorExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkGeneratorExpression_HasExpression);
}

void VisitorReverseEdges::visitGeneratorExpression_HasGenerator(const expression::GeneratorExpression& begin, const expression::Generator& end) {
  revEdges->insertEdge(&end, &begin, edkGeneratorExpression_HasGenerator);
}

void VisitorReverseEdges::visitIdentifier_RefersTo(const expression::Identifier& begin, const module::Object& end) {
  revEdges->insertEdge(&end, &begin, edkIdentifier_RefersTo);
}

void VisitorReverseEdges::visitIfExpression_HasBody(const expression::IfExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkIfExpression_HasBody);
}

void VisitorReverseEdges::visitIfExpression_HasElseBody(const expression::IfExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkIfExpression_HasElseBody);
}

void VisitorReverseEdges::visitIfExpression_HasTest(const expression::IfExpression& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkIfExpression_HasTest);
}

void VisitorReverseEdges::visitKeyValue_HasKey(const expression::KeyValue& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkKeyValue_HasKey);
}

void VisitorReverseEdges::visitKeyValue_HasValue(const expression::KeyValue& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkKeyValue_HasValue);
}

void VisitorReverseEdges::visitKeyword_HasKey(const expression::Keyword& begin, const expression::Identifier& end) {
  revEdges->insertEdge(&end, &begin, edkKeyword_HasKey);
}

void VisitorReverseEdges::visitKeyword_HasValue(const expression::Keyword& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkKeyword_HasValue);
}

void VisitorReverseEdges::visitLambda_HasObject(const expression::Lambda& begin, const module::Object& end) {
  revEdges->insertEdge(&end, &begin, edkLambda_HasObject);
}

void VisitorReverseEdges::visitLambda_HasParameter(const expression::Lambda& begin, const statement::Parameter& end) {
  revEdges->insertEdge(&end, &begin, edkLambda_HasParameter);
}

void VisitorReverseEdges::visitLambda_HasExpression(const expression::Lambda& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkLambda_HasExpression);
}

void VisitorReverseEdges::visitList_HasExpression(const expression::List& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkList_HasExpression);
}

void VisitorReverseEdges::visitListComp_HasExpression(const expression::ListComp& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkListComp_HasExpression);
}

void VisitorReverseEdges::visitListComp_HasGenerator(const expression::ListComp& begin, const expression::Generator& end) {
  revEdges->insertEdge(&end, &begin, edkListComp_HasGenerator);
}

void VisitorReverseEdges::visitSet_HasExpression(const expression::Set& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkSet_HasExpression);
}

void VisitorReverseEdges::visitSetComp_HasExpression(const expression::SetComp& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkSetComp_HasExpression);
}

void VisitorReverseEdges::visitSetComp_HasGenerator(const expression::SetComp& begin, const expression::Generator& end) {
  revEdges->insertEdge(&end, &begin, edkSetComp_HasGenerator);
}

void VisitorReverseEdges::visitSlice_HasLowerBound(const expression::Slice& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkSlice_HasLowerBound);
}

void VisitorReverseEdges::visitSlice_HasStride(const expression::Slice& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkSlice_HasStride);
}

void VisitorReverseEdges::visitSlice_HasUpperBound(const expression::Slice& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkSlice_HasUpperBound);
}

void VisitorReverseEdges::visitStringConversion_HasExpressionList(const expression::StringConversion& begin, const expression::ExpressionList& end) {
  revEdges->insertEdge(&end, &begin, edkStringConversion_HasExpressionList);
}

void VisitorReverseEdges::visitSubscription_HasSlicing(const expression::Subscription& begin, const expression::Slicing& end) {
  revEdges->insertEdge(&end, &begin, edkSubscription_HasSlicing);
}

void VisitorReverseEdges::visitUnary_HasExpression(const expression::Unary& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkUnary_HasExpression);
}

void VisitorReverseEdges::visitYieldExpression_HasYieldExpression(const expression::YieldExpression& begin, const expression::ExpressionList& end) {
  revEdges->insertEdge(&end, &begin, edkYieldExpression_HasYieldExpression);
}

void VisitorReverseEdges::visitModule_HasObject(const module::Module& begin, const module::Object& end) {
  revEdges->insertEdge(&end, &begin, edkModule_HasObject);
}

void VisitorReverseEdges::visitModule_HasStatement(const module::Module& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkModule_HasStatement);
}

void VisitorReverseEdges::visitModule_Docstring(const module::Module& begin, const base::Docstring& end) {
  revEdges->insertEdge(&end, &begin, edkModule_Docstring);
}

void VisitorReverseEdges::visitObject_RefersTo(const module::Object& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkObject_RefersTo);
}

void VisitorReverseEdges::visitObject_HasType(const module::Object& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkObject_HasType);
}

void VisitorReverseEdges::visitPackage_HasModule(const module::Package& begin, const module::Module& end) {
  revEdges->insertEdge(&end, &begin, edkPackage_HasModule);
}

void VisitorReverseEdges::visitPackage_HasPackage(const module::Package& begin, const module::Package& end) {
  revEdges->insertEdge(&end, &begin, edkPackage_HasPackage);
}

void VisitorReverseEdges::visitAlias_RefersTo(const statement::Alias& begin, const base::Base& end) {
  revEdges->insertEdge(&end, &begin, edkAlias_RefersTo);
}

void VisitorReverseEdges::visitAssert_HasMsgExpression(const statement::Assert& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkAssert_HasMsgExpression);
}

void VisitorReverseEdges::visitAssert_HasTestExpression(const statement::Assert& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkAssert_HasTestExpression);
}

void VisitorReverseEdges::visitAssign_HasExpression(const statement::Assign& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkAssign_HasExpression);
}

void VisitorReverseEdges::visitAssign_HasTargetList(const statement::Assign& begin, const statement::TargetList& end) {
  revEdges->insertEdge(&end, &begin, edkAssign_HasTargetList);
}

void VisitorReverseEdges::visitBaseSpecifier_HasName(const statement::BaseSpecifier& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkBaseSpecifier_HasName);
}

void VisitorReverseEdges::visitBaseSpecifier_DerivesFrom(const statement::BaseSpecifier& begin, const statement::ClassDef& end) {
  revEdges->insertEdge(&end, &begin, edkBaseSpecifier_DerivesFrom);
}

void VisitorReverseEdges::visitClassDef_HasObject(const statement::ClassDef& begin, const module::Object& end) {
  revEdges->insertEdge(&end, &begin, edkClassDef_HasObject);
}

void VisitorReverseEdges::visitClassDef_HasBaseSpecifier(const statement::ClassDef& begin, const statement::BaseSpecifier& end) {
  revEdges->insertEdge(&end, &begin, edkClassDef_HasBaseSpecifier);
}

void VisitorReverseEdges::visitClassDef_HasDecorator(const statement::ClassDef& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkClassDef_HasDecorator);
}

void VisitorReverseEdges::visitClassDef_RefersTo(const statement::ClassDef& begin, const module::Object& end) {
  revEdges->insertEdge(&end, &begin, edkClassDef_RefersTo);
}

void VisitorReverseEdges::visitClassDef_Docstring(const statement::ClassDef& begin, const base::Docstring& end) {
  revEdges->insertEdge(&end, &begin, edkClassDef_Docstring);
}

void VisitorReverseEdges::visitCompoundStatement_HasBody(const statement::CompoundStatement& begin, const statement::Suite& end) {
  revEdges->insertEdge(&end, &begin, edkCompoundStatement_HasBody);
}

void VisitorReverseEdges::visitDelete_HasTargetList(const statement::Delete& begin, const statement::TargetList& end) {
  revEdges->insertEdge(&end, &begin, edkDelete_HasTargetList);
}

void VisitorReverseEdges::visitExec_HasExpression(const statement::Exec& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkExec_HasExpression);
}

void VisitorReverseEdges::visitExec_HasGlobals(const statement::Exec& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkExec_HasGlobals);
}

void VisitorReverseEdges::visitExec_HasLocals(const statement::Exec& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkExec_HasLocals);
}

void VisitorReverseEdges::visitFor_HasExpressionList(const statement::For& begin, const expression::ExpressionList& end) {
  revEdges->insertEdge(&end, &begin, edkFor_HasExpressionList);
}

void VisitorReverseEdges::visitFor_HasTargetList(const statement::For& begin, const statement::TargetList& end) {
  revEdges->insertEdge(&end, &begin, edkFor_HasTargetList);
}

void VisitorReverseEdges::visitFunctionDef_HasDecorator(const statement::FunctionDef& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkFunctionDef_HasDecorator);
}

void VisitorReverseEdges::visitFunctionDef_HasObject(const statement::FunctionDef& begin, const module::Object& end) {
  revEdges->insertEdge(&end, &begin, edkFunctionDef_HasObject);
}

void VisitorReverseEdges::visitFunctionDef_HasParameter(const statement::FunctionDef& begin, const statement::Parameter& end) {
  revEdges->insertEdge(&end, &begin, edkFunctionDef_HasParameter);
}

void VisitorReverseEdges::visitFunctionDef_RefersTo(const statement::FunctionDef& begin, const module::Object& end) {
  revEdges->insertEdge(&end, &begin, edkFunctionDef_RefersTo);
}

void VisitorReverseEdges::visitFunctionDef_ReturnType(const statement::FunctionDef& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkFunctionDef_ReturnType);
}

void VisitorReverseEdges::visitFunctionDef_Docstring(const statement::FunctionDef& begin, const base::Docstring& end) {
  revEdges->insertEdge(&end, &begin, edkFunctionDef_Docstring);
}

void VisitorReverseEdges::visitGlobal_HasIdentifier(const statement::Global& begin, const expression::Identifier& end) {
  revEdges->insertEdge(&end, &begin, edkGlobal_HasIdentifier);
}

void VisitorReverseEdges::visitHandler_HasName(const statement::Handler& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkHandler_HasName);
}

void VisitorReverseEdges::visitHandler_HasExceptBody(const statement::Handler& begin, const statement::Suite& end) {
  revEdges->insertEdge(&end, &begin, edkHandler_HasExceptBody);
}

void VisitorReverseEdges::visitHandler_HasType(const statement::Handler& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkHandler_HasType);
}

void VisitorReverseEdges::visitIf_HasElseBody(const statement::If& begin, const statement::Suite& end) {
  revEdges->insertEdge(&end, &begin, edkIf_HasElseBody);
}

void VisitorReverseEdges::visitIf_HasTestExpression(const statement::If& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkIf_HasTestExpression);
}

void VisitorReverseEdges::visitImportStatement_HasAlias(const statement::ImportStatement& begin, const statement::Alias& end) {
  revEdges->insertEdge(&end, &begin, edkImportStatement_HasAlias);
}

void VisitorReverseEdges::visitIteration_HasElseBody(const statement::Iteration& begin, const statement::Suite& end) {
  revEdges->insertEdge(&end, &begin, edkIteration_HasElseBody);
}

void VisitorReverseEdges::visitParameter_HasDefaultValue(const statement::Parameter& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkParameter_HasDefaultValue);
}

void VisitorReverseEdges::visitParameter_RefersTo(const statement::Parameter& begin, const module::Object& end) {
  revEdges->insertEdge(&end, &begin, edkParameter_RefersTo);
}

void VisitorReverseEdges::visitPrint_HasExpressionList(const statement::Print& begin, const expression::ExpressionList& end) {
  revEdges->insertEdge(&end, &begin, edkPrint_HasExpressionList);
}

void VisitorReverseEdges::visitPrint_HasDestination(const statement::Print& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkPrint_HasDestination);
}

void VisitorReverseEdges::visitRaise_HasTracebackExpression(const statement::Raise& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkRaise_HasTracebackExpression);
}

void VisitorReverseEdges::visitRaise_HasTypeExpression(const statement::Raise& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkRaise_HasTypeExpression);
}

void VisitorReverseEdges::visitRaise_HasValueExpression(const statement::Raise& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkRaise_HasValueExpression);
}

void VisitorReverseEdges::visitReturn_HasExpression(const statement::Return& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkReturn_HasExpression);
}

void VisitorReverseEdges::visitSuite_HasStatement(const statement::Suite& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkSuite_HasStatement);
}

void VisitorReverseEdges::visitTargetList_HasTarget(const statement::TargetList& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkTargetList_HasTarget);
}

void VisitorReverseEdges::visitTryExcept_HasElseBody(const statement::TryExcept& begin, const statement::Suite& end) {
  revEdges->insertEdge(&end, &begin, edkTryExcept_HasElseBody);
}

void VisitorReverseEdges::visitTryExcept_HasHandler(const statement::TryExcept& begin, const statement::Handler& end) {
  revEdges->insertEdge(&end, &begin, edkTryExcept_HasHandler);
}

void VisitorReverseEdges::visitTryExcept_HasFinallyBody(const statement::TryExcept& begin, const statement::Suite& end) {
  revEdges->insertEdge(&end, &begin, edkTryExcept_HasFinallyBody);
}

void VisitorReverseEdges::visitTryFinal_HasFinallyBody(const statement::TryFinal& begin, const statement::Suite& end) {
  revEdges->insertEdge(&end, &begin, edkTryFinal_HasFinallyBody);
}

void VisitorReverseEdges::visitWhile_HasTestExpression(const statement::While& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkWhile_HasTestExpression);
}

void VisitorReverseEdges::visitWith_HasExpression(const statement::With& begin, const expression::Expression& end) {
  revEdges->insertEdge(&end, &begin, edkWith_HasExpression);
}

void VisitorReverseEdges::visitWith_HasTargetList(const statement::With& begin, const statement::TargetList& end) {
  revEdges->insertEdge(&end, &begin, edkWith_HasTargetList);
}

void VisitorReverseEdges::visitReferenceType_RefersTo(const type::ReferenceType& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkReferenceType_RefersTo);
}


}}}
