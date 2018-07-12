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

#ifndef _GRAPHSUPPORTRULBUILDER
#define _GRAPHSUPPORTRULBUILDER

#include <graph/inc/graph.h>
#include "GraphRangeIndexer.h"


namespace columbus {

  namespace rul {
    class RulHandler;
  }

  namespace graphsupport {
    void buildRulToGraph(graph::Graph& graph, rul::RulHandler& rulHandler);
        
    void buildRuleItemToGraph(graph::Graph& graph,
                              const std::string& metricID, 
                              const std::string& toolID, 
                              const std::string& description, 
                              const std::string& displayName, 
                              bool isEnabled, 
                              const std::string& groupType, 
                              const std::string& helpText, 
                              bool isWarning, 
                              const std::map<std::string, std::string>& settings, 
                              const std::set<std::string>& calculated);
                              
    bool readRuleItemFromGraph(graph::Graph& graph,
                              const std::string& metricID, 
                              std::string& description, 
                              std::string& displayName, 
                              bool& isEnabled, 
                              std::string& groupType, 
                              std::string& helpText, 
                              bool& isWarning, 
                              std::map<std::string, std::string>& settings, 
                              std::set<std::string>& calculated);
  }
}

#endif
