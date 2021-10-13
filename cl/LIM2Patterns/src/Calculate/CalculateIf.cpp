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

#include "../../inc/Calculate/CalculateIf.h"
#include "../../inc/Conditions/Condition.h"

using namespace std;
using namespace columbus::graph;
using namespace columbus::lim::asg::base;
using columbus::lim::patterns::conditions::Condition;

namespace columbus { namespace lim { namespace patterns { namespace calculate {
    IfCode::IfCode(Condition *_condition, CodeBlock* _code, const set<string> &_defineLocalVariables) : condition(move(_condition)), defineLocalVariables(_defineLocalVariables), codeBlock(move(_code)), elseIfStatements(), elseStatement(nullptr) {};
    IfCode::~IfCode() {}
    void IfCode::addElseIfStatemnt(IfCode * _ifCode) {
        elseIfStatements.push_back(unique_ptr<IfCode>(move(_ifCode)));
    }
    void IfCode::setElseStatement(IfCode * _ifCode) {
        elseStatement.reset(move(_ifCode));
    }
    bool IfCode::runCode(Graph &inGraph, const Base &base, stringAnyLValue &scopeVariables) {
        auto savedGlobalVars = Globals::roleNames()[Globals::currentPatternDocument()][Globals::currentlyIn().back().second].second;
        auto savedDepth = Globals::calculatedVariablesInNodesDepth();

        Globals::roleNames()[Globals::currentPatternDocument()][Globals::currentlyIn().back().second].second = scopeVariables;
        Globals::calculatedVariablesInNodesDepth() = 0;
        bool retVal = this->condition ? this->condition->testCondition(inGraph, base) : true;
        Globals::calculatedVariablesInNodesDepth() = savedDepth;
        Globals::roleNames()[Globals::currentPatternDocument()][Globals::currentlyIn().back().second].second = savedGlobalVars;

        if (retVal) {
            this->codeBlock->runCode(inGraph, base, scopeVariables);
        }
        else {
            if (!this->elseIfStatements.empty()) {
                for (auto &elseIF : this->elseIfStatements) {
                    retVal = elseIF->runCode(inGraph, base, scopeVariables);
                    if (retVal) break;
                }
            }
            if (!retVal && elseStatement) {
                this->elseStatement->runCode(inGraph, base, scopeVariables);
                retVal = true;
            }
        }
        return retVal;
    };

}}}}