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

#include "../../inc/Calculate/CreateCalculate.h"
#include "../../inc/Conditions/CreateCondition.h"
#include "../../inc/Calculate/Checker/PatternValidator.h"
#include "../../inc/GlobalsAndConstans.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::lim::patterns::conditions;
using namespace columbus::lim::patterns::calculate::validator;

namespace columbus { namespace lim { namespace patterns { namespace calculate {

    Code* createCalculate(const YAML::Node &node) {
        
        validateNode(node);
        auto &variables = Globals::roleNames()[Globals::currentPatternDocument()][Globals::currentlyIn().back().second].second;

        if (0 < node[DEFINE].size()) {
            if (Globals::currentlyIn().size() > 1) {
                auto &_previousVariables = Globals::roleNames()[Globals::currentPatternDocument()][Globals::currentlyIn()[Globals::currentlyIn().size() - 2].second].second;
                variables.insert(_previousVariables.begin(), _previousVariables.end());
            }
        }

        for (size_t index = 0; index < node[DEFINE].size(); index++) {
            string variable = node[DEFINE][index].Scalar();
            bool writeToGraph = false;
            if (variable.back() == '*') {
                writeToGraph = true;
                variable.pop_back();
            }
            // insert new variable
            variables[variable] = { writeToGraph, boost::any() };
        }
        Code *code = createCalculateFromArray(node[CODE_BLOCK]);
        return code;
    };

    Code* createCalculateFromMap(const YAML::Node &node) {
        static auto getEdgeKind = [](string _edge) -> pair<string, EdgeKind> {
            vector<string> result;
            boost::split(result, _edge, boost::is_any_of("."));
            pair<string, EdgeKind> ret;
            for (size_t index = 0; index < edgesKind.size(); index++) {
                if (edgesKind[index] == result.back()) {
                    ret.first = result.size() == 2 ? result[0] : "";
                    ret.second = (asg::EdgeKind)index;
                }
            }
            // the validator ensures we never return an empty pair
            return ret;
        };
        static auto collectDefineLocalVariables = [](set<string> &defineLocalVariables,const YAML::Node &_node) {
            if (_node[DEFINE].IsDefined()) {
                for (size_t index = 0; index < _node[DEFINE].size(); index++) {
                    defineLocalVariables.insert(_node[DEFINE][index].Scalar());
                }
            }
        };
        static auto saveGlobalVariables = [](set<string> &defineLocalVariables, const string &loc = "") {
            auto _savedGlobalVariables = Globals::roleNames()[Globals::currentPatternDocument()][Globals::currentlyIn().back().second].second;
            if (!loc.empty()) Globals::roleNames()[Globals::currentPatternDocument()][Globals::currentlyIn().back().second].second[loc].second = boost::any();
            for (auto str : defineLocalVariables) Globals::roleNames()[Globals::currentPatternDocument()][Globals::currentlyIn().back().second].second[str].second = boost::any();
            return _savedGlobalVariables;
        };
        static auto resetGlobalVariables = [](const stringAnyLValue &_savedGlobalVariables) {
            Globals::roleNames()[Globals::currentPatternDocument()][Globals::currentlyIn().back().second].second = _savedGlobalVariables;
        };
        static auto createIf = [](const YAML::Node &_second, Condition *fC) {
            set<string> defineLocalVariables;
            collectDefineLocalVariables(defineLocalVariables, _second);
            const auto &_savedGlobalVariables = saveGlobalVariables(defineLocalVariables);
            CodeBlock *cB = dynamic_cast<CodeBlock*>(createCalculateFromArray(_second[CODE_BLOCK]));
            resetGlobalVariables(_savedGlobalVariables);

            IfCode *ifCode = new IfCode(fC, cB, defineLocalVariables);
            return ifCode;
        };
        static auto decideCondition = [](const YAML::Node &_second) {
            Condition *cond = nullptr;
            // _second == - condition :...
            if (_second.IsScalar()) {
                cond = std::move(createConditionFromScalar(_second, ""));
            }
            else {
                const YAML::Node &conditions = _second[0].IsScalar() ? _second :
                    (_second[0][ANY] || _second[0][ALL] ? _second : _second[0]);
                cond = std::move(createConditionFromMap(conditions, ""));
            }
            return cond;
        };

        const YAML::const_iterator &firstIt = node.begin();
        const string &type = firstIt->first.as<string>();
        const YAML::Node &_second = firstIt->second;
        
        validateMap(node, type, _second, Globals::roleNames()[Globals::currentPatternDocument()][Globals::currentlyIn().back().second].second);

        if (type == FOR) {
            Direction dir = _second[DIRECTION].IsDefined() == false ? Direction::forward : (_second[DIRECTION].Scalar() == FORWARD ? Direction::forward : Direction::reverse);
            const string &loc = _second[LOCAL].Scalar();
            const auto &edkPair = getEdgeKind(_second[EDGE].Scalar());
            const EdgeKind &edk = edkPair.second;
            const string &inNode = edkPair.first;
            set<string> defineLocalVariables;
            collectDefineLocalVariables(defineLocalVariables, _second);

            const auto &_savedGlobalVariables = saveGlobalVariables(defineLocalVariables, loc);
            EdgeForCode *efC = new EdgeForCode(dir, loc, defineLocalVariables, inNode, edk, dynamic_cast<CodeBlock*>(createCalculateFromArray(_second[CODE_BLOCK])));
            resetGlobalVariables(_savedGlobalVariables);

            return efC;
        }
        else if (type == IF) {
            // if its if-else
            if (_second.IsMap()) {
                const YAML::Node &_conditions = _second[CONDITIONS];
                Condition *fC = std::move(decideCondition(_conditions));
                IfCode *ifCode = createIf(_second, fC);

                if (_second[ELSE].IsDefined()) {
                    IfCode *elseCode = createIf(_second[ELSE], nullptr);
                    ifCode->setElseStatement(elseCode);
                }

                return ifCode;
            }
            // if its if, else if / else
            else if (_second.IsSequence() && _second.size() >= 1) {
                Condition *fC = std::move(decideCondition(_second[0][CONDITIONS]));
                IfCode *ifCode = createIf(_second[0], fC);
                bool isElse = false;

                for (size_t index = 1; index < _second.size(); index++) {
                    if (isElse) {
                        throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("All 'else if' statement must be before the 'else' statement!")));
                    }
                    Condition *fC = nullptr;
                    if (_second[index][CONDITIONS].IsDefined()) {
                        fC = std::move(decideCondition(_second[index][CONDITIONS]));
                    }
                    else {
                        isElse = true;
                        fC = new FormulaCondition({ {"","1" } }, Globals::equal, { {"","1" } });
                    }

                    IfCode *elseIf = createIf(_second[index], fC);

                    if (isElse) {
                        ifCode->setElseStatement(elseIf);
                    }
                    else {
                        ifCode->addElseIfStatemnt(elseIf);
                    }

                }

                return ifCode;
            }
        }

        // the validator ensures we never return a nullptr
        return nullptr;
    }

    Code* createCalculateFromArray(const YAML::Node &node) {
        validateSequence(node);

        CodeBlock *codeblock = new CodeBlock();
        for (size_t index = 0; index < node.size(); index++) {
            auto &_node = node[index];
            Code *_code;
            if (_node.IsScalar()) {
                _code = createCalculateFromScalar(_node);
            }
            else {
                _code = createCalculateFromMap(_node);
            }
            codeblock->addCodeToBlock(_code);
        }
        return codeblock;
    }

    Code* createCalculateFromScalar(const YAML::Node &node) {
        vector<string> result, form1, form2, form1Postfix, form2Postfix;
        string formula = node.Scalar();
        boost::erase_all(formula, " ");
        boost::split(result, formula, boost::is_any_of("="));

        // if its ++ or --
        if (result.size() == 1) {

            static auto splitString = [](string token, string formula, string &result) {
                vector<string> temp;
                boost::split(temp, formula, boost::is_any_of(token), boost::token_compress_on);
                if (temp.size() == 1) return false;
                result = temp[0].empty() ? temp[1] : temp[0];
                return true;
            };
            string variable = "";

            if (splitString("+", result[0], variable)) {
                formula = variable + "=" + variable + "+1";
            }
            else if (splitString("-", result[0], variable)) {
                formula = variable + "=" + variable + "-1";
            }

            result.clear();
            boost::split(result, formula, boost::is_any_of("="));
        }
        if (result.size() != 2) {
            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("Formula '" + formula + "' must be a value assignment, therefore it cannot have more than 1 assignment!")));
        }

        splitFormula(result[0], form1);
        splitFormula(result[1], form2);

        validateScalar(form1, form2, Globals::roleNames()[Globals::currentPatternDocument()][Globals::currentlyIn().back().second].second);

        RPN::formulaToPostfix(form1, form1Postfix);
        RPN::formulaToPostfix(form2, form2Postfix);

        vector<string> splitMetric;
        vector<pair<string, string>> right;
        const string &left = form1Postfix[0];

        for (const auto &str : form2Postfix) {
            splitMetric.clear();
            right.push_back({ "", str });
            if (!isalpha(str.at(0))) continue;
            boost::split(splitMetric, str, boost::is_any_of("."));
            if (splitMetric.size() == 2) {
                right.back() = { splitMetric[0], splitMetric[1] };
            }
        }

        return new FormulaCode(left, right);
    }

}}}}