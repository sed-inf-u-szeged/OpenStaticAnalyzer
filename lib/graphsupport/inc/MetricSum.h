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

#ifndef _METRICSUMGRAPSUPPORT
#define _METRICSUMGRAPSUPPORT

#include <graph/inc/graph.h>
#include "GraphRangeIndexer.h"


namespace columbus { 
  
  namespace rul {
    class RulHandler;
  }

  namespace graphsupport { 

  /**
  * \brief Summarizes the warning attributes (attributes with 'warning' context) in the 'graph' along the 'edgeType' type edges
  * \param graph [inout] the graph
  * \param edgeType [in] the type of edges
  * \param sumWarnings [in] if it is true, warning will be summarized, otherwise not
  * \param metrics [in] if it is not empty, then it summarizes the metrircs in the given set
  */
  void cumSum(graph::Graph& graph, const graph::Edge::EdgeType& edgeType, bool sumWarnings, const std::set<std::string>& metrics =  std::set<std::string>());

  /**
  * \brief Create attributeInt for groups of summarized and summarize metrics by groups (grups and metrics in rulx file)
  * \param graph [inout] the graph
  * \param rulHandler [in] rule handler
  * \param metrics [in] if it is not empty, then it creates the groups for the metrics in the given set
  */
  void createGroupMetrics(graph::Graph& graph, rul::RulHandler& rulHandler, const std::set<std::string>& metrics =  std::set<std::string>());

  /**
   * \brief Summarizes the warning metrics by priorty and creates metrics for each priority category. 
   * \param graph    [inout] the graph
   * \param buildRul [in]    If it is set, artificial rule nodes for the priority metrics will also be built into the graph
   * \param metrics [in] if it is not empty, then it creates the priority groups for the metrics in the given set
   */
  void summarizeWarningMetricsByPriority(graph::Graph& graph, const bool buildRul, const std::set<std::string>& metrics =  std::set<std::string>());
  }

}

#endif
