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

#include "../../inc/Conditions/MultiCondition.h"

using namespace std;
using namespace columbus::graph;
using namespace columbus::lim::asg::base;

namespace columbus { namespace lim { namespace patterns { namespace conditions {
    MultiCondition::MultiCondition() {};
    MultiCondition::MultiCondition(MultiCondition *multiCond) {
        // move ownership
        for (auto &_cond : multiCond->conditions) {
            this->conditions.push_back(move(_cond));
        }
        // delete temp multiCond
        // usually we would not do this, but because how 'createConditionFromArray' is constructed, we must destroy the temporary object here
        delete multiCond;
    }
    MultiCondition::~MultiCondition() {}
    void MultiCondition::addCondition(Condition *_condition) {
        conditions.push_back(unique_ptr<Condition>(_condition));
    }
    bool MultiCondition::testCondition(Graph &inGraph, const Base& limNode) {
        for (auto &condition : conditions) {
            condition->testCondition(inGraph, limNode);
        }
        return true;
    }
    const vector<unique_ptr<Condition>>& MultiCondition::getConditions() {
        return this->conditions;
    };

}}}}