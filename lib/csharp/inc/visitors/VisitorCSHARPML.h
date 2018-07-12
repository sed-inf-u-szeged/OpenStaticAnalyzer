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

#ifndef _CSHARP_VISITORCSHARPML_H_
#define _CSHARP_VISITORCSHARPML_H_

#include "csharp/inc/csharp.h"
#include <fstream>

/**
* \file VisitorCSHARPML.h
* \brief Contains declaration of VisitorCSHARPML class.
*/

namespace columbus { namespace csharp { namespace asg {
  /**
  * \brief Creates XML dump of the ASG.
  */
  class VisitorCSHARPML : public Visitor {
    public:

      /**
      * \brief Constructor of XML generator visitor.
      * \param targetStream [in] ofstream to write the output
      * \param projectName  [in] Name of project - generated into the output
      * \param noId         [in] Do not write the ID of the nodes.
      * \param noLineInfo   [in] Do not write the line info of the nodes.
      */
      VisitorCSHARPML(std::ofstream& targetStream,
                      const std::string& _projectName,
                      bool noId = false,
                      bool noLineInfo = false);

      /**
      * \brief Virtual destructor.
      */
      virtual ~VisitorCSHARPML();

      /**
      * \brief This function is calling before the beginning of visiting process. It flushes the header of xml.
      */
      void beginVisit();

      /**
      * \brief This function is calling when the visiting process has finished. It flushes the tail of xml.
      */
      void finishVisit();

      /**
      * \brief Writes the XML representation of the expression::AliasQualifiedNameSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AliasQualifiedNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::AliasQualifiedNameSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AliasQualifiedNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::AnonymousMethodExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AnonymousMethodExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::AnonymousMethodExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AnonymousMethodExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::AnonymousObjectCreationExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AnonymousObjectCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::AnonymousObjectCreationExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AnonymousObjectCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ArrayCreationExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ArrayCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ArrayCreationExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ArrayCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ArrayTypeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ArrayTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ArrayTypeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ArrayTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::AssignmentExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AssignmentExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::AssignmentExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AssignmentExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::AwaitExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AwaitExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::AwaitExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AwaitExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::BaseExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::BaseExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::BaseExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::BaseExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::BinaryExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::BinaryExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::BinaryExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::BinaryExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::CastExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::CastExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::CastExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::CastExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::CheckedExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::CheckedExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::CheckedExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::CheckedExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ConditionalAccessExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ConditionalAccessExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ConditionalAccessExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ConditionalAccessExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ConditionalExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ConditionalExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ConditionalExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ConditionalExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::DefaultExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::DefaultExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::DefaultExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::DefaultExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ElementAccessExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ElementAccessExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ElementAccessExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ElementAccessExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ElementBindingExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ElementBindingExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ElementBindingExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ElementBindingExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::GenericNameSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::GenericNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::GenericNameSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::GenericNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::IdentifierNameSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::IdentifierNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::IdentifierNameSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::IdentifierNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ImplicitArrayCreationExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ImplicitArrayCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ImplicitArrayCreationExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ImplicitArrayCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ImplicitElementAccessSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ImplicitElementAccessSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ImplicitElementAccessSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ImplicitElementAccessSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::InitializerExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::InitializerExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::InitializerExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::InitializerExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::InterpolatedStringExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::InterpolatedStringExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::InterpolatedStringExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::InterpolatedStringExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::InvocationExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::InvocationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::InvocationExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::InvocationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::LiteralExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::LiteralExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::LiteralExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::LiteralExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::MakeRefExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::MakeRefExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::MakeRefExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::MakeRefExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::MemberAccessExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::MemberAccessExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::MemberAccessExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::MemberAccessExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::MemberBindingExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::MemberBindingExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::MemberBindingExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::MemberBindingExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::NullableTypeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::NullableTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::NullableTypeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::NullableTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ObjectCreationExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ObjectCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ObjectCreationExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ObjectCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::OmittedArraySizeExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::OmittedArraySizeExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::OmittedArraySizeExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::OmittedArraySizeExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::OmittedTypeArgumentSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::OmittedTypeArgumentSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::OmittedTypeArgumentSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::OmittedTypeArgumentSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ParenthesizedExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ParenthesizedExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ParenthesizedExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ParenthesizedExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ParenthesizedLambdaExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ParenthesizedLambdaExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ParenthesizedLambdaExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ParenthesizedLambdaExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::PointerTypeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::PointerTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::PointerTypeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::PointerTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::PostfixUnaryExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::PostfixUnaryExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::PostfixUnaryExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::PostfixUnaryExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::PredefinedTypeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::PredefinedTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::PredefinedTypeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::PredefinedTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::PrefixUnaryExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::PrefixUnaryExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::PrefixUnaryExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::PrefixUnaryExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::QualifiedNameSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::QualifiedNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::QualifiedNameSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::QualifiedNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::QueryExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::QueryExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::QueryExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::QueryExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::RefTypeExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::RefTypeExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::RefTypeExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::RefTypeExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::RefValueExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::RefValueExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::RefValueExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::RefValueExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::SimpleLambdaExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::SimpleLambdaExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::SimpleLambdaExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::SimpleLambdaExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::SizeOfExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::SizeOfExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::SizeOfExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::SizeOfExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::StackAllocArrayCreationExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::StackAllocArrayCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::StackAllocArrayCreationExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::StackAllocArrayCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::ThisExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ThisExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::ThisExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ThisExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the expression::TypeOfExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::TypeOfExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the expression::TypeOfExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::TypeOfExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::BlockSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::BlockSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::BlockSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::BlockSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::BreakStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::BreakStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::BreakStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::BreakStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::CheckedStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::CheckedStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::CheckedStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::CheckedStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::ContinueStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ContinueStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::ContinueStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ContinueStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::DoStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::DoStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::DoStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::DoStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::EmptyStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::EmptyStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::EmptyStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::EmptyStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::ExpressionStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ExpressionStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::ExpressionStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ExpressionStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::FixedStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::FixedStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::FixedStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::FixedStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::ForEachStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ForEachStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::ForEachStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ForEachStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::ForStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ForStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::ForStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ForStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::GotoStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::GotoStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::GotoStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::GotoStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::IfStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::IfStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::IfStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::IfStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::LabeledStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::LabeledStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::LabeledStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::LabeledStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::LocalDeclarationStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::LocalDeclarationStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::LocalDeclarationStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::LocalDeclarationStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::LockStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::LockStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::LockStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::LockStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::ReturnStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ReturnStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::ReturnStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ReturnStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::SwitchStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::SwitchStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::SwitchStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::SwitchStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::ThrowStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ThrowStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::ThrowStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ThrowStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::TryStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::TryStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::TryStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::TryStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::UnsafeStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::UnsafeStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::UnsafeStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::UnsafeStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::UsingStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::UsingStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::UsingStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::UsingStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::WhileStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::WhileStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::WhileStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::WhileStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the statement::YieldStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::YieldStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the statement::YieldStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::YieldStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::AccessorDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AccessorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::AccessorDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AccessorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::AccessorListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AccessorListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::AccessorListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AccessorListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::AnonymousObjectMemberDeclaratorSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AnonymousObjectMemberDeclaratorSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::AnonymousObjectMemberDeclaratorSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AnonymousObjectMemberDeclaratorSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ArgumentListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ArgumentListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ArgumentListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ArgumentListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ArgumentSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ArgumentSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ArgumentSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ArgumentSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ArrayRankSpecifierSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ArrayRankSpecifierSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ArrayRankSpecifierSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ArrayRankSpecifierSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ArrowExpressionClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ArrowExpressionClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ArrowExpressionClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ArrowExpressionClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::AttributeArgumentListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AttributeArgumentListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::AttributeArgumentListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AttributeArgumentListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::AttributeArgumentSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AttributeArgumentSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::AttributeArgumentSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AttributeArgumentSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::AttributeListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AttributeListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::AttributeListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AttributeListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::AttributeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AttributeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::AttributeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AttributeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::AttributeTargetSpecifierSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AttributeTargetSpecifierSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::AttributeTargetSpecifierSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AttributeTargetSpecifierSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::BaseListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::BaseListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::BaseListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::BaseListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::BracketedArgumentListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::BracketedArgumentListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::BracketedArgumentListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::BracketedArgumentListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::BracketedParameterListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::BracketedParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::BracketedParameterListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::BracketedParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::CaseSwitchLabelSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CaseSwitchLabelSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::CaseSwitchLabelSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CaseSwitchLabelSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::CatchClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CatchClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::CatchClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CatchClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::CatchDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CatchDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::CatchDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CatchDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::CatchFilterClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CatchFilterClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::CatchFilterClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CatchFilterClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ClassDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ClassDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ClassDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ClassDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ClassOrStructConstraintSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ClassOrStructConstraintSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ClassOrStructConstraintSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ClassOrStructConstraintSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::CompilationUnitSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CompilationUnitSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::CompilationUnitSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CompilationUnitSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ConstructorConstraintSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ConstructorConstraintSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ConstructorConstraintSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ConstructorConstraintSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ConstructorDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ConstructorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ConstructorDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ConstructorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ConstructorInitializerSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ConstructorInitializerSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ConstructorInitializerSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ConstructorInitializerSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ConversionOperatorDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ConversionOperatorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ConversionOperatorDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ConversionOperatorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ConversionOperatorMemberCrefSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ConversionOperatorMemberCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ConversionOperatorMemberCrefSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ConversionOperatorMemberCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::CrefBracketedParameterListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CrefBracketedParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::CrefBracketedParameterListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CrefBracketedParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::CrefParameterListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CrefParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::CrefParameterListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CrefParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::CrefParameterSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CrefParameterSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::CrefParameterSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CrefParameterSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::DefaultSwitchLabelSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::DefaultSwitchLabelSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::DefaultSwitchLabelSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::DefaultSwitchLabelSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::DelegateDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::DelegateDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::DelegateDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::DelegateDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::DestructorDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::DestructorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::DestructorDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::DestructorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ElseClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ElseClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ElseClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ElseClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::EnumDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::EnumDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::EnumDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::EnumDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::EnumMemberDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::EnumMemberDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::EnumMemberDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::EnumMemberDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::EqualsValueClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::EqualsValueClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::EqualsValueClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::EqualsValueClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::EventDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::EventDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::EventDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::EventDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::EventFieldDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::EventFieldDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::EventFieldDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::EventFieldDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ExplicitInterfaceSpecifierSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ExplicitInterfaceSpecifierSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ExplicitInterfaceSpecifierSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ExplicitInterfaceSpecifierSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ExternAliasDirectiveSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ExternAliasDirectiveSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ExternAliasDirectiveSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ExternAliasDirectiveSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::FieldDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::FieldDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::FieldDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::FieldDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::FinallyClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::FinallyClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::FinallyClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::FinallyClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::FromClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::FromClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::FromClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::FromClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::GlobalStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::GlobalStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::GlobalStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::GlobalStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::GroupClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::GroupClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::GroupClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::GroupClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::IncompleteMemberSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::IncompleteMemberSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::IncompleteMemberSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::IncompleteMemberSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::IndexerDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::IndexerDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::IndexerDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::IndexerDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::IndexerMemberCrefSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::IndexerMemberCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::IndexerMemberCrefSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::IndexerMemberCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::InterfaceDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::InterfaceDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::InterfaceDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::InterfaceDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::InterpolatedStringTextSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::InterpolatedStringTextSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::InterpolatedStringTextSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::InterpolatedStringTextSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::InterpolationAlignmentClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::InterpolationAlignmentClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::InterpolationAlignmentClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::InterpolationAlignmentClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::InterpolationFormatClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::InterpolationFormatClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::InterpolationFormatClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::InterpolationFormatClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::InterpolationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::InterpolationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::InterpolationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::InterpolationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::JoinClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::JoinClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::JoinClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::JoinClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::JoinIntoClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::JoinIntoClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::JoinIntoClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::JoinIntoClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::LetClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::LetClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::LetClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::LetClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::MethodDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::MethodDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::MethodDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::MethodDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::NameColonSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::NameColonSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::NameColonSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::NameColonSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::NameEqualsSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::NameEqualsSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::NameEqualsSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::NameEqualsSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::NameMemberCrefSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::NameMemberCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::NameMemberCrefSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::NameMemberCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::NamespaceDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::NamespaceDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::NamespaceDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::NamespaceDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::OperatorDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::OperatorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::OperatorDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::OperatorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::OperatorMemberCrefSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::OperatorMemberCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::OperatorMemberCrefSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::OperatorMemberCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::OrderByClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::OrderByClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::OrderByClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::OrderByClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::OrderingSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::OrderingSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::OrderingSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::OrderingSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ParameterListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ParameterListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::ParameterSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ParameterSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::ParameterSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ParameterSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::PropertyDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::PropertyDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::PropertyDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::PropertyDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::QualifiedCrefSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::QualifiedCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::QualifiedCrefSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::QualifiedCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::QueryBodySyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::QueryBodySyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::QueryBodySyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::QueryBodySyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::QueryContinuationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::QueryContinuationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::QueryContinuationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::QueryContinuationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::SelectClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::SelectClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::SelectClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::SelectClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::SimpleBaseTypeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::SimpleBaseTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::SimpleBaseTypeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::SimpleBaseTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::StructDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::StructDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::StructDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::StructDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::SwitchSectionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::SwitchSectionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::SwitchSectionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::SwitchSectionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::SyntaxToken node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::SyntaxToken& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::SyntaxToken node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::SyntaxToken& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::TypeArgumentListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::TypeArgumentListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::TypeArgumentListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::TypeArgumentListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::TypeConstraintSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::TypeConstraintSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::TypeConstraintSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::TypeConstraintSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::TypeCrefSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::TypeCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::TypeCrefSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::TypeCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::TypeParameterConstraintClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::TypeParameterConstraintClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::TypeParameterConstraintClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::TypeParameterConstraintClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::TypeParameterListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::TypeParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::TypeParameterListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::TypeParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::TypeParameterSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::TypeParameterSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::TypeParameterSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::TypeParameterSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::UsingDirectiveSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::UsingDirectiveSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::UsingDirectiveSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::UsingDirectiveSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::VariableDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::VariableDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::VariableDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::VariableDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::VariableDeclaratorSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::VariableDeclaratorSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::VariableDeclaratorSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::VariableDeclaratorSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::WhereClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::WhereClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::WhereClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::WhereClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::XmlCDataSectionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlCDataSectionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::XmlCDataSectionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlCDataSectionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::XmlCommentSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlCommentSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::XmlCommentSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlCommentSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::XmlCrefAttributeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlCrefAttributeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::XmlCrefAttributeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlCrefAttributeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::XmlElementEndTagSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlElementEndTagSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::XmlElementEndTagSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlElementEndTagSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::XmlElementStartTagSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlElementStartTagSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::XmlElementStartTagSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlElementStartTagSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::XmlElementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlElementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::XmlElementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlElementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::XmlEmptyElementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlEmptyElementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::XmlEmptyElementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlEmptyElementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::XmlNameAttributeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlNameAttributeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::XmlNameAttributeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlNameAttributeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::XmlNameSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::XmlNameSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::XmlPrefixSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlPrefixSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::XmlPrefixSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlPrefixSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::XmlProcessingInstructionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlProcessingInstructionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::XmlProcessingInstructionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlProcessingInstructionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::XmlTextAttributeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlTextAttributeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::XmlTextAttributeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlTextAttributeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the XML representation of the structure::XmlTextSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlTextSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the end part of XML representation of the structure::XmlTextSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlTextSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Edge  visitor for Alias edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAliasQualifiedNameSyntax_Alias(const expression::AliasQualifiedNameSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge end visitor for Alias edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAliasQualifiedNameSyntax_Alias(const expression::AliasQualifiedNameSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAliasQualifiedNameSyntax_Name(const expression::AliasQualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAliasQualifiedNameSyntax_Name(const expression::AliasQualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnonymousFunctionExpressionSyntax_Body(const expression::AnonymousFunctionExpressionSyntax& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAnonymousFunctionExpressionSyntax_Body(const expression::AnonymousFunctionExpressionSyntax& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnonymousMethodExpressionSyntax_ParameterList(const expression::AnonymousMethodExpressionSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge end visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAnonymousMethodExpressionSyntax_ParameterList(const expression::AnonymousMethodExpressionSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Initializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnonymousObjectCreationExpressionSyntax_Initializers(const expression::AnonymousObjectCreationExpressionSyntax& begin, const structure::AnonymousObjectMemberDeclaratorSyntax& end);

      /**
      * \brief Edge end visitor for Initializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAnonymousObjectCreationExpressionSyntax_Initializers(const expression::AnonymousObjectCreationExpressionSyntax& begin, const structure::AnonymousObjectMemberDeclaratorSyntax& end);

      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayCreationExpressionSyntax_Initializer(const expression::ArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArrayCreationExpressionSyntax_Initializer(const expression::ArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayCreationExpressionSyntax_Type(const expression::ArrayCreationExpressionSyntax& begin, const expression::ArrayTypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArrayCreationExpressionSyntax_Type(const expression::ArrayCreationExpressionSyntax& begin, const expression::ArrayTypeSyntax& end);

      /**
      * \brief Edge  visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayTypeSyntax_ElementType(const expression::ArrayTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArrayTypeSyntax_ElementType(const expression::ArrayTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for RankSpecifiers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayTypeSyntax_RankSpecifiers(const expression::ArrayTypeSyntax& begin, const structure::ArrayRankSpecifierSyntax& end);

      /**
      * \brief Edge end visitor for RankSpecifiers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArrayTypeSyntax_RankSpecifiers(const expression::ArrayTypeSyntax& begin, const structure::ArrayRankSpecifierSyntax& end);

      /**
      * \brief Edge visitor for EventAccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentExpressionSyntax_EventAccessorCall(const expression::AssignmentExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for EventAccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssignmentExpressionSyntax_EventAccessorCall(const expression::AssignmentExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentExpressionSyntax_Left(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssignmentExpressionSyntax_Left(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentExpressionSyntax_OverloadedOperatorCall(const expression::AssignmentExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssignmentExpressionSyntax_OverloadedOperatorCall(const expression::AssignmentExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentExpressionSyntax_Right(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssignmentExpressionSyntax_Right(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAwaitExpressionSyntax_Expression(const expression::AwaitExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAwaitExpressionSyntax_Expression(const expression::AwaitExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinaryExpressionSyntax_Left(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBinaryExpressionSyntax_Left(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinaryExpressionSyntax_OverloadedOperatorCall(const expression::BinaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBinaryExpressionSyntax_OverloadedOperatorCall(const expression::BinaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinaryExpressionSyntax_Right(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBinaryExpressionSyntax_Right(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge visitor for ConversionOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCastExpressionSyntax_ConversionOperatorCall(const expression::CastExpressionSyntax& begin, const structure::ConversionOperatorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for ConversionOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCastExpressionSyntax_ConversionOperatorCall(const expression::CastExpressionSyntax& begin, const structure::ConversionOperatorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCastExpressionSyntax_Expression(const expression::CastExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCastExpressionSyntax_Expression(const expression::CastExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCastExpressionSyntax_Type(const expression::CastExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCastExpressionSyntax_Type(const expression::CastExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCheckedExpressionSyntax_Expression(const expression::CheckedExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCheckedExpressionSyntax_Expression(const expression::CheckedExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalAccessExpressionSyntax_Expression(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConditionalAccessExpressionSyntax_Expression(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for WhenNotNull edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalAccessExpressionSyntax_WhenNotNull(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for WhenNotNull edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConditionalAccessExpressionSyntax_WhenNotNull(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalExpressionSyntax_Condition(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConditionalExpressionSyntax_Condition(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for WhenFalse edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalExpressionSyntax_WhenFalse(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for WhenFalse edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConditionalExpressionSyntax_WhenFalse(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for WhenTrue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalExpressionSyntax_WhenTrue(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for WhenTrue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConditionalExpressionSyntax_WhenTrue(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDefaultExpressionSyntax_Type(const expression::DefaultExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDefaultExpressionSyntax_Type(const expression::DefaultExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge visitor for AccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitElementAccessExpressionSyntax_AccessorCall(const expression::ElementAccessExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for AccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndElementAccessExpressionSyntax_AccessorCall(const expression::ElementAccessExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitElementAccessExpressionSyntax_ArgumentList(const expression::ElementAccessExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndElementAccessExpressionSyntax_ArgumentList(const expression::ElementAccessExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitElementAccessExpressionSyntax_Expression(const expression::ElementAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndElementAccessExpressionSyntax_Expression(const expression::ElementAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitElementBindingExpressionSyntax_ArgumentList(const expression::ElementBindingExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndElementBindingExpressionSyntax_ArgumentList(const expression::ElementBindingExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge  visitor for TypeArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGenericNameSyntax_TypeArgumentList(const expression::GenericNameSyntax& begin, const structure::TypeArgumentListSyntax& end);

      /**
      * \brief Edge end visitor for TypeArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndGenericNameSyntax_TypeArgumentList(const expression::GenericNameSyntax& begin, const structure::TypeArgumentListSyntax& end);

      /**
      * \brief Edge visitor for AccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIdentifierNameSyntax_AccessorCall(const expression::IdentifierNameSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for AccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIdentifierNameSyntax_AccessorCall(const expression::IdentifierNameSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for Declaration edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIdentifierNameSyntax_Declaration(const expression::IdentifierNameSyntax& begin, const base::Positioned& end);

      /**
      * \brief Edge visitor for Declaration edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIdentifierNameSyntax_Declaration(const expression::IdentifierNameSyntax& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImplicitArrayCreationExpressionSyntax_Initializer(const expression::ImplicitArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndImplicitArrayCreationExpressionSyntax_Initializer(const expression::ImplicitArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImplicitElementAccessSyntax_ArgumentList(const expression::ImplicitElementAccessSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndImplicitElementAccessSyntax_ArgumentList(const expression::ImplicitElementAccessSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge  visitor for Expressions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInitializerExpressionSyntax_Expressions(const expression::InitializerExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expressions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInitializerExpressionSyntax_Expressions(const expression::InitializerExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Contents edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInterpolatedStringExpressionSyntax_Contents(const expression::InterpolatedStringExpressionSyntax& begin, const structure::InterpolatedStringContentSyntax& end);

      /**
      * \brief Edge end visitor for Contents edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInterpolatedStringExpressionSyntax_Contents(const expression::InterpolatedStringExpressionSyntax& begin, const structure::InterpolatedStringContentSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInvocationExpressionSyntax_ArgumentList(const expression::InvocationExpressionSyntax& begin, const structure::ArgumentListSyntax& end);

      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInvocationExpressionSyntax_ArgumentList(const expression::InvocationExpressionSyntax& begin, const structure::ArgumentListSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInvocationExpressionSyntax_Expression(const expression::InvocationExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInvocationExpressionSyntax_Expression(const expression::InvocationExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge visitor for MethodCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInvocationExpressionSyntax_MethodCall(const expression::InvocationExpressionSyntax& begin, const structure::MethodDeclarationSyntax& end);

      /**
      * \brief Edge visitor for MethodCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInvocationExpressionSyntax_MethodCall(const expression::InvocationExpressionSyntax& begin, const structure::MethodDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMakeRefExpressionSyntax_Expression(const expression::MakeRefExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMakeRefExpressionSyntax_Expression(const expression::MakeRefExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMemberAccessExpressionSyntax_Expression(const expression::MemberAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMemberAccessExpressionSyntax_Expression(const expression::MemberAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMemberAccessExpressionSyntax_Name(const expression::MemberAccessExpressionSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMemberAccessExpressionSyntax_Name(const expression::MemberAccessExpressionSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMemberBindingExpressionSyntax_Name(const expression::MemberBindingExpressionSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMemberBindingExpressionSyntax_Name(const expression::MemberBindingExpressionSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge  visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNullableTypeSyntax_ElementType(const expression::NullableTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNullableTypeSyntax_ElementType(const expression::NullableTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObjectCreationExpressionSyntax_ArgumentList(const expression::ObjectCreationExpressionSyntax& begin, const structure::ArgumentListSyntax& end);

      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndObjectCreationExpressionSyntax_ArgumentList(const expression::ObjectCreationExpressionSyntax& begin, const structure::ArgumentListSyntax& end);

      /**
      * \brief Edge visitor for ConstructorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObjectCreationExpressionSyntax_ConstructorCall(const expression::ObjectCreationExpressionSyntax& begin, const structure::ConstructorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for ConstructorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndObjectCreationExpressionSyntax_ConstructorCall(const expression::ObjectCreationExpressionSyntax& begin, const structure::ConstructorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObjectCreationExpressionSyntax_Initializer(const expression::ObjectCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndObjectCreationExpressionSyntax_Initializer(const expression::ObjectCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObjectCreationExpressionSyntax_Type(const expression::ObjectCreationExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndObjectCreationExpressionSyntax_Type(const expression::ObjectCreationExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParenthesizedExpressionSyntax_Expression(const expression::ParenthesizedExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndParenthesizedExpressionSyntax_Expression(const expression::ParenthesizedExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParenthesizedLambdaExpressionSyntax_ParameterList(const expression::ParenthesizedLambdaExpressionSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge end visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndParenthesizedLambdaExpressionSyntax_ParameterList(const expression::ParenthesizedLambdaExpressionSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge  visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPointerTypeSyntax_ElementType(const expression::PointerTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPointerTypeSyntax_ElementType(const expression::PointerTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Operand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPostfixUnaryExpressionSyntax_Operand(const expression::PostfixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Operand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPostfixUnaryExpressionSyntax_Operand(const expression::PostfixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPostfixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PostfixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPostfixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PostfixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Operand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPrefixUnaryExpressionSyntax_Operand(const expression::PrefixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Operand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPrefixUnaryExpressionSyntax_Operand(const expression::PrefixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPrefixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PrefixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPrefixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PrefixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQualifiedNameSyntax_Left(const expression::QualifiedNameSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge end visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQualifiedNameSyntax_Left(const expression::QualifiedNameSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge  visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQualifiedNameSyntax_Right(const expression::QualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge end visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQualifiedNameSyntax_Right(const expression::QualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQueryExpressionSyntax_Body(const expression::QueryExpressionSyntax& begin, const structure::QueryBodySyntax& end);

      /**
      * \brief Edge end visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQueryExpressionSyntax_Body(const expression::QueryExpressionSyntax& begin, const structure::QueryBodySyntax& end);

      /**
      * \brief Edge  visitor for FromClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQueryExpressionSyntax_FromClause(const expression::QueryExpressionSyntax& begin, const structure::FromClauseSyntax& end);

      /**
      * \brief Edge end visitor for FromClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQueryExpressionSyntax_FromClause(const expression::QueryExpressionSyntax& begin, const structure::FromClauseSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitRefTypeExpressionSyntax_Expression(const expression::RefTypeExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndRefTypeExpressionSyntax_Expression(const expression::RefTypeExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitRefValueExpressionSyntax_Expression(const expression::RefValueExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndRefValueExpressionSyntax_Expression(const expression::RefValueExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitRefValueExpressionSyntax_Type(const expression::RefValueExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndRefValueExpressionSyntax_Type(const expression::RefValueExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Parameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSimpleLambdaExpressionSyntax_Parameter(const expression::SimpleLambdaExpressionSyntax& begin, const structure::ParameterSyntax& end);

      /**
      * \brief Edge end visitor for Parameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSimpleLambdaExpressionSyntax_Parameter(const expression::SimpleLambdaExpressionSyntax& begin, const structure::ParameterSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSizeOfExpressionSyntax_Type(const expression::SizeOfExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSizeOfExpressionSyntax_Type(const expression::SizeOfExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitStackAllocArrayCreationExpressionSyntax_Type(const expression::StackAllocArrayCreationExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndStackAllocArrayCreationExpressionSyntax_Type(const expression::StackAllocArrayCreationExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeOfExpressionSyntax_Type(const expression::TypeOfExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeOfExpressionSyntax_Type(const expression::TypeOfExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge visitor for OriginalDefinition edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeSyntax_OriginalDefinition(const expression::TypeSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge visitor for OriginalDefinition edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeSyntax_OriginalDefinition(const expression::TypeSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Statements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBlockSyntax_Statements(const statement::BlockSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBlockSyntax_Statements(const statement::BlockSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCheckedStatementSyntax_Block(const statement::CheckedStatementSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge end visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCheckedStatementSyntax_Block(const statement::CheckedStatementSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDoStatementSyntax_Condition(const statement::DoStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDoStatementSyntax_Condition(const statement::DoStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDoStatementSyntax_Statement(const statement::DoStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDoStatementSyntax_Statement(const statement::DoStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExpressionStatementSyntax_Expression(const statement::ExpressionStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExpressionStatementSyntax_Expression(const statement::ExpressionStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFixedStatementSyntax_Declaration(const statement::FixedStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFixedStatementSyntax_Declaration(const statement::FixedStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFixedStatementSyntax_Statement(const statement::FixedStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFixedStatementSyntax_Statement(const statement::FixedStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForEachStatementSyntax_Expression(const statement::ForEachStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForEachStatementSyntax_Expression(const statement::ForEachStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForEachStatementSyntax_Statement(const statement::ForEachStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForEachStatementSyntax_Statement(const statement::ForEachStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForEachStatementSyntax_Type(const statement::ForEachStatementSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForEachStatementSyntax_Type(const statement::ForEachStatementSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatementSyntax_Condition(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForStatementSyntax_Condition(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatementSyntax_Declaration(const statement::ForStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForStatementSyntax_Declaration(const statement::ForStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Incrementors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatementSyntax_Incrementors(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Incrementors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForStatementSyntax_Incrementors(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Initializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatementSyntax_Initializers(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Initializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForStatementSyntax_Initializers(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatementSyntax_Statement(const statement::ForStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForStatementSyntax_Statement(const statement::ForStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGotoStatementSyntax_Expression(const statement::GotoStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndGotoStatementSyntax_Expression(const statement::GotoStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfStatementSyntax_Condition(const statement::IfStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIfStatementSyntax_Condition(const statement::IfStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Else edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfStatementSyntax_Else(const statement::IfStatementSyntax& begin, const structure::ElseClauseSyntax& end);

      /**
      * \brief Edge end visitor for Else edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIfStatementSyntax_Else(const statement::IfStatementSyntax& begin, const structure::ElseClauseSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfStatementSyntax_Statement(const statement::IfStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIfStatementSyntax_Statement(const statement::IfStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLabeledStatementSyntax_Statement(const statement::LabeledStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLabeledStatementSyntax_Statement(const statement::LabeledStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLocalDeclarationStatementSyntax_Declaration(const statement::LocalDeclarationStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLocalDeclarationStatementSyntax_Declaration(const statement::LocalDeclarationStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLockStatementSyntax_Expression(const statement::LockStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLockStatementSyntax_Expression(const statement::LockStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLockStatementSyntax_Statement(const statement::LockStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLockStatementSyntax_Statement(const statement::LockStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitReturnStatementSyntax_Expression(const statement::ReturnStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndReturnStatementSyntax_Expression(const statement::ReturnStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchStatementSyntax_Expression(const statement::SwitchStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSwitchStatementSyntax_Expression(const statement::SwitchStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Sections edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchStatementSyntax_Sections(const statement::SwitchStatementSyntax& begin, const structure::SwitchSectionSyntax& end);

      /**
      * \brief Edge end visitor for Sections edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSwitchStatementSyntax_Sections(const statement::SwitchStatementSyntax& begin, const structure::SwitchSectionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitThrowStatementSyntax_Expression(const statement::ThrowStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndThrowStatementSyntax_Expression(const statement::ThrowStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryStatementSyntax_Block(const statement::TryStatementSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge end visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTryStatementSyntax_Block(const statement::TryStatementSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for Catches edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryStatementSyntax_Catches(const statement::TryStatementSyntax& begin, const structure::CatchClauseSyntax& end);

      /**
      * \brief Edge end visitor for Catches edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTryStatementSyntax_Catches(const statement::TryStatementSyntax& begin, const structure::CatchClauseSyntax& end);

      /**
      * \brief Edge  visitor for Finally edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryStatementSyntax_Finally(const statement::TryStatementSyntax& begin, const structure::FinallyClauseSyntax& end);

      /**
      * \brief Edge end visitor for Finally edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTryStatementSyntax_Finally(const statement::TryStatementSyntax& begin, const structure::FinallyClauseSyntax& end);

      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUnsafeStatementSyntax_Block(const statement::UnsafeStatementSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge end visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUnsafeStatementSyntax_Block(const statement::UnsafeStatementSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUsingStatementSyntax_Declaration(const statement::UsingStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUsingStatementSyntax_Declaration(const statement::UsingStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUsingStatementSyntax_Expression(const statement::UsingStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUsingStatementSyntax_Expression(const statement::UsingStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUsingStatementSyntax_Statement(const statement::UsingStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUsingStatementSyntax_Statement(const statement::UsingStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhileStatementSyntax_Condition(const statement::WhileStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndWhileStatementSyntax_Condition(const statement::WhileStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhileStatementSyntax_Statement(const statement::WhileStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndWhileStatementSyntax_Statement(const statement::WhileStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitYieldStatementSyntax_Expression(const statement::YieldStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndYieldStatementSyntax_Expression(const statement::YieldStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAccessorDeclarationSyntax_AttributeLists(const structure::AccessorDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAccessorDeclarationSyntax_AttributeLists(const structure::AccessorDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAccessorDeclarationSyntax_Body(const structure::AccessorDeclarationSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge end visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAccessorDeclarationSyntax_Body(const structure::AccessorDeclarationSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for Accessors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAccessorListSyntax_Accessors(const structure::AccessorListSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Accessors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAccessorListSyntax_Accessors(const structure::AccessorListSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnonymousObjectMemberDeclaratorSyntax_Expression(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAnonymousObjectMemberDeclaratorSyntax_Expression(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for NameEquals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnonymousObjectMemberDeclaratorSyntax_NameEquals(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const structure::NameEqualsSyntax& end);

      /**
      * \brief Edge end visitor for NameEquals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAnonymousObjectMemberDeclaratorSyntax_NameEquals(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const structure::NameEqualsSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArgumentSyntax_Expression(const structure::ArgumentSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArgumentSyntax_Expression(const structure::ArgumentSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for NameColon edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArgumentSyntax_NameColon(const structure::ArgumentSyntax& begin, const structure::NameColonSyntax& end);

      /**
      * \brief Edge end visitor for NameColon edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArgumentSyntax_NameColon(const structure::ArgumentSyntax& begin, const structure::NameColonSyntax& end);

      /**
      * \brief Edge  visitor for Sizes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayRankSpecifierSyntax_Sizes(const structure::ArrayRankSpecifierSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Sizes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArrayRankSpecifierSyntax_Sizes(const structure::ArrayRankSpecifierSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrowExpressionClauseSyntax_Expression(const structure::ArrowExpressionClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArrowExpressionClauseSyntax_Expression(const structure::ArrowExpressionClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeArgumentListSyntax_Arguments(const structure::AttributeArgumentListSyntax& begin, const structure::AttributeArgumentSyntax& end);

      /**
      * \brief Edge end visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAttributeArgumentListSyntax_Arguments(const structure::AttributeArgumentListSyntax& begin, const structure::AttributeArgumentSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeArgumentSyntax_Expression(const structure::AttributeArgumentSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAttributeArgumentSyntax_Expression(const structure::AttributeArgumentSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for NameColon edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeArgumentSyntax_NameColon(const structure::AttributeArgumentSyntax& begin, const structure::NameColonSyntax& end);

      /**
      * \brief Edge end visitor for NameColon edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAttributeArgumentSyntax_NameColon(const structure::AttributeArgumentSyntax& begin, const structure::NameColonSyntax& end);

      /**
      * \brief Edge  visitor for NameEquals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeArgumentSyntax_NameEquals(const structure::AttributeArgumentSyntax& begin, const structure::NameEqualsSyntax& end);

      /**
      * \brief Edge end visitor for NameEquals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAttributeArgumentSyntax_NameEquals(const structure::AttributeArgumentSyntax& begin, const structure::NameEqualsSyntax& end);

      /**
      * \brief Edge  visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeListSyntax_Attributes(const structure::AttributeListSyntax& begin, const structure::AttributeSyntax& end);

      /**
      * \brief Edge end visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAttributeListSyntax_Attributes(const structure::AttributeListSyntax& begin, const structure::AttributeSyntax& end);

      /**
      * \brief Edge  visitor for Target edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeListSyntax_Target(const structure::AttributeListSyntax& begin, const structure::AttributeTargetSpecifierSyntax& end);

      /**
      * \brief Edge end visitor for Target edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAttributeListSyntax_Target(const structure::AttributeListSyntax& begin, const structure::AttributeTargetSpecifierSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeSyntax_ArgumentList(const structure::AttributeSyntax& begin, const structure::AttributeArgumentListSyntax& end);

      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAttributeSyntax_ArgumentList(const structure::AttributeSyntax& begin, const structure::AttributeArgumentListSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeSyntax_Name(const structure::AttributeSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAttributeSyntax_Name(const structure::AttributeSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge  visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseArgumentListSyntax_Arguments(const structure::BaseArgumentListSyntax& begin, const structure::ArgumentSyntax& end);

      /**
      * \brief Edge end visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseArgumentListSyntax_Arguments(const structure::BaseArgumentListSyntax& begin, const structure::ArgumentSyntax& end);

      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseCrefParameterListSyntax_Parameters(const structure::BaseCrefParameterListSyntax& begin, const structure::CrefParameterSyntax& end);

      /**
      * \brief Edge end visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseCrefParameterListSyntax_Parameters(const structure::BaseCrefParameterListSyntax& begin, const structure::CrefParameterSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseFieldDeclarationSyntax_AttributeLists(const structure::BaseFieldDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseFieldDeclarationSyntax_AttributeLists(const structure::BaseFieldDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseFieldDeclarationSyntax_Declaration(const structure::BaseFieldDeclarationSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseFieldDeclarationSyntax_Declaration(const structure::BaseFieldDeclarationSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Types edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseListSyntax_Types(const structure::BaseListSyntax& begin, const structure::BaseTypeSyntax& end);

      /**
      * \brief Edge end visitor for Types edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseListSyntax_Types(const structure::BaseListSyntax& begin, const structure::BaseTypeSyntax& end);

      /**
      * \brief Edge visitor for AccessedEnumMembers edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseMethodDeclarationSyntax_AccessedEnumMembers(const structure::BaseMethodDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end);

      /**
      * \brief Edge visitor for AccessedEnumMembers edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseMethodDeclarationSyntax_AccessedEnumMembers(const structure::BaseMethodDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseMethodDeclarationSyntax_AttributeLists(const structure::BaseMethodDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseMethodDeclarationSyntax_AttributeLists(const structure::BaseMethodDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseMethodDeclarationSyntax_Body(const structure::BaseMethodDeclarationSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge end visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseMethodDeclarationSyntax_Body(const structure::BaseMethodDeclarationSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseMethodDeclarationSyntax_ParameterList(const structure::BaseMethodDeclarationSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge end visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseMethodDeclarationSyntax_ParameterList(const structure::BaseMethodDeclarationSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseParameterListSyntax_Parameters(const structure::BaseParameterListSyntax& begin, const structure::ParameterSyntax& end);

      /**
      * \brief Edge end visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseParameterListSyntax_Parameters(const structure::BaseParameterListSyntax& begin, const structure::ParameterSyntax& end);

      /**
      * \brief Edge  visitor for AccessorList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasePropertyDeclarationSyntax_AccessorList(const structure::BasePropertyDeclarationSyntax& begin, const structure::AccessorListSyntax& end);

      /**
      * \brief Edge end visitor for AccessorList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBasePropertyDeclarationSyntax_AccessorList(const structure::BasePropertyDeclarationSyntax& begin, const structure::AccessorListSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasePropertyDeclarationSyntax_AttributeLists(const structure::BasePropertyDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBasePropertyDeclarationSyntax_AttributeLists(const structure::BasePropertyDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for ExplicitInterfaceSpecifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::BasePropertyDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end);

      /**
      * \brief Edge end visitor for ExplicitInterfaceSpecifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::BasePropertyDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasePropertyDeclarationSyntax_Type(const structure::BasePropertyDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBasePropertyDeclarationSyntax_Type(const structure::BasePropertyDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseTypeDeclarationSyntax_AttributeLists(const structure::BaseTypeDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseTypeDeclarationSyntax_AttributeLists(const structure::BaseTypeDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for BaseList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseTypeDeclarationSyntax_BaseList(const structure::BaseTypeDeclarationSyntax& begin, const structure::BaseListSyntax& end);

      /**
      * \brief Edge end visitor for BaseList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseTypeDeclarationSyntax_BaseList(const structure::BaseTypeDeclarationSyntax& begin, const structure::BaseListSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseTypeSyntax_Type(const structure::BaseTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseTypeSyntax_Type(const structure::BaseTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCaseSwitchLabelSyntax_Value(const structure::CaseSwitchLabelSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCaseSwitchLabelSyntax_Value(const structure::CaseSwitchLabelSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchClauseSyntax_Block(const structure::CatchClauseSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge end visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCatchClauseSyntax_Block(const structure::CatchClauseSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchClauseSyntax_Declaration(const structure::CatchClauseSyntax& begin, const structure::CatchDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCatchClauseSyntax_Declaration(const structure::CatchClauseSyntax& begin, const structure::CatchDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Filter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchClauseSyntax_Filter(const structure::CatchClauseSyntax& begin, const structure::CatchFilterClauseSyntax& end);

      /**
      * \brief Edge end visitor for Filter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCatchClauseSyntax_Filter(const structure::CatchClauseSyntax& begin, const structure::CatchFilterClauseSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchDeclarationSyntax_Type(const structure::CatchDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCatchDeclarationSyntax_Type(const structure::CatchDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for FilterExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchFilterClauseSyntax_FilterExpression(const structure::CatchFilterClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for FilterExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCatchFilterClauseSyntax_FilterExpression(const structure::CatchFilterClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnitSyntax_AttributeLists(const structure::CompilationUnitSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCompilationUnitSyntax_AttributeLists(const structure::CompilationUnitSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Externs edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnitSyntax_Externs(const structure::CompilationUnitSyntax& begin, const structure::ExternAliasDirectiveSyntax& end);

      /**
      * \brief Edge end visitor for Externs edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCompilationUnitSyntax_Externs(const structure::CompilationUnitSyntax& begin, const structure::ExternAliasDirectiveSyntax& end);

      /**
      * \brief Edge  visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnitSyntax_Members(const structure::CompilationUnitSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCompilationUnitSyntax_Members(const structure::CompilationUnitSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Usings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnitSyntax_Usings(const structure::CompilationUnitSyntax& begin, const structure::UsingDirectiveSyntax& end);

      /**
      * \brief Edge end visitor for Usings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCompilationUnitSyntax_Usings(const structure::CompilationUnitSyntax& begin, const structure::UsingDirectiveSyntax& end);

      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConstructorDeclarationSyntax_Initializer(const structure::ConstructorDeclarationSyntax& begin, const structure::ConstructorInitializerSyntax& end);

      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConstructorDeclarationSyntax_Initializer(const structure::ConstructorDeclarationSyntax& begin, const structure::ConstructorInitializerSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConstructorInitializerSyntax_ArgumentList(const structure::ConstructorInitializerSyntax& begin, const structure::ArgumentListSyntax& end);

      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConstructorInitializerSyntax_ArgumentList(const structure::ConstructorInitializerSyntax& begin, const structure::ArgumentListSyntax& end);

      /**
      * \brief Edge visitor for ConstructorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConstructorInitializerSyntax_ConstructorCall(const structure::ConstructorInitializerSyntax& begin, const structure::ConstructorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for ConstructorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConstructorInitializerSyntax_ConstructorCall(const structure::ConstructorInitializerSyntax& begin, const structure::ConstructorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConversionOperatorDeclarationSyntax_ExpressionBody(const structure::ConversionOperatorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge end visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConversionOperatorDeclarationSyntax_ExpressionBody(const structure::ConversionOperatorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConversionOperatorDeclarationSyntax_Type(const structure::ConversionOperatorDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConversionOperatorDeclarationSyntax_Type(const structure::ConversionOperatorDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConversionOperatorMemberCrefSyntax_Parameters(const structure::ConversionOperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end);

      /**
      * \brief Edge end visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConversionOperatorMemberCrefSyntax_Parameters(const structure::ConversionOperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConversionOperatorMemberCrefSyntax_Type(const structure::ConversionOperatorMemberCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConversionOperatorMemberCrefSyntax_Type(const structure::ConversionOperatorMemberCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCrefParameterSyntax_Type(const structure::CrefParameterSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCrefParameterSyntax_Type(const structure::CrefParameterSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDelegateDeclarationSyntax_AttributeLists(const structure::DelegateDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDelegateDeclarationSyntax_AttributeLists(const structure::DelegateDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDelegateDeclarationSyntax_ConstraintClauses(const structure::DelegateDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end);

      /**
      * \brief Edge end visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDelegateDeclarationSyntax_ConstraintClauses(const structure::DelegateDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end);

      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDelegateDeclarationSyntax_ParameterList(const structure::DelegateDeclarationSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge end visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDelegateDeclarationSyntax_ParameterList(const structure::DelegateDeclarationSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge  visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDelegateDeclarationSyntax_ReturnType(const structure::DelegateDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDelegateDeclarationSyntax_ReturnType(const structure::DelegateDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitElseClauseSyntax_Statement(const structure::ElseClauseSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndElseClauseSyntax_Statement(const structure::ElseClauseSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEnumDeclarationSyntax_Members(const structure::EnumDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndEnumDeclarationSyntax_Members(const structure::EnumDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEnumMemberDeclarationSyntax_AttributeLists(const structure::EnumMemberDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndEnumMemberDeclarationSyntax_AttributeLists(const structure::EnumMemberDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for EqualsValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEnumMemberDeclarationSyntax_EqualsValue(const structure::EnumMemberDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge end visitor for EqualsValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndEnumMemberDeclarationSyntax_EqualsValue(const structure::EnumMemberDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge  visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEqualsValueClauseSyntax_Value(const structure::EqualsValueClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndEqualsValueClauseSyntax_Value(const structure::EqualsValueClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExplicitInterfaceSpecifierSyntax_Name(const structure::ExplicitInterfaceSpecifierSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExplicitInterfaceSpecifierSyntax_Name(const structure::ExplicitInterfaceSpecifierSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFinallyClauseSyntax_Block(const structure::FinallyClauseSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge end visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFinallyClauseSyntax_Block(const structure::FinallyClauseSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFromClauseSyntax_Expression(const structure::FromClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFromClauseSyntax_Expression(const structure::FromClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFromClauseSyntax_Type(const structure::FromClauseSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFromClauseSyntax_Type(const structure::FromClauseSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGlobalStatementSyntax_Statement(const structure::GlobalStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndGlobalStatementSyntax_Statement(const structure::GlobalStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for ByExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGroupClauseSyntax_ByExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for ByExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndGroupClauseSyntax_ByExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for GroupExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGroupClauseSyntax_GroupExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for GroupExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndGroupClauseSyntax_GroupExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIncompleteMemberSyntax_AttributeLists(const structure::IncompleteMemberSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIncompleteMemberSyntax_AttributeLists(const structure::IncompleteMemberSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIncompleteMemberSyntax_Type(const structure::IncompleteMemberSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIncompleteMemberSyntax_Type(const structure::IncompleteMemberSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIndexerDeclarationSyntax_ExpressionBody(const structure::IndexerDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge end visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIndexerDeclarationSyntax_ExpressionBody(const structure::IndexerDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIndexerDeclarationSyntax_ParameterList(const structure::IndexerDeclarationSyntax& begin, const structure::BracketedParameterListSyntax& end);

      /**
      * \brief Edge end visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIndexerDeclarationSyntax_ParameterList(const structure::IndexerDeclarationSyntax& begin, const structure::BracketedParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIndexerMemberCrefSyntax_Parameters(const structure::IndexerMemberCrefSyntax& begin, const structure::CrefBracketedParameterListSyntax& end);

      /**
      * \brief Edge end visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIndexerMemberCrefSyntax_Parameters(const structure::IndexerMemberCrefSyntax& begin, const structure::CrefBracketedParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInterpolationAlignmentClauseSyntax_Value(const structure::InterpolationAlignmentClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInterpolationAlignmentClauseSyntax_Value(const structure::InterpolationAlignmentClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for AlignmentClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInterpolationSyntax_AlignmentClause(const structure::InterpolationSyntax& begin, const structure::InterpolationAlignmentClauseSyntax& end);

      /**
      * \brief Edge end visitor for AlignmentClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInterpolationSyntax_AlignmentClause(const structure::InterpolationSyntax& begin, const structure::InterpolationAlignmentClauseSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInterpolationSyntax_Expression(const structure::InterpolationSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInterpolationSyntax_Expression(const structure::InterpolationSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for FormatClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInterpolationSyntax_FormatClause(const structure::InterpolationSyntax& begin, const structure::InterpolationFormatClauseSyntax& end);

      /**
      * \brief Edge end visitor for FormatClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInterpolationSyntax_FormatClause(const structure::InterpolationSyntax& begin, const structure::InterpolationFormatClauseSyntax& end);

      /**
      * \brief Edge  visitor for InExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitJoinClauseSyntax_InExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for InExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndJoinClauseSyntax_InExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Into edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitJoinClauseSyntax_Into(const structure::JoinClauseSyntax& begin, const structure::JoinIntoClauseSyntax& end);

      /**
      * \brief Edge end visitor for Into edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndJoinClauseSyntax_Into(const structure::JoinClauseSyntax& begin, const structure::JoinIntoClauseSyntax& end);

      /**
      * \brief Edge  visitor for LeftExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitJoinClauseSyntax_LeftExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for LeftExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndJoinClauseSyntax_LeftExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for RightExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitJoinClauseSyntax_RightExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for RightExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndJoinClauseSyntax_RightExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitJoinClauseSyntax_Type(const structure::JoinClauseSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndJoinClauseSyntax_Type(const structure::JoinClauseSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLetClauseSyntax_Expression(const structure::LetClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLetClauseSyntax_Expression(const structure::LetClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclarationSyntax_ConstraintClauses(const structure::MethodDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end);

      /**
      * \brief Edge end visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodDeclarationSyntax_ConstraintClauses(const structure::MethodDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end);

      /**
      * \brief Edge  visitor for ExplicitInterfaceSpecifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::MethodDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end);

      /**
      * \brief Edge end visitor for ExplicitInterfaceSpecifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::MethodDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end);

      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclarationSyntax_ExpressionBody(const structure::MethodDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge end visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodDeclarationSyntax_ExpressionBody(const structure::MethodDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge  visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclarationSyntax_ReturnType(const structure::MethodDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodDeclarationSyntax_ReturnType(const structure::MethodDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNameColonSyntax_Name(const structure::NameColonSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNameColonSyntax_Name(const structure::NameColonSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNameEqualsSyntax_Name(const structure::NameEqualsSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNameEqualsSyntax_Name(const structure::NameEqualsSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNameMemberCrefSyntax_Name(const structure::NameMemberCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNameMemberCrefSyntax_Name(const structure::NameMemberCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNameMemberCrefSyntax_Parameters(const structure::NameMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end);

      /**
      * \brief Edge end visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNameMemberCrefSyntax_Parameters(const structure::NameMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Externs edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNamespaceDeclarationSyntax_Externs(const structure::NamespaceDeclarationSyntax& begin, const structure::ExternAliasDirectiveSyntax& end);

      /**
      * \brief Edge end visitor for Externs edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNamespaceDeclarationSyntax_Externs(const structure::NamespaceDeclarationSyntax& begin, const structure::ExternAliasDirectiveSyntax& end);

      /**
      * \brief Edge  visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNamespaceDeclarationSyntax_Members(const structure::NamespaceDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNamespaceDeclarationSyntax_Members(const structure::NamespaceDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNamespaceDeclarationSyntax_Name(const structure::NamespaceDeclarationSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNamespaceDeclarationSyntax_Name(const structure::NamespaceDeclarationSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge  visitor for Usings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNamespaceDeclarationSyntax_Usings(const structure::NamespaceDeclarationSyntax& begin, const structure::UsingDirectiveSyntax& end);

      /**
      * \brief Edge end visitor for Usings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNamespaceDeclarationSyntax_Usings(const structure::NamespaceDeclarationSyntax& begin, const structure::UsingDirectiveSyntax& end);

      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitOperatorDeclarationSyntax_ExpressionBody(const structure::OperatorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge end visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndOperatorDeclarationSyntax_ExpressionBody(const structure::OperatorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge  visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitOperatorDeclarationSyntax_ReturnType(const structure::OperatorDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndOperatorDeclarationSyntax_ReturnType(const structure::OperatorDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitOperatorMemberCrefSyntax_Parameters(const structure::OperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end);

      /**
      * \brief Edge end visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndOperatorMemberCrefSyntax_Parameters(const structure::OperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Orderings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitOrderByClauseSyntax_Orderings(const structure::OrderByClauseSyntax& begin, const structure::OrderingSyntax& end);

      /**
      * \brief Edge end visitor for Orderings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndOrderByClauseSyntax_Orderings(const structure::OrderByClauseSyntax& begin, const structure::OrderingSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitOrderingSyntax_Expression(const structure::OrderingSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndOrderingSyntax_Expression(const structure::OrderingSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameterSyntax_AttributeLists(const structure::ParameterSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndParameterSyntax_AttributeLists(const structure::ParameterSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Default edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameterSyntax_Default(const structure::ParameterSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge end visitor for Default edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndParameterSyntax_Default(const structure::ParameterSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameterSyntax_Type(const structure::ParameterSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndParameterSyntax_Type(const structure::ParameterSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPropertyDeclarationSyntax_ExpressionBody(const structure::PropertyDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge end visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPropertyDeclarationSyntax_ExpressionBody(const structure::PropertyDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPropertyDeclarationSyntax_Initializer(const structure::PropertyDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPropertyDeclarationSyntax_Initializer(const structure::PropertyDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge  visitor for Container edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQualifiedCrefSyntax_Container(const structure::QualifiedCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Container edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQualifiedCrefSyntax_Container(const structure::QualifiedCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Member edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQualifiedCrefSyntax_Member(const structure::QualifiedCrefSyntax& begin, const structure::MemberCrefSyntax& end);

      /**
      * \brief Edge end visitor for Member edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQualifiedCrefSyntax_Member(const structure::QualifiedCrefSyntax& begin, const structure::MemberCrefSyntax& end);

      /**
      * \brief Edge  visitor for Clauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQueryBodySyntax_Clauses(const structure::QueryBodySyntax& begin, const structure::QueryClauseSyntax& end);

      /**
      * \brief Edge end visitor for Clauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQueryBodySyntax_Clauses(const structure::QueryBodySyntax& begin, const structure::QueryClauseSyntax& end);

      /**
      * \brief Edge  visitor for Continuation edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQueryBodySyntax_Continuation(const structure::QueryBodySyntax& begin, const structure::QueryContinuationSyntax& end);

      /**
      * \brief Edge end visitor for Continuation edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQueryBodySyntax_Continuation(const structure::QueryBodySyntax& begin, const structure::QueryContinuationSyntax& end);

      /**
      * \brief Edge  visitor for SelectOrGroup edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQueryBodySyntax_SelectOrGroup(const structure::QueryBodySyntax& begin, const structure::SelectOrGroupClauseSyntax& end);

      /**
      * \brief Edge end visitor for SelectOrGroup edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQueryBodySyntax_SelectOrGroup(const structure::QueryBodySyntax& begin, const structure::SelectOrGroupClauseSyntax& end);

      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQueryContinuationSyntax_Body(const structure::QueryContinuationSyntax& begin, const structure::QueryBodySyntax& end);

      /**
      * \brief Edge end visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQueryContinuationSyntax_Body(const structure::QueryContinuationSyntax& begin, const structure::QueryBodySyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSelectClauseSyntax_Expression(const structure::SelectClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSelectClauseSyntax_Expression(const structure::SelectClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Labels edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchSectionSyntax_Labels(const structure::SwitchSectionSyntax& begin, const structure::SwitchLabelSyntax& end);

      /**
      * \brief Edge end visitor for Labels edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSwitchSectionSyntax_Labels(const structure::SwitchSectionSyntax& begin, const structure::SwitchLabelSyntax& end);

      /**
      * \brief Edge  visitor for Statements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchSectionSyntax_Statements(const structure::SwitchSectionSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSwitchSectionSyntax_Statements(const structure::SwitchSectionSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeArgumentListSyntax_Arguments(const structure::TypeArgumentListSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeArgumentListSyntax_Arguments(const structure::TypeArgumentListSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeConstraintSyntax_Type(const structure::TypeConstraintSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeConstraintSyntax_Type(const structure::TypeConstraintSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeCrefSyntax_Type(const structure::TypeCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeCrefSyntax_Type(const structure::TypeCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclarationSyntax_ConstraintClauses(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end);

      /**
      * \brief Edge end visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeDeclarationSyntax_ConstraintClauses(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end);

      /**
      * \brief Edge  visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclarationSyntax_Members(const structure::TypeDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeDeclarationSyntax_Members(const structure::TypeDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for TypeParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclarationSyntax_TypeParameterList(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterListSyntax& end);

      /**
      * \brief Edge end visitor for TypeParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeDeclarationSyntax_TypeParameterList(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Constraints edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeParameterConstraintClauseSyntax_Constraints(const structure::TypeParameterConstraintClauseSyntax& begin, const structure::TypeParameterConstraintSyntax& end);

      /**
      * \brief Edge end visitor for Constraints edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeParameterConstraintClauseSyntax_Constraints(const structure::TypeParameterConstraintClauseSyntax& begin, const structure::TypeParameterConstraintSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeParameterConstraintClauseSyntax_Name(const structure::TypeParameterConstraintClauseSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeParameterConstraintClauseSyntax_Name(const structure::TypeParameterConstraintClauseSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge visitor for Parameters edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeParameterListSyntax_Parameters(const structure::TypeParameterListSyntax& begin, const structure::TypeParameterSyntax& end);

      /**
      * \brief Edge visitor for Parameters edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeParameterListSyntax_Parameters(const structure::TypeParameterListSyntax& begin, const structure::TypeParameterSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeParameterSyntax_AttributeLists(const structure::TypeParameterSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeParameterSyntax_AttributeLists(const structure::TypeParameterSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Alias edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUsingDirectiveSyntax_Alias(const structure::UsingDirectiveSyntax& begin, const structure::NameEqualsSyntax& end);

      /**
      * \brief Edge end visitor for Alias edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUsingDirectiveSyntax_Alias(const structure::UsingDirectiveSyntax& begin, const structure::NameEqualsSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUsingDirectiveSyntax_Name(const structure::UsingDirectiveSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUsingDirectiveSyntax_Name(const structure::UsingDirectiveSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclarationSyntax_Type(const structure::VariableDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndVariableDeclarationSyntax_Type(const structure::VariableDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Variables edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclarationSyntax_Variables(const structure::VariableDeclarationSyntax& begin, const structure::VariableDeclaratorSyntax& end);

      /**
      * \brief Edge end visitor for Variables edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndVariableDeclarationSyntax_Variables(const structure::VariableDeclarationSyntax& begin, const structure::VariableDeclaratorSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclaratorSyntax_ArgumentList(const structure::VariableDeclaratorSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndVariableDeclaratorSyntax_ArgumentList(const structure::VariableDeclaratorSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclaratorSyntax_Initializer(const structure::VariableDeclaratorSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndVariableDeclaratorSyntax_Initializer(const structure::VariableDeclaratorSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhereClauseSyntax_Condition(const structure::WhereClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndWhereClauseSyntax_Condition(const structure::WhereClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlAttributeSyntax_Name(const structure::XmlAttributeSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlAttributeSyntax_Name(const structure::XmlAttributeSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge  visitor for Cref edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlCrefAttributeSyntax_Cref(const structure::XmlCrefAttributeSyntax& begin, const structure::CrefSyntax& end);

      /**
      * \brief Edge end visitor for Cref edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlCrefAttributeSyntax_Cref(const structure::XmlCrefAttributeSyntax& begin, const structure::CrefSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlElementEndTagSyntax_Name(const structure::XmlElementEndTagSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlElementEndTagSyntax_Name(const structure::XmlElementEndTagSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge  visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlElementStartTagSyntax_Attributes(const structure::XmlElementStartTagSyntax& begin, const structure::XmlAttributeSyntax& end);

      /**
      * \brief Edge end visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlElementStartTagSyntax_Attributes(const structure::XmlElementStartTagSyntax& begin, const structure::XmlAttributeSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlElementStartTagSyntax_Name(const structure::XmlElementStartTagSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlElementStartTagSyntax_Name(const structure::XmlElementStartTagSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge  visitor for Content edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlElementSyntax_Content(const structure::XmlElementSyntax& begin, const structure::XmlNodeSyntax& end);

      /**
      * \brief Edge end visitor for Content edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlElementSyntax_Content(const structure::XmlElementSyntax& begin, const structure::XmlNodeSyntax& end);

      /**
      * \brief Edge  visitor for EndTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlElementSyntax_EndTag(const structure::XmlElementSyntax& begin, const structure::XmlElementEndTagSyntax& end);

      /**
      * \brief Edge end visitor for EndTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlElementSyntax_EndTag(const structure::XmlElementSyntax& begin, const structure::XmlElementEndTagSyntax& end);

      /**
      * \brief Edge  visitor for StartTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlElementSyntax_StartTag(const structure::XmlElementSyntax& begin, const structure::XmlElementStartTagSyntax& end);

      /**
      * \brief Edge end visitor for StartTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlElementSyntax_StartTag(const structure::XmlElementSyntax& begin, const structure::XmlElementStartTagSyntax& end);

      /**
      * \brief Edge  visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlEmptyElementSyntax_Attributes(const structure::XmlEmptyElementSyntax& begin, const structure::XmlAttributeSyntax& end);

      /**
      * \brief Edge end visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlEmptyElementSyntax_Attributes(const structure::XmlEmptyElementSyntax& begin, const structure::XmlAttributeSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlEmptyElementSyntax_Name(const structure::XmlEmptyElementSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlEmptyElementSyntax_Name(const structure::XmlEmptyElementSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge  visitor for Identifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlNameAttributeSyntax_Identifier(const structure::XmlNameAttributeSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge end visitor for Identifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlNameAttributeSyntax_Identifier(const structure::XmlNameAttributeSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge  visitor for Prefix edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlNameSyntax_Prefix(const structure::XmlNameSyntax& begin, const structure::XmlPrefixSyntax& end);

      /**
      * \brief Edge end visitor for Prefix edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlNameSyntax_Prefix(const structure::XmlNameSyntax& begin, const structure::XmlPrefixSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlProcessingInstructionSyntax_Name(const structure::XmlProcessingInstructionSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlProcessingInstructionSyntax_Name(const structure::XmlProcessingInstructionSyntax& begin, const structure::XmlNameSyntax& end);

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
      * \brief Writes out the attributes of the base::Base node.
      */
      virtual void writeAttributes(const base::Base& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the base::Positioned node.
      */
      virtual void writeAttributes(const base::Positioned& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::AliasQualifiedNameSyntax node.
      */
      virtual void writeAttributes(const expression::AliasQualifiedNameSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::AnonymousFunctionExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::AnonymousFunctionExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::AnonymousMethodExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::AnonymousMethodExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::AnonymousObjectCreationExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::AnonymousObjectCreationExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ArrayCreationExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::ArrayCreationExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ArrayTypeSyntax node.
      */
      virtual void writeAttributes(const expression::ArrayTypeSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::AssignmentExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::AssignmentExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::AwaitExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::AwaitExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::BaseExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::BaseExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::BinaryExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::BinaryExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::CastExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::CastExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::CheckedExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::CheckedExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ConditionalAccessExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::ConditionalAccessExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ConditionalExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::ConditionalExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::DefaultExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::DefaultExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ElementAccessExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::ElementAccessExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ElementBindingExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::ElementBindingExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::ExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::GenericNameSyntax node.
      */
      virtual void writeAttributes(const expression::GenericNameSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::IdentifierNameSyntax node.
      */
      virtual void writeAttributes(const expression::IdentifierNameSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ImplicitArrayCreationExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::ImplicitArrayCreationExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ImplicitElementAccessSyntax node.
      */
      virtual void writeAttributes(const expression::ImplicitElementAccessSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::InitializerExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::InitializerExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::InstanceExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::InstanceExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::InterpolatedStringExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::InterpolatedStringExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::InvocationExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::InvocationExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::LambdaExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::LambdaExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::LiteralExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::LiteralExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::MakeRefExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::MakeRefExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::MemberAccessExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::MemberAccessExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::MemberBindingExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::MemberBindingExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::NameSyntax node.
      */
      virtual void writeAttributes(const expression::NameSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::NullableTypeSyntax node.
      */
      virtual void writeAttributes(const expression::NullableTypeSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ObjectCreationExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::ObjectCreationExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::OmittedArraySizeExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::OmittedArraySizeExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::OmittedTypeArgumentSyntax node.
      */
      virtual void writeAttributes(const expression::OmittedTypeArgumentSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ParenthesizedExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::ParenthesizedExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ParenthesizedLambdaExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::ParenthesizedLambdaExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::PointerTypeSyntax node.
      */
      virtual void writeAttributes(const expression::PointerTypeSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::PostfixUnaryExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::PostfixUnaryExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::PredefinedTypeSyntax node.
      */
      virtual void writeAttributes(const expression::PredefinedTypeSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::PrefixUnaryExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::PrefixUnaryExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::QualifiedNameSyntax node.
      */
      virtual void writeAttributes(const expression::QualifiedNameSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::QueryExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::QueryExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::RefTypeExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::RefTypeExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::RefValueExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::RefValueExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::SimpleLambdaExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::SimpleLambdaExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::SimpleNameSyntax node.
      */
      virtual void writeAttributes(const expression::SimpleNameSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::SizeOfExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::SizeOfExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::StackAllocArrayCreationExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::StackAllocArrayCreationExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::ThisExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::ThisExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::TypeOfExpressionSyntax node.
      */
      virtual void writeAttributes(const expression::TypeOfExpressionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the expression::TypeSyntax node.
      */
      virtual void writeAttributes(const expression::TypeSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::BlockSyntax node.
      */
      virtual void writeAttributes(const statement::BlockSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::BreakStatementSyntax node.
      */
      virtual void writeAttributes(const statement::BreakStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::CheckedStatementSyntax node.
      */
      virtual void writeAttributes(const statement::CheckedStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::ContinueStatementSyntax node.
      */
      virtual void writeAttributes(const statement::ContinueStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::DoStatementSyntax node.
      */
      virtual void writeAttributes(const statement::DoStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::EmptyStatementSyntax node.
      */
      virtual void writeAttributes(const statement::EmptyStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::ExpressionStatementSyntax node.
      */
      virtual void writeAttributes(const statement::ExpressionStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::FixedStatementSyntax node.
      */
      virtual void writeAttributes(const statement::FixedStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::ForEachStatementSyntax node.
      */
      virtual void writeAttributes(const statement::ForEachStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::ForStatementSyntax node.
      */
      virtual void writeAttributes(const statement::ForStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::GotoStatementSyntax node.
      */
      virtual void writeAttributes(const statement::GotoStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::IfStatementSyntax node.
      */
      virtual void writeAttributes(const statement::IfStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::LabeledStatementSyntax node.
      */
      virtual void writeAttributes(const statement::LabeledStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::LocalDeclarationStatementSyntax node.
      */
      virtual void writeAttributes(const statement::LocalDeclarationStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::LockStatementSyntax node.
      */
      virtual void writeAttributes(const statement::LockStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::ReturnStatementSyntax node.
      */
      virtual void writeAttributes(const statement::ReturnStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::StatementSyntax node.
      */
      virtual void writeAttributes(const statement::StatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::SwitchStatementSyntax node.
      */
      virtual void writeAttributes(const statement::SwitchStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::ThrowStatementSyntax node.
      */
      virtual void writeAttributes(const statement::ThrowStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::TryStatementSyntax node.
      */
      virtual void writeAttributes(const statement::TryStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::UnsafeStatementSyntax node.
      */
      virtual void writeAttributes(const statement::UnsafeStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::UsingStatementSyntax node.
      */
      virtual void writeAttributes(const statement::UsingStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::WhileStatementSyntax node.
      */
      virtual void writeAttributes(const statement::WhileStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the statement::YieldStatementSyntax node.
      */
      virtual void writeAttributes(const statement::YieldStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::AccessorDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::AccessorDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::AccessorListSyntax node.
      */
      virtual void writeAttributes(const structure::AccessorListSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::AnonymousObjectMemberDeclaratorSyntax node.
      */
      virtual void writeAttributes(const structure::AnonymousObjectMemberDeclaratorSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ArgumentListSyntax node.
      */
      virtual void writeAttributes(const structure::ArgumentListSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ArgumentSyntax node.
      */
      virtual void writeAttributes(const structure::ArgumentSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ArrayRankSpecifierSyntax node.
      */
      virtual void writeAttributes(const structure::ArrayRankSpecifierSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ArrowExpressionClauseSyntax node.
      */
      virtual void writeAttributes(const structure::ArrowExpressionClauseSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::AttributeArgumentListSyntax node.
      */
      virtual void writeAttributes(const structure::AttributeArgumentListSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::AttributeArgumentSyntax node.
      */
      virtual void writeAttributes(const structure::AttributeArgumentSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::AttributeListSyntax node.
      */
      virtual void writeAttributes(const structure::AttributeListSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::AttributeSyntax node.
      */
      virtual void writeAttributes(const structure::AttributeSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::AttributeTargetSpecifierSyntax node.
      */
      virtual void writeAttributes(const structure::AttributeTargetSpecifierSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::BaseArgumentListSyntax node.
      */
      virtual void writeAttributes(const structure::BaseArgumentListSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::BaseCrefParameterListSyntax node.
      */
      virtual void writeAttributes(const structure::BaseCrefParameterListSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::BaseFieldDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::BaseFieldDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::BaseListSyntax node.
      */
      virtual void writeAttributes(const structure::BaseListSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::BaseMethodDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::BaseMethodDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::BaseParameterListSyntax node.
      */
      virtual void writeAttributes(const structure::BaseParameterListSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::BasePropertyDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::BasePropertyDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::BaseTypeDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::BaseTypeDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::BaseTypeSyntax node.
      */
      virtual void writeAttributes(const structure::BaseTypeSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::BracketedArgumentListSyntax node.
      */
      virtual void writeAttributes(const structure::BracketedArgumentListSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::BracketedParameterListSyntax node.
      */
      virtual void writeAttributes(const structure::BracketedParameterListSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::CaseSwitchLabelSyntax node.
      */
      virtual void writeAttributes(const structure::CaseSwitchLabelSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::CatchClauseSyntax node.
      */
      virtual void writeAttributes(const structure::CatchClauseSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::CatchDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::CatchDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::CatchFilterClauseSyntax node.
      */
      virtual void writeAttributes(const structure::CatchFilterClauseSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ClassDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::ClassDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ClassOrStructConstraintSyntax node.
      */
      virtual void writeAttributes(const structure::ClassOrStructConstraintSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::CompilationUnitSyntax node.
      */
      virtual void writeAttributes(const structure::CompilationUnitSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ConstructorConstraintSyntax node.
      */
      virtual void writeAttributes(const structure::ConstructorConstraintSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ConstructorDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::ConstructorDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ConstructorInitializerSyntax node.
      */
      virtual void writeAttributes(const structure::ConstructorInitializerSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ConversionOperatorDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::ConversionOperatorDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ConversionOperatorMemberCrefSyntax node.
      */
      virtual void writeAttributes(const structure::ConversionOperatorMemberCrefSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::CrefBracketedParameterListSyntax node.
      */
      virtual void writeAttributes(const structure::CrefBracketedParameterListSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::CrefParameterListSyntax node.
      */
      virtual void writeAttributes(const structure::CrefParameterListSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::CrefParameterSyntax node.
      */
      virtual void writeAttributes(const structure::CrefParameterSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::CrefSyntax node.
      */
      virtual void writeAttributes(const structure::CrefSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::DefaultSwitchLabelSyntax node.
      */
      virtual void writeAttributes(const structure::DefaultSwitchLabelSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::DelegateDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::DelegateDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::DestructorDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::DestructorDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ElseClauseSyntax node.
      */
      virtual void writeAttributes(const structure::ElseClauseSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::EnumDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::EnumDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::EnumMemberDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::EnumMemberDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::EqualsValueClauseSyntax node.
      */
      virtual void writeAttributes(const structure::EqualsValueClauseSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::EventDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::EventDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::EventFieldDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::EventFieldDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ExplicitInterfaceSpecifierSyntax node.
      */
      virtual void writeAttributes(const structure::ExplicitInterfaceSpecifierSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ExternAliasDirectiveSyntax node.
      */
      virtual void writeAttributes(const structure::ExternAliasDirectiveSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::FieldDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::FieldDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::FinallyClauseSyntax node.
      */
      virtual void writeAttributes(const structure::FinallyClauseSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::FromClauseSyntax node.
      */
      virtual void writeAttributes(const structure::FromClauseSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::GlobalStatementSyntax node.
      */
      virtual void writeAttributes(const structure::GlobalStatementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::GroupClauseSyntax node.
      */
      virtual void writeAttributes(const structure::GroupClauseSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::IncompleteMemberSyntax node.
      */
      virtual void writeAttributes(const structure::IncompleteMemberSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::IndexerDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::IndexerDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::IndexerMemberCrefSyntax node.
      */
      virtual void writeAttributes(const structure::IndexerMemberCrefSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::InterfaceDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::InterfaceDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::InterpolatedStringContentSyntax node.
      */
      virtual void writeAttributes(const structure::InterpolatedStringContentSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::InterpolatedStringTextSyntax node.
      */
      virtual void writeAttributes(const structure::InterpolatedStringTextSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::InterpolationAlignmentClauseSyntax node.
      */
      virtual void writeAttributes(const structure::InterpolationAlignmentClauseSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::InterpolationFormatClauseSyntax node.
      */
      virtual void writeAttributes(const structure::InterpolationFormatClauseSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::InterpolationSyntax node.
      */
      virtual void writeAttributes(const structure::InterpolationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::JoinClauseSyntax node.
      */
      virtual void writeAttributes(const structure::JoinClauseSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::JoinIntoClauseSyntax node.
      */
      virtual void writeAttributes(const structure::JoinIntoClauseSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::LetClauseSyntax node.
      */
      virtual void writeAttributes(const structure::LetClauseSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::MemberCrefSyntax node.
      */
      virtual void writeAttributes(const structure::MemberCrefSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::MemberDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::MemberDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::MethodDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::MethodDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::NameColonSyntax node.
      */
      virtual void writeAttributes(const structure::NameColonSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::NameEqualsSyntax node.
      */
      virtual void writeAttributes(const structure::NameEqualsSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::NameMemberCrefSyntax node.
      */
      virtual void writeAttributes(const structure::NameMemberCrefSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::NamespaceDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::NamespaceDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::OperatorDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::OperatorDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::OperatorMemberCrefSyntax node.
      */
      virtual void writeAttributes(const structure::OperatorMemberCrefSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::OrderByClauseSyntax node.
      */
      virtual void writeAttributes(const structure::OrderByClauseSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::OrderingSyntax node.
      */
      virtual void writeAttributes(const structure::OrderingSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ParameterListSyntax node.
      */
      virtual void writeAttributes(const structure::ParameterListSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::ParameterSyntax node.
      */
      virtual void writeAttributes(const structure::ParameterSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::PropertyDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::PropertyDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::QualifiedCrefSyntax node.
      */
      virtual void writeAttributes(const structure::QualifiedCrefSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::QueryBodySyntax node.
      */
      virtual void writeAttributes(const structure::QueryBodySyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::QueryClauseSyntax node.
      */
      virtual void writeAttributes(const structure::QueryClauseSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::QueryContinuationSyntax node.
      */
      virtual void writeAttributes(const structure::QueryContinuationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::SelectClauseSyntax node.
      */
      virtual void writeAttributes(const structure::SelectClauseSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::SelectOrGroupClauseSyntax node.
      */
      virtual void writeAttributes(const structure::SelectOrGroupClauseSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::SimpleBaseTypeSyntax node.
      */
      virtual void writeAttributes(const structure::SimpleBaseTypeSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::StructDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::StructDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::SwitchLabelSyntax node.
      */
      virtual void writeAttributes(const structure::SwitchLabelSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::SwitchSectionSyntax node.
      */
      virtual void writeAttributes(const structure::SwitchSectionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::SyntaxToken node.
      */
      virtual void writeAttributes(const structure::SyntaxToken& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::TypeArgumentListSyntax node.
      */
      virtual void writeAttributes(const structure::TypeArgumentListSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::TypeConstraintSyntax node.
      */
      virtual void writeAttributes(const structure::TypeConstraintSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::TypeCrefSyntax node.
      */
      virtual void writeAttributes(const structure::TypeCrefSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::TypeDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::TypeDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::TypeParameterConstraintClauseSyntax node.
      */
      virtual void writeAttributes(const structure::TypeParameterConstraintClauseSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::TypeParameterConstraintSyntax node.
      */
      virtual void writeAttributes(const structure::TypeParameterConstraintSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::TypeParameterListSyntax node.
      */
      virtual void writeAttributes(const structure::TypeParameterListSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::TypeParameterSyntax node.
      */
      virtual void writeAttributes(const structure::TypeParameterSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::UsingDirectiveSyntax node.
      */
      virtual void writeAttributes(const structure::UsingDirectiveSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::VariableDeclarationSyntax node.
      */
      virtual void writeAttributes(const structure::VariableDeclarationSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::VariableDeclaratorSyntax node.
      */
      virtual void writeAttributes(const structure::VariableDeclaratorSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::WhereClauseSyntax node.
      */
      virtual void writeAttributes(const structure::WhereClauseSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::XmlAttributeSyntax node.
      */
      virtual void writeAttributes(const structure::XmlAttributeSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::XmlCDataSectionSyntax node.
      */
      virtual void writeAttributes(const structure::XmlCDataSectionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::XmlCommentSyntax node.
      */
      virtual void writeAttributes(const structure::XmlCommentSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::XmlCrefAttributeSyntax node.
      */
      virtual void writeAttributes(const structure::XmlCrefAttributeSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::XmlElementEndTagSyntax node.
      */
      virtual void writeAttributes(const structure::XmlElementEndTagSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::XmlElementStartTagSyntax node.
      */
      virtual void writeAttributes(const structure::XmlElementStartTagSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::XmlElementSyntax node.
      */
      virtual void writeAttributes(const structure::XmlElementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::XmlEmptyElementSyntax node.
      */
      virtual void writeAttributes(const structure::XmlEmptyElementSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::XmlNameAttributeSyntax node.
      */
      virtual void writeAttributes(const structure::XmlNameAttributeSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::XmlNameSyntax node.
      */
      virtual void writeAttributes(const structure::XmlNameSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::XmlNodeSyntax node.
      */
      virtual void writeAttributes(const structure::XmlNodeSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::XmlPrefixSyntax node.
      */
      virtual void writeAttributes(const structure::XmlPrefixSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::XmlProcessingInstructionSyntax node.
      */
      virtual void writeAttributes(const structure::XmlProcessingInstructionSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::XmlTextAttributeSyntax node.
      */
      virtual void writeAttributes(const structure::XmlTextAttributeSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the structure::XmlTextSyntax node.
      */
      virtual void writeAttributes(const structure::XmlTextSyntax& node, bool composite, bool bWithParent = true);

      /**
      * \internal
      * \brief Writes out the attributes of the SourcePosition composite member.
      */
      void writeAttributes(const SourcePosition& node, bool composite);

      /** \internal \brief The ofstrem into the xml will be written. */
      std::ofstream &ofs;

      /** \internal \brief Flag to know if the ID of the nodes have to be written or not. */
      bool noId;

      /** \internal \brief Flag to know if the line info of the nodes have to be written or not. */
      bool noLineInfo;

      const std::string projectName;

  }; // VisitorCSHARPML


}}}
#endif

