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

#include "../../inc/metrics/NOI.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus { namespace lim { namespace metrics {

  NOI::NOI( bool enabled, SharedContainers* shared ) : MetricHandler( "NOI", mdtInt, enabled, shared ) {

    // Method level NOI
    this->registerHandler( phaseVisit, NTYPE_LIM_METHOD, limLangOther, false, [this]( NodeWrapper& node ) {

      if ( ! node.isDefinition() ) {
        setInvalid( node );
        return;
      }

      const logical::Method& method = node.getLimNode<logical::Method>();
      set<NodeId> s;
      
      ListIterator<logical::MethodCall> i = method.getCallsListIteratorBegin(), end = method.getCallsListIteratorEnd();
      for ( ; i != end; ++i ) {
        fillCalledMethods( *i, s, false );
      }

      // remove self reference
      s.erase( method.getId() );

      addMetric( node, (int) s.size() );

      // add to class level NOI
      if ( ! node.isFunction() ) {
        this->shared->currentClassInfo().sets[this->name].insert( s.begin(), s.end() );
      }
    });

    // Attribute "visit" for class level NOI
    this->registerHandler( phaseVisit, NTYPE_LIM_ATTRIBUTE, limLangOther, false, [this]( NodeWrapper& node ) {
      const logical::Attribute& attr = node.getLimNode<logical::Attribute>();

      if ( ! this->shared->classStack.empty() ) {
        ListIterator<logical::MethodCall> i = attr.getCallsListIteratorBegin(), end = attr.getCallsListIteratorEnd();
        for ( ; i != end; ++i ) {
          fillCalledMethods( *i, this->shared->currentClassInfo().sets[this->name], false );
        }
      }
    });

    // Class level NOI
    this->registerHandler( phaseVisitEnd, NTYPE_LIM_CLASS, limLangOther, false, [this]( NodeWrapper& node ) {

      const logical::Class& clazz = node.getLimNode<logical::Class>();
      set<NodeId>& noiSet = this->shared->currentClassInfo().sets[this->name];

      // self references removed
      for ( ListIterator<logical::Member> hasMemberIt = clazz.getMemberListIteratorBegin(); hasMemberIt != clazz.getMemberListIteratorEnd(); ++hasMemberIt ) {
        if ( Common::getIsMethod( *hasMemberIt ) ) {
          noiSet.erase( hasMemberIt->getId() );
        }
      }

      addMetric( node, (int) noiSet.size() );
    });

    // C vs. C++ compat
    registerHandler( phaseVisit, NTYPE_LIM_STRUCTURE, limLangC, false, [this] ( NodeWrapper& node ) {
      setInvalid( node );
    });
    registerHandler( phaseVisit, NTYPE_LIM_UNION, limLangC, false, [this] ( NodeWrapper& node ) {
      setInvalid( node );
    });

  }

  void NOI::fillCalledMethods( const logical::MethodCall& end, std::set<NodeId>& calledMethods, bool withInstances ){
    const logical::Method* calledMethod = end.getMethod();
    if ( calledMethod ) {
      if ( ! withInstances ) {
        if ( Common::getIsMethodGenericInstance( *calledMethod ) ) {
            const logical::MethodGenericInstance& methodGenericInst = (const logical::MethodGenericInstance&)(*calledMethod);
            const logical::MethodGeneric* methodGeneric = Common::getMethodPrototype( this->shared->factory->getReverseEdges(), methodGenericInst );
            if( methodGeneric != NULL ) {
              calledMethods.insert( methodGeneric->getId() );
            }
        } else {
          calledMethods.insert( calledMethod->getId() );
        }
      } else {
        calledMethods.insert( calledMethod->getId() );
      }
    }
  }

  const string& NOI::translateLevel( Language language, const string& level ) const {
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
