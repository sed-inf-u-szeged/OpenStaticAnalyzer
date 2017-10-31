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

#ifndef _METRICS_NL_H_
#define _METRICS_NL_H_

#include "../MetricHandler.h"

namespace columbus { namespace lim { namespace metrics {

  class NLBase : public MetricHandler {

    public:
      NLBase( const std::string& name, MetricDataTypes type, bool enabled );

    protected:
      virtual int getValue( const asg::logical::Method& method ) = 0;
      const std::string& translateLevel( asg::Language language, const std::string& level ) const override;
  };

  class NL : public NLBase {

    public:
      NL( bool enabled );

    protected:
      virtual int getValue( const asg::logical::Method& method );
  };

  class NLE : public NLBase {

    public:
      NLE( bool enabled );

    protected:
      virtual int getValue( const asg::logical::Method& method );
  };

}}}

#endif
