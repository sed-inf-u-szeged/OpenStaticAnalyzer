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


#include "../../inc/paramsup/LnParamsup.h"
#include <common/inc/FileSup.h>


namespace ColumbusWrappers {

namespace LnWrapperSup {


  bool examineLnArguments(const std::list<std::string>& args, LnArgs& lnArgs)
  {
    for (auto argsIt = args.begin(); argsIt != args.end(); ++argsIt)
    {
      const char* arg = argsIt->c_str();
      // Option
      if (arg[0] == '-')
      {
        if (*argsIt == "-f")
          lnArgs.force = true;
        else if (*argsIt == "-T" || *argsIt == "--no-target-directory")
          lnArgs.noTargetDirectory = true;
        else if (*argsIt == "-t")
          lnArgs.targetDirectory = *(++argsIt);
        else if (argsIt->find("--target-directory=") == 0)
          lnArgs.targetDirectory = argsIt->substr(20);
      }
      else
        lnArgs.targets.push_back(*argsIt);
    }

    // check the different modes by the number of targets and parameters.

//       ln [OPTION]... [-T] TARGET LINK_NAME   (1st form)
//       ln [OPTION]... TARGET                  (2nd form)
//       ln [OPTION]... TARGET... DIRECTORY     (3rd form)
//       ln [OPTION]... -t DIRECTORY TARGET...  (4th form)



    if (lnArgs.targets.empty())     // Invalid form
      return false;

    if (lnArgs.targets.size() == 1) // 2nd form
    {
      lnArgs.form = 2;
      return true;
    }

    const bool lastIsDirectory = common::pathIsDirectory(lnArgs.targets.back());

    if (lnArgs.noTargetDirectory || !lastIsDirectory) // 1st form
    {
      if (lnArgs.targets.size() > 2)
        return false;

      lnArgs.linkName = lnArgs.targets.back();
      lnArgs.targets.pop_back();
      lnArgs.form = 1;
    }
    else
    {
      if (lnArgs.targetDirectory.empty()) // 3rd form
      {
        if (!lastIsDirectory)
          return false;

        lnArgs.targetDirectory = lnArgs.targets.back();
        lnArgs.targets.pop_back();
        lnArgs.form = 3;
      }
      else // 4th form
        lnArgs.form = 4;
    }

    return true;
  }

}}
