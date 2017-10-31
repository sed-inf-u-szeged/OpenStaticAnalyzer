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
#include <sstream>

#include <io/inc/BinaryIO.h>
#include <io/inc/messages.h>
#include "Exception.h"

using namespace std;

namespace columbus {  namespace io {
  
  void BinaryIO::testSizes(){
    if( (sizeof(bool) !=1) || (sizeof(unsigned char) != 1) || (sizeof(char) != 1) ||
      (sizeof(unsigned short) != 2) || (sizeof(short) != 2) || (sizeof(unsigned) != 4)  ||
      (sizeof(int) != 4) || (sizeof(long long) != 8 ) || (sizeof(unsigned long long) != 8) ||
      (sizeof(double) != 8))
      
        throw IOException(COLUMBUS_LOCATION, CMSG_EX_WRONG_SIZE);
  }

  void BinaryIO::testLocalEndian() {
    int testNum = 1;
    char* testChar = reinterpret_cast<char*>(&testNum);
    if(*testChar == 0) {
      localEndianState = etBig;
      endianState = etBig;
    } else {
      localEndianState = etLittle;
      endianState = etLittle;
    }
  }

  inline void BinaryIO::endianSwap2(unsigned short& x) {
    if(endianState != localEndianState)
      x = (x <<8)
          | (x >>8);
  }

  inline void BinaryIO::endianSwap4(unsigned int& x) {
    if(endianState != localEndianState)
      x = (x>>24) |
          ((x<<8) & 0x00FF0000) |
          ((x>>8) & 0x0000FF00) |
          (x<<24);
  }

  inline void BinaryIO::endianSwap8(unsigned long long& x)
  {
    if(endianState != localEndianState)
      x = (x>>56) |
          ((x<<40) & 0x00FF000000000000ULL) |
          ((x<<24) & 0x0000FF0000000000ULL) |
          ((x<<8)  & 0x000000FF00000000ULL) |
          ((x>>8)  & 0x00000000FF000000ULL) |
          ((x>>24) & 0x0000000000FF0000ULL) |
          ((x>>40) & 0x000000000000FF00ULL) |
          (x<<56);
  }

  inline void BinaryIO::endianSwap8(double& value) {
    alltype at;
    at.d = value;
    endianSwap8(at.ull);
    value = at.d;
  }

  inline void BinaryIO::endianSwap4(float& value) {
    alltype at;
    at.f = value;
    endianSwap4(at.u);
    value = at.f;
  }

  inline void BinaryIO::endianSwap16(long double& value) {
    alltype at ;
    at.ld = value;
    if(endianState != localEndianState) {
      endianSwap8(at.ull);
      endianSwap8( *((unsigned long long*)(((char*)&at)+8)));
      unsigned long long swap = at.ull;
      at.ull = *((unsigned long long*)(((char*)&at)+8));
      *((unsigned long long*)(((char*)&at)+8)) = swap;
    }
    value = at.ld;
  }

  BinaryIO::BinaryIO() :
    IOBase(OperationMode::binary),
    localEndianState(),
    endianState(),
    blockSizePosition(0)
  {
    testSizes();
    testLocalEndian();
  }

  BinaryIO::BinaryIO(const string& filename, eOpenMode mode) :
    IOBase(OperationMode::binary),
    localEndianState(),
    endianState(),
    blockSizePosition(0)
  {
    testSizes();
    testLocalEndian();
    open(filename,mode);
  }

  BinaryIO::BinaryIO(const char *filename, IOBase::eOpenMode mode) :
    IOBase(OperationMode::binary),
    localEndianState(),
    endianState(),
    blockSizePosition(0)
  {
    testSizes();
    testLocalEndian();
    open(filename,mode);
  }

  BinaryIO::BinaryIO(bool toError) :
    IOBase(OperationMode::binary),
    localEndianState(),
    endianState(),
    blockSizePosition(0)
  {
    testSizes();
    testLocalEndian();
    open(toError);
  }

  void BinaryIO::writeBool1(bool b) {
    if( !((mode == omWrite) || (mode == omReadWrite) || (mode == omAppend)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_READ_ONLY);

    char c = b ? 1 : 0;
    try {
      write(&c, 1);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  bool BinaryIO::readBool1() {
    if( !((mode == omRead) || (mode == omReadWrite)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_WRITE_ONLY);
    char b = 0;
    try {
      read(&b, 1);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
    return b == 1;
  }

  void BinaryIO::writeUByte1(unsigned char b) {
    if( !((mode == omWrite) || (mode == omReadWrite) || (mode == omAppend)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_READ_ONLY);
    try {
      write((const char*)&b, 1);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  unsigned char BinaryIO::readUByte1() {
    if( !((mode == omRead) || (mode == omReadWrite)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_WRITE_ONLY);
    char b;
    try {
      read(&b, 1);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
    return b;
  }

  void BinaryIO::writeByte1(char b) {
    if( !((mode == omWrite) || (mode == omReadWrite) || (mode == omAppend)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_READ_ONLY);
    try {
      write(&b, 1);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  char BinaryIO::readByte1() {
    if( !((mode == omRead) || (mode == omReadWrite)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_WRITE_ONLY);
    char b;
    try {
      read(&b, 1);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
    return b;    
  }

  void BinaryIO::writeUShort2(unsigned short i) {
    if( !((mode == omWrite) || (mode == omReadWrite) || (mode == omAppend)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_READ_ONLY);
    try {
      endianSwap2(i);
      write((const char*)&i,2);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  unsigned short BinaryIO::readUShort2() {
    if( !((mode == omRead) || (mode == omReadWrite)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_WRITE_ONLY);
    unsigned short s;
    try {
      read((char*)&s,2);
      endianSwap2(s);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
    return s;
  }

  void BinaryIO::writeShort2(short i) {
    if( !((mode == omWrite) || (mode == omReadWrite) || (mode == omAppend)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_READ_ONLY);
    try {
      endianSwap2(*(reinterpret_cast<unsigned short*>(&i)));
      write((const char*)&i,2);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  short BinaryIO::readShort2() {
    if( !((mode == omRead) || (mode == omReadWrite)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_WRITE_ONLY);
    short s;
    try {
      read((char*)&s,2);
      endianSwap2(*(reinterpret_cast<unsigned short*>(&s)));
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
    return s;
  }

  void BinaryIO::writeUInt4(unsigned i) {
    if( !((mode == omWrite) || (mode == omReadWrite) || (mode == omAppend)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_READ_ONLY);
    try {
      endianSwap4(i);
      write( (char*)&i, 4);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  unsigned BinaryIO::readUInt4() {
    if( !((mode == omRead) || (mode == omReadWrite)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_WRITE_ONLY);
    unsigned u;
    try {
      read((char*)&u,4);
      endianSwap4(u);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
    return u;
  }

  void BinaryIO::writeInt4(int i) {
    if( !((mode == omWrite) || (mode == omReadWrite) || (mode == omAppend)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_READ_ONLY);
    try {
      endianSwap4(*(reinterpret_cast<unsigned int*>(&i)));
      write( (char*)&i, 4);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  int BinaryIO::readInt4() {
    if( !((mode == omRead) || (mode == omReadWrite)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_WRITE_ONLY);
    int i;
    try {
      read((char*)&i,4);
      endianSwap4(*(reinterpret_cast<unsigned int*>(&i)));
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
    return i;
  }

  void BinaryIO::writeLongLong8(long long i) {
    if( !((mode == omWrite) || (mode == omReadWrite) || (mode == omAppend)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_READ_ONLY);
    try {
      endianSwap8(*(reinterpret_cast<unsigned long long*>(&i)));
      write( (char*)&i, 8);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  long long BinaryIO::readLongLong8() {
    if( !((mode == omRead) || (mode == omReadWrite)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_WRITE_ONLY);
    long long ll;
    try {
      read((char*)&ll,8);
      endianSwap8(*(reinterpret_cast<unsigned long long*>(&ll)));
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
    return ll;
  }

  void BinaryIO::writeULongLong8(unsigned long long i) {
    if( !((mode == omWrite) || (mode == omReadWrite) || (mode == omAppend)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_READ_ONLY);
    try {
      endianSwap8(i);
      write( (char*)&i, 8);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  unsigned long long BinaryIO::readULongLong8() {
    if( !((mode == omRead) || (mode == omReadWrite)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_WRITE_ONLY);
    unsigned long long ll;
    try {
      read((char*)&ll,8);
      endianSwap8(ll);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
    return ll;
  }

  void BinaryIO::writeDouble8(double d) {
    if( !((mode == omWrite) || (mode == omReadWrite) || (mode == omAppend)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_READ_ONLY);
    try {
      alltype x;
      x.d = d;
      endianSwap8(x.ull);
      write( (char*)&x.ull, 8);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  double BinaryIO::readDouble8() {
    if( !((mode == omRead) || (mode == omReadWrite)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_WRITE_ONLY);
    alltype x;
    try {
      read((char*)&x.ull,8);
      endianSwap8(x.ull);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
    return x.d;
  }

  void  BinaryIO::writeLongDouble16(long double d){
    if( !((mode == omWrite) || (mode == omReadWrite) || (mode == omAppend)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_READ_ONLY);
    try {
      alltype x;
      x.d = d;
      endianSwap16(x.ld);
      write( (char*)&x.ull, 16);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  long double  BinaryIO::readLongDouble16(){
    if( !((mode == omRead) || (mode == omReadWrite)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_WRITE_ONLY);
    alltype x;
    try {
      read((char*)&x.ld,16);
      endianSwap16(x.ld);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
    return x.d;
  }

  void BinaryIO::writeShortString(const string& s) {
    if( !((mode == omWrite) || (mode == omReadWrite) || (mode == omAppend)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_READ_ONLY);
    try {
      size_t size =  s.size();
      
      if (size > 0xFFFF)
        throw IOException(COLUMBUS_LOCATION, CMSG_EX_TOO_LONG_STRING);
      unsigned short writeSize = (unsigned short)size;

      writeShort2((short)size);
      write(s.c_str(), writeSize);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }

  }

  const string BinaryIO::readShortString() {
    if( !((mode == omRead) || (mode == omReadWrite)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_WRITE_ONLY);
    try {
      char* buffer;
      unsigned short size = readShort2();

      buffer = (char*)malloc(size);
      if (!buffer)
        throw IOException(COLUMBUS_LOCATION, CMSG_EX_MEMORY_ALLOCATION);
        
      read(buffer, size);
      
      string str;
      str.assign(buffer, size);
      free(buffer);
      return str;
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  void BinaryIO::readShortString(string& s) {
    if( !((mode == omRead) || (mode == omReadWrite)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_WRITE_ONLY);
    try {
      char* buffer;
      unsigned short size = readShort2();

      buffer = (char*)malloc(size);
      if (!buffer)
        throw IOException(COLUMBUS_LOCATION, CMSG_EX_MEMORY_ALLOCATION);
        
      read(buffer, size);
      s.assign(buffer, size);
      free(buffer);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  void BinaryIO::writeString(const string& s) {
    if( !((mode == omWrite) || (mode == omReadWrite) || (mode == omAppend)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_READ_ONLY);
    size_t len = s.size();
    try {
      write(s.c_str(),(streamsize)len+1);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }



  void BinaryIO::readString(string& s) {
    if( !((mode == omRead) || (mode == omReadWrite)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_WRITE_ONLY);
    try {
      stringbuf ss;
      get(ss,'\0');
      // read string end 0
      char zero;
      read(&zero, 1);
      s = ss.str();
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }


  const string BinaryIO::readString() {
    if( !((mode == omRead) || (mode == omReadWrite)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_WRITE_ONLY);
    try {
      stringbuf ss;
      get(ss,'\0');
      // read string end 0
      char zero;
      read(&zero, 1);
      return ss.str();
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  void BinaryIO::writeData(const void* data, streamsize size) {
    if( !((mode == omWrite) || (mode == omReadWrite) || (mode == omAppend)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_READ_ONLY);
    try {
      write((char*)data, size);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  void BinaryIO::readData(void* data, streamsize size) {
    if( !((mode == omRead) || (mode == omReadWrite)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_WRITE_ONLY);
    try {
      read((char*)data,size);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  void BinaryIO::writeFloat4(float f) {
    if( !((mode == omWrite) || (mode == omReadWrite) || (mode == omAppend)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_READ_ONLY);
    try {
      alltype x;
      x.f = f;
      endianSwap4(x.u);
      write( (char*)&x.u, 4);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  float BinaryIO::readFloat4() {
    if( !((mode == omRead) || (mode == omReadWrite)) ) 
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_WRITE_ONLY);
    alltype x;
    try {
      read((char*)&x.u,4);
      endianSwap4(x.u);
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
    return x.f;
  }

  void BinaryIO::setEndianState(EndianType endianState) {
    endianState = endianState;
  }

  BinaryIO::EndianType BinaryIO::getEndianState() {
    return endianState;
  }

  void BinaryIO::writeStartSizeOfBlock() {
    blockSizePosition = tellg();
    writeLongLong8(0);

  }

  void BinaryIO::skipNext(streamsize length) {
    seekg(length,ios_base::cur);
  }

  void BinaryIO::writeEndSizeOfBlock() {
    streampos filepos = tellg();
    seekg(blockSizePosition);
    long long i = filepos - blockSizePosition;
    writeLongLong8(i);
    seekg(0,ios::end);
  }

  void BinaryIO::setStartReadPosition(streampos& startPos) {
    if(!stream) {
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_NOT_OPEN);
    }

    streampos seekSize = 1024 * 1024 * 1024;
    streampos curPos = ios_base::beg;
    seekg(0,ios_base::beg);
    while ( curPos + seekSize < startPos)
    {
      seekg(seekSize,ios_base::cur);
      curPos += seekSize;
    }
    seekg(startPos - curPos,ios_base::cur);
  }

  void BinaryIO::setStartWritePosition(streampos& startPos) {
    if(!stream) {
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_NOT_OPEN);
    }

    streampos seekSize = 1024 * 1024 * 1024;
    streampos curPos = ios_base::beg;
    seekp(0,ios_base::beg);
    while ( curPos + seekSize < startPos)
    {
      seekp(seekSize,ios_base::cur);
      curPos += seekSize;
    }
    seekp(startPos - curPos,ios_base::cur);
  }

  void BinaryIO::write(const char* data, const streampos size) {
    // There is deliberately no nullptr pointer check as it is used only internally
    // from the write methods, which already checks it.
    stream->write(data, size);
  }

  void BinaryIO::read(char* data, const streampos size) {
    // There is deliberately no nullptr pointer check as it is used only internally
    // from the read methods, which already checks it.
    stream->read(data, size);
  }

  void BinaryIO::seekg(streamoff off, ios_base::seekdir way) {
    // There is deliberately no nullptr pointer check as it is used only internally
    // from the read methods, which already checks it.
    stream->seekg(off, way);
  }

  void BinaryIO::seekp(streamoff off, ios_base::seekdir way) {
    // There is deliberately no nullptr pointer check as it is used only internally
    // from the write methods, which already checks it.
    stream->seekp(off, way);
  }

  streampos BinaryIO::tellg() {
    // There is deliberately no nullptr pointer check as it is used only internally
    // from the read methods, which already checks it.
    return stream->tellg();
  }

  void BinaryIO::get(streambuf& sb, char delim) {
    // There is deliberately no nullptr pointer check as it is used only internally
    // from the read methods, which already checks it.
    stream->get(sb, delim);
  }

}}

