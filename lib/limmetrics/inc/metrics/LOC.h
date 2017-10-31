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

#ifndef _METRICS_LLOC_H_
#define _METRICS_LLOC_H_

#include "../MetricHandler.h"

namespace columbus { namespace lim { namespace metrics {

  class LOCBase : public MetricHandler {

    public:

      typedef unsigned int (asg::logical::Scope::*ScopePtr) () const;
      typedef unsigned int (asg::physical::File::*FilePtr) () const;
      typedef unsigned int (asg::base::Component::*ComponentPtr) () const;

      /**
      * Sets up a common handler that uses the getValue* methods as a "template methods"
      */
      LOCBase( const std::string& name, bool enabled, ScopePtr scopePtr, FilePtr filePtr, ComponentPtr componentPtr );

    protected:

      /**
      * The level translation redirects methods, classes and packages to the common Scope handler
      */
      virtual const std::string& translateLevel( asg::Language language, const std::string& level ) const;

    public:
      ScopePtr scopePtr;
      FilePtr filePtr;
      ComponentPtr componentPtr;
  };

  /**
  * Specialized implementation for LOC
  */
  class LOC : public LOCBase {
    public:
      LOC( bool enabled );
  };

  /**
  * Specialized implementation for LLOC
  */
  class LLOC : public LOCBase {
    public:
      LLOC( bool enabled );
  };

  /**
  * Specialized implementation for TLOC
  */
  class TLOC : public LOCBase {
    public:
      TLOC( bool enabled );
  };

  /**
  * Specialized implementation for TLLOC
  */
  class TLLOC : public LOCBase {
    public:
      TLLOC( bool enabled );
  };

}}}

#endif
