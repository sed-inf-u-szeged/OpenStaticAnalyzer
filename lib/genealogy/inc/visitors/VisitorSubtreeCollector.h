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

#ifndef _GENEALOGY_VISITORSUBTREECOLLECTOR_H_
#define _GENEALOGY_VISITORSUBTREECOLLECTOR_H_

#include "genealogy/inc/genealogy.h"

/**
* \file VisitorSubtreeCollector.h
* \brief Contains declaration of VisitorSubtreeCollector class.
*/

namespace columbus { namespace genealogy { 
  /**
  * \brief Visitor ...
  */
  class VisitorSubtreeCollector : public VisitorAbstractNodes {
    public:
      /**
      * \brief Constructor for Visitor.
      * \param nodelist [in, out] The list where the id of the visited nodes are inserted.
      */
      VisitorSubtreeCollector(std::list< NodeId> &nodelist);

      /**
      * \brief Visitor for all nodes.
      * \param node [in] This node is being visited.
      */
      virtual void visit(const Base &node, bool callVirtualBase = true);

    protected:
      /** \internal \brief Reference to the list where the ids will be collected. */
      std::list<NodeId> &nodelist;

  }; // VisitorSave


}}
#endif

