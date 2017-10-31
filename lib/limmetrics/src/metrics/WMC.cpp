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

#include "../../inc/metrics/WMC.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus { namespace lim { namespace metrics {

  WMC::WMC( bool enabled, SharedContainers* shared ) : MetricHandler( "WMC", mdtInt, enabled, shared ) {

    this->registerHandler( phaseVisit, NTYPE_LIM_CLASS, limLangOther, false, [this]( NodeWrapper& node ) {

      int wmc = 0;
      const logical::Class& clazz = node.getLimNode<logical::Class>();

      ListIterator<logical::Member> i = clazz.getMemberListIteratorBegin(), end = clazz.getMemberListIteratorEnd();
      for ( ; i != end; ++i ) {
        if ( Common::getIsMethod( *i ) ) {
          wmc += dynamic_cast<const logical::Method&>( *i ).getNumberOfBranches();
        }
      }

      addMetric( node, wmc );

      // propagate to package level
      this->shared->currentPackageInfo().ints[this->name] += wmc;
    });

  }

  const string& WMC::translateLevel( Language language, const string& level ) const {
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

  TWMC::TWMC(bool enabled, SharedContainers* shared) : MetricHandler("TWMC", mdtInt, enabled, shared) {
    dependencies.insert("WMC");
    propagateScopeInt(phaseFinalize, NTYPE_LIM_PACKAGE, limLangOther);
  }

}}}
