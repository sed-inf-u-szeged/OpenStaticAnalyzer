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

#include "../inc/Containers.h"
#include <iostream>

using namespace std;
using namespace common;
using namespace columbus::lim::asg;

namespace columbus { namespace lim { namespace metrics {

  //
  // INHERITANCE HELPER
  //

  InheritanceHelper::InheritanceHelper( const asg::ReverseEdges& reverseEdges ) :
    reverseEdges( reverseEdges ),
    upCache(),
    downCache()
    {}

  void InheritanceHelper::collectParents( const asg::logical::Class& node, std::set<const asg::logical::Class*>& parents ) {
    Common::collectParents( reverseEdges, node, parents );
  }

  int InheritanceHelper::collectAncestors( const asg::logical::Class& node, std::set<const asg::logical::Class*>& ancestors ) {
    return Common::collectAncestors( reverseEdges, node, ancestors, &upCache );
  }

  void InheritanceHelper::collectChildren( const asg::logical::Class& node, std::set<const asg::logical::Class*>& children ) {
    // children of the instances of the node
    for ( ListIterator<logical::Member> ii = node.getInstanceListIteratorBegin(); ii != node.getInstanceListIteratorEnd(); ++ii ) {
      if ( Common::getIsClass( *ii ) ) {
        const logical::Class* c = dynamic_cast<const logical::Class*>( &(*ii) );
        Common::collectChildren( reverseEdges, *c, children );
      }
    }

    // children of the node itself
    Common::collectChildren( reverseEdges, node, children );
  }

  int InheritanceHelper::collectDescendants( const asg::logical::Class& node, std::set<const asg::logical::Class*>& descendants ) {
    // descendants of the instances of the node
    for ( ListIterator<logical::Member> ii = node.getInstanceListIteratorBegin(); ii != node.getInstanceListIteratorEnd(); ++ii ) {
      if ( Common::getIsClass( *ii ) ) {
        const logical::Class* c = dynamic_cast<const logical::Class*>( &(*ii) );
        Common::collectDescendants( reverseEdges, *c, descendants, &downCache );
      }
    }

    // descendants of the node itself
    return Common::collectDescendants( reverseEdges, node, descendants, &downCache );
  }


  //
  // INFO
  //

  Info::Info() :
    aggregated( false ),
    ints(),
    sets(),
    maps()
  {}

  Info& Info::merge( const Info& other ) {

    // ints
    map<const string, int>::const_iterator ii = other.ints.begin();
    for ( ; ii != other.ints.end(); ++ii )
    {
      ints[ii->first] += ii->second;
    }

    // sets
    map<const string, set<NodeId> >::const_iterator i = other.sets.begin();
    for ( ; i != other.sets.end(); ++i )
    {
      set<NodeId>::const_iterator j = i->second.begin();
      for ( ; j != i->second.end(); ++j ) sets[i->first].insert( *j );
    }

    // maps
    map<const string, map<NodeId, int> >::const_iterator k = other.maps.begin();
    for ( ; k != other.maps.end(); ++k )
    {
      map<NodeId, int>::const_iterator l = k->second.begin();
      for ( ; l != k->second.end(); ++l ) maps[k->first][l->first] = l->second;
    }

    return *this;
  }

  int Info::mapCount( const string& name ) {
    unsigned int sum = 0;
    map<const string, map<NodeId, int>>::iterator mapIt = maps.find( name );
    if ( mapIt == maps.end() ) {
      return 0;
    }
    std::map<NodeId, int>::const_iterator i = mapIt->second.begin();
    for ( ; i != mapIt->second.end(); ++i ) {
      sum += i->second;
    }
    return sum;
  }

  void Info::dumpInt( const std::string& key ) {
    cout << "Info.ints[" << key << "] = " << ints[key] << endl;
  }

  void Info::dumpSet( const std::string& key ) {
    cout << "Info.sets[" << key << "] = {";
    for ( set<NodeId>::const_iterator i = sets[key].begin(); i != sets[key].end(); ++i ) {
      cout << *i << ", ";
    }
    cout << "} , size = " << sets[key].size() << endl;
  }

  void Info::dumpMap( const std::string& key ) {
    // TODO
  }

  //
  // SHARED CONTAINER BASE
  //

  void SharedContainer::phaseOver( DispatchPhases phase ) {
    ContainerType::iterator i = map.begin(), end = map.end();
    for ( ; i != end; ++i ) {
      aggregate( phase, i->first, i->second );
    }
  }

  Info& SharedContainer::aggregate( DispatchPhases phase, const asg::base::Base* ptr, Info& info ) {
    return info;
  }

  void SharedContainer::totalize( Info& info ) {
    Info::IntMap newIntMap;
    Info::IntMap::iterator intIt = info.ints.begin(), intEnd = info.ints.end();
    for ( ; intIt != intEnd; ++intIt ) {
      newIntMap["T" + intIt->first] = intIt->second;
    }
    info.ints = newIntMap;

    Info::SetMap newSetMap;
    Info::SetMap::iterator setIt = info.sets.begin(), setEnd = info.sets.end();
    for ( ; setIt != setEnd; ++setIt ) {
      newSetMap["T" + setIt->first] = setIt->second;
    }
    info.sets = newSetMap;

    Info::MapMap newMapMap;
    Info::MapMap::iterator mapIt = info.maps.begin(), mapEnd = info.maps.end();
    for ( ; mapIt != mapEnd; ++mapIt ) {
      newMapMap["T" + mapIt->first] = mapIt->second;
    }
    info.maps = newMapMap;
  }

  //
  // COMPONENTS
  // 

  Info& ComponentMap::aggregate( DispatchPhases phase, const base::Base* ptr, Info& info ) {
    if ( phase == phaseFinishVisit && !info.aggregated ) {

      info.aggregated = true;
      const base::Component& component = dynamic_cast<const base::Component&>( *ptr );

      //cout << "Component aggregate: " << component.getName() << endl;
      //info.dumpSet( "NPKG" );

      totalize( info );

      // aggregate info from child components
      lim::asg::ListIterator<lim::asg::base::Component> containsIt = component.getContainsListIteratorBegin();
      for ( ; containsIt != component.getContainsListIteratorEnd(); ++containsIt )
      {
        const base::Component* subComponent = &( *containsIt );
        //cout << "  MERGES: " << subComponent->getName() << endl;
        Info& subComponentInfo = map.find( subComponent )->second;
        info.merge( aggregate( phase, subComponent, subComponentInfo ) );
      }
    }
    return info;
  }


  //
  // PACKAGE, CLASS, METHOD
  //

  Info& ScopeMap::aggregate( DispatchPhases phase, const base::Base* ptr, Info& info ) {
    if ( phase == phaseFinishVisit && !info.aggregated ) {

      //cout << "Scope aggregate for " << dynamic_cast<const logical::Scope*>( ptr )->getName() << endl;
      //cout << "NM: " << endl;
      //info.dumpSet( "NM" );

      info.aggregated = true;
      totalize( info );

      // aggregate info from child scopes
      set<const base::Base*> children( info.children );
      set<const base::Base*>::iterator i = children.begin(), end = children.end();
      for ( ; i != end; ++i )
      {
        const logical::Scope* subScope = dynamic_cast<const logical::Scope*>( *i );

        //cout << "  MERGES: " << subScope->getName() << endl;

        ContainerType::iterator scopeIt = map.find( subScope );
        if ( scopeIt != map.end() ) {
          Info& subScopeInfo = scopeIt->second;
          info.merge( aggregate( phase, subScope, subScopeInfo ) );
        }
      }

      //cout << "DONE for " << dynamic_cast<const logical::Scope*>( ptr )->getName() << endl;
      //cout << "TNM: " << endl;
      //info.dumpSet( "TNM" );
    }
    return info;
  }

  //
  // SHARED CONTAINERS
  //

  void SharedContainers::phaseOver( DispatchPhases phase ) {

    // NEWSHARED
    // If a new shared container is added that relies on its
    // phaseOver method then a call to it should be added here

    components.phaseOver( phase );
    scopes.phaseOver( phase );
  }

  Info& SharedContainers::currentPackageInfo() {
    return scopes.map[&packageStack.back().getLimNode<logical::Package>()];
  }

  Info& SharedContainers::currentClassInfo() {
    return scopes.map[&classStack.back().getLimNode<logical::Class>()];
  }

  Info& SharedContainers::currentMethodInfo() {
    return scopes.map[&methodStack.back().getLimNode<logical::Method>()];
  }

}}}
