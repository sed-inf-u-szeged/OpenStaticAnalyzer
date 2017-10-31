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

#ifndef __ABSTRACT_FILTER_H
#define __ABSTRACT_FILTER_H
#include "genealogy/inc/genealogy.h"

namespace columbus { namespace dcf {
  class DuplicatedCodeMiner;
} }

class AbstractFilter {
private:
  int maxValue;
  int currentValue;

public:
  AbstractFilter() ;
  virtual ~AbstractFilter(){}
   bool checkCloneClass(const columbus::genealogy::CloneClass& cc) {
    currentValue++;
    return isFiltered(cc);
  }
  std::string getDebuggableName() {
    return std::string("Filtering clones");
  }
  int getMaxValue();
  int getValue() {
    return currentValue;
  }
protected:
  virtual bool isFiltered(const columbus::genealogy::CloneClass& cc) = 0;
};

#endif
