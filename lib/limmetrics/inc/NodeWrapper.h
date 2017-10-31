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

#ifndef _NODE_WRAPPER_H_
#define _NODE_WRAPPER_H_

#include "lim/inc/lim.h"
#include "graph/inc/graph.h"

namespace columbus { namespace lim { namespace metrics {

  /**
  * The NodeWrapper class encapsulates a LIM and a GRAPH node and adds helper
  * methods that make common, metrics related tasks easier.
  *
  * The computation of metrics can vary for different source languages, node
  * types (and even node kinds or other attributes inside the same node type)
  * or whether the node is a variant or aggregate in the lim. The definition
  * of these categories are centralized here along with typecasts and helpers
  * to attach labeled values onto the wrapped graph node.
  */
  class NodeWrapper {

    public:

      //
      // CONSTRUCTORS
      //

      /**
      * Node wrappers can be constructed from a lim node and the whole converted
      * lim graph. The corresponding graph node is automatically loaded using a
      * unique id obtained from the lim node.
      */
      NodeWrapper() {}
      NodeWrapper( const asg::base::Base& limNode, graph::Graph& graph );

      //
      // GETTERS
      //

      /**
      * Getter method for the wrapped lim node
      * Templated for automatic type casts but the type parameter can be omitted
      * if a Base node is acceptable
      */
      template<class L> const L& getLimNode() const {
        return dynamic_cast<const L&>( *limNode );
      }

      /**
      * Getter method for the wrapped graph node
      */
      const graph::Node& getGraphNode() const;

      /**
      * Getter for the metric level of the node
      */
      const std::string& getLevel() const;

      /**
      * Getter for the source language of the node
      */
      asg::Language getLanguage() const;

      /**
      * Flag indicating whether the node is a variant or an aggregate
      */
      bool getIsVariant() const;

      //
      // GRAPH HELPERS
      //

      /**
      * Metric value setters/incrementers
      */
      void addMetric( const std::string& metric, int value );
      void addMetric( const std::string& metric, float value );

      /**
      * Metric value getters
      */
      int getIntMetric( const std::string& metric );
      float getFloatMetric( const std::string& metric );

      //
      // COMMON ATTRIBUTES
      //

      /**
      * Checks if the current node is a member definition
      */
      bool isDefinition() const;
      static bool isDefinition( const asg::base::Base& node );

      bool isFunction() const;
      static bool isFunction( const asg::base::Base& node );

      bool isGlobalAttribute() const;
      static bool isGlobalAttribute( const asg::base::Base& node );

    private:

      static bool isParentClass( const asg::base::Base& node );

      static asg::Language lnk2limLang( asg::LanguageKind kind );

      const asg::base::Base* limNode;
      graph::Node graphNode;
      graph::Graph* graph;
  };

}}}

#endif