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

#include "../../inc/Calculate/CalculateFor.h"
#include "../../inc/Conditions/FormulaCondition.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graph;
using namespace columbus::lim::asg::base;
using columbus::lim::patterns::conditions::FormulaCondition;

namespace columbus { namespace lim { namespace patterns { namespace calculate {
    EdgeForCode::EdgeForCode(Direction &_direction, const string &_localVariableName, const set<string> _defineLocalVariables, const string &_nodeToFindIn, EdgeKind _edgeKind, CodeBlock* _code) : 
        direction(_direction),
        localVariableName(_localVariableName), 
        defineLocalVariables(_defineLocalVariables), 
        nodeToFindIn(_nodeToFindIn),
        edgeKind(_edgeKind),  
        codeBlock(move(_code)) {};
    EdgeForCode::~EdgeForCode() {};

    bool EdgeForCode::runCode(Graph &inGraph, const Base &base, stringAnyLValue &scopeVariables) {
        stringAnyLValue thisScope = scopeVariables;
        static Factory &fact = base.getFactory();
        const auto &currentPatternDoc = Globals::currentPatternDocument();
        auto &roleNames = Globals::roleNames()[currentPatternDoc];

        for (const auto &_str : defineLocalVariables) {
            thisScope[_str].second = boost::any();
        }

        thisScope[localVariableName].second = boost::any();
        const Base &_nodeToFindIn = (nodeToFindIn.empty()) ?
            base :
            (roleNames.find(nodeToFindIn) != roleNames.end() ?
                fact.getRef(roleNames[nodeToFindIn].first) :
                *(boost::any_cast<Base*>(thisScope[nodeToFindIn].second)));

        const auto &travelTo = Globals::getTraversalEdges(_nodeToFindIn, this->edgeKind, this->direction);

        for (size_t index = 0; index < travelTo.size(); index++) {
            thisScope[localVariableName].second = boost::any(travelTo[index]);
            codeBlock->runCode(inGraph, *travelTo[index], thisScope);
            thisScope[localVariableName].second = boost::any();
        }

        // Refresh the values in the parent Scope
        for (auto &_val : scopeVariables) {
            // if variable exists and its not overlapped by a local variable
            if (!thisScope.at(_val.first).second.empty() && defineLocalVariables.find(_val.first) == defineLocalVariables.end() && _val.first != localVariableName) {
                _val.second.second = thisScope[_val.first].second;
            }
        }
        return true;
    };

}}}}