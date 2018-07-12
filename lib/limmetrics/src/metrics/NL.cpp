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

#include "../../inc/metrics/NL.h"

#include <algorithm>

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus { namespace lim { namespace metrics {

  NLBase::NLBase( const string& name, MetricDataTypes type, bool enabled ) : MetricHandler( name, type, enabled ) {

    // Method level
    this->registerHandler( phaseVisit, NTYPE_LIM_METHOD, limLangOther, false, [this]( NodeWrapper& node ) {
      addMetric( node, getValue( node.getLimNode<logical::Method>() ) );
    });

    // Class level
    this->registerHandler( phaseVisit, NTYPE_LIM_CLASS, asg::limLangOther, false, [this]( NodeWrapper& node ) {
      
      int value = 0;
      const logical::Class& clazz = node.getLimNode<logical::Class>(); 

      ListIterator<logical::Member> i = clazz.getMemberListIteratorBegin(), end = clazz.getMemberListIteratorEnd();
      for ( ; i != end; ++i ) {
        if ( Common::getIsMethod( *i ) ) {
          value = max( value, getValue( dynamic_cast<const logical::Method&>( *i ) ) );
        }
      }

      addMetric( node, value );
    });
  }

  const string& NLBase::translateLevel( Language language, const string& level ) const {
    const string& newLevel = MetricHandler::translateLevel( language, level );

    switch ( language ) {
      case limLangCpp:
        if (
          newLevel == NTYPE_LIM_CLASS ||
          newLevel == NTYPE_LIM_UNION
        ) {
          return NTYPE_LIM_CLASS;
        }
        break;
      default:
        break;
    }

    return newLevel;
  }


  NL::NL( bool enabled ) : NLBase( "NL", mdtInt, enabled ) {}

  int NL::getValue( const asg::logical::Method& method ) {
    return method.getNestingLevel();
  }

  NLE::NLE( bool enabled ) : NLBase( "NLE", mdtInt, enabled ) {}

  int NLE::getValue( const asg::logical::Method& method ) {
    return method.getNestingLevelElseIf();
  }

}}}
