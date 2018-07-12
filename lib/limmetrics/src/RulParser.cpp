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

#include "../inc/RulParser.h"
#include "../inc/Messages.h"

// separate metrics headers
#include "../inc/metrics/CBO.h"
#include "../inc/metrics/Documentation.h"
#include "../inc/metrics/Inheritance.h"
#include "../inc/metrics/LCOM5.h"
#include "../inc/metrics/LOC.h"
#include "../inc/metrics/McCC.h"
#include "../inc/metrics/NA.h"
#include "../inc/metrics/NCL.h"
#include "../inc/metrics/NII.h"
#include "../inc/metrics/NL.h"
#include "../inc/metrics/NM.h"
#include "../inc/metrics/NOI.h"
#include "../inc/metrics/NOS.h"
#include "../inc/metrics/NPKG.h"
#include "../inc/metrics/NUMPAR.h"
#include "../inc/metrics/RFC.h"
#include "../inc/metrics/TNFI.h"
#include "../inc/metrics/WMC.h"
#include "../inc/metrics/Halstead.h"

#include "../inc/metrics/Aggregates.h"

// macro for easier metric handler matching
#define MATCH( name ) if ( id == #name ) return new name( enabled );
#define MATCH_SHARED( name ) if ( id == #name ) return new name( enabled, &shared );

using namespace std;
using namespace columbus::rul;
using namespace columbus::lim::asg;

namespace columbus { namespace lim { namespace metrics {

  RulParser::RulParser( RulHandler& rul, SharedContainers& shared) : rul( rul ), shared( shared ) {
    parse();
    sort();
  }

  RulParser::~RulParser() {
    map<string, MetricHandler*>::iterator i = handlerMap.begin(), end = handlerMap.end();
    for ( ; i != end; ++i ) {
      delete i->second;
    }
    handlerMap.clear();
  }

  void RulParser::parse() {

    deque<string> queue;
   set<string> groupIds;
    rul.getGroupIdList( groupIds );

    // loading all metrics
   set<string>::iterator groupIt = groupIds.begin(), groupEnd = groupIds.end();
    for ( ; groupIt != groupEnd; ++groupIt )
    {
      string groupId = *groupIt;

     set<string> ids;
      rul.getGroupMembers( groupId, ids );

     set<string>::iterator metricsIt = ids.begin(), metricsEnd = ids.end();
      for ( ; metricsIt != metricsEnd; ++metricsIt )
      {
        string id = *metricsIt;
        bool enabled = rul.getIsEnabled( id );
        handlerMap[id] = matchHandler( id, enabled );
        handlerMap[id]->setCalculatedFor( rul.getCalculatedForSet(id) );
        if ( enabled ) {
          queue.push_back( id );
        }
      }
    }

    // propagating dependency information
    while ( ! queue.empty() ) {

      MetricHandler* handler = handlerMap[queue.front()];
      queue.pop_front();

      set<string>::const_iterator dIt = handler->getDependencies().begin(), dEnd = handler->getDependencies().end();
      for ( ; dIt != dEnd; ++dIt ) {

        MetricHandler* dependency = handlerMap[*dIt];

        if ( ! dependency->getIsOn() ) {
          dependency->setIsDependency( true );
          queue.push_back( *dIt );
        }
      }
    }
  }

  MetricHandler* RulParser::matchHandler( const string& id, bool enabled ) {

      // CBO.h
      MATCH_SHARED( CBOI )

      // Documentation.h
      MATCH_SHARED( DLOC )
      MATCH_SHARED( PDA )
      MATCH_SHARED( TPDA )
      MATCH_SHARED( PUA )
      MATCH_SHARED( TPUA )
      MATCH_SHARED( AD )
      MATCH_SHARED( TAD )
      MATCH_SHARED( CD )
      MATCH_SHARED( TCD )
    
      // Inheritance.h
      MATCH_SHARED( NOP )
      MATCH_SHARED( NOA )
      MATCH_SHARED( NOD )        

      // NA.h
      MATCH_SHARED( NA );
      MATCH_SHARED( NLA );
      MATCH_SHARED( NPA );
      MATCH_SHARED( NLPA );
      MATCH_SHARED( TNA );
      MATCH_SHARED( TNLA );
      MATCH_SHARED( TNPA );
      MATCH_SHARED( TNLPA );
    
      // NCL.h
      MATCH_SHARED( NIN )
      MATCH_SHARED( NST )
      MATCH_SHARED( NUN )
      MATCH_SHARED( TNIN )
      MATCH_SHARED( TNST )
      MATCH_SHARED( TNUN )
      MATCH_SHARED( TNPCL )
      MATCH_SHARED( TNPIN )
      MATCH_SHARED( TNPEN )
      MATCH_SHARED( TNPST )
      MATCH_SHARED( TNPUN )

      // NII.h
      MATCH_SHARED( NII )

      // NL.h
      MATCH( NL )
      MATCH( NLE )

      // NM.h
      MATCH_SHARED( NM )
      MATCH_SHARED( NLM )
      MATCH_SHARED( NG )
      MATCH_SHARED( NLG )
      MATCH_SHARED( NS )
      MATCH_SHARED( NLS )
      MATCH_SHARED( NPM )
      MATCH_SHARED( NLPM )
      MATCH_SHARED( TNM )
      MATCH_SHARED( TNLM )
      MATCH_SHARED( TNLG )
      MATCH_SHARED( TNLS )
      MATCH_SHARED( TNPM )
      MATCH_SHARED( TNLPM )


      // NOS.h
      MATCH_SHARED( NOS )
      MATCH_SHARED( TNOS )

      // NPKG.h
      MATCH_SHARED( NPKG )
      MATCH_SHARED( TNPKG )

      // NUMPAR.h
      MATCH( NUMPAR )


      // TNFI.h
      MATCH_SHARED( TNFI )
      MATCH_SHARED( TNDI )

      // Aggregates.h
      MATCH_SHARED( MI )
      MATCH_SHARED( MISEI )
      MATCH_SHARED( MIMS )
      MATCH_SHARED( MISM )


    // WMC.h
    MATCH_SHARED( WMC )
    MATCH_SHARED( TWMC )
    // LCOM.h
    MATCH_SHARED( LCOM5 )
    MATCH_SHARED( TLCOM5 )
    // McCC.h
    MATCH_SHARED( McCC )
    // Halstead.h
    MATCH_SHARED( HPV )
    MATCH_SHARED( HPL )
    MATCH_SHARED( HCPL )
    MATCH_SHARED( HVOL )
    MATCH_SHARED( HDIF )
    MATCH_SHARED( HEFF )
    MATCH_SHARED( HTRP )
    MATCH_SHARED( HNDB )
    // CBO.h
    MATCH_SHARED( CBO )
    MATCH_SHARED( TCBO )
    // NOI.h
    MATCH_SHARED( NOI )
    // RFC.h
    MATCH_SHARED( RFC )
    MATCH_SHARED( TRFC )
    // Documentation.h
    MATCH_SHARED( CLOC )
    MATCH_SHARED( TCLOC )
    // Inheritance.h
    MATCH_SHARED( DIT )
    MATCH_SHARED( NOC )
    // LOC.h
    MATCH( LOC )
    MATCH( LLOC )
    MATCH( TLOC )
    MATCH( TLLOC )
    // NCL.h
    MATCH_SHARED( NCL )
    MATCH_SHARED( NEN )
    MATCH_SHARED( TNCL )
    MATCH_SHARED( TNEN )
    // NM.h
    MATCH_SHARED( TNG )
    MATCH_SHARED( TNS )

    // Aggregates
    MATCH_SHARED( AvgRFC )
    MATCH_SHARED( AvgWMC )
    MATCH_SHARED( AvgCBO )
    MATCH_SHARED( AvgLCOM5 )

    // default case
    return new MetricHandler();

  }

  void RulParser::sort() {

    // keep going until there is a change
    size_t orderSize;
    do {

      orderSize = handlerOrder.size();

      // one concrete pass over the handlers
      map<string, MetricHandler*>::iterator handlerIt = handlerMap.begin(), handlerEnd = handlerMap.end();
      for ( ; handlerIt != handlerEnd; ++handlerIt ) {

        // a handler can be added to the order list if
        // (1) it is "on"
        // (2) it hasn't been added yet
        // (3) all of its dependencies are already added
        bool good = true;

        if ( ! handlerIt->second->getIsOn() ) { // 1
          good = false;
        } else if ( find( handlerOrder.begin(), handlerOrder.end(), handlerIt->first ) != handlerOrder.end() ) { // 2
          good = false;
        } else {
          const set<string>& dependencies = handlerIt->second->getDependencies();
          set<string>::const_iterator dIt = dependencies.begin(), dEnd = dependencies.end();
          for ( ; dIt != dEnd; ++dIt ) {
            if ( find( handlerOrder.begin(), handlerOrder.end(), *dIt ) == handlerOrder.end() ) { // 3
              // has at least one dependency that is not in the new list yet, skip
              good = false;
              break;
            }
          }
        }

        if ( good ) {
          handlerOrder.push_back( handlerIt->first );
        }
      }

    } while ( orderSize != handlerOrder.size() );
  }

  void RulParser::dispatch( DispatchPhases phase, NodeWrapper& node ) {

    if ( phase == phaseVisit ) {
      stack( node, true ); // push
    }

    vector<string>::iterator orderIt = handlerOrder.begin(), orderEnd = handlerOrder.end();
    for ( ; orderIt != orderEnd; ++orderIt ) {
      handlerMap[*orderIt]->dispatch( phase, node );
    }

    if ( phase == phaseVisitEnd ) {
      stack( node, false ); // pop
    }

  }

  void RulParser::phaseOver( DispatchPhases phase ) {
    shared.phaseOver( phase );
  }

  /*
  * Stack maintenance + child relations among scopes for correct aggregation
  * Besides getting pushed to the scope stack, the following happens to each scope type 
  *
  * Package --> Child of current Package (if any)
  *             Push to Package stack
  *
  * Class -->   Child of current Class (if any)
  *             Child of top level Scope if it is a Method
  *             Push to the Class stack
  *
  * Method -->  Child of top level scope if it is a Method
  *             Push to the Method stack
  */
  void RulParser::stack( const NodeWrapper& node, bool push ) {

    const base::Base& base = node.getLimNode<base::Base>();
    
    std::deque<NodeWrapper>* stackPtr = nullptr;
    std::vector<const base::Base*> parents;

    if ( Common::getIsPackage( base ) ) {
      stackPtr = & shared.packageStack;
      if ( ! shared.packageStack.empty() ) {
        parents.push_back( & shared.packageStack.back().getLimNode<base::Base>() );
      }

    } else if ( Common::getIsClass( base ) ) {
      stackPtr = & shared.classStack;
      if ( ! shared.classStack.empty() ) {
        parents.push_back( & shared.classStack.back().getLimNode<base::Base>() );
      }
      if ( ! shared.scopeStack.empty() ) {
        const base::Base* m = & shared.scopeStack.back().getLimNode<base::Base>();
        if ( Common::getIsMethod( *m ) ) {
          parents.push_back( m );
        }
      }

    } else if ( Common::getIsMethod( base ) ) {
      stackPtr = & shared.methodStack;
      if ( ! shared.scopeStack.empty() ) {
        const base::Base* b = & shared.scopeStack.back().getLimNode<base::Base>();
        if ( Common::getIsMethod( *b ) ) {
          parents.push_back( b );
        }
      }
    }

    if ( stackPtr ) {

      if ( push ) {

        // child relations
        for ( vector<const base::Base*>::iterator p = parents.begin(); p != parents.end(); ++p ) {
          shared.scopes.map[*p].children.insert( &base );
        }

        stackPtr->push_back( node );
        shared.scopeStack.push_back( node );
      } else {
        stackPtr->pop_back();
        shared.scopeStack.pop_back();
      }

    }
  }

}}}
