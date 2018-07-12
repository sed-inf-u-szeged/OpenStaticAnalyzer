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

#ifndef _GENEALOGY_EXCEPTION_H_
#define _GENEALOGY_EXCEPTION_H_

#include "genealogy/inc/genealogy.h"

/**
* \file GenealogyException.h
* \brief Contains declaration for the common (base) class of all genealogy Exceptions.
*/

namespace columbus { namespace genealogy { 
  /**
  * \brief General (base) class for all genealogy::Exception.
  */
  class GenealogyException : public columbus::Exception {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      GenealogyException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~GenealogyException();

      /**
      * \brief Gives back the name of the genealogy::GenealogyException class.
      * \return Returns the name of the genealogy::GenealogyException class.
      */
      virtual const std::string getClassName() const;

  }; // GenealogyException


  /**
  * \brief Thrown by ListIterator if the iterator is invalid.
  */
  class GenealogyInvalidIteratorException : public GenealogyException {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      GenealogyInvalidIteratorException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~GenealogyInvalidIteratorException();

      /**
      * \brief Gives back the name of the Genealogy::GenealogyInvalidIteratorException class.
      * \return Returns the name of the Genealogy::GenealogyInvalidIteratorException class.
      */
      virtual const std::string getClassName() const;

  }; // GenealogyInvalidIteratorException


  /**
  * \brief Thrown by ListIterator if illegal operation is executed on an iterator.
  */
  class GenealogyIllegalStateException : public GenealogyException {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      GenealogyIllegalStateException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~GenealogyIllegalStateException();

      /**
      * \brief Gives back the name of the Genealogy::IllegalStateException class.
      * \return Returns the name of the Genealogy::IllegalStateException class.
      */
      virtual const std::string getClassName() const;

  }; // GenealogyIllegalStateException


  /**
  * \brief Thrown by ListIterator if next()(or pervious() ) is called and there is no next (previous) element.
  */
  class GenealogyNoSuchElementException : public GenealogyException {
    public:
      /**
      * \brief Constructor.
      * \param location [in] The location of the exception (the "place" where the exception was thrown).
      * \param message  [in] The cause of the exception.
      */
      GenealogyNoSuchElementException(const std::string &location, const std::string &message);

      /**
      * \brief Destructor.
      */
      virtual ~GenealogyNoSuchElementException();

      /**
      * \brief Gives back the name of the genealogy::GenealogyNoSuchElementException class.
      * \return Returns the name of the genealogy::GenealogyNoSuchElementException class.
      */
      virtual const std::string getClassName() const;

  }; // GenealogyNoSuchElementException



}}
#endif

