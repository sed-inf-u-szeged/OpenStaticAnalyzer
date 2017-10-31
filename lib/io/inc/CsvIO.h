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

#ifndef CSVIOIO_H
#define CSVIOIO_H

#include <io/inc/ioBase.h>
#include <list>
#include <vector>

/**
* \file CsvIO.h
* \brief Contains CsvIO declaration
*/

namespace columbus {  namespace io {

  class CsvIO : virtual public IOBase {

    protected:
      char separator; // the separator character (default value is ',' )
      char qchar;     // the quotation character for the columns (default value is '"')
      char dmark;     // the decimal mark character for the float and double values (default is '.' )
      bool quotation; // quotation mode state. encapsulates the columns with the qchar  (default is false)
      
      /**
      * \param write a column value in to a line
      * \param value [in] column value
      * \throw IOException if the writing is failed.
      * \throw IOException if the open mode isn't write
      */
      template<class Val>
      void writeColumnByTemplate(Val value);

      /**
      * \param write a value in to a line
      * \param value [in] column value
      */
      template<class Val>
      void writeValueByTemplate(Val value);

      /**
      * \internal
      * \brief it true, if we write the first column
      */
      bool isWriteFirstColumn;

    public:

      /**
      * \brief constructor, create empty CsvIO object
      */
      CsvIO();

      /**
      * \brief create a CsvIO object and open a file
      * \param filename [in] file name
      * \param mode [in] open mode
      * \throw IOException if open is failed
      */
      CsvIO(const std::string& filename, eOpenMode mode);

      /**
      * \brief create a CsvIO object and open a file
      * \param filename [in] file name
      * \param mode [in] open mode
      * \throw IOException if open is failed
      */
      CsvIO(const char *filename, eOpenMode mode);

      /**
      * \brief create CsvIO object and open a stream to stdout/stderr
      * \param toError [in] if it is true, stream is open to stderr, otherwise stdout
      */
      CsvIO(bool toError);

      /**
      * \brief destructor
      */
      ~CsvIO();
      
      /**
      * \brief set separator character
      * \param separator [in] separator character
      */
      void setSeparator(char separator);
      
      /**
      * \brief set precision for the float and double values
      * \param precision [in] number of digits after the decimal point in case of float and double values
      */
      void setPrecision(int precision);

      /**
      * \brief set quotation character for the columns. 
      * \param qchar [in] quotation character
      */
      void setQuotationChar(char qchar);

      /**
      * \brief enables or disables the quotation of the columns
      * \param quotation [in] the quotation mode
      */
      void setQuotationMode(bool quotation);
      
      /**
      * \brief set the decimal mark character for the float and double values
      * \param dmark [in] decimal mark character
      */
      void setDecimalMark(char dmark);
      
      /**
      * \param write a column value in to a line
      * \param value [in] column value
      */
      void writeColumn(const std::string& value);

      /**
      * \param write a column value in to a line
      * \param value [in] column value
      * \throw IOException if the writing is failed.
      * \throw IOException if the open mode isn't write
      */
      void writeColumn(const char* value);

      /**
      * \param write a column value in to a line
      * \param value [in] column value
      * \throw IOException if the writing is failed.
      * \throw IOException if the open mode isn't write
      */
      void writeColumn(int value);

      /**
      * \param write a column value in to a line
      * \param value [in] column value
      * \throw IOException if the writing is failed.
      * \throw IOException if the open mode isn't write
      */
      void writeColumn(unsigned int value);

      /**
      * \param write a column value in to a line
      * \param value [in] column value
      * \throw IOException if the writing is failed.
      * \throw IOException if the open mode isn't write
      */
      void writeColumn(long value);

      /**
      * \param write a column value in to a line
      * \param value [in] column value
      * \throw IOException if the writing is failed.
      * \throw IOException if the open mode isn't write
      */
      void writeColumn(unsigned long value);

      /**
      * \param write a column value in to a line
      * \param value [in] column value
      * \throw IOException if the writing is failed.
      * \throw IOException if the open mode isn't write
      */
      void writeColumn(long long value);

      /**
      * \param write a column value in to a line
      * \param value [in] column value
      * \throw IOException if the writing is failed.
      * \throw IOException if the open mode isn't write
      */
      void writeColumn(double value);

      /**
      * \param write a column value in to a line
      * \param value [in] column value
      * \throw IOException if the writing is failed.
      * \throw IOException if the open mode isn't write
      */
      void writeColumn(bool value);

      /**
      * \param write a new line
      * \throw IOException if the writing is failed.
      * \throw IOException if the open mode isn't write
      */
      void writeNewLine();
      
      /**
      * \brief read a new line and append 'line'
      * \param line [inout] the appended line
      * \return true if read a line
      * \throw IOException if the writing is failed.
      * \throw IOException if the open mode isn't read
      */
      bool readLine(std::list<std::string>& line);

      bool readLine(std::vector<std::string>& line);
  };

}}

#endif

