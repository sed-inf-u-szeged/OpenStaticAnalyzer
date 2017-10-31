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

#ifndef __INTERVAL_H
#define __INTERVAL_H

#include <set>

struct Interval {
  unsigned int a;
  unsigned int b;

  mutable std::vector<unsigned int>* intervals;

  Interval(const Interval& object)
    : a(object.a)
    , b(object.b)
    , intervals(object.intervals) 
  {
    object.intervals = NULL;
    //TODO write a safer solution like this. :
    /*if (object.intervals != NULL) {
      intervals = new std::set<unsigned int>(*object.intervals);
    }
    but the current solution is faster :-) */
  }

  const Interval& operator=(const Interval&);

  Interval(unsigned int _a, unsigned int _b) : a(_a), b(_b), intervals(NULL) { }

  bool operator<=(const Interval& I) {
    /**
    * This realtion is actually the contains relation
    */
    return (a>=I.a && b<=I.b);
  }
  bool operator==(const Interval& I) {
    return (a==I.a && b==I.b);
  }
  bool operator<(const Interval& I) {
    /*
    partial ordering is defined by means of the lhs of the interval
    */
    return (a<I.a);
  }

  ~Interval() {
    delete intervals;
  }

  Interval clone() const {
    Interval I(a, b);
    if (intervals != NULL)
      I.intervals = new std::vector<unsigned int>(*intervals);
    else
      I.intervals = NULL;
    return I;
  }
};

inline bool operator<(const Interval& I1, const Interval& I2) {
  return I1.a>I2.a;
}
#endif
