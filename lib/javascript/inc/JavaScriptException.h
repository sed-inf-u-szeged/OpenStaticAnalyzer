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
* \file JavaScriptException.h
* \brief Contains declaration for the common (base) class of all javascript Exceptions.
*/

namespace columbus { namespace javascript { namespace asg {
  /**
  * \brief General (base) class for all javascript::Exception.
  */
  class JavaScriptException : public columbus::Exception {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      JavaScriptException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~JavaScriptException();

      /**
      * \brief Gives back the name of the javascript::JavaScriptException class.
      * \return Returns the name of the javascript::JavaScriptException class.
      */
      virtual const std::string getClassName() const;

  }; // JavaScriptException


  /**
  * \brief Thrown by ListIterator if the iterator is invalid.
  */
  class JavaScriptInvalidIteratorException : public JavaScriptException {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      JavaScriptInvalidIteratorException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~JavaScriptInvalidIteratorException();

      /**
      * \brief Gives back the name of the JavaScript::JavaScriptInvalidIteratorException class.
      * \return Returns the name of the JavaScript::JavaScriptInvalidIteratorException class.
      */
      virtual const std::string getClassName() const;

  }; // JavaScriptInvalidIteratorException


  /**
  * \brief Thrown by ListIterator if illegal operation is executed on an iterator.
  */
  class JavaScriptIllegalStateException : public JavaScriptException {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      JavaScriptIllegalStateException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~JavaScriptIllegalStateException();

      /**
      * \brief Gives back the name of the JavaScript::IllegalStateException class.
      * \return Returns the name of the JavaScript::IllegalStateException class.
      */
      virtual const std::string getClassName() const;

  }; // JavaScriptIllegalStateException


  /**
  * \brief Thrown by ListIterator if next()(or pervious() ) is called and there is no next (previous) element.
  */
  class JavaScriptNoSuchElementException : public JavaScriptException {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      JavaScriptNoSuchElementException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~JavaScriptNoSuchElementException();

      /**
      * \brief Gives back the name of the javascript::JavaScriptNoSuchElementException class.
      * \return Returns the name of the javascript::JavaScriptNoSuchElementException class.
      */
      virtual const std::string getClassName() const;

  }; // JavaScriptNoSuchElementException



}}}
#endif

