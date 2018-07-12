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

/**
* \file VisitorSimpleEdge.cpp
* \brief Contains declaration of VisitorSimpleEdge class.
*/

namespace columbus { namespace python { namespace asg {
      VisitorSimpleEdge::~VisitorSimpleEdge(){};

      /**
      * \brief Edge visitor for comments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitPositioned_Comments(const base::Positioned& begin, const base::Comment& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for comments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndPositioned_Comments(const base::Positioned& begin, const base::Comment& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasPositionalArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitArgumentList_HasPositionalArguments(const expression::ArgumentList& begin, const expression::ExpressionList& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasPositionalArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndArgumentList_HasPositionalArguments(const expression::ArgumentList& begin, const expression::ExpressionList& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasDictionary edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitArgumentList_HasDictionary(const expression::ArgumentList& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasDictionary edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndArgumentList_HasDictionary(const expression::ArgumentList& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasKeyword edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitArgumentList_HasKeyword(const expression::ArgumentList& begin, const expression::Keyword& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasKeyword edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndArgumentList_HasKeyword(const expression::ArgumentList& begin, const expression::Keyword& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTuple edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitArgumentList_HasTuple(const expression::ArgumentList& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTuple edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndArgumentList_HasTuple(const expression::ArgumentList& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasLeftExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBinary_HasLeftExpression(const expression::Binary& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasLeftExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBinary_HasLeftExpression(const expression::Binary& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasRightExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBinary_HasRightExpression(const expression::Binary& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasRightExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBinary_HasRightExpression(const expression::Binary& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCall_HasArgumentList(const expression::Call& begin, const expression::ArgumentList& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCall_HasArgumentList(const expression::Call& begin, const expression::ArgumentList& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCall_RefersTo(const expression::Call& begin, const statement::CompoundStatement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCall_RefersTo(const expression::Call& begin, const statement::CompoundStatement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasKeyValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDictComp_HasKeyValue(const expression::DictComp& begin, const expression::KeyValue& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasKeyValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDictComp_HasKeyValue(const expression::DictComp& begin, const expression::KeyValue& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDictComp_HasGenerator(const expression::DictComp& begin, const expression::Generator& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDictComp_HasGenerator(const expression::DictComp& begin, const expression::Generator& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasKeyValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDictionary_HasKeyValue(const expression::Dictionary& begin, const expression::KeyValue& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasKeyValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDictionary_HasKeyValue(const expression::Dictionary& begin, const expression::KeyValue& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitExpression_HasType(const expression::Expression& begin, const type::Type& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndExpression_HasType(const expression::Expression& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitExpressionList_HasExpression(const expression::ExpressionList& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndExpressionList_HasExpression(const expression::ExpressionList& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasItem edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitExtSlice_HasItem(const expression::ExtSlice& begin, const expression::Slicing& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasItem edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndExtSlice_HasItem(const expression::ExtSlice& begin, const expression::Slicing& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitGenerator_HasCondition(const expression::Generator& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasCondition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndGenerator_HasCondition(const expression::Generator& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasIter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitGenerator_HasIter(const expression::Generator& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasIter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndGenerator_HasIter(const expression::Generator& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTarget edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitGenerator_HasTarget(const expression::Generator& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTarget edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndGenerator_HasTarget(const expression::Generator& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitGeneratorExpression_HasExpression(const expression::GeneratorExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndGeneratorExpression_HasExpression(const expression::GeneratorExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitGeneratorExpression_HasGenerator(const expression::GeneratorExpression& begin, const expression::Generator& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndGeneratorExpression_HasGenerator(const expression::GeneratorExpression& begin, const expression::Generator& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIdentifier_RefersTo(const expression::Identifier& begin, const module::Object& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIdentifier_RefersTo(const expression::Identifier& begin, const module::Object& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIfExpression_HasBody(const expression::IfExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIfExpression_HasBody(const expression::IfExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIfExpression_HasElseBody(const expression::IfExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIfExpression_HasElseBody(const expression::IfExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIfExpression_HasTest(const expression::IfExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIfExpression_HasTest(const expression::IfExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitKeyValue_HasKey(const expression::KeyValue& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndKeyValue_HasKey(const expression::KeyValue& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitKeyValue_HasValue(const expression::KeyValue& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndKeyValue_HasValue(const expression::KeyValue& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitKeyword_HasKey(const expression::Keyword& begin, const expression::Identifier& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndKeyword_HasKey(const expression::Keyword& begin, const expression::Identifier& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitKeyword_HasValue(const expression::Keyword& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndKeyword_HasValue(const expression::Keyword& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitLambda_HasObject(const expression::Lambda& begin, const module::Object& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndLambda_HasObject(const expression::Lambda& begin, const module::Object& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitLambda_HasParameter(const expression::Lambda& begin, const statement::Parameter& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndLambda_HasParameter(const expression::Lambda& begin, const statement::Parameter& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitLambda_HasExpression(const expression::Lambda& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndLambda_HasExpression(const expression::Lambda& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitList_HasExpression(const expression::List& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndList_HasExpression(const expression::List& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitListComp_HasExpression(const expression::ListComp& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndListComp_HasExpression(const expression::ListComp& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitListComp_HasGenerator(const expression::ListComp& begin, const expression::Generator& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndListComp_HasGenerator(const expression::ListComp& begin, const expression::Generator& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSet_HasExpression(const expression::Set& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSet_HasExpression(const expression::Set& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSetComp_HasExpression(const expression::SetComp& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSetComp_HasExpression(const expression::SetComp& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSetComp_HasGenerator(const expression::SetComp& begin, const expression::Generator& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasGenerator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSetComp_HasGenerator(const expression::SetComp& begin, const expression::Generator& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasLowerBound edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSlice_HasLowerBound(const expression::Slice& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasLowerBound edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSlice_HasLowerBound(const expression::Slice& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasStride edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSlice_HasStride(const expression::Slice& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasStride edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSlice_HasStride(const expression::Slice& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasUpperBound edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSlice_HasUpperBound(const expression::Slice& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasUpperBound edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSlice_HasUpperBound(const expression::Slice& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpressionList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitStringConversion_HasExpressionList(const expression::StringConversion& begin, const expression::ExpressionList& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpressionList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndStringConversion_HasExpressionList(const expression::StringConversion& begin, const expression::ExpressionList& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasSlicing edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSubscription_HasSlicing(const expression::Subscription& begin, const expression::Slicing& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasSlicing edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSubscription_HasSlicing(const expression::Subscription& begin, const expression::Slicing& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitUnary_HasExpression(const expression::Unary& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndUnary_HasExpression(const expression::Unary& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasYieldExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitYieldExpression_HasYieldExpression(const expression::YieldExpression& begin, const expression::ExpressionList& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasYieldExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndYieldExpression_HasYieldExpression(const expression::YieldExpression& begin, const expression::ExpressionList& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitModule_HasObject(const module::Module& begin, const module::Object& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndModule_HasObject(const module::Module& begin, const module::Object& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasStatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitModule_HasStatement(const module::Module& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasStatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndModule_HasStatement(const module::Module& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for docstring edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitModule_Docstring(const module::Module& begin, const base::Docstring& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for docstring edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndModule_Docstring(const module::Module& begin, const base::Docstring& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitObject_RefersTo(const module::Object& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndObject_RefersTo(const module::Object& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitObject_HasType(const module::Object& begin, const type::Type& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndObject_HasType(const module::Object& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasModule edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitPackage_HasModule(const module::Package& begin, const module::Module& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasModule edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndPackage_HasModule(const module::Package& begin, const module::Module& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasPackage edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitPackage_HasPackage(const module::Package& begin, const module::Package& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasPackage edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndPackage_HasPackage(const module::Package& begin, const module::Package& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAlias_RefersTo(const statement::Alias& begin, const base::Base& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAlias_RefersTo(const statement::Alias& begin, const base::Base& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasMsgExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAssert_HasMsgExpression(const statement::Assert& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasMsgExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAssert_HasMsgExpression(const statement::Assert& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTestExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAssert_HasTestExpression(const statement::Assert& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTestExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAssert_HasTestExpression(const statement::Assert& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAssign_HasExpression(const statement::Assign& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAssign_HasExpression(const statement::Assign& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAssign_HasTargetList(const statement::Assign& begin, const statement::TargetList& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAssign_HasTargetList(const statement::Assign& begin, const statement::TargetList& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBaseSpecifier_HasName(const statement::BaseSpecifier& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBaseSpecifier_HasName(const statement::BaseSpecifier& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for derivesFrom edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBaseSpecifier_DerivesFrom(const statement::BaseSpecifier& begin, const statement::ClassDef& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for derivesFrom edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBaseSpecifier_DerivesFrom(const statement::BaseSpecifier& begin, const statement::ClassDef& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitClassDef_HasObject(const statement::ClassDef& begin, const module::Object& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndClassDef_HasObject(const statement::ClassDef& begin, const module::Object& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBaseSpecifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitClassDef_HasBaseSpecifier(const statement::ClassDef& begin, const statement::BaseSpecifier& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBaseSpecifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndClassDef_HasBaseSpecifier(const statement::ClassDef& begin, const statement::BaseSpecifier& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasDecorator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitClassDef_HasDecorator(const statement::ClassDef& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasDecorator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndClassDef_HasDecorator(const statement::ClassDef& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitClassDef_RefersTo(const statement::ClassDef& begin, const module::Object& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndClassDef_RefersTo(const statement::ClassDef& begin, const module::Object& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for docstring edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitClassDef_Docstring(const statement::ClassDef& begin, const base::Docstring& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for docstring edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndClassDef_Docstring(const statement::ClassDef& begin, const base::Docstring& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCompoundStatement_HasBody(const statement::CompoundStatement& begin, const statement::Suite& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCompoundStatement_HasBody(const statement::CompoundStatement& begin, const statement::Suite& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitDelete_HasTargetList(const statement::Delete& begin, const statement::TargetList& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndDelete_HasTargetList(const statement::Delete& begin, const statement::TargetList& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitExec_HasExpression(const statement::Exec& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndExec_HasExpression(const statement::Exec& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasGlobals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitExec_HasGlobals(const statement::Exec& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasGlobals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndExec_HasGlobals(const statement::Exec& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasLocals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitExec_HasLocals(const statement::Exec& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasLocals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndExec_HasLocals(const statement::Exec& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpressionList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFor_HasExpressionList(const statement::For& begin, const expression::ExpressionList& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpressionList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFor_HasExpressionList(const statement::For& begin, const expression::ExpressionList& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFor_HasTargetList(const statement::For& begin, const statement::TargetList& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFor_HasTargetList(const statement::For& begin, const statement::TargetList& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasDecorator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFunctionDef_HasDecorator(const statement::FunctionDef& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasDecorator edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFunctionDef_HasDecorator(const statement::FunctionDef& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFunctionDef_HasObject(const statement::FunctionDef& begin, const module::Object& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFunctionDef_HasObject(const statement::FunctionDef& begin, const module::Object& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFunctionDef_HasParameter(const statement::FunctionDef& begin, const statement::Parameter& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFunctionDef_HasParameter(const statement::FunctionDef& begin, const statement::Parameter& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFunctionDef_RefersTo(const statement::FunctionDef& begin, const module::Object& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFunctionDef_RefersTo(const statement::FunctionDef& begin, const module::Object& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for returnType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFunctionDef_ReturnType(const statement::FunctionDef& begin, const type::Type& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for returnType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFunctionDef_ReturnType(const statement::FunctionDef& begin, const type::Type& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for docstring edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFunctionDef_Docstring(const statement::FunctionDef& begin, const base::Docstring& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for docstring edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFunctionDef_Docstring(const statement::FunctionDef& begin, const base::Docstring& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitGlobal_HasIdentifier(const statement::Global& begin, const expression::Identifier& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndGlobal_HasIdentifier(const statement::Global& begin, const expression::Identifier& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitHandler_HasName(const statement::Handler& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasName edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndHandler_HasName(const statement::Handler& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExceptBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitHandler_HasExceptBody(const statement::Handler& begin, const statement::Suite& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExceptBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndHandler_HasExceptBody(const statement::Handler& begin, const statement::Suite& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitHandler_HasType(const statement::Handler& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndHandler_HasType(const statement::Handler& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIf_HasElseBody(const statement::If& begin, const statement::Suite& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIf_HasElseBody(const statement::If& begin, const statement::Suite& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTestExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIf_HasTestExpression(const statement::If& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTestExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIf_HasTestExpression(const statement::If& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasAlias edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitImportStatement_HasAlias(const statement::ImportStatement& begin, const statement::Alias& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasAlias edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndImportStatement_HasAlias(const statement::ImportStatement& begin, const statement::Alias& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIteration_HasElseBody(const statement::Iteration& begin, const statement::Suite& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIteration_HasElseBody(const statement::Iteration& begin, const statement::Suite& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasDefaultValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitParameter_HasDefaultValue(const statement::Parameter& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasDefaultValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndParameter_HasDefaultValue(const statement::Parameter& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitParameter_RefersTo(const statement::Parameter& begin, const module::Object& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndParameter_RefersTo(const statement::Parameter& begin, const module::Object& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpressionList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitPrint_HasExpressionList(const statement::Print& begin, const expression::ExpressionList& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpressionList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndPrint_HasExpressionList(const statement::Print& begin, const expression::ExpressionList& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasDestination edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitPrint_HasDestination(const statement::Print& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasDestination edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndPrint_HasDestination(const statement::Print& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTracebackExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitRaise_HasTracebackExpression(const statement::Raise& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTracebackExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndRaise_HasTracebackExpression(const statement::Raise& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTypeExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitRaise_HasTypeExpression(const statement::Raise& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTypeExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndRaise_HasTypeExpression(const statement::Raise& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasValueExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitRaise_HasValueExpression(const statement::Raise& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasValueExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndRaise_HasValueExpression(const statement::Raise& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitReturn_HasExpression(const statement::Return& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndReturn_HasExpression(const statement::Return& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasStatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSuite_HasStatement(const statement::Suite& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasStatement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSuite_HasStatement(const statement::Suite& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTarget edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTargetList_HasTarget(const statement::TargetList& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTarget edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTargetList_HasTarget(const statement::TargetList& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTryExcept_HasElseBody(const statement::TryExcept& begin, const statement::Suite& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasElseBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTryExcept_HasElseBody(const statement::TryExcept& begin, const statement::Suite& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasHandler edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTryExcept_HasHandler(const statement::TryExcept& begin, const statement::Handler& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasHandler edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTryExcept_HasHandler(const statement::TryExcept& begin, const statement::Handler& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasFinallyBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTryExcept_HasFinallyBody(const statement::TryExcept& begin, const statement::Suite& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasFinallyBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTryExcept_HasFinallyBody(const statement::TryExcept& begin, const statement::Suite& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasFinallyBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTryFinal_HasFinallyBody(const statement::TryFinal& begin, const statement::Suite& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasFinallyBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTryFinal_HasFinallyBody(const statement::TryFinal& begin, const statement::Suite& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTestExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitWhile_HasTestExpression(const statement::While& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTestExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndWhile_HasTestExpression(const statement::While& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitWith_HasExpression(const statement::With& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndWith_HasExpression(const statement::With& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitWith_HasTargetList(const statement::With& begin, const statement::TargetList& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTargetList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndWith_HasTargetList(const statement::With& begin, const statement::TargetList& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitReferenceType_RefersTo(const type::ReferenceType& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndReferenceType_RefersTo(const type::ReferenceType& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }

}}}
