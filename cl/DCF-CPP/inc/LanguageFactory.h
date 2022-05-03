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

#ifndef LANGUAGEFACTORY_H_
#define LANGUAGEFACTORY_H_

#include <string>
#include <map>
#include <list>

#include <clang/Frontend/ASTUnit.h>
#include <clang/Frontend/PCHContainerOperations.h>

#include <genealogy/inc/genealogy.h>

namespace columbus {

class LanguageFactory {

protected:
  bool loaded;
  std::map<std::string, std::string> limComponentNameFileNameMap;
  std::map<std::string, std::size_t> hashCodes;
  
public:
  LanguageFactory();
  virtual ~LanguageFactory();

  const std::map<std::string, std::string>& getLimComponentNameFileNameMap() const;
public:

  void load(columbus::genealogy::System& system, bool deleteFiltered=false) ;
  std::string getFileNameByComponentId(const std::string& id);
  bool isLoaded() const {
    return loaded;
  }


  /**
   * @brief This function is fill the limComponentNameFileNameMap data structure.
   * @parameter listOfInputFile the list of string with the language asg names.
   */
  void fillComponentList (std::list<std::string> listOfInputFile);
  
};

}
#endif /* LANGUAGEFACTORY_H_ */
