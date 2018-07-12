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

#ifndef _RUL_PARSER_H_
#define _RUL_PARSER_H_

#include "Containers.h"
#include "MetricHandler.h"

#include "rul/inc/RulHandler.h"

namespace columbus { namespace lim { namespace metrics {

  class RulParser {

    public: 

      /**
      * Constructs a new RulParser from a "built-in" RulHandler
      */
      RulParser( rul::RulHandler& rul, SharedContainers& shared );

      /**
      * Deletes the allocated MetricHandlers
      */
      ~RulParser();

      /**
      * Dispatches the node to the loaded metric handlers in dependency order
      * (For more on the dispatch mechanism, see MetricHandler::dispatch)
      */
      void dispatch( DispatchPhases phase, NodeWrapper& node );

      /**
      * Signals the shared containers that a given phase is over
      */
      void phaseOver( DispatchPhases phase );

    private:

      /**
      * This method parses every metric from the given rul file (even disabled ones)
      * and translates them to their corresponding metric handlers
      *
      * Then it propagates dependency information
      * In the end, only those metrics will be marked as "on" that can be reached from
      * enabled nodes in the dependency tree
      */
      void parse();

      /**
      * This method matches a MetricHandler instance to a given metric in the RUL by its name
      */
      MetricHandler* matchHandler( const std::string& id, bool enabled );

      /**
      * This method sorts the loaded handlers by their dependencies so that when a
      * concrete node is processed they can be simply executed in order
      */
      void sort();

      /**
      * The (sorted) list of loaded metric handlers
      * (represented as a group of metric handlers mapped by their names and a separate
      * order vector)
      */
      std::map<std::string, MetricHandler*> handlerMap;
      std::vector<std::string> handlerOrder;

      /**
      * The original rul handler
      */
      rul::RulHandler& rul;

      /**
      * Shared containers
      */
      SharedContainers& shared;
      
      /**
      * Common stack maintenance for the shared containers
      */
      void stack( const NodeWrapper& node, bool push );

      /**
      * Checks whether a certain metric is calculated for a specific node type
      */
      bool isCalculatedFor( const std::string& metric, NodeWrapper& node );
  };

}}}

#endif
