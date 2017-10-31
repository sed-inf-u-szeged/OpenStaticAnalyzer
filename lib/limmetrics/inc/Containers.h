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

#ifndef _LIMMETRICS_CONTAINERS_
#define _LIMMETRICS_CONTAINERS_

#include <lim/inc/lim.h>

#include "Defines.h"
#include "NodeWrapper.h"

namespace columbus { namespace lim { namespace metrics {

  class InheritanceHelper {

    public:

      InheritanceHelper( const asg::ReverseEdges& reverseEdges );

      /**
      * Wrapper methods around the functions of the same name in lim::Common, see documentation there
      */
      void collectParents( const asg::logical::Class& node, std::set<const asg::logical::Class*>& parents );
      int collectAncestors( const asg::logical::Class& node, std::set<const asg::logical::Class*>& ancestors );
      void collectChildren( const asg::logical::Class& node, std::set<const asg::logical::Class*>& children );
      int collectDescendants( const asg::logical::Class& node, std::set<const asg::logical::Class*>& descendants );

    private:
      
      const asg::ReverseEdges& reverseEdges;
      asg::Common::InheritanceCache upCache;
      asg::Common::InheritanceCache downCache;

  };


  //
  // SHARED CONTAINERS
  //

  struct Info {

    typedef std::map<const std::string, int> IntMap;
    typedef std::map<const std::string, std::set<NodeId>> SetMap;
    typedef std::map<const std::string, std::map<NodeId, int>> MapMap;

    /** Constructors */
    Info();

    /** Adding two Infos */
    Info& merge( const Info& other );

    /** Counts a given map */
    int mapCount( const std::string& name );

    /** The nodes that appeared in the corresponding stack above this node (for easier aggregation) */
    std::set<const asg::base::Base*> children;

    /** Flag to avoid duplicate aggregation */
    bool aggregated;

    /** Containers for the collected values */
    IntMap ints;
    SetMap sets;
    MapMap maps;

    /** Debug methods */
    void dumpInt( const std::string& key );
    void dumpSet( const std::string& key );
    void dumpMap( const std::string& key );
    
  };


  class SharedContainer {
    public:
      typedef std::map<const asg::base::Base*, Info> ContainerType;
      
      void phaseOver( DispatchPhases phase );
      virtual Info& aggregate( DispatchPhases phase, const asg::base::Base* ptr, Info& info );
      void totalize( Info& info );

      ContainerType map;
  };


  class ComponentMap : public SharedContainer {
    public:
      Info& aggregate( DispatchPhases phase, const asg::base::Base* ptr, Info& info );
  };


  class ScopeMap : public SharedContainer {
    public:
      Info& aggregate( DispatchPhases phase, const asg::base::Base* ptr, Info& info );
  };

  typedef std::map<std::string, std::map<std::string, std::vector<std::string>>> LCOMMapType;

  class SharedContainers {

    public:

      /**
      * Phase over signal for the individual shared containers
      */
      void phaseOver( DispatchPhases phase );

      /**
      * Stacks for the visit process
      */
      std::deque<NodeWrapper> packageStack;
      std::deque<NodeWrapper> classStack;
      std::deque<NodeWrapper> methodStack;

      /**
      * Another stack for all the scopes for correct parent-child relations 
      */
      std::deque<NodeWrapper> scopeStack;

      /**
      * Constant storage of data
      */
      ComponentMap components;
      ScopeMap scopes;
      SharedContainer::ContainerType files;

      /**
      * Convenience accessors
      */
      Info& currentPackageInfo();
      Info& currentClassInfo();
      Info& currentMethodInfo();

      /**
      * Other, "outside" information
      */
      asg::OverrideRelations* overrides;
      asg::Factory* factory;
      InheritanceHelper* inheritance;
      LCOMMapType* LCOMMap;

  };

}}}

#endif
