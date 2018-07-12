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

#include "../inc/NodeWrapper.h"
#include "../inc/Messages.h"

#include "common/inc/WriteMessage.h"
#include "graphsupport/inc/GraphConstants.h"
#include "lim2graph/inc/VisitorGraphConverter.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graph;
using namespace columbus::graphsupport::graphconstants;

namespace columbus { namespace lim { namespace metrics {

  NodeWrapper::NodeWrapper( const base::Base& limNode, Graph& graph ) : limNode( &limNode ), graph( &graph ) {
    graphNode = graph.findNode( lim2graph::VisitorGraphConverter::determineNodeName( limNode ) );
    if ( this->graphNode == graph::Graph::invalidNode ) {
      throw Exception( COLUMBUS_LOCATION, CMSG_LIMMETRICS_EX_INVALID_GRAPH_NODE( Common::toString( limNode.getId() ) ) );
    }
  }

  const Node& NodeWrapper::getGraphNode() const {
    return graphNode;
  }

  const std::string& NodeWrapper::getLevel() const {

    Language lang = getLanguage();

    if ( Common::getIsClass( *limNode ) ) {
      switch ( dynamic_cast<const logical::Class&>(*limNode).getClassKind() ) {
        case clkAnnotation: return NTYPE_LIM_ANNOTATION;
        case clkEnum: return NTYPE_LIM_ENUM;
        case clkInterface: return NTYPE_LIM_INTERFACE;
        case clkStruct: return NTYPE_LIM_STRUCTURE;
        case clkUnion: return NTYPE_LIM_UNION;

        case clkClass:
        default:
          return NTYPE_LIM_CLASS;
      }

    } else if ( Common::getIsMethod( *limNode ) ) {

      if ( isFunction() ) return NTYPE_LIM_FUNCTION;
      return NTYPE_LIM_METHOD;

    } else if ( Common::getIsAttribute( *limNode ) ) {
      return NTYPE_LIM_ATTRIBUTE;

    } else if ( Common::getIsPackage( *limNode ) ) {

      if ( lang == limLangCpp || lang == limLangC || lang == limLangCsharp ) return NTYPE_LIM_NAMESPACE;
      if ( lang == limLangPython && dynamic_cast<const logical::Package&>( *limNode ).getPackageKind() == pkModule ) {
        return NTYPE_LIM_MODULE;
      }
      return NTYPE_LIM_PACKAGE;

    } else if ( Common::getIsFile( *limNode ) ) {
      return NTYPE_LIM_FILE;

    } else if ( Common::getIsComponent( *limNode ) ) {
      return NTYPE_LIM_COMPONENT;
    }

    return NTYPE_LIM_ROOT;
  }

  Language NodeWrapper::lnk2limLang( LanguageKind kind ) {
    switch ( kind ) {
      case lnkJava: return limLangJava;
      case lnkC: return limLangC;
      case lnkCpp: return limLangCpp;
      case lnkCsharp: return limLangCsharp;
      case lnkPython: return limLangPython;
      case lnkJavaScript: return limLangJavaScript;
      default: break;
    }
    return limLangOther;
  }

  Language NodeWrapper::getLanguage() const {
    if ( Common::getIsMember( *limNode ) ) {
      LanguageKind kind = dynamic_cast<const logical::Member&>( *limNode ).getLanguage();
      if ( kind != lnkNotSet ) {
        return lnk2limLang( kind );
      }

      // Special case: The root package doesn't have a language kind
      // so we use the language of the factory instead
      if ( limNode->getId() == limNode->getFactory().getRoot()->getId() ) {
        return limNode->getFactory().getLanguage();
      }
    }
    return limLangOther;
  }

  bool NodeWrapper::getIsVariant() const {
    return false; // TODO temporary
  }

  void NodeWrapper::addMetric( const std::string& metric, int value ) {
    //cout << "  " << limNode->getId() << "(" << Common::to_string(limNode->getNodeKind()) << ") --> " << metric << "= " << value << endl;
    graph::Attribute::AttributeIterator aIt = graphNode.findAttributeByName( metric );
    if ( aIt.hasNext() ) {
      ((graph::AttributeInt&)aIt.next()).incValue( value );
    } else {
      graphNode.addAttribute( graph->createAttributeInt( metric, CONTEXT_METRIC, value ) );
    }
  }

  void NodeWrapper::addMetric( const std::string& metric, float value ) {
    //cout << "  " << limNode->getId() << "(" << Common::to_string(limNode->getNodeKind()) << ") --> " << metric << "= " << value << endl;
    graph::Attribute::AttributeIterator aIt = graphNode.findAttributeByName( metric );
    if ( aIt.hasNext() ) {
      ((graph::AttributeFloat&)aIt.next()).incValue( value );
    } else {
      graphNode.addAttribute( graph->createAttributeFloat( metric, CONTEXT_METRIC, value ) );
    }
  }

  int NodeWrapper::getIntMetric(const std::string& metric) {
    graph::Attribute::AttributeIterator aIt = graphNode.findAttributeByName(metric);
    if (aIt.hasNext()) {
      return ((graph::AttributeInt&)aIt.next()).getValue();
    }
    else {
      return 0;
    }
  }

  float NodeWrapper::getFloatMetric(const std::string& metric) {
    graph::Attribute::AttributeIterator aIt = graphNode.findAttributeByName(metric);
    if (aIt.hasNext()) {
      return ((graph::AttributeFloat&)aIt.next()).getValue();
    }
    else {
      return 0;
    }
  }

  bool NodeWrapper::isDefinition() const {
    return isDefinition( *limNode );
  }

  bool NodeWrapper::isDefinition( const base::Base& node ) {
    if ( Common::getIsMember( node ) ) {
      const logical::Member& member = dynamic_cast<const logical::Member&>( node );
      ListIteratorAssocSourcePosition<physical::File> i = member.getIsContainedInListIteratorAssocBegin();
      for (; i != member.getIsContainedInListIteratorAssocEnd(); ++i) {
        const SourcePosition& srcPos =  i.getAssocClass();
        if ( srcPos.getRealizationLevel() == relDefines ) return true;
      }
    }
    return false;
  }

  bool NodeWrapper::isFunction() const {
    return isFunction( *limNode );
  }

  bool NodeWrapper::isFunction( const base::Base& node ) {
    return Common::getIsMethod( node ) && ! isParentClass( node );
  }

  bool NodeWrapper::isGlobalAttribute() const {
    return isGlobalAttribute( *limNode );
  }

  bool NodeWrapper::isGlobalAttribute( const base::Base& node ) {
    return Common::getIsAttribute( node ) && ! isParentClass( node );
  }

  bool NodeWrapper::isParentClass( const asg::base::Base& node ) {
    ListIterator<base::Base> it = node.getFactory().getReverseEdges().constIteratorBegin( node.getId(), edkScope_HasMember );
    if ( it != node.getFactory().getReverseEdges().constIteratorEnd( node.getId(), edkScope_HasMember ) ) {
      return Common::getIsClass( *it );
    }
    return false;
  }

}}}
