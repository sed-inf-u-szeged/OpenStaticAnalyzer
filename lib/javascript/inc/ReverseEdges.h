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

#ifndef _JAVASCRIPT_REVERSEEDGES_H_
#define _JAVASCRIPT_REVERSEEDGES_H_

#include "javascript/inc/javascript.h"

/**
* \file ReverseEdges.h
* \brief Contains declaration of ReverseEdges class.
*/

namespace columbus { namespace javascript { namespace asg {
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
      * \param id                  [in] The id of the node whose edges will be iterated.
      * \param edge                [in] The kind of the edge.
      * \throw JavaScriptException Throws exception if there is node for the id or the edge kind is invalid for this node (it is not invalid if the node can have such edge but it has not got at that moment).
      * \return Returns with a iterator which iterates the node's reverse edges of the given kind.
      */
      const ListIterator<base::Base> constIteratorBegin(NodeId id, EdgeKind edge) const;

      /**
      * \brief Gives back a ListIterator for the given node with the given edge kind.
      * \param id                  [in] The id of the node whose edges will be iterated.
      * \param edge                [in] The kind of the edge.
      * \throw JavaScriptException Throws exception if there is node for the id or the edge kind is invalid for this node (it is not invalid if the node can have such edge but it has not got at that moment).
      * \return Returns with a iterator which iterates the node's reverse edges of the given kind.
      */
      const ListIterator<base::Base> constIteratorEnd(NodeId id, EdgeKind edge) const;

      /**
      * \brief Tells all kind of edges the node actually has.
      * \param id                  [in] The id of the node whose edges we want to know.
      * \param edges               [out] A vector containing all kind of edges the node has (the vector is cleared before inserting new elements).
      * \throw JavaScriptException Throws exception if the node does not exist.
      */
      void getAllExistingEdges(NodeId id, std::vector<EdgeKind>& edges) const;

      /**
      * \brief Tells all kind of edges the node actually has.
      * \param id                  [in] The id of the node whose edges we want to know.
      * \param edges               [out] A set containing all kind of edges the node has (the vector is cleared before inserting new elements).
      * \throw JavaScriptException Throws exception if the node does not exist.
      */
      void getAllExistingEdges(NodeId id, std::set<EdgeKind>& edges) const;

      /**
      * \brief Tells all kind of edges this kind of node can have.
      * \param kind                [in] The kind of the node whose edges we want to know.
      * \param edges               [out] A vector containing all kind of edges this kind of node can have (the vector is cleared before inserting new elements).
      * \throw JavaScriptException Throws exception if the kind is invalid.
      */
      void getAllPossibleEdges(NodeKind kind, std::vector<EdgeKind>& edges) const;

      /**
      * \brief Tells all kind of edges this kind of node can have.
      * \param kind                [in] The kind of the node whose edges we want to know.
      * \param edges               [out] A set containing all kind of edges this kind of node can have (the vector is cleared before inserting new elements).
      * \throw JavaScriptException Throws exception if the kind is invalid.
      */
      void getAllPossibleEdges(NodeKind kind, std::set<EdgeKind>& edges) const;

    private:

      /**
      * \internal
      * \brief Inserts a node (if the node has already been inserted nothing happens, otherwise the node is inserted without its edges).
      * \param id                  [in] The id of the node which will be inserted.
      * \throw JavaScriptException Throws Exception if the node does not exist.
      */
      void insertNode(NodeId id);

      /**
      * \internal
      * \brief Removes a node (with out without its edges?).
      * \param id                  [in] The id of the node which will be removed.
      * \throw JavaScriptException Throws JavaScriptException if there is no node for the id.
      */
      void removeNode(NodeId id);

      /**
      * \internal
      * \brief Inserts an edge.
      * \param from                [in] The reversed edge starts from that node (originally it was the target of the edge).
      * \param to                  [in] The target of the reversed edge (originally it was the start of the edge).
      * \param edge                [in] The kind of the edge.
      * \throw JavaScriptException Throws JavaScriptException if the from node is not valid.
      */
      void insertEdge(const base::Base* from, const base::Base* to, EdgeKind edge);

      /**
      * \internal
      * \brief Inserts an edge.
      * \param from                [in] The reversed edge starts from that node (originally it was the target of the edge).
      * \param to                  [in] The target of the reversed edge (originally it was the start of the edge).
      * \param edge                [in] The kind of the edge.
      * \throw JavaScriptException Throws JavaScriptException if the from node is not valid.
      */
      void insertEdge(NodeId from, NodeId to, EdgeKind edge);

      /**
      * \internal
      * \brief Removes an edge.
      * \param from                [in] The reversed edge starts from that node (originally it was the target of the edge).
      * \param to                  [in] The target of the reversed edge (originally it was the start of the edge).
      * \param edge                [in] The kind of the edge.
      * \throw JavaScriptException todo.
      */
      void removeEdge(NodeId from, NodeId to, EdgeKind edge);

      /** \internal \brief Pointer to the Factory (the edges belong to it). */
      const Factory* fact;

      /** \internal \brief Pointer to selector function. */
      FuncPtrWithBaseParameterType selectorFunc;

      /** \internal \brief The Container (the edges are stored in it). */
      RevEdgesContainer reContainer;

      /** \internal \brief The possible edges by nodes. */
      static bool possibleEdges[86][93];

      friend class Factory;
      friend class VisitorReverseEdges;

      friend class base::Base;
      friend class base::Comment;
      friend class base::Named;
      friend class base::Positioned;
      friend class base::Program;
      friend class base::System;
      friend class declaration::ClassDeclaration;
      friend class declaration::Declaration;
      friend class declaration::ExportAllDeclaration;
      friend class declaration::ExportDefaultDeclaration;
      friend class declaration::ExportNamedDeclaration;
      friend class declaration::FunctionDeclaration;
      friend class declaration::ImportDeclaration;
      friend class declaration::ModuleDeclaration;
      friend class declaration::VariableDeclaration;
      friend class declaration::VariableDeclarator;
      friend class expression::ArrayExpression;
      friend class expression::ArrowFunctionExpression;
      friend class expression::AssignmentExpression;
      friend class expression::AssignmentProperty;
      friend class expression::AwaitExpression;
      friend class expression::BinaryExpression;
      friend class expression::BooleanLiteral;
      friend class expression::CallExpression;
      friend class expression::ClassExpression;
      friend class expression::ConditionalExpression;
      friend class expression::Expression;
      friend class expression::FunctionExpression;
      friend class expression::Identifier;
      friend class expression::Literal;
      friend class expression::LogicalExpression;
      friend class expression::MemberExpression;
      friend class expression::MetaProperty;
      friend class expression::NewExpression;
      friend class expression::NullLiteral;
      friend class expression::NumberLiteral;
      friend class expression::ObjectExpression;
      friend class expression::Property;
      friend class expression::RegExpLiteral;
      friend class expression::SequenceExpression;
      friend class expression::SpreadElement;
      friend class expression::StringLiteral;
      friend class expression::Super;
      friend class expression::TaggedTemplateExpression;
      friend class expression::TemplateElement;
      friend class expression::TemplateLiteral;
      friend class expression::ThisExpression;
      friend class expression::UnaryExpression;
      friend class expression::UpdateExpression;
      friend class expression::YieldExpression;
      friend class statement::ArrayPattern;
      friend class statement::AssignmentPattern;
      friend class statement::BlockStatement;
      friend class statement::BreakStatement;
      friend class statement::CatchClause;
      friend class statement::ContinueStatement;
      friend class statement::DebuggerStatement;
      friend class statement::DoWhileStatement;
      friend class statement::EmptyStatement;
      friend class statement::ExpressionStatement;
      friend class statement::ForInStatement;
      friend class statement::ForOfStatement;
      friend class statement::ForStatement;
      friend class statement::Function;
      friend class statement::IfStatement;
      friend class statement::LabeledStatement;
      friend class statement::ObjectPattern;
      friend class statement::Pattern;
      friend class statement::RestElement;
      friend class statement::ReturnStatement;
      friend class statement::Statement;
      friend class statement::SwitchCase;
      friend class statement::SwitchStatement;
      friend class statement::ThrowStatement;
      friend class statement::TryStatement;
      friend class statement::WhileStatement;
      friend class statement::WithStatement;
      friend class structure::Class;
      friend class structure::ClassBody;
      friend class structure::ExportSpecifier;
      friend class structure::ImpSpecifier;
      friend class structure::ImportDefaultSpecifier;
      friend class structure::ImportNamespaceSpecifier;
      friend class structure::ImportSpecifier;
      friend class structure::MethodDefinition;
      friend class structure::ModuleSpecifier;
  }; // ReverseEdges


}}}
#endif

