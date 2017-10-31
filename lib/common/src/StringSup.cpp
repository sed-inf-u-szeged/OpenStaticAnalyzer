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
#include <iostream>
#include <cstring>
#include <string>

#include <boost/algorithm/string.hpp>

#include <common/inc/StringSup.h>
#include <common/inc/PlatformDependentDefines.h>
#include <common/inc/messages.h>
#include "Exception.h"

using namespace std;

namespace common {

  bool case_insensitive_compare::operator()(const string& a, const string& b) const
  {
    return boost::algorithm::lexicographical_compare(a, b, boost::is_iless());
  }

  /**
  * \brief Converts integer or floating type string to number.
  * \param str [in]  The string being converted.
  * \param num [out] The converted number if str is a number, undefined ortherwise.
  * \return          Returns true if it can be converted to a number.
  */
  template <typename T1, typename T2>
  bool str2num(T1 str, T2& num)
  {
    std::stringstream ss(str);
    ss >> num;
    if (ss.fail() || !ss.eof())
      return false;
    else
      return true;
  }

  bool str2int(const std::string& str, int& num)
  {
    return str2num(str, num);
  }

  bool str2int(const char* str, int& num)
  {
    return str2num(str, num);
  }

  int str2int(const string& str)
  {
    int num;
    if (str2num(str, num))
      return num;
    else
      throw columbus::Exception(COLUMBUS_LOCATION, CMSG_EX_CANNOT_BE_CONVERTED(str));
  }

  unsigned str2unsigned(const string& str)
  {
    unsigned num;
    if (str2num(str, num))
      return num;
    else
      throw columbus::Exception(COLUMBUS_LOCATION, CMSG_EX_CANNOT_BE_CONVERTED(str));
  }

  bool str2unsignedlong(const string& str, unsigned long& num)
  {
    return str2num(str, num);
  }

  bool str2double(const std::string& str, double& num)
  {
    return str2num(str, num);
  }

  char* stringLower(char *str)
  {
    if (!str)
      return str;

    for (unsigned i = 0; str[i]; i++)
      if ('A' <= str[i] && str[i] <= 'Z')
        str[i] = str[i] - 'A' + 'a';

    return str;
  }

  string stringLower(string& str)
  {
    for (unsigned i = 0; i < str.length(); i++)
      if ('A' <= str[i] && str[i] <= 'Z')
        str[i] += 'a' - 'A';
    return str;
  }

  const string stringLower(const string& str)
  {
    string ret(str);
    for (unsigned i = 0; i < ret.length(); i++)
      if ('A' <= ret[i] && ret[i] <= 'Z')
        ret[i] += 'a' - 'A';
    return ret;
  }

  const string stringUpper(const string& str)
  {
    string ret(str);
    for (unsigned i = 0; i < ret.length(); i++)
      if ('a' <= ret[i] && ret[i] <= 'z')
        ret[i] += 'A' - 'a';
    return ret;
  }

  std::string removeNewline(const std::string& str)
  {
    std::string ret(str);
    unsigned i;
    for (i = 0; i < ret.length() && ret[i] != '\r' && ret[i] != '\n'; i++);
    return ret.substr(0, i);
  }

  bool isQuoted(const std::string& source)
  {
    size_t length=source.length();
    for (size_t i=0; i<length; i++) {
      if (source[i] == CL_PAR_PLUS[0]) {
        if (i!=0 && i!=length-1)
          return false;
      }
      if (i==0 || i==length-1) {
        if (source[i] != CL_PAR_PLUS[0]) 
          return false;
      }
    }
    return true;
  }

  bool caseInsensitiveComp(const string& str1, const string& str2)
  {
    return caseInsensitiveComp(str1.c_str(), str2.c_str());
  }

  bool caseInsensitiveComp(const char* str1, const char* str2)
  {
    if(!str1 || !str2) return false;
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    if (len1 != len2)
      return false;

    unsigned i = 0;
    while (i < len1 && i < len2) {
      if (!( str1[i] == str2[i] || 
            ('A' <= str1[i] && str1[i] <= 'Z' && str1[i] - 'A' + 'a' == str2[i]) ||
            ('A' <= str2[i] && str2[i] <= 'Z' && str2[i] - 'A' + 'a' == str1[i])
           )
         )
        return false;
      i++;
    }

    return true;
  }

  void splitArgs(const char* str1, std::vector<std::string>& out)
  {
    unsigned int first=0;
    unsigned int last=0;
    size_t length=strlen(str1);
    std::string inp(str1);
    bool inQuotes=false;
    while (last<length) {
      if (inQuotes && str1[last] != CL_PAR_PLUS[0]) {
        last++;
        continue;
      } else if (str1[last] == CL_PAR_PLUS[0]) {
        inQuotes=!inQuotes;
        last++;
        continue;
      } else if (str1[last]== ' ') {
        out.push_back(inp.substr(first, last-first));
        do {
          last++;
        } while (str1[last] == ' ' && last<length);
        first=last;
        continue;
      }
      last++;
    }
    if (first<last)
      out.push_back(inp.substr(first, last));
  }

  std::string articulateNumber(long num)
  {
    string s;
    bool neg = false;
    if (num == 0)
      return string("0");
    if (num < 0) {
      neg = true;
      num *= -1;
    }

    while (0 < num) {
      unsigned n = num - num/1000*1000;
      if (num / 1000) {
        if (n == 0) {
          s = ".000" + s;
        } else if (n < 10) {
          s = ".00" + toString(n) + s;
        } else if (n < 100) {
          s = ".0" + toString(n) + s;
        } else {
          s = "." + toString(n) + s;
        }
      } else {
        s = toString(n) + s;
      }
      num /= 1000;
    }

    return (neg?"-":"") + s;
  }


  void split(const string& str, vector<string>& strList, char separator)
  {
    split(str, strList, separator, 0, true);
  }

  void split(const string& str, vector<string>& strList, char separator, unsigned int maxSplits)
  {
    split(str, strList, separator, maxSplits, false);
  }

  void split(const string& str, vector<string>& strList, char separator, unsigned int maxSplits, bool endless)
  {
    size_t dpos = str.find_first_of(separator);
    size_t start = 0;

    while ((endless || maxSplits) && dpos != string::npos) {
      strList.push_back(str.substr(start, dpos - start));
      start = dpos + 1; 
      dpos = str.find_first_of(separator, start);
      --maxSplits;
    }

    if ((endless || maxSplits) && str.length())
      strList.push_back(str.substr(start));
  }

  void split(const std::string& str, std::list<std::string>& strlist, char separator)
  {
    size_t dpos = str.find_first_of(separator);
    size_t start = 0;

    while (dpos != std::string::npos) {
      strlist.push_back(str.substr(start, dpos - start));
      start = dpos + 1; 
      dpos = str.find_first_of(separator, start);
    }

    if (str.length())
      strlist.push_back(str.substr(start));
  }

  std::string removeQuotes(const std::string& s)
  {
    std::string ret = std::string(s);
    std::string::size_type size = ret.length();

    if (size>1) {
      if (ret[size-1]=='"' || ret[size-1]=='`')
        ret.erase(size-1);
      if (ret[0]=='"' || ret[0]=='`')
        ret.erase(0,1);
    }

    return ret;
  }

  std::string replace(const char *str, const char *from, const char *to)
  {
    if(!str || !from || !to) return std::string();
    std::string res;
    std::string source(str);
    size_t size = strlen(from);
    size_t last = 0;
    size_t current = 0;

    while ((current = source.find(from, last)) != std::string::npos) {
      res += source.substr(last, current - last);
      res += to;
      last = current + size;
    }

    if (!last)
      return source;
    else
      return res + source.substr(last, source.size());
  }

  void convertJavaUniqueNameToJniName(string& name)
  {
    size_t pos;
    // remove the generic parameters
    while ((pos = name.find_first_of("<")) != string::npos) {
      name.erase(pos, name.find_first_of(">", pos) - pos + 1);
    }

    // remove the return type
    pos = name.find_first_of("@") + 1;
    name.erase(pos, name.find_first_of("@", pos) - pos);
  }

  /**
  * \brief Converts primitive types to string.
  * \param value [in] The primitive typed value which will be converted.
  * \return           The converted value (in string form).
  */
  template <typename T> const std::string toStringT(T value)
  {
    std::stringstream s;
    s << value;
    return s.str();
  }

  const string toString(const long value) {
    return toStringT(value);
  }

  const string toString(const unsigned long value) {
    return toStringT(value);
  }

  const string toString(const long long value) {
    return toStringT(value);
  }

  const string toString(const int value) {
    return toStringT(value);
  }

  const string toString(const short value) {
    return toStringT(value);
  }

  const string toString(const unsigned long long value) {
    return toStringT(value);
  }

  const string toString(const unsigned value) {
    return toStringT(value);
  }
  
  const string toString(const unsigned short value) {
    return toStringT(value);
  }

  const string toString(const double value) {
    return toStringT(value);
  }

  const string toString(const float value) {
    return toStringT(value);
  }

  const string toString(const char value) {
    return string(1, value);
  }

  const string toString(const bool value) {
    return value ? "true" : "false";
  }

  void trim(std::string& string, const char* whitespaces)
  {
    size_t start = string.find_first_not_of(whitespaces);
    if (start != string::npos) {
      string.erase(0, start);
    } else {
      string.clear();
      return;
    }

    size_t end = string.find_last_not_of(whitespaces);
    if (end != string::npos)
      string.erase(end + 1, string::npos);
  }

  std::string trim(const std::string& string, const char* whitespaces)
  {
    std::string result = string;
    trim(result, whitespaces);
    return result;
  }

  void writeMessage(const char* msg)
  {
    std::cout << msg;
  }

  std::wstring string2Wstr(const  std::string& str )
  {
    std::wstring ret;
    ret.assign(str.begin(),str.end());
    return ret;
  }

  std::string wstring2str( const std::wstring& str )
  {
    std::string ret;
    ret.assign(str.begin(),str.end());
    return ret;
  }
  
  bool changePath(std::string& path, const std::string& from, const std::string& to)
  {
    if(from.empty())
      return false;
#ifdef _WIN32
    std::string tmpPath = common::stringLower((const std::string&)path);
#else
    std::string tmpPath = path;
#endif
    bool replaced = false;
    string::size_type found = -1;
    string::size_type size = from.size();

    while ((found = tmpPath.find(from, found+1)) != string::npos) {
      tmpPath.replace(found, size, to);
      path.replace(found, size, to);
      found += to.length();
      replaced = true;
    }
    return replaced;
  }

  void lowerDriveLetter(std::string& path)
  {
    if ((path.length() > 1) && (path[1] == ':') && (path[0] >= 'A') && (path[0] <= 'Z'))
      path[0] += ('a'-'A');
  }

  void upperDriveLetter(std::string& path)
  {
    if (path.length() > 1 && (path[1] == ':') && (path[0] >= 'a') && (path[0] <= 'z'))
      path[0] += ('A'-'a');
  }

  string getCurrentTimeAndDate(const char* format)
  {
    std::time_t rawtime;
    std::tm timeinfo;
    char buffer [200];

    std::time(&rawtime);
#ifdef _WIN32
    localtime_s(&timeinfo, &rawtime);
#else
    localtime_r(&rawtime, &timeinfo);
#endif
    
    std::strftime(buffer, 200, format, &timeinfo);
    return string(buffer);
  }

  bool isGetterOrSetter( const std::string& name, bool get )
  {
    if ( name.length() >= 4 ) {
      string fourth = name.substr( 3, 1 );
      if ( fourth == "_" || fourth == stringUpper( fourth ) ) {
        string firstThree = stringLower( name.substr( 0, 3 ) );
        return (get && firstThree == "get") || (!get && firstThree == "set");
      }
    }
    return false;
  }

  bool isGetter( const std::string& name )
  {
    return isGetterOrSetter( name, true );
  }

  bool isSetter( const std::string& name )
  {
    return isGetterOrSetter( name, false );
  }

} // namespace common
