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

#include "../../inc/metrics/NCL.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus { namespace lim { namespace metrics {

  //
  // COMMON STUFF
  //

  NCLBase::NCLBase( const string& name, bool total, bool enabled, SharedContainers* shared ) : MetricHandler( name, mdtInt, enabled, shared ) {
    
    if ( name == "NCL" ) {
      registerHandler( phaseVisit, NTYPE_LIM_CLASS, limLangOther, false, [this] ( NodeWrapper& node ) {
        processClass( node );
      });
    } else {
      dependencies.insert( "NCL" );
    }

    if ( total ) {
      propagateScopeSet( phaseFinalize, NTYPE_LIM_PACKAGE, limLangOther );
      propagateComponentSet();
    } else { // not total
      propagateScopeSet( phaseVisitEnd, NTYPE_LIM_PACKAGE, limLangOther );
    }

  }

  void NCLBase::processClass( NodeWrapper& node ) {

    string name, publicName;
    const logical::Class& clazz = node.getLimNode<logical::Class>();
    ClassKind clk = clazz.getClassKind();

    switch ( clk ) {
      case clkClass:        name = "NCL"; publicName = "NPCL"; break;
      case clkInterface:    name = "NIN"; publicName = "NPIN"; break;
      case clkEnum:         name = "NEN"; publicName = "NPEN"; break;
      case clkStruct:       name = "NST"; publicName = "NPST"; break;
      case clkUnion:        name = "NUN"; publicName = "NPUN"; break;
      default: break;
    }

    if ( name.empty() ) return;

    // Package level
    add( clazz, shared->currentPackageInfo(), name, publicName );

    // Component level
    ListIterator<base::Component> i = clazz.getBelongsToListIteratorBegin(), end = clazz.getBelongsToListIteratorEnd();
    for ( ; i != end; ++i ) {
      const base::Component& c = dynamic_cast<const base::Component&>( *i );
      Info& cInfo = shared->components.map[&c];
      add( clazz, cInfo, name, publicName );
    }
  }

  void NCLBase::add( const asg::logical::Class& clazz, Info& info, const string& name, const string& publicName ) {
    info.sets[name].insert( clazz.getId() );
    if ( clazz.getAccessibility() == ackPublic ) {
      info.sets[publicName].insert( clazz.getId() );
    }
  }

  const string& NCLBase::translateLevel( Language language, const string& level ) const {
    const string& newLevel = MetricHandler::translateLevel( language, level );

    if ( language == limLangCpp ) {
      if (
        newLevel == NTYPE_LIM_CLASS ||
        newLevel == NTYPE_LIM_INTERFACE ||
        newLevel == NTYPE_LIM_UNION ||
        newLevel == NTYPE_LIM_ENUM
      ) {
        return NTYPE_LIM_CLASS;
      }
    }

    else if ( language == limLangCsharp ) {
      if (
        newLevel == NTYPE_LIM_CLASS ||
        newLevel == NTYPE_LIM_INTERFACE ||
        newLevel == NTYPE_LIM_ENUM
      ) {
        return NTYPE_LIM_CLASS;
      }
    }

    return newLevel;
  }

}}}
