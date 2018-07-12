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

#include <iostream>
#include <fstream>

#include <io/inc/IO.h>
#include <io/inc/messages.h>
#include "Exception.h"
#include <common/inc/PlatformDependentDefines.h>

using namespace std;

namespace columbus {  namespace io {

  IOBase::IOBase(OperationMode operationMode) : stream(nullptr), isFile(false), mode(omRead), operationMode(operationMode)
  {
  }

  IOBase::~IOBase() {
    close();
  }

  void IOBase::open(const string& filename, eOpenMode mode) {
    if(stream != nullptr)
      close();
    try {
      isFile = true;
      this->mode = mode;

      ios_base::openmode om;
      switch(mode) {
        case omRead:
          om = ios_base::in;
          break;
        case omWrite:
          om = ios_base::out;
          break;
        case omReadWrite:
          om = ios_base::in | ios_base::out;
          break;
        case omAppend:
          om = ios_base::out | ios_base::app;
          break;
      }
      
      if (operationMode == OperationMode::binary)
        om |= ios_base::binary;

#if defined(_WIN32)
      if (filename.length() > 255 && (strncmp(filename.c_str(),LONGDIRPREFIXSTRING_A,4) != 0) ) {
        string fixedFileName = LONGDIRPREFIXSTRING_A;
        fixedFileName += filename;
        stream = make_unique<fstream>(fixedFileName.c_str(), om);
      } else {
        stream = make_unique<fstream>(filename.c_str(), om);
      }
#else
      stream = make_unique<fstream>(filename.c_str(), om);
#endif

      if(stream == nullptr || stream->fail())
        throw IOException(COLUMBUS_LOCATION, CMSG_EX_OPEN_FILE + filename);
      stream->exceptions(ios_base::failbit | ios_base::badbit);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  void IOBase::open(const char *filename, eOpenMode mode) {
    open(string(filename),mode);
  }

  void IOBase::open(streambuf* buffer) {
    if (stream != nullptr)
      close();
    stream = make_unique<iostream>(buffer);
    if(stream == nullptr || stream->fail())
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_OPEN_STREAMBUF);
    stream->exceptions(ios_base::failbit | ios_base::badbit);
    mode = omReadWrite;
  }

  void IOBase::open(bool error) {
    if(stream != nullptr && !isFile)
      close();
    if(stream != nullptr && isFile)
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_OPEN_TWO_FILES);
    isFile = false;
    mode = omWrite;
    if(!error) {
      stream = make_unique<iostream>(cout.rdbuf());
    } else {
      stream = make_unique<iostream>(cerr.rdbuf());
    }
  }

  bool IOBase::isOpen() {
    if(stream == nullptr)
      return false;
      
    if (isFile)
      return dynamic_cast<fstream*>(stream.get())->is_open();
    
    return true;
  }

  void IOBase::flush() {
    if(stream == nullptr) {
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_NOT_OPEN);
    }

    try {
      stream->flush();
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  void IOBase::close() {
    if(stream == nullptr)
      return;
    try {
      if (isFile)
        dynamic_cast<fstream*>(stream.get())->close();
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
    delete stream.release();
  }

  bool IOBase::eof() {
    if(stream == nullptr) {
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_NOT_OPEN);
    }
    return stream->eof();
  }

}}

