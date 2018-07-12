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

#ifndef _CSHARP_EXCEPTION_H_
#define _CSHARP_EXCEPTION_H_

#include "csharp/inc/csharp.h"

/**
* \file CsharpException.h
* \brief Contains declaration for the common (base) class of all csharp Exceptions.
*/

namespace columbus { namespace csharp { namespace asg {
  /**
  * \brief General (base) class for all csharp::Exception.
  */
  class CsharpException : public columbus::Exception {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      CsharpException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~CsharpException();

      /**
      * \brief Gives back the name of the csharp::CsharpException class.
      * \return Returns the name of the csharp::CsharpException class.
      */
      virtual const std::string getClassName() const;

  }; // CsharpException


  /**
  * \brief Thrown by ListIterator if the iterator is invalid.
  */
  class CsharpInvalidIteratorException : public CsharpException {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      CsharpInvalidIteratorException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~CsharpInvalidIteratorException();

      /**
      * \brief Gives back the name of the Csharp::CsharpInvalidIteratorException class.
      * \return Returns the name of the Csharp::CsharpInvalidIteratorException class.
      */
      virtual const std::string getClassName() const;

  }; // CsharpInvalidIteratorException


  /**
  * \brief Thrown by ListIterator if illegal operation is executed on an iterator.
  */
  class CsharpIllegalStateException : public CsharpException {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      CsharpIllegalStateException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~CsharpIllegalStateException();

      /**
      * \brief Gives back the name of the Csharp::IllegalStateException class.
      * \return Returns the name of the Csharp::IllegalStateException class.
      */
      virtual const std::string getClassName() const;

  }; // CsharpIllegalStateException


  /**
  * \brief Thrown by ListIterator if next()(or pervious() ) is called and there is no next (previous) element.
  */
  class CsharpNoSuchElementException : public CsharpException {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      CsharpNoSuchElementException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~CsharpNoSuchElementException();

      /**
      * \brief Gives back the name of the csharp::CsharpNoSuchElementException class.
      * \return Returns the name of the csharp::CsharpNoSuchElementException class.
      */
      virtual const std::string getClassName() const;

  }; // CsharpNoSuchElementException



}}}
#endif

