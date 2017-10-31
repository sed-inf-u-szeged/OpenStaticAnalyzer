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

#ifndef _METRICS_CBO_H_
#define _METRICS_CBO_H_

#include "../MetricHandler.h"

namespace columbus { namespace lim { namespace metrics {

  class CBOBase : public MetricHandler {
    public:
      CBOBase( const std::string& name, MetricDataTypes type, bool enabled, SharedContainers* shared = NULL );
    protected:
      const std::string& translateLevel( asg::Language language, const std::string& level ) const override;
  };

  class CBO : public CBOBase {
    public:
      CBO( bool enabled, SharedContainers* shared );
    private:
      void collectUsedClasses( const asg::base::Base& to, const asg::logical::Class& node, std::set<const asg::logical::Class*>& usedClasses) const;
      void getClassOfType( const asg::type::Type& type, const asg::logical::Class& node, std::set<const asg::logical::Class*>& usedClasses ) const;
      const asg::logical::Class* getClassOfReferencedMember( const asg::logical::Class& fromClass, const asg::logical::Member& referedMember ) const;
  };

  class CBOI : public CBOBase {
    public:
      CBOI( bool enabled, SharedContainers* shared );
  };

  class TCBO : public MetricHandler {
    public:
      TCBO(bool enabled, SharedContainers* shared);
  };

}}}

#endif
