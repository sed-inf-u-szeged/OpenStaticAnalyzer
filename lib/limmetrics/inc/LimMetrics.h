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

#ifndef _LIM_METRICS_H_
#define _LIM_METRICS_H_

#include "lim/inc/lim.h"
#include "graph/inc/graph.h"

#include "RulParser.h"

//#include <set>
//#include <string>

namespace columbus { namespace lim { namespace metrics {

  class LimMetricsVisitor : public asg::VisitorAbstractNodes {

    public:

      //
      // CONSTRUCTOR
      //

      LimMetricsVisitor( asg::Factory& factory, graph::Graph& graph, rul::RulHandler& rul, SharedContainers& shared);
      virtual ~LimMetricsVisitor();

      //
      // MAIN LOGIC
      //

      void run();
      void apRun();

      //
      // VISITORS
      //

      virtual void visit    (const asg::physical::File& node, bool callVirtualBase = true);
      virtual void visitEnd (const asg::physical::File& node, bool callVirtualBase = true);

      virtual void visit    (const asg::base::Component& node, bool callVirtualBase = true);
      virtual void visitEnd (const asg::base::Component& node, bool callVirtualBase = true);

      virtual void visit    (const asg::logical::Member& node, bool callVirtualBase = true);
      virtual void visitEnd (const asg::logical::Member& node, bool callVirtualBase = true);
    
    private:

      //
      // MERGED VISIT LOGIC
      //

      void begin( const asg::base::Base& node );
      void end( const asg::base::Base& node );

      //
      // DATA MEMBERS
      //

      asg::Factory& factory;                  ///> The lim factory
      graph::Graph& graph;                    ///> The graph converted from the above lim factory
      RulParser rul;                          ///> The corresponding (parsed) rul file
      const asg::ReverseEdges& reverseEdges;  ///> Reverse edges

      /**
      * Because of the more complex traversal required (meaning separate runs from the factory root, the
      * filesystem root and the component root) and the multiple passes (init for every node involved 
      * before a "normal" visit-visitEnd cycle followed by one or more finalizations) this visitor stores
      * its own traversal algorithm
      */
      asg::AlgorithmPreorder ap;

      DispatchPhases phase;                   ///> Which phase should be used when dispatching
      bool useVisitEnd;                       ///> Whether or not to use the visitEnd methods in the current pass
  };

}}}

#endif
