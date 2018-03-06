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
Visitor::Visitor(): depth(0) {
}

Visitor::~Visitor() {
}

unsigned Visitor::getDepth() const {
  return depth;
}

void Visitor::incDepth() {
  ++depth;
}

void Visitor::decDepth() {
  --depth;
}

void Visitor::beginVisit() {
}

void Visitor::finishVisit() {
}

void Visitor::visit(const base::Comment& node , bool callVirtualBase) {}

void Visitor::visitEnd(const base::Comment& node , bool callVirtualBase) { }

void Visitor::visit(const base::Docstring& node , bool callVirtualBase) {}

void Visitor::visitEnd(const base::Docstring& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ArgumentList& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ArgumentList& node , bool callVirtualBase) { }

void Visitor::visit(const expression::AttributeRef& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::AttributeRef& node , bool callVirtualBase) { }

void Visitor::visit(const expression::BinaryArithmetic& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::BinaryArithmetic& node , bool callVirtualBase) { }

void Visitor::visit(const expression::BinaryLogical& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::BinaryLogical& node , bool callVirtualBase) { }

void Visitor::visit(const expression::Call& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::Call& node , bool callVirtualBase) { }

void Visitor::visit(const expression::DictComp& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::DictComp& node , bool callVirtualBase) { }

void Visitor::visit(const expression::Dictionary& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::Dictionary& node , bool callVirtualBase) { }

void Visitor::visit(const expression::Ellipsis& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::Ellipsis& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ExpressionList& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ExpressionList& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ExtSlice& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ExtSlice& node , bool callVirtualBase) { }

void Visitor::visit(const expression::FloatNumber& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::FloatNumber& node , bool callVirtualBase) { }

void Visitor::visit(const expression::Generator& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::Generator& node , bool callVirtualBase) { }

void Visitor::visit(const expression::GeneratorExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::GeneratorExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::Identifier& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::Identifier& node , bool callVirtualBase) { }

void Visitor::visit(const expression::IfExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::IfExpression& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ImagNumber& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ImagNumber& node , bool callVirtualBase) { }

void Visitor::visit(const expression::Index& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::Index& node , bool callVirtualBase) { }

void Visitor::visit(const expression::IntegerLiteral& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::IntegerLiteral& node , bool callVirtualBase) { }

void Visitor::visit(const expression::KeyValue& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::KeyValue& node , bool callVirtualBase) { }

void Visitor::visit(const expression::Keyword& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::Keyword& node , bool callVirtualBase) { }

void Visitor::visit(const expression::Lambda& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::Lambda& node , bool callVirtualBase) { }

void Visitor::visit(const expression::List& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::List& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ListComp& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ListComp& node , bool callVirtualBase) { }

void Visitor::visit(const expression::LongInteger& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::LongInteger& node , bool callVirtualBase) { }

void Visitor::visit(const expression::Set& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::Set& node , bool callVirtualBase) { }

void Visitor::visit(const expression::SetComp& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::SetComp& node , bool callVirtualBase) { }

void Visitor::visit(const expression::Slice& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::Slice& node , bool callVirtualBase) { }

void Visitor::visit(const expression::StringConversion& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::StringConversion& node , bool callVirtualBase) { }

void Visitor::visit(const expression::StringLiteral& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::StringLiteral& node , bool callVirtualBase) { }

void Visitor::visit(const expression::Subscription& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::Subscription& node , bool callVirtualBase) { }

void Visitor::visit(const expression::UnaryOperation& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::UnaryOperation& node , bool callVirtualBase) { }

void Visitor::visit(const expression::YieldExpression& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::YieldExpression& node , bool callVirtualBase) { }

void Visitor::visit(const module::Module& node , bool callVirtualBase) {}

void Visitor::visitEnd(const module::Module& node , bool callVirtualBase) { }

void Visitor::visit(const module::Object& node , bool callVirtualBase) {}

void Visitor::visitEnd(const module::Object& node , bool callVirtualBase) { }

void Visitor::visit(const module::Package& node , bool callVirtualBase) {}

void Visitor::visitEnd(const module::Package& node , bool callVirtualBase) { }

void Visitor::visit(const statement::Alias& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::Alias& node , bool callVirtualBase) { }

void Visitor::visit(const statement::Assert& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::Assert& node , bool callVirtualBase) { }

void Visitor::visit(const statement::Assign& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::Assign& node , bool callVirtualBase) { }

void Visitor::visit(const statement::AugAssign& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::AugAssign& node , bool callVirtualBase) { }

void Visitor::visit(const statement::BaseSpecifier& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::BaseSpecifier& node , bool callVirtualBase) { }

void Visitor::visit(const statement::Break& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::Break& node , bool callVirtualBase) { }

void Visitor::visit(const statement::ClassDef& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::ClassDef& node , bool callVirtualBase) { }

void Visitor::visit(const statement::Continue& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::Continue& node , bool callVirtualBase) { }

void Visitor::visit(const statement::Delete& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::Delete& node , bool callVirtualBase) { }

void Visitor::visit(const statement::Exec& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::Exec& node , bool callVirtualBase) { }

void Visitor::visit(const statement::For& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::For& node , bool callVirtualBase) { }

void Visitor::visit(const statement::FunctionDef& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::FunctionDef& node , bool callVirtualBase) { }

void Visitor::visit(const statement::Global& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::Global& node , bool callVirtualBase) { }

void Visitor::visit(const statement::Handler& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::Handler& node , bool callVirtualBase) { }

void Visitor::visit(const statement::If& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::If& node , bool callVirtualBase) { }

void Visitor::visit(const statement::ImportFrom& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::ImportFrom& node , bool callVirtualBase) { }

void Visitor::visit(const statement::ImportStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::ImportStatement& node , bool callVirtualBase) { }

void Visitor::visit(const statement::Parameter& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::Parameter& node , bool callVirtualBase) { }

void Visitor::visit(const statement::Pass& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::Pass& node , bool callVirtualBase) { }

void Visitor::visit(const statement::Print& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::Print& node , bool callVirtualBase) { }

void Visitor::visit(const statement::Raise& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::Raise& node , bool callVirtualBase) { }

void Visitor::visit(const statement::Return& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::Return& node , bool callVirtualBase) { }

void Visitor::visit(const statement::Suite& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::Suite& node , bool callVirtualBase) { }

void Visitor::visit(const statement::TargetList& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::TargetList& node , bool callVirtualBase) { }

void Visitor::visit(const statement::TryExcept& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::TryExcept& node , bool callVirtualBase) { }

void Visitor::visit(const statement::TryFinal& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::TryFinal& node , bool callVirtualBase) { }

void Visitor::visit(const statement::While& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::While& node , bool callVirtualBase) { }

void Visitor::visit(const statement::With& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::With& node , bool callVirtualBase) { }

void Visitor::visit(const type::DictType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::DictType& node , bool callVirtualBase) { }

void Visitor::visit(const type::ReferenceType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::ReferenceType& node , bool callVirtualBase) { }

void Visitor::visit(const type::SequenceType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::SequenceType& node , bool callVirtualBase) { }

void Visitor::visit(const type::SimpleType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::SimpleType& node , bool callVirtualBase) { }

void Visitor::visitPositioned_Comments(const base::Positioned& begin, const base::Comment& end) { }

void Visitor::visitEndPositioned_Comments(const base::Positioned& begin, const base::Comment& end) { }

void Visitor::visitArgumentList_HasPositionalArguments(const expression::ArgumentList& begin, const expression::ExpressionList& end) { }

void Visitor::visitEndArgumentList_HasPositionalArguments(const expression::ArgumentList& begin, const expression::ExpressionList& end) { }

void Visitor::visitArgumentList_HasDictionary(const expression::ArgumentList& begin, const expression::Expression& end) { }

void Visitor::visitEndArgumentList_HasDictionary(const expression::ArgumentList& begin, const expression::Expression& end) { }

void Visitor::visitArgumentList_HasKeyword(const expression::ArgumentList& begin, const expression::Keyword& end) { }

void Visitor::visitEndArgumentList_HasKeyword(const expression::ArgumentList& begin, const expression::Keyword& end) { }

void Visitor::visitArgumentList_HasTuple(const expression::ArgumentList& begin, const expression::Expression& end) { }

void Visitor::visitEndArgumentList_HasTuple(const expression::ArgumentList& begin, const expression::Expression& end) { }

void Visitor::visitBinary_HasLeftExpression(const expression::Binary& begin, const expression::Expression& end) { }

void Visitor::visitEndBinary_HasLeftExpression(const expression::Binary& begin, const expression::Expression& end) { }

void Visitor::visitBinary_HasRightExpression(const expression::Binary& begin, const expression::Expression& end) { }

void Visitor::visitEndBinary_HasRightExpression(const expression::Binary& begin, const expression::Expression& end) { }

void Visitor::visitCall_HasArgumentList(const expression::Call& begin, const expression::ArgumentList& end) { }

void Visitor::visitEndCall_HasArgumentList(const expression::Call& begin, const expression::ArgumentList& end) { }

void Visitor::visitCall_RefersTo(const expression::Call& begin, const statement::CompoundStatement& end) { }

void Visitor::visitEndCall_RefersTo(const expression::Call& begin, const statement::CompoundStatement& end) { }

void Visitor::visitDictComp_HasKeyValue(const expression::DictComp& begin, const expression::KeyValue& end) { }

void Visitor::visitEndDictComp_HasKeyValue(const expression::DictComp& begin, const expression::KeyValue& end) { }

void Visitor::visitDictComp_HasGenerator(const expression::DictComp& begin, const expression::Generator& end) { }

void Visitor::visitEndDictComp_HasGenerator(const expression::DictComp& begin, const expression::Generator& end) { }

void Visitor::visitDictionary_HasKeyValue(const expression::Dictionary& begin, const expression::KeyValue& end) { }

void Visitor::visitEndDictionary_HasKeyValue(const expression::Dictionary& begin, const expression::KeyValue& end) { }

void Visitor::visitExpression_HasType(const expression::Expression& begin, const type::Type& end) { }

void Visitor::visitEndExpression_HasType(const expression::Expression& begin, const type::Type& end) { }

void Visitor::visitExpressionList_HasExpression(const expression::ExpressionList& begin, const expression::Expression& end) { }

void Visitor::visitEndExpressionList_HasExpression(const expression::ExpressionList& begin, const expression::Expression& end) { }

void Visitor::visitExtSlice_HasItem(const expression::ExtSlice& begin, const expression::Slicing& end) { }

void Visitor::visitEndExtSlice_HasItem(const expression::ExtSlice& begin, const expression::Slicing& end) { }

void Visitor::visitGenerator_HasCondition(const expression::Generator& begin, const expression::Expression& end) { }

void Visitor::visitEndGenerator_HasCondition(const expression::Generator& begin, const expression::Expression& end) { }

void Visitor::visitGenerator_HasIter(const expression::Generator& begin, const expression::Expression& end) { }

void Visitor::visitEndGenerator_HasIter(const expression::Generator& begin, const expression::Expression& end) { }

void Visitor::visitGenerator_HasTarget(const expression::Generator& begin, const expression::Expression& end) { }

void Visitor::visitEndGenerator_HasTarget(const expression::Generator& begin, const expression::Expression& end) { }

void Visitor::visitGeneratorExpression_HasExpression(const expression::GeneratorExpression& begin, const expression::Expression& end) { }

void Visitor::visitEndGeneratorExpression_HasExpression(const expression::GeneratorExpression& begin, const expression::Expression& end) { }

void Visitor::visitGeneratorExpression_HasGenerator(const expression::GeneratorExpression& begin, const expression::Generator& end) { }

void Visitor::visitEndGeneratorExpression_HasGenerator(const expression::GeneratorExpression& begin, const expression::Generator& end) { }

void Visitor::visitIdentifier_RefersTo(const expression::Identifier& begin, const module::Object& end) { }

void Visitor::visitEndIdentifier_RefersTo(const expression::Identifier& begin, const module::Object& end) { }

void Visitor::visitIfExpression_HasBody(const expression::IfExpression& begin, const expression::Expression& end) { }

void Visitor::visitEndIfExpression_HasBody(const expression::IfExpression& begin, const expression::Expression& end) { }

void Visitor::visitIfExpression_HasElseBody(const expression::IfExpression& begin, const expression::Expression& end) { }

void Visitor::visitEndIfExpression_HasElseBody(const expression::IfExpression& begin, const expression::Expression& end) { }

void Visitor::visitIfExpression_HasTest(const expression::IfExpression& begin, const expression::Expression& end) { }

void Visitor::visitEndIfExpression_HasTest(const expression::IfExpression& begin, const expression::Expression& end) { }

void Visitor::visitKeyValue_HasKey(const expression::KeyValue& begin, const expression::Expression& end) { }

void Visitor::visitEndKeyValue_HasKey(const expression::KeyValue& begin, const expression::Expression& end) { }

void Visitor::visitKeyValue_HasValue(const expression::KeyValue& begin, const expression::Expression& end) { }

void Visitor::visitEndKeyValue_HasValue(const expression::KeyValue& begin, const expression::Expression& end) { }

void Visitor::visitKeyword_HasKey(const expression::Keyword& begin, const expression::Identifier& end) { }

void Visitor::visitEndKeyword_HasKey(const expression::Keyword& begin, const expression::Identifier& end) { }

void Visitor::visitKeyword_HasValue(const expression::Keyword& begin, const expression::Expression& end) { }

void Visitor::visitEndKeyword_HasValue(const expression::Keyword& begin, const expression::Expression& end) { }

void Visitor::visitLambda_HasObject(const expression::Lambda& begin, const module::Object& end) { }

void Visitor::visitEndLambda_HasObject(const expression::Lambda& begin, const module::Object& end) { }

void Visitor::visitLambda_HasParameter(const expression::Lambda& begin, const statement::Parameter& end) { }

void Visitor::visitEndLambda_HasParameter(const expression::Lambda& begin, const statement::Parameter& end) { }

void Visitor::visitLambda_HasExpression(const expression::Lambda& begin, const expression::Expression& end) { }

void Visitor::visitEndLambda_HasExpression(const expression::Lambda& begin, const expression::Expression& end) { }

void Visitor::visitList_HasExpression(const expression::List& begin, const expression::Expression& end) { }

void Visitor::visitEndList_HasExpression(const expression::List& begin, const expression::Expression& end) { }

void Visitor::visitListComp_HasExpression(const expression::ListComp& begin, const expression::Expression& end) { }

void Visitor::visitEndListComp_HasExpression(const expression::ListComp& begin, const expression::Expression& end) { }

void Visitor::visitListComp_HasGenerator(const expression::ListComp& begin, const expression::Generator& end) { }

void Visitor::visitEndListComp_HasGenerator(const expression::ListComp& begin, const expression::Generator& end) { }

void Visitor::visitSet_HasExpression(const expression::Set& begin, const expression::Expression& end) { }

void Visitor::visitEndSet_HasExpression(const expression::Set& begin, const expression::Expression& end) { }

void Visitor::visitSetComp_HasExpression(const expression::SetComp& begin, const expression::Expression& end) { }

void Visitor::visitEndSetComp_HasExpression(const expression::SetComp& begin, const expression::Expression& end) { }

void Visitor::visitSetComp_HasGenerator(const expression::SetComp& begin, const expression::Generator& end) { }

void Visitor::visitEndSetComp_HasGenerator(const expression::SetComp& begin, const expression::Generator& end) { }

void Visitor::visitSlice_HasLowerBound(const expression::Slice& begin, const expression::Expression& end) { }

void Visitor::visitEndSlice_HasLowerBound(const expression::Slice& begin, const expression::Expression& end) { }

void Visitor::visitSlice_HasStride(const expression::Slice& begin, const expression::Expression& end) { }

void Visitor::visitEndSlice_HasStride(const expression::Slice& begin, const expression::Expression& end) { }

void Visitor::visitSlice_HasUpperBound(const expression::Slice& begin, const expression::Expression& end) { }

void Visitor::visitEndSlice_HasUpperBound(const expression::Slice& begin, const expression::Expression& end) { }

void Visitor::visitStringConversion_HasExpressionList(const expression::StringConversion& begin, const expression::ExpressionList& end) { }

void Visitor::visitEndStringConversion_HasExpressionList(const expression::StringConversion& begin, const expression::ExpressionList& end) { }

void Visitor::visitSubscription_HasSlicing(const expression::Subscription& begin, const expression::Slicing& end) { }

void Visitor::visitEndSubscription_HasSlicing(const expression::Subscription& begin, const expression::Slicing& end) { }

void Visitor::visitUnary_HasExpression(const expression::Unary& begin, const expression::Expression& end) { }

void Visitor::visitEndUnary_HasExpression(const expression::Unary& begin, const expression::Expression& end) { }

void Visitor::visitYieldExpression_HasYieldExpression(const expression::YieldExpression& begin, const expression::ExpressionList& end) { }

void Visitor::visitEndYieldExpression_HasYieldExpression(const expression::YieldExpression& begin, const expression::ExpressionList& end) { }

void Visitor::visitModule_HasObject(const module::Module& begin, const module::Object& end) { }

void Visitor::visitEndModule_HasObject(const module::Module& begin, const module::Object& end) { }

void Visitor::visitModule_HasStatement(const module::Module& begin, const base::Positioned& end) { }

void Visitor::visitEndModule_HasStatement(const module::Module& begin, const base::Positioned& end) { }

void Visitor::visitModule_Docstring(const module::Module& begin, const base::Docstring& end) { }

void Visitor::visitEndModule_Docstring(const module::Module& begin, const base::Docstring& end) { }

void Visitor::visitObject_RefersTo(const module::Object& begin, const base::Positioned& end) { }

void Visitor::visitEndObject_RefersTo(const module::Object& begin, const base::Positioned& end) { }

void Visitor::visitObject_HasType(const module::Object& begin, const type::Type& end) { }

void Visitor::visitEndObject_HasType(const module::Object& begin, const type::Type& end) { }

void Visitor::visitPackage_HasModule(const module::Package& begin, const module::Module& end) { }

void Visitor::visitEndPackage_HasModule(const module::Package& begin, const module::Module& end) { }

void Visitor::visitPackage_HasPackage(const module::Package& begin, const module::Package& end) { }

void Visitor::visitEndPackage_HasPackage(const module::Package& begin, const module::Package& end) { }

void Visitor::visitAlias_RefersTo(const statement::Alias& begin, const base::Base& end) { }

void Visitor::visitEndAlias_RefersTo(const statement::Alias& begin, const base::Base& end) { }

void Visitor::visitAssert_HasMsgExpression(const statement::Assert& begin, const expression::Expression& end) { }

void Visitor::visitEndAssert_HasMsgExpression(const statement::Assert& begin, const expression::Expression& end) { }

void Visitor::visitAssert_HasTestExpression(const statement::Assert& begin, const expression::Expression& end) { }

void Visitor::visitEndAssert_HasTestExpression(const statement::Assert& begin, const expression::Expression& end) { }

void Visitor::visitAssign_HasExpression(const statement::Assign& begin, const expression::Expression& end) { }

void Visitor::visitEndAssign_HasExpression(const statement::Assign& begin, const expression::Expression& end) { }

void Visitor::visitAssign_HasTargetList(const statement::Assign& begin, const statement::TargetList& end) { }

void Visitor::visitEndAssign_HasTargetList(const statement::Assign& begin, const statement::TargetList& end) { }

void Visitor::visitBaseSpecifier_HasName(const statement::BaseSpecifier& begin, const expression::Expression& end) { }

void Visitor::visitEndBaseSpecifier_HasName(const statement::BaseSpecifier& begin, const expression::Expression& end) { }

void Visitor::visitBaseSpecifier_DerivesFrom(const statement::BaseSpecifier& begin, const statement::ClassDef& end) { }

void Visitor::visitEndBaseSpecifier_DerivesFrom(const statement::BaseSpecifier& begin, const statement::ClassDef& end) { }

void Visitor::visitClassDef_HasObject(const statement::ClassDef& begin, const module::Object& end) { }

void Visitor::visitEndClassDef_HasObject(const statement::ClassDef& begin, const module::Object& end) { }

void Visitor::visitClassDef_HasBaseSpecifier(const statement::ClassDef& begin, const statement::BaseSpecifier& end) { }

void Visitor::visitEndClassDef_HasBaseSpecifier(const statement::ClassDef& begin, const statement::BaseSpecifier& end) { }

void Visitor::visitClassDef_HasDecorator(const statement::ClassDef& begin, const expression::Expression& end) { }

void Visitor::visitEndClassDef_HasDecorator(const statement::ClassDef& begin, const expression::Expression& end) { }

void Visitor::visitClassDef_RefersTo(const statement::ClassDef& begin, const module::Object& end) { }

void Visitor::visitEndClassDef_RefersTo(const statement::ClassDef& begin, const module::Object& end) { }

void Visitor::visitClassDef_Docstring(const statement::ClassDef& begin, const base::Docstring& end) { }

void Visitor::visitEndClassDef_Docstring(const statement::ClassDef& begin, const base::Docstring& end) { }

void Visitor::visitCompoundStatement_HasBody(const statement::CompoundStatement& begin, const statement::Suite& end) { }

void Visitor::visitEndCompoundStatement_HasBody(const statement::CompoundStatement& begin, const statement::Suite& end) { }

void Visitor::visitDelete_HasTargetList(const statement::Delete& begin, const statement::TargetList& end) { }

void Visitor::visitEndDelete_HasTargetList(const statement::Delete& begin, const statement::TargetList& end) { }

void Visitor::visitExec_HasExpression(const statement::Exec& begin, const expression::Expression& end) { }

void Visitor::visitEndExec_HasExpression(const statement::Exec& begin, const expression::Expression& end) { }

void Visitor::visitExec_HasGlobals(const statement::Exec& begin, const expression::Expression& end) { }

void Visitor::visitEndExec_HasGlobals(const statement::Exec& begin, const expression::Expression& end) { }

void Visitor::visitExec_HasLocals(const statement::Exec& begin, const expression::Expression& end) { }

void Visitor::visitEndExec_HasLocals(const statement::Exec& begin, const expression::Expression& end) { }

void Visitor::visitFor_HasExpressionList(const statement::For& begin, const expression::ExpressionList& end) { }

void Visitor::visitEndFor_HasExpressionList(const statement::For& begin, const expression::ExpressionList& end) { }

void Visitor::visitFor_HasTargetList(const statement::For& begin, const statement::TargetList& end) { }

void Visitor::visitEndFor_HasTargetList(const statement::For& begin, const statement::TargetList& end) { }

void Visitor::visitFunctionDef_HasDecorator(const statement::FunctionDef& begin, const expression::Expression& end) { }

void Visitor::visitEndFunctionDef_HasDecorator(const statement::FunctionDef& begin, const expression::Expression& end) { }

void Visitor::visitFunctionDef_HasObject(const statement::FunctionDef& begin, const module::Object& end) { }

void Visitor::visitEndFunctionDef_HasObject(const statement::FunctionDef& begin, const module::Object& end) { }

void Visitor::visitFunctionDef_HasParameter(const statement::FunctionDef& begin, const statement::Parameter& end) { }

void Visitor::visitEndFunctionDef_HasParameter(const statement::FunctionDef& begin, const statement::Parameter& end) { }

void Visitor::visitFunctionDef_RefersTo(const statement::FunctionDef& begin, const module::Object& end) { }

void Visitor::visitEndFunctionDef_RefersTo(const statement::FunctionDef& begin, const module::Object& end) { }

void Visitor::visitFunctionDef_ReturnType(const statement::FunctionDef& begin, const type::Type& end) { }

void Visitor::visitEndFunctionDef_ReturnType(const statement::FunctionDef& begin, const type::Type& end) { }

void Visitor::visitFunctionDef_Docstring(const statement::FunctionDef& begin, const base::Docstring& end) { }

void Visitor::visitEndFunctionDef_Docstring(const statement::FunctionDef& begin, const base::Docstring& end) { }

void Visitor::visitGlobal_HasIdentifier(const statement::Global& begin, const expression::Identifier& end) { }

void Visitor::visitEndGlobal_HasIdentifier(const statement::Global& begin, const expression::Identifier& end) { }

void Visitor::visitHandler_HasName(const statement::Handler& begin, const expression::Expression& end) { }

void Visitor::visitEndHandler_HasName(const statement::Handler& begin, const expression::Expression& end) { }

void Visitor::visitHandler_HasExceptBody(const statement::Handler& begin, const statement::Suite& end) { }

void Visitor::visitEndHandler_HasExceptBody(const statement::Handler& begin, const statement::Suite& end) { }

void Visitor::visitHandler_HasType(const statement::Handler& begin, const expression::Expression& end) { }

void Visitor::visitEndHandler_HasType(const statement::Handler& begin, const expression::Expression& end) { }

void Visitor::visitIf_HasElseBody(const statement::If& begin, const statement::Suite& end) { }

void Visitor::visitEndIf_HasElseBody(const statement::If& begin, const statement::Suite& end) { }

void Visitor::visitIf_HasTestExpression(const statement::If& begin, const expression::Expression& end) { }

void Visitor::visitEndIf_HasTestExpression(const statement::If& begin, const expression::Expression& end) { }

void Visitor::visitImportStatement_HasAlias(const statement::ImportStatement& begin, const statement::Alias& end) { }

void Visitor::visitEndImportStatement_HasAlias(const statement::ImportStatement& begin, const statement::Alias& end) { }

void Visitor::visitIteration_HasElseBody(const statement::Iteration& begin, const statement::Suite& end) { }

void Visitor::visitEndIteration_HasElseBody(const statement::Iteration& begin, const statement::Suite& end) { }

void Visitor::visitParameter_HasDefaultValue(const statement::Parameter& begin, const expression::Expression& end) { }

void Visitor::visitEndParameter_HasDefaultValue(const statement::Parameter& begin, const expression::Expression& end) { }

void Visitor::visitParameter_RefersTo(const statement::Parameter& begin, const module::Object& end) { }

void Visitor::visitEndParameter_RefersTo(const statement::Parameter& begin, const module::Object& end) { }

void Visitor::visitPrint_HasExpressionList(const statement::Print& begin, const expression::ExpressionList& end) { }

void Visitor::visitEndPrint_HasExpressionList(const statement::Print& begin, const expression::ExpressionList& end) { }

void Visitor::visitPrint_HasDestination(const statement::Print& begin, const expression::Expression& end) { }

void Visitor::visitEndPrint_HasDestination(const statement::Print& begin, const expression::Expression& end) { }

void Visitor::visitRaise_HasTracebackExpression(const statement::Raise& begin, const expression::Expression& end) { }

void Visitor::visitEndRaise_HasTracebackExpression(const statement::Raise& begin, const expression::Expression& end) { }

void Visitor::visitRaise_HasTypeExpression(const statement::Raise& begin, const expression::Expression& end) { }

void Visitor::visitEndRaise_HasTypeExpression(const statement::Raise& begin, const expression::Expression& end) { }

void Visitor::visitRaise_HasValueExpression(const statement::Raise& begin, const expression::Expression& end) { }

void Visitor::visitEndRaise_HasValueExpression(const statement::Raise& begin, const expression::Expression& end) { }

void Visitor::visitReturn_HasExpression(const statement::Return& begin, const expression::Expression& end) { }

void Visitor::visitEndReturn_HasExpression(const statement::Return& begin, const expression::Expression& end) { }

void Visitor::visitSuite_HasStatement(const statement::Suite& begin, const base::Positioned& end) { }

void Visitor::visitEndSuite_HasStatement(const statement::Suite& begin, const base::Positioned& end) { }

void Visitor::visitTargetList_HasTarget(const statement::TargetList& begin, const expression::Expression& end) { }

void Visitor::visitEndTargetList_HasTarget(const statement::TargetList& begin, const expression::Expression& end) { }

void Visitor::visitTryExcept_HasElseBody(const statement::TryExcept& begin, const statement::Suite& end) { }

void Visitor::visitEndTryExcept_HasElseBody(const statement::TryExcept& begin, const statement::Suite& end) { }

void Visitor::visitTryExcept_HasHandler(const statement::TryExcept& begin, const statement::Handler& end) { }

void Visitor::visitEndTryExcept_HasHandler(const statement::TryExcept& begin, const statement::Handler& end) { }

void Visitor::visitTryExcept_HasFinallyBody(const statement::TryExcept& begin, const statement::Suite& end) { }

void Visitor::visitEndTryExcept_HasFinallyBody(const statement::TryExcept& begin, const statement::Suite& end) { }

void Visitor::visitTryFinal_HasFinallyBody(const statement::TryFinal& begin, const statement::Suite& end) { }

void Visitor::visitEndTryFinal_HasFinallyBody(const statement::TryFinal& begin, const statement::Suite& end) { }

void Visitor::visitWhile_HasTestExpression(const statement::While& begin, const expression::Expression& end) { }

void Visitor::visitEndWhile_HasTestExpression(const statement::While& begin, const expression::Expression& end) { }

void Visitor::visitWith_HasExpression(const statement::With& begin, const expression::Expression& end) { }

void Visitor::visitEndWith_HasExpression(const statement::With& begin, const expression::Expression& end) { }

void Visitor::visitWith_HasTargetList(const statement::With& begin, const statement::TargetList& end) { }

void Visitor::visitEndWith_HasTargetList(const statement::With& begin, const statement::TargetList& end) { }

void Visitor::visitReferenceType_RefersTo(const type::ReferenceType& begin, const base::Positioned& end) { }

void Visitor::visitEndReferenceType_RefersTo(const type::ReferenceType& begin, const base::Positioned& end) { }


}}}
