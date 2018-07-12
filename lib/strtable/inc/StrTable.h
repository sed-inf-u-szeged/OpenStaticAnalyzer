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

#ifndef _STRTABLE_H
#define _STRTABLE_H

#include <map>
#include <string>
#include <vector>
#include <cstdio>

namespace columbus {

  namespace io {
    class BinaryIO;
  }

typedef unsigned Key;   // must be 32bit at least

class StrTable
{
  public:
    enum StrType {
      strDefault, strTmp, strToSave
    };

    StrTable(const unsigned buckets = 511);
    StrTable(const StrTable& st);
    
    virtual ~StrTable();

    
    StrTable& operator=(const StrTable& rhs);

    // Gives back the number of buckets.
    unsigned getNumberOfBuckets() const;

    // Inserts the given string into the string table and gives back a "unique" key.
    Key set(const char* s, StrType type = strDefault);

    Key set(const char* s, unsigned length, StrType type = strDefault);
    
    // Inserts the given string into the string table and gives back a "unique" key.
    Key set(const std::string& s, StrType type = strDefault);
    
    // Sets the type of the given string. If the given string does not exist in the table than it inserts it 
    // with a given type. 
    void setType(const char *s, StrType type);

    // Sets the type of the string stored in the string table with the given "unique" key. 
    void setType(const Key key, StrType type);

    // Gives back the "unique" key of the given string if it is in the string table. Otherwise it returns 0.
    Key get(const char* s) const;
    Key get(const char* s, unsigned length) const;

    // Gives back the "unique" key of the given string if it is in the string table. Otherwise it returns 0.
    Key get(const std::string& s) const;
    
    // Gives back the string stored in the string table with the given "unique" key or an empty string in case 
    // there is no string in the table with that key.
    const std::string& get(const Key key) const;

    // Saves the string table to the given file. The file must be already opened for writing!!!!!!!!!!!
    void save(FILE* file, StrType filterType = strDefault) const;

    // Saves the string table to the given file.
    void save(columbus::io::BinaryIO& file, StrType filterType = strDefault) const;

    // Loads the string table from the given file. All data exist in the current table will be lost.
    // The file must be already opened for reading!!!!!!!!!!!
    void load(FILE* file);

    // Loads the string table from the given file. All data exist in the current table will be lost.
    void load(columbus::io::BinaryIO& file);

    // Returns true if the given key is valid or false if it is invalid. 
    static bool getIsValid(Key key) { return key != 0; }

    //  Prints out the content of the table.
    void dump();
    
  protected:
    typedef std::map<Key, std::pair<std::string, StrType> > Map;

    unsigned                       no_buckets;           // Number of buckets
    std::vector<unsigned short>    count;                // Internal counter for each bucket 
    std::vector<Map>               str_table;            // The string table 


    unsigned short hash(const char* pString) const;     
    unsigned short hash(const char* pString, unsigned long length) const;     
    Key get(const char* s, std::size_t length, unsigned short hash_value, unsigned bucket_index) const;

    void copy(const StrTable& st); 
#ifdef DOSTAT    
    struct table_stat {
      unsigned long      element_count;
      unsigned long      number_of_search;
      unsigned long long number_of_it;
    };
    
    table_stat* statistic_counter;
#endif

};

} // namespace columbus

#endif
