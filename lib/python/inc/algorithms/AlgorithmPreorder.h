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

#ifndef _PYTHON_ALGORITHMPREORDER_H_
#define _PYTHON_ALGORITHMPREORDER_H_

#include "python/inc/python.h"

#include <set>

#include <list>

/**
* \file AlgorithmPreorder.h
* \brief Contains the class `AlgorithmPreorder' which implements the preorder traversal of the ASG.
* This is the visitor which when visit a node it call itself for all tree edges.
*/

namespace columbus { namespace python { namespace asg {
  /**
  * \brief Implements the preorder traversal of the ASG.
  */
  class AlgorithmPreorder: public Algorithm , public Visitor{
    private:
      /**
      * \brief Disable copy of object.
      */
      AlgorithmPreorder(const AlgorithmPreorder&);

      /**
      * \brief Disable copy of object.
      */
      AlgorithmPreorder& operator=(const AlgorithmPreorder&);

    public:
      /**
      * \brief Constructor.
      */
      AlgorithmPreorder();

      /**
      * \brief Virtual destructor.
      */
      virtual ~AlgorithmPreorder();

      /**
      * \brief Sets that a node will be visited only once in the visiting.
      */
      void setSafeMode();

      /**
      * \brief Sets that the preorder is executed duly the graph (which means that a node can be visited more than once, even if there is a circle in the graph it will be an endless visiting).
      */
      void setUnsafeMode();

      /**
      * \brief Set visit cross edge tree.
      * \param visit [in] If visit parameter is true, cross edge trees are visited, otherwise they are not visited.
      */
      void setVisitCrossEdgeTree(bool visit);

      /**
      * \brief Set visit filtered edges.
      * \param visit [in] If visit parameter is true, filtered edges are visited, otherwise they are not visited.
      */
      void setVisitFilteredEdges(bool visit);

      /**
      * \brief Sets whether special nodes (or only used of them) are visited or not.
      * \param visit    [in] If visit parameter is true, special nodes are visited as well, otherwise they are not visited.
      * \param usedOnly [in] If usedOnly parameter is true, only those special nodes are visited that were 'used' during preorder.
      */
      void setVisitSpecialNodes(bool visit, bool usedOnly);

      /**
      * \brief Set the factory
      * \param node    [in] The preorder visits only the subtree of this node.
      */
      void setFactory(Factory& fact);

      /**
      * \brief add visitor
      * \param node    [in] The preorder visits only the subtree of this node.
      */
      void addVisitor(Visitor& visitor);

      /**
      * \brief Starts a preorder traversal which visits all nodes
      */
      void run();

      /**
      * \brief Starts a preorder traversal, recursively processing all subtres
      * \param node    [in] The preorder visits only the subtree of this node.
      */
      void run(const base::Base& node);

      /**
      * \brief Starts a preorder traversal which visits all nodes of the parameter `fact', then recursively processing all subtrees, and at every nodes call the appropriate visit function of the Visitor `visitor'
      * \param fact    [in] The factory of the ASG.
      * \param visitor [in] The visitor which is called to visit the given node or edge.
      * \deprecated  Please set the visitor with add visitor, set the factory with the set factory function
      */
      void run(const Factory& fact, Visitor& visitor);

      /**
      * \brief Starts a preorder traversal which visits all nodes of the parameter `fact' by processing the parameter `node', then recursively processing all subtrees, and at every nodes call the appropriate visit function of the Visitor `visitor'
      * \param fact    [in] The factory of the ASG.
      * \param visitor [in] The visitor which is called to visit the given node or edge.
      * \param node    [in] The preorder visits only the subtree of this node.
      * \deprecated Please set the visitor with add visitor, set the factory with the set factory function
      */
      void run(const Factory& fact, Visitor& visitor, const base::Base& node);

      /**
      * \brief Starts a preorder traversal which visits all nodes of the parameter `fact' by processing the node with the given id, then recursively processing all subtrees, and at every nodes call the appropriate visit function of the Visitor `visitor'
      * \param fact    [in] The factory of the ASG.
      * \param visitor [in] The visitor which is called to visit the given node or edge.
      * \param nodeId  [in] The preorder visits only the subtree of this node.
      * \deprecated Please set the visitor with add visitor, set the factory with the set factory function
      */
      void run(const Factory& fact, Visitor& visitor, NodeId nodeId);

      /**
      * \brief It set the edge as a tree edge
      * \param edgekind [in] The edge which will used as tree edge.
      */
      void setCrossEdgeToTraversal(EdgeKind edgekind);

      /**
      * \brief Adds the visitor to the stopped visitor set.
      * \param visitor [in] The visitor we adds.
      */
      void stop(Visitor* visitor);

      /** \internal \brief The visitor functions owerloades */
      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const base::Comment& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const base::Docstring& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::ArgumentList& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::AttributeRef& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::Await& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::BinaryArithmetic& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::BinaryLogical& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::BytesLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::Call& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::DictComp& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::Dictionary& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::Ellipsis& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::ExpressionList& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::ExtSlice& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::FloatNumber& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::FormattedValue& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::Generator& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::GeneratorExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::Identifier& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::IfExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::ImagNumber& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::Index& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::IntegerLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::JoinedStr& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::KeyValue& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::Keyword& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::Lambda& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::List& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::ListComp& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::LongInteger& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::NamedExpr& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::Set& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::SetComp& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::Slice& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::Starred& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::StringConversion& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::StringLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::Subscription& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::UnaryOperation& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::YieldExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const module::Module& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const module::Object& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const module::Package& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::Alias& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::AnnAssign& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::Assert& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::Assign& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::AugAssign& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::BaseSpecifier& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::Break& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::ClassDef& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::Continue& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::Delete& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::Exec& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::For& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::FunctionDef& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::Global& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::Handler& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::If& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::ImportFrom& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::ImportStatement& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::Nonlocal& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::Parameter& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::Pass& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::Print& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::Raise& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::Return& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::Suite& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::TargetList& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::Try& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::While& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::With& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::WithItem& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::DictType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::ReferenceType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::SequenceType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::SimpleType& node , bool callVirtualBase = true);

      /** \internal \brief End The visitor functions owerloades */
    protected:
      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const base::Base& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const base::Comment& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const base::Docstring& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const base::Named& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const base::Positioned& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ArgumentList& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::AttributeRef& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::Await& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::Binary& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::BinaryArithmetic& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::BinaryLogical& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::BytesLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::Call& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::DictComp& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::Dictionary& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::Ellipsis& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::Expression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ExpressionList& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ExtSlice& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::FloatNumber& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::FormattedValue& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::Generator& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::GeneratorExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::Identifier& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::IfExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ImagNumber& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::Index& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::IntegerLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::JoinedStr& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::KeyValue& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::Keyword& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::Lambda& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::List& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ListComp& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::Literal& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::LongInteger& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::NamedExpr& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::Set& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::SetComp& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::Slice& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::Slicing& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::Starred& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::StringConversion& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::StringLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::Subscription& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::Unary& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::UnaryOperation& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::YieldExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const module::Module& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const module::Object& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const module::Package& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::Alias& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::AnnAssign& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::Assert& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::Assign& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::AugAssign& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::BaseSpecifier& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::Break& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::ClassDef& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::CompoundStatement& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::Continue& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::Delete& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::Exec& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::For& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::FunctionDef& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::Global& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::Handler& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::If& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::ImportFrom& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::ImportStatement& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::Iteration& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::Nonlocal& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::Parameter& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::Pass& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::Print& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::Raise& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::Return& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::SimpleStatement& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::Statement& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::Suite& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::TargetList& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::Try& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::While& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::With& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::WithItem& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::DictType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::ReferenceType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::SequenceType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::SimpleType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::Type& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief Starts a preorder traversal.
      */
      void mainRun(const Factory* fact, Visitor* visitor, const base::Base* node);

      /**
      * \internal
      * \brief Prepare for traversal. Modyficcate the filters if need it. Call the startvisit function for the all given vistor. ect.)
      */
      void startPreorder();

      /**
      * \internal
      * \brief Reset enviroment to the origal state. and call the visitFinish functions 
      */
      void endPreorder();

      /**
      * \brief Removes the stopped visitors from the visitorList. Sets the needPreorderStop true if the list becomes empty.
      */
      void clearStoppedVisitors();

      /** \internal \brief If it is true, two node are not visited during preorder. */
      bool safeMode;

      /** \internal \brief Stores the ids of the node which are already visited during the actual run. */
      std::vector<bool> visitedNodes;

      /** \internal \brief The set of ids of nodes which need to be visited. */
      std::vector<bool> unvisitedNodes;

      /** \internal \brief If it is true, it collect the sub trees. */
      bool visitCrossEdgeTree;

      /** \internal \brief If it is true, the preorder is stopped because of a visitor. */
      bool needPreorderStop;

      /** \internal \brief The set of visitors we stop in the next clearStoppedVisitors call. */
      std::set<Visitor*> stoppeds;

      /** \internal \brief Determines whether special nodes will be visited or not. */
      bool visitSpecialNodes;

      /** \internal \brief Determines whether only used special nodes will be visited or all of them. */
      bool visitUsedSpecialNodesOnly;

      bool visitFilteredEdge;

      bool originalFilterState;

      const base::Base* apRoot;

      std::list<Visitor*> visitorList;

      Factory* fact;

      bool traversaldCrossEdges[116];

  }; // AlgorithmPreorder


}}}
#endif

