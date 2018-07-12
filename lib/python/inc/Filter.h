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

#ifndef _PYTHON_FILTER_H_
#define _PYTHON_FILTER_H_

#include "python/inc/python.h"

/**
* \file Filter.h
* \brief Contains declaration of Filter class.
*/

namespace columbus { namespace python { namespace asg {
  /**
  * \brief Provides filtering mechanism for the ASG.
  */
  class Filter {
    public:

      /**
      * \brief The possible states of the Filter.
      */
      enum FilterState {

        /** \brief The node is filtered. */
        Filtered,

        /** \brief The node and all of its anchestors are not filtered. */
        NotFiltered
      };

    protected:

      /**
      * \internal
      * \brief Constructor.
      * \param fact [in] Reference to the Factory.
      */
      Filter(Factory& fact);

      /**
      * \brief Initializes the Filter.
      */
      void initializeFilter();

      /**
      * \brief Tells whether the node is filtered or not.
      * \param id              [in] The id of the node.
      * \throw PythonException Throws PythonException if the id is too large (larger than the size of the Filter).
      * \return Returns true if the node with the given id is filtered.
      */
      bool getIsFiltered(NodeId id) const;

      /**
      * \brief Filters out the given node and all of its descendants.
      * \param id              [in] The id of the node.
      * \throw PythonException Throws PythonException if the id is too large (larger than the size of the Filter).
      */
      void setFiltered(NodeId id);

      /**
      * \brief Sets the state of the node, all of its descendants and all of its ancestors to not filtered.
      * \param id              [in] The id of the node.
      * \throw PythonException Throws PythonException if the id is too large (larger than the size of the Filter).
      */
      void setNotFiltered(NodeId id);

      /**
      * \brief Sets the state of the node and all of its ancestors to not filtered.
      * \param id              [in] The id of the node.
      * \throw PythonException Throws PythonException if the id is too large (larger than the size of the Filter).
      */
      void setNotFilteredThisNode(NodeId id);

      /**
      * \internal
      * \brief Filter out only the given node (without its children).
      * \param id              [in] The id of the node.
      * \throw PythonException Throws PythonException if the id is too large (larger than the size of the Filter).
      */
      void setFilteredThisNodeOnly(NodeId id);

      /**
      * \internal
      * \brief Sets the state of the given node (without its children) to not filtered.
      * \param id              [in] The id of the node.
      * \throw PythonException Throws PythonException if the id is too large (larger than the size of the Filter).
      */
      void setNotFilteredThisNodeOnly(NodeId id);

      /**
      * \internal
      * \brief Gives back the state of the node.
      * \param id              [in] The id of the node.
      * \throw PythonException Throws PythonException if the id is too large (larger than the size of the Filter).
      * \return Returns the state of the node.
      */
      FilterState getFilterState(NodeId id) const;

      /**
      * \internal
      * \brief Saves the filter.
      * \param io [in] The filter is saved into "io".
      */
      void save(io::BinaryIO *io) const;

      /**
      * \internal
      * \brief Loads the filter.
      * \param io [in] The filter is loaded from "io".
      */
      void load(io::BinaryIO *io);

      /** \internal \brief Type definition for Container. */
      typedef std::vector<FilterState> Container;

      /** \internal \brief Contains the states of the nodes. */
      Container container;

      /** \internal \brief Reference to the factory. */
      Factory& factory;

      friend class Factory;

  }; // Filter


}}}
#endif

