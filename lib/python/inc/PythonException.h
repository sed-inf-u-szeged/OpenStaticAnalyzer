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

#ifndef _PYTHON_EXCEPTION_H_
#define _PYTHON_EXCEPTION_H_

#include "python/inc/python.h"

/**
* \file PythonException.h
* \brief Contains declaration for the common (base) class of all python Exceptions.
*/

namespace columbus { namespace python { namespace asg {
  /**
  * \brief General (base) class for all python::Exception.
  */
  class PythonException : public columbus::Exception {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      PythonException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~PythonException();

      /**
      * \brief Gives back the name of the python::PythonException class.
      * \return Returns the name of the python::PythonException class.
      */
      virtual const std::string getClassName() const;

  }; // PythonException


  /**
  * \brief Thrown by ListIterator if the iterator is invalid.
  */
  class PythonInvalidIteratorException : public PythonException {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      PythonInvalidIteratorException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~PythonInvalidIteratorException();

      /**
      * \brief Gives back the name of the Python::PythonInvalidIteratorException class.
      * \return Returns the name of the Python::PythonInvalidIteratorException class.
      */
      virtual const std::string getClassName() const;

  }; // PythonInvalidIteratorException


  /**
  * \brief Thrown by ListIterator if illegal operation is executed on an iterator.
  */
  class PythonIllegalStateException : public PythonException {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      PythonIllegalStateException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~PythonIllegalStateException();

      /**
      * \brief Gives back the name of the Python::IllegalStateException class.
      * \return Returns the name of the Python::IllegalStateException class.
      */
      virtual const std::string getClassName() const;

  }; // PythonIllegalStateException


  /**
  * \brief Thrown by ListIterator if next()(or pervious() ) is called and there is no next (previous) element.
  */
  class PythonNoSuchElementException : public PythonException {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      PythonNoSuchElementException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~PythonNoSuchElementException();

      /**
      * \brief Gives back the name of the python::PythonNoSuchElementException class.
      * \return Returns the name of the python::PythonNoSuchElementException class.
      */
      virtual const std::string getClassName() const;

  }; // PythonNoSuchElementException



}}}
#endif

