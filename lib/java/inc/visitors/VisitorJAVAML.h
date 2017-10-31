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

#ifndef _JAVA_VISITORJAVAML_H_
#define _JAVA_VISITORJAVAML_H_

#include "java/inc/java.h"
#include <fstream>

/**
* \file VisitorJAVAML.h
* \brief Contains declaration of VisitorJAVAML class.
*/

namespace columbus { namespace java { namespace asg {
  /**
  * \brief Creates XML dump of the ASG.
  */
  class VisitorJAVAML : public Visitor {
    public:

      /**
      * \brief Constructor of XML generator visitor.
      * \param targetStream [in] ofstream to write the output
      * \param projectName  [in] Name of project - generated into the output
      * \param noId         [in] Do not write the ID of the nodes.
      * \param noLineInfo   [in] Do not write the line info of the nodes.
      */
      VisitorJAVAML(std::ofstream& targetStream,
                    const std::string& _projectName,
                    bool noId = false,
                    bool noLineInfo = false);

      /**
      * \brief Virtual destructor.
      */
      virtual ~VisitorJAVAML();

      /**
      * \brief This function is calling before the beginning of visiting process. It flushes the header of xml.
      */
      void beginVisit();

      /**
      * \brief This function is calling when the visiting process has finished. It flushes the tail of xml.
      */
      void finishVisit();

      /**
      * \brief Writes the XML representation of the base::BlockComment node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::BlockComment& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the base::BlockComment node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::BlockComment& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the base::JavadocComment node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::JavadocComment& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the base::JavadocComment node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::JavadocComment& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the base::LineComment node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::LineComment& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the base::LineComment node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::LineComment& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::ArrayAccess node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::ArrayAccess& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::ArrayAccess node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::ArrayAccess& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::ArrayTypeExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::ArrayTypeExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::ArrayTypeExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::ArrayTypeExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::Assignment node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::Assignment& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::Assignment node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::Assignment& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::BooleanLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::BooleanLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::BooleanLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::BooleanLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::CharacterLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::CharacterLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::CharacterLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::CharacterLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::ClassLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::ClassLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::ClassLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::ClassLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::Conditional node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::Conditional& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::Conditional node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::Conditional& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::DoubleLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::DoubleLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::DoubleLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::DoubleLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::Erroneous node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::Erroneous& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::Erroneous node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::Erroneous& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::ErroneousTypeExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::ErroneousTypeExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::ErroneousTypeExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::ErroneousTypeExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::ExternalTypeExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::ExternalTypeExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::ExternalTypeExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::ExternalTypeExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::FieldAccess node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::FieldAccess& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::FieldAccess node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::FieldAccess& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::FloatLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::FloatLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::FloatLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::FloatLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::Identifier node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::Identifier& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::Identifier node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::Identifier& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::InfixExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::InfixExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::InfixExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::InfixExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::InstanceOf node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::InstanceOf& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::InstanceOf node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::InstanceOf& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::IntegerLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::IntegerLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::IntegerLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::IntegerLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::LongLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::LongLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::LongLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::LongLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::MarkerAnnotation node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::MarkerAnnotation& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::MarkerAnnotation node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::MarkerAnnotation& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::MethodInvocation node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::MethodInvocation& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::MethodInvocation node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::MethodInvocation& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::NewArray node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::NewArray& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::NewArray node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::NewArray& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::NewClass node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::NewClass& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::NewClass node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::NewClass& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::NormalAnnotation node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::NormalAnnotation& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::NormalAnnotation node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::NormalAnnotation& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::NullLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::NullLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::NullLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::NullLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::ParenthesizedExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::ParenthesizedExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::ParenthesizedExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::ParenthesizedExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::PostfixExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::PostfixExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::PostfixExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::PostfixExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::PrefixExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::PrefixExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::PrefixExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::PrefixExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::PrimitiveTypeExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::PrimitiveTypeExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::PrimitiveTypeExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::PrimitiveTypeExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::QualifiedTypeExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::QualifiedTypeExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::QualifiedTypeExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::QualifiedTypeExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::SimpleTypeExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::SimpleTypeExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::SimpleTypeExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::SimpleTypeExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::SingleElementAnnotation node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::SingleElementAnnotation& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::SingleElementAnnotation node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::SingleElementAnnotation& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::StringLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::StringLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::StringLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::StringLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::Super node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::Super& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::Super node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::Super& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::This node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::This& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::This node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::This& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::TypeApplyExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::TypeApplyExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::TypeApplyExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::TypeApplyExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::TypeCast node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::TypeCast& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::TypeCast node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::TypeCast& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::TypeUnionExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::TypeUnionExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::TypeUnionExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::TypeUnionExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expr::WildcardExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expr::WildcardExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expr::WildcardExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expr::WildcardExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::Assert node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Assert& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::Assert node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Assert& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::BasicFor node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::BasicFor& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::BasicFor node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::BasicFor& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::Block node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Block& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::Block node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Block& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::Break node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Break& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::Break node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Break& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::Case node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Case& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::Case node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Case& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::Continue node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Continue& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::Continue node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Continue& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::Default node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Default& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::Default node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Default& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::Do node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Do& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::Do node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Do& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::Empty node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Empty& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::Empty node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Empty& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::EnhancedFor node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::EnhancedFor& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::EnhancedFor node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::EnhancedFor& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::ExpressionStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::ExpressionStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::ExpressionStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::ExpressionStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::Handler node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Handler& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::Handler node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Handler& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::If node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::If& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::If node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::If& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::LabeledStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::LabeledStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::LabeledStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::LabeledStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::Return node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Return& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::Return node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Return& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::Switch node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Switch& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::Switch node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Switch& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::Synchronized node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Synchronized& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::Synchronized node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Synchronized& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::Throw node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Throw& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::Throw node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Throw& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::Try node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::Try& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::Try node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::Try& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statm::While node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statm::While& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statm::While node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statm::While& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::AnnotationType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::AnnotationType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::AnnotationType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::AnnotationType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::AnnotationTypeElement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::AnnotationTypeElement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::AnnotationTypeElement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::AnnotationTypeElement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::AnonymousClass node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::AnonymousClass& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::AnonymousClass node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::AnonymousClass& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::Class node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::Class& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::Class node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::Class& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::ClassGeneric node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::ClassGeneric& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::ClassGeneric node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::ClassGeneric& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::CompilationUnit node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::CompilationUnit& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::CompilationUnit node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::CompilationUnit& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::Enum node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::Enum& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::Enum node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::Enum& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::EnumConstant node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::EnumConstant& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::EnumConstant node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::EnumConstant& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::Import node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::Import& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::Import node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::Import& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::InstanceInitializerBlock node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::InstanceInitializerBlock& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::InstanceInitializerBlock node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::InstanceInitializerBlock& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::Interface node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::Interface& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::Interface node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::Interface& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::InterfaceGeneric node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::InterfaceGeneric& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::InterfaceGeneric node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::InterfaceGeneric& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::Method node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::Method& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::Method node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::Method& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::MethodGeneric node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::MethodGeneric& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::MethodGeneric node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::MethodGeneric& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::Package node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::Package& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::Package node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::Package& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::PackageDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::PackageDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::PackageDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::PackageDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::Parameter node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::Parameter& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::Parameter node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::Parameter& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::StaticInitializerBlock node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::StaticInitializerBlock& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::StaticInitializerBlock node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::StaticInitializerBlock& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::TypeParameter node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::TypeParameter& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::TypeParameter node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::TypeParameter& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the struc::Variable node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const struc::Variable& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the struc::Variable node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const struc::Variable& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::ArrayType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::ArrayType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::ArrayType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::ArrayType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::BooleanType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::BooleanType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::BooleanType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::BooleanType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::ByteType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::ByteType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::ByteType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::ByteType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::CharType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::CharType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::CharType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::CharType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::ClassType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::ClassType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::ClassType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::ClassType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::DoubleType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::DoubleType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::DoubleType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::DoubleType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::ErrorType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::ErrorType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::ErrorType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::ErrorType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::FloatType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::FloatType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::FloatType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::FloatType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::IntType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::IntType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::IntType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::IntType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::LongType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::LongType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::LongType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::LongType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::LowerBoundedWildcardType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::LowerBoundedWildcardType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::LowerBoundedWildcardType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::LowerBoundedWildcardType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::MethodType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::MethodType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::MethodType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::MethodType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::NoType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::NoType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::NoType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::NoType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::NullType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::NullType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::NullType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::NullType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::PackageType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::PackageType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::PackageType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::PackageType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::ParameterizedType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::ParameterizedType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::ParameterizedType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::ParameterizedType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::ShortType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::ShortType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::ShortType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::ShortType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::TypeVariable node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::TypeVariable& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::TypeVariable node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::TypeVariable& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::UnboundedWildcardType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::UnboundedWildcardType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::UnboundedWildcardType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::UnboundedWildcardType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::UnionType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::UnionType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::UnionType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::UnionType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::UpperBoundedWildcardType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::UpperBoundedWildcardType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::UpperBoundedWildcardType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::UpperBoundedWildcardType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the type::VoidType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::VoidType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the type::VoidType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::VoidType& node, bool callVirtualBase = true);

      /**
      * \brief Edge visitor for comments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCommentable_Comments(const base::Commentable& begin, const base::Comment& end);

      /**
      * \brief Edge visitor for comments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCommentable_Comments(const base::Commentable& begin, const base::Comment& end);

      /**
      * \brief Edge  visitor for hasAnnotationName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnnotation_HasAnnotationName(const expr::Annotation& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasAnnotationName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAnnotation_HasAnnotationName(const expr::Annotation& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayTypeExpression_HasComponentType(const expr::ArrayTypeExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArrayTypeExpression_HasComponentType(const expr::ArrayTypeExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasLeftOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinary_HasLeftOperand(const expr::Binary& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasLeftOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBinary_HasLeftOperand(const expr::Binary& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasRightOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinary_HasRightOperand(const expr::Binary& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasRightOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBinary_HasRightOperand(const expr::Binary& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassLiteral_HasComponentType(const expr::ClassLiteral& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndClassLiteral_HasComponentType(const expr::ClassLiteral& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditional_HasCondition(const expr::Conditional& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConditional_HasCondition(const expr::Conditional& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasTrueExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditional_HasTrueExpression(const expr::Conditional& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasTrueExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConditional_HasTrueExpression(const expr::Conditional& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasFalseExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditional_HasFalseExpression(const expr::Conditional& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasFalseExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConditional_HasFalseExpression(const expr::Conditional& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasErrors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitErroneous_HasErrors(const expr::Erroneous& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasErrors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndErroneous_HasErrors(const expr::Erroneous& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasErrors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitErroneousTypeExpression_HasErrors(const expr::ErroneousTypeExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasErrors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndErroneousTypeExpression_HasErrors(const expr::ErroneousTypeExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge visitor for type edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExpression_Type(const expr::Expression& begin, const type::Type& end);

      /**
      * \brief Edge visitor for type edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExpression_Type(const expr::Expression& begin, const type::Type& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIdentifier_RefersTo(const expr::Identifier& begin, const base::Named& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIdentifier_RefersTo(const expr::Identifier& begin, const base::Named& end);

      /**
      * \brief Edge  visitor for hasTypeOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInstanceOf_HasTypeOperand(const expr::InstanceOf& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasTypeOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInstanceOf_HasTypeOperand(const expr::InstanceOf& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodInvocation_HasTypeArguments(const expr::MethodInvocation& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodInvocation_HasTypeArguments(const expr::MethodInvocation& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodInvocation_HasArguments(const expr::MethodInvocation& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodInvocation_HasArguments(const expr::MethodInvocation& begin, const expr::Expression& end);

      /**
      * \brief Edge visitor for invokes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodInvocation_Invokes(const expr::MethodInvocation& begin, const struc::MethodDeclaration& end);

      /**
      * \brief Edge visitor for invokes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodInvocation_Invokes(const expr::MethodInvocation& begin, const struc::MethodDeclaration& end);

      /**
      * \brief Edge  visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewArray_HasComponentType(const expr::NewArray& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasComponentType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewArray_HasComponentType(const expr::NewArray& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasDimensions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewArray_HasDimensions(const expr::NewArray& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasDimensions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewArray_HasDimensions(const expr::NewArray& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasInitializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewArray_HasInitializers(const expr::NewArray& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasInitializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewArray_HasInitializers(const expr::NewArray& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasEnclosingExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewClass_HasEnclosingExpression(const expr::NewClass& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasEnclosingExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewClass_HasEnclosingExpression(const expr::NewClass& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewClass_HasTypeArguments(const expr::NewClass& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewClass_HasTypeArguments(const expr::NewClass& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasTypeName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewClass_HasTypeName(const expr::NewClass& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasTypeName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewClass_HasTypeName(const expr::NewClass& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewClass_HasArguments(const expr::NewClass& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewClass_HasArguments(const expr::NewClass& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasAnonymousClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewClass_HasAnonymousClass(const expr::NewClass& begin, const struc::AnonymousClass& end);

      /**
      * \brief Edge end visitor for hasAnonymousClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewClass_HasAnonymousClass(const expr::NewClass& begin, const struc::AnonymousClass& end);

      /**
      * \brief Edge visitor for constructor edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewClass_Constructor(const expr::NewClass& begin, const struc::NormalMethod& end);

      /**
      * \brief Edge visitor for constructor edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewClass_Constructor(const expr::NewClass& begin, const struc::NormalMethod& end);

      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNormalAnnotation_HasArguments(const expr::NormalAnnotation& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNormalAnnotation_HasArguments(const expr::NormalAnnotation& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasQualifierType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQualifiedTypeExpression_HasQualifierType(const expr::QualifiedTypeExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasQualifierType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQualifiedTypeExpression_HasQualifierType(const expr::QualifiedTypeExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasSimpleType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQualifiedTypeExpression_HasSimpleType(const expr::QualifiedTypeExpression& begin, const expr::SimpleTypeExpression& end);

      /**
      * \brief Edge end visitor for hasSimpleType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQualifiedTypeExpression_HasSimpleType(const expr::QualifiedTypeExpression& begin, const expr::SimpleTypeExpression& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSingleElementAnnotation_HasArgument(const expr::SingleElementAnnotation& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSingleElementAnnotation_HasArgument(const expr::SingleElementAnnotation& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasRawType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeApplyExpression_HasRawType(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasRawType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeApplyExpression_HasRawType(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeApplyExpression_HasTypeArguments(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasTypeArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeApplyExpression_HasTypeArguments(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasTypeOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeCast_HasTypeOperand(const expr::TypeCast& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasTypeOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeCast_HasTypeOperand(const expr::TypeCast& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasAlternatives edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeUnionExpression_HasAlternatives(const expr::TypeUnionExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasAlternatives edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeUnionExpression_HasAlternatives(const expr::TypeUnionExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUnary_HasOperand(const expr::Unary& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasOperand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUnary_HasOperand(const expr::Unary& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasBound edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWildcardExpression_HasBound(const expr::WildcardExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasBound edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndWildcardExpression_HasBound(const expr::WildcardExpression& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssert_HasCondition(const statm::Assert& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssert_HasCondition(const statm::Assert& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasDetail edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssert_HasDetail(const statm::Assert& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasDetail edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssert_HasDetail(const statm::Assert& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasInitializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasicFor_HasInitializers(const statm::BasicFor& begin, const statm::Statement& end);

      /**
      * \brief Edge end visitor for hasInitializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBasicFor_HasInitializers(const statm::BasicFor& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasicFor_HasCondition(const statm::BasicFor& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBasicFor_HasCondition(const statm::BasicFor& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasUpdates edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasicFor_HasUpdates(const statm::BasicFor& begin, const statm::Statement& end);

      /**
      * \brief Edge end visitor for hasUpdates edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBasicFor_HasUpdates(const statm::BasicFor& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasStatements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBlock_HasStatements(const statm::Block& begin, const statm::Statement& end);

      /**
      * \brief Edge end visitor for hasStatements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBlock_HasStatements(const statm::Block& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCase_HasExpression(const statm::Case& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCase_HasExpression(const statm::Case& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDo_HasCondition(const statm::Do& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDo_HasCondition(const statm::Do& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEnhancedFor_HasParameter(const statm::EnhancedFor& begin, const struc::Parameter& end);

      /**
      * \brief Edge end visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndEnhancedFor_HasParameter(const statm::EnhancedFor& begin, const struc::Parameter& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEnhancedFor_HasExpression(const statm::EnhancedFor& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndEnhancedFor_HasExpression(const statm::EnhancedFor& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExpressionStatement_HasExpression(const statm::ExpressionStatement& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExpressionStatement_HasExpression(const statm::ExpressionStatement& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitHandler_HasParameter(const statm::Handler& begin, const struc::Parameter& end);

      /**
      * \brief Edge end visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndHandler_HasParameter(const statm::Handler& begin, const struc::Parameter& end);

      /**
      * \brief Edge  visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitHandler_HasBlock(const statm::Handler& begin, const statm::Block& end);

      /**
      * \brief Edge end visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndHandler_HasBlock(const statm::Handler& begin, const statm::Block& end);

      /**
      * \brief Edge  visitor for hasSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIf_HasSubstatement(const statm::If& begin, const statm::Statement& end);

      /**
      * \brief Edge end visitor for hasSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIf_HasSubstatement(const statm::If& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasFalseSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIf_HasFalseSubstatement(const statm::If& begin, const statm::Statement& end);

      /**
      * \brief Edge end visitor for hasFalseSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIf_HasFalseSubstatement(const statm::If& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIteration_HasSubstatement(const statm::Iteration& begin, const statm::Statement& end);

      /**
      * \brief Edge end visitor for hasSubstatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIteration_HasSubstatement(const statm::Iteration& begin, const statm::Statement& end);

      /**
      * \brief Edge visitor for target edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitJump_Target(const statm::Jump& begin, const statm::Statement& end);

      /**
      * \brief Edge visitor for target edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndJump_Target(const statm::Jump& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasStatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLabeledStatement_HasStatement(const statm::LabeledStatement& begin, const statm::Statement& end);

      /**
      * \brief Edge end visitor for hasStatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLabeledStatement_HasStatement(const statm::LabeledStatement& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitReturn_HasExpression(const statm::Return& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndReturn_HasExpression(const statm::Return& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSelection_HasCondition(const statm::Selection& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSelection_HasCondition(const statm::Selection& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasCases edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitch_HasCases(const statm::Switch& begin, const statm::SwitchLabel& end);

      /**
      * \brief Edge end visitor for hasCases edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSwitch_HasCases(const statm::Switch& begin, const statm::SwitchLabel& end);

      /**
      * \brief Edge  visitor for hasStatements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchLabel_HasStatements(const statm::SwitchLabel& begin, const statm::Statement& end);

      /**
      * \brief Edge end visitor for hasStatements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSwitchLabel_HasStatements(const statm::SwitchLabel& begin, const statm::Statement& end);

      /**
      * \brief Edge  visitor for hasLock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSynchronized_HasLock(const statm::Synchronized& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasLock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSynchronized_HasLock(const statm::Synchronized& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSynchronized_HasBlock(const statm::Synchronized& begin, const statm::Block& end);

      /**
      * \brief Edge end visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSynchronized_HasBlock(const statm::Synchronized& begin, const statm::Block& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitThrow_HasExpression(const statm::Throw& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndThrow_HasExpression(const statm::Throw& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasResources edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTry_HasResources(const statm::Try& begin, const struc::Variable& end);

      /**
      * \brief Edge end visitor for hasResources edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTry_HasResources(const statm::Try& begin, const struc::Variable& end);

      /**
      * \brief Edge  visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTry_HasBlock(const statm::Try& begin, const statm::Block& end);

      /**
      * \brief Edge end visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTry_HasBlock(const statm::Try& begin, const statm::Block& end);

      /**
      * \brief Edge  visitor for hasHandlers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTry_HasHandlers(const statm::Try& begin, const statm::Handler& end);

      /**
      * \brief Edge end visitor for hasHandlers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTry_HasHandlers(const statm::Try& begin, const statm::Handler& end);

      /**
      * \brief Edge  visitor for hasFinallyBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTry_HasFinallyBlock(const statm::Try& begin, const statm::Block& end);

      /**
      * \brief Edge end visitor for hasFinallyBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTry_HasFinallyBlock(const statm::Try& begin, const statm::Block& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhile_HasCondition(const statm::While& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndWhile_HasCondition(const statm::While& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasAnnotations edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnnotatedElement_HasAnnotations(const struc::AnnotatedElement& begin, const expr::Annotation& end);

      /**
      * \brief Edge end visitor for hasAnnotations edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAnnotatedElement_HasAnnotations(const struc::AnnotatedElement& begin, const expr::Annotation& end);

      /**
      * \brief Edge  visitor for hasDefaultValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnnotationTypeElement_HasDefaultValue(const struc::AnnotationTypeElement& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasDefaultValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAnnotationTypeElement_HasDefaultValue(const struc::AnnotationTypeElement& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasPackageDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnit_HasPackageDeclaration(const struc::CompilationUnit& begin, const struc::PackageDeclaration& end);

      /**
      * \brief Edge end visitor for hasPackageDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCompilationUnit_HasPackageDeclaration(const struc::CompilationUnit& begin, const struc::PackageDeclaration& end);

      /**
      * \brief Edge  visitor for hasImports edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnit_HasImports(const struc::CompilationUnit& begin, const struc::Import& end);

      /**
      * \brief Edge end visitor for hasImports edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCompilationUnit_HasImports(const struc::CompilationUnit& begin, const struc::Import& end);

      /**
      * \brief Edge visitor for typeDeclarations edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnit_TypeDeclarations(const struc::CompilationUnit& begin, const struc::TypeDeclaration& end);

      /**
      * \brief Edge visitor for typeDeclarations edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCompilationUnit_TypeDeclarations(const struc::CompilationUnit& begin, const struc::TypeDeclaration& end);

      /**
      * \brief Edge  visitor for hasOthers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnit_HasOthers(const struc::CompilationUnit& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasOthers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCompilationUnit_HasOthers(const struc::CompilationUnit& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasNewClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEnumConstant_HasNewClass(const struc::EnumConstant& begin, const expr::NewClass& end);

      /**
      * \brief Edge end visitor for hasNewClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndEnumConstant_HasNewClass(const struc::EnumConstant& begin, const expr::NewClass& end);

      /**
      * \brief Edge  visitor for hasTypeParameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGenericDeclaration_HasTypeParameters(const struc::GenericDeclaration& begin, const struc::TypeParameter& end);

      /**
      * \brief Edge end visitor for hasTypeParameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndGenericDeclaration_HasTypeParameters(const struc::GenericDeclaration& begin, const struc::TypeParameter& end);

      /**
      * \brief Edge  visitor for hasTarget edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImport_HasTarget(const struc::Import& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasTarget edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndImport_HasTarget(const struc::Import& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInitializerBlock_HasBody(const struc::InitializerBlock& begin, const statm::Block& end);

      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInitializerBlock_HasBody(const struc::InitializerBlock& begin, const statm::Block& end);

      /**
      * \brief Edge  visitor for hasReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclaration_HasReturnType(const struc::MethodDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodDeclaration_HasReturnType(const struc::MethodDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge visitor for methodType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclaration_MethodType(const struc::MethodDeclaration& begin, const type::MethodType& end);

      /**
      * \brief Edge visitor for methodType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodDeclaration_MethodType(const struc::MethodDeclaration& begin, const type::MethodType& end);

      /**
      * \brief Edge visitor for overrides edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclaration_Overrides(const struc::MethodDeclaration& begin, const struc::MethodDeclaration& end);

      /**
      * \brief Edge visitor for overrides edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodDeclaration_Overrides(const struc::MethodDeclaration& begin, const struc::MethodDeclaration& end);

      /**
      * \brief Edge  visitor for hasParameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNormalMethod_HasParameters(const struc::NormalMethod& begin, const struc::Parameter& end);

      /**
      * \brief Edge end visitor for hasParameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNormalMethod_HasParameters(const struc::NormalMethod& begin, const struc::Parameter& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNormalMethod_HasBody(const struc::NormalMethod& begin, const statm::Block& end);

      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNormalMethod_HasBody(const struc::NormalMethod& begin, const statm::Block& end);

      /**
      * \brief Edge  visitor for hasThrownExceptions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNormalMethod_HasThrownExceptions(const struc::NormalMethod& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasThrownExceptions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNormalMethod_HasThrownExceptions(const struc::NormalMethod& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasCompilationUnits edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPackage_HasCompilationUnits(const struc::Package& begin, const struc::CompilationUnit& end);

      /**
      * \brief Edge end visitor for hasCompilationUnits edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPackage_HasCompilationUnits(const struc::Package& begin, const struc::CompilationUnit& end);

      /**
      * \brief Edge  visitor for hasPackageName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPackageDeclaration_HasPackageName(const struc::PackageDeclaration& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasPackageName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPackageDeclaration_HasPackageName(const struc::PackageDeclaration& begin, const expr::Expression& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPackageDeclaration_RefersTo(const struc::PackageDeclaration& begin, const struc::Package& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPackageDeclaration_RefersTo(const struc::PackageDeclaration& begin, const struc::Package& end);

      /**
      * \brief Edge  visitor for hasMembers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitScope_HasMembers(const struc::Scope& begin, const struc::Member& end);

      /**
      * \brief Edge end visitor for hasMembers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndScope_HasMembers(const struc::Scope& begin, const struc::Member& end);

      /**
      * \brief Edge visitor for isInCompilationUnit edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclaration_IsInCompilationUnit(const struc::TypeDeclaration& begin, const struc::CompilationUnit& end);

      /**
      * \brief Edge visitor for isInCompilationUnit edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeDeclaration_IsInCompilationUnit(const struc::TypeDeclaration& begin, const struc::CompilationUnit& end);

      /**
      * \brief Edge  visitor for hasSuperClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclaration_HasSuperClass(const struc::TypeDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasSuperClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeDeclaration_HasSuperClass(const struc::TypeDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasSuperInterfaces edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclaration_HasSuperInterfaces(const struc::TypeDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasSuperInterfaces edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeDeclaration_HasSuperInterfaces(const struc::TypeDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasOthers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclaration_HasOthers(const struc::TypeDeclaration& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasOthers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeDeclaration_HasOthers(const struc::TypeDeclaration& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasBounds edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeParameter_HasBounds(const struc::TypeParameter& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasBounds edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeParameter_HasBounds(const struc::TypeParameter& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge  visitor for hasInitialValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariable_HasInitialValue(const struc::Variable& begin, const expr::Expression& end);

      /**
      * \brief Edge end visitor for hasInitialValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndVariable_HasInitialValue(const struc::Variable& begin, const expr::Expression& end);

      /**
      * \brief Edge  visitor for hasType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclaration_HasType(const struc::VariableDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge end visitor for hasType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndVariableDeclaration_HasType(const struc::VariableDeclaration& begin, const expr::TypeExpression& end);

      /**
      * \brief Edge visitor for componentType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayType_ComponentType(const type::ArrayType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for componentType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArrayType_ComponentType(const type::ArrayType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassType_RefersTo(const type::ClassType& begin, const struc::TypeDeclaration& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndClassType_RefersTo(const type::ClassType& begin, const struc::TypeDeclaration& end);

      /**
      * \brief Edge visitor for returnType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodType_ReturnType(const type::MethodType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for returnType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodType_ReturnType(const type::MethodType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for parameterTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodType_ParameterTypes(const type::MethodType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for parameterTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodType_ParameterTypes(const type::MethodType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for thrownTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodType_ThrownTypes(const type::MethodType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for thrownTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodType_ThrownTypes(const type::MethodType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPackageType_RefersTo(const type::PackageType& begin, const struc::Package& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPackageType_RefersTo(const type::PackageType& begin, const struc::Package& end);

      /**
      * \brief Edge visitor for rawType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameterizedType_RawType(const type::ParameterizedType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for rawType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndParameterizedType_RawType(const type::ParameterizedType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for argumentTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameterizedType_ArgumentTypes(const type::ParameterizedType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for argumentTypes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndParameterizedType_ArgumentTypes(const type::ParameterizedType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for owner edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitScopedType_Owner(const type::ScopedType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for owner edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndScopedType_Owner(const type::ScopedType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeVariable_RefersTo(const type::TypeVariable& begin, const struc::TypeParameter& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeVariable_RefersTo(const type::TypeVariable& begin, const struc::TypeParameter& end);

      /**
      * \brief Edge visitor for alternatives edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUnionType_Alternatives(const type::UnionType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for alternatives edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUnionType_Alternatives(const type::UnionType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for bound edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWildcardType_Bound(const type::WildcardType& begin, const type::Type& end);

      /**
      * \brief Edge visitor for bound edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndWildcardType_Bound(const type::WildcardType& begin, const type::Type& end);

    protected:

      /**
      * \internal
      * \brief Creates the indentation according to the depth.
      */
      void createIndentation();

      /**
      * \internal
      * \brief Replaces the invalid characters for XML in the string.
      */
      std::string chk(std::string s);

      /**
      * \internal
      * \brief Writes out a Range attribute with name.
      */
      void writeRange(const char *name, const Range &range);

      /**
      * \internal
      * \brief Writes out the attributes of the base::Base node.
      */
      virtual void writeAttributes(const base::Base& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the base::BlockComment node.
      */
      virtual void writeAttributes(const base::BlockComment& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the base::Comment node.
      */
      virtual void writeAttributes(const base::Comment& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the base::Commentable node.
      */
      virtual void writeAttributes(const base::Commentable& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the base::JavadocComment node.
      */
      virtual void writeAttributes(const base::JavadocComment& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the base::LineComment node.
      */
      virtual void writeAttributes(const base::LineComment& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the base::Named node.
      */
      virtual void writeAttributes(const base::Named& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the base::NonJavadocComment node.
      */
      virtual void writeAttributes(const base::NonJavadocComment& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the base::Positioned node.
      */
      virtual void writeAttributes(const base::Positioned& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the base::PositionedWithoutComment node.
      */
      virtual void writeAttributes(const base::PositionedWithoutComment& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::Annotation node.
      */
      virtual void writeAttributes(const expr::Annotation& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::ArrayAccess node.
      */
      virtual void writeAttributes(const expr::ArrayAccess& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::ArrayTypeExpression node.
      */
      virtual void writeAttributes(const expr::ArrayTypeExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::Assignment node.
      */
      virtual void writeAttributes(const expr::Assignment& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::Binary node.
      */
      virtual void writeAttributes(const expr::Binary& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::BooleanLiteral node.
      */
      virtual void writeAttributes(const expr::BooleanLiteral& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::CharacterLiteral node.
      */
      virtual void writeAttributes(const expr::CharacterLiteral& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::ClassLiteral node.
      */
      virtual void writeAttributes(const expr::ClassLiteral& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::Conditional node.
      */
      virtual void writeAttributes(const expr::Conditional& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::DoubleLiteral node.
      */
      virtual void writeAttributes(const expr::DoubleLiteral& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::Erroneous node.
      */
      virtual void writeAttributes(const expr::Erroneous& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::ErroneousTypeExpression node.
      */
      virtual void writeAttributes(const expr::ErroneousTypeExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::Expression node.
      */
      virtual void writeAttributes(const expr::Expression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::ExternalTypeExpression node.
      */
      virtual void writeAttributes(const expr::ExternalTypeExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::FieldAccess node.
      */
      virtual void writeAttributes(const expr::FieldAccess& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::FloatLiteral node.
      */
      virtual void writeAttributes(const expr::FloatLiteral& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::Identifier node.
      */
      virtual void writeAttributes(const expr::Identifier& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::InfixExpression node.
      */
      virtual void writeAttributes(const expr::InfixExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::InstanceOf node.
      */
      virtual void writeAttributes(const expr::InstanceOf& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::IntegerLiteral node.
      */
      virtual void writeAttributes(const expr::IntegerLiteral& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::Literal node.
      */
      virtual void writeAttributes(const expr::Literal& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::LongLiteral node.
      */
      virtual void writeAttributes(const expr::LongLiteral& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::MarkerAnnotation node.
      */
      virtual void writeAttributes(const expr::MarkerAnnotation& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::MethodInvocation node.
      */
      virtual void writeAttributes(const expr::MethodInvocation& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::NewArray node.
      */
      virtual void writeAttributes(const expr::NewArray& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::NewClass node.
      */
      virtual void writeAttributes(const expr::NewClass& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::NormalAnnotation node.
      */
      virtual void writeAttributes(const expr::NormalAnnotation& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::NullLiteral node.
      */
      virtual void writeAttributes(const expr::NullLiteral& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::NumberLiteral node.
      */
      virtual void writeAttributes(const expr::NumberLiteral& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::ParenthesizedExpression node.
      */
      virtual void writeAttributes(const expr::ParenthesizedExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::PostfixExpression node.
      */
      virtual void writeAttributes(const expr::PostfixExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::PrefixExpression node.
      */
      virtual void writeAttributes(const expr::PrefixExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::PrimitiveTypeExpression node.
      */
      virtual void writeAttributes(const expr::PrimitiveTypeExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::QualifiedTypeExpression node.
      */
      virtual void writeAttributes(const expr::QualifiedTypeExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::SimpleTypeExpression node.
      */
      virtual void writeAttributes(const expr::SimpleTypeExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::SingleElementAnnotation node.
      */
      virtual void writeAttributes(const expr::SingleElementAnnotation& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::StringLiteral node.
      */
      virtual void writeAttributes(const expr::StringLiteral& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::Super node.
      */
      virtual void writeAttributes(const expr::Super& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::This node.
      */
      virtual void writeAttributes(const expr::This& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::TypeApplyExpression node.
      */
      virtual void writeAttributes(const expr::TypeApplyExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::TypeCast node.
      */
      virtual void writeAttributes(const expr::TypeCast& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::TypeExpression node.
      */
      virtual void writeAttributes(const expr::TypeExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::TypeUnionExpression node.
      */
      virtual void writeAttributes(const expr::TypeUnionExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::Unary node.
      */
      virtual void writeAttributes(const expr::Unary& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expr::WildcardExpression node.
      */
      virtual void writeAttributes(const expr::WildcardExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::Assert node.
      */
      virtual void writeAttributes(const statm::Assert& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::BasicFor node.
      */
      virtual void writeAttributes(const statm::BasicFor& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::Block node.
      */
      virtual void writeAttributes(const statm::Block& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::Break node.
      */
      virtual void writeAttributes(const statm::Break& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::Case node.
      */
      virtual void writeAttributes(const statm::Case& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::Continue node.
      */
      virtual void writeAttributes(const statm::Continue& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::Default node.
      */
      virtual void writeAttributes(const statm::Default& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::Do node.
      */
      virtual void writeAttributes(const statm::Do& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::Empty node.
      */
      virtual void writeAttributes(const statm::Empty& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::EnhancedFor node.
      */
      virtual void writeAttributes(const statm::EnhancedFor& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::ExpressionStatement node.
      */
      virtual void writeAttributes(const statm::ExpressionStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::For node.
      */
      virtual void writeAttributes(const statm::For& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::Handler node.
      */
      virtual void writeAttributes(const statm::Handler& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::If node.
      */
      virtual void writeAttributes(const statm::If& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::Iteration node.
      */
      virtual void writeAttributes(const statm::Iteration& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::Jump node.
      */
      virtual void writeAttributes(const statm::Jump& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::LabeledStatement node.
      */
      virtual void writeAttributes(const statm::LabeledStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::Return node.
      */
      virtual void writeAttributes(const statm::Return& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::Selection node.
      */
      virtual void writeAttributes(const statm::Selection& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::Statement node.
      */
      virtual void writeAttributes(const statm::Statement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::Switch node.
      */
      virtual void writeAttributes(const statm::Switch& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::SwitchLabel node.
      */
      virtual void writeAttributes(const statm::SwitchLabel& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::Synchronized node.
      */
      virtual void writeAttributes(const statm::Synchronized& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::Throw node.
      */
      virtual void writeAttributes(const statm::Throw& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::Try node.
      */
      virtual void writeAttributes(const statm::Try& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statm::While node.
      */
      virtual void writeAttributes(const statm::While& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::AnnotatedElement node.
      */
      virtual void writeAttributes(const struc::AnnotatedElement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::AnnotationType node.
      */
      virtual void writeAttributes(const struc::AnnotationType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::AnnotationTypeElement node.
      */
      virtual void writeAttributes(const struc::AnnotationTypeElement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::AnonymousClass node.
      */
      virtual void writeAttributes(const struc::AnonymousClass& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::Class node.
      */
      virtual void writeAttributes(const struc::Class& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::ClassDeclaration node.
      */
      virtual void writeAttributes(const struc::ClassDeclaration& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::ClassGeneric node.
      */
      virtual void writeAttributes(const struc::ClassGeneric& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::CompilationUnit node.
      */
      virtual void writeAttributes(const struc::CompilationUnit& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::Declaration node.
      */
      virtual void writeAttributes(const struc::Declaration& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::Enum node.
      */
      virtual void writeAttributes(const struc::Enum& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::EnumConstant node.
      */
      virtual void writeAttributes(const struc::EnumConstant& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::GenericDeclaration node.
      */
      virtual void writeAttributes(const struc::GenericDeclaration& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::Import node.
      */
      virtual void writeAttributes(const struc::Import& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::InitializerBlock node.
      */
      virtual void writeAttributes(const struc::InitializerBlock& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::InstanceInitializerBlock node.
      */
      virtual void writeAttributes(const struc::InstanceInitializerBlock& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::Interface node.
      */
      virtual void writeAttributes(const struc::Interface& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::InterfaceDeclaration node.
      */
      virtual void writeAttributes(const struc::InterfaceDeclaration& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::InterfaceGeneric node.
      */
      virtual void writeAttributes(const struc::InterfaceGeneric& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::Member node.
      */
      virtual void writeAttributes(const struc::Member& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::Method node.
      */
      virtual void writeAttributes(const struc::Method& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::MethodDeclaration node.
      */
      virtual void writeAttributes(const struc::MethodDeclaration& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::MethodGeneric node.
      */
      virtual void writeAttributes(const struc::MethodGeneric& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::NamedDeclaration node.
      */
      virtual void writeAttributes(const struc::NamedDeclaration& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::NormalMethod node.
      */
      virtual void writeAttributes(const struc::NormalMethod& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::Package node.
      */
      virtual void writeAttributes(const struc::Package& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::PackageDeclaration node.
      */
      virtual void writeAttributes(const struc::PackageDeclaration& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::Parameter node.
      */
      virtual void writeAttributes(const struc::Parameter& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::Scope node.
      */
      virtual void writeAttributes(const struc::Scope& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::StaticInitializerBlock node.
      */
      virtual void writeAttributes(const struc::StaticInitializerBlock& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::TypeDeclaration node.
      */
      virtual void writeAttributes(const struc::TypeDeclaration& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::TypeParameter node.
      */
      virtual void writeAttributes(const struc::TypeParameter& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::Variable node.
      */
      virtual void writeAttributes(const struc::Variable& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the struc::VariableDeclaration node.
      */
      virtual void writeAttributes(const struc::VariableDeclaration& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::ArrayType node.
      */
      virtual void writeAttributes(const type::ArrayType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::BooleanType node.
      */
      virtual void writeAttributes(const type::BooleanType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::BoundedWildcardType node.
      */
      virtual void writeAttributes(const type::BoundedWildcardType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::ByteType node.
      */
      virtual void writeAttributes(const type::ByteType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::CharType node.
      */
      virtual void writeAttributes(const type::CharType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::ClassType node.
      */
      virtual void writeAttributes(const type::ClassType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::DoubleType node.
      */
      virtual void writeAttributes(const type::DoubleType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::ErrorType node.
      */
      virtual void writeAttributes(const type::ErrorType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::FloatType node.
      */
      virtual void writeAttributes(const type::FloatType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::IntType node.
      */
      virtual void writeAttributes(const type::IntType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::LongType node.
      */
      virtual void writeAttributes(const type::LongType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::LowerBoundedWildcardType node.
      */
      virtual void writeAttributes(const type::LowerBoundedWildcardType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::MethodType node.
      */
      virtual void writeAttributes(const type::MethodType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::NoType node.
      */
      virtual void writeAttributes(const type::NoType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::NullType node.
      */
      virtual void writeAttributes(const type::NullType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::PackageType node.
      */
      virtual void writeAttributes(const type::PackageType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::ParameterizedType node.
      */
      virtual void writeAttributes(const type::ParameterizedType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::PrimitiveType node.
      */
      virtual void writeAttributes(const type::PrimitiveType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::ScopedType node.
      */
      virtual void writeAttributes(const type::ScopedType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::ShortType node.
      */
      virtual void writeAttributes(const type::ShortType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::Type node.
      */
      virtual void writeAttributes(const type::Type& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::TypeVariable node.
      */
      virtual void writeAttributes(const type::TypeVariable& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::UnboundedWildcardType node.
      */
      virtual void writeAttributes(const type::UnboundedWildcardType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::UnionType node.
      */
      virtual void writeAttributes(const type::UnionType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::UpperBoundedWildcardType node.
      */
      virtual void writeAttributes(const type::UpperBoundedWildcardType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::VoidType node.
      */
      virtual void writeAttributes(const type::VoidType& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the type::WildcardType node.
      */
      virtual void writeAttributes(const type::WildcardType& node, bool composite, bool bWithParent = true);

      /** \internal \brief The ofstrem into the xml will be written. */
      std::ofstream &ofs;

      /** \internal \brief Flag to know if the ID of the nodes have to be written or not. */
      bool noId;

      /** \internal \brief Flag to know if the line info of the nodes have to be written or not. */
      bool noLineInfo;

      const std::string projectName;

  }; // VisitorJAVAML


}}}
#endif

