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

#ifndef _JAVA_REVERSEEDGES_H_
#define _JAVA_REVERSEEDGES_H_

#include "java/inc/java.h"

/**
* \file ReverseEdges.h
* \brief Contains declaration of ReverseEdges class.
*/

namespace columbus { namespace java { namespace asg {
  /**
  * \brief Collects the inverse relation of any "one way" defined edges.
  * The reverse relation tells for a given node the non trivial nodes
  * for which it has an incoming edge from.
  */
  class ReverseEdges {
    public:

      /** \internal \brief Type which will be use to select node types to revers edges. */
      typedef bool(*FuncPtrWithBaseParameterType)(const base::Base*);

    protected:

      /** \internal \brief The nodes of the same edges. */
      typedef ListIterator<base::Base>::Container NodeListType;

      /** \internal \brief Type which represent one node and its edges. */
      typedef std::map<EdgeKind, NodeListType> NodeEdgesType;

      /** \internal \brief Type which stores for all nodes their reversed edges. */
      typedef std::vector<NodeEdgesType*> RevEdgesContainer;

      /**
      * \internal
      * \brief Constructor.
      * \param factory [in] Revesred edges stored for this Factory.
      */
      ReverseEdges(const Factory* factory, FuncPtrWithBaseParameterType selectorFunction = NULL);

      /**
      * \internal
      * \brief Destructor.
      */
      ~ReverseEdges();

    private:

      /**
      * \internal
      * \brief Copy constructor.It not implemented it make linker error so it disable the copy of this object
      */
      ReverseEdges(const ReverseEdges&);

      /**
      * \internal
      * \brief It not implemented it make linker error so it disable the copy of this object.
      */
      ReverseEdges& operator=(ReverseEdges);

    public:

      /**
      * \brief Gives back a ListIterator for the given node with the given edge kind.
      * \param id            [in] The id of the node whose edges will be iterated.
      * \param edge          [in] The kind of the edge.
      * \throw JavaException Throws exception if there is node for the id or the edge kind is invalid for this node (it is not invalid if the node can have such edge but it has not got at that moment).
      * \return Returns with a iterator which iterates the node's reverse edges of the given kind.
      */
      const ListIterator<base::Base> constIteratorBegin(NodeId id, EdgeKind edge) const;

      /**
      * \brief Gives back a ListIterator for the given node with the given edge kind.
      * \param id            [in] The id of the node whose edges will be iterated.
      * \param edge          [in] The kind of the edge.
      * \throw JavaException Throws exception if there is node for the id or the edge kind is invalid for this node (it is not invalid if the node can have such edge but it has not got at that moment).
      * \return Returns with a iterator which iterates the node's reverse edges of the given kind.
      */
      const ListIterator<base::Base> constIteratorEnd(NodeId id, EdgeKind edge) const;

      /**
      * \brief Tells all kind of edges the node actually has.
      * \param id            [in] The id of the node whose edges we want to know.
      * \param edges         [out] A vector containing all kind of edges the node has (the vector is cleared before inserting new elements).
      * \throw JavaException Throws exception if the node does not exist.
      */
      void getAllExistingEdges(NodeId id, std::vector<EdgeKind>& edges) const;

      /**
      * \brief Tells all kind of edges the node actually has.
      * \param id            [in] The id of the node whose edges we want to know.
      * \param edges         [out] A set containing all kind of edges the node has (the vector is cleared before inserting new elements).
      * \throw JavaException Throws exception if the node does not exist.
      */
      void getAllExistingEdges(NodeId id, std::set<EdgeKind>& edges) const;

      /**
      * \brief Tells all kind of edges this kind of node can have.
      * \param kind          [in] The kind of the node whose edges we want to know.
      * \param edges         [out] A vector containing all kind of edges this kind of node can have (the vector is cleared before inserting new elements).
      * \throw JavaException Throws exception if the kind is invalid.
      */
      void getAllPossibleEdges(NodeKind kind, std::vector<EdgeKind>& edges) const;

      /**
      * \brief Tells all kind of edges this kind of node can have.
      * \param kind          [in] The kind of the node whose edges we want to know.
      * \param edges         [out] A set containing all kind of edges this kind of node can have (the vector is cleared before inserting new elements).
      * \throw JavaException Throws exception if the kind is invalid.
      */
      void getAllPossibleEdges(NodeKind kind, std::set<EdgeKind>& edges) const;

    private:

      /**
      * \internal
      * \brief Inserts a node (if the node has already been inserted nothing happens, otherwise the node is inserted without its edges).
      * \param id            [in] The id of the node which will be inserted.
      * \throw JavaException Throws Exception if the node does not exist.
      */
      void insertNode(NodeId id);

      /**
      * \internal
      * \brief Removes a node (with out without its edges?).
      * \param id            [in] The id of the node which will be removed.
      * \throw JavaException Throws JavaException if there is no node for the id.
      */
      void removeNode(NodeId id);

      /**
      * \internal
      * \brief Inserts an edge.
      * \param from          [in] The reversed edge starts from that node (originally it was the target of the edge).
      * \param to            [in] The target of the reversed edge (originally it was the start of the edge).
      * \param edge          [in] The kind of the edge.
      * \throw JavaException Throws JavaException if the from node is not valid.
      */
      void insertEdge(const base::Base* from, const base::Base* to, EdgeKind edge);

      /**
      * \internal
      * \brief Inserts an edge.
      * \param from          [in] The reversed edge starts from that node (originally it was the target of the edge).
      * \param to            [in] The target of the reversed edge (originally it was the start of the edge).
      * \param edge          [in] The kind of the edge.
      * \throw JavaException Throws JavaException if the from node is not valid.
      */
      void insertEdge(NodeId from, NodeId to, EdgeKind edge);

      /**
      * \internal
      * \brief Removes an edge.
      * \param from          [in] The reversed edge starts from that node (originally it was the target of the edge).
      * \param to            [in] The target of the reversed edge (originally it was the start of the edge).
      * \param edge          [in] The kind of the edge.
      * \throw JavaException todo.
      */
      void removeEdge(NodeId from, NodeId to, EdgeKind edge);

      /** \internal \brief Pointer to the Factory (the edges belong to it). */
      const Factory* fact;

      /** \internal \brief Pointer to selector function. */
      FuncPtrWithBaseParameterType selectorFunc;

      /** \internal \brief The Container (the edges are stored in it). */
      RevEdgesContainer reContainer;

      /** \internal \brief The possible edges by nodes. */
      static bool possibleEdges[141][105];

      friend class Factory;
      friend class VisitorReverseEdges;

      friend class base::Base;
      friend class base::BlockComment;
      friend class base::Comment;
      friend class base::Commentable;
      friend class base::JavadocComment;
      friend class base::LineComment;
      friend class base::Named;
      friend class base::NonJavadocComment;
      friend class base::Positioned;
      friend class base::PositionedWithoutComment;
      friend class expr::Annotation;
      friend class expr::ArrayAccess;
      friend class expr::ArrayTypeExpression;
      friend class expr::Assignment;
      friend class expr::Binary;
      friend class expr::BooleanLiteral;
      friend class expr::CharacterLiteral;
      friend class expr::ClassLiteral;
      friend class expr::Conditional;
      friend class expr::DoubleLiteral;
      friend class expr::Erroneous;
      friend class expr::ErroneousTypeExpression;
      friend class expr::Expression;
      friend class expr::ExternalTypeExpression;
      friend class expr::FieldAccess;
      friend class expr::FloatLiteral;
      friend class expr::Identifier;
      friend class expr::InfixExpression;
      friend class expr::InstanceOf;
      friend class expr::IntegerLiteral;
      friend class expr::Literal;
      friend class expr::LongLiteral;
      friend class expr::MarkerAnnotation;
      friend class expr::MethodInvocation;
      friend class expr::NewArray;
      friend class expr::NewClass;
      friend class expr::NormalAnnotation;
      friend class expr::NullLiteral;
      friend class expr::NumberLiteral;
      friend class expr::ParenthesizedExpression;
      friend class expr::PostfixExpression;
      friend class expr::PrefixExpression;
      friend class expr::PrimitiveTypeExpression;
      friend class expr::QualifiedTypeExpression;
      friend class expr::SimpleTypeExpression;
      friend class expr::SingleElementAnnotation;
      friend class expr::StringLiteral;
      friend class expr::Super;
      friend class expr::This;
      friend class expr::TypeApplyExpression;
      friend class expr::TypeCast;
      friend class expr::TypeExpression;
      friend class expr::TypeUnionExpression;
      friend class expr::Unary;
      friend class expr::WildcardExpression;
      friend class statm::Assert;
      friend class statm::BasicFor;
      friend class statm::Block;
      friend class statm::Break;
      friend class statm::Case;
      friend class statm::Continue;
      friend class statm::Default;
      friend class statm::Do;
      friend class statm::Empty;
      friend class statm::EnhancedFor;
      friend class statm::ExpressionStatement;
      friend class statm::For;
      friend class statm::Handler;
      friend class statm::If;
      friend class statm::Iteration;
      friend class statm::Jump;
      friend class statm::LabeledStatement;
      friend class statm::Return;
      friend class statm::Selection;
      friend class statm::Statement;
      friend class statm::Switch;
      friend class statm::SwitchLabel;
      friend class statm::Synchronized;
      friend class statm::Throw;
      friend class statm::Try;
      friend class statm::While;
      friend class struc::AnnotatedElement;
      friend class struc::AnnotationType;
      friend class struc::AnnotationTypeElement;
      friend class struc::AnonymousClass;
      friend class struc::Class;
      friend class struc::ClassDeclaration;
      friend class struc::ClassGeneric;
      friend class struc::CompilationUnit;
      friend class struc::Declaration;
      friend class struc::Enum;
      friend class struc::EnumConstant;
      friend class struc::GenericDeclaration;
      friend class struc::Import;
      friend class struc::InitializerBlock;
      friend class struc::InstanceInitializerBlock;
      friend class struc::Interface;
      friend class struc::InterfaceDeclaration;
      friend class struc::InterfaceGeneric;
      friend class struc::Member;
      friend class struc::Method;
      friend class struc::MethodDeclaration;
      friend class struc::MethodGeneric;
      friend class struc::NamedDeclaration;
      friend class struc::NormalMethod;
      friend class struc::Package;
      friend class struc::PackageDeclaration;
      friend class struc::Parameter;
      friend class struc::Scope;
      friend class struc::StaticInitializerBlock;
      friend class struc::TypeDeclaration;
      friend class struc::TypeParameter;
      friend class struc::Variable;
      friend class struc::VariableDeclaration;
      friend class type::ArrayType;
      friend class type::BooleanType;
      friend class type::BoundedWildcardType;
      friend class type::ByteType;
      friend class type::CharType;
      friend class type::ClassType;
      friend class type::DoubleType;
      friend class type::ErrorType;
      friend class type::FloatType;
      friend class type::IntType;
      friend class type::LongType;
      friend class type::LowerBoundedWildcardType;
      friend class type::MethodType;
      friend class type::NoType;
      friend class type::NullType;
      friend class type::PackageType;
      friend class type::ParameterizedType;
      friend class type::PrimitiveType;
      friend class type::ScopedType;
      friend class type::ShortType;
      friend class type::Type;
      friend class type::TypeVariable;
      friend class type::UnboundedWildcardType;
      friend class type::UnionType;
      friend class type::UpperBoundedWildcardType;
      friend class type::VoidType;
      friend class type::WildcardType;
  }; // ReverseEdges


}}}
#endif

