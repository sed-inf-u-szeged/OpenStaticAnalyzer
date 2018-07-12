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

#include "../../inc/metrics/LOC.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus { namespace lim { namespace metrics {

  //
  // LOC BASE
  //

  LOCBase::LOCBase( const string& name, bool enabled, ScopePtr scopePtr, FilePtr filePtr, ComponentPtr componentPtr ) :
    MetricHandler( name, mdtInt, enabled, NULL ),
    scopePtr( scopePtr ),
    filePtr( filePtr ),
    componentPtr( componentPtr )
  {

    registerHandler( phaseVisit, NTYPE_LIM_CLASS, limLangOther, false, [this] ( NodeWrapper& node ) {
      const logical::Scope& scope = node.getLimNode<logical::Scope>();
      addMetric( node, (int) (scope.*(this->scopePtr))() );
    });

    registerHandler( phaseVisit, NTYPE_LIM_FILE, limLangOther, false, [this] ( NodeWrapper& node ) {
      if ( this->filePtr != NULL ) {
        const physical::File& file = node.getLimNode<physical::File>();
        addMetric( node, (int) (file.*(this->filePtr))() );
      }
    });

    registerHandler( phaseVisit, NTYPE_LIM_COMPONENT, limLangOther, false, [this] ( NodeWrapper& node ) {
      if ( this->componentPtr != NULL ) {
        const base::Component& component = node.getLimNode<base::Component>();
        addMetric( node, (int) (component.*(this->componentPtr))() );
      }
    });
  }

  const string& LOCBase::translateLevel( asg::Language language, const std::string& level ) const {
    
    const string& newLevel = MetricHandler::translateLevel( language, level );

    // Scopes (method/class/package) are handled together

    if (
      // method-like
      newLevel == NTYPE_LIM_METHOD ||
      newLevel == NTYPE_LIM_FUNCTION ||
      // class-like
      newLevel == NTYPE_LIM_CLASS ||
      newLevel == NTYPE_LIM_STRUCTURE ||
      newLevel == NTYPE_LIM_UNION ||
      newLevel == NTYPE_LIM_ENUM ||
      newLevel == NTYPE_LIM_INTERFACE ||
      newLevel == NTYPE_LIM_ANNOTATION ||
      // package-like
      newLevel == NTYPE_LIM_PACKAGE ||
      newLevel == NTYPE_LIM_NAMESPACE ||
      newLevel == NTYPE_LIM_MODULE
    ) {
      return NTYPE_LIM_CLASS;
    }

    return newLevel;
  }

  //
  // SPECIALIZATIONS
  //

  LOC::LOC( bool enabled ) : LOCBase( "LOC", enabled, &logical::Scope::getLOC, &physical::File::getLOC, NULL ) {}
  LLOC::LLOC( bool enabled ) : LOCBase( "LLOC", enabled, &logical::Scope::getLLOC, &physical::File::getLLOC, NULL ) {}
  TLOC::TLOC( bool enabled ) : LOCBase( "TLOC", enabled, &logical::Scope::getTLOC, NULL, &base::Component::getTLOC ) {}
  TLLOC::TLLOC( bool enabled ) : LOCBase( "TLLOC", enabled, &logical::Scope::getTLLOC, NULL, &base::Component::getTLLOC ) {}

}}}
