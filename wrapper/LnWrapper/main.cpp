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


#include <AbstractWrapperLib/inc/abstractwrapper/AbstractFilesystemLinker.h>
#include <AnalyzerWrapperConfig/AnalyzerWrapperConfig.h>
#include <AbstractWrapperLib/inc/paramsup/LnParamsup.h>
#include <common/inc/FileSup.h>
#include <common/inc/PlatformDependentDefines.h>

#include <string>
#include <list>

using namespace std;
using namespace ColumbusWrappers;


class LnWrapper : public AbstractFSLinker
{
public:
  LnWrapper(const std::string& configfile)
    : AbstractFSLinker (configfile)
  {
  }

  bool process(int argc, char** argv)
  {
    LnArgs processedLnArgs;
    list<string> unprocessedLnArgs;
    setParams(argc, argv, unprocessedLnArgs, {});

    if (LnWrapperSup::examineLnArguments(unprocessedLnArgs, processedLnArgs))
      return executeFSLink(processedLnArgs);
    else
      return false;
  }
};


int main(int argc, char** argv)
{
  LnWrapper lnWrapper(common::getExecutableProgramDir() + DIRDIVSTRING + ANALYZER_WRAPPER_CONFIG);
  if (lnWrapper.process(argc-1, argv+1))
    return EXIT_SUCCESS;

  return EXIT_FAILURE;
}