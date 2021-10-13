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

#ifndef _JAVA_ALGORITHMPREORDER_H_
#define _JAVA_ALGORITHMPREORDER_H_

#include "java/inc/java.h"

#include <set>

#include <list>

/**
* \file AlgorithmPreorder.h
* \brief Contains the class `AlgorithmPreorder' which implements the preorder traversal of the ASG.
* This is the visitor which when visit a node it call itself for all tree edges.
*/

namespace columbus { namespace java { namespace asg {
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
      virtual void visit(const base::BlockComment& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const base::JavadocComment& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const base::LineComment& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::AnnotatedTypeExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::ArrayAccess& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::ArrayTypeExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::Assignment& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::BooleanLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::CharacterLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::ClassLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::Conditional& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::DoubleLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::Erroneous& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::ErroneousTypeExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::ExternalTypeExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::FieldAccess& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::FloatLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::Identifier& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::InfixExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::InstanceOf& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::IntegerLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::Lambda& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::LongLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::MarkerAnnotation& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::MemberReference& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::MethodInvocation& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::NewArray& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::NewClass& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::NormalAnnotation& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::NullLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::ParenthesizedExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::PostfixExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::PrefixExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::PrimitiveTypeExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::QualifiedTypeExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::SimpleTypeExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::SingleElementAnnotation& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::StringLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::Super& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::This& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::TypeApplyExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::TypeCast& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::TypeIntersectionExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::TypeUnionExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expr::WildcardExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const module::Exports& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const module::Opens& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const module::Provides& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const module::Requires& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const module::Uses& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::Assert& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::BasicFor& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::Block& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::Break& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::Case& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::Continue& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::Default& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::Do& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::Empty& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::EnhancedFor& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::ExpressionStatement& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::Handler& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::If& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::LabeledStatement& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::Return& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::Switch& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::Synchronized& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::Throw& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::Try& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statm::While& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::AnnotationType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::AnnotationTypeElement& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::AnonymousClass& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::Class& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::ClassGeneric& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::CompilationUnit& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::Enum& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::EnumConstant& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::Import& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::InstanceInitializerBlock& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::Interface& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::InterfaceGeneric& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::Method& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::MethodGeneric& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::Module& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::ModuleDeclaration& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::Package& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::PackageDeclaration& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::Parameter& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::StaticInitializerBlock& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::TypeParameter& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const struc::Variable& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::ArrayType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::BooleanType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::ByteType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::CharType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::ClassType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::DoubleType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::ErrorType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::FloatType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::IntType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::IntersectionType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::LongType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::LowerBoundedWildcardType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::MethodType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::ModuleType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::NoType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::NullType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::PackageType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::ParameterizedType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::ShortType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::TypeVariable& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::UnboundedWildcardType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::UnionType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::UpperBoundedWildcardType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const type::VoidType& node , bool callVirtualBase = true);

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
      virtual void visitAllEdges(const base::BlockComment& node , bool callVirtualBase = true);

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
      virtual void visitAllEdges(const base::Commentable& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const base::JavadocComment& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const base::LineComment& node , bool callVirtualBase = true);

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
      virtual void visitAllEdges(const base::NonJavadocComment& node , bool callVirtualBase = true);

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
      virtual void visitAllEdges(const base::PositionedWithoutComment& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::AnnotatedTypeExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::Annotation& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::ArrayAccess& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::ArrayTypeExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::Assignment& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::Binary& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::BooleanLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::CharacterLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::ClassLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::Conditional& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::DoubleLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::Erroneous& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::ErroneousTypeExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::Expression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::ExternalTypeExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::FieldAccess& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::FloatLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::FunctionalExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::Identifier& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::InfixExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::InstanceOf& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::IntegerLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::Lambda& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::Literal& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::LongLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::MarkerAnnotation& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::MemberReference& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::MethodInvocation& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::NewArray& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::NewClass& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::NormalAnnotation& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::NullLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::NumberLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::ParenthesizedExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::PolyExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::PostfixExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::PrefixExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::PrimitiveTypeExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::QualifiedTypeExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::SimpleTypeExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::SingleElementAnnotation& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::StringLiteral& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::Super& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::This& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::TypeApplyExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::TypeCast& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::TypeExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::TypeIntersectionExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::TypeUnionExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::Unary& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expr::WildcardExpression& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const module::Exports& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const module::ModuleDirective& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const module::Opens& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const module::Provides& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const module::Requires& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const module::Uses& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::Assert& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::BasicFor& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::Block& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::Break& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::Case& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::Continue& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::Default& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::Do& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::Empty& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::EnhancedFor& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::ExpressionStatement& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::For& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::Handler& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::If& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::Iteration& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::Jump& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::LabeledStatement& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::Return& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::Selection& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::Statement& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::Switch& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::SwitchLabel& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::Synchronized& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::Throw& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::Try& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statm::While& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::AnnotatedElement& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::AnnotationType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::AnnotationTypeElement& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::AnonymousClass& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::Class& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::ClassDeclaration& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::ClassGeneric& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::CompilationUnit& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::Declaration& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::Enum& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::EnumConstant& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::GenericDeclaration& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::Import& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::InitializerBlock& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::InstanceInitializerBlock& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::Interface& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::InterfaceDeclaration& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::InterfaceGeneric& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::Member& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::Method& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::MethodDeclaration& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::MethodGeneric& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::Module& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::ModuleDeclaration& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::NamedDeclaration& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::NormalMethod& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::Package& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::PackageDeclaration& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::Parameter& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::Scope& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::StaticInitializerBlock& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::TypeDeclaration& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::TypeParameter& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::Variable& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const struc::VariableDeclaration& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::ArrayType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::BooleanType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::BoundedWildcardType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::ByteType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::CharType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::ClassType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::DoubleType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::ErrorType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::FloatType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::IntType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::IntersectionType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::LongType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::LowerBoundedWildcardType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::MethodType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::ModuleType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::NoType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::NullType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::PackageType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::ParameterizedType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::PrimitiveType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::ScopedType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::ShortType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::Type& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::TypeVariable& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::UnboundedWildcardType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::UnionType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::UpperBoundedWildcardType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::VoidType& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const type::WildcardType& node , bool callVirtualBase = true);

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

      bool traversaldCrossEdges[133];

  }; // AlgorithmPreorder


}}}
#endif

