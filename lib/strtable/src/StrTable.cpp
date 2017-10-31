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

#include <cstring>
#include <cstdlib>
#include <common/inc/WriteMessage.h>
#include <io/inc/IO.h>
#include "../inc/messages.h"
#include "../inc/StrTable.h"

static_assert(sizeof(unsigned) >= 4, "Size of the 'unsigned' is expected to be greater than or equal to 4 bytes!");
static_assert(sizeof(unsigned short) >= 2, "Size of the 'unsigned short' is expected to be greater than or equal to 2 bytes!");

#define CHECKIO(instr, error_msg)    \
if (!(instr)) {  \
    common::WriteMsg::writeToErr( common::WriteMsg::mlError, error_msg); \
    abort(); \
  } \

namespace columbus {

unsigned char random_numbers[] =  /* Table from p. 678.*/
{    /* Pseudorandom Permutation of the Integers 0 through 255: */
     1, 14,110, 25, 97,174,132,119,138,170,125,118, 27,233,140, 51,
    87,197,177,107,234,169, 56, 68, 30,  7,173, 73,188, 40, 36, 65,
    49,213,104,190, 57,211,148,223, 48,115, 15,  2, 67,186,210, 28,
    12,181,103, 70, 22, 58, 75, 78,183,167,238,157,124,147,172,144,
   176,161,141, 86, 60, 66,128, 83,156,241, 79, 46,168,198, 41,254,
   178, 85,253,237,250,154,133, 88, 35,206, 95,116,252,192, 54,221,
   102,218,255,240, 82,106,158,201, 61,  3, 89,  9, 42,155,159, 93,
   166, 80, 50, 34,175,195,100, 99, 26,150, 16,145,  4, 33,  8,189,
   121, 64, 77, 72,208,245,130,122,143, 55,105,134, 29,164,185,194,
   193,239,101,242,  5,171,126, 11, 74, 59,137,228,108,191,232,139,
     6, 24, 81, 20,127, 17, 91, 92,251,151,225,207, 21, 98,113,112,
    84,226, 18,214,199,187, 13, 32, 94,220,224,212,247,204,196, 43,
   249,236, 45,244,111,182,153,136,129, 90,217,202, 19,165,231, 71,
   230,142, 96,227, 62,179,246,114,162, 53,160,215,205,180, 47,109,
    44, 38, 31,149,135,  0,216, 52, 63, 23, 37, 69, 39,117,146,184,
   163,200,222,235,248,243,219, 10,152,131,123,229,203, 76,120,209
};

StrTable::StrTable(const unsigned buckets) : no_buckets(buckets), count(), str_table()
#ifdef DOSTAT
  , statistic_counter(NULL)
#endif  
{
  str_table.resize(no_buckets);
  count.resize(no_buckets, 1);

#ifdef DOSTAT
  statistic_counter = (table_stat*)calloc(no_buckets , sizeof(table_stat));
  if (!statistic_counter) {
    common::WriteMsg::writeToErr( CMSG_ERROR_MEMORY_ALLOCATION);
    abort();
  }
#endif
}

StrTable::StrTable(const StrTable& st) : no_buckets(), count(), str_table()
#ifdef DOSTAT
  , statistic_counter(NULL)
#endif  
{
  copy(st);
}

StrTable::~StrTable()
{
#ifdef DOSTAT
  for (unsigned i = 0; i < no_buckets; i++)
    fprintf(stderr, "%03d[noe:%08lu nos:%08lu noit:%020llu avg:%.2lf]\n", i, statistic_counter[i].element_count, statistic_counter[i].number_of_search, statistic_counter[i].number_of_it, (double)statistic_counter[i].number_of_it / statistic_counter[i].number_of_search);

  free(statistic_counter);
#endif
}

void StrTable::copy(const StrTable& st)
{
  no_buckets = st.no_buckets;

#ifdef DOSTAT
  free(statistic_counter);

  statistic_counter = (table_stat*)calloc(no_buckets , sizeof(table_stat));
  if (!statistic_counter) {
    common::WriteMsg::writeToErr( CMSG_ERROR_MEMORY_ALLOCATION);
    abort();
  }
#endif

  count.clear();
  count.resize(no_buckets);

  str_table.clear();
  str_table.resize(no_buckets);

  for (unsigned i = 0; i < no_buckets; i++) {
    count[i] = st.count[i];

    for (Map::const_iterator it = st.str_table[i].begin(); it != st.str_table[i].end(); ++it) {
      str_table[i].insert(Map::value_type(it->first, std::make_pair(it->second.first, it->second.second)));
    }
  }
}

StrTable& StrTable::operator=(const StrTable& rhs)
{
  copy(rhs);
  return *this;
}

unsigned StrTable::getNumberOfBuckets() const
{
  return no_buckets;
}

/* Hashing function described in                   */
/* "Fast Hashing of Variable-Length Text Strings," */
/* by Peter K. Pearson, CACM, June 1990.           */
unsigned short StrTable::hash(const char* string) const
{
  unsigned hash_hi  = 0;
  unsigned hash_low = 0;
  unsigned i   = 0;
  const unsigned char* v = (const unsigned char*)string;

  if(string == NULL) 
    return 0;
  
  if(string[0] == 0) 
    return 0;

  while (v[i] != 0)
    hash_hi = random_numbers[hash_hi ^ v[i++]];

  // Increment the first character by one and recalculate the hash
  hash_low = random_numbers[hash_low ^ ((v[0] + 1) & 0xFF)];
  i = 1;
  while (v[i] != 0)
    hash_low = random_numbers[hash_low ^ v[i++]];

  return (hash_hi << 8) | hash_low;
}

unsigned short StrTable::hash(const char* string,unsigned long length) const
{
  unsigned hash_hi  = 0;
  unsigned hash_low = 0;
  unsigned i   = 0;
  const unsigned char* v = (const unsigned char*)string;

  if(string == NULL) 
    return 0;
  
  if(length == 0) 
    return 0;
    
  while (i < length)
    hash_hi = random_numbers[hash_hi ^ v[i++]];

  // Increment the first character by one and recalculate the hash
  hash_low = random_numbers[hash_low ^ ((v[0] + 1) & 0xFF)];
  i = 1;
  while (i < length)
    hash_low = random_numbers[hash_low ^ v[i++]];

  return (hash_hi << 8) | hash_low;
}

Key StrTable::set(const std::string& s, StrType type)
{
  return set(s.c_str(), (unsigned)s.size(), type);
}

Key StrTable::set(const char* s, unsigned length, StrType type)
{
  if (s == NULL)
    return 0;

  if(length == 0)
    return 0;

  Key key;
  unsigned short hash_value = hash(s, length);
  unsigned bucket_index = hash_value % no_buckets;

  // If the string does not exists in the table we insert it
  if (!(key = get(s,length, hash_value, bucket_index))) {

    key = ((Key)hash_value << 16) | count[bucket_index]++;

    if (count[bucket_index] == 0xFFFF)
      common::WriteMsg::writeToErr( CMSG_BUCKET_IS_FULL, bucket_index);


    str_table[bucket_index].insert(Map::value_type(key, std::make_pair(std::string(s,length), type)));

#ifdef DOSTAT
    statistic_counter[bucket_index].element_count++;
#endif
  }
  return key;
}

Key StrTable::set(const char* s, StrType type)
{
  if (s == NULL)
    return 0;

  if (!s[0])
    return 0;

  Key key;
  unsigned short hash_value = hash(s);
  unsigned bucket_index = hash_value % no_buckets;

  // If the string does not exists in the table we insert it
  if (!(key = get(s, strlen(s), hash_value, bucket_index))) {

    key = ((Key)hash_value << 16) | count[bucket_index]++;

    if (count[bucket_index] == 0xFFFF)
      common::WriteMsg::writeToErr( CMSG_BUCKET_IS_FULL, bucket_index);


    str_table[bucket_index].insert(Map::value_type(key, std::make_pair(s, type)));

#ifdef DOSTAT
    statistic_counter[bucket_index].element_count++;
#endif
  }

  return key;
}

void StrTable::setType(const char *s, StrType type)
{
  if (s == NULL)
    return;

  if (!s[0])
    return;

  Key key;
  unsigned short hash_value = hash(s);
  unsigned bucket_index = hash_value % no_buckets;

  // If the string does not exists in the table we insert it
  if (!(key = get(s, strlen(s), hash_value, bucket_index))) {

    key = ((Key)hash_value << 16) | count[bucket_index]++;

    if (count[bucket_index] == 0xFFFF)
      common::WriteMsg::writeToErr( CMSG_BUCKET_IS_FULL, bucket_index);

    str_table[bucket_index].insert(Map::value_type(key, std::make_pair(s, type)));

#ifdef DOSTAT
    statistic_counter[bucket_index].element_count++;
#endif
  } else    // Just modify the type of it
    str_table[bucket_index].find(key)->second.second = type;
}

void StrTable::setType(const Key key, StrType type)
{
  unsigned bucket_index = (key >>16) % no_buckets;

  Map::iterator it = str_table[bucket_index].find(key);
  if (it != str_table[bucket_index].end())
    it->second.second = type;
}

Key StrTable::get(const char* s, size_t length, unsigned short hash_value, unsigned bucket_index) const
{
  // It does not check the s because it is already checked in StrTable::set or in StrTable::get.
#ifdef DOSTAT
  statistic_counter[bucket_index].number_of_search++;
#endif

  Map::const_iterator from = str_table[bucket_index].lower_bound((Key)hash_value << 16);
  Map::const_iterator to = str_table[bucket_index].upper_bound(((Key)hash_value << 16) + 0xFFFF);

  for(Map::const_iterator it = from; it != to; ++it) {
#ifdef DOSTAT
    statistic_counter[bucket_index].number_of_it++;
#endif
    if ((it->second.first.length() == length)&&(it->second.first.compare(0,length,s,length) == 0)) {
      return it->first;
    }
  }
  return 0;
}

Key StrTable::get(const std::string& s) const
{
  return get(s.c_str(), (unsigned)s.size());
}

Key StrTable::get(const char* s) const
{
  if (s == NULL)
    return 0;

  if (!s[0])
    return 0;

  unsigned short hash_value = hash(s);
  unsigned bucket_index = hash_value % no_buckets;

  return get(s, strlen(s), hash_value, bucket_index);
}

Key StrTable::get(const char* s, unsigned length) const
{
  if (s == NULL)
    return 0;

  if (length == 0)
    return 0;

  unsigned short hash_value = hash(s, length);
  unsigned bucket_index = hash_value % no_buckets;

  return get(s, length, hash_value, bucket_index);

}

const std::string& StrTable::get(Key key) const
{
  static std::string empty_string;
  unsigned bucket_index = (key >>16) % no_buckets;

  Map::const_iterator it = str_table[bucket_index].find(key);
  if (it != str_table[bucket_index].end())
    return it->second.first;

  return empty_string;
}

void StrTable::save(FILE* file, StrType filterType) const
{
  CHECKIO(fwrite("STRTBL", 6, 1, file), CMSG_WRITE_ERR);     // ID string (6)
  CHECKIO(fwrite(&no_buckets, 4, 1, file), CMSG_WRITE_ERR);  // Number of buckets (4)

  for (unsigned i = 0; i < no_buckets; i++) {
    unsigned short ic = count[i];
    CHECKIO(fwrite(&ic, 2, 1, file), CMSG_WRITE_ERR);        // no_buckets x Internal counter (2)
  }

  // write out each element
  for (unsigned j = 0; j < no_buckets; j++) {
    const Map& current_map = str_table[j];

    for (Map::const_iterator it = current_map.begin(); it != current_map.end(); ++it) {
      if (filterType == strTmp) {      // In tmp mode nodes with tmp flag will be skipped.
        if (it->second.second == strTmp)
          continue;
      } else
        if (filterType == strToSave)  // In save mode only nodes with save flag will be written out.
          if (it->second.second != strToSave)
            continue;

      CHECKIO(fwrite(&it->first, 4, 1, file), CMSG_WRITE_ERR);   // The key (4)
      unsigned str_size = (unsigned)it->second.first.size();
      CHECKIO(fwrite(&str_size, 4, 1, file), CMSG_WRITE_ERR);    // Size of the string (4)

      CHECKIO(fwrite(it->second.first.c_str(), str_size, 1, file), CMSG_WRITE_ERR); // Characters of the string (n)

    }
  }

  // Write out the end of StringTable sign
  unsigned long end_sign = 0;
  CHECKIO(fwrite(&end_sign, 4, 1, file), CMSG_WRITE_ERR);    
 
}

void StrTable::save(columbus::io::BinaryIO& file, StrType filterType) const
{
  file.writeData("STRTBL", 6);
  file.writeUInt4(no_buckets);

  for (unsigned i = 0; i < no_buckets; i++) {
    unsigned short ic = count[i];
    file.writeUShort2(ic);  // no_buckets x Internal counter (2)
  }

  for (unsigned j = 0; j < no_buckets; j++) {
    const Map& current_map = str_table[j];

    for (Map::const_iterator it = current_map.begin(); it != current_map.end(); ++it) {
      if (filterType == strTmp) {      // In tmp mode nodes with tmp flag will be skipped.
        if (it->second.second == strTmp)
          continue;
      } else
        if (filterType == strToSave)  // In save mode only nodes with save flag will be written out.
          if (it->second.second != strToSave)
            continue;

      file.writeUInt4(it->first);
      size_t str_size = it->second.first.size();
      file.writeUInt4((unsigned)str_size);
      file.writeData(it->second.first.c_str(), str_size);
    }
  }
    // Write out the end of StringTable sign
  file.writeUInt4(0);
}

void StrTable::load(FILE* file)
{
  char id[6] = {'M', 'A', 'G', 'I' , 'C', 0 };
  CHECKIO(fread(id, 6, 1, file), CMSG_READ_ERR);    // ID string
  if (strncmp(id, "STRTBL", 6)) {
    common::WriteMsg::writeToErr( CMSG_WRONG_FILE_FORMAT);
    return;
  }

  CHECKIO(fread(&no_buckets, 4, 1, file), CMSG_READ_ERR);
  str_table.clear();
  str_table.resize(no_buckets);

  count.clear();
  count.resize(no_buckets, 0);

#ifdef DOSTAT
  free(statistic_counter);

  statistic_counter = (table_stat*)calloc(no_buckets , sizeof(table_stat));
  if (!statistic_counter) {
    common::WriteMsg::writeToErr( CMSG_ERROR_MEMORY_ALLOCATION);
    abort();
  }
#endif

  for (unsigned i = 0; i < no_buckets; i++) {
    unsigned short ic;
    CHECKIO(fread(&ic, 2, 1, file), CMSG_READ_ERR);     // no_buckets x Internal counter (2)
    count[i] = ic;
  }
  
  while (true) {
    Key key = 0;

    CHECKIO(fread(&key, 4, 1, file), CMSG_READ_ERR);    // The key (4)
    
    // If the key is zero then we reached the end of the string table
    if (!key) 
      break;

    unsigned str_size;
    CHECKIO(fread(&str_size, 4, 1, file), CMSG_READ_ERR); // Size of the string (4)

    char* buffer = (char*)calloc(1, str_size + 1);
    if (!buffer) {
      common::WriteMsg::writeToErr( CMSG_LOAD_ERROR);
      abort();
    }

    CHECKIO(fread(buffer, str_size, 1, file), CMSG_READ_ERR);  // Characters of the string (n)
    unsigned bucket_index = (key >>16) % no_buckets;
    str_table[bucket_index].insert(Map::value_type(key, std::make_pair(std::string(buffer, str_size), strDefault)));
    
    free(buffer);
  }
}

void StrTable::load(columbus::io::BinaryIO& file)
{
  char id[6] = {'M', 'A', 'G', 'I' , 'C', 0 };
  file.readData(id, 6);
  if (strncmp(id, "STRTBL", 6)) {
    common::WriteMsg::writeToErr( CMSG_WRONG_FILE_FORMAT);
    return;
  }

  no_buckets = file.readUInt4();
  str_table.clear();
  str_table.resize(no_buckets);

  count.clear();
  count.resize(no_buckets, 0);

#ifdef DOSTAT
  free(statistic_counter);

  statistic_counter = (table_stat*)calloc(no_buckets , sizeof(table_stat));
  if (!statistic_counter) {
    common::WriteMsg::writeToErr( CMSG_ERROR_MEMORY_ALLOCATION);
    abort();
  }
#endif

  for (unsigned i = 0; i < no_buckets; i++) {
    count[i] = file.readUShort2();  // no_buckets x Internal counter (2)
  }

  while (true) {
    Key key;
    key = file.readUInt4();
    
    // If the key is zero then we reached the end of the string table
    if (!key) 
      break;

    unsigned str_size = file.readUInt4(); // Size of the string (4)

    char* buffer = (char*)calloc(1, str_size + 1);
    if (!buffer) {
      common::WriteMsg::writeToErr( CMSG_LOAD_ERROR);
      abort();
    }

    file.readData(buffer, str_size); // Characters of the string (n)

    unsigned bucket_index = (key >>16) % no_buckets;
    str_table[bucket_index].insert(Map::value_type(key, std::make_pair(std::string(buffer, str_size), strDefault)));

    free(buffer);
  }
}

void StrTable::dump()
{
  unsigned i = 0;
  Map::size_type total_counter = 0;
  for (std::vector<Map>::const_iterator it = str_table.begin(); it != str_table.end(); ++it) {
    common::WriteMsg::write( CMSG_BUCKET_TOTAL_NUMBER, i++, it->size());
    for (Map::const_iterator sit = it->begin(); sit != it->end(); ++sit)
      printf("[%X]:[%s][%d]\n", sit->first, sit->second.first.c_str(),  sit->second.second);
    total_counter += it->size();
  }
  
  for (unsigned i = 0; i < no_buckets; ++i) {
    printf("Counter[%u]:%hu\n", i, count[i]);
  }
  
  common::WriteMsg::write( CMSG_TOTAL_COUNT, total_counter);
}

} // columbus namespace
