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

#include "python/inc/python.h"


namespace columbus { namespace python { namespace asg {
VisitorAbstractNodes::~VisitorAbstractNodes() { }

void VisitorAbstractNodes::visit   (const base::Base& node , bool callVirtualBase) { }
void VisitorAbstractNodes::visitEnd(const base::Base& node , bool callVirtualBase) { }

void VisitorAbstractNodes::visit(const base::Comment& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::Comment& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const base::Docstring& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::Docstring& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const base::Named& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::Named& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const base::Positioned& node , bool callVirtualBase) {
  visit   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::Positioned& node , bool callVirtualBase) {
  visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ArgumentList& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ArgumentList& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::AttributeRef& node , bool callVirtualBase) {
  visit   ((expression::Binary&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::AttributeRef& node , bool callVirtualBase) {
  visitEnd   ((expression::Binary&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Await& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Await& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Binary& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Binary& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::BinaryArithmetic& node , bool callVirtualBase) {
  visit   ((expression::Binary&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::BinaryArithmetic& node , bool callVirtualBase) {
  visitEnd   ((expression::Binary&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::BinaryLogical& node , bool callVirtualBase) {
  visit   ((expression::Binary&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::BinaryLogical& node , bool callVirtualBase) {
  visitEnd   ((expression::Binary&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::BytesLiteral& node , bool callVirtualBase) {
  visit   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::BytesLiteral& node , bool callVirtualBase) {
  visitEnd   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Call& node , bool callVirtualBase) {
  visit   ((expression::Unary&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Call& node , bool callVirtualBase) {
  visitEnd   ((expression::Unary&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::DictComp& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::DictComp& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Dictionary& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Dictionary& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Ellipsis& node , bool callVirtualBase) {
  visit   ((expression::Slicing&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Ellipsis& node , bool callVirtualBase) {
  visitEnd   ((expression::Slicing&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Expression& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Expression& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ExpressionList& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ExpressionList& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ExtSlice& node , bool callVirtualBase) {
  visit   ((expression::Slicing&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ExtSlice& node , bool callVirtualBase) {
  visitEnd   ((expression::Slicing&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::FloatNumber& node , bool callVirtualBase) {
  visit   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::FloatNumber& node , bool callVirtualBase) {
  visitEnd   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::FormattedValue& node , bool callVirtualBase) {
  visit   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::FormattedValue& node , bool callVirtualBase) {
  visitEnd   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Generator& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Generator& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::GeneratorExpression& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::GeneratorExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Identifier& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Identifier& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::IfExpression& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::IfExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ImagNumber& node , bool callVirtualBase) {
  visit   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ImagNumber& node , bool callVirtualBase) {
  visitEnd   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Index& node , bool callVirtualBase) {
  visit   ((expression::Slicing&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Index& node , bool callVirtualBase) {
  visitEnd   ((expression::Slicing&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::IntegerLiteral& node , bool callVirtualBase) {
  visit   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::IntegerLiteral& node , bool callVirtualBase) {
  visitEnd   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::JoinedStr& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::JoinedStr& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::KeyValue& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::KeyValue& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Keyword& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Keyword& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Lambda& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Lambda& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::List& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::List& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ListComp& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ListComp& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Literal& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Literal& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::LongInteger& node , bool callVirtualBase) {
  visit   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::LongInteger& node , bool callVirtualBase) {
  visitEnd   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::NamedExpr& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::NamedExpr& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Set& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Set& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::SetComp& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::SetComp& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Slice& node , bool callVirtualBase) {
  visit   ((expression::Slicing&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Slice& node , bool callVirtualBase) {
  visitEnd   ((expression::Slicing&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Slicing& node , bool callVirtualBase) {
  visit   ((expression::Unary&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Slicing& node , bool callVirtualBase) {
  visitEnd   ((expression::Unary&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Starred& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Starred& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::StringConversion& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::StringConversion& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::StringLiteral& node , bool callVirtualBase) {
  visit   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::StringLiteral& node , bool callVirtualBase) {
  visitEnd   ((expression::Literal&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Subscription& node , bool callVirtualBase) {
  visit   ((expression::Unary&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Subscription& node , bool callVirtualBase) {
  visitEnd   ((expression::Unary&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::Unary& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::Unary& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::UnaryOperation& node , bool callVirtualBase) {
  visit   ((expression::Unary&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::UnaryOperation& node , bool callVirtualBase) {
  visitEnd   ((expression::Unary&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::YieldExpression& node , bool callVirtualBase) {
  visit   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::YieldExpression& node , bool callVirtualBase) {
  visitEnd   ((expression::Expression&)node,false); 
}

void VisitorAbstractNodes::visit(const module::Module& node , bool callVirtualBase) {
  visit   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const module::Module& node , bool callVirtualBase) {
  visitEnd   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visit(const module::Object& node , bool callVirtualBase) {
  visit   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const module::Object& node , bool callVirtualBase) {
  visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const module::Package& node , bool callVirtualBase) {
  visit   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const module::Package& node , bool callVirtualBase) {
  visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Alias& node , bool callVirtualBase) {
  visit   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Alias& node , bool callVirtualBase) {
  visitEnd   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::AnnAssign& node , bool callVirtualBase) {
  visit   ((statement::Assign&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::AnnAssign& node , bool callVirtualBase) {
  visitEnd   ((statement::Assign&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Assert& node , bool callVirtualBase) {
  visit   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Assert& node , bool callVirtualBase) {
  visitEnd   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Assign& node , bool callVirtualBase) {
  visit   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Assign& node , bool callVirtualBase) {
  visitEnd   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::AugAssign& node , bool callVirtualBase) {
  visit   ((statement::Assign&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::AugAssign& node , bool callVirtualBase) {
  visitEnd   ((statement::Assign&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::BaseSpecifier& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::BaseSpecifier& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Break& node , bool callVirtualBase) {
  visit   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Break& node , bool callVirtualBase) {
  visitEnd   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::ClassDef& node , bool callVirtualBase) {
  visit   ((statement::CompoundStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::ClassDef& node , bool callVirtualBase) {
  visitEnd   ((statement::CompoundStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::CompoundStatement& node , bool callVirtualBase) {
  visit   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::CompoundStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Continue& node , bool callVirtualBase) {
  visit   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Continue& node , bool callVirtualBase) {
  visitEnd   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Delete& node , bool callVirtualBase) {
  visit   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Delete& node , bool callVirtualBase) {
  visitEnd   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Exec& node , bool callVirtualBase) {
  visit   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Exec& node , bool callVirtualBase) {
  visitEnd   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::For& node , bool callVirtualBase) {
  visit   ((statement::Iteration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::For& node , bool callVirtualBase) {
  visitEnd   ((statement::Iteration&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::FunctionDef& node , bool callVirtualBase) {
  visit   ((statement::CompoundStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::FunctionDef& node , bool callVirtualBase) {
  visitEnd   ((statement::CompoundStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Global& node , bool callVirtualBase) {
  visit   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Global& node , bool callVirtualBase) {
  visitEnd   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Handler& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Handler& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::If& node , bool callVirtualBase) {
  visit   ((statement::CompoundStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::If& node , bool callVirtualBase) {
  visitEnd   ((statement::CompoundStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::ImportFrom& node , bool callVirtualBase) {
  visit   ((statement::ImportStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::ImportFrom& node , bool callVirtualBase) {
  visitEnd   ((statement::ImportStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::ImportStatement& node , bool callVirtualBase) {
  visit   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::ImportStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Iteration& node , bool callVirtualBase) {
  visit   ((statement::CompoundStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Iteration& node , bool callVirtualBase) {
  visitEnd   ((statement::CompoundStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Nonlocal& node , bool callVirtualBase) {
  visit   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Nonlocal& node , bool callVirtualBase) {
  visitEnd   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Parameter& node , bool callVirtualBase) {
  visit   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Parameter& node , bool callVirtualBase) {
  visitEnd   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Pass& node , bool callVirtualBase) {
  visit   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Pass& node , bool callVirtualBase) {
  visitEnd   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Print& node , bool callVirtualBase) {
  visit   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Print& node , bool callVirtualBase) {
  visitEnd   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Raise& node , bool callVirtualBase) {
  visit   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Raise& node , bool callVirtualBase) {
  visitEnd   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Return& node , bool callVirtualBase) {
  visit   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Return& node , bool callVirtualBase) {
  visitEnd   ((statement::SimpleStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::SimpleStatement& node , bool callVirtualBase) {
  visit   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::SimpleStatement& node , bool callVirtualBase) {
  visitEnd   ((statement::Statement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Statement& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Statement& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Suite& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Suite& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::TargetList& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::TargetList& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::Try& node , bool callVirtualBase) {
  visit   ((statement::CompoundStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::Try& node , bool callVirtualBase) {
  visitEnd   ((statement::CompoundStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::While& node , bool callVirtualBase) {
  visit   ((statement::Iteration&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::While& node , bool callVirtualBase) {
  visitEnd   ((statement::Iteration&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::With& node , bool callVirtualBase) {
  visit   ((statement::CompoundStatement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::With& node , bool callVirtualBase) {
  visitEnd   ((statement::CompoundStatement&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::WithItem& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::WithItem& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const type::DictType& node , bool callVirtualBase) {
  visit   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::DictType& node , bool callVirtualBase) {
  visitEnd   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visit(const type::ReferenceType& node , bool callVirtualBase) {
  visit   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::ReferenceType& node , bool callVirtualBase) {
  visitEnd   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visit(const type::SequenceType& node , bool callVirtualBase) {
  visit   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::SequenceType& node , bool callVirtualBase) {
  visitEnd   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visit(const type::SimpleType& node , bool callVirtualBase) {
  visit   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::SimpleType& node , bool callVirtualBase) {
  visitEnd   ((type::Type&)node,false); 
}

void VisitorAbstractNodes::visit(const type::Type& node , bool callVirtualBase) {
  visit   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::Type& node , bool callVirtualBase) {
  visitEnd   ((base::Base&)node,false); 
}


}}}
