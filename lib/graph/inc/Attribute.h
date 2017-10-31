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

#ifndef _GRAPHATTRIBUTE_H
#define _GRAPHATTRIBUTE_H

#include <string>
#include <list>
#include <set>
#include <strtable/inc/StrTable.h>

/**
* \file Attribute.h
* \brief Contains Attribute and AttributeIterator declaration for the graph lib
*/

namespace columbus {  namespace graph {

  class Graph;

  class AttributeComposite;

  /**
  * \brief attributes to nodes and edges
  */
  class Attribute {

    public:
      
      /**
      * \brief the possible attributes Type
      */
      enum aType {
        atInt,
        atFloat,
        atString,
        atComposite,
        atInvalid
      };


      class AttributeIterator;
     
      Attribute(const Attribute& other);
      Attribute& operator=(const Attribute& other);
    protected: 
      /** \internal \brief pointer to container Graph */
      Graph *graph;
      /** \internal \brief key of attribute name */
      Key name;
      /** \internal \brief key of attribute context */
      Key context;

      /** \internal \brief list of AttributeIterators */
      typedef std::list<Attribute::AttributeIterator*> AttributeIteratorList;
      /** \internal \brief containst witch vertex has attribute iterator
      GraphVertex not comparable!!!
      */
      typedef std::map<GraphVertex,Attribute::AttributeIteratorList* > AttributeIteratorOnVertexMap;
      /** \internal \brief containst witch edge has attribute iterator
      GraphEdge not comparable!!!
      */
      typedef std::map<GraphEdge,Attribute::AttributeIteratorList* > AttributeIteratorOnEdgeMap;
      
    public:

     /**
      * \brief iterator to attributes
      */
      class AttributeIterator {

        public:
          /** \internal Ereaser function for iterator containers */
          typedef void (*IteratorContainerEraser) (void* container, void* iterator);

        protected:

          /** \internal \brief Type definition to store attributes in a container. */
          typedef AttributeList Container;

          /** \internal \brief Type definition to store iterators in a container. */
          typedef AttributeIteratorList IteratorContainer;


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

          /** \internal \brief flags for attribute filter */
          struct FilterFlags {
            /** \internal \brief type is filtered */
            bool type;
            /** \internal \brief name is filtered */
            bool name;
            /** \internal \brief context is filtered */
            bool context;
            /** \internal \brief return true, if flags are equals */
            bool operator==(const FilterFlags& fflag) const;
            /** \internal \brief constructor */
            FilterFlags(bool type, bool name, bool context);
          };

          /**
          * \internal
          * \brief Non-public constructor, which creates a usable new iterator.
          * \param container   [in] The container which stores the ids of the nodes the iteration is going on it.
          * \param itContainer [in] The container which stores other iterators applied for the same container.
          * \param graph [in] Pointer to the graph
          * \param graphVertex [in] The graph vertex on which the iterator is based
          */
          AttributeIterator(Container *container, IteratorContainer *itContainer, Graph *graph, GraphVertex graphVertex);

          /**
          * \internal
          * \brief Non-public constructor, which creates a usable new iterator.
          * \param container   [in] The container which stores the ids of the nodes the iteration is going on it.
          * \param itContainer [in] The container which stores other iterators applied for the same container.
          * \param graph [in] Pointer to the graph
          * \param graphEdge [in] The graph edge on which the iterator is based
          */
          AttributeIterator(Container *container, IteratorContainer *itContainer, Graph *graph, GraphEdge graphEdge);

          /**
          * \internal
          * \brief Non-public constructor, which creates a usable new iterator.
          * \param container   [in] The container which stores the ids of the nodes the iteration is going on it.
          * \param itContainer [in] The container which stores other iterators applied for the same container.
          * \param graph [in] Pointer to the graph
          * \param attrComposite [in] attributeComposite object, witch containst the attributes and the iterator list
          */
          AttributeIterator(Container *container, IteratorContainer *itContainer, Graph *graph, AttributeComposite* attrComposite);

          /**
          * \internal
          * \brief Non-public constructor, which creates a usable new iterator.
          * \param container   [in] The container which stores the ids of the nodes the iteration is going on it.
          * \param itContainer [in] The container which stores other iterators applied for the same container.
          * \param graph [in] Pointer to the graph
          * \param graphVertex [in] The graph vertex on which the iterator is based
          * \param filter [in] attribute filterFlag set witch filter is enabled or disabled
          * \param type [in] the not filtered attribute type
          * \param name [in] the not fileterd attribute name
          * \param context [in] the not filtered attribute context
          */
          AttributeIterator(Container *container, IteratorContainer *itContainer, Graph *graph, GraphVertex graphVertex, FilterFlags filter, Attribute::aType type , const std::string& name, const std::string& context);

          /**
          * \internal
          * \brief Non-public constructor, which creates a usable new iterator.
          * \param container   [in] The container which stores the ids of the nodes the iteration is going on it.
          * \param itContainer [in] The container which stores other iterators applied for the same container.
          * \param graph [in] Pointer to the graph
          * \param graphEdge [in] The graph edge on which the iterator is based
          * \param filter [in] attribute filterFlag set witch filter is enabled or disabled
          * \param type [in] the not filtered attribute type
          * \param name [in] the not fileterd attribute name
          * \param context [in] the not filtered attribute context
          */
          AttributeIterator(Container *container, IteratorContainer *itContainer, Graph *graph, GraphEdge graphEdge, FilterFlags filter, Attribute::aType type, const std::string& name, const std::string& context);

          /**
          * \internal
          * \brief Non-public constructor, which creates a usable new iterator.
          * \param container   [in] The container which stores the ids of the nodes the iteration is going on it.
          * \param itContainer [in] The container which stores other iterators applied for the same container.
          * \param graph [in] Pointer to the graph
          * \param attrComposite [in] attributeComposite object, witch containst the attributes and the iterator list
          * \param filter [in] attribute filterFlag set witch filter is enabled or disabled
          * \param type [in] the not filtered attribute type
          * \param name [in] the not fileterd attribute name
          * \param context [in] the not filtered attribute context
          */
          AttributeIterator(Container *container, IteratorContainer *itContainer, Graph *graph, AttributeComposite* attrComposite, FilterFlags filter, Attribute::aType type, const std::string& name, const std::string& context);
          
          /**
          * \internal
          * \brief Inserts the specified element into the list.
          * \param attribute  [in] The element.
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          *
          * The element is inserted immediately before the next element that would be returned by next(), if any,
          * and after the next element that would be returned by previous(), if any. (If the list contains no elements,
          * the new element becomes the sole element on the list.) The new element is inserted before the implicit cursor:
          * a subsequent call to next() would be unaffected, and a subsequent call to previous() would return the new element.
          */
          void add(const Attribute& attribute);

          /**
          * \internal
          * \brief Removes from the list the last element that was returned by next() or previous().
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          * \throw GraphIllegalStateException    Neither next() nor previous() have been called, or remove() or add() have been called after the last call to next() or previous().
          *
          * This call can only be made once per call to next() or previous(). It can be made
          * only if add() has not been called after the last call to next() or previous().
          */
          void remove();

        public:

          /**
          * \brief Creates an invalid AttributeIterator (this can be used only to create an iterator but cannot be used until giving value to it).
          */
          AttributeIterator();

          /**
          * \brief Creates an AttributeIterator by copying the one given in parameter.
          * \param iterator [in] The other AttributeIterator which initializes this one.
          */
          AttributeIterator(const AttributeIterator &iterator);

          /**
          * \brief Detructor which safely destroys the AttributeIterator.
          */
          virtual ~AttributeIterator();

          /**
          * \brief Copies a AttributeIterator.
          * \param otherIt                     [in] The other AttributeIterator which initializes this one.
          * \throw GraphInvalidIteratorException If the other iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns a reference to a AttributeIterator.
          */
          AttributeIterator& operator=(const AttributeIterator& otherIt);

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
          * \throw GraphNoSuchElementException   If the iteration has no next element GraphNoSuchElementException is thrown.
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns the next element in the list.
          *
          * This method may be called repeatedly to iterate through the list, or intermixed with calls to previous() to go back and forth.
          * (Note that alternating calls to next() and previous() will return the same element repeatedly.)
          */
          virtual Attribute& next();

          /**
          * \brief Returns true if this iterator has more elements when traversing the list in the reverse direction. 
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns true if the iterator has more elements when traversing the list in the reverse direction.
          *
          * In other words, returns true if previous() would return an element rather than throwing an exception.
          */
          virtual bool hasPrevious();

          /**
          * \brief Returns the previous element in the list.
          * \throw GraphNoSuchElementException   If the iteration has no previous element GraphNoSuchElementException is thrown.
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns the previous element in the list.
          *
          * This method may be called repeatedly to iterate through the list backwards, or intermixed with calls to next() to go back and forth.
          * (Note that alternating calls to next() and previous() will return the same element repeatedly.)
          */
          virtual Attribute& previous();

          /**
          * \brief Compares the two iterators.
          * \param otherIt                     [in] The iterator is compared to it.
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns true if the two iterators would give back the same elements with the next previous() and next() calls.
          */
          virtual bool equals(const AttributeIterator& otherIt) const;

          virtual int hashCode() const;

        private:

          bool isOutFilteredItem(Attribute* attribute);

          /**
          * \internal
          * \brief Searches for the next element.
          * \param inc [in] If inc is true, the iterator steps before searching.
          * \param it  [in] The iterator whose next element is searched.
          * \return Returns the next non-deleted element (or the end of the container if there is no next element).
          */
          Container::iterator findNextNotFiltered(bool inc, const Container::iterator& it);

          /**
          * \internal
          * \brief Gives back the next element.
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns the next element (or the end of the container if there is no next element).
          */
          Container::iterator nextItem();

          /**
          * \internal
          * \brief Searches for the previous not deleted element.
          * \param dec [in] If dec is true, the iterator steps before searching.
          * \param it  [in] The iterator whose previous element is searched.
          * \return Returns the previous not deleted element (or the end of the container if there is no previous element).
          */
          Container::iterator findPrevious(bool dec, const Container::iterator& it);

          /**
          * \internal
          * \brief Gives back the previous element.
          * \throw GraphInvalidIteratorException If the iterator is invalid GraphInvalidIteratorException is thrown.
          * \return Returns the previous element (or the end of the container if there is no previous element).
          */
          Container::iterator previousItem();

          /**
          * \internal
          * \brief Safely removes an element element.
          * \param it [in] The iterator which will be removed.
          * \return todo.
          */
          Container::iterator safeRemove(const Container::iterator& it);

          /**
          * \internal
          * \brief Invalidates the iterator (sets its state to op_Invalidated).
          */
          void invalidate();

          /**
          * \internal
          * \brief Removes the iterator from the iterator list. If the list becomes empty, than the allocated memory for it will be released.
          */
          void removeIterator();

        protected:

          /** \internal \brief Pointer to the Graph. */
          Graph* graph;

          /** \internal \brief Pointer to the Container the ids stored in. */
          Container* container;

          /** \internal \brief Inner iterator of the Container. */
          Container::iterator it;

          /** \internal \brief Pointer to the list of the iterators of the Container. */
          IteratorContainer* iterators;

          /** \internal \brief State of the iterator (the last operation done on the iterator). */
          op lastOp;

          /** filtered types */
          Attribute::aType type;

          /** filtered name */
          std::string name;

          /** filtered context */
          std::string context;

           /** \internal \brief The key of the name filter. */
          Key nameKey;
           /** \internal \brief The key of the context filter. */
          Key contextKey;

          /** witch attributes of attribute is filtered */
          FilterFlags fFlags;

          GraphVertex graphVertex;
          GraphEdge graphEdge;
          AttributeComposite* attributeComposite;
          
          enum {
            iteratorOnEdge,
            iteratorOnVertex,
            iteratorOnComposite
          } iteratorType;

          friend class Graph;
          friend class Node;
          friend class Edge;
          friend class AttributeContainer;
          friend class AttributeComposite;
      };

    public:

      virtual ~Attribute();
      virtual const std::string& getName() const;
      virtual const std::string& getContext() const;
      virtual aType getType() const;
      virtual bool equals(const Attribute& attribute) const;
      virtual int hashCode() const;
      bool operator==(const Attribute& attribute) const;
      bool operator!=(const Attribute& attribute) const;
      bool operator<(const Attribute& attribute) const;
      virtual Attribute& add(const Attribute& attribute);
      virtual std::string getStringValue() const;
      
    protected:

      /**
      * \internal
      * \brief copy the attribute, and return with new instance
      * \return the new attribute
      */
      virtual Attribute* copy() const;

      /**
      * \internal
      * \brief constructor
      * \param name [in] attributum neve
      * \param context [in] attributum kontextusa
      */
      Attribute(const std::string& name, const std::string& context, Graph* g);

      /**
      * \internal
      * \brief constructor
      * \param nameKey [in]
      * \param contextKey [in]
      */
      Attribute(Key nameKey, Key contextKey, Graph* g);

      /**
      * \internal
      * \brief copy attribute name form 'from' StringTabel to 'to' StringTable
      * \param form [in] the source StringTable
      * \param to [out] the target StringTable
      */
      virtual void copyStrings(StrTable *from,StrTable *to);

      /**
      * \internal
      * \brief set attribute graph to 'graph'
      * \param graph [in] new graph
      */
      virtual void setGraph(Graph* graph);

      /**
      * \internal
      * \brief constructor, create empty attribute
      */
      Attribute();
    protected:

    friend class Graph;
    friend class Node;
    friend class Edge;
    friend class AttributeContainer;
    friend class AttributeComposite;
    friend Attribute* copyAttribute(const Attribute& attr) ;

  };

  /**
  * \brief Class for Integer type attribute
  */
  class AttributeInt : public Attribute {
    protected:

      int value;

      AttributeInt(const std::string& name, const std::string& context, int value,Graph *g);
      AttributeInt(Key nameKey, Key contextKey, int value, Graph *g);

      /** 
      * \internal
      * \brief copy attribute
      * \return the new attribute
      */
      virtual Attribute* copy() const;

    public:

      int getValue() const;
      void setValue(int value);
      void incValue(int value);
      virtual aType getType() const;
      virtual bool equals(const Attribute& attribute) const;
      virtual int hashCode() const;
      virtual std::string getStringValue() const;

      /**
      * \brief create invalidAttribute
      */
      AttributeInt();

    friend class Graph;
      
  };

  /**
  * \brief Class for Float type attribute
  */
  class AttributeFloat : public Attribute {
    protected:

      float value;

      AttributeFloat(const std::string& name, const std::string& context, float value,Graph *g);
      AttributeFloat(Key nameKey, Key contextKey, float value, Graph *g);

      /**
      * \internal
      * \brief copy the attribute and return with new instance
      * \return the new attribute
      */
      virtual Attribute* copy() const;


    public:

      float getValue() const;
      void setValue(float value);
      void incValue(float value);
      virtual aType getType() const;

      /**
      * \brief create invalidAttribute
      */
      AttributeFloat();
      virtual bool equals(const Attribute& attribute) const;
      virtual int hashCode() const;
      virtual std::string getStringValue() const;

    friend class Graph;

  };

  /** 
  * \brief Class for string type attribute
  */
  class AttributeString : public Attribute {
    protected:

      Key value;
      AttributeString(const std::string& name, const std::string& context, const std::string& value,Graph *g);
      AttributeString(Key nameKey, Key contextKey, Key valueKey, Graph *g);
      virtual Attribute* copy() const;

    public:

      const std::string& getValue() const;
      void setValue(const std::string& value);
      virtual aType getType() const;

      /**
      * \brief create invalidAttribute
      */
      AttributeString();

      virtual bool equals(const Attribute& attribute) const;
      virtual int hashCode() const;
      virtual std::string getStringValue() const;
      
    protected:

      /**
      * \internal
      * \brief copy StringAttribute name and value form 'from' StringTabel to 'to' StringTable
      * \param form [in] the source StringTable
      * \param to [out] the target StringTable
      */
      virtual void copyStrings(StrTable *from,StrTable *to);

    friend class Graph;

  };

  /**
  * \brief Class for composite attribute
  */
  class AttributeComposite : public Attribute {

    protected:

      /** \internal \brief the contained attributes */
      AttributeList* values;
      
      /** \internal \brief the attribute iterators on AttributeComposite */
      AttributeIterator::IteratorContainer* iterators; 
      
      AttributeComposite(const std::string& name, const std::string& context, Graph *g);
      AttributeComposite(Key nameKey, Key contextKey, Graph *g);
      
      /**
      * \internal
      * \brief copy the attribute and return with new instance
      * \return the new attribute
      */
      virtual Attribute* copy() const;


    public:

      /**
      * \brief destructor
      */
      virtual ~AttributeComposite();

      virtual aType getType() const;


      AttributeComposite& operator=(const columbus::graph::AttributeComposite&);

      /**
      * \brief copy constructor
      * \param attribute [in] the other AttributeComposite
      */
      AttributeComposite(const AttributeComposite& attribute);

      /**
      * \brief add new value if is not exist in values list
      * \param value [in] the new value
      * \throw AlreadyExist if attribute in values list
      * \return the copyed attribute
      */

      Attribute& addAttribute(const Attribute& value);

      /**
      * \brief get Attributes by name ,if attribute doesn't exist, the result iterator is empty(hasNext function alwasy return false) 
      * \param name [in] attribute name
      * \return the founded attribute, or invalidAttribute
      */
      Attribute::AttributeIterator findAttribute(const aType type, const std::string& name, const std::string& context) ;

      /**
      * \brief gives back attribute iterator to 'type' type of attributes, if attribute doesn't exist, the result iterator is empty(hasNext function alwasy return false)
      * \param type [in] the attribute type
      * \return iterator to 'type' type of attributes
      */
      Attribute::AttributeIterator findAttributeByType(Attribute::aType type) ;

      /**
      * \brief gives back attribute iterator to 'name' name of attributes, if attribute doesn't exist, the result iterator is empty(hasNext function alwasy return false)
      * \param name [in] the name of attribute
      * \return iterator to 'name' name of attributes
      */
      Attribute::AttributeIterator findAttributeByName(const std::string& name) ;

      /**
      * \brief gives back attribute iterator to 'context' context of attributes, if attribute doesn't exist, the result iterator is empty(hasNext function alwasy return false)
      * \param context [in] the context of attribute
      * \return iterator to 'context' context of attributes
      */
      Attribute::AttributeIterator findAttributeByContext(const std::string& context) ;

      /**
      * \brief create invalidAttribute
      */
      AttributeComposite();

      /**
      * \brief gives back attribute iterator to attributes witch contains the AttributeComposite attribute
      * \return the iterator
      */
      Attribute::AttributeIterator getAttributes();

      bool deleteAttribute(const Attribute& attribute); // O(a)
      bool deleteAttribute(Attribute::aType type, const std::string& name); // O(a)
      bool deleteAttribute(Attribute::aType type); // O(a)

      virtual bool equals(const Attribute& attribute) const;
      virtual int hashCode() const;
      virtual std::string getStringValue() const;
      
    protected:

      /**
      * \internal
      * \brief copy attribute name form 'from' StringTabel to 'to' StringTable
      * \param form [in] the source StringTable
      * \param to [out] the target StringTable
      */
      virtual void copyStrings(StrTable *from,StrTable *to);

      /**
      * \internal
      * \brief set attribute graph to 'graph'
      * \param graph [in] new graph
      */
      virtual void setGraph(Graph* graph);

    friend class AttributeIterator;
    friend class Graph;
    friend class GraphSchemaReader;

  };


  
}}

#endif
