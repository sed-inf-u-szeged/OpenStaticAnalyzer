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

#include "../../inc/metrics/NA.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus { namespace lim { namespace metrics {

  //
  // COMMON STUFF
  //

  NABase::NABase( const string& name, bool local, bool total, bool enabled, SharedContainers* shared )
    : MetricHandler( name, mdtInt, enabled, shared ), localMetric( local ), totalMetric( total )
  {
    if ( name == "NA" ) {

      registerHandler( phaseVisit, NTYPE_LIM_CLASS, limLangOther, false, [this] ( NodeWrapper& node ) {
        traverseClass( node );
        addMetric( node, (int) this->shared->currentClassInfo().sets[this->name].size() );
      });

      propagateScopeSet( phaseVisitEnd, NTYPE_LIM_PACKAGE, limLangOther );

    } else {

      dependencies.insert( "NA" );

      if ( total ) {
        propagateScopeSet( phaseFinalize, NTYPE_LIM_CLASS, limLangOther );
        if ( ! local ) {
          propagateScopeSet( phaseFinalize, NTYPE_LIM_PACKAGE, limLangOther );
          propagateComponentSet();
        }
      } else { // not total
        propagateScopeSet( phaseVisitEnd, NTYPE_LIM_CLASS, limLangOther );
        if ( ! local ) {
          propagateScopeSet( phaseVisitEnd, NTYPE_LIM_PACKAGE, limLangOther );
        }
      }

    }
  }

  void NABase::traverseClass( NodeWrapper& node ) {

    const logical::Class& clazz = node.getLimNode<logical::Class>();

    // local methods
    ListIterator<logical::Member> i = clazz.getMemberListIteratorBegin(), end = clazz.getMemberListIteratorEnd();
    for ( ; i != end; ++i ) {
      if ( Common::getIsAttribute( *i ) ) {
        const logical::Attribute& attr = dynamic_cast<const logical::Attribute&>( *i );
        if ( !attr.getDeclares() && !attr.getIsContainedInIsEmpty() ) {
          processAttribute( attr, true );
        }
      }
    }

    // inherited methods
    set<const logical::Class*> ancestors;
    shared->inheritance->collectAncestors( clazz, ancestors );

    set<const logical::Class*>::iterator aIt = ancestors.begin(), aEnd = ancestors.end();
    for ( ; aIt != aEnd; ++aIt ) {

      const logical::Class& aClass = *dynamic_cast<const logical::Class*>( *aIt );

      ListIterator<logical::Member> i = aClass.getMemberListIteratorBegin(), end = aClass.getMemberListIteratorEnd();
      for ( ; i != end; ++i ) {
        if ( Common::getIsAttribute( *i ) ) {
          const logical::Attribute& attr = dynamic_cast<const logical::Attribute&>( *i );
          if ( !attr.getDeclares() && !attr.getIsContainedInIsEmpty() ) {
            processAttribute( attr, false );
          }
        }
      }
    }

  }

  void NABase::processAttribute( const asg::logical::Attribute& attr, bool local ) {

    // class level NA
    add( attr, shared->currentClassInfo(), local );
    
    // package level NA
    if ( local ) {
      add( attr, shared->currentPackageInfo(), false );
    }

    // component level NA
    ListIterator<base::Component> i = attr.getBelongsToListIteratorBegin(), end = attr.getBelongsToListIteratorEnd();
    for ( ; i != end; ++i ) {
      const base::Component& c = dynamic_cast<const base::Component&>( *i );
      Info& cInfo = shared->components.map[&c];
      add( attr, cInfo, false );
    }
  }

  void NABase::add( const asg::logical::Attribute& attr, Info& info, bool local ) {

    innerAdd( attr, info, local, "NA", "NLA" );

    if ( attr.getAccessibility() == ackPublic )
    {
      innerAdd( attr, info, local, "NPA", "NLPA" );
    }
  }

  void NABase::innerAdd( const asg::logical::Attribute& attr, Info& info, bool local, string normalName, string localName ) {
    info.sets[normalName].insert( attr.getId() );
    if ( local ) {
      info.sets[localName].insert( attr.getId() );
    }
  }

  
  const string& NABase::translateLevel( Language language, const string& level ) const {
    const string& newLevel = MetricHandler::translateLevel( language, level );

    // C
    if ( language == limLangC ) {
      // Struct/Union
      if (
        ( name == "NA" || name == "TNA" ) &&
        ( newLevel == NTYPE_LIM_STRUCTURE || newLevel == NTYPE_LIM_UNION )
      ) {
        return NTYPE_LIM_CLASS;
      }

      // Enum
      if ( name == "NA" && newLevel == NTYPE_LIM_ENUM ) {
        return NTYPE_LIM_CLASS;
      }
    }

    // C++
    // Classes/Structs are merged with Interfaces (and Unions for non-local metrics) (and Enums for NA only)
    if ( language == limLangCpp ) {
      if (
        newLevel == NTYPE_LIM_CLASS ||
        newLevel == NTYPE_LIM_INTERFACE ||
        ( ! localMetric && newLevel == NTYPE_LIM_UNION ) ||
        ( name == "NA" && newLevel == NTYPE_LIM_ENUM )
      ) {
        return NTYPE_LIM_CLASS;
      }
    }

    // C#
    // Classes/Structs are merged with Interfaces and Enums for NA only
    if ( language == limLangCsharp ) {
      if (
        newLevel == NTYPE_LIM_CLASS ||
        newLevel == NTYPE_LIM_INTERFACE ||
        ( name == "NA" && newLevel == NTYPE_LIM_ENUM )
      ) {
        return NTYPE_LIM_CLASS;
      }
    }

    return newLevel;
  }

}}}
