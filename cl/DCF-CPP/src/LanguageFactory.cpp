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

#include "../inc/LanguageFactory.h"

#include <boost/functional/hash.hpp>
#include <Exception.h>

using namespace std;

namespace columbus {

  LanguageFactory::LanguageFactory()
    : loaded(false)
    , limComponentNameFileNameMap()
    , hashCodes()
  {}
  
  LanguageFactory::~LanguageFactory() {
  }

  std::string LanguageFactory::getFileNameByComponentId( const std::string& id )
  {
    std::map<std::string, std::string>::iterator it = limComponentNameFileNameMap.find(id);
    if (it != limComponentNameFileNameMap.end()) {
      return it->second;
    }
    return  std::string();
  }

  const std::map<std::string, std::string>& LanguageFactory::getLimComponentNameFileNameMap() const
  {
    return limComponentNameFileNameMap;
  }

  void LanguageFactory::fillComponentList( std::list<std::string> listOfInputFile )
  {
    for (std::list<std::string>::iterator it = listOfInputFile.begin();it != listOfInputFile.end();++it) {
    }
  }





}

