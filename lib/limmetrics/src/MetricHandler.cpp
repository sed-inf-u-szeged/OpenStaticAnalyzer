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

#include "../inc/MetricHandler.h"
#include "../inc/Messages.h"

using namespace std;
using namespace common;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus { namespace lim { namespace metrics {

  MetricHandler::MetricHandler() :
    name( "Undefined" ), type( mdtInt ), enabled( false ), dependency( false ), shared( NULL ) {}

  MetricHandler::MetricHandler( const string& name, MetricDataTypes type, bool enabled, SharedContainers* shared ) :
      name( name ), type( type ), enabled( enabled ), dependency( false ), shared( shared )
  {
    WriteMsg::write( CMSG_LIMMETRICS_HANDLER_CREATED, name.c_str() );
  }

  const std::string& MetricHandler::getName() const {
    return name;
  }

  MetricDataTypes MetricHandler::getType() const {
    return type;
  }

  bool MetricHandler::getIsEnabled() const {
    return enabled;
  }

  bool MetricHandler::getIsDependency() const {
    return dependency;
  }

  void MetricHandler::setIsDependency( bool value ) {
    dependency = value;
  }

  bool MetricHandler::getIsOn() const {
    return enabled || dependency;
  }

  const set<string>& MetricHandler::getDependencies() const {
    return dependencies;
  }

  int MetricHandler::hasDependencies() const {
    return dependencies.size();
  }

  void MetricHandler::setCalculatedFor( const set<string>& c ) {
    calc = c;
  }

  void MetricHandler::dispatch( DispatchPhases phase, NodeWrapper& node ) {
    HandlerFunction* function = NULL;
    
    Language lang = node.getLanguage();
    auto phaseIt = dispatchMap.find( phase );
    if ( phaseIt != dispatchMap.end() ) {
      auto levelIt = phaseIt->second.find( translateLevel( lang, node.getLevel() ) );
      if ( levelIt != phaseIt->second.end() ) {
        auto langIt = levelIt->second.find( lang );
        if ( langIt != levelIt->second.end() ) {
          auto variantIt = langIt->second.find( translateVariant( lang, node.getIsVariant() ) );
          if ( variantIt != langIt->second.end() ) {
            function = &variantIt->second;
          }
        }

        // Fallback to the limLangOther language if there's no handler yet
        if ( function == NULL ) {
          langIt = levelIt->second.find( limLangOther );
          if ( langIt != levelIt->second.end() ) {
            auto variantIt = langIt->second.find( translateVariant( lang, node.getIsVariant() ) );
            if ( variantIt != langIt->second.end() ) {
              function = &variantIt->second;
            }
          }
        }
      }
    }

    if ( function != NULL ) {
      WriteMsg::write( CMSG_LIMMETRICS_DISPATCH, name.c_str(), node.getLimNode<base::Base>().getId(), phase );
      (*function)( node );
    } else {
      WriteMsg::write( CMSG_LIMMETRICS_NO_DISPATCH, name.c_str(), node.getLimNode<base::Base>().getId(), phase );
    }
  }

  /*
  * Default level translations for equivalent classes in a language
  */
  const string& MetricHandler::translateLevel( Language language, const std::string& level ) const {
    switch ( language ) {
      case limLangJava:
        if (
          level == NTYPE_LIM_ANNOTATION ||
          level == NTYPE_LIM_ENUM ||
          level == NTYPE_LIM_INTERFACE
        ) {
          return NTYPE_LIM_CLASS;
        }
        break;

      case limLangCpp:
        if ( level == NTYPE_LIM_NAMESPACE ) {
          return NTYPE_LIM_PACKAGE;
        }

        if (
          level == NTYPE_LIM_CLASS ||
          level == NTYPE_LIM_STRUCTURE
        ) {
          return NTYPE_LIM_CLASS;
        }

        if (
          level == NTYPE_LIM_METHOD ||
          level == NTYPE_LIM_FUNCTION
        ) {
          return NTYPE_LIM_METHOD;
        }
        break;

      case limLangC:
        if ( level == NTYPE_LIM_NAMESPACE ) {
          return NTYPE_LIM_PACKAGE;
        }

        if (
          level == NTYPE_LIM_STRUCTURE ||
          level == NTYPE_LIM_UNION
        ) {
          return NTYPE_LIM_STRUCTURE;
        }

        if (
          level == NTYPE_LIM_FUNCTION ||
          level == NTYPE_LIM_METHOD
        ) {
          return NTYPE_LIM_METHOD;
        }
        break;

      case limLangCsharp:
        if ( level == NTYPE_LIM_NAMESPACE ) {
          return NTYPE_LIM_PACKAGE;
        }

        if (
          level == NTYPE_LIM_CLASS ||
          level == NTYPE_LIM_STRUCTURE
        ) {
          return NTYPE_LIM_CLASS;
        }
        break;

      case limLangPython:
        if (
          level == NTYPE_LIM_FUNCTION ||
          level == NTYPE_LIM_METHOD
        ) {
          return NTYPE_LIM_METHOD;
        }

        if (
          level == NTYPE_LIM_PACKAGE ||
          level == NTYPE_LIM_MODULE
        ) {
          return NTYPE_LIM_PACKAGE;
        }
        break;
      case limLangJavaScript:
          if (
              level == NTYPE_LIM_FUNCTION ||
              level == NTYPE_LIM_METHOD
              ) {
              return NTYPE_LIM_METHOD;
          }
      default:
        break;
    }

    return level;
  }

  bool MetricHandler::translateVariant( Language language, bool variant ) const {
    switch ( language ) {
      case limLangJava: return false;
      default: return variant;
    }
  }

  void MetricHandler::registerHandler(
    DispatchPhases phase,
    const string& level,
    Language language,
    bool isVariant,
    HandlerFunction handler
  ) {

    if ( dispatchMap.find( phase ) == dispatchMap.end() ) {
      dispatchMap[phase] = map<string, map<Language, map<bool, HandlerFunction>>>();
    }

    if ( dispatchMap[phase].find( level ) == dispatchMap[phase].end() ) {
      dispatchMap[phase][level] = map<Language, map<bool, HandlerFunction>>();
    }

    if ( dispatchMap[phase][level].find( language ) == dispatchMap[phase][level].end() ) {
      dispatchMap[phase][level][language] = map<bool, HandlerFunction>();
    }

    dispatchMap[phase][level][language][isVariant] = handler;
  }

  void MetricHandler::addMetric( NodeWrapper& node, int value ) {
    if ( type == mdtFloat ) {
      throw Exception( COLUMBUS_LOCATION, CMSG_LIMMETRICS_EX_INVALID_METRIC_TYPE( name ) );
    }
    if ( enabled && isCalculatedFor(node) ) {
      node.addMetric( name, value );
    } else {
      WriteMsg::write( CMSG_LIMMETRICS_DISABLED_METRIC, name.c_str() );
    }
  }

  void MetricHandler::addMetric( NodeWrapper& node, double value ) {
    if ( type == mdtInt ) {
      throw Exception( COLUMBUS_LOCATION, CMSG_LIMMETRICS_EX_INVALID_METRIC_TYPE( name ) );
    }
    if ( enabled && isCalculatedFor(node) ) {
      node.addMetric( name, (float)value );
    } else {
      WriteMsg::write( CMSG_LIMMETRICS_DISABLED_METRIC, name.c_str() );
    }
  }

  void MetricHandler::propagateScopeInt( DispatchPhases phase, const string& level, Language lang ) {
    this->registerHandler( phase, level, lang, false, [this]( NodeWrapper& node ) {
      const base::Base* ptr = &node.getLimNode<base::Base>();
      Info& info = this->shared->scopes.map[ptr];
      addMetric( node, info.ints[this->name] );
    });
  }

  void MetricHandler::propagateComponentInt() {
    registerHandler( phaseFinalize, NTYPE_LIM_COMPONENT, limLangOther, false, [this] ( NodeWrapper& node ) {
      const base::Base* ptr = &node.getLimNode<base::Base>();
      Info& info = this->shared->components.map[ptr];
      addMetric( node, info.ints[this->name] );
    });
  }

  void MetricHandler::propagateScopeSet( DispatchPhases phase, const string& level, Language lang ) {
    this->registerHandler( phase, level, lang, false, [this]( NodeWrapper& node ) {
      const base::Base* ptr = &node.getLimNode<base::Base>();
      Info& info = this->shared->scopes.map[ptr];
      addMetric( node, (int) info.sets[this->name].size() );
    });
  }

  void MetricHandler::propagateComponentSet() {
    registerHandler( phaseFinalize, NTYPE_LIM_COMPONENT, limLangOther, false, [this] ( NodeWrapper& node ) {
      const base::Base* ptr = &node.getLimNode<base::Base>();
      Info& info = this->shared->components.map[ptr];
      addMetric( node, (int) info.sets[this->name].size() );
    });
  }

  void MetricHandler::propagateScopeMap( DispatchPhases phase, const string& level, Language lang ) {
    this->registerHandler( phase, level, lang, false, [this]( NodeWrapper& node ) {
      const base::Base* ptr = &node.getLimNode<base::Base>();
      Info& info = this->shared->scopes.map[ptr];
      addMetric( node, info.mapCount( this->name ) );
    });
  }

  void MetricHandler::propagateComponentMap() {
    registerHandler( phaseFinalize, NTYPE_LIM_COMPONENT, limLangOther, false, [this] ( NodeWrapper& node ) {
      const base::Base* ptr = &node.getLimNode<base::Base>();
      Info& info = this->shared->components.map[ptr];
      addMetric( node, info.mapCount( this->name ) );
    });
  }

  void MetricHandler::cleanup( NodeWrapper& node ) {
    cleanup( node, name );
  }

  void MetricHandler::cleanup( NodeWrapper& node, const std::string& name ) {

    if ( shared ) {
      
      const base::Base& base = node.getLimNode<base::Base>();
      Info* info;

      if ( Common::getIsScope( base ) ) {
        info = & shared->scopes.map[&base];
      } else if ( Common::getIsComponent( base ) ) {
        info = & shared->components.map[&base];
      }

      if ( info ) {
        info->ints.erase( name );
        info->sets.erase( name );
        info->maps.erase( name );
      }

    }

  }

  bool MetricHandler::isCalculatedFor( NodeWrapper& node ) {
    return calc.find( node.getLevel() ) != calc.end();
  }

}}}
