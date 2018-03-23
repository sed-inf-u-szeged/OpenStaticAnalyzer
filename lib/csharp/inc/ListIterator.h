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

#ifndef _CSHARP_ListIterator_H_
#define _CSHARP_ListIterator_H_

#include "csharp/inc/csharp.h"
#include "common/inc/sllist.h"

/**
* \file ListIterator.h
* \brief Contains declaration of the internal ListIterator class.
*/

namespace columbus { namespace csharp { namespace asg {
  /**
  * \brief Iterator, which can be used to iterate through the edges of the nodes.
  */
  template <typename B, typename T>
  class ListIteratorBase {

    protected:

      /** \brief Type definition to store node ids in a container. */
      typedef literateprograms::sllist<B> Container;

      /**
      * \internal
      * \brief Non-public constructor, which creates a usable new iterator.
      * \param container     [in] The container which stores the ids of the nodes the iteration is going on it.
      * \param factory       [in] The Factory.
      * \param createAsBegin [in] Create iterator begin or end.
      */
      ListIteratorBase(const Container *container, const Factory* factory, bool createAsBegin);

    public:

      /**
      * \brief Creates an ListIteratorBase by copying the one given in parameter.
      * \param otherIt [in] The other ListIteratorBase which initializes this one.
      */
      ListIteratorBase(const ListIteratorBase &otherIt);

      /**
      * \brief Destructor which safely destroys the ListIteratorBase.
      */
      virtual ~ListIteratorBase();

      /**
      * \brief Copies a ListIteratorBase.
      * \param otherIt                        [in] The other ListIteratorBase which initializes this one.
      * \throw CsharpInvalidIteratorException If the other iterator is invalid CsharpInvalidIteratorException is thrown.
      * \return Returns a reference to a ListIteratorBase.
      */
      ListIteratorBase& operator=(const ListIteratorBase& otherIt);

      /**
      * \brief This is a * operator of ListIteratorBase.
      * \throw CsharpInvalidIteratorException If the other iterator is invalid CsharpInvalidIteratorException is thrown.
      * \return Returns a reference to a node.
      */
      virtual const T& operator*();

      /**
      * \brief This is a -> operator of ListIteratorBase.
      * \throw CsharpInvalidIteratorException If the other iterator is invalid CsharpInvalidIteratorException is thrown.
      * \return Returns a pointer to a node.
      */
      virtual const T* operator->();

      /**
      * \brief This is a ++ operator of ListIteratorBase.
      * \throw CsharpInvalidIteratorException If the other iterator is invalid CsharpInvalidIteratorException is thrown.
      * \return Returns a reference to a ListIteratorBase.
      */
      virtual ListIteratorBase& operator++();

      /**
      * \brief This is a -- operator of ListIteratorBase.
      * \throw CsharpInvalidIteratorException If the other iterator is invalid CsharpInvalidIteratorException is thrown.
      * \return Returns a reference to a ListIteratorBase.
      */
      virtual ListIteratorBase& operator--();

      /**
      * \brief This is a == operator of ListIteratorBase.
      * \param rhs                            [in] The iterator is compared to it.
      * \throw CsharpInvalidIteratorException If the other iterator is invalid CsharpInvalidIteratorException is thrown.
      * \return Return true if the both iteratis is same
      */
      virtual bool operator==(const ListIteratorBase& rhs) const;

      /**
      * \brief This is a != operator of ListIteratorBase.
      * \param rhs                            [in] The iterator is compared to it.
      * \throw CsharpInvalidIteratorException If the other iterator is invalid CsharpInvalidIteratorException is thrown.
      * \return Return true if the both iteratis is not same
      */
      virtual bool operator!=(const ListIteratorBase& rhs) const;

      /**
      * \brief Compares the two iterators.
      * \param otherIt                        [in] The iterator is compared to it.
      * \throw CsharpInvalidIteratorException If the iterator is invalid CsharpInvalidIteratorException is thrown.
      * \return Returns true if the two iterators would give back the same elements with the next previous() and next() calls.
      */
      virtual bool equals(const ListIteratorBase& otherIt) const;

    private:
      /**
      * \brief Returns the next element in the list.
      * \throw CsharpNoSuchElementException   If the iteration has no next element CsharpNoSuchElementException is thrown.
      * \throw CsharpInvalidIteratorException If the iterator is invalid CsharpInvalidIteratorException is thrown.
      * \return Returns the next element in the list.
      *
      * This method may be called repeatedly to iterate through the list, or intermixed with calls to previous() to go back and forth.
      * (Note that alternating calls to next() and previous() will return the same element repeatedly.)
      */
      virtual void next();

      /**
      * \brief Returns the previous element in the list.
      * \throw CsharpNoSuchElementException   If the iteration has no previous element CsharpNoSuchElementException is thrown.
      * \throw CsharpInvalidIteratorException If the iterator is invalid CsharpInvalidIteratorException is thrown.
      * \return Returns the previous element in the list.
      *
      * This method may be called repeatedly to iterate through the list backwards, or intermixed with calls to next() to go back and forth.
      * (Note that alternating calls to next() and previous() will return the same element repeatedly.)
      */
      virtual void previous();

      /**
      * \internal
      * \brief Searches for the next element.
      * \param it  [in] The iterator whose next element is searched.
      * \return Returns the next element (or the end of the container if there is no next element).
      */
      typename Container::const_iterator findNext(const typename Container::const_iterator& it);

      /**
      * \internal
      * \brief Searches for the next not filtered, element.
      * \param it  [in] The iterator whose next element is searched.
      * \return Returns the next not filtered, element (or the end of the container if there is no next element).
      */
      typename Container::const_iterator findNextNotFiltered(const typename Container::const_iterator& it);

      /**
      * \internal
      * \brief Gives back the next element.
      * \throw CsharpInvalidIteratorException If the iterator is invalid CsharpInvalidIteratorException is thrown.
      * \return Returns the next element (or the end of the container if there is no next element).
      */
      typename Container::const_iterator nextItem();

      /**
      * \internal
      * \brief Searches for the previous not deleted element.
      * \param it  [in] The iterator whose previous element is searched.
      * \return Returns the previous not deleted element (or the end of the container if there is no previous element).
      */
      typename Container::const_iterator findPrevious(const typename Container::const_iterator& it);

      /**
      * \internal
      * \brief Searches for the previous not filtered, not filtered, not deleted element.
      * \param it  [in] The iterator whose previous element is searched.
      * \return Returns the previous not filtered, not deleted element (or the end of the container if there is no previous element).
      */
      typename Container::const_iterator findPreviousNotFiltered(const typename Container::const_iterator& it);

      /**
      * \internal
      * \brief Gives back the previous element.
      * \throw CsharpInvalidIteratorException If the iterator is invalid CsharpInvalidIteratorException is thrown.
      * \return Returns the previous element (or the end of the container if there is no previous element).
      */
      typename Container::const_iterator previousItem();

    protected:

      /** \internal \brief Pointer to the Factory. */
      const Factory* fact;

      /** \internal \brief Pointer to the Container the ids stored in. */
      const Container* container;

      /** \internal \brief Inner iterator of the Container. */
      typename Container::const_iterator it;

      /** \internal \brief Flag for invalidate. */
      bool invalid;

  }; // ListIteratorBase

  /**
  * \brief Iterator, which can be used to iterate through the edges of the nodes.
  */
  template <typename T>
  class ListIterator : public ListIteratorBase<NodeId, T> {

    protected:

      /** \brief Type definition to store node ids in a container. */
      typedef typename ListIteratorBase<NodeId, T>::Container Container;

      /**
      * \internal
      * \brief Non-public constructor, which creates a usable new iterator.
      * \param container     [in] The container which stores the ids of the nodes the iteration is going on it.
      * \param factory       [in] The Factory.
      * \param createAsBegin [in] Create iterator begin or end.
      */
      ListIterator(const Container *container, const Factory* factory, bool createAsBegin);

    public:

      /**
      * \brief Destructor which safely destroys the ListIterator.
      */
      virtual ~ListIterator();

      /**
      * \brief Creates an ListIterator by copying the one given in parameter.
      * \param otherIt [in] The other ListIterator which initializes this one.
      */
      ListIterator(const ListIterator& otherIt);

      /**
      * \brief Copies a ListIterator.
      * \param otherIt                        [in] The other ListIterator which initializes this one.
      * \throw CsharpInvalidIteratorException If the other iterator is invalid CsharpInvalidIteratorException is thrown.
      * \return Returns a reference to a ListIterator.
      */
      ListIterator& operator=(const ListIterator& otherIt);

      friend class ReverseEdges;

      // ---------- List of nodes having edge containers ----------

      friend class expression::AnonymousObjectCreationExpressionSyntax;
      friend class expression::ArrayTypeSyntax;
      friend class expression::ElementAccessExpressionSyntax;
      friend class expression::IdentifierNameSyntax;
      friend class expression::InitializerExpressionSyntax;
      friend class expression::InterpolatedStringExpressionSyntax;
      friend class statement::BlockSyntax;
      friend class statement::ForStatementSyntax;
      friend class statement::SwitchStatementSyntax;
      friend class statement::TryStatementSyntax;
      friend class structure::AccessorDeclarationSyntax;
      friend class structure::AccessorListSyntax;
      friend class structure::ArrayRankSpecifierSyntax;
      friend class structure::AttributeArgumentListSyntax;
      friend class structure::AttributeListSyntax;
      friend class structure::BaseArgumentListSyntax;
      friend class structure::BaseCrefParameterListSyntax;
      friend class structure::BaseFieldDeclarationSyntax;
      friend class structure::BaseListSyntax;
      friend class structure::BaseMethodDeclarationSyntax;
      friend class structure::BaseParameterListSyntax;
      friend class structure::BasePropertyDeclarationSyntax;
      friend class structure::BaseTypeDeclarationSyntax;
      friend class structure::CompilationUnitSyntax;
      friend class structure::DelegateDeclarationSyntax;
      friend class structure::EnumDeclarationSyntax;
      friend class structure::EnumMemberDeclarationSyntax;
      friend class structure::IncompleteMemberSyntax;
      friend class structure::MethodDeclarationSyntax;
      friend class structure::NamespaceDeclarationSyntax;
      friend class structure::OrderByClauseSyntax;
      friend class structure::ParameterSyntax;
      friend class structure::QueryBodySyntax;
      friend class structure::SwitchSectionSyntax;
      friend class structure::TypeArgumentListSyntax;
      friend class structure::TypeDeclarationSyntax;
      friend class structure::TypeParameterConstraintClauseSyntax;
      friend class structure::TypeParameterListSyntax;
      friend class structure::TypeParameterSyntax;
      friend class structure::VariableDeclarationSyntax;
      friend class structure::XmlElementStartTagSyntax;
      friend class structure::XmlElementSyntax;
      friend class structure::XmlEmptyElementSyntax;
  }; // ListIterator


}}}
#endif

