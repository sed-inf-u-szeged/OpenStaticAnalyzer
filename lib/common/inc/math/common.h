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

#ifndef COMMON_MATH_COMMON_H
#define COMMON_MATH_COMMON_H

#include <vector>
#include <limits>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <cinttypes>

namespace common { namespace math { 

  /**
  * Checks whether the number is prime or not
  * Uses Miller-Rabin prime-test
  **/
  bool isPrime(uint32_t number);
  unsigned int editDistanceRec(const std::vector<int>& v1, unsigned int lastV1, const std::vector<int>& v2, unsigned int lastV2);
  size_t editDistance(const std::vector<int>& v1, const std::vector<int>& v2, unsigned int bound=std::numeric_limits<unsigned int>::max());
  size_t editDistance(const std::string& v1, const std::string& v2, unsigned int bound=std::numeric_limits<unsigned int>::max());

}}


#endif
