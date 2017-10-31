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

#ifndef _LIM_EXCEPTION_H_
#define _LIM_EXCEPTION_H_

#include "lim/inc/lim.h"

/**
* \file LimException.h
* \brief Contains declaration for the common (base) class of all lim Exceptions.
*/

namespace columbus { namespace lim { namespace asg {
  /**
  * \brief General (base) class for all lim::Exception.
  */
  class LimException : public columbus::Exception {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      LimException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~LimException();

      /**
      * \brief Gives back the name of the lim::LimException class.
      * \return Returns the name of the lim::LimException class.
      */
      virtual const std::string getClassName() const;

  }; // LimException


  /**
  * \brief Thrown by ListIterator if the iterator is invalid.
  */
  class LimInvalidIteratorException : public LimException {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      LimInvalidIteratorException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~LimInvalidIteratorException();

      /**
      * \brief Gives back the name of the Lim::LimInvalidIteratorException class.
      * \return Returns the name of the Lim::LimInvalidIteratorException class.
      */
      virtual const std::string getClassName() const;

  }; // LimInvalidIteratorException


  /**
  * \brief Thrown by ListIterator if illegal operation is executed on an iterator.
  */
  class LimIllegalStateException : public LimException {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      LimIllegalStateException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~LimIllegalStateException();

      /**
      * \brief Gives back the name of the Lim::IllegalStateException class.
      * \return Returns the name of the Lim::IllegalStateException class.
      */
      virtual const std::string getClassName() const;

  }; // LimIllegalStateException


  /**
  * \brief Thrown by ListIterator if next()(or pervious() ) is called and there is no next (previous) element.
  */
  class LimNoSuchElementException : public LimException {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      LimNoSuchElementException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~LimNoSuchElementException();

      /**
      * \brief Gives back the name of the lim::LimNoSuchElementException class.
      * \return Returns the name of the lim::LimNoSuchElementException class.
      */
      virtual const std::string getClassName() const;

  }; // LimNoSuchElementException



}}}
#endif

