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

#ifndef _CSVEXPORTER_H
#define _CSVEXPORTER_H

#include <graph/inc/graph.h>
#include <string>
#include <map>
#include <vector>

namespace columbus { namespace graphsupport {

  /**
   * \brief export impacted nodes from graph to a csv file
   * \param graph [in] graph
   * \param filename [in] the output file name
   * \param edgeTypes [in] the impaction edges
   */
  void exportImpactSet(graph::Graph& graph, const std::string& filename, graph::Edge::EdgeTypeSet& edgeTypes);

  /**
   * \brief export impacted nodes from graph to a csv file
   * \param graph [in] graph
   * \param filename [in] the output file name
   * \param edgeTypes [in] the impaction edges
   * \param parentNodes [in] the impacted nodes parents
   */
  void exportImpactSet(graph::Graph& graph, const std::string& filename, graph::Edge::EdgeTypeSet& edgeTypes, const std::set<graph::Node>& parentNodes);

  void exportReadableMetricsCSV(graph::Graph& graph, const std::string& filename, char separator = ',', char dmark = '.');

}}

#endif
