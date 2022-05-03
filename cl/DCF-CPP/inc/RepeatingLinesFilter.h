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

#ifndef _REPEATING_LINES_FILTER
#define _REPEATING_LINES_FILTER

#include "AbstractFilter.h"
#include "messages.h"

namespace columbus
{
  class DuplicatedCodeMiner;
}

class RepeatingLinesFilter: public AbstractFilter {
private:
  const columbus::DuplicatedCodeMiner& dcm;

public:
  RepeatingLinesFilter(columbus::DuplicatedCodeMiner& dcm) : AbstractFilter(), dcm(dcm) {};
  bool isFiltered(const columbus::genealogy::CloneClass& ccre);

  std::string getDebuggableName() {
    return std::string(CMSG_OS_FILTERING_CLONES_WITH_REPEATING_LINES);
  }

};

#endif
