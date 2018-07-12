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

#ifndef _PYTHON_VISITOR_H_
#define _PYTHON_VISITOR_H_

#include "python/inc/python.h"

/**
* \file Visitor.h
* \brief Contains declaration of Visitor class.
*/

namespace columbus { namespace python { namespace asg {
  /**
  * \brief Visitor for each non-abstract nodes and all edges of the graph.
  */
  class Visitor {
    public:
      /**
      * \brief Constructor for Visitor.
      */
      Visitor();

      /**
      * \brief Destructor.
      */
      virtual ~Visitor();

      /**
      * \brief Gives back the the actual position's depth in the ASG.
      * \return The depth of the actual position.
      */
      unsigned getDepth() const;

      /**
      * \brief Increasing the depth by one in the ASG.
      */
      void incDepth();

      /**
      * \brief Decreasing the depth by one in the ASG.
      */
      void decDepth();

      /**
      * \brief This function is calling before the beginning of visiting process.
      */
      virtual void beginVisit();

      /**
      * \brief This function is calling when the visiting process has finished.
      */
      virtual void finishVisit();

      /**
      * \brief Visitor which is called at the beginning of the base::Comment node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Comment& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the base::Comment node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::Comment& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the base::Docstring node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Docstring& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the base::Docstring node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::Docstring& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::ArgumentList node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ArgumentList& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::ArgumentList node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ArgumentList& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::AttributeRef node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AttributeRef& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::AttributeRef node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AttributeRef& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::BinaryArithmetic node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::BinaryArithmetic& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::BinaryArithmetic node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::BinaryArithmetic& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::BinaryLogical node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::BinaryLogical& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::BinaryLogical node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::BinaryLogical& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::Call node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Call& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::Call node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Call& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::DictComp node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::DictComp& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::DictComp node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::DictComp& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::Dictionary node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Dictionary& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::Dictionary node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Dictionary& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::Ellipsis node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Ellipsis& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::Ellipsis node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Ellipsis& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::ExpressionList node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ExpressionList& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::ExpressionList node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ExpressionList& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::ExtSlice node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ExtSlice& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::ExtSlice node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ExtSlice& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::FloatNumber node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::FloatNumber& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::FloatNumber node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::FloatNumber& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::Generator node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Generator& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::Generator node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Generator& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::GeneratorExpression node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::GeneratorExpression& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::GeneratorExpression node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::GeneratorExpression& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::Identifier node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Identifier& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::Identifier node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Identifier& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::IfExpression node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::IfExpression& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::IfExpression node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::IfExpression& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::ImagNumber node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ImagNumber& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::ImagNumber node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ImagNumber& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::Index node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Index& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::Index node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Index& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::IntegerLiteral node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::IntegerLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::IntegerLiteral node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::IntegerLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::KeyValue node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::KeyValue& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::KeyValue node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::KeyValue& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::Keyword node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Keyword& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::Keyword node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Keyword& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::Lambda node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Lambda& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::Lambda node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Lambda& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::List node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::List& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::List node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::List& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::ListComp node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ListComp& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::ListComp node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ListComp& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::LongInteger node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::LongInteger& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::LongInteger node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::LongInteger& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::Set node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Set& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::Set node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Set& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::SetComp node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::SetComp& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::SetComp node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::SetComp& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::Slice node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Slice& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::Slice node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Slice& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::StringConversion node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::StringConversion& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::StringConversion node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::StringConversion& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::StringLiteral node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::StringLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::StringLiteral node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::StringLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::Subscription node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Subscription& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::Subscription node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Subscription& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::UnaryOperation node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::UnaryOperation& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::UnaryOperation node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::UnaryOperation& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::YieldExpression node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::YieldExpression& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::YieldExpression node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::YieldExpression& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the module::Module node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const module::Module& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the module::Module node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const module::Module& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the module::Object node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const module::Object& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the module::Object node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const module::Object& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the module::Package node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const module::Package& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the module::Package node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const module::Package& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::Alias node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Alias& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::Alias node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Alias& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::Assert node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Assert& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::Assert node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Assert& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::Assign node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Assign& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::Assign node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Assign& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::AugAssign node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::AugAssign& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::AugAssign node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::AugAssign& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::BaseSpecifier node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::BaseSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::BaseSpecifier node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::BaseSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::Break node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Break& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::Break node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Break& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::ClassDef node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ClassDef& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::ClassDef node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ClassDef& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::Continue node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Continue& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::Continue node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Continue& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::Delete node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Delete& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::Delete node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Delete& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::Exec node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Exec& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::Exec node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Exec& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::For node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::For& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::For node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::For& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::FunctionDef node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::FunctionDef& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::FunctionDef node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::FunctionDef& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::Global node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Global& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::Global node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Global& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::Handler node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Handler& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::Handler node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Handler& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::If node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::If& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::If node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::If& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::ImportFrom node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ImportFrom& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::ImportFrom node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ImportFrom& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::ImportStatement node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ImportStatement& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::ImportStatement node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ImportStatement& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::Parameter node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Parameter& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::Parameter node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Parameter& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::Pass node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Pass& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::Pass node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Pass& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::Print node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Print& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::Print node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Print& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::Raise node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Raise& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::Raise node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Raise& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::Return node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Return& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::Return node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Return& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::Suite node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Suite& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::Suite node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Suite& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::TargetList node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::TargetList& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::TargetList node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::TargetList& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::TryExcept node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::TryExcept& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::TryExcept node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::TryExcept& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::TryFinal node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::TryFinal& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::TryFinal node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::TryFinal& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::While node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::While& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::While node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::While& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::With node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::With& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::With node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::With& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the type::DictType node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::DictType& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the type::DictType node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::DictType& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the type::ReferenceType node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::ReferenceType& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the type::ReferenceType node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::ReferenceType& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the type::SequenceType node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::SequenceType& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the type::SequenceType node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::SequenceType& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the type::SimpleType node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::SimpleType& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the type::SimpleType node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::SimpleType& node , bool callVirtualBase = true);

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
      * \brief Edge  visitor for hasPositionalArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArgumentList_HasPositionalArguments(const expression::ArgumentList& begin, const expression::ExpressionList& end);

      /**
      * \brief Edge end visitor for hasPositionalArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArgumentList_HasPositionalArguments(const expression::ArgumentList& begin, const expression::ExpressionList& end);

      /**
      * \brief Edge  visitor for hasDictionary edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArgumentList_HasDictionary(const expression::ArgumentList& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasDictionary edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArgumentList_HasDictionary(const expression::ArgumentList& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasKeyword edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArgumentList_HasKeyword(const expression::ArgumentList& begin, const expression::Keyword& end);

      /**
      * \brief Edge end visitor for hasKeyword edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArgumentList_HasKeyword(const expression::ArgumentList& begin, const expression::Keyword& end);

      /**
      * \brief Edge  visitor for hasTuple edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArgumentList_HasTuple(const expression::ArgumentList& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasTuple edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArgumentList_HasTuple(const expression::ArgumentList& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasLeftExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinary_HasLeftExpression(const expression::Binary& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasLeftExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBinary_HasLeftExpression(const expression::Binary& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasRightExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinary_HasRightExpression(const expression::Binary& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasRightExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBinary_HasRightExpression(const expression::Binary& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCall_HasArgumentList(const expression::Call& begin, const expression::ArgumentList& end);

      /**
      * \brief Edge end visitor for hasArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCall_HasArgumentList(const expression::Call& begin, const expression::ArgumentList& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCall_RefersTo(const expression::Call& begin, const statement::CompoundStatement& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCall_RefersTo(const expression::Call& begin, const statement::CompoundStatement& end);

      /**
      * \brief Edge  visitor for hasKeyValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDictComp_HasKeyValue(const expression::DictComp& begin, const expression::KeyValue& end);

      /**
      * \brief Edge end visitor for hasKeyValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDictComp_HasKeyValue(const expression::DictComp& begin, const expression::KeyValue& end);

      /**
      * \brief Edge  visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDictComp_HasGenerator(const expression::DictComp& begin, const expression::Generator& end);

      /**
      * \brief Edge end visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDictComp_HasGenerator(const expression::DictComp& begin, const expression::Generator& end);

      /**
      * \brief Edge  visitor for hasKeyValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDictionary_HasKeyValue(const expression::Dictionary& begin, const expression::KeyValue& end);

      /**
      * \brief Edge end visitor for hasKeyValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDictionary_HasKeyValue(const expression::Dictionary& begin, const expression::KeyValue& end);

      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExpression_HasType(const expression::Expression& begin, const type::Type& end);

      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExpression_HasType(const expression::Expression& begin, const type::Type& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExpressionList_HasExpression(const expression::ExpressionList& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExpressionList_HasExpression(const expression::ExpressionList& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasItem edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExtSlice_HasItem(const expression::ExtSlice& begin, const expression::Slicing& end);

      /**
      * \brief Edge end visitor for hasItem edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExtSlice_HasItem(const expression::ExtSlice& begin, const expression::Slicing& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGenerator_HasCondition(const expression::Generator& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndGenerator_HasCondition(const expression::Generator& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasIter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGenerator_HasIter(const expression::Generator& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasIter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndGenerator_HasIter(const expression::Generator& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTarget edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGenerator_HasTarget(const expression::Generator& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasTarget edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndGenerator_HasTarget(const expression::Generator& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGeneratorExpression_HasExpression(const expression::GeneratorExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndGeneratorExpression_HasExpression(const expression::GeneratorExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGeneratorExpression_HasGenerator(const expression::GeneratorExpression& begin, const expression::Generator& end);

      /**
      * \brief Edge end visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndGeneratorExpression_HasGenerator(const expression::GeneratorExpression& begin, const expression::Generator& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIdentifier_RefersTo(const expression::Identifier& begin, const module::Object& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIdentifier_RefersTo(const expression::Identifier& begin, const module::Object& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfExpression_HasBody(const expression::IfExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIfExpression_HasBody(const expression::IfExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfExpression_HasElseBody(const expression::IfExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIfExpression_HasElseBody(const expression::IfExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfExpression_HasTest(const expression::IfExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIfExpression_HasTest(const expression::IfExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitKeyValue_HasKey(const expression::KeyValue& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndKeyValue_HasKey(const expression::KeyValue& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitKeyValue_HasValue(const expression::KeyValue& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndKeyValue_HasValue(const expression::KeyValue& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitKeyword_HasKey(const expression::Keyword& begin, const expression::Identifier& end);

      /**
      * \brief Edge end visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndKeyword_HasKey(const expression::Keyword& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitKeyword_HasValue(const expression::Keyword& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndKeyword_HasValue(const expression::Keyword& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLambda_HasObject(const expression::Lambda& begin, const module::Object& end);

      /**
      * \brief Edge end visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLambda_HasObject(const expression::Lambda& begin, const module::Object& end);

      /**
      * \brief Edge  visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLambda_HasParameter(const expression::Lambda& begin, const statement::Parameter& end);

      /**
      * \brief Edge end visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLambda_HasParameter(const expression::Lambda& begin, const statement::Parameter& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLambda_HasExpression(const expression::Lambda& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLambda_HasExpression(const expression::Lambda& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitList_HasExpression(const expression::List& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndList_HasExpression(const expression::List& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitListComp_HasExpression(const expression::ListComp& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndListComp_HasExpression(const expression::ListComp& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitListComp_HasGenerator(const expression::ListComp& begin, const expression::Generator& end);

      /**
      * \brief Edge end visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndListComp_HasGenerator(const expression::ListComp& begin, const expression::Generator& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSet_HasExpression(const expression::Set& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSet_HasExpression(const expression::Set& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSetComp_HasExpression(const expression::SetComp& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSetComp_HasExpression(const expression::SetComp& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSetComp_HasGenerator(const expression::SetComp& begin, const expression::Generator& end);

      /**
      * \brief Edge end visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSetComp_HasGenerator(const expression::SetComp& begin, const expression::Generator& end);

      /**
      * \brief Edge  visitor for hasLowerBound edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSlice_HasLowerBound(const expression::Slice& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasLowerBound edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSlice_HasLowerBound(const expression::Slice& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasStride edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSlice_HasStride(const expression::Slice& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasStride edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSlice_HasStride(const expression::Slice& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasUpperBound edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSlice_HasUpperBound(const expression::Slice& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasUpperBound edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSlice_HasUpperBound(const expression::Slice& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpressionList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitStringConversion_HasExpressionList(const expression::StringConversion& begin, const expression::ExpressionList& end);

      /**
      * \brief Edge end visitor for hasExpressionList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndStringConversion_HasExpressionList(const expression::StringConversion& begin, const expression::ExpressionList& end);

      /**
      * \brief Edge  visitor for hasSlicing edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSubscription_HasSlicing(const expression::Subscription& begin, const expression::Slicing& end);

      /**
      * \brief Edge end visitor for hasSlicing edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSubscription_HasSlicing(const expression::Subscription& begin, const expression::Slicing& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUnary_HasExpression(const expression::Unary& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUnary_HasExpression(const expression::Unary& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasYieldExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitYieldExpression_HasYieldExpression(const expression::YieldExpression& begin, const expression::ExpressionList& end);

      /**
      * \brief Edge end visitor for hasYieldExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndYieldExpression_HasYieldExpression(const expression::YieldExpression& begin, const expression::ExpressionList& end);

      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitModule_HasObject(const module::Module& begin, const module::Object& end);

      /**
      * \brief Edge end visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndModule_HasObject(const module::Module& begin, const module::Object& end);

      /**
      * \brief Edge  visitor for hasStatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitModule_HasStatement(const module::Module& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasStatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndModule_HasStatement(const module::Module& begin, const base::Positioned& end);

      /**
      * \brief Edge visitor for docstring edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitModule_Docstring(const module::Module& begin, const base::Docstring& end);

      /**
      * \brief Edge visitor for docstring edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndModule_Docstring(const module::Module& begin, const base::Docstring& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObject_RefersTo(const module::Object& begin, const base::Positioned& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndObject_RefersTo(const module::Object& begin, const base::Positioned& end);

      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObject_HasType(const module::Object& begin, const type::Type& end);

      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndObject_HasType(const module::Object& begin, const type::Type& end);

      /**
      * \brief Edge  visitor for hasModule edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPackage_HasModule(const module::Package& begin, const module::Module& end);

      /**
      * \brief Edge end visitor for hasModule edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPackage_HasModule(const module::Package& begin, const module::Module& end);

      /**
      * \brief Edge  visitor for hasPackage edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPackage_HasPackage(const module::Package& begin, const module::Package& end);

      /**
      * \brief Edge end visitor for hasPackage edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPackage_HasPackage(const module::Package& begin, const module::Package& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAlias_RefersTo(const statement::Alias& begin, const base::Base& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAlias_RefersTo(const statement::Alias& begin, const base::Base& end);

      /**
      * \brief Edge  visitor for hasMsgExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssert_HasMsgExpression(const statement::Assert& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasMsgExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssert_HasMsgExpression(const statement::Assert& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTestExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssert_HasTestExpression(const statement::Assert& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasTestExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssert_HasTestExpression(const statement::Assert& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssign_HasExpression(const statement::Assign& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssign_HasExpression(const statement::Assign& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssign_HasTargetList(const statement::Assign& begin, const statement::TargetList& end);

      /**
      * \brief Edge end visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssign_HasTargetList(const statement::Assign& begin, const statement::TargetList& end);

      /**
      * \brief Edge  visitor for hasName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseSpecifier_HasName(const statement::BaseSpecifier& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseSpecifier_HasName(const statement::BaseSpecifier& begin, const expression::Expression& end);

      /**
      * \brief Edge visitor for derivesFrom edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseSpecifier_DerivesFrom(const statement::BaseSpecifier& begin, const statement::ClassDef& end);

      /**
      * \brief Edge visitor for derivesFrom edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseSpecifier_DerivesFrom(const statement::BaseSpecifier& begin, const statement::ClassDef& end);

      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassDef_HasObject(const statement::ClassDef& begin, const module::Object& end);

      /**
      * \brief Edge end visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndClassDef_HasObject(const statement::ClassDef& begin, const module::Object& end);

      /**
      * \brief Edge  visitor for hasBaseSpecifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassDef_HasBaseSpecifier(const statement::ClassDef& begin, const statement::BaseSpecifier& end);

      /**
      * \brief Edge end visitor for hasBaseSpecifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndClassDef_HasBaseSpecifier(const statement::ClassDef& begin, const statement::BaseSpecifier& end);

      /**
      * \brief Edge  visitor for hasDecorator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassDef_HasDecorator(const statement::ClassDef& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasDecorator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndClassDef_HasDecorator(const statement::ClassDef& begin, const expression::Expression& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassDef_RefersTo(const statement::ClassDef& begin, const module::Object& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndClassDef_RefersTo(const statement::ClassDef& begin, const module::Object& end);

      /**
      * \brief Edge visitor for docstring edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassDef_Docstring(const statement::ClassDef& begin, const base::Docstring& end);

      /**
      * \brief Edge visitor for docstring edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndClassDef_Docstring(const statement::ClassDef& begin, const base::Docstring& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompoundStatement_HasBody(const statement::CompoundStatement& begin, const statement::Suite& end);

      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCompoundStatement_HasBody(const statement::CompoundStatement& begin, const statement::Suite& end);

      /**
      * \brief Edge  visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDelete_HasTargetList(const statement::Delete& begin, const statement::TargetList& end);

      /**
      * \brief Edge end visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDelete_HasTargetList(const statement::Delete& begin, const statement::TargetList& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExec_HasExpression(const statement::Exec& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExec_HasExpression(const statement::Exec& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasGlobals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExec_HasGlobals(const statement::Exec& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasGlobals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExec_HasGlobals(const statement::Exec& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasLocals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExec_HasLocals(const statement::Exec& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasLocals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExec_HasLocals(const statement::Exec& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpressionList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFor_HasExpressionList(const statement::For& begin, const expression::ExpressionList& end);

      /**
      * \brief Edge end visitor for hasExpressionList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFor_HasExpressionList(const statement::For& begin, const expression::ExpressionList& end);

      /**
      * \brief Edge  visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFor_HasTargetList(const statement::For& begin, const statement::TargetList& end);

      /**
      * \brief Edge end visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFor_HasTargetList(const statement::For& begin, const statement::TargetList& end);

      /**
      * \brief Edge  visitor for hasDecorator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunctionDef_HasDecorator(const statement::FunctionDef& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasDecorator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFunctionDef_HasDecorator(const statement::FunctionDef& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunctionDef_HasObject(const statement::FunctionDef& begin, const module::Object& end);

      /**
      * \brief Edge end visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFunctionDef_HasObject(const statement::FunctionDef& begin, const module::Object& end);

      /**
      * \brief Edge  visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunctionDef_HasParameter(const statement::FunctionDef& begin, const statement::Parameter& end);

      /**
      * \brief Edge end visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFunctionDef_HasParameter(const statement::FunctionDef& begin, const statement::Parameter& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunctionDef_RefersTo(const statement::FunctionDef& begin, const module::Object& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFunctionDef_RefersTo(const statement::FunctionDef& begin, const module::Object& end);

      /**
      * \brief Edge visitor for returnType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunctionDef_ReturnType(const statement::FunctionDef& begin, const type::Type& end);

      /**
      * \brief Edge visitor for returnType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFunctionDef_ReturnType(const statement::FunctionDef& begin, const type::Type& end);

      /**
      * \brief Edge visitor for docstring edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunctionDef_Docstring(const statement::FunctionDef& begin, const base::Docstring& end);

      /**
      * \brief Edge visitor for docstring edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFunctionDef_Docstring(const statement::FunctionDef& begin, const base::Docstring& end);

      /**
      * \brief Edge  visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGlobal_HasIdentifier(const statement::Global& begin, const expression::Identifier& end);

      /**
      * \brief Edge end visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndGlobal_HasIdentifier(const statement::Global& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitHandler_HasName(const statement::Handler& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndHandler_HasName(const statement::Handler& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExceptBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitHandler_HasExceptBody(const statement::Handler& begin, const statement::Suite& end);

      /**
      * \brief Edge end visitor for hasExceptBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndHandler_HasExceptBody(const statement::Handler& begin, const statement::Suite& end);

      /**
      * \brief Edge  visitor for hasType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitHandler_HasType(const statement::Handler& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndHandler_HasType(const statement::Handler& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIf_HasElseBody(const statement::If& begin, const statement::Suite& end);

      /**
      * \brief Edge end visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIf_HasElseBody(const statement::If& begin, const statement::Suite& end);

      /**
      * \brief Edge  visitor for hasTestExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIf_HasTestExpression(const statement::If& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasTestExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIf_HasTestExpression(const statement::If& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasAlias edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImportStatement_HasAlias(const statement::ImportStatement& begin, const statement::Alias& end);

      /**
      * \brief Edge end visitor for hasAlias edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndImportStatement_HasAlias(const statement::ImportStatement& begin, const statement::Alias& end);

      /**
      * \brief Edge  visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIteration_HasElseBody(const statement::Iteration& begin, const statement::Suite& end);

      /**
      * \brief Edge end visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIteration_HasElseBody(const statement::Iteration& begin, const statement::Suite& end);

      /**
      * \brief Edge  visitor for hasDefaultValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameter_HasDefaultValue(const statement::Parameter& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasDefaultValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndParameter_HasDefaultValue(const statement::Parameter& begin, const expression::Expression& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameter_RefersTo(const statement::Parameter& begin, const module::Object& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndParameter_RefersTo(const statement::Parameter& begin, const module::Object& end);

      /**
      * \brief Edge  visitor for hasExpressionList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPrint_HasExpressionList(const statement::Print& begin, const expression::ExpressionList& end);

      /**
      * \brief Edge end visitor for hasExpressionList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPrint_HasExpressionList(const statement::Print& begin, const expression::ExpressionList& end);

      /**
      * \brief Edge  visitor for hasDestination edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPrint_HasDestination(const statement::Print& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasDestination edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPrint_HasDestination(const statement::Print& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTracebackExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitRaise_HasTracebackExpression(const statement::Raise& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasTracebackExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndRaise_HasTracebackExpression(const statement::Raise& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTypeExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitRaise_HasTypeExpression(const statement::Raise& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasTypeExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndRaise_HasTypeExpression(const statement::Raise& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasValueExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitRaise_HasValueExpression(const statement::Raise& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasValueExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndRaise_HasValueExpression(const statement::Raise& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitReturn_HasExpression(const statement::Return& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndReturn_HasExpression(const statement::Return& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasStatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSuite_HasStatement(const statement::Suite& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for hasStatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSuite_HasStatement(const statement::Suite& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasTarget edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTargetList_HasTarget(const statement::TargetList& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasTarget edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTargetList_HasTarget(const statement::TargetList& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryExcept_HasElseBody(const statement::TryExcept& begin, const statement::Suite& end);

      /**
      * \brief Edge end visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTryExcept_HasElseBody(const statement::TryExcept& begin, const statement::Suite& end);

      /**
      * \brief Edge  visitor for hasHandler edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryExcept_HasHandler(const statement::TryExcept& begin, const statement::Handler& end);

      /**
      * \brief Edge end visitor for hasHandler edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTryExcept_HasHandler(const statement::TryExcept& begin, const statement::Handler& end);

      /**
      * \brief Edge  visitor for hasFinallyBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryExcept_HasFinallyBody(const statement::TryExcept& begin, const statement::Suite& end);

      /**
      * \brief Edge end visitor for hasFinallyBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTryExcept_HasFinallyBody(const statement::TryExcept& begin, const statement::Suite& end);

      /**
      * \brief Edge  visitor for hasFinallyBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryFinal_HasFinallyBody(const statement::TryFinal& begin, const statement::Suite& end);

      /**
      * \brief Edge end visitor for hasFinallyBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTryFinal_HasFinallyBody(const statement::TryFinal& begin, const statement::Suite& end);

      /**
      * \brief Edge  visitor for hasTestExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhile_HasTestExpression(const statement::While& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasTestExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndWhile_HasTestExpression(const statement::While& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWith_HasExpression(const statement::With& begin, const expression::Expression& end);

      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndWith_HasExpression(const statement::With& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWith_HasTargetList(const statement::With& begin, const statement::TargetList& end);

      /**
      * \brief Edge end visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndWith_HasTargetList(const statement::With& begin, const statement::TargetList& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitReferenceType_RefersTo(const type::ReferenceType& begin, const base::Positioned& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndReferenceType_RefersTo(const type::ReferenceType& begin, const base::Positioned& end);

    protected:
      /** \internal \brief Stores the depth position in the ASG. */
      unsigned depth;
  }; // Visitor


}}}
#endif

