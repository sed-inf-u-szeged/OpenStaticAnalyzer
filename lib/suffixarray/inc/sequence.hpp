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


#ifndef _SUFFIXARRAY_SEQUENCE_HPP_
#define _SUFFIXARRAY_SEQUENCE_HPP_

#include<stdlib.h>
#include<memory.h>
#include<algorithm>

namespace columbus { namespace suffix_array {

template<class T>
Sequence<T>::Sequence(T* s, unsigned int _length) {
  length=_length;
  start=new T[length];
  memcpy(start, s, length*sizeof(T));
}


template<class T>
Sequence<T>::Sequence(const std::vector<T>& v) {
  length = (unsigned)v.size();
  start=new T[length];
  for (unsigned i = 0; i < length; i++)
    start[i] = v[i];
}

template<class T>
Sequence<T>::~Sequence() {
  delete[] start;
}
template<class T>
bool Sequence<T>::operator<(Sequence<T>& rhs) const {
  unsigned int min=std::min<unsigned int>(length, rhs.length);
  for (unsigned int i=0; i<min; i++) {
    if (*(start+i) < *(rhs.start+i))
      return true;
    else if (*(start+i) > *(rhs.start+i))
      return false;
  }
  if (length<rhs.length)
    return true;
  return false;
}

template<class T>
const SubSequence<T> Sequence<T>::createSubSequence(unsigned int i) {
  return SubSequence<T>(*this, i);
}
template<class T>
void Sequence<T>::dump() const {
  typename std::set<SubSequence<T> >::const_iterator iter=subsequences.begin();
  while (iter!=subsequences.end()) {
    const SubSequence<T>& current=*iter;
    current.dump();
    std::cout << std::endl;
    iter++;
  }
}
template<class T>
void Sequence<T>::buildSuffixArray() {
  
}

}}

#endif
