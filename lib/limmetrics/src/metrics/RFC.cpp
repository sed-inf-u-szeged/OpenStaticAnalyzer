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

#include "../../inc/metrics/RFC.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus { namespace lim { namespace metrics {

  RFC::RFC( bool enabled, SharedContainers* shared ) : MetricHandler( "RFC", mdtInt, enabled, shared ) {

    dependencies.insert( "NLM" );
    dependencies.insert( "NOI" );

    registerHandler( phaseVisitEnd, NTYPE_LIM_CLASS, limLangOther, false, [this] ( NodeWrapper& node ) {

      if ( ! node.isDefinition() ) {
        return;
      }

      // RFC = NLM union Class level NOI
      int nlm = this->shared->currentClassInfo().ints["NLM"];

      set<NodeId>& noi = this->shared->currentClassInfo().sets["NOI"];
      int rfc = nlm + (int) noi.size();

      addMetric( node, rfc );

      // propagate to package level
      this->shared->currentPackageInfo().ints[this->name] += rfc;

      cleanup( node, "NOI" );
    });

    // C vs. C++ compat
    registerHandler( phaseVisit, NTYPE_LIM_STRUCTURE, limLangC, false, [this] ( NodeWrapper& node ) {
      setInvalid( node );
    });
    registerHandler( phaseVisit, NTYPE_LIM_UNION, limLangC, false, [this] ( NodeWrapper& node ) {
      setInvalid( node );
    });

  }

  const string& RFC::translateLevel( Language language, const string& level ) const {
    const string& newLevel = MetricHandler::translateLevel( language, level );

    if ( language == limLangCpp ) {
      if (
        newLevel == NTYPE_LIM_CLASS ||
        newLevel == NTYPE_LIM_UNION
      ) {
        return NTYPE_LIM_CLASS;
      }
    }

    return newLevel;
  }

  TRFC::TRFC(bool enabled, SharedContainers* shared) : MetricHandler("TRFC", mdtInt, enabled, shared) {
    dependencies.insert("RFC");
    propagateScopeInt(phaseFinalize, NTYPE_LIM_PACKAGE, limLangOther);
  }

}}}
