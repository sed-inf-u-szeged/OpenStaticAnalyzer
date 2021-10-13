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

#include "../../inc/metrics/NII.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus { namespace lim { namespace metrics {

  NII::NII( bool enabled, SharedContainers* shared ) : MetricHandler( "NII", mdtInt, enabled, shared ) {

    // Method level NII
    this->registerHandler( phaseVisit, NTYPE_LIM_METHOD, limLangOther, false, [this]( NodeWrapper& node ) {

      const logical::Method& method = node.getLimNode<logical::Method>();
      set<NodeId> s;

      fillIncomingMethodInvocations( method, s, false );

      // remove self reference
      s.erase( method.getId() );

      addMetric( node, (int) s.size() );

      // add to class level NII
      if ( ! node.isFunction() ) {
        this->shared->currentClassInfo().sets[this->name].insert( s.begin(), s.end() );
      }
    });

    // Class level NII
    this->registerHandler( phaseVisitEnd, NTYPE_LIM_CLASS, limLangOther, false, [this]( NodeWrapper& node ) {

      const logical::Class& clazz = node.getLimNode<logical::Class>();
      set<NodeId>& niiSet = this->shared->currentClassInfo().sets[this->name];

      // self references removed
      for ( ListIterator<logical::Member> hasMemberIt = clazz.getMemberListIteratorBegin(); hasMemberIt != clazz.getMemberListIteratorEnd(); ++hasMemberIt ) {
        niiSet.erase( hasMemberIt->getId() );
      }

      addMetric( node, (int) this->shared->currentClassInfo().sets[this->name].size() );

      cleanup( node );
    });

    // C vs. C++ compat
    registerHandler( phaseVisit, NTYPE_LIM_STRUCTURE, limLangC, false, [this] ( NodeWrapper& node ) {
      setInvalid( node );
    });
    registerHandler( phaseVisit, NTYPE_LIM_UNION, limLangC, false, [this] ( NodeWrapper& node ) {
      setInvalid( node );
    });

  }

  void NII::fillIncomingMethodInvocations( const logical::Method& method, std::set<NodeId>& incomingInvocations, bool withInstances ) {
    ListIterator<base::Base> it = this->shared->factory->getReverseEdges().constIteratorBegin( method.getId(), edkMethodCall_Method );
    for ( ; it != this->shared->factory->getReverseEdges().constIteratorEnd(method.getId(), edkMethodCall_Method); ++it ) {
      if ( Common::getIsMethodCall( *it ) ) {
        const logical::MethodCall& methodCall = (const logical::MethodCall&)(*it);
        ListIterator<base::Base> itMcall = this->shared->factory->getReverseEdges().constIteratorBegin( methodCall.getId(), edkMethod_Calls );
        for(; itMcall != this->shared->factory->getReverseEdges().constIteratorEnd(methodCall.getId(), edkMethod_Calls); ++itMcall) {
          if ( Common::getIsMethod( *itMcall ) ) {
            const logical::Method& callerMethod = (const logical::Method&)(*itMcall);
            if ( ! withInstances ) {
              if ( Common::getIsMethodGenericInstance( callerMethod ) ) {
                const logical::MethodGenericInstance& methodGenericInst = (const logical::MethodGenericInstance&)(callerMethod);
                const logical::MethodGeneric* methodGeneric = Common::getMethodPrototype( this->shared->factory->getReverseEdges(), methodGenericInst );
                if( methodGeneric != NULL ) {
                  incomingInvocations.insert(methodGeneric->getId());
                }
              } else {
                incomingInvocations.insert(callerMethod.getId());
              }
            } else {
              incomingInvocations.insert(callerMethod.getId());
            }
          }
        }
        ListIterator<base::Base> itAcall = this->shared->factory->getReverseEdges().constIteratorBegin( methodCall.getId(), edkAttribute_Calls );
        for ( ; itAcall != this->shared->factory->getReverseEdges().constIteratorEnd( methodCall.getId(), edkAttribute_Calls ); ++itAcall ) {
          if ( Common::getIsAttribute( *itAcall ) ) {
            const logical::Attribute& callerAttribute = (const logical::Attribute&)(*itAcall);
            incomingInvocations.insert( callerAttribute.getId() );
          }
        }
      }
    }
  }

  const string& NII::translateLevel( Language language, const string& level ) const {
    const string& newLevel = MetricHandler::translateLevel( language, level );

    switch ( language ) {
      case limLangCpp:
        if (
          newLevel == NTYPE_LIM_CLASS ||
          newLevel == NTYPE_LIM_UNION ||
          newLevel == NTYPE_LIM_INTERFACE
        ) {
          return NTYPE_LIM_CLASS;
        }
        break;

      case limLangCsharp:
        if (
          newLevel == NTYPE_LIM_CLASS ||
          newLevel == NTYPE_LIM_INTERFACE
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
