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

#ifndef _UDM_NODE_
#define _UDM_NODE_

#include "UdmCommon.h"
#include <algorithm>
#include <set>
#include <vector>
#include <map>

using namespace std;
using namespace columbus;

class UdmNode {

private:
    
    string metricName;

    string formula;
    
    string formulaType;
    
    set<string> calcFor;

    // Stores all of the dependencies, which must be load from the graph before calculate this metric
    set<string> graphDependency;

    // Stores all of the udm_dependencies, which must be calculated in the same Node before this metric
    set<string> normalDependency;
    
    // Stores all of the udm_dependencies, which must be calculated for every Node before this metric
    set<string> passDependency;
    
    // Have elements, if the formula contains aggr. function. The set store the child types (which derived Nodes will be aggregated), the string is the requested metric
    vector<pair<set<string>, string>> aggrCalcFors;
    
    // Indicate if the passIndex is already calculated
    bool visited;
    
    int passIndex;
    
public:

    UdmNode(const string& metricName, const string& formula, const string& formulaType, const set<string>& calcFor);

    const string& getMetricName() const;
    
    const string& getFormula() const;
    
    const string& getFormulaType() const;
    
    const set<string>& getCalcFors() const; 
    
    const set<string>& getNormalDependency() const;
    
    const set<string>& getPassDependency() const;

    const set<string>& getGraphDependency() const;
    
    const vector<pair<set<string>, string>>& getAggregateCalcFors() const;

    // Non const bc we can fill it directly
    set<string>& getNormalDependency();

    set<string>& getPassDependency();

    set<string>& getGraphDependency();

    vector<pair<set<string>, string>>& getAggregateCalcFors();

    // Calculate the passIndex of this Node, call their dependencies traverse(), then insert oneself
    // Return value : passIndex
    int traverse(vector<vector<string>>& passVector, map<string, UdmNode>& nodes, vector<string>& loopCheck);

};

#endif