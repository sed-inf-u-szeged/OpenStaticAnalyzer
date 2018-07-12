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

#ifndef _PYTHON_VISITORFILTER_H_
#define _PYTHON_VISITORFILTER_H_

#include "python/inc/python.h"

/**
* \file VisitorFilter.h
* \brief Contains declaration of VisitorFilter class.
*/

namespace columbus { namespace python { namespace asg {
  /**
  * \brief VisitorFilter class filters out nodes from the ASG.
  */
  class VisitorFilter : public Visitor {
    protected:
      /** \internal \brief Pointer to the set(Not)FilteredThisNodeOnly() method. */
      void (Factory::*selector)(NodeId id);

    public:
      /**
      * \brief Constructor for VisitorFilter.
      * \param filter [in] If this parameter is true then the visitor will filter the nodes out. If it is false then it set the nodes to not filtered.
      */
      VisitorFilter(bool filter = true);

      /**
      * \brief Destructor.
      */
      virtual ~VisitorFilter();

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::Comment& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::Docstring& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ArgumentList& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AttributeRef& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::BinaryArithmetic& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::BinaryLogical& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Call& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::DictComp& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Dictionary& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Ellipsis& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ExpressionList& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ExtSlice& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::FloatNumber& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Generator& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::GeneratorExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Identifier& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::IfExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ImagNumber& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Index& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::IntegerLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::KeyValue& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Keyword& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Lambda& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::List& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ListComp& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::LongInteger& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Set& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::SetComp& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Slice& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::StringConversion& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::StringLiteral& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Subscription& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::UnaryOperation& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::YieldExpression& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const module::Module& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const module::Object& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const module::Package& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Alias& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Assert& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Assign& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::AugAssign& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::BaseSpecifier& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Break& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ClassDef& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Continue& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Delete& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Exec& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::For& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::FunctionDef& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Global& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Handler& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::If& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ImportFrom& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ImportStatement& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Parameter& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Pass& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Print& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Raise& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Return& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Suite& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::TargetList& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::TryExcept& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::TryFinal& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::While& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::With& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::DictType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::ReferenceType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::SequenceType& node , bool callVirtualBase = true);

      /**
      * \brief Deselects the actual node (and only this).
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::SimpleType& node , bool callVirtualBase = true);

  }; // VisitorFilter


}}}
#endif

