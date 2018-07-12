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

#include "common.h"
#include <string>
#include <map>

namespace columbus { namespace dcf {

class LanguageFactory {

protected:
  bool loaded;
  std::map<std::string, Factory*> factories;
  std::map<std::string, std::string> limComponentNameFileNameMap;
 
  
  std::map<std::string, std::size_t> hashCodes;

public:
  LanguageFactory();
  virtual ~LanguageFactory();

  const std::map<std::string, std::string>& getLimComponentNameFileNameMap() const;
  void loadComponentByComponentID(const std::string& componentID);
  Factory* getByComponentID(const std::string& component) ;

  void loadComponent(const std::string& fname, bool deleteFiltered=false, unsigned long long* hash = NULL , std::string* componentID = NULL);
  
public:

#ifdef GENEALOGY
  void load(columbus::genealogy::System& system, bool deleteFiltered=false) ;
#endif


  std::string getFileNameByComponentId(const std::string& id);
  void release() ;

  LanguageFactory& operator=(LanguageFactory& lf) ;

  Factory* operator()(const std::string& component) ;
  bool isLoaded() const {return loaded;}

  std::size_t calculateHash(const Factory* factory, const std::string& name);

  /**
   * @brief This function is fill the limComponentNameFileNameMap data structure.
   * @parameter listOfInputFile the list of string with the language asg names.
   */
  void fillComponentList (std::list<std::string> listOfInputFile);

};

}}
#endif /* LANGUAGEFACTORY_H_ */
