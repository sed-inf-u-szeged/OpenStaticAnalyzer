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

#include <fstream>
#include <sstream>

#include <io/inc/CsvIO.h>
#include <io/inc/messages.h>
#include "Exception.h"
#include <algorithm>

using namespace std;

namespace columbus {  namespace io {
  CsvIO::CsvIO() : 
    IOBase(OperationMode::text),
    separator(','),
    qchar('"'),
    dmark('.'),
    quotation(false),
    isWriteFirstColumn(false)
  {
  }

  CsvIO::CsvIO(const string& filename, eOpenMode mode) :
    IOBase(OperationMode::text),
    separator(';'),
    qchar('"'),
    dmark('.'),
    quotation(false),
    isWriteFirstColumn(false)
  {
    open(filename, mode);
  }

  CsvIO::CsvIO(const char *filename, eOpenMode mode) : 
    IOBase(OperationMode::text),
    separator(';'),
    qchar('"'),
    dmark('.'),
    quotation(false),
    isWriteFirstColumn(false)
  {
    open(filename, mode);
  }

  CsvIO::CsvIO(bool toError) :
    IOBase(OperationMode::text),
    separator(';'),
    qchar('"'),
    dmark('.'),
    quotation(false),
    isWriteFirstColumn(false)
  {
    open(toError);
  }

  CsvIO::~CsvIO() {
  }

  void CsvIO::setSeparator(char separator) {
    this->separator = separator;
  }

  void CsvIO::setQuotationChar(char qchar) {
    this->qchar = qchar;
  }
  
  void CsvIO::setQuotationMode(bool quotation) {
    this->quotation = quotation;
  }

  void CsvIO::setPrecision(int precision) {
    if (stream) {
      stream->precision(precision);
      stream->operator<<(fixed);
    }
  }
  
  void CsvIO::setDecimalMark(char dmark) {
    this->dmark = dmark;
  }  
  
  template <class Val>
  void CsvIO::writeValueByTemplate(Val value) {
    (*stream) << value;
  }

  template <>
  void CsvIO::writeValueByTemplate<double>(double value) {
    stringstream s;
    s.precision(stream->precision());
    s.flags(stream->flags());
    s << value;
    string str = s.str();
    replace(str.begin(), str.end(), '.', dmark);
    (*stream) << str;
  }
  
  template<class Val>
  void CsvIO::writeColumnByTemplate(Val value) {
    if( !((mode == omWrite) || (mode == omReadWrite) || (mode == omAppend)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_READ_ONLY);
    try {
      if(isWriteFirstColumn)
        (*stream) << separator;
      
      if (quotation) 
        (*stream) << qchar;
      
      writeValueByTemplate(value);

      if (quotation) 
        (*stream) << qchar;

      isWriteFirstColumn = true;
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  void CsvIO::writeColumn(const string& value) {
    writeColumnByTemplate(value);
  }

  void CsvIO::writeColumn(const char* value) {
    writeColumnByTemplate(value);
  }

  void CsvIO::writeColumn(int value) {
    writeColumnByTemplate(value);
  }

  void CsvIO::writeColumn(unsigned int value) {
    writeColumnByTemplate(value);
  }

  void CsvIO::writeColumn(long value) {
    writeColumnByTemplate(value);
  }
  void CsvIO::writeColumn(unsigned long value) {
    writeColumnByTemplate(value);
  }

  void CsvIO::writeColumn(long long value) {
    writeColumnByTemplate(value);
  }

  void CsvIO::writeColumn(double value) {
     writeColumnByTemplate(value);
  }

  void CsvIO::writeColumn(bool value) {
    writeColumnByTemplate(value);
  }

  void CsvIO::writeNewLine() {
    if( !((mode == omWrite) || (mode == omReadWrite) || (mode == omAppend)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_READ_ONLY);
    try {
      (*stream) << '\n';
      isWriteFirstColumn = false;
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  bool CsvIO::readLine(list<string>& line) {
    if( !((mode == omRead) || (mode == omReadWrite)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_WRITE_ONLY);
    if(stream->eof() || !isOpen())
      return false;
    try {
      string s;
      size_t sep;

      getline ( *stream, s );
      while( (sep = s.find_first_of(separator)) != string::npos  ) {
        string split = s.substr(0,sep);
        s = s.substr(sep+1);

        if(split.empty()) {
          line.push_back("");
          continue;
        }
        while((split[split.length()-1] == '\r') || (split[split.length()-1] == '\n'))
          split = split.substr(0, split.length()-1);
        line.push_back(split);
      }
      while(!s.empty() && ( (s[s.length()-1] == '\r') || (s[s.length()-1] == '\n') ) )
        s = s.substr(0, s.length()-1);
      if(!s.empty()) 
        line.push_back(s);
      return true;
    } catch (const exception&) {
      return false;
    }
  }

  bool CsvIO::readLine(vector<string>& line) {
    list<string> line_list;
    bool ret = readLine(line_list);
    for(auto s : line_list) {
      line.push_back(s);
    }
    return ret;
  }

}}

