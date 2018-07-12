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

#ifndef GRAPHEXCEPTIONS_H
#define GRAPHEXCEPTIONS_H

#include <Exception.h>

/**
* \file Edge.h
* \brief Contains exception declaration for the graph lib
*/

namespace columbus {  namespace graph {

  /** 
  * \brief the base graph exception
  */
  class GraphException : public Exception {
    public:
      /**
      * \brief constructor
      * \param location [in] location of the exception
      * \param message [in] message of the exception
      */
      GraphException(const std::string &location, const std::string &message);
  };
  
  /** 
  * \brief the node is already exist in the graph
  */
  class AlreadyExist : public GraphException{
    public:
      /**
      * \brief constructor
      * \param location [in] location of the exception
      * \param message [in] message of the exception
      */
      AlreadyExist(const std::string &location, const std::string &message);
  };

  /** 
  * \brief the graph doesn't contain the edge
  */
  class EdgeNotFound : public GraphException{
    public:
      /**
      * \brief constructor
      * \param location [in] location of the exception
      * \param message [in] message of the exception
      */
      EdgeNotFound(const std::string &location, const std::string &message);
  };

  /** 
  * \brief invalidEdge and InvalidNode getter
  */
  class InvalidGetter : public GraphException{
    public:
      /**
      * \brief constructor
      * \param location [in] location of the exception
      * \param message [in] message of the exception
      */
      InvalidGetter(const std::string &location, const std::string &message);
  };

  /** 
  * \brief invalidEdge and InvalidNode setter
  */
  class InvalidSetter : public GraphException{
    public:
      /**
      * \brief constructor
      * \param location [in] location of the exception
      * \param message [in] message of the exception
      */
      InvalidSetter(const std::string &location, const std::string &message);
  };

  /** 
  * \brief invalid iterator
  */
  class GraphInvalidIteratorException : public GraphException {
    public:
      /**
      * \brief constructor
      * \param location [in] location of the exception
      * \param message [in] message of the exception
      */
      GraphInvalidIteratorException(const std::string &location, const std::string &message);
  };

  /** 
  * \brief graph doesn't contain the element
  */
  class GraphNoSuchElementException : public GraphException {
    public:
      /**
      * \brief constructor
      * \param location [in] location of the exception
      * \param message [in] message of the exception
      */
      GraphNoSuchElementException(const std::string &location, const std::string &message);
  };

  /** 
  * \brief exception during use graph schema
  */
  class GraphSchemaException : public GraphException {
    public:
      /**
      * \brief constructor
      * \param location [in] location of the exception
      * \param message [in] message of the exception
      */
      GraphSchemaException(const std::string &location, const std::string &message);
  };

}}

#endif 
