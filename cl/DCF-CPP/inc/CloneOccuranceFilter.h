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

#ifndef __CLONE_OCCURANCE_FILER_H
#define __CLONE_OCCURANCE_FILER_H
#include "AbstractFilter.h"
#include "../inc/messages.h"

class CloneOccuranceFilter: public AbstractFilter {
private:
  unsigned int occurance;

public:
  CloneOccuranceFilter(unsigned int _occurance) : AbstractFilter(), occurance(_occurance) {};
  bool isFiltered(const columbus::genealogy::CloneClass& cc) {
    if(cc.getInstances() < occurance) return true;
    return false;
  }

  std::string getDebuggableName() {
    return std::string(CMSG_OS_RUNNING_OCCURANCE_FILTER);
  }
};



#endif
