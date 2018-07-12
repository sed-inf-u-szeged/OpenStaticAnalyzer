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

#ifndef _METRICS_NA_H_
#define _METRICS_NA_H_

#include "../MetricHandler.h"

namespace columbus { namespace lim { namespace metrics {

  class NABase : public MetricHandler {
    
    public:
      NABase( const std::string& name, bool local, bool total, bool enabled, SharedContainers* shared );

    protected:
      void traverseClass( NodeWrapper& node );
      void processAttribute( const asg::logical::Attribute& attr, bool local );
      void add( const asg::logical::Attribute& attr, Info& info, bool local );
      void innerAdd( const asg::logical::Attribute& attr, Info& info, bool local, std::string normalName, std::string localName );
      const std::string& translateLevel( asg::Language language, const std::string& level ) const override;

      bool localMetric;
      bool totalMetric;
  };

  class NA : public NABase {
    public:
      NA( bool enabled, SharedContainers* shared ) : NABase( "NA", false, false, enabled, shared ) {}
  };

  class NLA : public NABase {
    public:
      NLA( bool enabled, SharedContainers* shared ) : NABase( "NLA", true, false, enabled, shared ) {}
  };

  class NPA : public NABase {
    public:
      NPA( bool enabled, SharedContainers* shared ) : NABase( "NPA", false, false, enabled, shared ) {}
  };

  class NLPA : public NABase {
    public:
      NLPA( bool enabled, SharedContainers* shared ) : NABase( "NLPA", true, false, enabled, shared ) {}
  };

  class TNA : public NABase {
    public:
      TNA( bool enabled, SharedContainers* shared ) : NABase( "TNA", false, true, enabled, shared ) {}
  };

  class TNLA : public NABase {
    public:
      TNLA( bool enabled, SharedContainers* shared ) : NABase( "TNLA", true, true, enabled, shared ) {}
  };

  class TNPA : public NABase {
    public:
      TNPA( bool enabled, SharedContainers* shared ) : NABase( "TNPA", false, true, enabled, shared ) {}
  };

  class TNLPA : public NABase {
    public:
      TNLPA( bool enabled, SharedContainers* shared ) : NABase( "TNLPA", true, true, enabled, shared ) {}
  };

}}}

#endif
