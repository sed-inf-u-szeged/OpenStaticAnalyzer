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

#ifndef _GRAPHEDGE_H
#define _GRAPHEDGE_H

#include  <list>


/**
* \file Edge.h
* \brief Contains edge,edgeType,edgeIterator declaration for the graph lib
*/


namespace columbus {  namespace graph {

  class Node;

  /**
  * \brief Class represent an edge in the grapg
  */
  class Edge {

    public:

      /** \brief edge directions */
      enum eDirectionType {
        /** \brief bidirectional edge, create 2 edge to each directions */
        edtBidirectional,
        /** \brief directional edge */
        edtDirectional,
        /** \brief reverse edge, it belongs to a directional edge */
        edtReverse
      };

      /** \brief edge Type */
      class EdgeType {

        protected:
          /** \internal \brief the edge type name */
          std::string _type;
          /** \internal \brief the edge direction */
          eDirectionType _dtype;
        public:
          /**
          * \brief constructor
          * \param type [in] name of the edge
          * \param dtype [in] direction of the edge
          */
          EdgeType(const std::string& type, eDirectionType dtype);
          
          /**
          * \brief gives back the type name of edge
          * \return name of the type
          */
          const std::string& getType() const;

          /**
          * \brief gives back the direction of the edge
          * \return edge direction
          */
          eDirectionType getDirectionType() const;

          /**
          * \brief operator <
          * \param edgeType [in] the other edge
          * \return true, if the edge 'type' is lower then 'edgeType' 'type'
          */
          bool operator<(const EdgeType& edgeType) const;

          /**
          * \brief operator ==
          * \param edgeType [in] the other edge
          * \return true, if the 2 edge 'type' and 'direction' is equal
          */
          bool operator==(const EdgeType& edgeType) const;

          /**
          * \brief operator ==
          * \param edgeType [in] the other edge
          * \return true, if the 2 edge 'type' and 'direction' is not equal
          */
          bool operator!=(const EdgeType& edgeType) const;

      };

      /** \brief set of edge types */
      typedef std::set<EdgeType> EdgeTypeSet;
      typedef std::set<std::pair<Key, eDirectionType> > InternalEdgeTypeSet;
      
      /**
      * \brief Interator class for edges
      */
      class EdgeIterator {

        protected:


          /** \internal \brief Type definition to store iterators in a container. */
          typedef std::list<EdgeIterator*> IteratorContainer;

        protected:

          void removeIterator();

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
          * \param filteredEdges   [in] If it is empty, we use all edges, else we use only filteredEdges edges
          */
          EdgeIterator(out_edge_iter container_begin,out_edge_iter container_end, IteratorContainer *itContainer, Graph* graph, GraphVertex vertex,const EdgeTypeSet &filteredEdges);

          /**
          * \internal
          * \brief Inserts the specified element into the list.
          * \param edge [in] The element.
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          *
          * The element is inserted immediately before the next element that would be returned by next(), if any,
          * and after the next element that would be returned by previous(), if any. (If the list contains no elements,
          * the new element becomes the sole element on the list.) The new element is inserted before the implicit cursor:
          * a subsequent call to next() would be unaffected, and a subsequent call to previous() would return the new element.
          */
          void add(const Edge& edge);

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
          * \brief Creates an invalid EdgeIterator (this can be used only to create an iterator but cannot be used until giving value to it).
          */
          EdgeIterator();

          /**
          * \brief Creates an EdgeIterator by copying the one given in parameter.
          * \param iterator [in] The other EdgeIterator which initializes this one.
          */
          EdgeIterator(const EdgeIterator &iterator);

          /**
          * \brief Detructor which safely destroys the EdgeIterator.
          */
          virtual ~EdgeIterator();

          /**
          * \brief Copies a EdgeIterator.
          * \param otherIt [in] The other EdgeIterator which initializes this one.
          * \throw GraphInvalidIteratorException If the other iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns a reference to a EdgeIterator.
          */
          EdgeIterator& operator=(const EdgeIterator& otherIt);

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
          virtual Edge next();

          /**
          * \brief Returns true if this iterator has more elements when traversing the list in the reverse direction. 
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns true if the  iterator has more elements when traversing the list in the reverse direction.
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
          virtual Edge previous();

          /**
          * \brief Compares the two iterators.
          * \param otherIt                     [in] The iterator is compared to it.
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns true if the two iterators would give back the same elements with the next previous() and next() calls.
          */
          virtual bool equals(const EdgeIterator& otherIt) const;

          virtual int hashCode() const
;
        private:
          /**
          * \internal
          * \brief Searches for the next non-deleted element.
          * \param inc [in] If inc is true, the iterator steps before searching.
          * \param it  [in] The iterator whose next element is searched.
          * \return Returns the next non-deleted element (or the end of the container if there is no next element).
          */
          out_edge_iter findNextNotFiltered(bool inc, const out_edge_iter& it);

          /**
          * \internal
          * \brief Gives back the next element.
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns the next element (or the end of the container if there is no next element).
          */
          out_edge_iter nextItem();

          /**
          * \internal
          * \brief Searches for the previous not deleted element.
          * \param dec [in] If dec is true, the iterator steps before searching.
          * \param it  [in] The iterator whose previous element is searched.
          * \return Returns the previous not deleted element (or the end of the container if there is no previous element).
          */
          out_edge_iter findPreviousNotDeletedFiltered(bool dec, const out_edge_iter& it);

          /**
          * \internal
          * \brief Gives back the previous element.
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns the previous element (or the end of the container if there is no previous element).
          */
          out_edge_iter previousItem();

          /**
          * \internal
          * \brief Safely removes an element element.
          * \param it [in] The iterator which will be removed.
          * \return todo.
          */
          out_edge_iter safeRemove(const out_edge_iter& it);

          /**
          * \internal
          * \brief Invalidates the iterator (sets its state to op_Invalidated).
          */
          void invalidate();

        protected:

          /** \internal \brief Pointer to the Factory. */
          Graph* graph;
          GraphVertex vertex;

          /** \internal \brief Pointer to the Container the ids stored in. */
          out_edge_iter container_begin;
          out_edge_iter container_end;

          /** \internal \brief Inner iterator of the Container. */
          out_edge_iter it;

          /** \internal \brief Pointer to the list of the iterators of the Container. */
          IteratorContainer* iterators;
      
          /** \internal \brief Filtered edges */
          InternalEdgeTypeSet filteredEdges;
      

          /** \internal \brief State of the iterator (the last operation done on the iterator). */
          op lastOp;

          friend class Graph;
          friend class Node;
      };
  
    public:

      /**
      * \brief invalidEdge constructor
      */
      Edge();

      /**
      * \brief edge copy constructor
      * \param edge [in] other edge
      */
      Edge(const Edge& edge);

      Attribute& addAttribute(const Attribute& attribute);  // O(a)
      bool deleteAttribute(const Attribute& attribute); // O(a)
      bool deleteAttribute(Attribute::aType type, const std::string& name); // O(a)
      bool deleteAttribute(Attribute::aType type); // O(a)
      bool deleteAttribute(Attribute::aType type, const std::string& name, const std::string& context);
      void deleteAttributes();
      Attribute::AttributeIterator getAttributes() const; // O(1)
      Attribute::AttributeIterator findAttribute(Attribute::aType type, const std::string& name, const std::string& context) const; // O(a)
      
      /**
      * \brief gives back attribute iterator to 'type' type of attributes
      * \param type [in] the attribute type
      * \return iterator to 'type' type of attributes
      */
      Attribute::AttributeIterator findAttributeByType(Attribute::aType type) const;

      /**
      * \brief gives back attribute iterator to 'name' name of attributes
      * \param name [in] the name of attribute
      * \return iterator to 'name' name of attributes
      */
      Attribute::AttributeIterator findAttributeByName(const std::string& name) const;

      /**
      * \brief gives back attribute iterator to 'context' context of attributes
      * \param context [in] the context of attribute
      * \return iterator to 'context' context of attributes
      */
      Attribute::AttributeIterator findAttributeByContext(const std::string& context) const;
    
      Edge getReversePair() const;
      Node getFromNode() const; // O(1)
      Node getToNode() const; // O(1)
      EdgeType getType() const; // O(1)
      bool equals(const Edge& edge) const; // O(1)

      int hashCode() const;
      std::string getName() const;
      bool operator==(const Edge& edge) const;
      bool operator!=(const Edge& edge) const;

      /**
      * \brief operator <
      * \param edgeType [in] the other edge
      * \return true, if the edge 'type' is lower then 'edgeType' 'type'
      */
      bool operator<(const Edge& edge) const;


    protected:

      Edge(Graph* g, GraphEdge edge);

    protected:

      Graph *g;
      GraphEdge edge;

    friend class Graph;
    friend class Node;
    friend class GraphXmlHandler;  
    friend GraphEdge getEdgeEdge(const Edge&);
    friend Graph* getEdgeGraph(const Edge&);
    friend Edge createEdge(Graph*, GraphEdge);
  };

}}


#endif
