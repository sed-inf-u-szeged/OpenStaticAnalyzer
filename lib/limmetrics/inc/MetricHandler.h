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

#ifndef _METRIC_HANDLER_H_
#define _METRIC_HANDLER_H_

#include "Containers.h"
#include "Defines.h"
#include "NodeWrapper.h"

#include "graphsupport/inc/GraphConstants.h"

#include <map>
#include <functional>

namespace columbus { namespace lim { namespace metrics {

  //
  // TYPES
  //

  class MetricHandler;

  /**
  * The type of the metric handler functions
  */
  typedef std::function<void(NodeWrapper&)> HandlerFunction;

  class MetricHandler {

    public:

      //
      // CONSTRUCTOR / DESTRUCTOR
      //

      MetricHandler(); ///> Default constructor for use with the "[]" operator
      MetricHandler( const std::string& name, MetricDataTypes type, bool enabled, SharedContainers* shared = NULL );
      virtual ~MetricHandler() {}

      //
      // SETTERS/GETTERS
      //

      /**
      * Getter for the name attribute
      */
      const std::string& getName() const;

      /**
      * Getter for the type attribute
      */
      MetricDataTypes getType() const;

      /**
      * Getter for the enabled attribute
      */
      bool getIsEnabled() const;

      /**
      * Getter for the dependency attribute
      */
      bool getIsDependency() const;

      /**
      * Setter for the dependency attribute
      */
      void setIsDependency( bool value );

      /**
      * Getter for the virtual "on" property
      * A metric handler is considered to be on when it is either enabled on its own or it is a dependency
      * of another metric
      */
      bool getIsOn() const;

      /**
      * Getter for the names of the other metrics on which the calculation of this metric depends
      */
      const std::set<std::string>& getDependencies() const;

      /**
      * Getter for the number of other metrics on which the calculation of this metric depends
      */
      int hasDependencies() const;

      /**
      * Setter for the calculatedFor entries of this metric
      */
      void setCalculatedFor( const std::set<std::string>& c );

      //
      // DISPATCH
      //

      /**
      * This method does the actual dispatching of nodes to their corresponding handlers which are looked
      * up in the dispatchMap below by phase (initialize, prepare, process, finalize, see aliases below),
      * level (string values come from the GraphConstants header), language (enum values from the LIM
      * Type.h header) and finally whether the current node is a variant or not.
      *
      * This dispatch mechanism will be common for every metric handler class, they only need to register
      * their corresponding member functions to the appropriate place in the dispatch map by calling the
      * register method.
      *
      * Note that there are default implementations and dispatch fallbacks for empty map entries so a new
      * metric handler class only needs to define the methods that are relevant to it. I.e. if the phase,
      * level, language or variant flag of the node does not lead to a defined handler, nothing happens
      *
      * Language-based defaults (e.g. every computation that is defined for a class will be that same for
      * enums/annotations/etc. so an automatic redirect can be injected in the dispatch mechanism) can be
      * by modifying the translate methods or overriding them in an intermediate subclass
      */
      void dispatch( DispatchPhases phase, NodeWrapper& node );

      /**
      * Translator method for the metric level by language
      * Can be used to set default redirects (see above)
      */
      virtual const std::string& translateLevel( asg::Language language, const std::string& level ) const;

      /**
      * Translator method for the variant flag by language
      * Can be used to set default redirects (see above)
      */
      virtual bool translateVariant( asg::Language language, bool variant ) const;

      //
      // HELPERS
      //

      void addMetric( NodeWrapper& node, int value );
      void addMetric( NodeWrapper& node, double value );

    protected:

      /**
      * This method can be used by the descendant nodes to add concrete handlers to certain events
      */
      void registerHandler(
        DispatchPhases phase,
        const std::string& level,
        asg::Language language,
        bool isVariant,
        HandlerFunction handler
      );

      //
      // DATA
      //

      std::string name;
      MetricDataTypes type;

      bool enabled;
      bool dependency;

      std::set<std::string> dependencies;

      std::map<DispatchPhases, std::map<std::string, std::map<asg::Language, std::map<bool, HandlerFunction>>>> dispatchMap;

      SharedContainers* shared;

      /**
      * A cached set of calculatedFor entries
      */
      std::set<std::string> calc;

      //
      // COMMON METHODS
      //

      void propagateScopeInt( DispatchPhases phase, const std::string& level, asg::Language lang );
      void propagateComponentInt();

      void propagateScopeSet( DispatchPhases phase, const std::string& level, asg::Language lang );
      void propagateComponentSet();

      void propagateScopeMap( DispatchPhases phase, const std::string& level, asg::Language lang );
      void propagateComponentMap();

      void cleanup( NodeWrapper& node );
      void cleanup( NodeWrapper& node, const std::string& name );

      bool isCalculatedFor( NodeWrapper& node );
  };

}}}

#endif
