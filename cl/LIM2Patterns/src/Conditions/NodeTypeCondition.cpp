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

#include "../../inc/Conditions/NodeTypeCondition.h"
#include "../../inc/Helpers.h"

using namespace std;
using namespace columbus::graph;
using namespace columbus::lim::asg;
using namespace columbus::lim::asg::base;
//using namespace columbus::lim::patterns::calculate;

namespace columbus { namespace lim { namespace patterns { namespace conditions {
    // TODO:: Calculate remove
    NodeTypeCondition::NodeTypeCondition(NodeKind _nodeKind, Condition *_condition, Condition *_filterCondition, /*Code *_calculateCode,*/ const string &_roleName, const string &_patternName, const string &_displayName, const string &_category, const string &_description, const string &_priority)
        : 
        patternName(_patternName), 
        displayName(_displayName), 
        category(_category), 
        description(_description), 
        roleName(_roleName), 
        priority(_priority) ,
        filterCondition(move(_filterCondition)),
        condition(move(_condition)), 
        nodeKind(_nodeKind)/*, 
        calculate(move(_calculateCode)) */// TODO:: Calculate remove
    { };
    NodeTypeCondition::~NodeTypeCondition() {}
    const NodeKind& NodeTypeCondition::getNodeKind() {
        return this->nodeKind;
    }
    const string & NodeTypeCondition::getPatternName() {
        return this->patternName;
    }
    const string & NodeTypeCondition::getDisplayName() {
        return this->displayName;
    }
    const string & NodeTypeCondition::getCategory() {
        return this->category;
    }
    const string & NodeTypeCondition::getDescription() {
        return this->description;
    }
    const string& NodeTypeCondition::getRoleName() {
        return this->roleName;
    }
    const string & NodeTypeCondition::getPriority() {
        return this->priority;
    }
    const unique_ptr<Condition>& NodeTypeCondition::getFilterCondition() {
        return this->filterCondition;
    }
    bool NodeTypeCondition::testCondition(Graph &inGraph, const Base& limNode) {

        const auto &currentPatternDoc = currentPatternDocument();
        auto &roleNames = getRoleNames()[currentPatternDoc];

        if (recursiveNodeKindSearching(limNode.getNodeKind(), this->nodeKind)) {
            bool r = true;

            // filtering
            if (filterCondition != nullptr) {
                if (!filterCondition->testCondition(inGraph, limNode)) {
                    return false;
                }
            }
            
            roleNames[this->roleName].first = limNode.getId(); 
            currentlyIn().push_back({ this->nodeKind, this->roleName });
            // TODO:: Calculate remove
            /*
            auto &currentVariables = roleNames[this->roleName].second;

            {
                if (currentlyIn().size() > 1) {
                    const string &_selector = currentlyIn()[currentlyIn().size() - 2].second;
                    auto &previousVariables = roleNames[_selector].second;
                    for (auto &_variable : previousVariables) {
                        currentVariables[_variable.first] = _variable.second;
                    }
                }
            }
            
            
            // run codes if its defined
            if (this->calculate != nullptr) {
                this->calculate->runCode(inGraph, limNode, currentVariables);
            }
            
            if (Common::getIsMember(limNode)) {
                stringAnyLValue _variables;
                if (currentlyIn().size() > 1) {
                    const string &_selector = currentlyIn()[currentlyIn().size() - 2].second;
                    auto &previousVariables = roleNames[_selector].second;

                    for (auto &_variable : currentVariables) {
                        if (previousVariables.find(_variable.first) == previousVariables.end()) {
                            _variables[_variable.first] = _variable.second;
                        }
                    }
                }
                else {
                    _variables = currentVariables;
                }
            }*/
            result().addNodeToTrace(limNode.getId(), this->roleName, this->patternName,/* _variables,*/ calculatedVariablesInNodesDepth());
            
            // testing
            r = condition ? condition->testCondition(inGraph, limNode) : true;
            
            if (!Common::getIsMember(limNode) || !r || roleNames[this->roleName].second) {
                result().removeFromTrace(limNode.getId());
            }
            // TODO:: Calculate remove
            /*
            {
                if (currentlyIn().size() > 1) {
                    const string &_selector = currentlyIn()[currentlyIn().size() - 2].second;
                    auto &previousVariables = roleNames[_selector].second;
                    for (auto &_variable : currentVariables) {
                        if (previousVariables.find(_variable.first) != previousVariables.end()) {
                            previousVariables[_variable.first] = _variable.second;
                        }
                    }
                }
            }*/
            currentlyIn().pop_back();

            
            roleNames[this->roleName].first = NO_VALUE;
            return r;
        }
        else
            return false;
    }

}}}}