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

#ifndef _METRICS_NCL_H_
#define _METRICS_NCL_H_

#include "../MetricHandler.h"

namespace columbus { namespace lim { namespace metrics {

  class NCLBase : public MetricHandler {
    
    public:
      NCLBase( const std::string& name, bool total, bool enabled, SharedContainers* shared );

    protected:
      void processClass( NodeWrapper& node );
      void add( const asg::logical::Class& clazz, Info& info, const std::string& name, const std::string& publicName );
      const std::string& translateLevel( asg::Language language, const std::string& level ) const override;
  };

  class NCL : public NCLBase {
    public:
      NCL( bool enabled, SharedContainers* shared ) : NCLBase( "NCL", false, enabled, shared ) {}
  };

  class NIN : public NCLBase {
    public:
      NIN( bool enabled, SharedContainers* shared ) : NCLBase( "NIN", false, enabled, shared ) {}
  };

  class NEN : public NCLBase {
    public:
      NEN( bool enabled, SharedContainers* shared ) : NCLBase( "NEN", false, enabled, shared ) {}
  };

  class NST : public NCLBase {
    public:
      NST( bool enabled, SharedContainers* shared ) : NCLBase( "NST", false, enabled, shared ) {}
  };

  class NUN : public NCLBase {
    public:
      NUN( bool enabled, SharedContainers* shared ) : NCLBase( "NUN", false, enabled, shared ) {}
  };

  class TNCL : public NCLBase {
    public:
      TNCL( bool enabled, SharedContainers* shared ) : NCLBase( "TNCL", true, enabled, shared ) {}
  };

  class TNIN : public NCLBase {
    public:
      TNIN( bool enabled, SharedContainers* shared ) : NCLBase( "TNIN", true, enabled, shared ) {}
  };

  class TNEN : public NCLBase {
    public:
      TNEN( bool enabled, SharedContainers* shared ) : NCLBase( "TNEN", true, enabled, shared ) {}
  };

  class TNST : public NCLBase {
    public:
      TNST( bool enabled, SharedContainers* shared ) : NCLBase( "TNST", true, enabled, shared ) {}
  };

  class TNUN : public NCLBase {
    public:
      TNUN( bool enabled, SharedContainers* shared ) : NCLBase( "TNUN", true, enabled, shared ) {}
  };

  class TNPCL : public NCLBase {
    public:
      TNPCL( bool enabled, SharedContainers* shared ) : NCLBase( "TNPCL", true, enabled, shared ) {}
  };

  class TNPIN : public NCLBase {
    public:
      TNPIN( bool enabled, SharedContainers* shared ) : NCLBase( "TNPIN", true, enabled, shared ) {}
  };

  class TNPEN : public NCLBase {
    public:
      TNPEN( bool enabled, SharedContainers* shared ) : NCLBase( "TNPEN", true, enabled, shared ) {}
  };

  class TNPST : public NCLBase {
    public:
      TNPST( bool enabled, SharedContainers* shared ) : NCLBase( "TNPST", true, enabled, shared ) {}
  };

  class TNPUN : public NCLBase {
    public:
      TNPUN( bool enabled, SharedContainers* shared ) : NCLBase( "TNPUN", true, enabled, shared ) {}
  };
  

}}}

#endif
