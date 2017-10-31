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

#include "../../inc/metrics/NPKG.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus { namespace lim { namespace metrics {

  NPKGBase::NPKGBase( const std::string& name, MetricDataTypes type, bool enabled, SharedContainers* shared ) :
    MetricHandler( name, type, enabled, shared ) {}

  const std::string& NPKGBase::translateLevel( asg::Language language, const std::string& level ) const {
    const string& newLevel = MetricHandler::translateLevel( language, level );

    if ( language == limLangPython ) {
      if ( level == NTYPE_LIM_MODULE ) {
        return NTYPE_LIM_MODULE;
      }
    }

    return newLevel;
  }

  NPKG::NPKG( bool enabled, SharedContainers* shared ) : NPKGBase( "NPKG", mdtInt, enabled, shared ) {

    registerHandler( phaseVisit, NTYPE_LIM_PACKAGE, limLangOther, false, [this] ( NodeWrapper& node ) {

      const logical::Package& package = node.getLimNode<logical::Package>();

      // deal with "real" Packages only
      if ( package.getPackageKind() != pkPackage ) {
        return;
      }

      // find first Package parent
      const asg::ReverseEdges& rev = this->shared->factory->getReverseEdges();
      
      const base::Base* step = &package;
      do {
        ListIterator<base::Base>  stepIt = rev.constIteratorBegin( step->getId(), edkScope_HasMember ),
                                  stepEnd = rev.constIteratorEnd( step->getId(), edkScope_HasMember );
        step = nullptr;
        if ( stepIt != stepEnd ) {
          step = &(*stepIt);
        }
      } while ( step  && ! Common::getIsPackage(*step) );

      // if there is one
      if ( step ) {

        const logical::Package& parentPackage = dynamic_cast<const logical::Package&>( *step );

        // add current package to its parent package
        Info& parentInfo = this->shared->scopes.map[&parentPackage];
        parentInfo.sets[this->name].insert( package.getId() );
      }

      // if it's not the root package
      if ( &package != this->shared->factory->getRoot() ) {
        // add current package to the components it belongs to
        ListIterator<base::Component> i = package.getBelongsToListIteratorBegin(), end = package.getBelongsToListIteratorEnd();
        for ( ; i != end; ++i ) {
          const base::Component& c = dynamic_cast<const base::Component&>( *i );
          Info& cInfo = this->shared->components.map[&c];
          cInfo.sets[this->name].insert( package.getId() );
        }
      }
    });

    propagateScopeSet( phaseFinishVisit, NTYPE_LIM_PACKAGE, limLangOther );
  }

  TNPKG::TNPKG( bool enabled, SharedContainers* shared ) : NPKGBase( "TNPKG", mdtInt, enabled, shared ) {

    dependencies.insert( "NPKG" );

    propagateScopeSet( phaseFinalize, NTYPE_LIM_PACKAGE, limLangOther );
    propagateComponentSet();

  }

}}}
