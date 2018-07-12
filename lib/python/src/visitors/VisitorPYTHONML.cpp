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

using namespace std;


namespace columbus { namespace python { namespace asg {
VisitorPYTHONML::VisitorPYTHONML(std::ofstream& targetStream,
                                 const std::string& _projectName,
                                 bool _noId,
                                 bool _noLineInfo) : ofs(targetStream), noId(_noId), noLineInfo(_noLineInfo), projectName(_projectName)
{
}

VisitorPYTHONML::~VisitorPYTHONML() {
}

void VisitorPYTHONML::beginVisit() {
  ofs << "<?xml version='1.0' encoding=\"utf-8\"?>\n";
  ofs << "<!DOCTYPE Project SYSTEM 'python-1.2.4.dtd'>\n";
  ofs << "<Project name='" << projectName << "'"
      << " xmlns:base='columbus_python_schema/base'"
      << " xmlns:expression='columbus_python_schema/expression'"
      << " xmlns:module='columbus_python_schema/module'"
      << " xmlns:statement='columbus_python_schema/statement'"
      << " xmlns:type='columbus_python_schema/type'"
      << ">\n";
}

void VisitorPYTHONML::finishVisit() {
  ofs << "<Filtered id='id1'/>\n";
  ofs << "</Project>\n";
}

void VisitorPYTHONML::visit(const base::Comment& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<base:Comment";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const base::Comment& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</base:Comment>\n";
}

void VisitorPYTHONML::visit(const base::Docstring& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<base:Docstring";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const base::Docstring& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</base:Docstring>\n";
}

void VisitorPYTHONML::visit(const expression::ArgumentList& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ArgumentList";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::ArgumentList& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ArgumentList>\n";
}

void VisitorPYTHONML::visit(const expression::AttributeRef& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:AttributeRef";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::AttributeRef& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:AttributeRef>\n";
}

void VisitorPYTHONML::visit(const expression::BinaryArithmetic& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:BinaryArithmetic";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::BinaryArithmetic& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:BinaryArithmetic>\n";
}

void VisitorPYTHONML::visit(const expression::BinaryLogical& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:BinaryLogical";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::BinaryLogical& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:BinaryLogical>\n";
}

void VisitorPYTHONML::visit(const expression::Call& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:Call";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::Call& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:Call>\n";
}

void VisitorPYTHONML::visit(const expression::DictComp& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:DictComp";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::DictComp& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:DictComp>\n";
}

void VisitorPYTHONML::visit(const expression::Dictionary& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:Dictionary";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::Dictionary& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:Dictionary>\n";
}

void VisitorPYTHONML::visit(const expression::Ellipsis& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:Ellipsis";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::Ellipsis& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:Ellipsis>\n";
}

void VisitorPYTHONML::visit(const expression::ExpressionList& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ExpressionList";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::ExpressionList& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ExpressionList>\n";
}

void VisitorPYTHONML::visit(const expression::ExtSlice& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ExtSlice";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::ExtSlice& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ExtSlice>\n";
}

void VisitorPYTHONML::visit(const expression::FloatNumber& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:FloatNumber";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::FloatNumber& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:FloatNumber>\n";
}

void VisitorPYTHONML::visit(const expression::Generator& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:Generator";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::Generator& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:Generator>\n";
}

void VisitorPYTHONML::visit(const expression::GeneratorExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:GeneratorExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::GeneratorExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:GeneratorExpression>\n";
}

void VisitorPYTHONML::visit(const expression::Identifier& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:Identifier";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::Identifier& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:Identifier>\n";
}

void VisitorPYTHONML::visit(const expression::IfExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:IfExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::IfExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:IfExpression>\n";
}

void VisitorPYTHONML::visit(const expression::ImagNumber& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ImagNumber";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::ImagNumber& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ImagNumber>\n";
}

void VisitorPYTHONML::visit(const expression::Index& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:Index";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::Index& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:Index>\n";
}

void VisitorPYTHONML::visit(const expression::IntegerLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:IntegerLiteral";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::IntegerLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:IntegerLiteral>\n";
}

void VisitorPYTHONML::visit(const expression::KeyValue& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:KeyValue";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::KeyValue& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:KeyValue>\n";
}

void VisitorPYTHONML::visit(const expression::Keyword& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:Keyword";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::Keyword& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:Keyword>\n";
}

void VisitorPYTHONML::visit(const expression::Lambda& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:Lambda";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::Lambda& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:Lambda>\n";
}

void VisitorPYTHONML::visit(const expression::List& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:List";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::List& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:List>\n";
}

void VisitorPYTHONML::visit(const expression::ListComp& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ListComp";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::ListComp& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ListComp>\n";
}

void VisitorPYTHONML::visit(const expression::LongInteger& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:LongInteger";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::LongInteger& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:LongInteger>\n";
}

void VisitorPYTHONML::visit(const expression::Set& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:Set";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::Set& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:Set>\n";
}

void VisitorPYTHONML::visit(const expression::SetComp& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:SetComp";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::SetComp& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:SetComp>\n";
}

void VisitorPYTHONML::visit(const expression::Slice& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:Slice";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::Slice& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:Slice>\n";
}

void VisitorPYTHONML::visit(const expression::StringConversion& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:StringConversion";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::StringConversion& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:StringConversion>\n";
}

void VisitorPYTHONML::visit(const expression::StringLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:StringLiteral";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::StringLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:StringLiteral>\n";
}

void VisitorPYTHONML::visit(const expression::Subscription& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:Subscription";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::Subscription& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:Subscription>\n";
}

void VisitorPYTHONML::visit(const expression::UnaryOperation& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:UnaryOperation";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::UnaryOperation& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:UnaryOperation>\n";
}

void VisitorPYTHONML::visit(const expression::YieldExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:YieldExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const expression::YieldExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:YieldExpression>\n";
}

void VisitorPYTHONML::visit(const module::Module& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<module:Module";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const module::Module& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</module:Module>\n";
}

void VisitorPYTHONML::visit(const module::Object& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<module:Object";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const module::Object& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</module:Object>\n";
}

void VisitorPYTHONML::visit(const module::Package& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<module:Package";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const module::Package& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</module:Package>\n";
}

void VisitorPYTHONML::visit(const statement::Alias& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:Alias";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::Alias& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:Alias>\n";
}

void VisitorPYTHONML::visit(const statement::Assert& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:Assert";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::Assert& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:Assert>\n";
}

void VisitorPYTHONML::visit(const statement::Assign& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:Assign";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::Assign& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:Assign>\n";
}

void VisitorPYTHONML::visit(const statement::AugAssign& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:AugAssign";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::AugAssign& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:AugAssign>\n";
}

void VisitorPYTHONML::visit(const statement::BaseSpecifier& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:BaseSpecifier";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::BaseSpecifier& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:BaseSpecifier>\n";
}

void VisitorPYTHONML::visit(const statement::Break& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:Break";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::Break& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:Break>\n";
}

void VisitorPYTHONML::visit(const statement::ClassDef& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:ClassDef";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::ClassDef& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:ClassDef>\n";
}

void VisitorPYTHONML::visit(const statement::Continue& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:Continue";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::Continue& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:Continue>\n";
}

void VisitorPYTHONML::visit(const statement::Delete& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:Delete";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::Delete& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:Delete>\n";
}

void VisitorPYTHONML::visit(const statement::Exec& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:Exec";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::Exec& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:Exec>\n";
}

void VisitorPYTHONML::visit(const statement::For& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:For";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::For& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:For>\n";
}

void VisitorPYTHONML::visit(const statement::FunctionDef& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:FunctionDef";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::FunctionDef& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:FunctionDef>\n";
}

void VisitorPYTHONML::visit(const statement::Global& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:Global";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::Global& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:Global>\n";
}

void VisitorPYTHONML::visit(const statement::Handler& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:Handler";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::Handler& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:Handler>\n";
}

void VisitorPYTHONML::visit(const statement::If& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:If";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::If& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:If>\n";
}

void VisitorPYTHONML::visit(const statement::ImportFrom& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:ImportFrom";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::ImportFrom& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:ImportFrom>\n";
}

void VisitorPYTHONML::visit(const statement::ImportStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:ImportStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::ImportStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:ImportStatement>\n";
}

void VisitorPYTHONML::visit(const statement::Parameter& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:Parameter";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::Parameter& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:Parameter>\n";
}

void VisitorPYTHONML::visit(const statement::Pass& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:Pass";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::Pass& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:Pass>\n";
}

void VisitorPYTHONML::visit(const statement::Print& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:Print";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::Print& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:Print>\n";
}

void VisitorPYTHONML::visit(const statement::Raise& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:Raise";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::Raise& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:Raise>\n";
}

void VisitorPYTHONML::visit(const statement::Return& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:Return";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::Return& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:Return>\n";
}

void VisitorPYTHONML::visit(const statement::Suite& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:Suite";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::Suite& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:Suite>\n";
}

void VisitorPYTHONML::visit(const statement::TargetList& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:TargetList";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::TargetList& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:TargetList>\n";
}

void VisitorPYTHONML::visit(const statement::TryExcept& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:TryExcept";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::TryExcept& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:TryExcept>\n";
}

void VisitorPYTHONML::visit(const statement::TryFinal& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:TryFinal";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::TryFinal& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:TryFinal>\n";
}

void VisitorPYTHONML::visit(const statement::While& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:While";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::While& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:While>\n";
}

void VisitorPYTHONML::visit(const statement::With& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:With";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const statement::With& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:With>\n";
}

void VisitorPYTHONML::visit(const type::DictType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:DictType";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const type::DictType& node , bool callVirtualBase) {
}

void VisitorPYTHONML::visit(const type::ReferenceType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:ReferenceType";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const type::ReferenceType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</type:ReferenceType>\n";
}

void VisitorPYTHONML::visit(const type::SequenceType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:SequenceType";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const type::SequenceType& node , bool callVirtualBase) {
}

void VisitorPYTHONML::visit(const type::SimpleType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:SimpleType";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorPYTHONML::visitEnd(const type::SimpleType& node , bool callVirtualBase) {
}

void VisitorPYTHONML::visitPositioned_Comments(const base::Positioned& begin, const base::Comment& end) {
  createIndentation();
  ofs << "<Positioned_Comments ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorPYTHONML::visitEndPositioned_Comments(const base::Positioned& begin, const base::Comment& end) {
}

void VisitorPYTHONML::visitArgumentList_HasPositionalArguments(const expression::ArgumentList& begin, const expression::ExpressionList& end) {
  createIndentation();
  ofs << "<ArgumentList_HasPositionalArguments>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndArgumentList_HasPositionalArguments(const expression::ArgumentList& begin, const expression::ExpressionList& end) {
  decDepth();
  createIndentation();
  ofs << "</ArgumentList_HasPositionalArguments>\n";
}

void VisitorPYTHONML::visitArgumentList_HasDictionary(const expression::ArgumentList& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<ArgumentList_HasDictionary>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndArgumentList_HasDictionary(const expression::ArgumentList& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</ArgumentList_HasDictionary>\n";
}

void VisitorPYTHONML::visitArgumentList_HasKeyword(const expression::ArgumentList& begin, const expression::Keyword& end) {
  createIndentation();
  ofs << "<ArgumentList_HasKeyword>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndArgumentList_HasKeyword(const expression::ArgumentList& begin, const expression::Keyword& end) {
  decDepth();
  createIndentation();
  ofs << "</ArgumentList_HasKeyword>\n";
}

void VisitorPYTHONML::visitArgumentList_HasTuple(const expression::ArgumentList& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<ArgumentList_HasTuple>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndArgumentList_HasTuple(const expression::ArgumentList& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</ArgumentList_HasTuple>\n";
}

void VisitorPYTHONML::visitBinary_HasLeftExpression(const expression::Binary& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Binary_HasLeftExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndBinary_HasLeftExpression(const expression::Binary& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Binary_HasLeftExpression>\n";
}

void VisitorPYTHONML::visitBinary_HasRightExpression(const expression::Binary& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Binary_HasRightExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndBinary_HasRightExpression(const expression::Binary& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Binary_HasRightExpression>\n";
}

void VisitorPYTHONML::visitCall_HasArgumentList(const expression::Call& begin, const expression::ArgumentList& end) {
  createIndentation();
  ofs << "<Call_HasArgumentList>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndCall_HasArgumentList(const expression::Call& begin, const expression::ArgumentList& end) {
  decDepth();
  createIndentation();
  ofs << "</Call_HasArgumentList>\n";
}

void VisitorPYTHONML::visitCall_RefersTo(const expression::Call& begin, const statement::CompoundStatement& end) {
  createIndentation();
  ofs << "<Call_RefersTo ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorPYTHONML::visitEndCall_RefersTo(const expression::Call& begin, const statement::CompoundStatement& end) {
}

void VisitorPYTHONML::visitDictComp_HasKeyValue(const expression::DictComp& begin, const expression::KeyValue& end) {
  createIndentation();
  ofs << "<DictComp_HasKeyValue>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndDictComp_HasKeyValue(const expression::DictComp& begin, const expression::KeyValue& end) {
  decDepth();
  createIndentation();
  ofs << "</DictComp_HasKeyValue>\n";
}

void VisitorPYTHONML::visitDictComp_HasGenerator(const expression::DictComp& begin, const expression::Generator& end) {
  createIndentation();
  ofs << "<DictComp_HasGenerator>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndDictComp_HasGenerator(const expression::DictComp& begin, const expression::Generator& end) {
  decDepth();
  createIndentation();
  ofs << "</DictComp_HasGenerator>\n";
}

void VisitorPYTHONML::visitDictionary_HasKeyValue(const expression::Dictionary& begin, const expression::KeyValue& end) {
  createIndentation();
  ofs << "<Dictionary_HasKeyValue>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndDictionary_HasKeyValue(const expression::Dictionary& begin, const expression::KeyValue& end) {
  decDepth();
  createIndentation();
  ofs << "</Dictionary_HasKeyValue>\n";
}

void VisitorPYTHONML::visitExpression_HasType(const expression::Expression& begin, const type::Type& end) {
  createIndentation();
  ofs << "<Expression_HasType ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorPYTHONML::visitEndExpression_HasType(const expression::Expression& begin, const type::Type& end) {
}

void VisitorPYTHONML::visitExpressionList_HasExpression(const expression::ExpressionList& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<ExpressionList_HasExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndExpressionList_HasExpression(const expression::ExpressionList& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</ExpressionList_HasExpression>\n";
}

void VisitorPYTHONML::visitExtSlice_HasItem(const expression::ExtSlice& begin, const expression::Slicing& end) {
  createIndentation();
  ofs << "<ExtSlice_HasItem>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndExtSlice_HasItem(const expression::ExtSlice& begin, const expression::Slicing& end) {
  decDepth();
  createIndentation();
  ofs << "</ExtSlice_HasItem>\n";
}

void VisitorPYTHONML::visitGenerator_HasCondition(const expression::Generator& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Generator_HasCondition>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndGenerator_HasCondition(const expression::Generator& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Generator_HasCondition>\n";
}

void VisitorPYTHONML::visitGenerator_HasIter(const expression::Generator& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Generator_HasIter>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndGenerator_HasIter(const expression::Generator& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Generator_HasIter>\n";
}

void VisitorPYTHONML::visitGenerator_HasTarget(const expression::Generator& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Generator_HasTarget>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndGenerator_HasTarget(const expression::Generator& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Generator_HasTarget>\n";
}

void VisitorPYTHONML::visitGeneratorExpression_HasExpression(const expression::GeneratorExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<GeneratorExpression_HasExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndGeneratorExpression_HasExpression(const expression::GeneratorExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</GeneratorExpression_HasExpression>\n";
}

void VisitorPYTHONML::visitGeneratorExpression_HasGenerator(const expression::GeneratorExpression& begin, const expression::Generator& end) {
  createIndentation();
  ofs << "<GeneratorExpression_HasGenerator>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndGeneratorExpression_HasGenerator(const expression::GeneratorExpression& begin, const expression::Generator& end) {
  decDepth();
  createIndentation();
  ofs << "</GeneratorExpression_HasGenerator>\n";
}

void VisitorPYTHONML::visitIdentifier_RefersTo(const expression::Identifier& begin, const module::Object& end) {
  createIndentation();
  ofs << "<Identifier_RefersTo ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorPYTHONML::visitEndIdentifier_RefersTo(const expression::Identifier& begin, const module::Object& end) {
}

void VisitorPYTHONML::visitIfExpression_HasBody(const expression::IfExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<IfExpression_HasBody>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndIfExpression_HasBody(const expression::IfExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</IfExpression_HasBody>\n";
}

void VisitorPYTHONML::visitIfExpression_HasElseBody(const expression::IfExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<IfExpression_HasElseBody>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndIfExpression_HasElseBody(const expression::IfExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</IfExpression_HasElseBody>\n";
}

void VisitorPYTHONML::visitIfExpression_HasTest(const expression::IfExpression& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<IfExpression_HasTest>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndIfExpression_HasTest(const expression::IfExpression& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</IfExpression_HasTest>\n";
}

void VisitorPYTHONML::visitKeyValue_HasKey(const expression::KeyValue& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<KeyValue_HasKey>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndKeyValue_HasKey(const expression::KeyValue& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</KeyValue_HasKey>\n";
}

void VisitorPYTHONML::visitKeyValue_HasValue(const expression::KeyValue& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<KeyValue_HasValue>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndKeyValue_HasValue(const expression::KeyValue& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</KeyValue_HasValue>\n";
}

void VisitorPYTHONML::visitKeyword_HasKey(const expression::Keyword& begin, const expression::Identifier& end) {
  createIndentation();
  ofs << "<Keyword_HasKey>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndKeyword_HasKey(const expression::Keyword& begin, const expression::Identifier& end) {
  decDepth();
  createIndentation();
  ofs << "</Keyword_HasKey>\n";
}

void VisitorPYTHONML::visitKeyword_HasValue(const expression::Keyword& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Keyword_HasValue>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndKeyword_HasValue(const expression::Keyword& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Keyword_HasValue>\n";
}

void VisitorPYTHONML::visitLambda_HasObject(const expression::Lambda& begin, const module::Object& end) {
  createIndentation();
  ofs << "<Lambda_HasObject>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndLambda_HasObject(const expression::Lambda& begin, const module::Object& end) {
  decDepth();
  createIndentation();
  ofs << "</Lambda_HasObject>\n";
}

void VisitorPYTHONML::visitLambda_HasParameter(const expression::Lambda& begin, const statement::Parameter& end) {
  createIndentation();
  ofs << "<Lambda_HasParameter>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndLambda_HasParameter(const expression::Lambda& begin, const statement::Parameter& end) {
  decDepth();
  createIndentation();
  ofs << "</Lambda_HasParameter>\n";
}

void VisitorPYTHONML::visitLambda_HasExpression(const expression::Lambda& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Lambda_HasExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndLambda_HasExpression(const expression::Lambda& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Lambda_HasExpression>\n";
}

void VisitorPYTHONML::visitList_HasExpression(const expression::List& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<List_HasExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndList_HasExpression(const expression::List& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</List_HasExpression>\n";
}

void VisitorPYTHONML::visitListComp_HasExpression(const expression::ListComp& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<ListComp_HasExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndListComp_HasExpression(const expression::ListComp& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</ListComp_HasExpression>\n";
}

void VisitorPYTHONML::visitListComp_HasGenerator(const expression::ListComp& begin, const expression::Generator& end) {
  createIndentation();
  ofs << "<ListComp_HasGenerator>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndListComp_HasGenerator(const expression::ListComp& begin, const expression::Generator& end) {
  decDepth();
  createIndentation();
  ofs << "</ListComp_HasGenerator>\n";
}

void VisitorPYTHONML::visitSet_HasExpression(const expression::Set& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Set_HasExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndSet_HasExpression(const expression::Set& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Set_HasExpression>\n";
}

void VisitorPYTHONML::visitSetComp_HasExpression(const expression::SetComp& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<SetComp_HasExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndSetComp_HasExpression(const expression::SetComp& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</SetComp_HasExpression>\n";
}

void VisitorPYTHONML::visitSetComp_HasGenerator(const expression::SetComp& begin, const expression::Generator& end) {
  createIndentation();
  ofs << "<SetComp_HasGenerator>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndSetComp_HasGenerator(const expression::SetComp& begin, const expression::Generator& end) {
  decDepth();
  createIndentation();
  ofs << "</SetComp_HasGenerator>\n";
}

void VisitorPYTHONML::visitSlice_HasLowerBound(const expression::Slice& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Slice_HasLowerBound>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndSlice_HasLowerBound(const expression::Slice& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Slice_HasLowerBound>\n";
}

void VisitorPYTHONML::visitSlice_HasStride(const expression::Slice& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Slice_HasStride>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndSlice_HasStride(const expression::Slice& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Slice_HasStride>\n";
}

void VisitorPYTHONML::visitSlice_HasUpperBound(const expression::Slice& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Slice_HasUpperBound>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndSlice_HasUpperBound(const expression::Slice& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Slice_HasUpperBound>\n";
}

void VisitorPYTHONML::visitStringConversion_HasExpressionList(const expression::StringConversion& begin, const expression::ExpressionList& end) {
  createIndentation();
  ofs << "<StringConversion_HasExpressionList>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndStringConversion_HasExpressionList(const expression::StringConversion& begin, const expression::ExpressionList& end) {
  decDepth();
  createIndentation();
  ofs << "</StringConversion_HasExpressionList>\n";
}

void VisitorPYTHONML::visitSubscription_HasSlicing(const expression::Subscription& begin, const expression::Slicing& end) {
  createIndentation();
  ofs << "<Subscription_HasSlicing>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndSubscription_HasSlicing(const expression::Subscription& begin, const expression::Slicing& end) {
  decDepth();
  createIndentation();
  ofs << "</Subscription_HasSlicing>\n";
}

void VisitorPYTHONML::visitUnary_HasExpression(const expression::Unary& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Unary_HasExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndUnary_HasExpression(const expression::Unary& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Unary_HasExpression>\n";
}

void VisitorPYTHONML::visitYieldExpression_HasYieldExpression(const expression::YieldExpression& begin, const expression::ExpressionList& end) {
  createIndentation();
  ofs << "<YieldExpression_HasYieldExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndYieldExpression_HasYieldExpression(const expression::YieldExpression& begin, const expression::ExpressionList& end) {
  decDepth();
  createIndentation();
  ofs << "</YieldExpression_HasYieldExpression>\n";
}

void VisitorPYTHONML::visitModule_HasObject(const module::Module& begin, const module::Object& end) {
  createIndentation();
  ofs << "<Module_HasObject>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndModule_HasObject(const module::Module& begin, const module::Object& end) {
  decDepth();
  createIndentation();
  ofs << "</Module_HasObject>\n";
}

void VisitorPYTHONML::visitModule_HasStatement(const module::Module& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<Module_HasStatement>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndModule_HasStatement(const module::Module& begin, const base::Positioned& end) {
  decDepth();
  createIndentation();
  ofs << "</Module_HasStatement>\n";
}

void VisitorPYTHONML::visitModule_Docstring(const module::Module& begin, const base::Docstring& end) {
  createIndentation();
  ofs << "<Module_Docstring ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorPYTHONML::visitEndModule_Docstring(const module::Module& begin, const base::Docstring& end) {
}

void VisitorPYTHONML::visitObject_RefersTo(const module::Object& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<Object_RefersTo ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorPYTHONML::visitEndObject_RefersTo(const module::Object& begin, const base::Positioned& end) {
}

void VisitorPYTHONML::visitObject_HasType(const module::Object& begin, const type::Type& end) {
  createIndentation();
  ofs << "<Object_HasType ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorPYTHONML::visitEndObject_HasType(const module::Object& begin, const type::Type& end) {
}

void VisitorPYTHONML::visitPackage_HasModule(const module::Package& begin, const module::Module& end) {
  createIndentation();
  ofs << "<Package_HasModule>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndPackage_HasModule(const module::Package& begin, const module::Module& end) {
  decDepth();
  createIndentation();
  ofs << "</Package_HasModule>\n";
}

void VisitorPYTHONML::visitPackage_HasPackage(const module::Package& begin, const module::Package& end) {
  createIndentation();
  ofs << "<Package_HasPackage>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndPackage_HasPackage(const module::Package& begin, const module::Package& end) {
  decDepth();
  createIndentation();
  ofs << "</Package_HasPackage>\n";
}

void VisitorPYTHONML::visitAlias_RefersTo(const statement::Alias& begin, const base::Base& end) {
  createIndentation();
  ofs << "<Alias_RefersTo ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorPYTHONML::visitEndAlias_RefersTo(const statement::Alias& begin, const base::Base& end) {
}

void VisitorPYTHONML::visitAssert_HasMsgExpression(const statement::Assert& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Assert_HasMsgExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndAssert_HasMsgExpression(const statement::Assert& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Assert_HasMsgExpression>\n";
}

void VisitorPYTHONML::visitAssert_HasTestExpression(const statement::Assert& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Assert_HasTestExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndAssert_HasTestExpression(const statement::Assert& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Assert_HasTestExpression>\n";
}

void VisitorPYTHONML::visitAssign_HasExpression(const statement::Assign& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Assign_HasExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndAssign_HasExpression(const statement::Assign& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Assign_HasExpression>\n";
}

void VisitorPYTHONML::visitAssign_HasTargetList(const statement::Assign& begin, const statement::TargetList& end) {
  createIndentation();
  ofs << "<Assign_HasTargetList>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndAssign_HasTargetList(const statement::Assign& begin, const statement::TargetList& end) {
  decDepth();
  createIndentation();
  ofs << "</Assign_HasTargetList>\n";
}

void VisitorPYTHONML::visitBaseSpecifier_HasName(const statement::BaseSpecifier& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<BaseSpecifier_HasName>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndBaseSpecifier_HasName(const statement::BaseSpecifier& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</BaseSpecifier_HasName>\n";
}

void VisitorPYTHONML::visitBaseSpecifier_DerivesFrom(const statement::BaseSpecifier& begin, const statement::ClassDef& end) {
  createIndentation();
  ofs << "<BaseSpecifier_DerivesFrom ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorPYTHONML::visitEndBaseSpecifier_DerivesFrom(const statement::BaseSpecifier& begin, const statement::ClassDef& end) {
}

void VisitorPYTHONML::visitClassDef_HasObject(const statement::ClassDef& begin, const module::Object& end) {
  createIndentation();
  ofs << "<ClassDef_HasObject>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndClassDef_HasObject(const statement::ClassDef& begin, const module::Object& end) {
  decDepth();
  createIndentation();
  ofs << "</ClassDef_HasObject>\n";
}

void VisitorPYTHONML::visitClassDef_HasBaseSpecifier(const statement::ClassDef& begin, const statement::BaseSpecifier& end) {
  createIndentation();
  ofs << "<ClassDef_HasBaseSpecifier>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndClassDef_HasBaseSpecifier(const statement::ClassDef& begin, const statement::BaseSpecifier& end) {
  decDepth();
  createIndentation();
  ofs << "</ClassDef_HasBaseSpecifier>\n";
}

void VisitorPYTHONML::visitClassDef_HasDecorator(const statement::ClassDef& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<ClassDef_HasDecorator>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndClassDef_HasDecorator(const statement::ClassDef& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</ClassDef_HasDecorator>\n";
}

void VisitorPYTHONML::visitClassDef_RefersTo(const statement::ClassDef& begin, const module::Object& end) {
  createIndentation();
  ofs << "<ClassDef_RefersTo ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorPYTHONML::visitEndClassDef_RefersTo(const statement::ClassDef& begin, const module::Object& end) {
}

void VisitorPYTHONML::visitClassDef_Docstring(const statement::ClassDef& begin, const base::Docstring& end) {
  createIndentation();
  ofs << "<ClassDef_Docstring ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorPYTHONML::visitEndClassDef_Docstring(const statement::ClassDef& begin, const base::Docstring& end) {
}

void VisitorPYTHONML::visitCompoundStatement_HasBody(const statement::CompoundStatement& begin, const statement::Suite& end) {
  createIndentation();
  ofs << "<CompoundStatement_HasBody>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndCompoundStatement_HasBody(const statement::CompoundStatement& begin, const statement::Suite& end) {
  decDepth();
  createIndentation();
  ofs << "</CompoundStatement_HasBody>\n";
}

void VisitorPYTHONML::visitDelete_HasTargetList(const statement::Delete& begin, const statement::TargetList& end) {
  createIndentation();
  ofs << "<Delete_HasTargetList>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndDelete_HasTargetList(const statement::Delete& begin, const statement::TargetList& end) {
  decDepth();
  createIndentation();
  ofs << "</Delete_HasTargetList>\n";
}

void VisitorPYTHONML::visitExec_HasExpression(const statement::Exec& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Exec_HasExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndExec_HasExpression(const statement::Exec& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Exec_HasExpression>\n";
}

void VisitorPYTHONML::visitExec_HasGlobals(const statement::Exec& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Exec_HasGlobals>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndExec_HasGlobals(const statement::Exec& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Exec_HasGlobals>\n";
}

void VisitorPYTHONML::visitExec_HasLocals(const statement::Exec& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Exec_HasLocals>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndExec_HasLocals(const statement::Exec& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Exec_HasLocals>\n";
}

void VisitorPYTHONML::visitFor_HasExpressionList(const statement::For& begin, const expression::ExpressionList& end) {
  createIndentation();
  ofs << "<For_HasExpressionList>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndFor_HasExpressionList(const statement::For& begin, const expression::ExpressionList& end) {
  decDepth();
  createIndentation();
  ofs << "</For_HasExpressionList>\n";
}

void VisitorPYTHONML::visitFor_HasTargetList(const statement::For& begin, const statement::TargetList& end) {
  createIndentation();
  ofs << "<For_HasTargetList>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndFor_HasTargetList(const statement::For& begin, const statement::TargetList& end) {
  decDepth();
  createIndentation();
  ofs << "</For_HasTargetList>\n";
}

void VisitorPYTHONML::visitFunctionDef_HasDecorator(const statement::FunctionDef& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<FunctionDef_HasDecorator>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndFunctionDef_HasDecorator(const statement::FunctionDef& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</FunctionDef_HasDecorator>\n";
}

void VisitorPYTHONML::visitFunctionDef_HasObject(const statement::FunctionDef& begin, const module::Object& end) {
  createIndentation();
  ofs << "<FunctionDef_HasObject>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndFunctionDef_HasObject(const statement::FunctionDef& begin, const module::Object& end) {
  decDepth();
  createIndentation();
  ofs << "</FunctionDef_HasObject>\n";
}

void VisitorPYTHONML::visitFunctionDef_HasParameter(const statement::FunctionDef& begin, const statement::Parameter& end) {
  createIndentation();
  ofs << "<FunctionDef_HasParameter>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndFunctionDef_HasParameter(const statement::FunctionDef& begin, const statement::Parameter& end) {
  decDepth();
  createIndentation();
  ofs << "</FunctionDef_HasParameter>\n";
}

void VisitorPYTHONML::visitFunctionDef_RefersTo(const statement::FunctionDef& begin, const module::Object& end) {
  createIndentation();
  ofs << "<FunctionDef_RefersTo ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorPYTHONML::visitEndFunctionDef_RefersTo(const statement::FunctionDef& begin, const module::Object& end) {
}

void VisitorPYTHONML::visitFunctionDef_ReturnType(const statement::FunctionDef& begin, const type::Type& end) {
  createIndentation();
  ofs << "<FunctionDef_ReturnType ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorPYTHONML::visitEndFunctionDef_ReturnType(const statement::FunctionDef& begin, const type::Type& end) {
}

void VisitorPYTHONML::visitFunctionDef_Docstring(const statement::FunctionDef& begin, const base::Docstring& end) {
  createIndentation();
  ofs << "<FunctionDef_Docstring ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorPYTHONML::visitEndFunctionDef_Docstring(const statement::FunctionDef& begin, const base::Docstring& end) {
}

void VisitorPYTHONML::visitGlobal_HasIdentifier(const statement::Global& begin, const expression::Identifier& end) {
  createIndentation();
  ofs << "<Global_HasIdentifier>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndGlobal_HasIdentifier(const statement::Global& begin, const expression::Identifier& end) {
  decDepth();
  createIndentation();
  ofs << "</Global_HasIdentifier>\n";
}

void VisitorPYTHONML::visitHandler_HasName(const statement::Handler& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Handler_HasName>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndHandler_HasName(const statement::Handler& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Handler_HasName>\n";
}

void VisitorPYTHONML::visitHandler_HasExceptBody(const statement::Handler& begin, const statement::Suite& end) {
  createIndentation();
  ofs << "<Handler_HasExceptBody>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndHandler_HasExceptBody(const statement::Handler& begin, const statement::Suite& end) {
  decDepth();
  createIndentation();
  ofs << "</Handler_HasExceptBody>\n";
}

void VisitorPYTHONML::visitHandler_HasType(const statement::Handler& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Handler_HasType>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndHandler_HasType(const statement::Handler& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Handler_HasType>\n";
}

void VisitorPYTHONML::visitIf_HasElseBody(const statement::If& begin, const statement::Suite& end) {
  createIndentation();
  ofs << "<If_HasElseBody>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndIf_HasElseBody(const statement::If& begin, const statement::Suite& end) {
  decDepth();
  createIndentation();
  ofs << "</If_HasElseBody>\n";
}

void VisitorPYTHONML::visitIf_HasTestExpression(const statement::If& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<If_HasTestExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndIf_HasTestExpression(const statement::If& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</If_HasTestExpression>\n";
}

void VisitorPYTHONML::visitImportStatement_HasAlias(const statement::ImportStatement& begin, const statement::Alias& end) {
  createIndentation();
  ofs << "<ImportStatement_HasAlias>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndImportStatement_HasAlias(const statement::ImportStatement& begin, const statement::Alias& end) {
  decDepth();
  createIndentation();
  ofs << "</ImportStatement_HasAlias>\n";
}

void VisitorPYTHONML::visitIteration_HasElseBody(const statement::Iteration& begin, const statement::Suite& end) {
  createIndentation();
  ofs << "<Iteration_HasElseBody>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndIteration_HasElseBody(const statement::Iteration& begin, const statement::Suite& end) {
  decDepth();
  createIndentation();
  ofs << "</Iteration_HasElseBody>\n";
}

void VisitorPYTHONML::visitParameter_HasDefaultValue(const statement::Parameter& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Parameter_HasDefaultValue>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndParameter_HasDefaultValue(const statement::Parameter& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Parameter_HasDefaultValue>\n";
}

void VisitorPYTHONML::visitParameter_RefersTo(const statement::Parameter& begin, const module::Object& end) {
  createIndentation();
  ofs << "<Parameter_RefersTo ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorPYTHONML::visitEndParameter_RefersTo(const statement::Parameter& begin, const module::Object& end) {
}

void VisitorPYTHONML::visitPrint_HasExpressionList(const statement::Print& begin, const expression::ExpressionList& end) {
  createIndentation();
  ofs << "<Print_HasExpressionList>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndPrint_HasExpressionList(const statement::Print& begin, const expression::ExpressionList& end) {
  decDepth();
  createIndentation();
  ofs << "</Print_HasExpressionList>\n";
}

void VisitorPYTHONML::visitPrint_HasDestination(const statement::Print& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Print_HasDestination>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndPrint_HasDestination(const statement::Print& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Print_HasDestination>\n";
}

void VisitorPYTHONML::visitRaise_HasTracebackExpression(const statement::Raise& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Raise_HasTracebackExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndRaise_HasTracebackExpression(const statement::Raise& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Raise_HasTracebackExpression>\n";
}

void VisitorPYTHONML::visitRaise_HasTypeExpression(const statement::Raise& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Raise_HasTypeExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndRaise_HasTypeExpression(const statement::Raise& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Raise_HasTypeExpression>\n";
}

void VisitorPYTHONML::visitRaise_HasValueExpression(const statement::Raise& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Raise_HasValueExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndRaise_HasValueExpression(const statement::Raise& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Raise_HasValueExpression>\n";
}

void VisitorPYTHONML::visitReturn_HasExpression(const statement::Return& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<Return_HasExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndReturn_HasExpression(const statement::Return& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Return_HasExpression>\n";
}

void VisitorPYTHONML::visitSuite_HasStatement(const statement::Suite& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<Suite_HasStatement>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndSuite_HasStatement(const statement::Suite& begin, const base::Positioned& end) {
  decDepth();
  createIndentation();
  ofs << "</Suite_HasStatement>\n";
}

void VisitorPYTHONML::visitTargetList_HasTarget(const statement::TargetList& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<TargetList_HasTarget>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndTargetList_HasTarget(const statement::TargetList& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</TargetList_HasTarget>\n";
}

void VisitorPYTHONML::visitTryExcept_HasElseBody(const statement::TryExcept& begin, const statement::Suite& end) {
  createIndentation();
  ofs << "<TryExcept_HasElseBody>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndTryExcept_HasElseBody(const statement::TryExcept& begin, const statement::Suite& end) {
  decDepth();
  createIndentation();
  ofs << "</TryExcept_HasElseBody>\n";
}

void VisitorPYTHONML::visitTryExcept_HasHandler(const statement::TryExcept& begin, const statement::Handler& end) {
  createIndentation();
  ofs << "<TryExcept_HasHandler>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndTryExcept_HasHandler(const statement::TryExcept& begin, const statement::Handler& end) {
  decDepth();
  createIndentation();
  ofs << "</TryExcept_HasHandler>\n";
}

void VisitorPYTHONML::visitTryExcept_HasFinallyBody(const statement::TryExcept& begin, const statement::Suite& end) {
  createIndentation();
  ofs << "<TryExcept_HasFinallyBody>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndTryExcept_HasFinallyBody(const statement::TryExcept& begin, const statement::Suite& end) {
  decDepth();
  createIndentation();
  ofs << "</TryExcept_HasFinallyBody>\n";
}

void VisitorPYTHONML::visitTryFinal_HasFinallyBody(const statement::TryFinal& begin, const statement::Suite& end) {
  createIndentation();
  ofs << "<TryFinal_HasFinallyBody>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndTryFinal_HasFinallyBody(const statement::TryFinal& begin, const statement::Suite& end) {
  decDepth();
  createIndentation();
  ofs << "</TryFinal_HasFinallyBody>\n";
}

void VisitorPYTHONML::visitWhile_HasTestExpression(const statement::While& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<While_HasTestExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndWhile_HasTestExpression(const statement::While& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</While_HasTestExpression>\n";
}

void VisitorPYTHONML::visitWith_HasExpression(const statement::With& begin, const expression::Expression& end) {
  createIndentation();
  ofs << "<With_HasExpression>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndWith_HasExpression(const statement::With& begin, const expression::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</With_HasExpression>\n";
}

void VisitorPYTHONML::visitWith_HasTargetList(const statement::With& begin, const statement::TargetList& end) {
  createIndentation();
  ofs << "<With_HasTargetList>\n";
  incDepth();
}

void VisitorPYTHONML::visitEndWith_HasTargetList(const statement::With& begin, const statement::TargetList& end) {
  decDepth();
  createIndentation();
  ofs << "</With_HasTargetList>\n";
}

void VisitorPYTHONML::visitReferenceType_RefersTo(const type::ReferenceType& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<ReferenceType_RefersTo ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorPYTHONML::visitEndReferenceType_RefersTo(const type::ReferenceType& begin, const base::Positioned& end) {
}

void VisitorPYTHONML::createIndentation() {
  if (depth)
    ofs << std::string(depth, '\t');
}

string VisitorPYTHONML::chk(string s) {
  string::size_type pos = (string::size_type)-1;
  while ((pos = s.find("&", pos + 1)) != string::npos)
    s.replace(pos, 1, "&amp;");

  while ((pos = s.find("<", pos + 1)) != string::npos)
    s.replace(pos,1, "&lt;");

  while ((pos = s.find(">", pos + 1)) != string::npos)
    s.replace(pos,1, "&gt;");

  while ((pos = s.find("'", pos + 1)) != string::npos)
    s.replace(pos,1,"&apos;");

  while ((pos = s.find("\"", pos + 1)) != string::npos)
    s.replace(pos,1,"&quot;");

  while ((pos = s.find("\r", pos + 1)) != string::npos)
    s.replace(pos,1, "&#13;");

  while ((pos = s.find("\n", pos + 1)) != string::npos)
    s.replace(pos,1, "&#10;");

  while ((pos = s.find("\t", pos + 1)) != string::npos)
    s.replace(pos,1, "&#09;");

  return s;
}

void VisitorPYTHONML::writeRange(const char *name, const Range &range) {
  if(noLineInfo) return;
  incDepth();
  createIndentation();
  ofs << "<" << name << " path='" << chk(range.getPath()) << "'";
  ofs << " line='" << range.getLine() << "'";
  ofs << " col='" << range.getCol() << "'";
  ofs << " endLine='" << range.getEndLine() << "'";
  ofs << " endCol='" << range.getEndCol() << "'";
  ofs << "/>\n";
  decDepth();
}

void VisitorPYTHONML::writeAttributes(const base::Base& node,bool composite, bool bWithParent /*= true*/ ) {
  if (!composite) {
    ofs << " id='";
    if (!noId)
      ofs << "id" << node.getId();
    ofs << "'";

  }
  if (!composite) {
    ofs << " parent='";
    if (!noId)
      ofs << "id" << (node.getParent() ? node.getParent()->getId() : 0);
    ofs << "'";

  }
  if (!composite) {
  }
  if (!composite) {
    ofs << " originKind='" << Common::toString(node.getOriginKind()) << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const base::Comment& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

  if (!composite) {
    ofs << " text='" << chk(node.getText()) << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const base::Docstring& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

  if (!composite) {
    ofs << " text='" << chk(node.getText()) << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const base::Named& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

  if (!composite) {
    ofs << " name='" << chk(node.getName()) << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const base::Positioned& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Base&)node,composite,false);

  if (composite) {
    writeRange("Position", node.getPosition());
  }
}

void VisitorPYTHONML::writeAttributes(const expression::ArgumentList& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::AttributeRef& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Binary&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::Binary& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::BinaryArithmetic& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Binary&)node,composite,false);

  if (!composite) {
    ofs << " kind='" << Common::toString(node.getKind()) << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const expression::BinaryLogical& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Binary&)node,composite,false);

  if (!composite) {
    ofs << " kind='" << Common::toString(node.getKind()) << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const expression::Call& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Unary&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::DictComp& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::Dictionary& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::Ellipsis& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Slicing&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::Expression& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::ExpressionList& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Expression&)node,composite,false);

  if (!composite) {
    ofs << " isYieldExpression='" << (node.getIsYieldExpression() ? "true" : "false") << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const expression::ExtSlice& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Slicing&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::FloatNumber& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Literal&)node,composite,false);

  if (!composite) {
    ofs << " value='" << node.getValue() << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const expression::Generator& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::GeneratorExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::Identifier& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Expression&)node,composite,false);

  if (!composite) {
    ofs << " name='" << chk(node.getName()) << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const expression::IfExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::ImagNumber& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Literal&)node,composite,false);

  if (!composite) {
    ofs << " im='" << node.getIm() << "'";
  }
  if (!composite) {
    ofs << " real='" << node.getReal() << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const expression::Index& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Slicing&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::IntegerLiteral& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Literal&)node,composite,false);

  if (!composite) {
    ofs << " value='" << node.getValue() << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const expression::KeyValue& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::Keyword& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::Lambda& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::List& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Expression&)node,composite,false);

  if (!composite) {
    ofs << " isTuple='" << (node.getIsTuple() ? "true" : "false") << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const expression::ListComp& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::Literal& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::LongInteger& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Literal&)node,composite,false);

  if (!composite) {
    ofs << " value='" << node.getValue() << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const expression::Set& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::SetComp& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::Slice& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Slicing&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::Slicing& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Unary&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::StringConversion& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::StringLiteral& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Literal&)node,composite,false);

  if (!composite) {
    ofs << " value='" << chk(node.getValue()) << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const expression::Subscription& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Unary&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::Unary& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const expression::UnaryOperation& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Unary&)node,composite,false);

  if (!composite) {
    ofs << " kind='" << Common::toString(node.getKind()) << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const expression::YieldExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::Expression&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const module::Module& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Named&)node,composite,false);

  if (!composite) {
    ofs << " lloc='" << node.getLloc() << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const module::Object& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Base&)node,composite,false);

  if (!composite) {
    ofs << " name='" << chk(node.getName()) << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const module::Package& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Base&)node,composite,false);

  if (!composite) {
    ofs << " name='" << chk(node.getName()) << "'";
  }
  if (!composite) {
    ofs << " path='" << chk(node.getPath()) << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const statement::Alias& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Named&)node,composite,false);

  if (!composite) {
    ofs << " alias='" << chk(node.getAlias()) << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const statement::Assert& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::SimpleStatement&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::Assign& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::SimpleStatement&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::AugAssign& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::Assign&)node,composite,false);

  if (!composite) {
    ofs << " kind='" << Common::toString(node.getKind()) << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const statement::BaseSpecifier& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::Break& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::SimpleStatement&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::ClassDef& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::CompoundStatement&)node,composite,false);

  if (!composite) {
    ofs << " name='" << chk(node.getName()) << "'";
  }
  if (!composite) {
    ofs << " lloc='" << node.getLloc() << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const statement::CompoundStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::Continue& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::SimpleStatement&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::Delete& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::SimpleStatement&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::Exec& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::SimpleStatement&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::For& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::Iteration&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::FunctionDef& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::CompoundStatement&)node,composite,false);

  if (!composite) {
    ofs << " name='" << chk(node.getName()) << "'";
  }
  if (!composite) {
    ofs << " lloc='" << node.getLloc() << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const statement::Global& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::SimpleStatement&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::Handler& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::If& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::CompoundStatement&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::ImportFrom& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::ImportStatement&)node,composite,false);

  if (!composite) {
    ofs << " modulname='" << chk(node.getModulname()) << "'";
  }
  if (!composite) {
    ofs << " level='" << node.getLevel() << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const statement::ImportStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::SimpleStatement&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::Iteration& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::CompoundStatement&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::Parameter& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Named&)node,composite,false);

  if (!composite) {
    ofs << " kind='" << Common::toString(node.getKind()) << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const statement::Pass& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::SimpleStatement&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::Print& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::SimpleStatement&)node,composite,false);

  if (!composite) {
    ofs << " nl='" << (node.getNl() ? "true" : "false") << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const statement::Raise& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::SimpleStatement&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::Return& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::SimpleStatement&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::SimpleStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::Statement&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::Statement& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::Suite& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::TargetList& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::Try& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::CompoundStatement&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::TryExcept& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::Try&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::TryFinal& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::Try&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::While& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::Iteration&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const statement::With& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::CompoundStatement&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const type::DictType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::Type&)node,composite,false);

}

void VisitorPYTHONML::writeAttributes(const type::ReferenceType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::Type&)node,composite,false);

  if (!composite) {
    ofs << " name='" << chk(node.getName()) << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const type::SequenceType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::Type&)node,composite,false);

  if (!composite) {
    ofs << " kind='" << Common::toString(node.getKind()) << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const type::SimpleType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::Type&)node,composite,false);

  if (!composite) {
    ofs << " kind='" << Common::toString(node.getKind()) << "'";
  }
}

void VisitorPYTHONML::writeAttributes(const type::Type& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Base&)node,composite,false);

}


}}}
