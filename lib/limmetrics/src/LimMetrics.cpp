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

#include "../inc/LimMetrics.h"
#include "../inc/Messages.h"

#include <common/inc/WriteMessage.h>
#include <common/inc/StringSup.h>
#include <lim2graph/inc/VisitorGraphConverter.h>
#include <graphsupport/inc/GraphConstants.h>

#include "../inc/metrics/NM.h"
#include "../inc/metrics/LOC.h"


#define VISIT_DEBUG(part) WriteMsg::write( CMSG_LIMMETRICS_VISIT_DEBUG, part, node.getId(), lim::asg::Common::toString(node.getNodeKind()).c_str(), phase );


using namespace std;
using namespace common;
using namespace columbus::lim::asg;

namespace columbus { namespace lim { namespace metrics {

  //
  // CONSTRUCTOR
  //

  LimMetricsVisitor::LimMetricsVisitor( Factory& factory, graph::Graph& graph, rul::RulHandler& rul, SharedContainers& shared) :
    factory( factory ),
    graph( graph ),
    rul( RulParser( rul, shared ) ),
    reverseEdges( factory.getReverseEdges() ),
    phase( phaseVisit ),
    useVisitEnd( true )
  {
    ap.setVisitSpecialNodes(true, true);
    ap.setCrossEdgeToTraversal(lim::asg::edkScope_HasMember);
    ap.setSafeMode();
  }

  LimMetricsVisitor::~LimMetricsVisitor() {}

  //
  // MAIN LOGIC
  //

  void LimMetricsVisitor::run() {

    // main run
    WriteMsg::write( CMSG_LIMMETRICS_PHASE, "Visit" );
    apRun();

    WriteMsg::write( CMSG_LIMMETRICS_PHASE_OVER, "Visit" );
    rul.phaseOver( phaseVisit );
    WriteMsg::write( CMSG_LIMMETRICS_PHASE_OVER, "VisitEnd" );
    rul.phaseOver( phaseVisitEnd );

    // finalization before totaling
    phase = phaseFinishVisit;
    useVisitEnd = false;
    WriteMsg::write( CMSG_LIMMETRICS_PHASE, "FinishVisit" );
    apRun();
    WriteMsg::write( CMSG_LIMMETRICS_PHASE_OVER, "FinishVisit" );
    rul.phaseOver( phaseFinishVisit );

    // finalization AFTER totaling
    phase = phaseFinalize;
    WriteMsg::write( CMSG_LIMMETRICS_PHASE, "Finalize" );
    apRun();
    WriteMsg::write( CMSG_LIMMETRICS_PHASE_OVER, "Finalize" );
    rul.phaseOver( phaseFinalize );

  }

  void LimMetricsVisitor::apRun() {
    // "normal" tree
    ap.run( factory, *this, factory.getRoot()->getId() );

    // file system
    ap.run( factory, *this, factory.getFileSystemRoot() );

    // components
    factory.getComponentRootRef().accept( *this );
    factory.getComponentRootRef().acceptEnd( *this );
  }

  //
  // VISITORS
  //

  void LimMetricsVisitor::visit( const lim::asg::physical::File& node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit( node );
    begin( node );
  }

  void LimMetricsVisitor::visitEnd( const lim::asg::physical::File& node, bool callVirtualBase ) {
    VisitorAbstractNodes::visitEnd( node );
    end( node );
  }

  void LimMetricsVisitor::visit(const base::Component& node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit( node );
    begin( node );
  }

  void LimMetricsVisitor::visitEnd(const base::Component& node, bool callVirtualBase ) {
    VisitorAbstractNodes::visitEnd( node );
    end( node );
  }

  void LimMetricsVisitor::visit(const logical::Member& node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit( node );
    begin( node );
  }

  void LimMetricsVisitor::visitEnd(const logical::Member& node, bool callVirtualBase ) {
    VisitorAbstractNodes::visitEnd( node );
    end( node );
  }

  //
  // MERGED VISIT LOGIC
  //

  void LimMetricsVisitor::begin( const base::Base& node ) {
    VISIT_DEBUG( "begin" );
    NodeWrapper nw( node, graph );
    rul.dispatch( phase, nw );
  }

  void LimMetricsVisitor::end( const base::Base& node ) {
    if ( useVisitEnd ) {
      VISIT_DEBUG( "end" );
      NodeWrapper nw( node, graph );
      rul.dispatch( phaseVisitEnd, nw );
    }
  }
   
}}}

