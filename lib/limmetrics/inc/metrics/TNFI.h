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

#ifndef _METRICS_TNFI_H_
#define _METRICS_TNFI_H_

#include "../MetricHandler.h"

namespace columbus { namespace lim { namespace metrics {

  class TNFIDIBase : public MetricHandler {
    public:
      TNFIDIBase( const std::string& name, MetricDataTypes type, bool enabled, SharedContainers* shared = NULL );
    protected:
      const std::string& translateLevel( asg::Language language, const std::string& level ) const override;
  };

  class TNFI : public TNFIDIBase {
    public:
      TNFI( bool enabled, SharedContainers* shared );
    private:
      void collectFilesAndDirsForComponent( const asg::base::Component& component, std::set<NodeId>& fileSet, std::set<NodeId>& dirSet );
      void collectFilesAndDirsRecursively( const asg::logical::Member& member, std::set<NodeId>& fileSet, std::set<NodeId>& dirSet );
      void collectFilesAndDirsForMember( const asg::logical::Member& member, std::set<NodeId>& fileSet, std::set<NodeId>& dirSet );
  };

  class TNDI : public TNFIDIBase {
    public:
      TNDI( bool enabled, SharedContainers* shared );
  };

}}}

#endif
