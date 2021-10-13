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

#ifndef _UDM_HELPER_
#define _UDM_HELPER_

#include "UdmCommon.h"
#include "UdmNode.h"
#include "UdmFunction.h"
#include "graphsupport/inc/Metric.h"
#include "rul/inc/RulHandler.h"

using namespace std;
using namespace columbus;
using namespace common;

// Loading graph's "RulMetric" type nodes Calculated for attributes
void loadGraphcCalcFor(graph::Graph& graph, map<string, set<string>>& graph_calculatedFors);

// Loading user's metrics to udm_nodes, after this function it's safe to use
void loadUdmMetrics(map<string, UdmNode>& udm_nodes, rul::RulHandler& rulHand, map<string, set<string>>& metricNodeCalculatedFors);

// Checking the "calculated for" attributes between the formulas and its dependencies
void checkCalcFors(const map<string, UdmNode>& udm_nodes, map<string, set<string>>& graph_calculatedFors);

// Building the dependency vector, detecting loops
void buildDependency(vector<vector<string>>& passVector, map<string, UdmNode>& udm_nodes);

// Calculate every metrics in every Node and write it to the graph
void evaluateGraph(const map<string, UdmNode>& udm_nodes, const vector<vector<string>>& passVector, graph::Graph& graph);


#endif
