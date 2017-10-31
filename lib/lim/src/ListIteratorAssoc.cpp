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

#include "lim/inc/lim.h"


namespace columbus { namespace lim { namespace asg {
  template <typename T, typename V>
  ListIteratorAssoc<T,V>::ListIteratorAssoc(const Container* container, const Factory* factory, bool createAsBegin) :
    ListIteratorBase<AssocEdge<NodeId,V>,T>(container, factory, createAsBegin)
  {
  }

  template <typename T, typename V>
  ListIteratorAssoc<T,V>::~ListIteratorAssoc() {
  }


  template <typename T>
  ListIteratorAssocString<T>::ListIteratorAssocString(const Container* container, const Factory* factory, bool createAsBegin) : ListIteratorAssoc<T,Key>(container, factory, createAsBegin) {
  }

  template <typename T>
  ListIteratorAssocString<T>::~ListIteratorAssocString() {
  }

  template <typename T>
  ListIteratorAssocString<T>::ListIteratorAssocString(const ListIteratorAssocString &otherIt) : ListIteratorAssoc<T,Key>(otherIt) {
  }

  template <typename T>
  ListIteratorAssocString<T>& ListIteratorAssocString<T>::operator=(const ListIteratorAssocString &otherIt) {
    ListIteratorAssoc<T,Key>::operator=(otherIt);
    return *this;
  }

  template <typename T>
  const std::string& ListIteratorAssocString<T>::getAssocClass() {
    return this->fact->getStringTable().get((*this->it).assocClass);
  }


  template <typename T>
  ListIteratorAssocTypeArgumentConstraintKind<T>::ListIteratorAssocTypeArgumentConstraintKind(const Container* container, const Factory* factory, bool createAsBegin) : ListIteratorAssoc<T,TypeArgumentConstraintKind>(container, factory, createAsBegin) {
  }

  template <typename T>
  ListIteratorAssocTypeArgumentConstraintKind<T>::~ListIteratorAssocTypeArgumentConstraintKind() {
  }

  template <typename T>
  ListIteratorAssocTypeArgumentConstraintKind<T>::ListIteratorAssocTypeArgumentConstraintKind(const ListIteratorAssocTypeArgumentConstraintKind &otherIt) : ListIteratorAssoc<T,TypeArgumentConstraintKind>(otherIt) {
  }

  template <typename T>
  ListIteratorAssocTypeArgumentConstraintKind<T>& ListIteratorAssocTypeArgumentConstraintKind<T>::operator=(const ListIteratorAssocTypeArgumentConstraintKind &otherIt) {
    ListIteratorAssoc<T,TypeArgumentConstraintKind>::operator=(otherIt);
    return *this;
  }

  template <typename T>
  TypeArgumentConstraintKind ListIteratorAssocTypeArgumentConstraintKind<T>::getAssocClass() {
    return (*this->it).assocClass;
  }


  template <typename T>
  ListIteratorAssocSourcePosition<T>::ListIteratorAssocSourcePosition(const Container* container, const Factory* factory, bool createAsBegin) : ListIteratorAssoc<T,SourcePosition>(container, factory, createAsBegin) {
  }

  template <typename T>
  ListIteratorAssocSourcePosition<T>::~ListIteratorAssocSourcePosition() {
  }

  template <typename T>
  ListIteratorAssocSourcePosition<T>::ListIteratorAssocSourcePosition(const ListIteratorAssocSourcePosition &otherIt) : ListIteratorAssoc<T,SourcePosition>(otherIt) {
  }

  template <typename T>
  ListIteratorAssocSourcePosition<T>& ListIteratorAssocSourcePosition<T>::operator=(const ListIteratorAssocSourcePosition &otherIt) {
    ListIteratorAssoc<T,SourcePosition>::operator=(otherIt);
    return *this;
  }

  template <typename T>
  const SourcePosition& ListIteratorAssocSourcePosition<T>::getAssocClass() {
    return (*this->it).assocClass;
  }


  template <typename T>
  ListIteratorAssocParameterKind<T>::ListIteratorAssocParameterKind(const Container* container, const Factory* factory, bool createAsBegin) : ListIteratorAssoc<T,ParameterKind>(container, factory, createAsBegin) {
  }

  template <typename T>
  ListIteratorAssocParameterKind<T>::~ListIteratorAssocParameterKind() {
  }

  template <typename T>
  ListIteratorAssocParameterKind<T>::ListIteratorAssocParameterKind(const ListIteratorAssocParameterKind &otherIt) : ListIteratorAssoc<T,ParameterKind>(otherIt) {
  }

  template <typename T>
  ListIteratorAssocParameterKind<T>& ListIteratorAssocParameterKind<T>::operator=(const ListIteratorAssocParameterKind &otherIt) {
    ListIteratorAssoc<T,ParameterKind>::operator=(otherIt);
    return *this;
  }

  template <typename T>
  ParameterKind ListIteratorAssocParameterKind<T>::getAssocClass() {
    return (*this->it).assocClass;
  }

  template class ListIteratorAssocString<base::Named>;
  template class ListIteratorAssocTypeArgumentConstraintKind<type::Type>;
  template class ListIteratorAssocSourcePosition<physical::File>;
  template class ListIteratorAssocParameterKind<type::Type>;

  template class ListIteratorAssoc<base::Base,acdLinkInfo >;

}}}
