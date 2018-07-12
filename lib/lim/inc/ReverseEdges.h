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

#ifndef _LIM_REVERSEEDGES_H_
#define _LIM_REVERSEEDGES_H_

#include "lim/inc/lim.h"

/**
* \file ReverseEdges.h
* \brief Contains declaration of ReverseEdges class.
*/

namespace columbus { namespace lim { namespace asg {
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
      * \param id           [in] The id of the node whose edges will be iterated.
      * \param edge         [in] The kind of the edge.
      * \throw LimException Throws exception if there is node for the id or the edge kind is invalid for this node (it is not invalid if the node can have such edge but it has not got at that moment).
      * \return Returns with a iterator which iterates the node's reverse edges of the given kind.
      */
      const ListIterator<base::Base> constIteratorBegin(NodeId id, EdgeKind edge) const;

      /**
      * \brief Gives back a ListIterator for the given node with the given edge kind.
      * \param id           [in] The id of the node whose edges will be iterated.
      * \param edge         [in] The kind of the edge.
      * \throw LimException Throws exception if there is node for the id or the edge kind is invalid for this node (it is not invalid if the node can have such edge but it has not got at that moment).
      * \return Returns with a iterator which iterates the node's reverse edges of the given kind.
      */
      const ListIterator<base::Base> constIteratorEnd(NodeId id, EdgeKind edge) const;

      /**
      * \brief Tells all kind of edges the node actually has.
      * \param id           [in] The id of the node whose edges we want to know.
      * \param edges        [out] A vector containing all kind of edges the node has (the vector is cleared before inserting new elements).
      * \throw LimException Throws exception if the node does not exist.
      */
      void getAllExistingEdges(NodeId id, std::vector<EdgeKind>& edges) const;

      /**
      * \brief Tells all kind of edges the node actually has.
      * \param id           [in] The id of the node whose edges we want to know.
      * \param edges        [out] A set containing all kind of edges the node has (the vector is cleared before inserting new elements).
      * \throw LimException Throws exception if the node does not exist.
      */
      void getAllExistingEdges(NodeId id, std::set<EdgeKind>& edges) const;

      /**
      * \brief Tells all kind of edges this kind of node can have.
      * \param kind         [in] The kind of the node whose edges we want to know.
      * \param edges        [out] A vector containing all kind of edges this kind of node can have (the vector is cleared before inserting new elements).
      * \throw LimException Throws exception if the kind is invalid.
      */
      void getAllPossibleEdges(NodeKind kind, std::vector<EdgeKind>& edges) const;

      /**
      * \brief Tells all kind of edges this kind of node can have.
      * \param kind         [in] The kind of the node whose edges we want to know.
      * \param edges        [out] A set containing all kind of edges this kind of node can have (the vector is cleared before inserting new elements).
      * \throw LimException Throws exception if the kind is invalid.
      */
      void getAllPossibleEdges(NodeKind kind, std::set<EdgeKind>& edges) const;

    private:

      /**
      * \internal
      * \brief Inserts a node (if the node has already been inserted nothing happens, otherwise the node is inserted without its edges).
      * \param id           [in] The id of the node which will be inserted.
      * \throw LimException Throws Exception if the node does not exist.
      */
      void insertNode(NodeId id);

      /**
      * \internal
      * \brief Removes a node (with out without its edges?).
      * \param id           [in] The id of the node which will be removed.
      * \throw LimException Throws LimException if there is no node for the id.
      */
      void removeNode(NodeId id);

      /**
      * \internal
      * \brief Inserts an edge.
      * \param from         [in] The reversed edge starts from that node (originally it was the target of the edge).
      * \param to           [in] The target of the reversed edge (originally it was the start of the edge).
      * \param edge         [in] The kind of the edge.
      * \throw LimException Throws LimException if the from node is not valid.
      */
      void insertEdge(const base::Base* from, const base::Base* to, EdgeKind edge);

      /**
      * \internal
      * \brief Inserts an edge.
      * \param from         [in] The reversed edge starts from that node (originally it was the target of the edge).
      * \param to           [in] The target of the reversed edge (originally it was the start of the edge).
      * \param edge         [in] The kind of the edge.
      * \throw LimException Throws LimException if the from node is not valid.
      */
      void insertEdge(NodeId from, NodeId to, EdgeKind edge);

      /**
      * \internal
      * \brief Removes an edge.
      * \param from         [in] The reversed edge starts from that node (originally it was the target of the edge).
      * \param to           [in] The target of the reversed edge (originally it was the start of the edge).
      * \param edge         [in] The kind of the edge.
      * \throw LimException todo.
      */
      void removeEdge(NodeId from, NodeId to, EdgeKind edge);

      /** \internal \brief Pointer to the Factory (the edges belong to it). */
      const Factory* fact;

      /** \internal \brief Pointer to selector function. */
      FuncPtrWithBaseParameterType selectorFunc;

      /** \internal \brief The Container (the edges are stored in it). */
      RevEdgesContainer reContainer;

      /** \internal \brief The possible edges by nodes. */
      static bool possibleEdges[34][49];

      friend class Factory;
      friend class VisitorReverseEdges;

      friend class base::Base;
      friend class base::Comment;
      friend class base::Component;
      friend class base::ControlFlowBlock;
      friend class base::Named;
      friend class logical::Attribute;
      friend class logical::AttributeAccess;
      friend class logical::Class;
      friend class logical::ClassGeneric;
      friend class logical::ClassGenericInstance;
      friend class logical::ClassGenericSpec;
      friend class logical::Friendship;
      friend class logical::GenericParameter;
      friend class logical::Member;
      friend class logical::Method;
      friend class logical::MethodCall;
      friend class logical::MethodGeneric;
      friend class logical::MethodGenericInstance;
      friend class logical::MethodGenericSpec;
      friend class logical::Package;
      friend class logical::Parameter;
      friend class logical::Scope;
      friend class physical::FSEntry;
      friend class physical::File;
      friend class physical::FileSystem;
      friend class physical::Folder;
      friend class type::SimpleType;
      friend class type::Type;
      friend class type::TypeFormer;
      friend class type::TypeFormerArray;
      friend class type::TypeFormerMethod;
      friend class type::TypeFormerNonType;
      friend class type::TypeFormerPointer;
      friend class type::TypeFormerType;
  }; // ReverseEdges


}}}
#endif

