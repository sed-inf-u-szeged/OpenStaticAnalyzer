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

#ifndef _AS_WRAPPER_H
#define _AS_WRAPPER_H

#include <AbstractWrapperLib/inc/abstractwrapper/AbstractWrapper.h>
#include <AbstractWrapperLib/inc/paramsup/ParamsupCommon.h>
#include <string>

namespace ColumbusWrappers {
  class AsWrapper :AbstractWrapper
  {
  public:
    AsWrapper(std::string configfile);

    virtual bool process( int argc, char** argv );

    std::string createCsiName(const std::string& outputFile) const ;

    bool parsingParameters( int argc, char** argv );
  private:
    std::string inputFile;
    std::string outputFile;
  };
}

#endif