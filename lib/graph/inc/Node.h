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

#ifndef _GRAPHNODE_H
#define _GRAPHNODE_H

#include  <list>

/**
* \file Node.h
* \brief Contains node,nodeType,nodeIterator declaration for the graph lib
*/

namespace columbus {  namespace graph {

  /**
  * \brief Class for node in graph
  */
  class Node {
    
    public:

      /** 
      * \brief node type
      */
      class NodeType {
        protected:
          /** \internal \brief type name */
          std::string _type;
        public:

          /**
          * \brief constructor
          * \param type [in] name of the type
          */
          NodeType(const std::string& type);

          /**
          * \brief copy constructor
          * \param NTYPE [in] node type
          */
          NodeType(const NodeType& NTYPE);
          
          /**
          * \brief gives back node type name
          * \return name of type
          */
          const std::string& getType() const;

          /**
          * \brief operator =
          * \param NTYPE [in]node type
          */
          NodeType& operator=(const NodeType& NTYPE);

          /**
          * \brief operator ==
          * \return true if node type name is equals
          */
          bool operator==(const NodeType &nodeType) const;

          /**
          * \brief operator !=
          * \return true if node type name is not equals
          */
          bool operator!=(const NodeType &nodeType) const;

          /**
          * \brief operator <
          * \param nodeType [in] the other edge
          * \return true, if the node 'type' is lower then 'nodeType' 'type'
          */
          bool operator<(const NodeType& nodeType) const;

      };

      /* \internal \brief set of nodeTypes */
      typedef std::set<NodeType> NodeTypeSet;
      /* \internal \brief set of nodes */
      typedef std::set<Node> NodeSet;

      /**
      * \brief Iterator class for nodes
      */
      class NodeIterator {

        protected:


          /** \internal \brief Type definition to store iterators in a container. */
          typedef std::list<NodeIterator*> IteratorContainer;

        protected:

          /**
          * \internal
          * \brief The possible states of an iterator.
          */
          enum op {
            /** \internal \brief None of the add(), remove(), next() or previous() was called. */
            op_None,

            /** \internal \brief The last call was an add(). */
            op_Add,

            /** \internal \brief The last call was a remove(). */
            op_Remove,

            /** \internal \brief The last call was a previous(). */
            op_Next,

            /** \internal \brief The last call was a previous(). */
            op_Previous,

            /** \internal \brief The node containing the container of the iterator is deleted. */
            op_Invalidated

          };

          /**
          * \internal
          * \brief Non-public constructor, which creates a usable new iterator.
          * \param container_begin [in] The begin of container which stores the ids of the edges the iteration is going on it.
          * \param container_end   [in] The end of container which stores the ids of the edges the iteration is going on it.
          * \param itContainer     [in] The container which stores other iterators applied for the same container.
          * \param factory         [in] The Factory.
          * \param NTYPE           [in] If it is empty, we use all nodes, else we use only filteredEdegs nodes
          */
          NodeIterator(vertex_iter container_begin,vertex_iter container_end, IteratorContainer *itContainer, Graph* graph,const NodeTypeSet& NTYPE);

          /**
          * \internal
          * \brief Insert the specified element into the list.
          * \param node  [in] The element.
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          *
          * The element is inserted immediately before the next element that would be returned by next(), if any,
          * and after the next element that would be returned by previous(), if any. (If the list contains no elements,
          * the new element becomes the sole element on the list.) The new element is inserted before the implicit cursor:
          * a subsequent call to next() would be unaffected, and a subsequent call to previous() would return the new element.
          */
          void add(const Node& node);

          /**
          * \internal
          * \brief Removes from the list the last element that was returned by next() or previous().
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          * \throw GraphInvalidIteratorException    Neither next() nor previous() have been called, or remove() or add() have been called after the last call to next() or previous().
          *
          * This call can only be made once per call to next() or previous(). It can be made
          * only if add() has not been called after the last call to next() or previous().
          */
          void remove();

        public:

          /**
          * \brief Creates an invalid NodeIterator (this can be used only to create an iterator but cannot be used until giving value to it).
          */
          NodeIterator();

          /**
          * \brief Creates an NodeIterator by copying the one given in parameter.
          * \param iterator [in] The other NodeIterator which initializes this one.
          */
          NodeIterator(const NodeIterator &iterator);

          /**
          * \brief Detructor which safely destroys the NodeIterator.
          */
          virtual ~NodeIterator();

          /**
          * \brief Copies a NodeIterator.
          * \param otherIt                     [in] The other NodeIterator which initializes this one.
          * \throw GraphInvalidIteratorException If the other iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns a reference to a NodeIterator.
          */
          NodeIterator& operator=(const NodeIterator& otherIt);

          /**
          * \brief Returns true if this iterator has more elements when traversing the list in the forward direction.
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns true if the iterator has more elements when traversing the list in the forward direction.
          *
          * In other words, returns true if next() would return an element rather than throwing an exception.
          */
          virtual bool hasNext();

          /**
          * \brief Returns the next element in the list.
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns the next element in the list.
          *
          * This method may be called repeatedly to iterate through the list, or intermixed with calls to previous() to go back and forth.
          * (Note that alternating calls to next() and previous() will return the same element repeatedly.)
          */
          virtual Node next();

          /**
          * \brief Returns true if this list iterator has more elements when traversing the list in the reverse direction. 
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns true if the list iterator has more elements when traversing the list in the reverse direction.
          *
          * In other words, returns true if previous() would return an element rather than throwing an exception.
          */
          virtual bool hasPrevious();

          /**
          * \brief Returns the previous element in the list.
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns the previous element in the list.
          *
          * This method may be called repeatedly to iterate through the list backwards, or intermixed with calls to next() to go back and forth.
          * (Note that alternating calls to next() and previous() will return the same element repeatedly.)
          */
          virtual Node previous();

          /**
          * \brief Compares the two iterators.
          * \param otherIt                     [in] The iterator is compared to it.
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns true if the two iterators would give back the same elements with the next previous() and next() calls.
          */
          virtual bool equals(const NodeIterator& otherIt) const;

          virtual int hashCode() const;

        protected:
          /**
          * \internal
          * \brief Searches for the next non-deleted, filtered element. / if filter is not set find next element
          * \param inc [in] If inc is true, the iterator steps before searching.
          * \param it  [in] The iterator whose next element is searched.
          * \return Returns the next non-deleted element (or the end of the container if there is no next element).
          */
          vertex_iter findNextNotFiltered(bool inc, const vertex_iter& it);

          /**
          * \internal
          * \brief Gives back the next element.
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns the next element (or the end of the container if there is no next element).
          */
          vertex_iter nextItem();

          /**
          * \internal
          * \brief Searches for the previous not deleted,filtered element / if filter is not set find previous element
          * \param dec [in] If dec is true, the iterator steps before searching.
          * \param it  [in] The iterator whose previous element is searched.
          * \return Returns the previous not deleted element (or the end of the container if there is no previous element).
          */
          vertex_iter findPreviousNotDeletedFiltered(bool dec, const vertex_iter& it);

          /**
          * \internal
          * \brief Gives back the previous element.
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns the previous element (or the end of the container if there is no previous element).
          */
          vertex_iter previousItem();

          /**
          * \internal
          * \brief Safely removes an element element.
          * \param it [in] The iterator which will be removed.
          * \return todo.
          */
          vertex_iter safeRemove(const vertex_iter& it);

          /**
          * \internal
          * \brief Invalidates the iterator (sets its state to op_Invalidated).
          */
          void invalidate();

        protected:

          /** \internal \brief Pointer to the Factory. */
          Graph* graph;

          /** \internal \brief Pointer to the Container the ids stored in. */
          vertex_iter container_begin;
          vertex_iter container_end;

          /** \internal \brief Pointer to the list of the iterators of the Container. */
          IteratorContainer* iterators;

          /** \internal \brief Filtered nodes */
          NodeTypeSet filteredNodes;

          /** \internal \brief Inner iterator of the Container. */
          vertex_iter it;

          /** \internal \brief State of the iterator (the last operation done on the iterator). */
          op lastOp;


        friend class Graph;
      };

    public:

      /**
      * \brief constructor for invalidNode
      */
      Node();

      /**
      * \brief copy constructor
      * \param node [in] the node
      */
      Node(const Node& node);

      /**
      * \brief destructor
      */
      ~Node();
      
      Attribute& addAttribute(const Attribute& attribute); // O(a)
      bool deleteAttribute(const Attribute& attribute); // O(a)
      bool deleteAttribute(Attribute::aType type, const std::string& name); // O(a)
      bool deleteAttribute(Attribute::aType type, const std::string& name, const std::string& context);
      bool deleteAttribute(Attribute::aType type); // O(a)
      bool deleteAttribute(const std::string& context);
      void deleteAttributes();

      Attribute::AttributeIterator getAttributes() const; // O(1)
      Attribute::AttributeIterator findAttribute(Attribute::aType type, const std::string& name, const std::string& context) const; // O(a)

      /**
      * \brief gives back attribute iterator to 'type' type of attributes, if attribute doesn't exist, the result iterator is empty(hasNext function alwasy return false)
      * \param type [in] the attribute type
      * \return iterator to 'type' type of attributes
      */
      Attribute::AttributeIterator findAttributeByType(Attribute::aType type) const;

      /**
      * \brief gives back attribute iterator to 'name' name of attributes, if attribute doesn't exist, the result iterator is empty(hasNext function alwasy return false) 
      * \param name [in] the name of attribute
      * \return iterator to 'name' name of attributes
      */
      Attribute::AttributeIterator findAttributeByName(const std::string& name) const;

      /**
      * \brief gives back attribute iterator to 'context' context of attributes, if attribute doesn't exist, the result iterator is empty(hasNext function alwasy return false) 
      * \param context [in] the context of attribute
      * \return iterator to 'context' context of attributes
      */
      Attribute::AttributeIterator findAttributeByContext(const std::string& context) const;

      Edge::EdgeIterator getOutEdges() const; // O(1)
      Edge::EdgeIterator findOutEdges(const Edge::EdgeType& type) const;  // O(e)
      Edge::EdgeIterator findOutEdges(const Edge::EdgeTypeSet& type) const;

      NodeType getType() const; // O(1)
      const std::string& getUID() const; // O(1)
      void setUID(const std::string& UID);
      bool equals(const Node& node) const; // O(1)

      int hashCode() const;

      bool operator==(const Node& node) const;
      bool operator!=(const Node& node) const;
      bool operator<(const Node& node) const;
      Node& operator=(const Node& node);

      /**
      * \brief set node type
      * \param type [in] the node type
      */
      void setType(const NodeType& type);

    protected:

      Node(Graph* g, GraphVertex vertex);

    protected:

      Graph *g;
      GraphVertex vertex;

    friend class Graph;
    friend class Edge;
    friend class NodeIterator;
    friend class GraphXmlHandler;
    friend class JNIRegistry;
    friend GraphVertex getNodeVertex(const Node&);
    friend Graph* getNodeGraph(const Node&);
    friend Node createNode(Graph* , GraphVertex);

  };

}}

#endif
