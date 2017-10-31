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

#ifndef _METRICS_DOCUMENTATION_H_
#define _METRICS_DOCUMENTATION_H_

#include "../MetricHandler.h"

namespace columbus { namespace lim { namespace metrics {

  class DocBase : public MetricHandler {
    public:
      DocBase( const std::string& name, MetricDataTypes type, bool enabled, SharedContainers* shared = NULL );
    protected:
      const std::string& translateLevel( asg::Language language, const std::string& level ) const override;
  };

  class DLOC : public DocBase {
    public:
      DLOC( bool enabled, SharedContainers* shared );
    protected:
      const std::string& translateLevel( asg::Language language, const std::string& level ) const override;
    private:
      void mapComments( const asg::logical::Member& node, Info& info ) const;
  };

  class CLOC : public DocBase {
    public:
      CLOC( bool enabled, SharedContainers* shared );
    protected:
      const std::string& translateLevel( asg::Language language, const std::string& level ) const override;
  };

  class TCLOC : public DocBase {
    public:
      TCLOC( bool enabled, SharedContainers* shared );
    protected:
      const std::string& translateLevel( asg::Language language, const std::string& level ) const override;
  };

  class PDA : public DocBase {
    public:
      PDA( bool enabled, SharedContainers* shared );
    protected:
      const std::string& translateLevel( asg::Language language, const std::string& level ) const override;
    private:
      void process( NodeWrapper& node );
      const asg::logical::Scope& resolve( const asg::logical::Scope& scope );
      bool isClassPublic( const asg::logical::Scope& scope ) const;
      bool isPackagePublic( const asg::logical::Scope& scope ) const;
      bool isFilePublic( const asg::logical::Scope& scope ) const;
      void add( const asg::logical::Scope& scope, Info::SetMap& sets, bool isPublic, bool documented );

      std::map<columbus::Key, const asg::logical::Scope*> resolveMap;
  };

  class TPDA : public DocBase {
    public:
      TPDA( bool enabled, SharedContainers* shared );
  };

  class PUABase : public DocBase {
    public:
      PUABase( bool total, bool enabled, SharedContainers* shared );
    protected:
      void computeScope( NodeWrapper& node, bool total );
      void computeComponent( NodeWrapper& node );
      void compute( NodeWrapper& node, Info::SetMap& sets, bool total );
  };

  class PUA : public PUABase {
    public:
      PUA( bool enabled, SharedContainers* shared );
    protected:
      const std::string& translateLevel( asg::Language language, const std::string& level ) const override;
  };

  class TPUA : public PUABase {
    public:
      TPUA( bool enabled, SharedContainers* shared );
  };

  class ADBase : public DocBase {
    public:
      ADBase( bool total, bool enabled, SharedContainers* shared );
    protected:
      void computeScope( NodeWrapper& node, bool total );
      void computeComponent( NodeWrapper& node );
      void compute( NodeWrapper& node, Info::SetMap& sets, bool total );
      const std::string& translateLevel( asg::Language language, const std::string& level ) const override;
  };

  class AD : public ADBase {
    public:
      AD( bool enabled, SharedContainers* shared );
  };

  class TAD : public ADBase {
    public:
      TAD( bool enabled, SharedContainers* shared );
  };

  class CDBase : public DocBase {
    public:
      typedef unsigned int (asg::logical::Scope::*ScopePtr) () const;
      typedef unsigned int (asg::base::Component::*ComponentPtr) () const;

      CDBase( bool total, bool enabled, SharedContainers* shared );
    protected:
      const std::string& translateLevel( asg::Language language, const std::string& level ) const override;
    private:
      ScopePtr scopeLLOC;
      ComponentPtr componentLLOC;
      std::string CLOC;
  };

  class CD : public CDBase {
    public:
      CD( bool enabled, SharedContainers* shared );
  };

  class TCD : public CDBase {
    public:
      TCD( bool enabled, SharedContainers* shared );
  };

}}}

#endif
