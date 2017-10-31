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

#ifndef IOIO_H
#define IOIO_H

#include <string>
#include <iostream>
#include <memory>


/**
* \file IOBase.h
* \brief Contains IOBase declaration
*/

namespace columbus {  namespace io {

  class IOBase {

    public:

      // open modes
      enum eOpenMode {
        omRead,
        omWrite,
        omReadWrite,
        omAppend,
      };

    protected:
      enum class OperationMode {
        binary,
        text
      };

      std::unique_ptr<std::iostream> stream; // pointer to the IO stream
      bool isFile;
      eOpenMode mode;
      OperationMode operationMode;

    public:

      /**
      * \brief default constructor
      */
      IOBase(OperationMode operationMode = OperationMode::binary);

      /**
      * \brief copy consturctor is disabled
      */
      IOBase(const IOBase& copy) = delete;

      /**
      * \brief copy assignment operator is disabled
      */
      IOBase& operator=(const columbus::io::IOBase&) = delete;

      /**
      * \brief destructor
      */
      virtual ~IOBase();

      /**
      * \brief open a file, if screen is open it will be colsed
      * \param filename [in] file name
      * \param mode [in] open mode
      * \throw IOException if a file already opened
      * \throw IOException if open is failed
      */
      virtual void open(const std::string& filename, eOpenMode mode);

      /**
      * \brief open a file, if screen is open it will be colsed
      * \param filename [in] file name
      * \param mode [in] open mode
      * \throw IOException if a file already opened
      * \throw IOException if open is failed
      */
      virtual void open(const char *filename, eOpenMode mode);

      /**
      * \brief open the given streambuffer for further read or write operations
      * \param buffer [in] the streambuffer from/to which you can read/write.
      * \param mode [in] open mode
      * \throw IOException if a file already opened
      * \throw IOException if open is failed
      */
      virtual void open(std::streambuf* buffer);

      /**
      * \brief open Out to screen, if other screen is open it will be colsed
      * \param error [in] if it is true, the output stream is stderr otherwise stdout
      * \throw IOException if a file already opened
      */
      virtual void open(bool error);

      /**
      * \brief check file is open
      */
      virtual bool isOpen();

      /**
      * \brief flush the file
      * \throw IOException if the the file is closed or not opened.
      * \throw IOException if can't flush the file
      */
      virtual void flush();

      /**
      * \brief close the opened file, after then we can open other file with open function
      * \throw IOException if the the file is already closed or not opened.
      * \throw IOException if can't close the file
      */
      virtual void close();

      /**
      * \brief return true, if fiel is end
      * \return true, if file is end, otherwise return false
      */
      virtual bool eof();
  };

}}

#endif

