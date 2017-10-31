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

using namespace std;


namespace columbus { namespace java { namespace asg {
VisitorJAVAML::VisitorJAVAML(std::ofstream& targetStream,
                             const std::string& _projectName,
                             bool _noId,
                             bool _noLineInfo) : ofs(targetStream), noId(_noId), noLineInfo(_noLineInfo), projectName(_projectName)
{
}

VisitorJAVAML::~VisitorJAVAML() {
}

void VisitorJAVAML::beginVisit() {
  ofs << "<?xml version='1.0' encoding=\"utf-8\"?>\n";
  ofs << "<!DOCTYPE Project SYSTEM 'java-2.0.40.dtd'>\n";
  ofs << "<Project name='" << projectName << "'"
      << " xmlns:base='columbus_java_schema/base'"
      << " xmlns:expr='columbus_java_schema/expr'"
      << " xmlns:statm='columbus_java_schema/statm'"
      << " xmlns:struc='columbus_java_schema/struc'"
      << " xmlns:type='columbus_java_schema/type'"
      << ">\n";
}

void VisitorJAVAML::finishVisit() {
  ofs << "<Filtered id='id1'/>\n";
  ofs << "</Project>\n";
}

void VisitorJAVAML::visit(const base::BlockComment& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<base:BlockComment";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const base::BlockComment& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</base:BlockComment>\n";
}

void VisitorJAVAML::visit(const base::JavadocComment& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<base:JavadocComment";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const base::JavadocComment& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</base:JavadocComment>\n";
}

void VisitorJAVAML::visit(const base::LineComment& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<base:LineComment";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const base::LineComment& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</base:LineComment>\n";
}

void VisitorJAVAML::visit(const expr::ArrayAccess& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:ArrayAccess";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::ArrayAccess& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:ArrayAccess>\n";
}

void VisitorJAVAML::visit(const expr::ArrayTypeExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:ArrayTypeExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::ArrayTypeExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:ArrayTypeExpression>\n";
}

void VisitorJAVAML::visit(const expr::Assignment& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:Assignment";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::Assignment& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:Assignment>\n";
}

void VisitorJAVAML::visit(const expr::BooleanLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:BooleanLiteral";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::BooleanLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:BooleanLiteral>\n";
}

void VisitorJAVAML::visit(const expr::CharacterLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:CharacterLiteral";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::CharacterLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:CharacterLiteral>\n";
}

void VisitorJAVAML::visit(const expr::ClassLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:ClassLiteral";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::ClassLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:ClassLiteral>\n";
}

void VisitorJAVAML::visit(const expr::Conditional& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:Conditional";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::Conditional& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:Conditional>\n";
}

void VisitorJAVAML::visit(const expr::DoubleLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:DoubleLiteral";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::DoubleLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:DoubleLiteral>\n";
}

void VisitorJAVAML::visit(const expr::Erroneous& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:Erroneous";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::Erroneous& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:Erroneous>\n";
}

void VisitorJAVAML::visit(const expr::ErroneousTypeExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:ErroneousTypeExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::ErroneousTypeExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:ErroneousTypeExpression>\n";
}

void VisitorJAVAML::visit(const expr::ExternalTypeExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:ExternalTypeExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::ExternalTypeExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:ExternalTypeExpression>\n";
}

void VisitorJAVAML::visit(const expr::FieldAccess& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:FieldAccess";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::FieldAccess& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:FieldAccess>\n";
}

void VisitorJAVAML::visit(const expr::FloatLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:FloatLiteral";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::FloatLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:FloatLiteral>\n";
}

void VisitorJAVAML::visit(const expr::Identifier& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:Identifier";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::Identifier& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:Identifier>\n";
}

void VisitorJAVAML::visit(const expr::InfixExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:InfixExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::InfixExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:InfixExpression>\n";
}

void VisitorJAVAML::visit(const expr::InstanceOf& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:InstanceOf";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::InstanceOf& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:InstanceOf>\n";
}

void VisitorJAVAML::visit(const expr::IntegerLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:IntegerLiteral";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::IntegerLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:IntegerLiteral>\n";
}

void VisitorJAVAML::visit(const expr::LongLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:LongLiteral";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::LongLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:LongLiteral>\n";
}

void VisitorJAVAML::visit(const expr::MarkerAnnotation& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:MarkerAnnotation";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::MarkerAnnotation& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:MarkerAnnotation>\n";
}

void VisitorJAVAML::visit(const expr::MethodInvocation& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:MethodInvocation";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::MethodInvocation& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:MethodInvocation>\n";
}

void VisitorJAVAML::visit(const expr::NewArray& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:NewArray";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::NewArray& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:NewArray>\n";
}

void VisitorJAVAML::visit(const expr::NewClass& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:NewClass";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::NewClass& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:NewClass>\n";
}

void VisitorJAVAML::visit(const expr::NormalAnnotation& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:NormalAnnotation";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::NormalAnnotation& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:NormalAnnotation>\n";
}

void VisitorJAVAML::visit(const expr::NullLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:NullLiteral";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::NullLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:NullLiteral>\n";
}

void VisitorJAVAML::visit(const expr::ParenthesizedExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:ParenthesizedExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::ParenthesizedExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:ParenthesizedExpression>\n";
}

void VisitorJAVAML::visit(const expr::PostfixExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:PostfixExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::PostfixExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:PostfixExpression>\n";
}

void VisitorJAVAML::visit(const expr::PrefixExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:PrefixExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::PrefixExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:PrefixExpression>\n";
}

void VisitorJAVAML::visit(const expr::PrimitiveTypeExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:PrimitiveTypeExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::PrimitiveTypeExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:PrimitiveTypeExpression>\n";
}

void VisitorJAVAML::visit(const expr::QualifiedTypeExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:QualifiedTypeExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::QualifiedTypeExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:QualifiedTypeExpression>\n";
}

void VisitorJAVAML::visit(const expr::SimpleTypeExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:SimpleTypeExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::SimpleTypeExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:SimpleTypeExpression>\n";
}

void VisitorJAVAML::visit(const expr::SingleElementAnnotation& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:SingleElementAnnotation";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::SingleElementAnnotation& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:SingleElementAnnotation>\n";
}

void VisitorJAVAML::visit(const expr::StringLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:StringLiteral";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::StringLiteral& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:StringLiteral>\n";
}

void VisitorJAVAML::visit(const expr::Super& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:Super";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::Super& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:Super>\n";
}

void VisitorJAVAML::visit(const expr::This& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:This";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::This& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:This>\n";
}

void VisitorJAVAML::visit(const expr::TypeApplyExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:TypeApplyExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::TypeApplyExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:TypeApplyExpression>\n";
}

void VisitorJAVAML::visit(const expr::TypeCast& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:TypeCast";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::TypeCast& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:TypeCast>\n";
}

void VisitorJAVAML::visit(const expr::TypeUnionExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:TypeUnionExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::TypeUnionExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:TypeUnionExpression>\n";
}

void VisitorJAVAML::visit(const expr::WildcardExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expr:WildcardExpression";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const expr::WildcardExpression& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expr:WildcardExpression>\n";
}

void VisitorJAVAML::visit(const statm::Assert& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:Assert";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::Assert& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:Assert>\n";
}

void VisitorJAVAML::visit(const statm::BasicFor& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:BasicFor";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::BasicFor& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:BasicFor>\n";
}

void VisitorJAVAML::visit(const statm::Block& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:Block";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::Block& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:Block>\n";
}

void VisitorJAVAML::visit(const statm::Break& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:Break";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::Break& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:Break>\n";
}

void VisitorJAVAML::visit(const statm::Case& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:Case";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::Case& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:Case>\n";
}

void VisitorJAVAML::visit(const statm::Continue& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:Continue";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::Continue& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:Continue>\n";
}

void VisitorJAVAML::visit(const statm::Default& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:Default";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::Default& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:Default>\n";
}

void VisitorJAVAML::visit(const statm::Do& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:Do";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::Do& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:Do>\n";
}

void VisitorJAVAML::visit(const statm::Empty& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:Empty";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::Empty& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:Empty>\n";
}

void VisitorJAVAML::visit(const statm::EnhancedFor& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:EnhancedFor";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::EnhancedFor& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:EnhancedFor>\n";
}

void VisitorJAVAML::visit(const statm::ExpressionStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:ExpressionStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::ExpressionStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:ExpressionStatement>\n";
}

void VisitorJAVAML::visit(const statm::Handler& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:Handler";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::Handler& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:Handler>\n";
}

void VisitorJAVAML::visit(const statm::If& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:If";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::If& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:If>\n";
}

void VisitorJAVAML::visit(const statm::LabeledStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:LabeledStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::LabeledStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:LabeledStatement>\n";
}

void VisitorJAVAML::visit(const statm::Return& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:Return";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::Return& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:Return>\n";
}

void VisitorJAVAML::visit(const statm::Switch& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:Switch";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::Switch& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:Switch>\n";
}

void VisitorJAVAML::visit(const statm::Synchronized& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:Synchronized";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::Synchronized& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:Synchronized>\n";
}

void VisitorJAVAML::visit(const statm::Throw& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:Throw";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::Throw& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:Throw>\n";
}

void VisitorJAVAML::visit(const statm::Try& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:Try";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::Try& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:Try>\n";
}

void VisitorJAVAML::visit(const statm::While& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statm:While";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const statm::While& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statm:While>\n";
}

void VisitorJAVAML::visit(const struc::AnnotationType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:AnnotationType";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::AnnotationType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:AnnotationType>\n";
}

void VisitorJAVAML::visit(const struc::AnnotationTypeElement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:AnnotationTypeElement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::AnnotationTypeElement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:AnnotationTypeElement>\n";
}

void VisitorJAVAML::visit(const struc::AnonymousClass& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:AnonymousClass";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::AnonymousClass& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:AnonymousClass>\n";
}

void VisitorJAVAML::visit(const struc::Class& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:Class";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::Class& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:Class>\n";
}

void VisitorJAVAML::visit(const struc::ClassGeneric& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:ClassGeneric";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::ClassGeneric& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:ClassGeneric>\n";
}

void VisitorJAVAML::visit(const struc::CompilationUnit& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:CompilationUnit";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::CompilationUnit& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:CompilationUnit>\n";
}

void VisitorJAVAML::visit(const struc::Enum& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:Enum";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::Enum& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:Enum>\n";
}

void VisitorJAVAML::visit(const struc::EnumConstant& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:EnumConstant";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::EnumConstant& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:EnumConstant>\n";
}

void VisitorJAVAML::visit(const struc::Import& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:Import";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::Import& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:Import>\n";
}

void VisitorJAVAML::visit(const struc::InstanceInitializerBlock& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:InstanceInitializerBlock";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::InstanceInitializerBlock& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:InstanceInitializerBlock>\n";
}

void VisitorJAVAML::visit(const struc::Interface& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:Interface";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::Interface& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:Interface>\n";
}

void VisitorJAVAML::visit(const struc::InterfaceGeneric& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:InterfaceGeneric";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::InterfaceGeneric& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:InterfaceGeneric>\n";
}

void VisitorJAVAML::visit(const struc::Method& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:Method";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::Method& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:Method>\n";
}

void VisitorJAVAML::visit(const struc::MethodGeneric& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:MethodGeneric";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::MethodGeneric& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:MethodGeneric>\n";
}

void VisitorJAVAML::visit(const struc::Package& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:Package";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::Package& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:Package>\n";
}

void VisitorJAVAML::visit(const struc::PackageDeclaration& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:PackageDeclaration";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::PackageDeclaration& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:PackageDeclaration>\n";
}

void VisitorJAVAML::visit(const struc::Parameter& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:Parameter";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::Parameter& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:Parameter>\n";
}

void VisitorJAVAML::visit(const struc::StaticInitializerBlock& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:StaticInitializerBlock";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::StaticInitializerBlock& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:StaticInitializerBlock>\n";
}

void VisitorJAVAML::visit(const struc::TypeParameter& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:TypeParameter";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::TypeParameter& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:TypeParameter>\n";
}

void VisitorJAVAML::visit(const struc::Variable& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<struc:Variable";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const struc::Variable& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</struc:Variable>\n";
}

void VisitorJAVAML::visit(const type::ArrayType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:ArrayType";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::ArrayType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</type:ArrayType>\n";
}

void VisitorJAVAML::visit(const type::BooleanType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:BooleanType";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::BooleanType& node , bool callVirtualBase) {
}

void VisitorJAVAML::visit(const type::ByteType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:ByteType";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::ByteType& node , bool callVirtualBase) {
}

void VisitorJAVAML::visit(const type::CharType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:CharType";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::CharType& node , bool callVirtualBase) {
}

void VisitorJAVAML::visit(const type::ClassType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:ClassType";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::ClassType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</type:ClassType>\n";
}

void VisitorJAVAML::visit(const type::DoubleType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:DoubleType";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::DoubleType& node , bool callVirtualBase) {
}

void VisitorJAVAML::visit(const type::ErrorType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:ErrorType";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::ErrorType& node , bool callVirtualBase) {
}

void VisitorJAVAML::visit(const type::FloatType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:FloatType";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::FloatType& node , bool callVirtualBase) {
}

void VisitorJAVAML::visit(const type::IntType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:IntType";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::IntType& node , bool callVirtualBase) {
}

void VisitorJAVAML::visit(const type::LongType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:LongType";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::LongType& node , bool callVirtualBase) {
}

void VisitorJAVAML::visit(const type::LowerBoundedWildcardType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:LowerBoundedWildcardType";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::LowerBoundedWildcardType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</type:LowerBoundedWildcardType>\n";
}

void VisitorJAVAML::visit(const type::MethodType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:MethodType";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::MethodType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</type:MethodType>\n";
}

void VisitorJAVAML::visit(const type::NoType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:NoType";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::NoType& node , bool callVirtualBase) {
}

void VisitorJAVAML::visit(const type::NullType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:NullType";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::NullType& node , bool callVirtualBase) {
}

void VisitorJAVAML::visit(const type::PackageType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:PackageType";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::PackageType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</type:PackageType>\n";
}

void VisitorJAVAML::visit(const type::ParameterizedType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:ParameterizedType";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::ParameterizedType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</type:ParameterizedType>\n";
}

void VisitorJAVAML::visit(const type::ShortType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:ShortType";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::ShortType& node , bool callVirtualBase) {
}

void VisitorJAVAML::visit(const type::TypeVariable& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:TypeVariable";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::TypeVariable& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</type:TypeVariable>\n";
}

void VisitorJAVAML::visit(const type::UnboundedWildcardType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:UnboundedWildcardType";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::UnboundedWildcardType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</type:UnboundedWildcardType>\n";
}

void VisitorJAVAML::visit(const type::UnionType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:UnionType";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::UnionType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</type:UnionType>\n";
}

void VisitorJAVAML::visit(const type::UpperBoundedWildcardType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:UpperBoundedWildcardType";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::UpperBoundedWildcardType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</type:UpperBoundedWildcardType>\n";
}

void VisitorJAVAML::visit(const type::VoidType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:VoidType";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorJAVAML::visitEnd(const type::VoidType& node , bool callVirtualBase) {
}

void VisitorJAVAML::visitCommentable_Comments(const base::Commentable& begin, const base::Comment& end) {
  createIndentation();
  ofs << "<Commentable_Comments ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndCommentable_Comments(const base::Commentable& begin, const base::Comment& end) {
}

void VisitorJAVAML::visitAnnotation_HasAnnotationName(const expr::Annotation& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<Annotation_HasAnnotationName>\n";
  incDepth();
}

void VisitorJAVAML::visitEndAnnotation_HasAnnotationName(const expr::Annotation& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</Annotation_HasAnnotationName>\n";
}

void VisitorJAVAML::visitArrayTypeExpression_HasComponentType(const expr::ArrayTypeExpression& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<ArrayTypeExpression_HasComponentType>\n";
  incDepth();
}

void VisitorJAVAML::visitEndArrayTypeExpression_HasComponentType(const expr::ArrayTypeExpression& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</ArrayTypeExpression_HasComponentType>\n";
}

void VisitorJAVAML::visitBinary_HasLeftOperand(const expr::Binary& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<Binary_HasLeftOperand>\n";
  incDepth();
}

void VisitorJAVAML::visitEndBinary_HasLeftOperand(const expr::Binary& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Binary_HasLeftOperand>\n";
}

void VisitorJAVAML::visitBinary_HasRightOperand(const expr::Binary& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<Binary_HasRightOperand>\n";
  incDepth();
}

void VisitorJAVAML::visitEndBinary_HasRightOperand(const expr::Binary& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Binary_HasRightOperand>\n";
}

void VisitorJAVAML::visitClassLiteral_HasComponentType(const expr::ClassLiteral& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<ClassLiteral_HasComponentType>\n";
  incDepth();
}

void VisitorJAVAML::visitEndClassLiteral_HasComponentType(const expr::ClassLiteral& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</ClassLiteral_HasComponentType>\n";
}

void VisitorJAVAML::visitConditional_HasCondition(const expr::Conditional& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<Conditional_HasCondition>\n";
  incDepth();
}

void VisitorJAVAML::visitEndConditional_HasCondition(const expr::Conditional& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Conditional_HasCondition>\n";
}

void VisitorJAVAML::visitConditional_HasTrueExpression(const expr::Conditional& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<Conditional_HasTrueExpression>\n";
  incDepth();
}

void VisitorJAVAML::visitEndConditional_HasTrueExpression(const expr::Conditional& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Conditional_HasTrueExpression>\n";
}

void VisitorJAVAML::visitConditional_HasFalseExpression(const expr::Conditional& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<Conditional_HasFalseExpression>\n";
  incDepth();
}

void VisitorJAVAML::visitEndConditional_HasFalseExpression(const expr::Conditional& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Conditional_HasFalseExpression>\n";
}

void VisitorJAVAML::visitErroneous_HasErrors(const expr::Erroneous& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<Erroneous_HasErrors>\n";
  incDepth();
}

void VisitorJAVAML::visitEndErroneous_HasErrors(const expr::Erroneous& begin, const base::Positioned& end) {
  decDepth();
  createIndentation();
  ofs << "</Erroneous_HasErrors>\n";
}

void VisitorJAVAML::visitErroneousTypeExpression_HasErrors(const expr::ErroneousTypeExpression& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<ErroneousTypeExpression_HasErrors>\n";
  incDepth();
}

void VisitorJAVAML::visitEndErroneousTypeExpression_HasErrors(const expr::ErroneousTypeExpression& begin, const base::Positioned& end) {
  decDepth();
  createIndentation();
  ofs << "</ErroneousTypeExpression_HasErrors>\n";
}

void VisitorJAVAML::visitExpression_Type(const expr::Expression& begin, const type::Type& end) {
  createIndentation();
  ofs << "<Expression_Type ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndExpression_Type(const expr::Expression& begin, const type::Type& end) {
}

void VisitorJAVAML::visitIdentifier_RefersTo(const expr::Identifier& begin, const base::Named& end) {
  createIndentation();
  ofs << "<Identifier_RefersTo ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndIdentifier_RefersTo(const expr::Identifier& begin, const base::Named& end) {
}

void VisitorJAVAML::visitInstanceOf_HasTypeOperand(const expr::InstanceOf& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<InstanceOf_HasTypeOperand>\n";
  incDepth();
}

void VisitorJAVAML::visitEndInstanceOf_HasTypeOperand(const expr::InstanceOf& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</InstanceOf_HasTypeOperand>\n";
}

void VisitorJAVAML::visitMethodInvocation_HasTypeArguments(const expr::MethodInvocation& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<MethodInvocation_HasTypeArguments>\n";
  incDepth();
}

void VisitorJAVAML::visitEndMethodInvocation_HasTypeArguments(const expr::MethodInvocation& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</MethodInvocation_HasTypeArguments>\n";
}

void VisitorJAVAML::visitMethodInvocation_HasArguments(const expr::MethodInvocation& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<MethodInvocation_HasArguments>\n";
  incDepth();
}

void VisitorJAVAML::visitEndMethodInvocation_HasArguments(const expr::MethodInvocation& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</MethodInvocation_HasArguments>\n";
}

void VisitorJAVAML::visitMethodInvocation_Invokes(const expr::MethodInvocation& begin, const struc::MethodDeclaration& end) {
  createIndentation();
  ofs << "<MethodInvocation_Invokes ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndMethodInvocation_Invokes(const expr::MethodInvocation& begin, const struc::MethodDeclaration& end) {
}

void VisitorJAVAML::visitNewArray_HasComponentType(const expr::NewArray& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<NewArray_HasComponentType>\n";
  incDepth();
}

void VisitorJAVAML::visitEndNewArray_HasComponentType(const expr::NewArray& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</NewArray_HasComponentType>\n";
}

void VisitorJAVAML::visitNewArray_HasDimensions(const expr::NewArray& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<NewArray_HasDimensions>\n";
  incDepth();
}

void VisitorJAVAML::visitEndNewArray_HasDimensions(const expr::NewArray& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</NewArray_HasDimensions>\n";
}

void VisitorJAVAML::visitNewArray_HasInitializers(const expr::NewArray& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<NewArray_HasInitializers>\n";
  incDepth();
}

void VisitorJAVAML::visitEndNewArray_HasInitializers(const expr::NewArray& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</NewArray_HasInitializers>\n";
}

void VisitorJAVAML::visitNewClass_HasEnclosingExpression(const expr::NewClass& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<NewClass_HasEnclosingExpression>\n";
  incDepth();
}

void VisitorJAVAML::visitEndNewClass_HasEnclosingExpression(const expr::NewClass& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</NewClass_HasEnclosingExpression>\n";
}

void VisitorJAVAML::visitNewClass_HasTypeArguments(const expr::NewClass& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<NewClass_HasTypeArguments>\n";
  incDepth();
}

void VisitorJAVAML::visitEndNewClass_HasTypeArguments(const expr::NewClass& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</NewClass_HasTypeArguments>\n";
}

void VisitorJAVAML::visitNewClass_HasTypeName(const expr::NewClass& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<NewClass_HasTypeName>\n";
  incDepth();
}

void VisitorJAVAML::visitEndNewClass_HasTypeName(const expr::NewClass& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</NewClass_HasTypeName>\n";
}

void VisitorJAVAML::visitNewClass_HasArguments(const expr::NewClass& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<NewClass_HasArguments>\n";
  incDepth();
}

void VisitorJAVAML::visitEndNewClass_HasArguments(const expr::NewClass& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</NewClass_HasArguments>\n";
}

void VisitorJAVAML::visitNewClass_HasAnonymousClass(const expr::NewClass& begin, const struc::AnonymousClass& end) {
  createIndentation();
  ofs << "<NewClass_HasAnonymousClass>\n";
  incDepth();
}

void VisitorJAVAML::visitEndNewClass_HasAnonymousClass(const expr::NewClass& begin, const struc::AnonymousClass& end) {
  decDepth();
  createIndentation();
  ofs << "</NewClass_HasAnonymousClass>\n";
}

void VisitorJAVAML::visitNewClass_Constructor(const expr::NewClass& begin, const struc::NormalMethod& end) {
  createIndentation();
  ofs << "<NewClass_Constructor ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndNewClass_Constructor(const expr::NewClass& begin, const struc::NormalMethod& end) {
}

void VisitorJAVAML::visitNormalAnnotation_HasArguments(const expr::NormalAnnotation& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<NormalAnnotation_HasArguments>\n";
  incDepth();
}

void VisitorJAVAML::visitEndNormalAnnotation_HasArguments(const expr::NormalAnnotation& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</NormalAnnotation_HasArguments>\n";
}

void VisitorJAVAML::visitQualifiedTypeExpression_HasQualifierType(const expr::QualifiedTypeExpression& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<QualifiedTypeExpression_HasQualifierType>\n";
  incDepth();
}

void VisitorJAVAML::visitEndQualifiedTypeExpression_HasQualifierType(const expr::QualifiedTypeExpression& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</QualifiedTypeExpression_HasQualifierType>\n";
}

void VisitorJAVAML::visitQualifiedTypeExpression_HasSimpleType(const expr::QualifiedTypeExpression& begin, const expr::SimpleTypeExpression& end) {
  createIndentation();
  ofs << "<QualifiedTypeExpression_HasSimpleType>\n";
  incDepth();
}

void VisitorJAVAML::visitEndQualifiedTypeExpression_HasSimpleType(const expr::QualifiedTypeExpression& begin, const expr::SimpleTypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</QualifiedTypeExpression_HasSimpleType>\n";
}

void VisitorJAVAML::visitSingleElementAnnotation_HasArgument(const expr::SingleElementAnnotation& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<SingleElementAnnotation_HasArgument>\n";
  incDepth();
}

void VisitorJAVAML::visitEndSingleElementAnnotation_HasArgument(const expr::SingleElementAnnotation& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</SingleElementAnnotation_HasArgument>\n";
}

void VisitorJAVAML::visitTypeApplyExpression_HasRawType(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<TypeApplyExpression_HasRawType>\n";
  incDepth();
}

void VisitorJAVAML::visitEndTypeApplyExpression_HasRawType(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</TypeApplyExpression_HasRawType>\n";
}

void VisitorJAVAML::visitTypeApplyExpression_HasTypeArguments(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<TypeApplyExpression_HasTypeArguments>\n";
  incDepth();
}

void VisitorJAVAML::visitEndTypeApplyExpression_HasTypeArguments(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</TypeApplyExpression_HasTypeArguments>\n";
}

void VisitorJAVAML::visitTypeCast_HasTypeOperand(const expr::TypeCast& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<TypeCast_HasTypeOperand>\n";
  incDepth();
}

void VisitorJAVAML::visitEndTypeCast_HasTypeOperand(const expr::TypeCast& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</TypeCast_HasTypeOperand>\n";
}

void VisitorJAVAML::visitTypeUnionExpression_HasAlternatives(const expr::TypeUnionExpression& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<TypeUnionExpression_HasAlternatives>\n";
  incDepth();
}

void VisitorJAVAML::visitEndTypeUnionExpression_HasAlternatives(const expr::TypeUnionExpression& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</TypeUnionExpression_HasAlternatives>\n";
}

void VisitorJAVAML::visitUnary_HasOperand(const expr::Unary& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<Unary_HasOperand>\n";
  incDepth();
}

void VisitorJAVAML::visitEndUnary_HasOperand(const expr::Unary& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Unary_HasOperand>\n";
}

void VisitorJAVAML::visitWildcardExpression_HasBound(const expr::WildcardExpression& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<WildcardExpression_HasBound>\n";
  incDepth();
}

void VisitorJAVAML::visitEndWildcardExpression_HasBound(const expr::WildcardExpression& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</WildcardExpression_HasBound>\n";
}

void VisitorJAVAML::visitAssert_HasCondition(const statm::Assert& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<Assert_HasCondition>\n";
  incDepth();
}

void VisitorJAVAML::visitEndAssert_HasCondition(const statm::Assert& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Assert_HasCondition>\n";
}

void VisitorJAVAML::visitAssert_HasDetail(const statm::Assert& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<Assert_HasDetail>\n";
  incDepth();
}

void VisitorJAVAML::visitEndAssert_HasDetail(const statm::Assert& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Assert_HasDetail>\n";
}

void VisitorJAVAML::visitBasicFor_HasInitializers(const statm::BasicFor& begin, const statm::Statement& end) {
  createIndentation();
  ofs << "<BasicFor_HasInitializers>\n";
  incDepth();
}

void VisitorJAVAML::visitEndBasicFor_HasInitializers(const statm::BasicFor& begin, const statm::Statement& end) {
  decDepth();
  createIndentation();
  ofs << "</BasicFor_HasInitializers>\n";
}

void VisitorJAVAML::visitBasicFor_HasCondition(const statm::BasicFor& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<BasicFor_HasCondition>\n";
  incDepth();
}

void VisitorJAVAML::visitEndBasicFor_HasCondition(const statm::BasicFor& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</BasicFor_HasCondition>\n";
}

void VisitorJAVAML::visitBasicFor_HasUpdates(const statm::BasicFor& begin, const statm::Statement& end) {
  createIndentation();
  ofs << "<BasicFor_HasUpdates>\n";
  incDepth();
}

void VisitorJAVAML::visitEndBasicFor_HasUpdates(const statm::BasicFor& begin, const statm::Statement& end) {
  decDepth();
  createIndentation();
  ofs << "</BasicFor_HasUpdates>\n";
}

void VisitorJAVAML::visitBlock_HasStatements(const statm::Block& begin, const statm::Statement& end) {
  createIndentation();
  ofs << "<Block_HasStatements>\n";
  incDepth();
}

void VisitorJAVAML::visitEndBlock_HasStatements(const statm::Block& begin, const statm::Statement& end) {
  decDepth();
  createIndentation();
  ofs << "</Block_HasStatements>\n";
}

void VisitorJAVAML::visitCase_HasExpression(const statm::Case& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<Case_HasExpression>\n";
  incDepth();
}

void VisitorJAVAML::visitEndCase_HasExpression(const statm::Case& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Case_HasExpression>\n";
}

void VisitorJAVAML::visitDo_HasCondition(const statm::Do& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<Do_HasCondition>\n";
  incDepth();
}

void VisitorJAVAML::visitEndDo_HasCondition(const statm::Do& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Do_HasCondition>\n";
}

void VisitorJAVAML::visitEnhancedFor_HasParameter(const statm::EnhancedFor& begin, const struc::Parameter& end) {
  createIndentation();
  ofs << "<EnhancedFor_HasParameter>\n";
  incDepth();
}

void VisitorJAVAML::visitEndEnhancedFor_HasParameter(const statm::EnhancedFor& begin, const struc::Parameter& end) {
  decDepth();
  createIndentation();
  ofs << "</EnhancedFor_HasParameter>\n";
}

void VisitorJAVAML::visitEnhancedFor_HasExpression(const statm::EnhancedFor& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<EnhancedFor_HasExpression>\n";
  incDepth();
}

void VisitorJAVAML::visitEndEnhancedFor_HasExpression(const statm::EnhancedFor& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</EnhancedFor_HasExpression>\n";
}

void VisitorJAVAML::visitExpressionStatement_HasExpression(const statm::ExpressionStatement& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<ExpressionStatement_HasExpression>\n";
  incDepth();
}

void VisitorJAVAML::visitEndExpressionStatement_HasExpression(const statm::ExpressionStatement& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</ExpressionStatement_HasExpression>\n";
}

void VisitorJAVAML::visitHandler_HasParameter(const statm::Handler& begin, const struc::Parameter& end) {
  createIndentation();
  ofs << "<Handler_HasParameter>\n";
  incDepth();
}

void VisitorJAVAML::visitEndHandler_HasParameter(const statm::Handler& begin, const struc::Parameter& end) {
  decDepth();
  createIndentation();
  ofs << "</Handler_HasParameter>\n";
}

void VisitorJAVAML::visitHandler_HasBlock(const statm::Handler& begin, const statm::Block& end) {
  createIndentation();
  ofs << "<Handler_HasBlock>\n";
  incDepth();
}

void VisitorJAVAML::visitEndHandler_HasBlock(const statm::Handler& begin, const statm::Block& end) {
  decDepth();
  createIndentation();
  ofs << "</Handler_HasBlock>\n";
}

void VisitorJAVAML::visitIf_HasSubstatement(const statm::If& begin, const statm::Statement& end) {
  createIndentation();
  ofs << "<If_HasSubstatement>\n";
  incDepth();
}

void VisitorJAVAML::visitEndIf_HasSubstatement(const statm::If& begin, const statm::Statement& end) {
  decDepth();
  createIndentation();
  ofs << "</If_HasSubstatement>\n";
}

void VisitorJAVAML::visitIf_HasFalseSubstatement(const statm::If& begin, const statm::Statement& end) {
  createIndentation();
  ofs << "<If_HasFalseSubstatement>\n";
  incDepth();
}

void VisitorJAVAML::visitEndIf_HasFalseSubstatement(const statm::If& begin, const statm::Statement& end) {
  decDepth();
  createIndentation();
  ofs << "</If_HasFalseSubstatement>\n";
}

void VisitorJAVAML::visitIteration_HasSubstatement(const statm::Iteration& begin, const statm::Statement& end) {
  createIndentation();
  ofs << "<Iteration_HasSubstatement>\n";
  incDepth();
}

void VisitorJAVAML::visitEndIteration_HasSubstatement(const statm::Iteration& begin, const statm::Statement& end) {
  decDepth();
  createIndentation();
  ofs << "</Iteration_HasSubstatement>\n";
}

void VisitorJAVAML::visitJump_Target(const statm::Jump& begin, const statm::Statement& end) {
  createIndentation();
  ofs << "<Jump_Target ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndJump_Target(const statm::Jump& begin, const statm::Statement& end) {
}

void VisitorJAVAML::visitLabeledStatement_HasStatement(const statm::LabeledStatement& begin, const statm::Statement& end) {
  createIndentation();
  ofs << "<LabeledStatement_HasStatement>\n";
  incDepth();
}

void VisitorJAVAML::visitEndLabeledStatement_HasStatement(const statm::LabeledStatement& begin, const statm::Statement& end) {
  decDepth();
  createIndentation();
  ofs << "</LabeledStatement_HasStatement>\n";
}

void VisitorJAVAML::visitReturn_HasExpression(const statm::Return& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<Return_HasExpression>\n";
  incDepth();
}

void VisitorJAVAML::visitEndReturn_HasExpression(const statm::Return& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Return_HasExpression>\n";
}

void VisitorJAVAML::visitSelection_HasCondition(const statm::Selection& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<Selection_HasCondition>\n";
  incDepth();
}

void VisitorJAVAML::visitEndSelection_HasCondition(const statm::Selection& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Selection_HasCondition>\n";
}

void VisitorJAVAML::visitSwitch_HasCases(const statm::Switch& begin, const statm::SwitchLabel& end) {
  createIndentation();
  ofs << "<Switch_HasCases>\n";
  incDepth();
}

void VisitorJAVAML::visitEndSwitch_HasCases(const statm::Switch& begin, const statm::SwitchLabel& end) {
  decDepth();
  createIndentation();
  ofs << "</Switch_HasCases>\n";
}

void VisitorJAVAML::visitSwitchLabel_HasStatements(const statm::SwitchLabel& begin, const statm::Statement& end) {
  createIndentation();
  ofs << "<SwitchLabel_HasStatements>\n";
  incDepth();
}

void VisitorJAVAML::visitEndSwitchLabel_HasStatements(const statm::SwitchLabel& begin, const statm::Statement& end) {
  decDepth();
  createIndentation();
  ofs << "</SwitchLabel_HasStatements>\n";
}

void VisitorJAVAML::visitSynchronized_HasLock(const statm::Synchronized& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<Synchronized_HasLock>\n";
  incDepth();
}

void VisitorJAVAML::visitEndSynchronized_HasLock(const statm::Synchronized& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Synchronized_HasLock>\n";
}

void VisitorJAVAML::visitSynchronized_HasBlock(const statm::Synchronized& begin, const statm::Block& end) {
  createIndentation();
  ofs << "<Synchronized_HasBlock>\n";
  incDepth();
}

void VisitorJAVAML::visitEndSynchronized_HasBlock(const statm::Synchronized& begin, const statm::Block& end) {
  decDepth();
  createIndentation();
  ofs << "</Synchronized_HasBlock>\n";
}

void VisitorJAVAML::visitThrow_HasExpression(const statm::Throw& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<Throw_HasExpression>\n";
  incDepth();
}

void VisitorJAVAML::visitEndThrow_HasExpression(const statm::Throw& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Throw_HasExpression>\n";
}

void VisitorJAVAML::visitTry_HasResources(const statm::Try& begin, const struc::Variable& end) {
  createIndentation();
  ofs << "<Try_HasResources>\n";
  incDepth();
}

void VisitorJAVAML::visitEndTry_HasResources(const statm::Try& begin, const struc::Variable& end) {
  decDepth();
  createIndentation();
  ofs << "</Try_HasResources>\n";
}

void VisitorJAVAML::visitTry_HasBlock(const statm::Try& begin, const statm::Block& end) {
  createIndentation();
  ofs << "<Try_HasBlock>\n";
  incDepth();
}

void VisitorJAVAML::visitEndTry_HasBlock(const statm::Try& begin, const statm::Block& end) {
  decDepth();
  createIndentation();
  ofs << "</Try_HasBlock>\n";
}

void VisitorJAVAML::visitTry_HasHandlers(const statm::Try& begin, const statm::Handler& end) {
  createIndentation();
  ofs << "<Try_HasHandlers>\n";
  incDepth();
}

void VisitorJAVAML::visitEndTry_HasHandlers(const statm::Try& begin, const statm::Handler& end) {
  decDepth();
  createIndentation();
  ofs << "</Try_HasHandlers>\n";
}

void VisitorJAVAML::visitTry_HasFinallyBlock(const statm::Try& begin, const statm::Block& end) {
  createIndentation();
  ofs << "<Try_HasFinallyBlock>\n";
  incDepth();
}

void VisitorJAVAML::visitEndTry_HasFinallyBlock(const statm::Try& begin, const statm::Block& end) {
  decDepth();
  createIndentation();
  ofs << "</Try_HasFinallyBlock>\n";
}

void VisitorJAVAML::visitWhile_HasCondition(const statm::While& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<While_HasCondition>\n";
  incDepth();
}

void VisitorJAVAML::visitEndWhile_HasCondition(const statm::While& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</While_HasCondition>\n";
}

void VisitorJAVAML::visitAnnotatedElement_HasAnnotations(const struc::AnnotatedElement& begin, const expr::Annotation& end) {
  createIndentation();
  ofs << "<AnnotatedElement_HasAnnotations>\n";
  incDepth();
}

void VisitorJAVAML::visitEndAnnotatedElement_HasAnnotations(const struc::AnnotatedElement& begin, const expr::Annotation& end) {
  decDepth();
  createIndentation();
  ofs << "</AnnotatedElement_HasAnnotations>\n";
}

void VisitorJAVAML::visitAnnotationTypeElement_HasDefaultValue(const struc::AnnotationTypeElement& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<AnnotationTypeElement_HasDefaultValue>\n";
  incDepth();
}

void VisitorJAVAML::visitEndAnnotationTypeElement_HasDefaultValue(const struc::AnnotationTypeElement& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</AnnotationTypeElement_HasDefaultValue>\n";
}

void VisitorJAVAML::visitCompilationUnit_HasPackageDeclaration(const struc::CompilationUnit& begin, const struc::PackageDeclaration& end) {
  createIndentation();
  ofs << "<CompilationUnit_HasPackageDeclaration>\n";
  incDepth();
}

void VisitorJAVAML::visitEndCompilationUnit_HasPackageDeclaration(const struc::CompilationUnit& begin, const struc::PackageDeclaration& end) {
  decDepth();
  createIndentation();
  ofs << "</CompilationUnit_HasPackageDeclaration>\n";
}

void VisitorJAVAML::visitCompilationUnit_HasImports(const struc::CompilationUnit& begin, const struc::Import& end) {
  createIndentation();
  ofs << "<CompilationUnit_HasImports>\n";
  incDepth();
}

void VisitorJAVAML::visitEndCompilationUnit_HasImports(const struc::CompilationUnit& begin, const struc::Import& end) {
  decDepth();
  createIndentation();
  ofs << "</CompilationUnit_HasImports>\n";
}

void VisitorJAVAML::visitCompilationUnit_TypeDeclarations(const struc::CompilationUnit& begin, const struc::TypeDeclaration& end) {
  createIndentation();
  ofs << "<CompilationUnit_TypeDeclarations ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndCompilationUnit_TypeDeclarations(const struc::CompilationUnit& begin, const struc::TypeDeclaration& end) {
}

void VisitorJAVAML::visitCompilationUnit_HasOthers(const struc::CompilationUnit& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<CompilationUnit_HasOthers>\n";
  incDepth();
}

void VisitorJAVAML::visitEndCompilationUnit_HasOthers(const struc::CompilationUnit& begin, const base::Positioned& end) {
  decDepth();
  createIndentation();
  ofs << "</CompilationUnit_HasOthers>\n";
}

void VisitorJAVAML::visitEnumConstant_HasNewClass(const struc::EnumConstant& begin, const expr::NewClass& end) {
  createIndentation();
  ofs << "<EnumConstant_HasNewClass>\n";
  incDepth();
}

void VisitorJAVAML::visitEndEnumConstant_HasNewClass(const struc::EnumConstant& begin, const expr::NewClass& end) {
  decDepth();
  createIndentation();
  ofs << "</EnumConstant_HasNewClass>\n";
}

void VisitorJAVAML::visitGenericDeclaration_HasTypeParameters(const struc::GenericDeclaration& begin, const struc::TypeParameter& end) {
  createIndentation();
  ofs << "<GenericDeclaration_HasTypeParameters>\n";
  incDepth();
}

void VisitorJAVAML::visitEndGenericDeclaration_HasTypeParameters(const struc::GenericDeclaration& begin, const struc::TypeParameter& end) {
  decDepth();
  createIndentation();
  ofs << "</GenericDeclaration_HasTypeParameters>\n";
}

void VisitorJAVAML::visitImport_HasTarget(const struc::Import& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<Import_HasTarget>\n";
  incDepth();
}

void VisitorJAVAML::visitEndImport_HasTarget(const struc::Import& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Import_HasTarget>\n";
}

void VisitorJAVAML::visitInitializerBlock_HasBody(const struc::InitializerBlock& begin, const statm::Block& end) {
  createIndentation();
  ofs << "<InitializerBlock_HasBody>\n";
  incDepth();
}

void VisitorJAVAML::visitEndInitializerBlock_HasBody(const struc::InitializerBlock& begin, const statm::Block& end) {
  decDepth();
  createIndentation();
  ofs << "</InitializerBlock_HasBody>\n";
}

void VisitorJAVAML::visitMethodDeclaration_HasReturnType(const struc::MethodDeclaration& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<MethodDeclaration_HasReturnType>\n";
  incDepth();
}

void VisitorJAVAML::visitEndMethodDeclaration_HasReturnType(const struc::MethodDeclaration& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</MethodDeclaration_HasReturnType>\n";
}

void VisitorJAVAML::visitMethodDeclaration_MethodType(const struc::MethodDeclaration& begin, const type::MethodType& end) {
  createIndentation();
  ofs << "<MethodDeclaration_MethodType ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndMethodDeclaration_MethodType(const struc::MethodDeclaration& begin, const type::MethodType& end) {
}

void VisitorJAVAML::visitMethodDeclaration_Overrides(const struc::MethodDeclaration& begin, const struc::MethodDeclaration& end) {
  createIndentation();
  ofs << "<MethodDeclaration_Overrides ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndMethodDeclaration_Overrides(const struc::MethodDeclaration& begin, const struc::MethodDeclaration& end) {
}

void VisitorJAVAML::visitNormalMethod_HasParameters(const struc::NormalMethod& begin, const struc::Parameter& end) {
  createIndentation();
  ofs << "<NormalMethod_HasParameters>\n";
  incDepth();
}

void VisitorJAVAML::visitEndNormalMethod_HasParameters(const struc::NormalMethod& begin, const struc::Parameter& end) {
  decDepth();
  createIndentation();
  ofs << "</NormalMethod_HasParameters>\n";
}

void VisitorJAVAML::visitNormalMethod_HasBody(const struc::NormalMethod& begin, const statm::Block& end) {
  createIndentation();
  ofs << "<NormalMethod_HasBody>\n";
  incDepth();
}

void VisitorJAVAML::visitEndNormalMethod_HasBody(const struc::NormalMethod& begin, const statm::Block& end) {
  decDepth();
  createIndentation();
  ofs << "</NormalMethod_HasBody>\n";
}

void VisitorJAVAML::visitNormalMethod_HasThrownExceptions(const struc::NormalMethod& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<NormalMethod_HasThrownExceptions>\n";
  incDepth();
}

void VisitorJAVAML::visitEndNormalMethod_HasThrownExceptions(const struc::NormalMethod& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</NormalMethod_HasThrownExceptions>\n";
}

void VisitorJAVAML::visitPackage_HasCompilationUnits(const struc::Package& begin, const struc::CompilationUnit& end) {
  createIndentation();
  ofs << "<Package_HasCompilationUnits>\n";
  incDepth();
}

void VisitorJAVAML::visitEndPackage_HasCompilationUnits(const struc::Package& begin, const struc::CompilationUnit& end) {
  decDepth();
  createIndentation();
  ofs << "</Package_HasCompilationUnits>\n";
}

void VisitorJAVAML::visitPackageDeclaration_HasPackageName(const struc::PackageDeclaration& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<PackageDeclaration_HasPackageName>\n";
  incDepth();
}

void VisitorJAVAML::visitEndPackageDeclaration_HasPackageName(const struc::PackageDeclaration& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</PackageDeclaration_HasPackageName>\n";
}

void VisitorJAVAML::visitPackageDeclaration_RefersTo(const struc::PackageDeclaration& begin, const struc::Package& end) {
  createIndentation();
  ofs << "<PackageDeclaration_RefersTo ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndPackageDeclaration_RefersTo(const struc::PackageDeclaration& begin, const struc::Package& end) {
}

void VisitorJAVAML::visitScope_HasMembers(const struc::Scope& begin, const struc::Member& end) {
  createIndentation();
  ofs << "<Scope_HasMembers>\n";
  incDepth();
}

void VisitorJAVAML::visitEndScope_HasMembers(const struc::Scope& begin, const struc::Member& end) {
  decDepth();
  createIndentation();
  ofs << "</Scope_HasMembers>\n";
}

void VisitorJAVAML::visitTypeDeclaration_IsInCompilationUnit(const struc::TypeDeclaration& begin, const struc::CompilationUnit& end) {
  createIndentation();
  ofs << "<TypeDeclaration_IsInCompilationUnit ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndTypeDeclaration_IsInCompilationUnit(const struc::TypeDeclaration& begin, const struc::CompilationUnit& end) {
}

void VisitorJAVAML::visitTypeDeclaration_HasSuperClass(const struc::TypeDeclaration& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<TypeDeclaration_HasSuperClass>\n";
  incDepth();
}

void VisitorJAVAML::visitEndTypeDeclaration_HasSuperClass(const struc::TypeDeclaration& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</TypeDeclaration_HasSuperClass>\n";
}

void VisitorJAVAML::visitTypeDeclaration_HasSuperInterfaces(const struc::TypeDeclaration& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<TypeDeclaration_HasSuperInterfaces>\n";
  incDepth();
}

void VisitorJAVAML::visitEndTypeDeclaration_HasSuperInterfaces(const struc::TypeDeclaration& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</TypeDeclaration_HasSuperInterfaces>\n";
}

void VisitorJAVAML::visitTypeDeclaration_HasOthers(const struc::TypeDeclaration& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<TypeDeclaration_HasOthers>\n";
  incDepth();
}

void VisitorJAVAML::visitEndTypeDeclaration_HasOthers(const struc::TypeDeclaration& begin, const base::Positioned& end) {
  decDepth();
  createIndentation();
  ofs << "</TypeDeclaration_HasOthers>\n";
}

void VisitorJAVAML::visitTypeParameter_HasBounds(const struc::TypeParameter& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<TypeParameter_HasBounds>\n";
  incDepth();
}

void VisitorJAVAML::visitEndTypeParameter_HasBounds(const struc::TypeParameter& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</TypeParameter_HasBounds>\n";
}

void VisitorJAVAML::visitVariable_HasInitialValue(const struc::Variable& begin, const expr::Expression& end) {
  createIndentation();
  ofs << "<Variable_HasInitialValue>\n";
  incDepth();
}

void VisitorJAVAML::visitEndVariable_HasInitialValue(const struc::Variable& begin, const expr::Expression& end) {
  decDepth();
  createIndentation();
  ofs << "</Variable_HasInitialValue>\n";
}

void VisitorJAVAML::visitVariableDeclaration_HasType(const struc::VariableDeclaration& begin, const expr::TypeExpression& end) {
  createIndentation();
  ofs << "<VariableDeclaration_HasType>\n";
  incDepth();
}

void VisitorJAVAML::visitEndVariableDeclaration_HasType(const struc::VariableDeclaration& begin, const expr::TypeExpression& end) {
  decDepth();
  createIndentation();
  ofs << "</VariableDeclaration_HasType>\n";
}

void VisitorJAVAML::visitArrayType_ComponentType(const type::ArrayType& begin, const type::Type& end) {
  createIndentation();
  ofs << "<ArrayType_ComponentType ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndArrayType_ComponentType(const type::ArrayType& begin, const type::Type& end) {
}

void VisitorJAVAML::visitClassType_RefersTo(const type::ClassType& begin, const struc::TypeDeclaration& end) {
  createIndentation();
  ofs << "<ClassType_RefersTo ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndClassType_RefersTo(const type::ClassType& begin, const struc::TypeDeclaration& end) {
}

void VisitorJAVAML::visitMethodType_ReturnType(const type::MethodType& begin, const type::Type& end) {
  createIndentation();
  ofs << "<MethodType_ReturnType ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndMethodType_ReturnType(const type::MethodType& begin, const type::Type& end) {
}

void VisitorJAVAML::visitMethodType_ParameterTypes(const type::MethodType& begin, const type::Type& end) {
  createIndentation();
  ofs << "<MethodType_ParameterTypes ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndMethodType_ParameterTypes(const type::MethodType& begin, const type::Type& end) {
}

void VisitorJAVAML::visitMethodType_ThrownTypes(const type::MethodType& begin, const type::Type& end) {
  createIndentation();
  ofs << "<MethodType_ThrownTypes ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndMethodType_ThrownTypes(const type::MethodType& begin, const type::Type& end) {
}

void VisitorJAVAML::visitPackageType_RefersTo(const type::PackageType& begin, const struc::Package& end) {
  createIndentation();
  ofs << "<PackageType_RefersTo ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndPackageType_RefersTo(const type::PackageType& begin, const struc::Package& end) {
}

void VisitorJAVAML::visitParameterizedType_RawType(const type::ParameterizedType& begin, const type::Type& end) {
  createIndentation();
  ofs << "<ParameterizedType_RawType ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndParameterizedType_RawType(const type::ParameterizedType& begin, const type::Type& end) {
}

void VisitorJAVAML::visitParameterizedType_ArgumentTypes(const type::ParameterizedType& begin, const type::Type& end) {
  createIndentation();
  ofs << "<ParameterizedType_ArgumentTypes ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndParameterizedType_ArgumentTypes(const type::ParameterizedType& begin, const type::Type& end) {
}

void VisitorJAVAML::visitScopedType_Owner(const type::ScopedType& begin, const type::Type& end) {
  createIndentation();
  ofs << "<ScopedType_Owner ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndScopedType_Owner(const type::ScopedType& begin, const type::Type& end) {
}

void VisitorJAVAML::visitTypeVariable_RefersTo(const type::TypeVariable& begin, const struc::TypeParameter& end) {
  createIndentation();
  ofs << "<TypeVariable_RefersTo ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndTypeVariable_RefersTo(const type::TypeVariable& begin, const struc::TypeParameter& end) {
}

void VisitorJAVAML::visitUnionType_Alternatives(const type::UnionType& begin, const type::Type& end) {
  createIndentation();
  ofs << "<UnionType_Alternatives ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndUnionType_Alternatives(const type::UnionType& begin, const type::Type& end) {
}

void VisitorJAVAML::visitWildcardType_Bound(const type::WildcardType& begin, const type::Type& end) {
  createIndentation();
  ofs << "<WildcardType_Bound ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorJAVAML::visitEndWildcardType_Bound(const type::WildcardType& begin, const type::Type& end) {
}

void VisitorJAVAML::createIndentation() {
  if (depth)
    ofs << std::string(depth, '\t');
}

string VisitorJAVAML::chk(string s) {
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

void VisitorJAVAML::writeRange(const char *name, const Range &range) {
  if(noLineInfo) return;
  incDepth();
  createIndentation();
  ofs << "<" << name << " path='" << chk(range.getPath()) << "'";
  ofs << " line='" << range.getLine() << "'";
  ofs << " col='" << range.getCol() << "'";
  ofs << " endLine='" << range.getEndLine() << "'";
  ofs << " endCol='" << range.getEndCol() << "'";
  ofs << " wideLine='" << range.getWideLine() << "'";
  ofs << " wideCol='" << range.getWideCol() << "'";
  ofs << " wideEndLine='" << range.getWideEndLine() << "'";
  ofs << " wideEndCol='" << range.getWideEndCol() << "'";
  ofs << "/>\n";
  decDepth();
}

void VisitorJAVAML::writeAttributes(const base::Base& node,bool composite, bool bWithParent /*= true*/ ) {
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
}

void VisitorJAVAML::writeAttributes(const base::BlockComment& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  writeAttributes((base::NonJavadocComment&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const base::Comment& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  writeAttributes((base::PositionedWithoutComment&)node,composite,false);

  if (!composite) {
    ofs << " text='" << chk(node.getText()) << "'";
  }
}

void VisitorJAVAML::writeAttributes(const base::Commentable& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const base::JavadocComment& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  writeAttributes((base::Comment&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const base::LineComment& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  writeAttributes((base::NonJavadocComment&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const base::Named& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if (!composite) {
    ofs << " name='" << chk(node.getName()) << "'";
  }
  if (composite) {
    writeRange("NamePosition", node.getNamePosition());
  }
}

void VisitorJAVAML::writeAttributes(const base::NonJavadocComment& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  writeAttributes((base::Comment&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const base::Positioned& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((base::PositionedWithoutComment&)node,composite,false);

  if (!composite) {
    ofs << " isCompilerGenerated='" << (node.getIsCompilerGenerated() ? "true" : "false") << "'";
  }
  if (!composite) {
    ofs << " isToolGenerated='" << (node.getIsToolGenerated() ? "true" : "false") << "'";
  }
}

void VisitorJAVAML::writeAttributes(const base::PositionedWithoutComment& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if (composite) {
    writeRange("Position", node.getPosition());
  }
}

void VisitorJAVAML::writeAttributes(const expr::Annotation& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Expression&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::ArrayAccess& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Binary&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::ArrayTypeExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::TypeExpression&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::Assignment& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Binary&)node,composite,false);

  if (!composite) {
    ofs << " operator='" << Common::toString(node.getOperator()) << "'";
  }
}

void VisitorJAVAML::writeAttributes(const expr::Binary& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Expression&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::BooleanLiteral& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Literal&)node,composite,false);

  if (!composite) {
    ofs << " booleanValue='" << (node.getBooleanValue() ? "true" : "false") << "'";
  }
}

void VisitorJAVAML::writeAttributes(const expr::CharacterLiteral& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Literal&)node,composite,false);

  if (!composite) {
    ofs << " charValue='" << node.getCharValue() << "'";
  }
  if (!composite) {
    ofs << " formatString='" << chk(node.getFormatString()) << "'";
  }
}

void VisitorJAVAML::writeAttributes(const expr::ClassLiteral& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Literal&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::Conditional& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Expression&)node,composite,false);

  if (composite) {
    writeRange("ColonPosition", node.getColonPosition());
  }
}

void VisitorJAVAML::writeAttributes(const expr::DoubleLiteral& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::NumberLiteral&)node,composite,false);

  if (!composite) {
    ofs << " doubleValue='" << node.getDoubleValue() << "'";
  }
}

void VisitorJAVAML::writeAttributes(const expr::Erroneous& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Expression&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::ErroneousTypeExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::TypeExpression&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::Expression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::ExternalTypeExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::TypeExpression&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::FieldAccess& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Binary&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::FloatLiteral& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::NumberLiteral&)node,composite,false);

  if (!composite) {
    ofs << " floatValue='" << node.getFloatValue() << "'";
  }
}

void VisitorJAVAML::writeAttributes(const expr::Identifier& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Expression&)node,composite,false);

  if (!composite) {
    ofs << " name='" << chk(node.getName()) << "'";
  }
}

void VisitorJAVAML::writeAttributes(const expr::InfixExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Binary&)node,composite,false);

  if (!composite) {
    ofs << " operator='" << Common::toString(node.getOperator()) << "'";
  }
}

void VisitorJAVAML::writeAttributes(const expr::InstanceOf& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Unary&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::IntegerLiteral& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::NumberLiteral&)node,composite,false);

  if (!composite) {
    ofs << " intValue='" << node.getIntValue() << "'";
  }
}

void VisitorJAVAML::writeAttributes(const expr::Literal& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Expression&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::LongLiteral& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::NumberLiteral&)node,composite,false);

  if (!composite) {
    ofs << " longValue='" << node.getLongValue() << "'";
  }
}

void VisitorJAVAML::writeAttributes(const expr::MarkerAnnotation& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Annotation&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::MethodInvocation& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Unary&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::NewArray& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Expression&)node,composite,false);

  if (composite) {
    writeRange("LeftBracePosition", node.getLeftBracePosition());
  }
}

void VisitorJAVAML::writeAttributes(const expr::NewClass& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Expression&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::NormalAnnotation& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Annotation&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::NullLiteral& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Literal&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::NumberLiteral& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Literal&)node,composite,false);

  if (!composite) {
    ofs << " value='" << chk(node.getValue()) << "'";
  }
}

void VisitorJAVAML::writeAttributes(const expr::ParenthesizedExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Unary&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::PostfixExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Unary&)node,composite,false);

  if (!composite) {
    ofs << " operator='" << Common::toString(node.getOperator()) << "'";
  }
}

void VisitorJAVAML::writeAttributes(const expr::PrefixExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Unary&)node,composite,false);

  if (!composite) {
    ofs << " operator='" << Common::toString(node.getOperator()) << "'";
  }
}

void VisitorJAVAML::writeAttributes(const expr::PrimitiveTypeExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::TypeExpression&)node,composite,false);

  if (!composite) {
    ofs << " kind='" << Common::toString(node.getKind()) << "'";
  }
}

void VisitorJAVAML::writeAttributes(const expr::QualifiedTypeExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::TypeExpression&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::SimpleTypeExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::TypeExpression&)node,composite,false);

  if (!composite) {
    ofs << " name='" << chk(node.getName()) << "'";
  }
}

void VisitorJAVAML::writeAttributes(const expr::SingleElementAnnotation& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Annotation&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::StringLiteral& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Literal&)node,composite,false);

  if (!composite) {
    ofs << " value='" << chk(node.getValue()) << "'";
  }
  if (!composite) {
    ofs << " formatString='" << chk(node.getFormatString()) << "'";
  }
}

void VisitorJAVAML::writeAttributes(const expr::Super& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Expression&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::This& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Expression&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::TypeApplyExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::TypeExpression&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::TypeCast& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Unary&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::TypeExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Expression&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::TypeUnionExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::TypeExpression&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::Unary& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::Expression&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const expr::WildcardExpression& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((expr::TypeExpression&)node,composite,false);

  if (!composite) {
    ofs << " kind='" << Common::toString(node.getKind()) << "'";
  }
}

void VisitorJAVAML::writeAttributes(const statm::Assert& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::Statement&)node,composite,false);

  if (composite) {
    writeRange("ColonPosition", node.getColonPosition());
  }
}

void VisitorJAVAML::writeAttributes(const statm::BasicFor& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::For&)node,composite,false);

  if (composite) {
    writeRange("FirstSemiPosition", node.getFirstSemiPosition());
  }
  if (composite) {
    writeRange("SecondSemiPosition", node.getSecondSemiPosition());
  }
}

void VisitorJAVAML::writeAttributes(const statm::Block& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::Statement&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const statm::Break& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::Jump&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const statm::Case& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::SwitchLabel&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const statm::Continue& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::Jump&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const statm::Default& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::SwitchLabel&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const statm::Do& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::Iteration&)node,composite,false);

  if (composite) {
    writeRange("WhilePosition", node.getWhilePosition());
  }
}

void VisitorJAVAML::writeAttributes(const statm::Empty& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::Statement&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const statm::EnhancedFor& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::For&)node,composite,false);

  if (composite) {
    writeRange("ColonPosition", node.getColonPosition());
  }
}

void VisitorJAVAML::writeAttributes(const statm::ExpressionStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::Statement&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const statm::For& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::Iteration&)node,composite,false);

  if (composite) {
    writeRange("LeftParenPosition", node.getLeftParenPosition());
  }
  if (composite) {
    writeRange("RightParenPosition", node.getRightParenPosition());
  }
}

void VisitorJAVAML::writeAttributes(const statm::Handler& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((base::Positioned&)node,composite,false);

  if (composite) {
    writeRange("LeftParenPosition", node.getLeftParenPosition());
  }
  if (composite) {
    writeRange("RightParenPosition", node.getRightParenPosition());
  }
}

void VisitorJAVAML::writeAttributes(const statm::If& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::Selection&)node,composite,false);

  if (composite) {
    writeRange("ElsePosition", node.getElsePosition());
  }
}

void VisitorJAVAML::writeAttributes(const statm::Iteration& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::Statement&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const statm::Jump& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::Statement&)node,composite,false);

  if (!composite) {
    ofs << " label='" << chk(node.getLabel()) << "'";
  }
  if (composite) {
    writeRange("LabelPosition", node.getLabelPosition());
  }
}

void VisitorJAVAML::writeAttributes(const statm::LabeledStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::Statement&)node,composite,false);

  if (!composite) {
    ofs << " label='" << chk(node.getLabel()) << "'";
  }
  if (composite) {
    writeRange("ColonPosition", node.getColonPosition());
  }
}

void VisitorJAVAML::writeAttributes(const statm::Return& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::Statement&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const statm::Selection& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::Statement&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const statm::Statement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const statm::Switch& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::Selection&)node,composite,false);

  if (composite) {
    writeRange("BlockStartPosition", node.getBlockStartPosition());
  }
}

void VisitorJAVAML::writeAttributes(const statm::SwitchLabel& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((base::Positioned&)node,composite,false);

  if (composite) {
    writeRange("ColonPosition", node.getColonPosition());
  }
}

void VisitorJAVAML::writeAttributes(const statm::Synchronized& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::Statement&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const statm::Throw& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::Statement&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const statm::Try& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::Statement&)node,composite,false);

  if (composite) {
    writeRange("ResourceLeftParenPosition", node.getResourceLeftParenPosition());
  }
  if (composite) {
    writeRange("ResourceRightParenPosition", node.getResourceRightParenPosition());
  }
  if (composite) {
    writeRange("FinallyPosition", node.getFinallyPosition());
  }
}

void VisitorJAVAML::writeAttributes(const statm::While& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((statm::Iteration&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::AnnotatedElement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::AnnotationType& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::TypeDeclaration&)node,composite,false);

  if (composite) {
    writeRange("AtSignPosition", node.getAtSignPosition());
  }
}

void VisitorJAVAML::writeAttributes(const struc::AnnotationTypeElement& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::MethodDeclaration&)node,composite,false);

  if (composite) {
    writeRange("DefaultPosition", node.getDefaultPosition());
  }
}

void VisitorJAVAML::writeAttributes(const struc::AnonymousClass& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::ClassDeclaration&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::Class& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::ClassDeclaration&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::ClassDeclaration& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::TypeDeclaration&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::ClassGeneric& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::ClassDeclaration&)node,composite,false);

  writeAttributes((struc::GenericDeclaration&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::CompilationUnit& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  writeAttributes((base::PositionedWithoutComment&)node,composite,false);

  writeAttributes((base::Commentable&)node,composite,false);

  if (!composite) {
    ofs << " fileEncoding='" << chk(node.getFileEncoding()) << "'";
  }
}

void VisitorJAVAML::writeAttributes(const struc::Declaration& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((statm::Statement&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::Enum& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::TypeDeclaration&)node,composite,false);

  if (composite) {
    writeRange("SemiPosition", node.getSemiPosition());
  }
}

void VisitorJAVAML::writeAttributes(const struc::EnumConstant& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::VariableDeclaration&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::GenericDeclaration& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::Import& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((base::Positioned&)node,composite,false);

  if (!composite) {
    ofs << " isStatic='" << (node.getIsStatic() ? "true" : "false") << "'";
  }
  if (composite) {
    writeRange("StaticPosition", node.getStaticPosition());
  }
}

void VisitorJAVAML::writeAttributes(const struc::InitializerBlock& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::Declaration&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::InstanceInitializerBlock& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::InitializerBlock&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::Interface& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::InterfaceDeclaration&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::InterfaceDeclaration& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::TypeDeclaration&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::InterfaceGeneric& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::InterfaceDeclaration&)node,composite,false);

  writeAttributes((struc::GenericDeclaration&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::Member& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((struc::AnnotatedElement&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::Method& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::NormalMethod&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::MethodDeclaration& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::NamedDeclaration&)node,composite,false);

  if (!composite) {
    ofs << " isAbstract='" << (node.getIsAbstract() ? "true" : "false") << "'";
  }
  if (composite) {
    writeRange("AbstractPosition", node.getAbstractPosition());
  }
  if (!composite) {
    ofs << " isStrictfp='" << (node.getIsStrictfp() ? "true" : "false") << "'";
  }
  if (composite) {
    writeRange("StrictfpPosition", node.getStrictfpPosition());
  }
  if (composite) {
    writeRange("ParametersStartPosition", node.getParametersStartPosition());
  }
  if (composite) {
    writeRange("ParametersEndPosition", node.getParametersEndPosition());
  }
}

void VisitorJAVAML::writeAttributes(const struc::MethodGeneric& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::NormalMethod&)node,composite,false);

  writeAttributes((struc::GenericDeclaration&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::NamedDeclaration& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::Declaration&)node,composite,false);

  writeAttributes((base::Named&)node,composite,false);

  if (!composite) {
    ofs << " accessibility='" << Common::toString(node.getAccessibility()) << "'";
  }
  if (composite) {
    writeRange("AccessibilityPosition", node.getAccessibilityPosition());
  }
  if (!composite) {
    ofs << " isStatic='" << (node.getIsStatic() ? "true" : "false") << "'";
  }
  if (composite) {
    writeRange("StaticPosition", node.getStaticPosition());
  }
  if (!composite) {
    ofs << " isFinal='" << (node.getIsFinal() ? "true" : "false") << "'";
  }
  if (composite) {
    writeRange("FinalPosition", node.getFinalPosition());
  }
}

void VisitorJAVAML::writeAttributes(const struc::NormalMethod& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::MethodDeclaration&)node,composite,false);

  if (!composite) {
    ofs << " methodKind='" << Common::toString(node.getMethodKind()) << "'";
  }
  if (!composite) {
    ofs << " isSynchronized='" << (node.getIsSynchronized() ? "true" : "false") << "'";
  }
  if (composite) {
    writeRange("SynchronizedPosition", node.getSynchronizedPosition());
  }
  if (!composite) {
    ofs << " isNative='" << (node.getIsNative() ? "true" : "false") << "'";
  }
  if (composite) {
    writeRange("NativePosition", node.getNativePosition());
  }
  if (composite) {
    writeRange("ThrowsPosition", node.getThrowsPosition());
  }
}

void VisitorJAVAML::writeAttributes(const struc::Package& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((base::Named&)node,composite,false);

  writeAttributes((struc::Scope&)node,composite,false);

  if (!composite) {
    ofs << " qualifiedName='" << chk(node.getQualifiedName()) << "'";
  }
}

void VisitorJAVAML::writeAttributes(const struc::PackageDeclaration& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::Parameter& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::VariableDeclaration&)node,composite,false);

  if (!composite) {
    ofs << " isVarargs='" << (node.getIsVarargs() ? "true" : "false") << "'";
  }
  if (composite) {
    writeRange("VarargsPosition", node.getVarargsPosition());
  }
}

void VisitorJAVAML::writeAttributes(const struc::Scope& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::StaticInitializerBlock& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::InitializerBlock&)node,composite,false);

  if (composite) {
    writeRange("BlockStartPosition", node.getBlockStartPosition());
  }
}

void VisitorJAVAML::writeAttributes(const struc::TypeDeclaration& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::NamedDeclaration&)node,composite,false);

  writeAttributes((struc::Scope&)node,composite,false);

  if (composite) {
    writeRange("TypeNamePosition", node.getTypeNamePosition());
  }
  if (!composite) {
    ofs << " isAbstract='" << (node.getIsAbstract() ? "true" : "false") << "'";
  }
  if (composite) {
    writeRange("AbstractPosition", node.getAbstractPosition());
  }
  if (!composite) {
    ofs << " isStrictfp='" << (node.getIsStrictfp() ? "true" : "false") << "'";
  }
  if (composite) {
    writeRange("StrictfpPosition", node.getStrictfpPosition());
  }
  if (!composite) {
    ofs << " binaryName='" << chk(node.getBinaryName()) << "'";
  }
  if (composite) {
    writeRange("ExtendsPosition", node.getExtendsPosition());
  }
  if (composite) {
    writeRange("ImplementsPosition", node.getImplementsPosition());
  }
  if (composite) {
    writeRange("BodyStartPosition", node.getBodyStartPosition());
  }
}

void VisitorJAVAML::writeAttributes(const struc::TypeParameter& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  writeAttributes((base::Positioned&)node,composite,false);

  writeAttributes((base::Named&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const struc::Variable& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::VariableDeclaration&)node,composite,false);

  if (!composite) {
    ofs << " isTransient='" << (node.getIsTransient() ? "true" : "false") << "'";
  }
  if (composite) {
    writeRange("TransientPosition", node.getTransientPosition());
  }
  if (!composite) {
    ofs << " isVolatile='" << (node.getIsVolatile() ? "true" : "false") << "'";
  }
  if (composite) {
    writeRange("VolatilePosition", node.getVolatilePosition());
  }
  if (composite) {
    writeRange("EqualSignPosition", node.getEqualSignPosition());
  }
}

void VisitorJAVAML::writeAttributes(const struc::VariableDeclaration& node,bool composite, bool bWithParent /*= true*/ ) {
  if(bWithParent)
    writeAttributes((base::Base&)node,composite,false);

  if(bWithParent)
    writeAttributes((base::Commentable&)node,composite,false);

  if(bWithParent)
    writeAttributes((struc::Member&)node,composite,false);

  writeAttributes((struc::NamedDeclaration&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::ArrayType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::Type&)node,composite,false);

  if (!composite) {
    ofs << " size='" << node.getSize() << "'";
  }
}

void VisitorJAVAML::writeAttributes(const type::BooleanType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::PrimitiveType&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::BoundedWildcardType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::WildcardType&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::ByteType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::PrimitiveType&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::CharType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::PrimitiveType&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::ClassType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::ScopedType&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::DoubleType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::PrimitiveType&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::ErrorType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::Type&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::FloatType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::PrimitiveType&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::IntType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::PrimitiveType&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::LongType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::PrimitiveType&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::LowerBoundedWildcardType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::BoundedWildcardType&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::MethodType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::Type&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::NoType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::Type&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::NullType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::Type&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::PackageType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::Type&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::ParameterizedType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::ScopedType&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::PrimitiveType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::Type&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::ScopedType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::Type&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::ShortType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::PrimitiveType&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::Type& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Base&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::TypeVariable& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::Type&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::UnboundedWildcardType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::WildcardType&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::UnionType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::Type&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::UpperBoundedWildcardType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::BoundedWildcardType&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::VoidType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::PrimitiveType&)node,composite,false);

}

void VisitorJAVAML::writeAttributes(const type::WildcardType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::Type&)node,composite,false);

}


}}}
