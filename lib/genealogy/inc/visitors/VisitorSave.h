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

#ifndef _GENEALOGY_VISITORSAVE_H_
#define _GENEALOGY_VISITORSAVE_H_

#include "genealogy/inc/genealogy.h"

/**
* \file VisitorSave.h
* \brief Contains declaration of VisitorSave class.
*/

namespace columbus { namespace genealogy { 
  /**
  * \brief Visitor for saving the graph.
  */
  class VisitorSave : public VisitorAbstractNodes {
    protected:
      /**
      * \brief Constructor for Visitor.
      * \param io [in] The graph is save into this IO.
      */
      VisitorSave(io::BinaryIO &io);

    public:
      /**
      * \brief Visitor for saving node.
      * \param node [in] This node is being saved.
      */
      virtual void visitEnd(const Base &node , bool callVirtualBase = true);

    protected:
      /** \internal \brief Pointer to the "output". */
      io::BinaryIO &m_io;

      friend class Factory;
  }; // VisitorSave


}}
#endif

