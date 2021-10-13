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

#include "javascript/inc/javascript.h"

/**
* \file VisitorSimpleEdge.cpp
* \brief Contains declaration of VisitorSimpleEdge class.
*/

namespace columbus { namespace javascript { namespace asg {
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
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitProgram_HasBody(const base::Program& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndProgram_HasBody(const base::Program& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasPrograms edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSystem_HasPrograms(const base::System& begin, const base::Program& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasPrograms edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSystem_HasPrograms(const base::System& begin, const base::Program& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitExportAllDeclaration_HasSource(const declaration::ExportAllDeclaration& begin, const expression::Literal& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndExportAllDeclaration_HasSource(const declaration::ExportAllDeclaration& begin, const expression::Literal& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitExportDefaultDeclaration_HasDeclaration(const declaration::ExportDefaultDeclaration& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndExportDefaultDeclaration_HasDeclaration(const declaration::ExportDefaultDeclaration& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitExportNamedDeclaration_HasDeclaration(const declaration::ExportNamedDeclaration& begin, const declaration::Declaration& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndExportNamedDeclaration_HasDeclaration(const declaration::ExportNamedDeclaration& begin, const declaration::Declaration& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasSpecifiers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitExportNamedDeclaration_HasSpecifiers(const declaration::ExportNamedDeclaration& begin, const structure::ExportSpecifier& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasSpecifiers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndExportNamedDeclaration_HasSpecifiers(const declaration::ExportNamedDeclaration& begin, const structure::ExportSpecifier& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitExportNamedDeclaration_HasSource(const declaration::ExportNamedDeclaration& begin, const expression::Literal& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndExportNamedDeclaration_HasSource(const declaration::ExportNamedDeclaration& begin, const expression::Literal& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasSpecifiers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitImportDeclaration_HasSpecifiers(const declaration::ImportDeclaration& begin, const structure::ImpSpecifier& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasSpecifiers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndImportDeclaration_HasSpecifiers(const declaration::ImportDeclaration& begin, const structure::ImpSpecifier& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitImportDeclaration_HasSource(const declaration::ImportDeclaration& begin, const expression::Literal& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndImportDeclaration_HasSource(const declaration::ImportDeclaration& begin, const expression::Literal& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasDeclarations edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitVariableDeclaration_HasDeclarations(const declaration::VariableDeclaration& begin, const declaration::VariableDeclarator& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasDeclarations edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndVariableDeclaration_HasDeclarations(const declaration::VariableDeclaration& begin, const declaration::VariableDeclarator& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitVariableDeclarator_HasIdentifier(const declaration::VariableDeclarator& begin, const statement::Pattern& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndVariableDeclarator_HasIdentifier(const declaration::VariableDeclarator& begin, const statement::Pattern& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasInit edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitVariableDeclarator_HasInit(const declaration::VariableDeclarator& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasInit edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndVariableDeclarator_HasInit(const declaration::VariableDeclarator& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasElements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitArrayExpression_HasElements(const expression::ArrayExpression& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasElements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndArrayExpression_HasElements(const expression::ArrayExpression& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAssignmentExpression_HasLeft(const expression::AssignmentExpression& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAssignmentExpression_HasLeft(const expression::AssignmentExpression& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAssignmentExpression_HasRight(const expression::AssignmentExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAssignmentExpression_HasRight(const expression::AssignmentExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAwaitExpression_HasArgument(const expression::AwaitExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAwaitExpression_HasArgument(const expression::AwaitExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBinaryExpression_HasLeft(const expression::BinaryExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBinaryExpression_HasLeft(const expression::BinaryExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBinaryExpression_HasRight(const expression::BinaryExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBinaryExpression_HasRight(const expression::BinaryExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasCallee edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCallExpression_HasCallee(const expression::CallExpression& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasCallee edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCallExpression_HasCallee(const expression::CallExpression& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCallExpression_HasArguments(const expression::CallExpression& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCallExpression_HasArguments(const expression::CallExpression& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCallExpression_Calls(const expression::CallExpression& begin, const statement::Function& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCallExpression_Calls(const expression::CallExpression& begin, const statement::Function& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasAlternate edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitConditionalExpression_HasAlternate(const expression::ConditionalExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasAlternate edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndConditionalExpression_HasAlternate(const expression::ConditionalExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasConsequent edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitConditionalExpression_HasConsequent(const expression::ConditionalExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasConsequent edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndConditionalExpression_HasConsequent(const expression::ConditionalExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitConditionalExpression_HasTest(const expression::ConditionalExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndConditionalExpression_HasTest(const expression::ConditionalExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIdentifier_RefersTo(const expression::Identifier& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIdentifier_RefersTo(const expression::Identifier& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitLogicalExpression_HasLeft(const expression::LogicalExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndLogicalExpression_HasLeft(const expression::LogicalExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitLogicalExpression_HasRight(const expression::LogicalExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndLogicalExpression_HasRight(const expression::LogicalExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasProperty edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMemberExpression_HasProperty(const expression::MemberExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasProperty edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMemberExpression_HasProperty(const expression::MemberExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMemberExpression_HasObject(const expression::MemberExpression& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMemberExpression_HasObject(const expression::MemberExpression& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasMeta edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMetaProperty_HasMeta(const expression::MetaProperty& begin, const expression::Identifier& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasMeta edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMetaProperty_HasMeta(const expression::MetaProperty& begin, const expression::Identifier& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasProperty edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMetaProperty_HasProperty(const expression::MetaProperty& begin, const expression::Identifier& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasProperty edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMetaProperty_HasProperty(const expression::MetaProperty& begin, const expression::Identifier& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasCallee edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNewExpression_HasCallee(const expression::NewExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasCallee edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNewExpression_HasCallee(const expression::NewExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNewExpression_HasArguments(const expression::NewExpression& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNewExpression_HasArguments(const expression::NewExpression& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitNewExpression_Calls(const expression::NewExpression& begin, const statement::Function& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndNewExpression_Calls(const expression::NewExpression& begin, const statement::Function& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasProperties edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitObjectExpression_HasProperties(const expression::ObjectExpression& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasProperties edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndObjectExpression_HasProperties(const expression::ObjectExpression& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitProperty_HasValue(const expression::Property& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndProperty_HasValue(const expression::Property& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitProperty_HasKey(const expression::Property& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndProperty_HasKey(const expression::Property& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpressions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSequenceExpression_HasExpressions(const expression::SequenceExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpressions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSequenceExpression_HasExpressions(const expression::SequenceExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSpreadElement_HasArgument(const expression::SpreadElement& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSpreadElement_HasArgument(const expression::SpreadElement& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTaggedTemplateExpression_HasTag(const expression::TaggedTemplateExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTaggedTemplateExpression_HasTag(const expression::TaggedTemplateExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasQuasi edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTaggedTemplateExpression_HasQuasi(const expression::TaggedTemplateExpression& begin, const expression::TemplateLiteral& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasQuasi edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTaggedTemplateExpression_HasQuasi(const expression::TaggedTemplateExpression& begin, const expression::TemplateLiteral& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasQuasis edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTemplateLiteral_HasQuasis(const expression::TemplateLiteral& begin, const expression::TemplateElement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasQuasis edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTemplateLiteral_HasQuasis(const expression::TemplateLiteral& begin, const expression::TemplateElement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpressions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTemplateLiteral_HasExpressions(const expression::TemplateLiteral& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpressions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTemplateLiteral_HasExpressions(const expression::TemplateLiteral& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitUnaryExpression_HasArgument(const expression::UnaryExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndUnaryExpression_HasArgument(const expression::UnaryExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitUpdateExpression_HasArgument(const expression::UpdateExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndUpdateExpression_HasArgument(const expression::UpdateExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitYieldExpression_HasArgument(const expression::YieldExpression& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndYieldExpression_HasArgument(const expression::YieldExpression& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasElements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitArrayPattern_HasElements(const statement::ArrayPattern& begin, const statement::Pattern& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasElements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndArrayPattern_HasElements(const statement::ArrayPattern& begin, const statement::Pattern& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAssignmentPattern_HasLeft(const statement::AssignmentPattern& begin, const statement::Pattern& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAssignmentPattern_HasLeft(const statement::AssignmentPattern& begin, const statement::Pattern& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitAssignmentPattern_HasRight(const statement::AssignmentPattern& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndAssignmentPattern_HasRight(const statement::AssignmentPattern& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBlockStatement_HasBody(const statement::BlockStatement& begin, const statement::Statement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBlockStatement_HasBody(const statement::BlockStatement& begin, const statement::Statement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasLabel edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitBreakStatement_HasLabel(const statement::BreakStatement& begin, const expression::Identifier& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasLabel edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndBreakStatement_HasLabel(const statement::BreakStatement& begin, const expression::Identifier& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasParam edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCatchClause_HasParam(const statement::CatchClause& begin, const statement::Pattern& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasParam edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCatchClause_HasParam(const statement::CatchClause& begin, const statement::Pattern& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitCatchClause_HasBody(const statement::CatchClause& begin, const statement::BlockStatement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndCatchClause_HasBody(const statement::CatchClause& begin, const statement::BlockStatement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasLabel edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitContinueStatement_HasLabel(const statement::ContinueStatement& begin, const expression::Identifier& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasLabel edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndContinueStatement_HasLabel(const statement::ContinueStatement& begin, const expression::Identifier& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitExpressionStatement_HasExpression(const statement::ExpressionStatement& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndExpressionStatement_HasExpression(const statement::ExpressionStatement& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitForInStatement_HasRight(const statement::ForInStatement& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndForInStatement_HasRight(const statement::ForInStatement& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitForInStatement_HasBody(const statement::ForInStatement& begin, const statement::Statement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndForInStatement_HasBody(const statement::ForInStatement& begin, const statement::Statement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitForInStatement_HasLeft(const statement::ForInStatement& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndForInStatement_HasLeft(const statement::ForInStatement& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitForStatement_HasBody(const statement::ForStatement& begin, const statement::Statement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndForStatement_HasBody(const statement::ForStatement& begin, const statement::Statement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitForStatement_HasTest(const statement::ForStatement& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndForStatement_HasTest(const statement::ForStatement& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasUpdate edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitForStatement_HasUpdate(const statement::ForStatement& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasUpdate edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndForStatement_HasUpdate(const statement::ForStatement& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasInit edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitForStatement_HasInit(const statement::ForStatement& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasInit edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndForStatement_HasInit(const statement::ForStatement& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasParams edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFunction_HasParams(const statement::Function& begin, const statement::Pattern& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasParams edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFunction_HasParams(const statement::Function& begin, const statement::Pattern& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFunction_HasBody(const statement::Function& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFunction_HasBody(const statement::Function& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitFunction_HasIdentifier(const statement::Function& begin, const expression::Identifier& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndFunction_HasIdentifier(const statement::Function& begin, const expression::Identifier& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIfStatement_HasTest(const statement::IfStatement& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIfStatement_HasTest(const statement::IfStatement& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasConsequent edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIfStatement_HasConsequent(const statement::IfStatement& begin, const statement::Statement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasConsequent edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIfStatement_HasConsequent(const statement::IfStatement& begin, const statement::Statement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasAlternate edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitIfStatement_HasAlternate(const statement::IfStatement& begin, const statement::Statement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasAlternate edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndIfStatement_HasAlternate(const statement::IfStatement& begin, const statement::Statement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasLabel edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitLabeledStatement_HasLabel(const statement::LabeledStatement& begin, const expression::Identifier& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasLabel edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndLabeledStatement_HasLabel(const statement::LabeledStatement& begin, const expression::Identifier& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitLabeledStatement_HasBody(const statement::LabeledStatement& begin, const statement::Statement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndLabeledStatement_HasBody(const statement::LabeledStatement& begin, const statement::Statement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasProperties edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitObjectPattern_HasProperties(const statement::ObjectPattern& begin, const base::Positioned& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasProperties edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndObjectPattern_HasProperties(const statement::ObjectPattern& begin, const base::Positioned& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitRestElement_HasArgument(const statement::RestElement& begin, const statement::Pattern& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndRestElement_HasArgument(const statement::RestElement& begin, const statement::Pattern& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitReturnStatement_HasArgument(const statement::ReturnStatement& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndReturnStatement_HasArgument(const statement::ReturnStatement& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSwitchCase_HasTest(const statement::SwitchCase& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSwitchCase_HasTest(const statement::SwitchCase& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasConsequent edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSwitchCase_HasConsequent(const statement::SwitchCase& begin, const statement::Statement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasConsequent edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSwitchCase_HasConsequent(const statement::SwitchCase& begin, const statement::Statement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasDiscriminant edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSwitchStatement_HasDiscriminant(const statement::SwitchStatement& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasDiscriminant edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSwitchStatement_HasDiscriminant(const statement::SwitchStatement& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasCases edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitSwitchStatement_HasCases(const statement::SwitchStatement& begin, const statement::SwitchCase& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasCases edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndSwitchStatement_HasCases(const statement::SwitchStatement& begin, const statement::SwitchCase& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitThrowStatement_HasArgument(const statement::ThrowStatement& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndThrowStatement_HasArgument(const statement::ThrowStatement& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTryStatement_HasBlock(const statement::TryStatement& begin, const statement::BlockStatement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTryStatement_HasBlock(const statement::TryStatement& begin, const statement::BlockStatement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasFinalizer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTryStatement_HasFinalizer(const statement::TryStatement& begin, const statement::BlockStatement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasFinalizer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTryStatement_HasFinalizer(const statement::TryStatement& begin, const statement::BlockStatement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasHandler edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitTryStatement_HasHandler(const statement::TryStatement& begin, const statement::CatchClause& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasHandler edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndTryStatement_HasHandler(const statement::TryStatement& begin, const statement::CatchClause& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitWhileStatement_HasBody(const statement::WhileStatement& begin, const statement::Statement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndWhileStatement_HasBody(const statement::WhileStatement& begin, const statement::Statement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitWhileStatement_HasTest(const statement::WhileStatement& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndWhileStatement_HasTest(const statement::WhileStatement& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitWithStatement_HasObject(const statement::WithStatement& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndWithStatement_HasObject(const statement::WithStatement& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitWithStatement_HasBody(const statement::WithStatement& begin, const statement::Statement& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndWithStatement_HasBody(const statement::WithStatement& begin, const statement::Statement& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitClass_HasBody(const structure::Class& begin, const structure::ClassBody& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndClass_HasBody(const structure::Class& begin, const structure::ClassBody& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasSuperClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitClass_HasSuperClass(const structure::Class& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasSuperClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndClass_HasSuperClass(const structure::Class& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitClass_HasIdentifier(const structure::Class& begin, const expression::Identifier& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndClass_HasIdentifier(const structure::Class& begin, const expression::Identifier& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitClassBody_HasBody(const structure::ClassBody& begin, const structure::MethodDefinition& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndClassBody_HasBody(const structure::ClassBody& begin, const structure::MethodDefinition& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasExported edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitExportSpecifier_HasExported(const structure::ExportSpecifier& begin, const expression::Identifier& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasExported edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndExportSpecifier_HasExported(const structure::ExportSpecifier& begin, const expression::Identifier& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasImported edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitImportSpecifier_HasImported(const structure::ImportSpecifier& begin, const expression::Identifier& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasImported edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndImportSpecifier_HasImported(const structure::ImportSpecifier& begin, const expression::Identifier& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethodDefinition_HasKey(const structure::MethodDefinition& begin, const expression::Expression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethodDefinition_HasKey(const structure::MethodDefinition& begin, const expression::Expression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitMethodDefinition_HasValue(const structure::MethodDefinition& begin, const expression::FunctionExpression& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndMethodDefinition_HasValue(const structure::MethodDefinition& begin, const expression::FunctionExpression& end) {
        visitAllEdgeEnd (begin, end);
      }
      /**
      * \brief Edge  visitor for hasLocal edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitModuleSpecifier_HasLocal(const structure::ModuleSpecifier& begin, const expression::Identifier& end) {
        visitAllEdge (begin, end);
      }
      /**
      * \brief Edge end visitor for hasLocal edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      void VisitorSimpleEdge::visitEndModuleSpecifier_HasLocal(const structure::ModuleSpecifier& begin, const expression::Identifier& end) {
        visitAllEdgeEnd (begin, end);
      }

}}}
