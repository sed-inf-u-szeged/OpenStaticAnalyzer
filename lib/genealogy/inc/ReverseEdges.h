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

#ifndef _GENEALOGY_REVERSEEDGES_H_
#define _GENEALOGY_REVERSEEDGES_H_

#include "genealogy/inc/genealogy.h"

/**
* \file ReverseEdges.h
* \brief Contains declaration of ReverseEdges class.
*/

namespace columbus { namespace genealogy { 
  /**
  * \brief Collects the inverse relation of any "one way" defined edges.
  * The reverse relation tells for a given node the non trivial nodes
  * for which it has an incoming edge from.
  */
  class ReverseEdges {
    public:

      /** \internal \brief Type which will be use to select node types to revers edges. */
      typedef bool(*FuncPtrWithBaseParameterType)(const Base*);

    protected:

      /** \internal \brief The nodes of the same edges. */
      typedef ListIterator<Base>::Container NodeListType;

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
      * \param id                 [in] The id of the node whose edges will be iterated.
      * \param edge               [in] The kind of the edge.
      * \throw GenealogyException Throws exception if there is node for the id or the edge kind is invalid for this node (it is not invalid if the node can have such edge but it has not got at that moment).
      * \return Returns with a iterator which iterates the node's reverse edges of the given kind.
      */
      const ListIterator<Base> constIteratorBegin(NodeId id, EdgeKind edge) const;

      /**
      * \brief Gives back a ListIterator for the given node with the given edge kind.
      * \param id                 [in] The id of the node whose edges will be iterated.
      * \param edge               [in] The kind of the edge.
      * \throw GenealogyException Throws exception if there is node for the id or the edge kind is invalid for this node (it is not invalid if the node can have such edge but it has not got at that moment).
      * \return Returns with a iterator which iterates the node's reverse edges of the given kind.
      */
      const ListIterator<Base> constIteratorEnd(NodeId id, EdgeKind edge) const;

      /**
      * \brief Tells all kind of edges the node actually has.
      * \param id                 [in] The id of the node whose edges we want to know.
      * \param edges              [out] A vector containing all kind of edges the node has (the vector is cleared before inserting new elements).
      * \throw GenealogyException Throws exception if the node does not exist.
      */
      void getAllExistingEdges(NodeId id, std::vector<EdgeKind>& edges) const;

      /**
      * \brief Tells all kind of edges the node actually has.
      * \param id                 [in] The id of the node whose edges we want to know.
      * \param edges              [out] A set containing all kind of edges the node has (the vector is cleared before inserting new elements).
      * \throw GenealogyException Throws exception if the node does not exist.
      */
      void getAllExistingEdges(NodeId id, std::set<EdgeKind>& edges) const;

      /**
      * \brief Tells all kind of edges this kind of node can have.
      * \param kind               [in] The kind of the node whose edges we want to know.
      * \param edges              [out] A vector containing all kind of edges this kind of node can have (the vector is cleared before inserting new elements).
      * \throw GenealogyException Throws exception if the kind is invalid.
      */
      void getAllPossibleEdges(NodeKind kind, std::vector<EdgeKind>& edges) const;

      /**
      * \brief Tells all kind of edges this kind of node can have.
      * \param kind               [in] The kind of the node whose edges we want to know.
      * \param edges              [out] A set containing all kind of edges this kind of node can have (the vector is cleared before inserting new elements).
      * \throw GenealogyException Throws exception if the kind is invalid.
      */
      void getAllPossibleEdges(NodeKind kind, std::set<EdgeKind>& edges) const;

    private:

      /**
      * \internal
      * \brief Inserts a node (if the node has already been inserted nothing happens, otherwise the node is inserted without its edges).
      * \param id                 [in] The id of the node which will be inserted.
      * \throw GenealogyException Throws Exception if the node does not exist.
      */
      void insertNode(NodeId id);

      /**
      * \internal
      * \brief Removes a node (with out without its edges?).
      * \param id                 [in] The id of the node which will be removed.
      * \throw GenealogyException Throws GenealogyException if there is no node for the id.
      */
      void removeNode(NodeId id);

      /**
      * \internal
      * \brief Inserts an edge.
      * \param from               [in] The reversed edge starts from that node (originally it was the target of the edge).
      * \param to                 [in] The target of the reversed edge (originally it was the start of the edge).
      * \param edge               [in] The kind of the edge.
      * \throw GenealogyException Throws GenealogyException if the from node is not valid.
      */
      void insertEdge(const Base* from, const Base* to, EdgeKind edge);

      /**
      * \internal
      * \brief Inserts an edge.
      * \param from               [in] The reversed edge starts from that node (originally it was the target of the edge).
      * \param to                 [in] The target of the reversed edge (originally it was the start of the edge).
      * \param edge               [in] The kind of the edge.
      * \throw GenealogyException Throws GenealogyException if the from node is not valid.
      */
      void insertEdge(NodeId from, NodeId to, EdgeKind edge);

      /**
      * \internal
      * \brief Removes an edge.
      * \param from               [in] The reversed edge starts from that node (originally it was the target of the edge).
      * \param to                 [in] The target of the reversed edge (originally it was the start of the edge).
      * \param edge               [in] The kind of the edge.
      * \throw GenealogyException todo.
      */
      void removeEdge(NodeId from, NodeId to, EdgeKind edge);

      /** \internal \brief Pointer to the Factory (the edges belong to it). */
      const Factory* fact;

      /** \internal \brief Pointer to selector function. */
      FuncPtrWithBaseParameterType selectorFunc;

      /** \internal \brief The Container (the edges are stored in it). */
      RevEdgesContainer reContainer;

      /** \internal \brief The possible edges by nodes. */
      static bool possibleEdges[16][22];

      friend class Factory;
      friend class VisitorReverseEdges;

      friend class Base;
      friend class Project;
      friend class Trackable;
      friend class Component;
      friend class SourceCodeElement;
      friend class System;
      friend class Clone;
      friend class StructuralClone;
      friend class CloneClass;
      friend class CloneInstance;
      friend class DataClumpsClass;
      friend class DataClumps;
      friend class DataElement;
      friend class SwitchStatementClass;
      friend class SwitchStatement;
      friend class CaseLabel;
  }; // ReverseEdges


}}
#endif

