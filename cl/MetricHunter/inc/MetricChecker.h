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

#ifndef _METRICCHECKER_H_
#define _METRICCHECKER_H_

#include <graph/inc/graph.h>
#include <rul/inc/RulHandler.h>
#include "ThresholdReader.h"
#include "Threshold.h"

namespace columbus { namespace rul {

  class MetricChecker {
  private:
    graph::Graph& theGraph;
    rul::RulHandler *rul;
    std::set<std::string> nodeTypes;
    std::string txtOutputFileName;
  public:
    int count;
    void addNodeType(std::string& nodeType);
    inline const bool checkRuleProperties(std::string& rulid, const std::string& nodetype);
    void runChecker();
    graph::Graph& getGraph() { return theGraph;}
    void addWarning(columbus::graph::Node& node, const std::string& warningName, const std::string& warningText);
    void save(const std::string& savingPath, bool saveXML, const std::string& xmlPath);
    void executeCheck(columbus::graph::Node& node, const std::string& metricName, const std::string& rulename, const std::string& relation, const std::string& baseline);
    MetricChecker(graph::Graph& graph, rul::RulHandler& handler, const std::string& txtOutputFileName);
    ~MetricChecker() { }
  };

} }

#endif
