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

#include <sstream>
#include <csi/inc/PropertyData.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <csi/inc/messages.h>

using namespace std;
using namespace common;

namespace columbus
{

PropertyData::PropertyData()
  : header()
{
}

PropertyData::~PropertyData()
{
  header.clear();
}

bool PropertyData::add(const std::string& key, const std::string& value)
{
  return header.insert(make_pair(key, value)).second;
}

bool PropertyData::addBool(const std::string& key, bool value)
{
  return header.insert(make_pair(key, value ? csih_True : csih_False)).second;
}

bool PropertyData::addInt(const std::string& key, int value)
{
  return header.insert(make_pair(key, common::toString(value))).second;
}

bool PropertyData::get(const std::string& key, std::string& value) const
{
  map<string, string>::const_iterator it = header.find(key);
  if (it != header.end()) 
    value = it->second;

  return it != header.end();
}

bool PropertyData::getBool(const std::string& key, bool& value) const
{
  map<string, string>::const_iterator it = header.find(key);
  if (it != header.end())
    value = it->second == csih_True; 

  return it != header.end();
}

bool PropertyData::getInt(const std::string& key, int& value) const
{
  map<string, string>::const_iterator it = header.find(key);
  if (it != header.end())
    return str2int(it->second, value);

  return it != header.end();
}


void PropertyData::save(io::BinaryIO &binIo) const
{
  binIo.writeUInt4((unsigned int)header.size()); 
  for (map<string, string>::const_iterator it = header.begin(); it != header.end(); ++it) {
    binIo.writeShortString(it->first.c_str());
    binIo.writeShortString(it->second.c_str());
  }
}
    
void PropertyData::load(io::BinaryIO &binIo)
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

columbus::HeaderDataTypeKind PropertyData::getType() const
{
  return hdkPropertyData;
}

std::string PropertyData::toString() const
{
  std::stringstream dumpstream;
  dumpstream << "PropertyData:\n";
  for (map<string, string>::const_iterator it = header.begin(); it != header.end(); ++it)
    dumpstream << "  Key:[" << it->first << "]  Value:[" << it->second << "]\n";
  
  return dumpstream.str();
}

const string PropertyData::csih_True = "1";
const string PropertyData::csih_False = "0";

const string PropertyData::csih_Type = "Type";
const string PropertyData::csih_BinaryVersion = "BinaryVersion";
const string PropertyData::csih_APIVersion = "APIVersion";
const string PropertyData::csih_FullAnalysis = "FullAnalysis";
const string PropertyData::csih_SchemaFilter = "SchemaFilter";
const string PropertyData::csih_PrecompiledHeader = "PrecompiledHeader";
const string PropertyData::csih_UsePrecompiledHeader = "UsePrecompileHeader";
const string PropertyData::csih_NumOfIncrLinked = "NumberOfIncrLinked";
const string PropertyData::csih_PreanalyzedIncludesUsed = "PreanalyzedIncludesUsed";
const string PropertyData::csih_OriginalLocation = "OriginalLocation";
const string PropertyData::csih_PsiKind = "PsiKind";
const string PropertyData::csih_Language = "Language";

} /// END of namespace 'columbus'


