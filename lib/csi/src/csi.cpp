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

#include <cstdlib>
#include <cstring>
#include <cstdio>

#include <csi/inc/csi.h>
#include <csi/inc/messages.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>

using namespace std;
using namespace common;

namespace columbus {

CsiHeader::CsiHeader() : header()
{
}

bool CsiHeader::add(const std::string& key, const std::string& value)
{
  return header.insert(make_pair(key, value)).second;
}

bool CsiHeader::addBool(const std::string& key, bool value)
{
  return header.insert(make_pair(key, value ? csih_True : csih_False)).second;
}

bool CsiHeader::addInt(const std::string& key, int value)
{
  return header.insert(make_pair(key, toString(value))).second;
}

bool CsiHeader::get(const std::string& key, std::string& value) const
{
  map<string, string>::const_iterator it = header.find(key);
  if (it != header.end()) 
    value = it->second;

  return it != header.end();
}

bool CsiHeader::getBool(const std::string& key, bool& value) const
{
  map<string, string>::const_iterator it = header.find(key);
  if (it != header.end())
    value = it->second == csih_True ? true : false; 

  return it != header.end();
}

bool CsiHeader::getInt(const std::string& key, int& value) const
{
  map<string, string>::const_iterator it = header.find(key);
  if (it != header.end())
    return str2int(it->second, value);

  return it != header.end();
}


void CsiHeader::write(io::BinaryIO &binIo) const
{
  binIo.writeUInt4((unsigned int)header.size());
  
  for (map<string, string>::const_iterator it = header.begin(); it != header.end(); ++it) {
    binIo.writeShortString(it->first.c_str());
    binIo.writeShortString(it->second.c_str());
  }
}
    
void CsiHeader::read(io::BinaryIO &binIo)
{
  unsigned num = binIo.readUInt4();
  
  for (unsigned i = 0; i < num; i++) {
    string key;
    string value;
        
    binIo.readShortString(key);
    binIo.readShortString(value);

    header.insert(std::make_pair(key, value));
  }
}


const string CsiHeader::csih_True = "1";
const string CsiHeader::csih_False = "0";
const string CsiHeader::csih_Type = "Type";
const string CsiHeader::csih_BinaryVersion = "BinaryVersion";
const string CsiHeader::csih_APIVersion = "APIVersion";
const string CsiHeader::csih_FullAnalysis = "FullAnalysis";
const string CsiHeader::csih_SchemaFilter = "SchemaFilter";
const string CsiHeader::csih_PrecompiledHeader = "PrecompiledHeader";
const string CsiHeader::csih_UsePrecompiledHeader = "UsePrecompileHeader";
const string CsiHeader::csih_NumOfIncrLinked = "NumberOfIncrLinked";
const string CsiHeader::csih_PreanalyzedIncludesUsed = "PreanalyzedIncludesUsed";
const string CsiHeader::csih_OriginalLocation = "OriginalLocation";
const string CsiHeader::csih_PsiKind = "PsiKind";
const string CsiHeader::csih_Language = "Language";
const string CsiHeader::csih_ChangesetID = "ChangesetID";

} // END of namespace 'columbus'
