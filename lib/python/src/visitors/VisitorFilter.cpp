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
VisitorFilter::VisitorFilter(bool filter) : Visitor() ,selector( filter?&Factory::setFilteredThisNodeOnly : &Factory::setNotFilteredThisNodeOnly) {
}

VisitorFilter::~VisitorFilter() {
}

void VisitorFilter::visitEnd(const base::Comment& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const base::Docstring& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ArgumentList& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::AttributeRef& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::BinaryArithmetic& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::BinaryLogical& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::Call& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::DictComp& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::Dictionary& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::Ellipsis& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ExpressionList& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ExtSlice& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::FloatNumber& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::Generator& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::GeneratorExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::Identifier& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::IfExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ImagNumber& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::Index& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::IntegerLiteral& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::KeyValue& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::Keyword& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::Lambda& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::List& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ListComp& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::LongInteger& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::Set& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::SetComp& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::Slice& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::StringConversion& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::StringLiteral& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::Subscription& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::UnaryOperation& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::YieldExpression& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const module::Module& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const module::Object& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const module::Package& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::Alias& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::Assert& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::Assign& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::AugAssign& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::BaseSpecifier& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::Break& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::ClassDef& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::Continue& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::Delete& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::Exec& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::For& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::FunctionDef& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::Global& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::Handler& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::If& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::ImportFrom& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::ImportStatement& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::Parameter& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::Pass& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::Print& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::Raise& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::Return& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::Suite& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::TargetList& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::TryExcept& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::TryFinal& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::While& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::With& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::DictType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::ReferenceType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::SequenceType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::SimpleType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}


}}}
