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

#ifndef _LIM_ListIteratorAssoc_H_
#define _LIM_ListIteratorAssoc_H_

#include "lim/inc/lim.h"
#include "common/inc/sllist.h"


namespace columbus { namespace lim { namespace asg {
  struct acdLinkInfo {
    short low, high;
    Key name_key;
  };

  /**
  * \brief AssocEdge represents the edge which has association class.
  */
  template <typename T, typename V>
  struct AssocEdge {
    const NodeId node;
    V assocClass;

    AssocEdge(const NodeId node, V assocClass) : node(node), assocClass(assocClass) {}

    const NodeId operator*() const {
      return node;
    }
    const NodeId* operator->() const {
      return node;
    }
    operator NodeId () const {
      return node;
    }
    bool operator==(const AssocEdge& rhs) const {
      return node == rhs.node && assocClass == rhs.assocClass;
    }
    bool operator!=(const AssocEdge& rhs) const {
      return !(*this == rhs);
    }
    bool operator==(const T* rhs) const {
      return node == rhs;
    }
    bool operator!=(const T* rhs) const {
      return !(*this == rhs);
    }
  };

  /**
  * \brief AssocEdge is the base class of all all iterator classes works on edges having association class.
  */
  template <typename T, typename V>
  class ListIteratorAssoc : public ListIteratorBase<AssocEdge<NodeId,V>,T> {

    public:
      /** \internal \brief Type definition to store association edges in a container. */
      typedef typename ListIteratorBase<AssocEdge<NodeId,V>,T>::Container Container;

    protected:
      /**
      * \internal
      * \brief Non-public constructor, which creates a usable new iterator.
      * \param container     [in] The container which stores the ids of the nodes the iteration is going on it.
      * \param factory       [in] The Factory.
      * \param createAsBegin [in] Create iterator begin or end.
      */
      ListIteratorAssoc(const Container *container, const Factory* factory, bool createAsBegin);

    public:
      /**
      * \internal
      * \brief Destructor which safely destroys the ListIteratorAssoc.
      */
      virtual ~ListIteratorAssoc();

    protected:

      friend class ReverseEdges;

      // ---------- List of nodes having edge containers ----------

      friend class base::Named;
      friend class logical::ClassGenericInstance;
      friend class logical::ClassGenericSpec;
      friend class logical::MethodGenericInstance;
      friend class logical::MethodGenericSpec;
      friend class type::TypeFormerMethod;
      friend class logical::Member;
  }; // ListIteratorAssoc


  /**
  * \brief ListIteratorAssocString iterates edges whose association class represents 'const std::string&' type.
  */
  template <typename T>
  class ListIteratorAssocString : public ListIteratorAssoc<T,Key> {

    public:

      /** \internal \brief Type definition to store association edges in a container. */
      typedef typename ListIteratorAssoc<T,Key>::Container Container;

    protected:

      /**
      * \internal
      * \brief Non-public constructor, which creates a usable new iterator.
      * \param container     [in] The container which stores the ids of the nodes the iteration is going on it.
      * \param factory       [in] The Factory.
      * \param createAsBegin [in] Create iterator begin or end.
      */
      ListIteratorAssocString(const Container *container, const Factory* factory, bool createAsBegin);

    public:

      /**
      * \brief Creates an ListIteratorAssocString by copying the one given in parameter.
      * \param otherIt [in] The other ListIteratorAssocString which initializes this one.
      */
      ListIteratorAssocString(const ListIteratorAssocString &otherIt);

      /**
      * \brief Destructor which safely destroys the ListIteratorAssocString.
      */
      virtual ~ListIteratorAssocString();

      /**
      * \brief Copies a ListIteratorAssocString.
      * \param otherIt                     [in] The other ListIteratorAssocString which initializes this one.
      * \throw LimInvalidIteratorException If the other iterator is invalid LimInvalidIteratorException is thrown.
      * \return Returns a reference to a ListIteratorAssocString.
      */
      ListIteratorAssocString& operator=(const ListIteratorAssocString& otherIt);

      /**
      * \brief Gives back the association class.
      * \throw LimInvalidIteratorException If the iterator is invalid LimInvalidIteratorException is thrown.
      * \return Returns with the association class.
      */
      const std::string& getAssocClass();

      friend class base::Named;
  };


  /**
  * \brief ListIteratorAssocTypeArgumentConstraintKind iterates edges whose association class represents 'TypeArgumentConstraintKind' type.
  */
  template <typename T>
  class ListIteratorAssocTypeArgumentConstraintKind : public ListIteratorAssoc<T,TypeArgumentConstraintKind> {

    public:

      /** \internal \brief Type definition to store association edges in a container. */
      typedef typename ListIteratorAssoc<T,TypeArgumentConstraintKind>::Container Container;

    protected:

      /**
      * \internal
      * \brief Non-public constructor, which creates a usable new iterator.
      * \param container     [in] The container which stores the ids of the nodes the iteration is going on it.
      * \param factory       [in] The Factory.
      * \param createAsBegin [in] Create iterator begin or end.
      */
      ListIteratorAssocTypeArgumentConstraintKind(const Container *container, const Factory* factory, bool createAsBegin);

    public:

      /**
      * \brief Creates an ListIteratorAssocTypeArgumentConstraintKind by copying the one given in parameter.
      * \param otherIt [in] The other ListIteratorAssocTypeArgumentConstraintKind which initializes this one.
      */
      ListIteratorAssocTypeArgumentConstraintKind(const ListIteratorAssocTypeArgumentConstraintKind &otherIt);

      /**
      * \brief Destructor which safely destroys the ListIteratorAssocTypeArgumentConstraintKind.
      */
      virtual ~ListIteratorAssocTypeArgumentConstraintKind();

      /**
      * \brief Copies a ListIteratorAssocTypeArgumentConstraintKind.
      * \param otherIt                     [in] The other ListIteratorAssocTypeArgumentConstraintKind which initializes this one.
      * \throw LimInvalidIteratorException If the other iterator is invalid LimInvalidIteratorException is thrown.
      * \return Returns a reference to a ListIteratorAssocTypeArgumentConstraintKind.
      */
      ListIteratorAssocTypeArgumentConstraintKind& operator=(const ListIteratorAssocTypeArgumentConstraintKind& otherIt);

      /**
      * \brief Gives back the association class.
      * \throw LimInvalidIteratorException If the iterator is invalid LimInvalidIteratorException is thrown.
      * \return Returns with the association class.
      */
      TypeArgumentConstraintKind getAssocClass();

      friend class logical::ClassGenericInstance;
      friend class logical::ClassGenericSpec;
      friend class logical::MethodGenericInstance;
      friend class logical::MethodGenericSpec;
      friend class type::TypeFormerMethod;
  };


  /**
  * \brief ListIteratorAssocSourcePosition iterates edges whose association class represents 'const SourcePosition&' type.
  */
  template <typename T>
  class ListIteratorAssocSourcePosition : public ListIteratorAssoc<T,SourcePosition> {

    public:

      /** \internal \brief Type definition to store association edges in a container. */
      typedef typename ListIteratorAssoc<T,SourcePosition>::Container Container;

    protected:

      /**
      * \internal
      * \brief Non-public constructor, which creates a usable new iterator.
      * \param container     [in] The container which stores the ids of the nodes the iteration is going on it.
      * \param factory       [in] The Factory.
      * \param createAsBegin [in] Create iterator begin or end.
      */
      ListIteratorAssocSourcePosition(const Container *container, const Factory* factory, bool createAsBegin);

    public:

      /**
      * \brief Creates an ListIteratorAssocSourcePosition by copying the one given in parameter.
      * \param otherIt [in] The other ListIteratorAssocSourcePosition which initializes this one.
      */
      ListIteratorAssocSourcePosition(const ListIteratorAssocSourcePosition &otherIt);

      /**
      * \brief Destructor which safely destroys the ListIteratorAssocSourcePosition.
      */
      virtual ~ListIteratorAssocSourcePosition();

      /**
      * \brief Copies a ListIteratorAssocSourcePosition.
      * \param otherIt                     [in] The other ListIteratorAssocSourcePosition which initializes this one.
      * \throw LimInvalidIteratorException If the other iterator is invalid LimInvalidIteratorException is thrown.
      * \return Returns a reference to a ListIteratorAssocSourcePosition.
      */
      ListIteratorAssocSourcePosition& operator=(const ListIteratorAssocSourcePosition& otherIt);

      /**
      * \brief Gives back the association class.
      * \throw LimInvalidIteratorException If the iterator is invalid LimInvalidIteratorException is thrown.
      * \return Returns with the association class.
      */
      const SourcePosition& getAssocClass();

      friend class logical::Member;
  };


  /**
  * \brief ListIteratorAssocParameterKind iterates edges whose association class represents 'ParameterKind' type.
  */
  template <typename T>
  class ListIteratorAssocParameterKind : public ListIteratorAssoc<T,ParameterKind> {

    public:

      /** \internal \brief Type definition to store association edges in a container. */
      typedef typename ListIteratorAssoc<T,ParameterKind>::Container Container;

    protected:

      /**
      * \internal
      * \brief Non-public constructor, which creates a usable new iterator.
      * \param container     [in] The container which stores the ids of the nodes the iteration is going on it.
      * \param factory       [in] The Factory.
      * \param createAsBegin [in] Create iterator begin or end.
      */
      ListIteratorAssocParameterKind(const Container *container, const Factory* factory, bool createAsBegin);

    public:

      /**
      * \brief Creates an ListIteratorAssocParameterKind by copying the one given in parameter.
      * \param otherIt [in] The other ListIteratorAssocParameterKind which initializes this one.
      */
      ListIteratorAssocParameterKind(const ListIteratorAssocParameterKind &otherIt);

      /**
      * \brief Destructor which safely destroys the ListIteratorAssocParameterKind.
      */
      virtual ~ListIteratorAssocParameterKind();

      /**
      * \brief Copies a ListIteratorAssocParameterKind.
      * \param otherIt                     [in] The other ListIteratorAssocParameterKind which initializes this one.
      * \throw LimInvalidIteratorException If the other iterator is invalid LimInvalidIteratorException is thrown.
      * \return Returns a reference to a ListIteratorAssocParameterKind.
      */
      ListIteratorAssocParameterKind& operator=(const ListIteratorAssocParameterKind& otherIt);

      /**
      * \brief Gives back the association class.
      * \throw LimInvalidIteratorException If the iterator is invalid LimInvalidIteratorException is thrown.
      * \return Returns with the association class.
      */
      ParameterKind getAssocClass();

      friend class logical::ClassGenericInstance;
      friend class logical::ClassGenericSpec;
      friend class logical::MethodGenericInstance;
      friend class logical::MethodGenericSpec;
      friend class type::TypeFormerMethod;
  };


}}}
#endif

