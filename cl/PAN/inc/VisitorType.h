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

#ifndef __VISITORTYPE_H_
#define __VISITORTYPE_H_

#include <python/inc/python.h>

using namespace columbus;
using namespace columbus::python::asg;

namespace columbus {
enum VisitedType{
  ExpressionsAndInit = 0,
  Assignments = 1,
  ExprAndAtrRef = 2,
  ReturnAndBaseSpec = 3
};

class VisitorType : public VisitorAbstractNodes {
private:
  static std::map< NodeId, std::set<NodeId> > type_set;

  Factory* factory;
  std::list< NodeId > module_scope;
  std::list< NodeId > scope;
  std::string attribute;
  NodeId currentObject;
  VisitedType filter;
  std::set< NodeId > import_resolved;

public:
  VisitorType(Factory* factory, VisitedType filter): factory(factory), filter(filter) {
  };

protected:

  void setType(module::Object& obj, type::Type& type);
  void setType(expression::Expression& obj, type::Type& type);
  void ListAssign(expression::List& target, expression::Expression& value);
  void setAttributeType(const expression::AttributeRef& node, NodeId leftNodeId);
  NodeId getObject(base::Base& current_scope, std::string name, bool create_object = false);
  NodeId findObject(base::Base& base_scope, std::string name, bool top_level_only = false);
  NodeId findObject(const std::string& name, ListIterator<module::Object> lit, ListIterator<module::Object> litEnd);

  void visit(const module::Module& node, bool);
  void visitEnd(const module::Module& node, bool);

  void visit(const module::Package& node, bool);
  void visitEnd(const module::Package& node, bool);

  void visit(const module::Object& node, bool);
  void visitEnd(const module::Object& node, bool);

  void visit(const statement::ClassDef& node, bool);
  void visitEnd(const statement::ClassDef& node, bool);

  void visit(const statement::FunctionDef& node, bool);
  void visitEnd(const statement::FunctionDef& node, bool);

  void visit(const statement::BaseSpecifier& node, bool);
  void visitEnd(const statement::BaseSpecifier& node, bool);

  void visit(const statement::Assign& node, bool);
  void visitEnd(const statement::Assign& node, bool);

  void visit(const statement::Return& node, bool);
  void visitEnd(const statement::Return& node, bool);

  void visit(const statement::TargetList& node, bool);
  void visitEnd(const statement::TargetList& node, bool);

  void visit(const expression::List& node, bool);
  void visitEnd(const expression::List& node, bool);

  void visit(const expression::KeyValue& node, bool);
  void visitEnd(const expression::KeyValue& node, bool);

  void visit(const expression::Generator& node, bool);
  void visitEnd(const expression::Generator& node, bool);

  void visit(const expression::GeneratorExpression& node, bool);
  void visitEnd(const expression::GeneratorExpression& node, bool);

  void visit(const expression::Lambda& node, bool);
  void visitEnd(const expression::Lambda& node, bool);

  void visit(const expression::Keyword& node, bool);
  void visitEnd(const expression::Keyword& node, bool);

  void visit(const expression::BinaryLogical& node, bool);
  void visitEnd(const expression::BinaryLogical& node, bool);

  void visit(const expression::IfExpression& node, bool);
  void visitEnd(const expression::IfExpression& node, bool);

  void visit(const expression::ArgumentList& node, bool);
  void visitEnd(const expression::ArgumentList& node, bool);

  void visit(const expression::StringConversion& node, bool);
  void visitEnd(const expression::StringConversion& node, bool);

  void visit(const expression::UnaryOperation& node, bool);
  void visitEnd(const expression::UnaryOperation& node, bool);

  void visit(const expression::AttributeRef& node, bool);
  void visitEnd(const expression::AttributeRef& node, bool);

  void visit(const expression::Dictionary& node, bool);
  void visitEnd(const expression::Dictionary& node, bool);

  void visit(const expression::Slicing& node, bool);
  void visitEnd(const expression::Slicing& node, bool);

  void visit(const expression::Slice& node, bool);
  void visitEnd(const expression::Slice& node, bool);

  void visit(const expression::BinaryArithmetic& node, bool);
  void visitEnd(const expression::BinaryArithmetic& node, bool);

  void visit(const expression::Identifier& node, bool);
  void visitEnd(const expression::Identifier& node, bool);

  void visit(const expression::ListComp& node, bool);
  void visitEnd(const expression::ListComp& node, bool);

  void visit(const expression::ExpressionList& node, bool);
  void visitEnd(const expression::ExpressionList& node, bool);

  void visit(const expression::Ellipsis& node, bool);
  void visitEnd(const expression::Ellipsis& node, bool);

  void visit(const expression::ExtSlice& node, bool);
  void visitEnd(const expression::ExtSlice& node, bool);

  void visit(const expression::Subscription& node, bool);
  void visitEnd(const expression::Subscription& node, bool);

  void visit(const expression::Call& node, bool);
  void visitEnd(const expression::Call& node, bool);

  void visit(const expression::Index& node, bool);
  void visitEnd(const expression::Index& node, bool);

  void visit(const expression::LongInteger& node, bool);

  void visit(const expression::IntegerLiteral& node, bool);

  void visit(const expression::ImagNumber& node, bool);

  void visit(const expression::FloatNumber& node, bool);

  void visit(const expression::StringLiteral& node, bool);

};
}

#endif