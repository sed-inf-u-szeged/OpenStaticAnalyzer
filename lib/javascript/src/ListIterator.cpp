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

#include "javascript/inc/javascript.h"

#include "javascript/inc/messages.h"

namespace columbus { namespace javascript { namespace asg {
  template <typename B, typename T>
  ListIteratorBase<B,T>::ListIteratorBase(const Container *_container, const Factory* factory, bool createAsBegin) :
    fact(factory),
    container(_container),
    it(createAsBegin ? container->begin() : container->end()),
    invalid(false)
  {
    if (createAsBegin) {
      if (it != container->end() && fact->getIsFiltered(*it))
        next();
    }
  }

  template <typename B, typename T>
  ListIteratorBase<B,T>::ListIteratorBase(const ListIteratorBase &iterator) :
    fact(iterator.fact),
    container(iterator.container),
    it(iterator.it),
    invalid(iterator.invalid)
  {
  }

  template <typename B, typename T>
  ListIteratorBase<B,T>::~ListIteratorBase() {
  }

  template <typename B, typename T>
  ListIteratorBase<B,T>& ListIteratorBase<B,T>::operator=(const ListIteratorBase& otherIt) {
    if (this == &otherIt)
      return *this;

    if (otherIt.invalid)
      throw JavaScriptInvalidIteratorException(COLUMBUS_LOCATION, CMSG_EX_THE_ITERATOR_IS_INVALID);

    fact = otherIt.fact;
    container = otherIt.container;
    it = otherIt.it;
    invalid = otherIt.invalid;

    return *this;
  }

  template <typename B, typename T>
  const T& ListIteratorBase<B,T>::operator*() {
    T *node = dynamic_cast<T*>(fact->getPointer(*it));
    return *node;
  }

  template <typename B, typename T>
  const T* ListIteratorBase<B,T>::operator->() {
    T *node = dynamic_cast<T*>(fact->getPointer(*it));
    return node;
  }

  template <typename B, typename T>
  ListIteratorBase<B,T>& ListIteratorBase<B,T>::operator++() {
    next();
    return *this;
  }

  template <typename B, typename T>
  ListIteratorBase<B,T>& ListIteratorBase<B,T>::operator--() {
    previous();
    return *this;
  }

  template <typename B, typename T>
  bool ListIteratorBase<B,T>::operator==(const ListIteratorBase& rhs) const {
    return it == rhs.it;
  }

  template <typename B, typename T>
  bool ListIteratorBase<B,T>::operator!=(const ListIteratorBase& rhs) const {
    return !(*this == rhs);
  }

  template <typename B, typename T>
  void ListIteratorBase<B,T>::next() {
    if (invalid)
      throw JavaScriptInvalidIteratorException(COLUMBUS_LOCATION, CMSG_EX_THE_ITERATOR_IS_INVALID);

    it = nextItem();
  }

  template <typename B, typename T>
  void ListIteratorBase<B,T>::previous() {
    if (invalid)
      throw JavaScriptInvalidIteratorException(COLUMBUS_LOCATION, CMSG_EX_THE_ITERATOR_IS_INVALID);

    it = previousItem();
  }

  template <typename B, typename T>
  bool ListIteratorBase<B,T>::equals(const ListIteratorBase& otherIt) const {
    if (invalid)
      throw JavaScriptInvalidIteratorException(COLUMBUS_LOCATION, CMSG_EX_THE_ITERATOR_IS_INVALID);

    return (it == otherIt.it) ;
  }

  template <typename B, typename T>
  typename ListIteratorBase<B,T>::Container::const_iterator ListIteratorBase<B,T>::findNext(const typename ListIteratorBase<B,T>::Container::const_iterator& _it) {
    typename Container::const_iterator j = _it;

    if (j == container->end() )
      return container->end();

    ++j;
    return j;
  }

  template <typename B, typename T>
  typename ListIteratorBase<B,T>::Container::const_iterator ListIteratorBase<B,T>::findNextNotFiltered(const typename ListIteratorBase<B,T>::Container::const_iterator& _it) {
    typename Container::const_iterator nextElement = findNext( _it);

    while (nextElement != container->end() && fact->getIsFiltered(*nextElement))
      nextElement = findNext( nextElement);

    return nextElement;
  }

  template <typename B, typename T>
  typename ListIteratorBase<B,T>::Container::const_iterator ListIteratorBase<B,T>::nextItem() {
        return findNextNotFiltered(it);
  }

  template <typename B, typename T>
  typename ListIteratorBase<B,T>::Container::const_iterator ListIteratorBase<B,T>::findPrevious(const typename ListIteratorBase<B,T>::Container::const_iterator& _it) {
    typename Container::const_iterator j = _it;

    if (j == container->begin() )
      return container->end();

    --j;
    return j;
  }

  template <typename B, typename T>
  typename ListIteratorBase<B,T>::Container::const_iterator ListIteratorBase<B,T>::findPreviousNotFiltered(const typename ListIteratorBase<B,T>::Container::const_iterator& _it) {
    typename Container::const_iterator prevElement = findPrevious( _it);

    while (prevElement != container->end() && fact->getIsFiltered(*prevElement))
      prevElement = findPrevious( prevElement);

    return prevElement;
  }

  template <typename B, typename T>
  typename ListIteratorBase<B,T>::Container::const_iterator ListIteratorBase<B,T>::previousItem() {
    return findPreviousNotFiltered(it);
  }

  template <typename T>
  ListIterator<T>::ListIterator(const Container *container, const Factory* factory, bool createAsBegin) : ListIteratorBase<NodeId, T>(container, factory, createAsBegin) {
  }

  template <typename T>
  ListIterator<T>::~ListIterator() {
  }

  template <typename T>
  ListIterator<T>::ListIterator(const ListIterator& otherIt) : ListIteratorBase<NodeId, T>(otherIt) {
  }

  template <typename T>
  ListIterator<T>& ListIterator<T>::operator=(const ListIterator& otherIt) {
    ListIteratorBase<NodeId, T>::operator=(otherIt);

    return *this;
  }

  template class ListIterator<base::Base>;
  template class ListIterator<base::Comment>;
  template class ListIterator<base::Positioned>;
  template class ListIterator<base::Program>;
  template class ListIterator<structure::ExportSpecifier>;
  template class ListIterator<structure::ImpSpecifier>;
  template class ListIterator<declaration::VariableDeclarator>;
  template class ListIterator<expression::Property>;
  template class ListIterator<expression::Expression>;
  template class ListIterator<expression::TemplateElement>;
  template class ListIterator<statement::Pattern>;
  template class ListIterator<statement::Statement>;
  template class ListIterator<statement::SwitchCase>;
  template class ListIterator<structure::MethodDefinition>;

}}}
