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

#include "../inc/common.h"
#include "../inc/LanguageFactory.h"

#include <boost/functional/hash.hpp>
#include <Exception.h>

using namespace std;

namespace columbus { namespace dcf {

  LanguageFactory::LanguageFactory()
    : loaded(false)
    , factories()
    , limComponentNameFileNameMap()
    , hashCodes()
  {}

  LanguageFactory::~LanguageFactory() {
    release();
  }

  void LanguageFactory::loadComponent(const std::string& fname, bool deleteFiltered, unsigned long long* hash, std::string* componentID /*=NULL*/) {
    columbus::RefDistributorStrTable *stt=new columbus::RefDistributorStrTable();
    Factory* factory = new Factory(*stt);

#if defined SCHEMA_JAVA || defined SCHEMA_PYTHON
    columbus::CsiHeader header;
    factory->load(fname, header);

#elif defined SCHEMA_CSHARP || defined SCHEMA_JAVASCRIPT
    std::list<HeaderData*> headerList;
    columbus::PropertyData header;
    headerList.push_back(&header);
    factory->load(fname, headerList);

#endif

    if (componentID) {
      if (!header.get(header.csih_OriginalLocation,*componentID)) {
        *componentID = fname;
        common::changePath(*componentID, config.changepathfrom, config.changepathto);
      }

      limComponentNameFileNameMap[*componentID] = fname;
    }
    factory->initializeFilter();
    boost::filesystem::path f(fname);
    f=boost::filesystem::change_extension(f, FILTER_FILE_EXTENSION);
    if (common::fileTimeCmp(f.string(), fname) == -1) {
      common::WriteMsg::write(CMSG_FILTER_FILE_OLD, f.string().c_str());
    } else {
      if(common::pathFileExists(f.string().c_str(), false))
      {
        factory->loadFilter(f.string());
      }
    }

    if(hash) {
      unsigned long long calc_hash = calculateHash(factory, fname);
      if(calc_hash != *hash)
        throw columbus::Exception(COLUMBUS_LOCATION, CMSG_EX_HASH_CODE_MISMATCH(fname));
    }

    factories.insert(make_pair(fname, factory));
    loaded=true;

  }

#ifdef GENEALOGY
  void LanguageFactory::load(columbus::genealogy::System& system, bool deleteFiltered) {
    for (columbus::genealogy::ListIterator<columbus::genealogy::Component> iter = system.getComponentsListIteratorBegin(); iter != system.getComponentsListIteratorEnd(); ++iter) {
      const columbus::genealogy::Component& cmp = *iter;
      unsigned long long code = cmp.getCode();
      loadComponent(cmp.getLocation(), deleteFiltered, &code);
      this->operator()(cmp.getLocation());
    }
    loaded=true;
  }
#endif

  void LanguageFactory::release() {
    std::map<std::string, Factory*>::iterator iter=factories.begin();
    while (iter!=factories.end()) {
      Factory* factory=(Factory*)(*iter).second;
      delete &(factory->getStringTable());
      delete factory;
      iter++;
    }
    factories.clear();
    loaded=false;
  }

  LanguageFactory& LanguageFactory::operator=(LanguageFactory& lf) {
    release();
    factories=lf.factories;
    lf.factories.clear();
    loaded=lf.loaded;
    lf.loaded=false;
    return *this;
  }

  Factory* LanguageFactory::operator()(const std::string& component) {
    std::map<std::string, Factory*>::iterator iter=factories.find(component);
    if (iter!=factories.end())
      return (*iter).second;
    return NULL;
  }

  std::size_t LanguageFactory::calculateHash(const Factory* factory, const std::string& name) {
    size_t hash = 0;
#ifdef GENEALOGY
    std::map<std::string, std::size_t>::const_iterator hashCodeIt =  hashCodes.find(name);
    if(hashCodeIt != hashCodes.end()) {
      return hashCodeIt->second;
    }
    Factory::ConstIterator nodesIt = factory->constIterator();
    while(nodesIt.hasNext()) {
      const Base& node = nodesIt.next();
      boost::hash_combine(hash, node.getNodeKind());
    }
    hashCodes.insert(make_pair(name, hash));
#endif
    return hash;
  }

  void LanguageFactory::loadComponentByComponentID( const std::string& componentID ) {


    std::string& fileName = limComponentNameFileNameMap[componentID];

    loadComponent(fileName);
  }

  Factory* LanguageFactory::getByComponentID( const std::string& componentID )
  {
    return operator()(getFileNameByComponentId(componentID));
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
#ifdef SCHEMA_JAVA
    for (std::list<std::string>::iterator it = listOfInputFile.begin();it != listOfInputFile.end();++it) {
      columbus::CsiHeader header;
      columbus::RefDistributorStrTable stt;
      std::string componentID ="";

      Factory factory(stt);
      factory.load(*it, header);

      if (!header.get(header.csih_OriginalLocation,componentID)) {
        componentID = *it;
        common::changePath(componentID, config.changepathfrom, config.changepathto);
      }

      limComponentNameFileNameMap[componentID] = *it;
    }
#endif
  }

}}

