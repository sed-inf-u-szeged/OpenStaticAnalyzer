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

#include "../../inc/metrics/Inheritance.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus { namespace lim { namespace metrics {

  InheritanceBase::InheritanceBase( const std::string& name, MetricDataTypes type, bool enabled, SharedContainers* shared ) :
    MetricHandler( name, type, enabled, shared ) {
      registerHandler(phaseVisit, NTYPE_LIM_STRUCTURE, limLangC, false, [this](NodeWrapper& node) {
          setInvalid(node);
      });
  }

  const string& InheritanceBase::translateLevel( Language language, const string& level ) const {
    const string& newLevel = MetricHandler::translateLevel( language, level );

    if ( language == limLangCpp || language == limLangCsharp ) {
      if ( newLevel == NTYPE_LIM_CLASS || newLevel == NTYPE_LIM_INTERFACE ) {
        return NTYPE_LIM_CLASS;
      }
    }

    return newLevel;
  }

  NOP::NOP( bool enabled, SharedContainers* shared ) : InheritanceBase( "NOP", mdtInt, enabled, shared ) {
    registerHandler( phaseVisit, NTYPE_LIM_CLASS, limLangOther, false, [this]( NodeWrapper& node ) {
      set<const logical::Class*> s;
      this->shared->inheritance->collectParents( node.getLimNode<logical::Class>(), s );
      addMetric( node, (int) s.size() );
    });
  }

  NOA::NOA( bool enabled, SharedContainers* shared ) : InheritanceBase( "NOA", mdtInt, enabled, shared ) {
    registerHandler( phaseVisit, NTYPE_LIM_CLASS, limLangOther, false, [this]( NodeWrapper& node ) {
      set<const logical::Class*> s;
      this->shared->inheritance->collectAncestors( node.getLimNode<logical::Class>(), s );
      addMetric( node, (int) s.size() );
    });
  }

  NOC::NOC( bool enabled, SharedContainers* shared ) : InheritanceBase( "NOC", mdtInt, enabled, shared ) {
    registerHandler( phaseVisit, NTYPE_LIM_CLASS, limLangOther, false, [this]( NodeWrapper& node ) {
      set<const logical::Class*> s;
      this->shared->inheritance->collectChildren( node.getLimNode<logical::Class>(), s );
      addMetric( node, (int) s.size() );
    });
  }

  NOD::NOD( bool enabled, SharedContainers* shared ) : InheritanceBase( "NOD", mdtInt, enabled, shared ) {
    registerHandler( phaseVisit, NTYPE_LIM_CLASS, limLangOther, false, [this]( NodeWrapper& node ) {
      set<const logical::Class*> s;
      this->shared->inheritance->collectDescendants( node.getLimNode<logical::Class>(), s );
      addMetric( node, (int) s.size() );
    });
  }

  DIT::DIT( bool enabled, SharedContainers* shared ) : InheritanceBase( "DIT", mdtInt, enabled, shared ) {
    registerHandler( phaseVisit, NTYPE_LIM_CLASS, limLangOther, false, [this]( NodeWrapper& node ) {
      set<const logical::Class*> s;
      // no performance loss from calling collectAncestors twice because it is already cached
      int dit = this->shared->inheritance->collectAncestors( node.getLimNode<logical::Class>(), s );
      addMetric( node, dit - 1 );
    });
  }

}}}
