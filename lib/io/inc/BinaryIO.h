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

#ifndef BINARYIOIO_H
#define BINARYIOIO_H

#include <io/inc/ioBase.h>

/**
* \file BinaryIO.h
* \brief Contains BinaryIO declaration
*/

namespace columbus {  namespace io {

  class BinaryIO : virtual public IOBase{
    public:
      /**
      \brief Write long long 0 size of the following block into the current file position
      * set the blockSizePosition to the current file position
      */
      virtual void writeStartSizeOfBlock();
       /**
      \brief Write the difference beetween the actual file positon and the BlockSizeposition as a file size to the storaged blockSizePosition
      */
      virtual void writeEndSizeOfBlock();

      /**
      \brief skip the next length long data.
      \param length of the data
      */
      virtual void skipNext(std::streamsize length);

      enum EndianType {
        etLittle,
        etBig
      };

      /**
      * \brief constructor, creatr empty BinaryIO object
      */
      BinaryIO();

      /**
      * \brief create BinaryIO object and open a file
      * \param filename [in] file name
      * \param mode [in] open mode
      * \throw IOException if open is failed
      */
      BinaryIO(const std::string& filename, IOBase::eOpenMode mode);

      /**
      * \brief create BinaryIO object and open a file
      * \param filename [in] file name
      * \param mode [in] open mode
      * \throw IOException if open is failed
      */
      BinaryIO(const char *filename, IOBase::eOpenMode mode);

      /**
      * \brief create BinaryIO object and open a stream to stdout/stderr
      * \param toError [in] if it is true, stream is open to stderr, otherwise stdout
      */
      BinaryIO(bool toError);
      
      /**
      * \brief Writes a boolean on 1 byte to the file.
      * \param b [in] output value
      * \throw IOException if the writing is failed.
      * \throw IOException if the open mode isn't write
      */
      virtual void writeBool1(bool b);

      /**
      * \brief Reads 1 byte into a bool from the file.
      * \return readed data
      * \throw IOException if the reading is failed.
      * \throw IOExceotion if the open mode isn't read
      */
      virtual bool readBool1();

      /**
      * \brief Writes an unsigned charater on 1 byte to the file.
      * \param b [in] output value
      * \throw IOException if the writing is failed.
      * \throw IOExceotion if the open mode isn't write
      */
      virtual void writeUByte1(unsigned char b);

      /**
      * \brief Reads 1 byte into an unsigned char from the file.
      * \return readed data
      * \throw IOException if the reading is failed.
      * \throw IOExceotion if the open mode isn't read
      */
      virtual unsigned char readUByte1();

      /**
      * \brief Writes an charater on 1 byte to the file.
      * \param b [in] output value
      * \throw IOException if the writing is failed.
      * \throw IOExceotion if the open mode isn't write
      */
      virtual void writeByte1(char b);

      /**
      * \brief Reads 1 byte into a char from the file.
      * \return readed data
      * \throw IOException if the reading is failed.
      * \throw IOExceotion if the open mode isn't read
      */
      virtual char readByte1();
      
      /**
      * \brief Writes an unsigned short on 2 byte to the file.
      * \param i [in] output value
      * \throw IOException if the writing is failed.
      * \throw IOExceotion if the open mode isn't write
      */
      virtual void writeUShort2(unsigned short i);

      /**
      * \brief Reads 2 byte into an unsigned short from the file.
      * \return readed data
      * \throw IOException if the reading is failed.
      * \throw IOExceotion if the open mode isn't read
      */
      virtual unsigned short readUShort2();

      /**
      * \brief Writes a short on 2 byte to the file.
      * \param i [in] output value
      * \throw IOException if the writing is failed.
      * \throw IOExceotion if the open mode isn't write
      */
      virtual void writeShort2(short i);

      /**
      * \brief Reads 2 byte into a short from the file.
      * \return readed data
      * \throw IOException if the reading is failed.
      * \throw IOExceotion if the open mode isn't read
      */
      virtual short readShort2();

      /**
      * \brief Writes an unsigned integer on 4 byte to the file.
      * \param i [in] output value
      * \throw IOException if the writing is failed.
      * \throw IOExceotion if the open mode isn't write
      */
      virtual void writeUInt4(unsigned i);

      /**
      * \brief Reads 4 byte into an unsigned integer from the file.
      * \return readed data
      * \throw IOException if the reading is failed.
      * \throw IOExceotion if the open mode isn't read
      */
      virtual unsigned readUInt4();
      
      /**
      * \brief Writes an integer on 4 byte to the file.
      * \param i [in] output value
      * \throw IOException if the writing is failed.
      * \throw IOExceotion if the open mode isn't write
      */
      virtual void writeInt4(int i);

      /**
      * \brief Reads 4 byte into an integer from the file.
      * \return readed data
      * \throw IOException if the reading is failed.
      * \throw IOExceotion if the open mode isn't read
      */
      virtual int readInt4();

      /**
      * \brief Writes a long long on 8 byte to the file.
      * \param i [in] output value
      * \throw IOException if the writing is failed.
      * \throw IOExceotion if the open mode isn't write
      */
      virtual void writeLongLong8(long long i);

      /**
      * \brief Reads 8 byte into a long long from the file.
      * \return readed data
      * \throw IOException if the reading is failed.
      * \throw IOExceotion if the open mode isn't read
      */
      virtual long long readLongLong8();

      /**
      * \brief Writes an unsigned long long on 8 byte to the file.
      * \param i [in] output value
      * \throw IOException if the writing is failed.
      * \throw IOExceotion if the open mode isn't write
      */
      virtual void writeULongLong8(unsigned long long i);

      /**
      * \brief Reads 8 byte into an unsigned long long from the file.
      * \return readed data
      * \throw IOException if the reading is failed.
      * \throw IOExceotion if the open mode isn't read
      */
      virtual unsigned long long readULongLong8();

      /**
      * \brief Writes a double on 8 byte to the file.
      * \param d [in] output value
      * \throw IOException if the writing is failed.
      * \throw IOExceotion if the open mode isn't write
      */
      virtual void writeDouble8(double d);

      /**
      * \brief Reads 8 byte into a double from the file.
      * \return readed data
      * \throw IOException if the reading is failed.
      * \throw IOExceotion if the open mode isn't read
      */
      virtual double readDouble8();

            /**
      * \brief Writes a long double on 16 byte to the file.
      * \param d [in] output value
      * \throw IOException if the writing is failed.
      * \throw IOExceotion if the open mode isn't write
      */
      virtual void writeLongDouble16(long double d);

      /**
      * \brief Reads 16 byte into a long double from the file.
      * \return readed data
      * \throw IOException if the reading is failed.
      * \throw IOExceotion if the open mode isn't read
      */
      virtual long double readLongDouble16();

     /**
      * \brief Writes short string to the file. String maximum length is 65k and it can contain '\0' character
      * \param s [in] output value
      * \throw IOException if the writing is failed.
      * \throw IOExceotion if the open mode isn't write
      */
      virtual void writeShortString(const std::string& s);

      /**
      * \brief Reads short string (can't read string) form the file. String length stored befor the data.
      * \return readed data
      * \throw IOException if the reading is failed.
      * \throw IOExceotion if the open mode isn't read
      */
      virtual const std::string readShortString();

      /**
      * \brief Reads short string form the file. String length stored befor the data.
      * \param s [out] readed data
      * \throw IOException if the reading is failed.
      * \throw IOExceotion if the open mode isn't read
      */
      virtual void readShortString(std::string &s);

      /**
      * \brief Writes string to the file. String doesn't have maximum length but it can't contain '\0' character.
      * \throw IOException if the writing is failed.
      * \throw IOExceotion if the open mode isn't write
      */      
      virtual void writeString(const std::string& s);

      /**
      * \brief Reads string (can't read short string) form the file. It reads until '\0' character is found.
      * \return readed data
      * \throw IOException if the reading is failed.
      * \throw IOExceotion if the open mode isn't read
      */
      virtual const std::string readString();

      /**
      * \brief Reads string (can't read short string) form the file. It reads until '\0' character is found.
      * \param s [out] readed data
      * \throw IOException if the reading is failed.
      * \throw IOExceotion if the open mode isn't read
      */
      virtual void readString(std::string& s);

      /**
      * \brief Writes a float on 4 byte to the file.
      * \param f [in] output value
      * \throw IOException if the writing is failed.
      * \throw IOExceotion if the open mode isn't write
      */
      virtual void writeFloat4(float f);

      /**
      * \brief Reads 4 byte into a float from the file.
      * \return readed data
      * \throw IOException if the reading is failed.
      * \throw IOExceotion if the open mode isn't read
      */
      virtual float readFloat4();

      /**
      * \brief Writes a void* on 'size' byte to the file.
      * \param data [in] output value
      * \param size [in] the data length
      * \throw IOException if the writing is failed.
      * \throw IOExceotion if the open mode isn't write
      */
      virtual void writeData(const void* data, std::streamsize size);

      /**
      * \brief Reads 'size' byte into a void* from the file.
      * \param buffer [out] to the data
      * \param size [in] the read length
      * \throw IOException if the reading is failed.
      * \throw IOExceotion if the open mode isn't read
      */
      virtual void readData (void* data, std::streamsize size);

      virtual void setEndianState(EndianType endianState);

      virtual EndianType getEndianState();

     /**
      * \brief set position to read
      * \param startPos startposition to read
      */
      virtual void setStartReadPosition(std::streampos& startPos);

      virtual void setStartWritePosition( std::streampos& startPos );

    private:

      /**
      * \brief test types size
      */
      virtual void testSizes();

      virtual void testLocalEndian();

      virtual void write(const char* data, const std::streampos size);
      virtual void read(char* data, const std::streampos size);
      virtual void seekg(std::streamoff off, std::ios_base::seekdir way = std::ios_base::beg);
      virtual void seekp(std::streamoff off, std::ios_base::seekdir way = std::ios_base::beg);
      virtual std::streampos tellg();
      virtual void get(std::streambuf& sb, char delim);

  protected:
      // 2 byte
      virtual void endianSwap2(unsigned short& value);

      // 4byte
      virtual void endianSwap4(unsigned int& value);

      // 8byte
      virtual void endianSwap8(unsigned long long& value);

      virtual void endianSwap8(double& value);

      virtual void endianSwap4(float& value);

      // 16byte
      virtual void endianSwap16(long double& value);

  protected:
      EndianType localEndianState;
      EndianType endianState;
      std::streampos blockSizePosition;

      typedef union {
        unsigned char bytes[16];
        int i;
        unsigned u;
        long l;
        unsigned long ul;
        long long ll;
        unsigned long long ull;
        float f;
        double d;
        long double ld;
      } alltype;
  };


}}

#endif

