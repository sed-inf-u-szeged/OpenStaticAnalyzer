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

#ifndef _JAVASCRIPT_EXCEPTION_H_
#define _JAVASCRIPT_EXCEPTION_H_

#include "javascript/inc/javascript.h"

/**
* \file JavascriptException.h
* \brief Contains declaration for the common (base) class of all javascript Exceptions.
*/

namespace columbus { namespace javascript { namespace asg {
  /**
  * \brief General (base) class for all javascript::Exception.
  */
  class JavascriptException : public columbus::Exception {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      JavascriptException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~JavascriptException();

      /**
      * \brief Gives back the name of the javascript::JavascriptException class.
      * \return Returns the name of the javascript::JavascriptException class.
      */
      virtual const std::string getClassName() const;

  }; // JavascriptException


  /**
  * \brief Thrown by ListIterator if the iterator is invalid.
  */
  class JavascriptInvalidIteratorException : public JavascriptException {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      JavascriptInvalidIteratorException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~JavascriptInvalidIteratorException();

      /**
      * \brief Gives back the name of the Javascript::JavascriptInvalidIteratorException class.
      * \return Returns the name of the Javascript::JavascriptInvalidIteratorException class.
      */
      virtual const std::string getClassName() const;

  }; // JavascriptInvalidIteratorException


  /**
  * \brief Thrown by ListIterator if illegal operation is executed on an iterator.
  */
  class JavascriptIllegalStateException : public JavascriptException {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      JavascriptIllegalStateException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~JavascriptIllegalStateException();

      /**
      * \brief Gives back the name of the Javascript::IllegalStateException class.
      * \return Returns the name of the Javascript::IllegalStateException class.
      */
      virtual const std::string getClassName() const;

  }; // JavascriptIllegalStateException


  /**
  * \brief Thrown by ListIterator if next()(or pervious() ) is called and there is no next (previous) element.
  */
  class JavascriptNoSuchElementException : public JavascriptException {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      JavascriptNoSuchElementException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~JavascriptNoSuchElementException();

      /**
      * \brief Gives back the name of the javascript::JavascriptNoSuchElementException class.
      * \return Returns the name of the javascript::JavascriptNoSuchElementException class.
      */
      virtual const std::string getClassName() const;

  }; // JavascriptNoSuchElementException



}}}
#endif

