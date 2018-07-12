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

#ifndef _CSHARP_ALGORITHM_H_
#define _CSHARP_ALGORITHM_H_

#include "csharp/inc/csharp.h"

/**
* \file Algorithm.h
* \brief Contains declaration of Algorithm class.
*/

namespace columbus { namespace csharp { namespace asg {
  /**
  * \brief Common base class for all algorithm classes.
  */
  class Algorithm {
    public:
      /**
      * \internal
      * \brief The constructor.
      */
      Algorithm(){}

      /**
      * \internal
      * \brief The virtual destructor.
      */
      virtual ~Algorithm(){}

    protected:
      /**
      * \internal
      * \brief Increases the depth of the given visitor.
      * \param v [in] The visitor class.
      */
      void incVisitorDepth(Visitor& v);

      /**
      * \internal
      * \brief Decreases the depth of the given visitor.
      * \param v [in] The visitor class.
      */
      void decVisitorDepth(Visitor& v);

  }; // Algorithm


}}}
#endif

