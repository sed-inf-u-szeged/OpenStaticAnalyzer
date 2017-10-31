/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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

#include "../inc/RefDistributorStrTable.h"

namespace columbus {

  RefDistributorStrTable::RefDistributorStrTable(const unsigned buckets)
    :StrTable(buckets), mapOfRef(), emptyReference(*this, 0) 
  {
  }

  RefDistributorStrTable::~RefDistributorStrTable()
  {
    clearRefMap();
  }

  RefDistributorStrTable& RefDistributorStrTable::operator=(const RefDistributorStrTable& rhs)
  {
    //call the super
    StrTable::operator=(rhs);
    for ( StringRefMap::const_iterator it = rhs.mapOfRef.begin(); it != rhs.mapOfRef.end(); ++it ) {
      StringReference* pNewReference = new StringReference(*this,it->first);
      mapOfRef.insert(std::pair<Key,StringReference*>(it->first,pNewReference));
    }
    return *this;
  }

  const StringReference* RefDistributorStrTable::setStr(const std::string& s, StrType type)
  {
   Key strKey = StrTable::set(s,type);
   return getRefByKey(strKey);
  }

  const StringReference* RefDistributorStrTable::getRefByKey(Key strKey)
  {
    if (strKey == 0) 
      return &emptyReference;
      
    StringRefMap::const_iterator it = mapOfRef.find(strKey);
     if (it != mapOfRef.end()) {
      return it->second;
    } else {
      StringReference* pNewReference = new StringReference(*this, strKey);
      mapOfRef.insert(std::make_pair(strKey,pNewReference));
      return pNewReference;
    }
    return NULL;
  }

  void RefDistributorStrTable::load(columbus::io::BinaryIO& file)
  {
    clearRefMap();
    StrTable::load(file);
  }

  void RefDistributorStrTable::loadWithKeepingTheRefMap(columbus::io::BinaryIO& file)
  {
    StrTable::load(file);
  }

  void RefDistributorStrTable::clearRefMap()
  {
     while ( mapOfRef.begin() != mapOfRef.end() ) {
      StringReference* pReference = mapOfRef.begin()->second;
      delete pReference;
      mapOfRef.erase(mapOfRef.begin());
    }
  }
  
  /*------------------StringReference----------------------------------------*/
  Key StringReference::getKey() const
  {
    return stringKey;
  }

  const std::string& StringReference::get() const
  {
    return rStrTable.get(stringKey);
  }

  RefDistributorStrTable& StringReference::getTable() const
  {
    return rStrTable;
  }

  StringReference::StringReference(RefDistributorStrTable& rStrTable, Key stringKey)
    : rStrTable(rStrTable)
    , stringKey(stringKey)
  {
  }

  void StringReference::copy (const StringReference*& pLeft, const StringReference* pRight)
  {
    if ((&pLeft->rStrTable) == (&pRight->rStrTable))
      pLeft = pRight;
    else 
      pLeft = pLeft->rStrTable.setStr( pRight->get());
  }
}
