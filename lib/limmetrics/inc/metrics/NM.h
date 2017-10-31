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

#ifndef _METRICS_NM_H_
#define _METRICS_NM_H_

#include "../MetricHandler.h"

namespace columbus { namespace lim { namespace metrics {

  class NMBase : public MetricHandler {
    
    public:
      NMBase( const std::string& name, bool local, bool total, bool enabled, SharedContainers* shared );

    protected:
      void traverseClass( NodeWrapper& node );
      void processMethod( const asg::logical::Method& method, bool local );
      void add( const asg::logical::Method& method, Info& info, bool local, int inc, bool useSets );
      void innerAdd( const asg::logical::Method& method, Info& info, bool local, int inc, bool useSets, std::string normalName, std::string localName );
      const std::string& translateLevel( asg::Language language, const std::string& level ) const override;

      bool localMetric;
      bool totalMetric;
  };


  //
  // Specifications
  //

  class NM : public NMBase {
    public:
      NM( bool enabled, SharedContainers* shared ) : NMBase( "NM", false, false, enabled, shared ) {}
  };

  class NLM : public NMBase {
    public:
      NLM( bool enabled, SharedContainers* shared ) : NMBase( "NLM", true, false, enabled, shared ) {}
  };

  class NG : public NMBase {
    public:
      NG( bool enabled, SharedContainers* shared ) : NMBase( "NG", false, false, enabled, shared ) {}
  };

  class NLG : public NMBase {
    public:
      NLG( bool enabled, SharedContainers* shared ) : NMBase( "NLG", true, false, enabled, shared ) {}
  };

  class NS : public NMBase {
    public:
      NS( bool enabled, SharedContainers* shared ) : NMBase( "NS", false, false, enabled, shared ) {}
  };

  class NLS : public NMBase {
    public:
      NLS( bool enabled, SharedContainers* shared ) : NMBase( "NLS", true, false, enabled, shared ) {}
  };

  class NPM : public NMBase {
    public:
      NPM( bool enabled, SharedContainers* shared ) : NMBase( "NPM", false, false, enabled, shared ) {}
  };

  class NLPM : public NMBase {
    public:
      NLPM( bool enabled, SharedContainers* shared ) : NMBase( "NLPM", true, false, enabled, shared ) {}
  };

  class TNM : public NMBase {
    public:
      TNM( bool enabled, SharedContainers* shared ) : NMBase( "TNM", false, true, enabled, shared ) {}
  };

  class TNLM : public NMBase {
    public:
      TNLM( bool enabled, SharedContainers* shared ) : NMBase( "TNLM", true, true, enabled, shared ) {}
  };

  class TNG : public NMBase {
    public:
      TNG( bool enabled, SharedContainers* shared ) : NMBase( "TNG", false, true, enabled, shared ) {}
  };

  class TNLG : public NMBase {
    public:
      TNLG( bool enabled, SharedContainers* shared ) : NMBase( "TNLG", true, true, enabled, shared ) {}
  };

  class TNS : public NMBase{
    public:
      TNS( bool enabled, SharedContainers* shared ) : NMBase( "TNS", false, true, enabled, shared ) {}
  };

  class TNLS : public NMBase {
    public:
      TNLS( bool enabled, SharedContainers* shared ) : NMBase( "TNLS", true, true, enabled, shared ) {}
  };

  class TNPM : public NMBase {
    public:
      TNPM( bool enabled, SharedContainers* shared ) : NMBase( "TNPM", false, true, enabled, shared ) {}
  };

  class TNLPM : public NMBase {
    public:
      TNLPM( bool enabled, SharedContainers* shared ) : NMBase( "TNLPM", true, true, enabled, shared ) {}
  };

}}}

#endif
