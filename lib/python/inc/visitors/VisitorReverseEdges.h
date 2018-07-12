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

#ifndef _PYTHON_VISITORREVERSEEDGES_H_
#define _PYTHON_VISITORREVERSEEDGES_H_

#include "python/inc/python.h"

/**
* \file VisitorReverseEdges.h
* \brief Contains declaration of VisitorReverseEdges class.
*/

namespace columbus { namespace python { namespace asg {
  /**
  * \brief Collects the inverse relation of any "one way" defined edges.
  */
  class VisitorReverseEdges : public VisitorAbstractNodes {
    private:

      /**
      * \brief Disable the copy of object .
      */
      VisitorReverseEdges(const VisitorReverseEdges& );

      /**
      * \brief Disable the copy of object.
      */
      VisitorReverseEdges& operator=(const VisitorReverseEdges& );

    protected:

      /**
      * \brief Only ReverseEdges can instantiates this class.
      * \param reverseEdges [in] The edges are inserted into this.
      */
      VisitorReverseEdges(ReverseEdges* reverseEdges);

      /**
      * \brief Destructor.
      */
      virtual ~VisitorReverseEdges();

    public:

      /**
      * \brief Sets all node "existing" in AlgorithmReverseEdges.
      * \param node [in] The node.
      */
      virtual void visit(const base::Base &node, bool callVirtualBase = true);

      /**
      * \brief Edge visitor for comments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPositioned_Comments(const base::Positioned& begin, const base::Comment& end);

      /**
      * \brief Edge  visitor for hasPositionalArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArgumentList_HasPositionalArguments(const expression::ArgumentList& begin, const expression::ExpressionList& end);

      /**
      * \brief Edge  visitor for hasDictionary edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArgumentList_HasDictionary(const expression::ArgumentList& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasKeyword edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArgumentList_HasKeyword(const expression::ArgumentList& begin, const expression::Keyword& end);

      /**
      * \brief Edge  visitor for hasTuple edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArgumentList_HasTuple(const expression::ArgumentList& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasLeftExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinary_HasLeftExpression(const expression::Binary& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasRightExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinary_HasRightExpression(const expression::Binary& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCall_HasArgumentList(const expression::Call& begin, const expression::ArgumentList& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCall_RefersTo(const expression::Call& begin, const statement::CompoundStatement& end);

      /**
      * \brief Edge  visitor for hasKeyValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDictComp_HasKeyValue(const expression::DictComp& begin, const expression::KeyValue& end);

      /**
      * \brief Edge  visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDictComp_HasGenerator(const expression::DictComp& begin, const expression::Generator& end);

      /**
      * \brief Edge  visitor for hasKeyValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDictionary_HasKeyValue(const expression::Dictionary& begin, const expression::KeyValue& end);

      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExpression_HasType(const expression::Expression& begin, const type::Type& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExpressionList_HasExpression(const expression::ExpressionList& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasItem edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExtSlice_HasItem(const expression::ExtSlice& begin, const expression::Slicing& end);

      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGenerator_HasCondition(const expression::Generator& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasIter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGenerator_HasIter(const expression::Generator& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTarget edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGenerator_HasTarget(const expression::Generator& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGeneratorExpression_HasExpression(const expression::GeneratorExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGeneratorExpression_HasGenerator(const expression::GeneratorExpression& begin, const expression::Generator& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIdentifier_RefersTo(const expression::Identifier& begin, const module::Object& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfExpression_HasBody(const expression::IfExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfExpression_HasElseBody(const expression::IfExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfExpression_HasTest(const expression::IfExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitKeyValue_HasKey(const expression::KeyValue& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitKeyValue_HasValue(const expression::KeyValue& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitKeyword_HasKey(const expression::Keyword& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitKeyword_HasValue(const expression::Keyword& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLambda_HasObject(const expression::Lambda& begin, const module::Object& end);

      /**
      * \brief Edge  visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLambda_HasParameter(const expression::Lambda& begin, const statement::Parameter& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLambda_HasExpression(const expression::Lambda& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitList_HasExpression(const expression::List& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitListComp_HasExpression(const expression::ListComp& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitListComp_HasGenerator(const expression::ListComp& begin, const expression::Generator& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSet_HasExpression(const expression::Set& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSetComp_HasExpression(const expression::SetComp& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSetComp_HasGenerator(const expression::SetComp& begin, const expression::Generator& end);

      /**
      * \brief Edge  visitor for hasLowerBound edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSlice_HasLowerBound(const expression::Slice& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasStride edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSlice_HasStride(const expression::Slice& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasUpperBound edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSlice_HasUpperBound(const expression::Slice& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpressionList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitStringConversion_HasExpressionList(const expression::StringConversion& begin, const expression::ExpressionList& end);

      /**
      * \brief Edge  visitor for hasSlicing edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSubscription_HasSlicing(const expression::Subscription& begin, const expression::Slicing& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUnary_HasExpression(const expression::Unary& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasYieldExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitYieldExpression_HasYieldExpression(const expression::YieldExpression& begin, const expression::ExpressionList& end);

      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitModule_HasObject(const module::Module& begin, const module::Object& end);

      /**
      * \brief Edge  visitor for hasStatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitModule_HasStatement(const module::Module& begin, const base::Positioned& end);

      /**
      * \brief Edge visitor for docstring edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitModule_Docstring(const module::Module& begin, const base::Docstring& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObject_RefersTo(const module::Object& begin, const base::Positioned& end);

      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObject_HasType(const module::Object& begin, const type::Type& end);

      /**
      * \brief Edge  visitor for hasModule edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPackage_HasModule(const module::Package& begin, const module::Module& end);

      /**
      * \brief Edge  visitor for hasPackage edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPackage_HasPackage(const module::Package& begin, const module::Package& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAlias_RefersTo(const statement::Alias& begin, const base::Base& end);

      /**
      * \brief Edge  visitor for hasMsgExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssert_HasMsgExpression(const statement::Assert& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTestExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssert_HasTestExpression(const statement::Assert& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssign_HasExpression(const statement::Assign& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssign_HasTargetList(const statement::Assign& begin, const statement::TargetList& end);

      /**
      * \brief Edge  visitor for hasName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseSpecifier_HasName(const statement::BaseSpecifier& begin, const expression::Expression& end);

      /**
      * \brief Edge visitor for derivesFrom edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseSpecifier_DerivesFrom(const statement::BaseSpecifier& begin, const statement::ClassDef& end);

      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassDef_HasObject(const statement::ClassDef& begin, const module::Object& end);

      /**
      * \brief Edge  visitor for hasBaseSpecifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassDef_HasBaseSpecifier(const statement::ClassDef& begin, const statement::BaseSpecifier& end);

      /**
      * \brief Edge  visitor for hasDecorator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassDef_HasDecorator(const statement::ClassDef& begin, const expression::Expression& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassDef_RefersTo(const statement::ClassDef& begin, const module::Object& end);

      /**
      * \brief Edge visitor for docstring edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassDef_Docstring(const statement::ClassDef& begin, const base::Docstring& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompoundStatement_HasBody(const statement::CompoundStatement& begin, const statement::Suite& end);

      /**
      * \brief Edge  visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDelete_HasTargetList(const statement::Delete& begin, const statement::TargetList& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExec_HasExpression(const statement::Exec& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasGlobals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExec_HasGlobals(const statement::Exec& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasLocals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExec_HasLocals(const statement::Exec& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpressionList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFor_HasExpressionList(const statement::For& begin, const expression::ExpressionList& end);

      /**
      * \brief Edge  visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFor_HasTargetList(const statement::For& begin, const statement::TargetList& end);

      /**
      * \brief Edge  visitor for hasDecorator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunctionDef_HasDecorator(const statement::FunctionDef& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunctionDef_HasObject(const statement::FunctionDef& begin, const module::Object& end);

      /**
      * \brief Edge  visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunctionDef_HasParameter(const statement::FunctionDef& begin, const statement::Parameter& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunctionDef_RefersTo(const statement::FunctionDef& begin, const module::Object& end);

      /**
      * \brief Edge visitor for returnType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunctionDef_ReturnType(const statement::FunctionDef& begin, const type::Type& end);

      /**
      * \brief Edge visitor for docstring edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunctionDef_Docstring(const statement::FunctionDef& begin, const base::Docstring& end);

      /**
      * \brief Edge  visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGlobal_HasIdentifier(const statement::Global& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitHandler_HasName(const statement::Handler& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExceptBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitHandler_HasExceptBody(const statement::Handler& begin, const statement::Suite& end);

      /**
      * \brief Edge  visitor for hasType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitHandler_HasType(const statement::Handler& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIf_HasElseBody(const statement::If& begin, const statement::Suite& end);

      /**
      * \brief Edge  visitor for hasTestExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIf_HasTestExpression(const statement::If& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasAlias edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImportStatement_HasAlias(const statement::ImportStatement& begin, const statement::Alias& end);

      /**
      * \brief Edge  visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIteration_HasElseBody(const statement::Iteration& begin, const statement::Suite& end);

      /**
      * \brief Edge  visitor for hasDefaultValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameter_HasDefaultValue(const statement::Parameter& begin, const expression::Expression& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameter_RefersTo(const statement::Parameter& begin, const module::Object& end);

      /**
      * \brief Edge  visitor for hasExpressionList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPrint_HasExpressionList(const statement::Print& begin, const expression::ExpressionList& end);

      /**
      * \brief Edge  visitor for hasDestination edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPrint_HasDestination(const statement::Print& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTracebackExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitRaise_HasTracebackExpression(const statement::Raise& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTypeExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitRaise_HasTypeExpression(const statement::Raise& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasValueExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitRaise_HasValueExpression(const statement::Raise& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitReturn_HasExpression(const statement::Return& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasStatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSuite_HasStatement(const statement::Suite& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasTarget edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTargetList_HasTarget(const statement::TargetList& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryExcept_HasElseBody(const statement::TryExcept& begin, const statement::Suite& end);

      /**
      * \brief Edge  visitor for hasHandler edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryExcept_HasHandler(const statement::TryExcept& begin, const statement::Handler& end);

      /**
      * \brief Edge  visitor for hasFinallyBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryExcept_HasFinallyBody(const statement::TryExcept& begin, const statement::Suite& end);

      /**
      * \brief Edge  visitor for hasFinallyBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryFinal_HasFinallyBody(const statement::TryFinal& begin, const statement::Suite& end);

      /**
      * \brief Edge  visitor for hasTestExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhile_HasTestExpression(const statement::While& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWith_HasExpression(const statement::With& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWith_HasTargetList(const statement::With& begin, const statement::TargetList& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitReferenceType_RefersTo(const type::ReferenceType& begin, const base::Positioned& end);

    protected:

      /** \internal \brief Edges are inserted into this ReverseEdges class. */
      ReverseEdges *revEdges;

      friend class ReverseEdges;

  }; // VisitorReverseEdges


}}}
#endif

