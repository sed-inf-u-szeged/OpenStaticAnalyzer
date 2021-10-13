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

#ifndef _LNPARAMSUP_H
#define _LNPARAMSUP_H

#include <list>
#include <string>
#include "ParamsupCommon.h"

namespace ColumbusWrappers {

namespace LnWrapperSup {

  
   /**
   * @brief Processes the given argument list of the ln command and collect those, which are necessary for wrapping.
   *
   * @param args           [in]  The given ln argument list.
   * @param lnArgs         [out] The arguments needed to be handled during ln wrapping.
   * @return                     True, if it can processes the given argument list.
   */
  bool examineLnArguments(const std::list<std::string>& args, LnArgs& lnArgs);

}}

#endif
