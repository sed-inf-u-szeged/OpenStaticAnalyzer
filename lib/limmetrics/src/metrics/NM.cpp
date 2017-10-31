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

#include "../../inc/metrics/NM.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus { namespace lim { namespace metrics {

  //
  // Common Stuff
  // Handle every type of method counting in NM
  // Insert a dependency on NM in the others
  // And propagate the computed values
  //

  NMBase::NMBase( const string& name, bool local, bool total, bool enabled, SharedContainers* shared ) :
    MetricHandler( name, mdtInt, enabled, shared ), localMetric( local ), totalMetric( total )
  {
    if ( name == "NM" ) {

      registerHandler( phaseVisit, NTYPE_LIM_CLASS, limLangOther, false, [this] ( NodeWrapper& node ) {
        traverseClass( node );
        addMetric( node, this->shared->currentClassInfo().ints[this->name] );
      });

      registerHandler( phaseVisit, NTYPE_LIM_METHOD, limLangOther, false, [this] ( NodeWrapper& node ) {
        if ( ! node.isFunction() ) return;
        processMethod( node.getLimNode<const logical::Method&>(), true );
      });

      propagateScopeSet( phaseVisitEnd, NTYPE_LIM_PACKAGE, limLangOther );

    } else {

      dependencies.insert( "NM" );

      if ( total ) {
        propagateScopeInt( phaseFinalize, NTYPE_LIM_CLASS, limLangOther );
        if ( ! local ) {
          propagateScopeSet( phaseFinalize, NTYPE_LIM_PACKAGE, limLangOther );
          propagateComponentSet();
        }
      } else { // not total
        propagateScopeInt( phaseVisitEnd, NTYPE_LIM_CLASS, limLangOther );
        if ( ! local ) {
          propagateScopeSet( phaseVisitEnd, NTYPE_LIM_PACKAGE, limLangOther );
        }
      }

    }
  }

  void NMBase::traverseClass( NodeWrapper& node ) {

    const logical::Class& clazz = node.getLimNode<logical::Class>();

    // local methods
    ListIterator<logical::Member> i = clazz.getMemberListIteratorBegin(), end = clazz.getMemberListIteratorEnd();
    for ( ; i != end; ++i ) {
      if ( Common::getIsMethod( *i ) ) {
        const logical::Method& method = dynamic_cast<const logical::Method&>( *i );
        if ( !method.getDeclares() && !method.getIsContainedInIsEmpty() ) {
          processMethod( method, true );
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
        if ( Common::getIsMethod( *i ) ) {
          const logical::Method& method = dynamic_cast<const logical::Method&>( *i );
          if ( !method.getDeclares() && !method.getIsContainedInIsEmpty() ) {
            processMethod( method, false );
          }
        }
      }
    }
  }

  void NMBase::processMethod( const asg::logical::Method& method, bool local ) {

    int inc = 1;
    
    // override handling
    NodeId methodId = method.getId();
    int numOfAbstractOverrides = 0;
    if ( shared->overrides->getIsOverride( methodId ) )
    {
      OverrideRelations::IdList idList = shared->overrides->getOverrideList( methodId );
      OverrideRelations::IdList::iterator it = idList.begin();
      for ( ; it != idList.end(); ++it )
      {
        const logical::Method& overridden = dynamic_cast<logical::Method&>( shared->factory->getRef( *it ) );
        bool isFiltered = shared->factory->getFilterState( overridden.getId() ) == lim::asg::Filter::Filtered;
        if ( overridden.getIsAbstract() && !isFiltered )
        {
          numOfAbstractOverrides++;
        }
      }
    }

    inc = 1 - numOfAbstractOverrides;

    // class level NM
    if ( ! shared->classStack.empty() ) {
      add( method, shared->currentClassInfo(), local, inc, false );
    }

    // package level NM
    if ( local ) {
      add( method, shared->currentPackageInfo(), false, 1, true );
    }

    // component level NM
    ListIterator<base::Component> i = method.getBelongsToListIteratorBegin(), end = method.getBelongsToListIteratorEnd();
    for ( ; i != end; ++i ) {
      const base::Component& c = dynamic_cast<const base::Component&>( *i );
      Info& cInfo = shared->components.map[&c];
      add( method, cInfo, false, 1, true );
    }
  }

  void NMBase::add( const asg::logical::Method& method, Info& info, bool local, int inc, bool useSets ) {

    innerAdd( method, info, local, inc, useSets, "NM", "NLM" );

    if ( method.getMethodKind() == mekGet ) {
      innerAdd( method, info, local, inc, useSets, "NG", "NLG" );
    }

    if ( method.getMethodKind() == mekSet ) {
      innerAdd( method, info, local, inc, useSets, "NS", "NLS" );
    }

    if ( method.getAccessibility() == ackPublic ) {
      innerAdd( method, info, local, inc, useSets, "NPM", "NLPM" );
    }

  }

  void NMBase::innerAdd( const asg::logical::Method& method, Info& info, bool local, int inc, bool useSets, string normalName, string localName ) {
    if ( useSets ) {
      if ( inc > 0 ) {
        info.sets[normalName].insert( method.getId() );
      }
      if ( local ) {
        info.sets[localName].insert( method.getId() );
      }
    } else {
      if ( inc > 0 ) {
        info.ints[normalName]++;
      }
      if ( local ) {
        info.ints[localName]++;
      }
    }
  }

  // Classes/Structs are merged with Interfaces (and Unions for non-local metrics)
  const string& NMBase::translateLevel( Language language, const string& level ) const {
    const string& newLevel = MetricHandler::translateLevel( language, level );

    if ( language == limLangCpp ) {
      if (
        newLevel == NTYPE_LIM_CLASS ||
        newLevel == NTYPE_LIM_INTERFACE
      ) {
        return NTYPE_LIM_CLASS;
      }

      if ( ! localMetric && newLevel == NTYPE_LIM_UNION ) {
        return NTYPE_LIM_CLASS;
      }
    }

    else if ( language == limLangCsharp ) {
      if (
        newLevel == NTYPE_LIM_CLASS ||
        newLevel == NTYPE_LIM_INTERFACE
      ) {
        return NTYPE_LIM_CLASS;
      }
    }

    return newLevel;
  }

}}}
