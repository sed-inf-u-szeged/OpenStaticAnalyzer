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

#ifndef _JAVASCRIPT_VISITORJAVASCRIPTML_H_
#define _JAVASCRIPT_VISITORJAVASCRIPTML_H_

#include "javascript/inc/javascript.h"
#include <fstream>

/**
* \file VisitorJAVASCRIPTML.h
* \brief Contains declaration of VisitorJAVASCRIPTML class.
*/

namespace columbus { namespace javascript { namespace asg {
  /**
  * \brief Creates XML dump of the ASG.
  */
  class VisitorJAVASCRIPTML : public Visitor {
    public:

      /**
      * \brief Constructor of XML generator visitor.
      * \param targetStream [in] ofstream to write the output
      * \param projectName  [in] Name of project - generated into the output
      * \param noId         [in] Do not write the ID of the nodes.
      * \param noLineInfo   [in] Do not write the line info of the nodes.
      */
      VisitorJAVASCRIPTML(std::ofstream& targetStream,
                          const std::string& _projectName,
                          bool noId = false,
                          bool noLineInfo = false);

      /**
      * \brief Virtual destructor.
      */
      virtual ~VisitorJAVASCRIPTML();

      /**
      * \brief This function is calling before the beginning of visiting process. It flushes the header of xml.
      */
      void beginVisit();

      /**
      * \brief This function is calling when the visiting process has finished. It flushes the tail of xml.
      */
      void finishVisit();

      /**
      * \brief Writes the XML representation of the base::Comment node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Comment& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the base::Comment node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::Comment& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the base::Program node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Program& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the base::Program node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::Program& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the base::System node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::System& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the base::System node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::System& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the declaration::ClassDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::ClassDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the declaration::ClassDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::ClassDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the declaration::ExportAllDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::ExportAllDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the declaration::ExportAllDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::ExportAllDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the declaration::ExportDefaultDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::ExportDefaultDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the declaration::ExportDefaultDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::ExportDefaultDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the declaration::ExportNamedDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::ExportNamedDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the declaration::ExportNamedDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::ExportNamedDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the declaration::FunctionDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::FunctionDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the declaration::FunctionDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::FunctionDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the declaration::ImportDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::ImportDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the declaration::ImportDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::ImportDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the declaration::ModuleDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::ModuleDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the declaration::ModuleDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::ModuleDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the declaration::VariableDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::VariableDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the declaration::VariableDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::VariableDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the declaration::VariableDeclarator node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::VariableDeclarator& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the declaration::VariableDeclarator node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::VariableDeclarator& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ArrayExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ArrayExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ArrayExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ArrayExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ArrowFunctionExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ArrowFunctionExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ArrowFunctionExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ArrowFunctionExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::AssignmentExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AssignmentExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::AssignmentExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AssignmentExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::AwaitExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AwaitExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::AwaitExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AwaitExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::BigIntLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::BigIntLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::BigIntLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::BigIntLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::BinaryExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::BinaryExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::BinaryExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::BinaryExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::BooleanLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::BooleanLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::BooleanLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::BooleanLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::CallExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::CallExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::CallExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::CallExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ChainElement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ChainElement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ChainElement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ChainElement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ChainExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ChainExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ChainExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ChainExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ClassExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ClassExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ClassExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ClassExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ConditionalExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ConditionalExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ConditionalExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ConditionalExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::FunctionExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::FunctionExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::FunctionExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::FunctionExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::Identifier node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Identifier& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::Identifier node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Identifier& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ImportExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ImportExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ImportExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ImportExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::LogicalExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::LogicalExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::LogicalExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::LogicalExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::MemberExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::MemberExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::MemberExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::MemberExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::MetaProperty node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::MetaProperty& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::MetaProperty node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::MetaProperty& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::NewExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::NewExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::NewExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::NewExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::NullLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::NullLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::NullLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::NullLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::NumberLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::NumberLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::NumberLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::NumberLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ObjectExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ObjectExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ObjectExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ObjectExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::PrivateIdentifier node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::PrivateIdentifier& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::PrivateIdentifier node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::PrivateIdentifier& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::Property node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Property& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::Property node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Property& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::RegExpLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::RegExpLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::RegExpLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::RegExpLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::SequenceExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::SequenceExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::SequenceExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::SequenceExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::SpreadElement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::SpreadElement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::SpreadElement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::SpreadElement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::StringLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::StringLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::StringLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::StringLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::Super node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Super& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::Super node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Super& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::TaggedTemplateExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::TaggedTemplateExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::TaggedTemplateExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::TaggedTemplateExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::TemplateElement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::TemplateElement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::TemplateElement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::TemplateElement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::TemplateLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::TemplateLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::TemplateLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::TemplateLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ThisExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ThisExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ThisExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ThisExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::UnaryExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::UnaryExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::UnaryExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::UnaryExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::UpdateExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::UpdateExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::UpdateExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::UpdateExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::YieldExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::YieldExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::YieldExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::YieldExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::ArrayPattern node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ArrayPattern& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::ArrayPattern node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ArrayPattern& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::AssignmentPattern node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::AssignmentPattern& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::AssignmentPattern node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::AssignmentPattern& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::BlockStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::BlockStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::BlockStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::BlockStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::BreakStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::BreakStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::BreakStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::BreakStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::CatchClause node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::CatchClause& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::CatchClause node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::CatchClause& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::ContinueStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ContinueStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::ContinueStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ContinueStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::DebuggerStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::DebuggerStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::DebuggerStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::DebuggerStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::DoWhileStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::DoWhileStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::DoWhileStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::DoWhileStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::EmptyStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::EmptyStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::EmptyStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::EmptyStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::ExpressionStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ExpressionStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::ExpressionStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ExpressionStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::ForInStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ForInStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::ForInStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ForInStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::ForOfStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ForOfStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::ForOfStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ForOfStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::ForStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ForStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::ForStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ForStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::Function node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Function& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::Function node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Function& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::IfStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::IfStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::IfStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::IfStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::LabeledStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::LabeledStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::LabeledStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::LabeledStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::ObjectPattern node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ObjectPattern& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::ObjectPattern node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ObjectPattern& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::RestElement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::RestElement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::RestElement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::RestElement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::ReturnStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ReturnStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::ReturnStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ReturnStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::SwitchCase node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::SwitchCase& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::SwitchCase node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::SwitchCase& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::SwitchStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::SwitchStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::SwitchStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::SwitchStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::ThrowStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ThrowStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::ThrowStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ThrowStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::TryStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::TryStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::TryStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::TryStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::WhileStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::WhileStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::WhileStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::WhileStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::WithStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::WithStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::WithStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::WithStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ClassBody node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ClassBody& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ClassBody node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ClassBody& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ExportSpecifier node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ExportSpecifier& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ExportSpecifier node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ExportSpecifier& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ImportDefaultSpecifier node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ImportDefaultSpecifier& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ImportDefaultSpecifier node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ImportDefaultSpecifier& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ImportNamespaceSpecifier node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ImportNamespaceSpecifier& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ImportNamespaceSpecifier node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ImportNamespaceSpecifier& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ImportSpecifier node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ImportSpecifier& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ImportSpecifier node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ImportSpecifier& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::MethodDefinition node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::MethodDefinition& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::MethodDefinition node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::MethodDefinition& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::PropertyDefinition node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::PropertyDefinition& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::PropertyDefinition node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::PropertyDefinition& node, bool callVirtualBase = true);

      /**
      * \brief Edge visitor for comments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPositioned_Comments(const base::Positioned& begin, const base::Comment& end);

      /**
      * \brief Edge visitor for comments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPositioned_Comments(const base::Positioned& begin, const base::Comment& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitProgram_HasBody(const base::Program& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndProgram_HasBody(const base::Program& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasPrograms edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSystem_HasPrograms(const base::System& begin, const base::Program& end);

      /**
      * \brief Edge end visitor for hasPrograms edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSystem_HasPrograms(const base::System& begin, const base::Program& end);

      /**
      * \brief Edge  visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportAllDeclaration_HasSource(const declaration::ExportAllDeclaration& begin, const expression::Literal& end);

      /**
      * \brief Edge end visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExportAllDeclaration_HasSource(const declaration::ExportAllDeclaration& begin, const expression::Literal& end);

      /**
      * \brief Edge  visitor for hasExported edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportAllDeclaration_HasExported(const declaration::ExportAllDeclaration& begin, const expression::Identifier& end);

      /**
      * \brief Edge end visitor for hasExported edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExportAllDeclaration_HasExported(const declaration::ExportAllDeclaration& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportDefaultDeclaration_HasDeclaration(const declaration::ExportDefaultDeclaration& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExportDefaultDeclaration_HasDeclaration(const declaration::ExportDefaultDeclaration& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportNamedDeclaration_HasDeclaration(const declaration::ExportNamedDeclaration& begin, const declaration::Declaration& end);

      /**
      * \brief Edge end visitor for hasDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExportNamedDeclaration_HasDeclaration(const declaration::ExportNamedDeclaration& begin, const declaration::Declaration& end);

      /**
      * \brief Edge  visitor for hasSpecifiers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportNamedDeclaration_HasSpecifiers(const declaration::ExportNamedDeclaration& begin, const structure::ExportSpecifier& end);

      /**
      * \brief Edge end visitor for hasSpecifiers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExportNamedDeclaration_HasSpecifiers(const declaration::ExportNamedDeclaration& begin, const structure::ExportSpecifier& end);

      /**
      * \brief Edge  visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportNamedDeclaration_HasSource(const declaration::ExportNamedDeclaration& begin, const expression::Literal& end);

      /**
      * \brief Edge end visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExportNamedDeclaration_HasSource(const declaration::ExportNamedDeclaration& begin, const expression::Literal& end);

      /**
      * \brief Edge  visitor for hasSpecifiers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImportDeclaration_HasSpecifiers(const declaration::ImportDeclaration& begin, const structure::ImpSpecifier& end);

      /**
      * \brief Edge end visitor for hasSpecifiers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndImportDeclaration_HasSpecifiers(const declaration::ImportDeclaration& begin, const structure::ImpSpecifier& end);

      /**
      * \brief Edge  visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImportDeclaration_HasSource(const declaration::ImportDeclaration& begin, const expression::Literal& end);

      /**
      * \brief Edge end visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndImportDeclaration_HasSource(const declaration::ImportDeclaration& begin, const expression::Literal& end);

      /**
      * \brief Edge  visitor for hasDeclarations edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclaration_HasDeclarations(const declaration::VariableDeclaration& begin, const declaration::VariableDeclarator& end);

      /**
      * \brief Edge end visitor for hasDeclarations edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndVariableDeclaration_HasDeclarations(const declaration::VariableDeclaration& begin, const declaration::VariableDeclarator& end);

      /**
      * \brief Edge  visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclarator_HasIdentifier(const declaration::VariableDeclarator& begin, const statement::Pattern& end);

      /**
      * \brief Edge end visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndVariableDeclarator_HasIdentifier(const declaration::VariableDeclarator& begin, const statement::Pattern& end);

      /**
      * \brief Edge  visitor for hasInit edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclarator_HasInit(const declaration::VariableDeclarator& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasInit edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndVariableDeclarator_HasInit(const declaration::VariableDeclarator& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasElements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayExpression_HasElements(const expression::ArrayExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasElements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArrayExpression_HasElements(const expression::ArrayExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentExpression_HasLeft(const expression::AssignmentExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssignmentExpression_HasLeft(const expression::AssignmentExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentExpression_HasRight(const expression::AssignmentExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssignmentExpression_HasRight(const expression::AssignmentExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAwaitExpression_HasArgument(const expression::AwaitExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAwaitExpression_HasArgument(const expression::AwaitExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinaryExpression_HasLeft(const expression::BinaryExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBinaryExpression_HasLeft(const expression::BinaryExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinaryExpression_HasRight(const expression::BinaryExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBinaryExpression_HasRight(const expression::BinaryExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasCallee edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCallExpression_HasCallee(const expression::CallExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasCallee edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCallExpression_HasCallee(const expression::CallExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCallExpression_HasArguments(const expression::CallExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCallExpression_HasArguments(const expression::CallExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCallExpression_Calls(const expression::CallExpression& begin, const statement::Function& end);

      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCallExpression_Calls(const expression::CallExpression& begin, const statement::Function& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitChainExpression_HasExpression(const expression::ChainExpression& begin, const expression::ChainElement& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndChainExpression_HasExpression(const expression::ChainExpression& begin, const expression::ChainElement& end);

      /**
      * \brief Edge  visitor for hasAlternate edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalExpression_HasAlternate(const expression::ConditionalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasAlternate edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConditionalExpression_HasAlternate(const expression::ConditionalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasConsequent edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalExpression_HasConsequent(const expression::ConditionalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasConsequent edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConditionalExpression_HasConsequent(const expression::ConditionalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalExpression_HasTest(const expression::ConditionalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConditionalExpression_HasTest(const expression::ConditionalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIdentifier_RefersTo(const expression::Identifier& begin, const base::Positioned& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIdentifier_RefersTo(const expression::Identifier& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImportExpression_HasSource(const expression::ImportExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndImportExpression_HasSource(const expression::ImportExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLogicalExpression_HasLeft(const expression::LogicalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLogicalExpression_HasLeft(const expression::LogicalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLogicalExpression_HasRight(const expression::LogicalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLogicalExpression_HasRight(const expression::LogicalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasProperty edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMemberExpression_HasProperty(const expression::MemberExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasProperty edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMemberExpression_HasProperty(const expression::MemberExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMemberExpression_HasObject(const expression::MemberExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMemberExpression_HasObject(const expression::MemberExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasMeta edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMetaProperty_HasMeta(const expression::MetaProperty& begin, const expression::Identifier& end);

      /**
      * \brief Edge end visitor for hasMeta edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMetaProperty_HasMeta(const expression::MetaProperty& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasProperty edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMetaProperty_HasProperty(const expression::MetaProperty& begin, const expression::Identifier& end);

      /**
      * \brief Edge end visitor for hasProperty edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMetaProperty_HasProperty(const expression::MetaProperty& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasCallee edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewExpression_HasCallee(const expression::NewExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasCallee edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewExpression_HasCallee(const expression::NewExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewExpression_HasArguments(const expression::NewExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewExpression_HasArguments(const expression::NewExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewExpression_Calls(const expression::NewExpression& begin, const statement::Function& end);

      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNewExpression_Calls(const expression::NewExpression& begin, const statement::Function& end);

      /**
      * \brief Edge  visitor for hasProperties edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObjectExpression_HasProperties(const expression::ObjectExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasProperties edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndObjectExpression_HasProperties(const expression::ObjectExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitProperty_HasValue(const expression::Property& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndProperty_HasValue(const expression::Property& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitProperty_HasKey(const expression::Property& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndProperty_HasKey(const expression::Property& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpressions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSequenceExpression_HasExpressions(const expression::SequenceExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasExpressions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSequenceExpression_HasExpressions(const expression::SequenceExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSpreadElement_HasArgument(const expression::SpreadElement& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSpreadElement_HasArgument(const expression::SpreadElement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTaggedTemplateExpression_HasTag(const expression::TaggedTemplateExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTaggedTemplateExpression_HasTag(const expression::TaggedTemplateExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasQuasi edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTaggedTemplateExpression_HasQuasi(const expression::TaggedTemplateExpression& begin, const expression::TemplateLiteral& end);

      /**
      * \brief Edge end visitor for hasQuasi edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTaggedTemplateExpression_HasQuasi(const expression::TaggedTemplateExpression& begin, const expression::TemplateLiteral& end);

      /**
      * \brief Edge  visitor for hasQuasis edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTemplateLiteral_HasQuasis(const expression::TemplateLiteral& begin, const expression::TemplateElement& end);

      /**
      * \brief Edge end visitor for hasQuasis edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTemplateLiteral_HasQuasis(const expression::TemplateLiteral& begin, const expression::TemplateElement& end);

      /**
      * \brief Edge  visitor for hasExpressions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTemplateLiteral_HasExpressions(const expression::TemplateLiteral& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasExpressions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTemplateLiteral_HasExpressions(const expression::TemplateLiteral& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUnaryExpression_HasArgument(const expression::UnaryExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUnaryExpression_HasArgument(const expression::UnaryExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUpdateExpression_HasArgument(const expression::UpdateExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUpdateExpression_HasArgument(const expression::UpdateExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitYieldExpression_HasArgument(const expression::YieldExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndYieldExpression_HasArgument(const expression::YieldExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasElements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayPattern_HasElements(const statement::ArrayPattern& begin, const statement::Pattern& end);

      /**
      * \brief Edge end visitor for hasElements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArrayPattern_HasElements(const statement::ArrayPattern& begin, const statement::Pattern& end);

      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentPattern_HasLeft(const statement::AssignmentPattern& begin, const statement::Pattern& end);

      /**
      * \brief Edge end visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssignmentPattern_HasLeft(const statement::AssignmentPattern& begin, const statement::Pattern& end);

      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentPattern_HasRight(const statement::AssignmentPattern& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssignmentPattern_HasRight(const statement::AssignmentPattern& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBlockStatement_HasBody(const statement::BlockStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBlockStatement_HasBody(const statement::BlockStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasLabel edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBreakStatement_HasLabel(const statement::BreakStatement& begin, const expression::Identifier& end);

      /**
      * \brief Edge end visitor for hasLabel edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBreakStatement_HasLabel(const statement::BreakStatement& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasParam edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchClause_HasParam(const statement::CatchClause& begin, const statement::Pattern& end);

      /**
      * \brief Edge end visitor for hasParam edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCatchClause_HasParam(const statement::CatchClause& begin, const statement::Pattern& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchClause_HasBody(const statement::CatchClause& begin, const statement::BlockStatement& end);

      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCatchClause_HasBody(const statement::CatchClause& begin, const statement::BlockStatement& end);

      /**
      * \brief Edge  visitor for hasLabel edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitContinueStatement_HasLabel(const statement::ContinueStatement& begin, const expression::Identifier& end);

      /**
      * \brief Edge end visitor for hasLabel edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndContinueStatement_HasLabel(const statement::ContinueStatement& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExpressionStatement_HasExpression(const statement::ExpressionStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExpressionStatement_HasExpression(const statement::ExpressionStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForInStatement_HasRight(const statement::ForInStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForInStatement_HasRight(const statement::ForInStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForInStatement_HasBody(const statement::ForInStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForInStatement_HasBody(const statement::ForInStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForInStatement_HasLeft(const statement::ForInStatement& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForInStatement_HasLeft(const statement::ForInStatement& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatement_HasBody(const statement::ForStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForStatement_HasBody(const statement::ForStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatement_HasTest(const statement::ForStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForStatement_HasTest(const statement::ForStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasUpdate edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatement_HasUpdate(const statement::ForStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasUpdate edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForStatement_HasUpdate(const statement::ForStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasInit edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatement_HasInit(const statement::ForStatement& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasInit edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForStatement_HasInit(const statement::ForStatement& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasParams edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunction_HasParams(const statement::Function& begin, const statement::Pattern& end);

      /**
      * \brief Edge end visitor for hasParams edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFunction_HasParams(const statement::Function& begin, const statement::Pattern& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunction_HasBody(const statement::Function& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFunction_HasBody(const statement::Function& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunction_HasIdentifier(const statement::Function& begin, const expression::Identifier& end);

      /**
      * \brief Edge end visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFunction_HasIdentifier(const statement::Function& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfStatement_HasTest(const statement::IfStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIfStatement_HasTest(const statement::IfStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasConsequent edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfStatement_HasConsequent(const statement::IfStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge end visitor for hasConsequent edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIfStatement_HasConsequent(const statement::IfStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasAlternate edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfStatement_HasAlternate(const statement::IfStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge end visitor for hasAlternate edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIfStatement_HasAlternate(const statement::IfStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasLabel edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLabeledStatement_HasLabel(const statement::LabeledStatement& begin, const expression::Identifier& end);

      /**
      * \brief Edge end visitor for hasLabel edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLabeledStatement_HasLabel(const statement::LabeledStatement& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLabeledStatement_HasBody(const statement::LabeledStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLabeledStatement_HasBody(const statement::LabeledStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasProperties edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObjectPattern_HasProperties(const statement::ObjectPattern& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasProperties edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndObjectPattern_HasProperties(const statement::ObjectPattern& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitRestElement_HasArgument(const statement::RestElement& begin, const statement::Pattern& end);

      /**
      * \brief Edge end visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndRestElement_HasArgument(const statement::RestElement& begin, const statement::Pattern& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitReturnStatement_HasArgument(const statement::ReturnStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndReturnStatement_HasArgument(const statement::ReturnStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchCase_HasTest(const statement::SwitchCase& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSwitchCase_HasTest(const statement::SwitchCase& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasConsequent edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchCase_HasConsequent(const statement::SwitchCase& begin, const statement::Statement& end);

      /**
      * \brief Edge end visitor for hasConsequent edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSwitchCase_HasConsequent(const statement::SwitchCase& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasDiscriminant edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchStatement_HasDiscriminant(const statement::SwitchStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasDiscriminant edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSwitchStatement_HasDiscriminant(const statement::SwitchStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasCases edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchStatement_HasCases(const statement::SwitchStatement& begin, const statement::SwitchCase& end);

      /**
      * \brief Edge end visitor for hasCases edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSwitchStatement_HasCases(const statement::SwitchStatement& begin, const statement::SwitchCase& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitThrowStatement_HasArgument(const statement::ThrowStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndThrowStatement_HasArgument(const statement::ThrowStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryStatement_HasBlock(const statement::TryStatement& begin, const statement::BlockStatement& end);

      /**
      * \brief Edge end visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTryStatement_HasBlock(const statement::TryStatement& begin, const statement::BlockStatement& end);

      /**
      * \brief Edge  visitor for hasFinalizer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryStatement_HasFinalizer(const statement::TryStatement& begin, const statement::BlockStatement& end);

      /**
      * \brief Edge end visitor for hasFinalizer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTryStatement_HasFinalizer(const statement::TryStatement& begin, const statement::BlockStatement& end);

      /**
      * \brief Edge  visitor for hasHandler edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryStatement_HasHandler(const statement::TryStatement& begin, const statement::CatchClause& end);

      /**
      * \brief Edge end visitor for hasHandler edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTryStatement_HasHandler(const statement::TryStatement& begin, const statement::CatchClause& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhileStatement_HasBody(const statement::WhileStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndWhileStatement_HasBody(const statement::WhileStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhileStatement_HasTest(const statement::WhileStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndWhileStatement_HasTest(const statement::WhileStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWithStatement_HasObject(const statement::WithStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndWithStatement_HasObject(const statement::WithStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWithStatement_HasBody(const statement::WithStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndWithStatement_HasBody(const statement::WithStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClass_HasBody(const structure::Class& begin, const structure::ClassBody& end);

      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndClass_HasBody(const structure::Class& begin, const structure::ClassBody& end);

      /**
      * \brief Edge  visitor for hasSuperClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClass_HasSuperClass(const structure::Class& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasSuperClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndClass_HasSuperClass(const structure::Class& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClass_HasIdentifier(const structure::Class& begin, const expression::Identifier& end);

      /**
      * \brief Edge end visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndClass_HasIdentifier(const structure::Class& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassBody_HasBody(const structure::ClassBody& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndClassBody_HasBody(const structure::ClassBody& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasExported edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportSpecifier_HasExported(const structure::ExportSpecifier& begin, const expression::Identifier& end);

      /**
      * \brief Edge end visitor for hasExported edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExportSpecifier_HasExported(const structure::ExportSpecifier& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasImported edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImportSpecifier_HasImported(const structure::ImportSpecifier& begin, const expression::Identifier& end);

      /**
      * \brief Edge end visitor for hasImported edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndImportSpecifier_HasImported(const structure::ImportSpecifier& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDefinition_HasKey(const structure::MethodDefinition& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodDefinition_HasKey(const structure::MethodDefinition& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDefinition_HasValue(const structure::MethodDefinition& begin, const expression::FunctionExpression& end);

      /**
      * \brief Edge end visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodDefinition_HasValue(const structure::MethodDefinition& begin, const expression::FunctionExpression& end);

      /**
      * \brief Edge  visitor for hasLocal edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitModuleSpecifier_HasLocal(const structure::ModuleSpecifier& begin, const expression::Identifier& end);

      /**
      * \brief Edge end visitor for hasLocal edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndModuleSpecifier_HasLocal(const structure::ModuleSpecifier& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPropertyDefinition_HasKey(const structure::PropertyDefinition& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPropertyDefinition_HasKey(const structure::PropertyDefinition& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPropertyDefinition_HasValue(const structure::PropertyDefinition& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPropertyDefinition_HasValue(const structure::PropertyDefinition& begin, const expression::Expression& end);

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
      * \brief Writes out the attributes of the base::Comment node.
      */
      virtual void writeAttributes(const base::Comment& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the base::Named node.
      */
      virtual void writeAttributes(const base::Named& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the base::Positioned node.
      */
      virtual void writeAttributes(const base::Positioned& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the base::Program node.
      */
      virtual void writeAttributes(const base::Program& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the base::System node.
      */
      virtual void writeAttributes(const base::System& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the declaration::ClassDeclaration node.
      */
      virtual void writeAttributes(const declaration::ClassDeclaration& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the declaration::Declaration node.
      */
      virtual void writeAttributes(const declaration::Declaration& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the declaration::ExportAllDeclaration node.
      */
      virtual void writeAttributes(const declaration::ExportAllDeclaration& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the declaration::ExportDefaultDeclaration node.
      */
      virtual void writeAttributes(const declaration::ExportDefaultDeclaration& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the declaration::ExportNamedDeclaration node.
      */
      virtual void writeAttributes(const declaration::ExportNamedDeclaration& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the declaration::FunctionDeclaration node.
      */
      virtual void writeAttributes(const declaration::FunctionDeclaration& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the declaration::ImportDeclaration node.
      */
      virtual void writeAttributes(const declaration::ImportDeclaration& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the declaration::ModuleDeclaration node.
      */
      virtual void writeAttributes(const declaration::ModuleDeclaration& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the declaration::VariableDeclaration node.
      */
      virtual void writeAttributes(const declaration::VariableDeclaration& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the declaration::VariableDeclarator node.
      */
      virtual void writeAttributes(const declaration::VariableDeclarator& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ArrayExpression node.
      */
      virtual void writeAttributes(const expression::ArrayExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ArrowFunctionExpression node.
      */
      virtual void writeAttributes(const expression::ArrowFunctionExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::AssignmentExpression node.
      */
      virtual void writeAttributes(const expression::AssignmentExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::AwaitExpression node.
      */
      virtual void writeAttributes(const expression::AwaitExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::BigIntLiteral node.
      */
      virtual void writeAttributes(const expression::BigIntLiteral& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::BinaryExpression node.
      */
      virtual void writeAttributes(const expression::BinaryExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::BooleanLiteral node.
      */
      virtual void writeAttributes(const expression::BooleanLiteral& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::CallExpression node.
      */
      virtual void writeAttributes(const expression::CallExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ChainElement node.
      */
      virtual void writeAttributes(const expression::ChainElement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ChainExpression node.
      */
      virtual void writeAttributes(const expression::ChainExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ClassExpression node.
      */
      virtual void writeAttributes(const expression::ClassExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ConditionalExpression node.
      */
      virtual void writeAttributes(const expression::ConditionalExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::Expression node.
      */
      virtual void writeAttributes(const expression::Expression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::FunctionExpression node.
      */
      virtual void writeAttributes(const expression::FunctionExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::Identifier node.
      */
      virtual void writeAttributes(const expression::Identifier& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ImportExpression node.
      */
      virtual void writeAttributes(const expression::ImportExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::Literal node.
      */
      virtual void writeAttributes(const expression::Literal& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::LogicalExpression node.
      */
      virtual void writeAttributes(const expression::LogicalExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::MemberExpression node.
      */
      virtual void writeAttributes(const expression::MemberExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::MetaProperty node.
      */
      virtual void writeAttributes(const expression::MetaProperty& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::NewExpression node.
      */
      virtual void writeAttributes(const expression::NewExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::NullLiteral node.
      */
      virtual void writeAttributes(const expression::NullLiteral& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::NumberLiteral node.
      */
      virtual void writeAttributes(const expression::NumberLiteral& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ObjectExpression node.
      */
      virtual void writeAttributes(const expression::ObjectExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::PrivateIdentifier node.
      */
      virtual void writeAttributes(const expression::PrivateIdentifier& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::Property node.
      */
      virtual void writeAttributes(const expression::Property& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::RegExpLiteral node.
      */
      virtual void writeAttributes(const expression::RegExpLiteral& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::SequenceExpression node.
      */
      virtual void writeAttributes(const expression::SequenceExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::SpreadElement node.
      */
      virtual void writeAttributes(const expression::SpreadElement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::StringLiteral node.
      */
      virtual void writeAttributes(const expression::StringLiteral& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::Super node.
      */
      virtual void writeAttributes(const expression::Super& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::TaggedTemplateExpression node.
      */
      virtual void writeAttributes(const expression::TaggedTemplateExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::TemplateElement node.
      */
      virtual void writeAttributes(const expression::TemplateElement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::TemplateLiteral node.
      */
      virtual void writeAttributes(const expression::TemplateLiteral& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ThisExpression node.
      */
      virtual void writeAttributes(const expression::ThisExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::UnaryExpression node.
      */
      virtual void writeAttributes(const expression::UnaryExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::UpdateExpression node.
      */
      virtual void writeAttributes(const expression::UpdateExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::YieldExpression node.
      */
      virtual void writeAttributes(const expression::YieldExpression& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::ArrayPattern node.
      */
      virtual void writeAttributes(const statement::ArrayPattern& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::AssignmentPattern node.
      */
      virtual void writeAttributes(const statement::AssignmentPattern& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::BlockStatement node.
      */
      virtual void writeAttributes(const statement::BlockStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::BreakStatement node.
      */
      virtual void writeAttributes(const statement::BreakStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::CatchClause node.
      */
      virtual void writeAttributes(const statement::CatchClause& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::ContinueStatement node.
      */
      virtual void writeAttributes(const statement::ContinueStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::DebuggerStatement node.
      */
      virtual void writeAttributes(const statement::DebuggerStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::DoWhileStatement node.
      */
      virtual void writeAttributes(const statement::DoWhileStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::EmptyStatement node.
      */
      virtual void writeAttributes(const statement::EmptyStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::ExpressionStatement node.
      */
      virtual void writeAttributes(const statement::ExpressionStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::ForInStatement node.
      */
      virtual void writeAttributes(const statement::ForInStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::ForOfStatement node.
      */
      virtual void writeAttributes(const statement::ForOfStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::ForStatement node.
      */
      virtual void writeAttributes(const statement::ForStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::Function node.
      */
      virtual void writeAttributes(const statement::Function& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::IfStatement node.
      */
      virtual void writeAttributes(const statement::IfStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::LabeledStatement node.
      */
      virtual void writeAttributes(const statement::LabeledStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::ObjectPattern node.
      */
      virtual void writeAttributes(const statement::ObjectPattern& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::Pattern node.
      */
      virtual void writeAttributes(const statement::Pattern& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::RestElement node.
      */
      virtual void writeAttributes(const statement::RestElement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::ReturnStatement node.
      */
      virtual void writeAttributes(const statement::ReturnStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::Statement node.
      */
      virtual void writeAttributes(const statement::Statement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::SwitchCase node.
      */
      virtual void writeAttributes(const statement::SwitchCase& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::SwitchStatement node.
      */
      virtual void writeAttributes(const statement::SwitchStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::ThrowStatement node.
      */
      virtual void writeAttributes(const statement::ThrowStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::TryStatement node.
      */
      virtual void writeAttributes(const statement::TryStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::WhileStatement node.
      */
      virtual void writeAttributes(const statement::WhileStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::WithStatement node.
      */
      virtual void writeAttributes(const statement::WithStatement& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::Class node.
      */
      virtual void writeAttributes(const structure::Class& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ClassBody node.
      */
      virtual void writeAttributes(const structure::ClassBody& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ExportSpecifier node.
      */
      virtual void writeAttributes(const structure::ExportSpecifier& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ImpSpecifier node.
      */
      virtual void writeAttributes(const structure::ImpSpecifier& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ImportDefaultSpecifier node.
      */
      virtual void writeAttributes(const structure::ImportDefaultSpecifier& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ImportNamespaceSpecifier node.
      */
      virtual void writeAttributes(const structure::ImportNamespaceSpecifier& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ImportSpecifier node.
      */
      virtual void writeAttributes(const structure::ImportSpecifier& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::MethodDefinition node.
      */
      virtual void writeAttributes(const structure::MethodDefinition& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ModuleSpecifier node.
      */
      virtual void writeAttributes(const structure::ModuleSpecifier& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::PropertyDefinition node.
      */
      virtual void writeAttributes(const structure::PropertyDefinition& node, bool composite, bool bWithParent = true);

      /** \internal \brief The ofstrem into the xml will be written. */
      std::ofstream &ofs;

      /** \internal \brief Flag to know if the ID of the nodes have to be written or not. */
      bool noId;

      /** \internal \brief Flag to know if the line info of the nodes have to be written or not. */
      bool noLineInfo;

      const std::string projectName;

  }; // VisitorJAVASCRIPTML


}}}
#endif

