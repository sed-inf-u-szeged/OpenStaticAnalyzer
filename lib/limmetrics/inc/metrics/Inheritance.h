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

#ifndef _METRICS_INHERITANCE_H_
#define _METRICS_INHERITANCE_H_

#include "../MetricHandler.h"

namespace columbus { namespace lim { namespace metrics {

  class InheritanceBase : public MetricHandler {
    public:
      InheritanceBase( const std::string& name, MetricDataTypes type, bool enabled, SharedContainers* shared );
    protected:
      const std::string& translateLevel( asg::Language language, const std::string& level ) const override;
  };

  class NOP : public InheritanceBase {
    public:
      NOP( bool enabled, SharedContainers* shared );
  };

  class NOA : public InheritanceBase {
    public:
      NOA( bool enabled, SharedContainers* shared );
  };

  class NOC : public InheritanceBase {
    public:
      NOC( bool enabled, SharedContainers* shared );
  };

  class NOD : public InheritanceBase {
    public:
      NOD( bool enabled, SharedContainers* shared );
  };

  class DIT : public InheritanceBase {
    public:
      DIT( bool enabled, SharedContainers* shared );
  };

}}}

#endif
