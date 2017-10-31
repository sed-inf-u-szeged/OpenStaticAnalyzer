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

#include "../../inc/metrics/TNFI.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus { namespace lim { namespace metrics {

  TNFIDIBase::TNFIDIBase( const std::string& name, MetricDataTypes type, bool enabled, SharedContainers* shared ) :
    MetricHandler( name, type, enabled, shared ) {}

  const std::string& TNFIDIBase::translateLevel( asg::Language language, const std::string& level ) const {
    const string& newLevel = MetricHandler::translateLevel( language, level );

    if ( language == limLangPython ) {
      if ( level == NTYPE_LIM_MODULE ) {
        return NTYPE_LIM_MODULE;
      }
    }

    return newLevel;
  }

  TNFI::TNFI( bool enabled, SharedContainers* shared ) : TNFIDIBase( "TNFI", mdtInt, enabled, shared ) {

    registerHandler( phaseVisit, NTYPE_LIM_PACKAGE, limLangOther, false, [this]( NodeWrapper& node ) {
      Info& info = this->shared->currentPackageInfo();
      collectFilesAndDirsRecursively( node.getLimNode<logical::Package>(), info.sets["NFI"], info.sets["NDI"] );
    });

    registerHandler( phaseVisit, NTYPE_LIM_COMPONENT, limLangOther, false, [this]( NodeWrapper& node ) {
      const base::Component* ptr = & node.getLimNode<base::Component>();
      Info& info = this->shared->components.map[ptr];
      collectFilesAndDirsForComponent( *ptr, info.sets["NFI"], info.sets["NDI"] );
    });

    propagateScopeSet( phaseFinalize, NTYPE_LIM_PACKAGE, limLangOther );
    propagateComponentSet();
  }

  void TNFI::collectFilesAndDirsForComponent( const base::Component& component, set<NodeId>& fileSet, set<NodeId>& dirSet )
  {
    // We reach File from Component using reverse belongsTo edge, then isContained edge
    // ( instead of direct hasFile edge which is currently missing )
    ListIterator<base::Base> memberIt = shared->factory->getReverseEdges().constIteratorBegin( component.getId(), edkMember_BelongsTo );
    for ( ; memberIt != shared->factory->getReverseEdges().constIteratorEnd( component.getId(), edkMember_BelongsTo ); ++memberIt )
    {
      const logical::Member& member = dynamic_cast<const logical::Member&>( *memberIt );

      // Packages are skipped, because they can span over different components
      if ( Common::getIsPackage( member ) &&  dynamic_cast<const logical::Package&>( member ).getPackageKind() == pkPackage ) {
        continue;
      }

      collectFilesAndDirsForMember( member, fileSet, dirSet );
    }
  }

  void TNFI::collectFilesAndDirsRecursively( const logical::Member& member, set<NodeId>& fileSet, set<NodeId>& dirSet ) {
    collectFilesAndDirsForMember( member, fileSet, dirSet );
    
    if ( Common::getIsScope( member ) )
    {
      const logical::Scope& scope = dynamic_cast<const logical::Scope&>( member );
      ListIterator<logical::Member> it = scope.getMemberListIteratorBegin();
      for ( ; it != scope.getMemberListIteratorEnd(); ++it )
      {
        collectFilesAndDirsRecursively( *it, fileSet, dirSet );
      }
    }
  }

  void TNFI::collectFilesAndDirsForMember( const logical::Member& member, set<NodeId>& fileSet, set<NodeId>& dirSet ) {

    ListIteratorAssocSourcePosition<physical::File> fileIt = member.getIsContainedInListIteratorAssocBegin();
    for ( ; fileIt != member.getIsContainedInListIteratorAssocEnd(); ++fileIt )
    {
      // file added to the related files set
      fileSet.insert( fileIt->getId() );

      // containing directories added to the related directories set
      NodeId step = fileIt->getId();
      for ( ;; )
      {
        bool going = false;
        ListIterator<base::Base> folderIt = shared->factory->getReverseEdges().constIteratorBegin( step, edkFolder_Contains );
        for ( ; folderIt != shared->factory->getReverseEdges().constIteratorEnd( step, edkFolder_Contains ); ++folderIt )
        {
          if ( Common::getIsFolder( *folderIt ) )
          {
            step = folderIt->getId();
            dirSet.insert( step );
            going = true;
            break;
          }
        }

        if ( going ) continue;
        else break;
      }
    }
  }

  TNDI::TNDI( bool enabled, SharedContainers* shared ) : TNFIDIBase( "TNDI", mdtInt, enabled, shared ) {

    dependencies.insert( "TNFI" );

    propagateScopeSet( phaseFinalize, NTYPE_LIM_PACKAGE, limLangOther );
    propagateComponentSet();

  }

}}}
