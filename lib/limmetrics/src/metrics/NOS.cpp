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

#include "../../inc/metrics/NOS.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus { namespace lim { namespace metrics {

  NOS::NOS( bool enabled, SharedContainers* shared ) : MetricHandler( "NOS", mdtInt, enabled, shared ) {

    this->registerHandler( phaseVisit, NTYPE_LIM_METHOD, limLangOther, false, [this]( NodeWrapper& node ) {
      
      // get NOS
      const logical::Method& method = node.getLimNode<logical::Method>();
      int nos = (int) method.getNumberOfStatements();

      // add to method info
      this->shared->currentMethodInfo().ints[this->name] = nos;
      
      // add to class info (if not function)
      if ( ! this->shared->classStack.empty() ) {
        this->shared->currentClassInfo().ints[this->name] += nos;
      }

      // add to package info
      this->shared->currentPackageInfo().ints[this->name] += nos;

      // add to component info
      auto i = method.getBelongsToListIteratorBegin();
      for ( ; i != method.getBelongsToListIteratorEnd(); ++i ) {
        const base::Component& c = dynamic_cast<const base::Component&>( *i );
        Info& cInfo = this->shared->components.map[&c];
        cInfo.ints[this->name] += nos;
      }

      // add to file info
      ListIteratorAssocSourcePosition<physical::File> files = method.getIsContainedInListIteratorAssocBegin(),
                                                      filesEnd = method.getIsContainedInListIteratorAssocEnd();
      for ( ; files != filesEnd; ++files ) {
        const physical::File* file = &(*files);
        this->shared->files[file].ints[name] += (int) method.getNumberOfStatements();
      }

      // add metric to method node
      addMetric( node, nos );
    });

    propagateScopeInt( phaseVisitEnd, NTYPE_LIM_CLASS, limLangOther );

    this->registerHandler( phaseFinishVisit, NTYPE_LIM_FILE, limLangOther, false, [this]( NodeWrapper& node ) {

      const physical::File* file = &node.getLimNode<physical::File>();

      //
      // File-level NOS is temporarily C/C++/Python only !!
      //
      Language l = file->getFactory().getLanguage();
      if ( l != limLangC && l != limLangCpp && l != limLangPython ) return;

      // Add the previously collected File level NOS to the node
      Info& fileInfo = this->shared->files[file];
      addMetric( node, fileInfo.ints[this->name] );
    });

  }

  const string& NOS::translateLevel( Language language, const string& level ) const {
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

  TNOS::TNOS( bool enabled, SharedContainers* shared ) : MetricHandler( "TNOS", mdtInt, enabled, shared ) {

    dependencies.insert( "NOS" );

    propagateScopeInt( phaseFinalize, NTYPE_LIM_METHOD, limLangOther );
    propagateScopeInt( phaseFinalize, NTYPE_LIM_CLASS, limLangOther );
    propagateScopeInt( phaseFinalize, NTYPE_LIM_PACKAGE, limLangOther );
    propagateComponentInt();
  }

  const string& TNOS::translateLevel( Language language, const string& level ) const {
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

}}}
