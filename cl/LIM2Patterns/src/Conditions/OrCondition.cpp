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

#include "../../inc/Conditions/OrCondition.h"

using std::string;
using columbus::graph::Graph;
using columbus::lim::asg::base::Base;

namespace columbus { namespace lim { namespace patterns { namespace conditions {
    OrCondition::OrCondition() {};
    OrCondition::OrCondition(MultiCondition *multiCond) : MultiCondition(multiCond) {};
    bool OrCondition::testCondition(Graph &inGraph, const Base& limNode) {
        for (auto &condition : conditions) {
            if (condition->testCondition(inGraph, limNode)) {
                return true;
            }
        }
        return false;
    };
}}}}