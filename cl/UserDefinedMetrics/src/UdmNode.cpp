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

#include "../inc/UdmNode.h"
#include <iostream>

UdmNode::UdmNode(const string& metricName, const string& formula, const string& formulaType, const set<string>& calcFor) :
                metricName(metricName), formula(formula), formulaType(formulaType), calcFor(calcFor), visited(false) {}

int UdmNode::traverse(vector<vector<string>>& passVector, map<string, UdmNode>& nodes, vector<string>& loopCheck) {

    if (!visited) {
        
        // If the loopCheck already contains this metric, there is a loop
        if (find(loopCheck.begin(), loopCheck.end(), metricName) != loopCheck.end()) {
            
            throwLoopEx(loopCheck, metricName);
            
        }

        loopCheck.push_back(metricName);
        passIndex = 0;
        // Requesting the pass deps passIndexes with traverse(), store the max value. If they wasn't in the vector yet, inserted.
        for (const string& metric : passDependency) {

            UdmNode& dep = nodes.find(metric)->second;
            int depIndex = dep.traverse(passVector, nodes, loopCheck);
            if (depIndex > passIndex) {
                passIndex = depIndex;
            }
        }

        // If have pass dependency, Node must be one higher pass then the max value
        if (passDependency.size()) { passIndex++; }


        // Requesting the normal deps passIndexes, update passIndex, if it's necessary.
        // Calling the deps traverse first guarantee, they be before in the passVector
        for (const string& metric : normalDependency) {

            UdmNode& dep = nodes.find(metric)->second;
            int depIndex = dep.traverse(passVector, nodes, loopCheck);
            if (depIndex > passIndex) {
                passIndex = depIndex;
            }
        }

        // Only there setting visited true, bc the loopChecking
        visited = true;
        passVector[passIndex].push_back(metricName);
    }

    return passIndex;
}

const string& UdmNode::getMetricName() const { return metricName; }

const string& UdmNode::getFormula() const { return formula; }

const string& UdmNode::getFormulaType() const { return formulaType; }

const set<string>& UdmNode::getCalcFors() const { return calcFor; }

const set<string>& UdmNode::getNormalDependency() const { return normalDependency; }

const set<string>& UdmNode::getPassDependency() const { return passDependency; }

const set<string>& UdmNode::getGraphDependency() const { return graphDependency; }

const vector<pair<set<string>, string>>& UdmNode::getAggregateCalcFors() const { return aggrCalcFors; }

set<string>& UdmNode::getNormalDependency() { return normalDependency; }

set<string>& UdmNode::getPassDependency() { return passDependency; }

set<string>& UdmNode::getGraphDependency() { return graphDependency; }

vector<pair<set<string>, string>>& UdmNode::getAggregateCalcFors() { return aggrCalcFors; }
