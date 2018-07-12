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

#ifndef __SUBSEQUENCE__
#define __SUBSEQUENCE__
#include<iostream>
#include"sequence.h"

namespace columbus { namespace suffix_array {

template<class T>
class Sequence;

template<class T>
class SubSequence {
  friend class Sequence<T>;
  unsigned int first;
  unsigned int lcp;
private:
  const Sequence<T>& parent;
  SubSequence(const Sequence<T>& s, unsigned int _first) :  first(_first), parent(s) {}

public:
  bool operator<(const SubSequence<T>& rhs) const {
    unsigned int min=std::min<unsigned int>(parent.getLength()-first, rhs.parent.getLength()-rhs.first);
    for (unsigned int i=0; i<min; i++) {
      if (*(parent.getSequence()+i+first) < *(rhs.parent.getSequence()+i+rhs.first))
        return true;
      else if (*(parent.getSequence()+i+first) > *(rhs.parent.getSequence()+i+rhs.first))
        return false;
    }
    if (parent.getLength()-first<rhs.parent.getLength()-rhs.first)
      return true;
    return false;
  }
  void dump() const {
    std::cout << "[" << first << "] - ";
    for (unsigned int i=0; i<parent.getLength()-first; i++) {
      std::cout << *(parent.getSequence()+first+i);
      if (i<parent.getLength()-1)
        std::cout << ", ";
    }
  }
  inline void setLcp(unsigned int _lcp) {lcp=_lcp;}
  inline unsigned int getLcp() {return lcp;}
  inline unsigned int getFirst() const {return first;}
};

}}
#endif
