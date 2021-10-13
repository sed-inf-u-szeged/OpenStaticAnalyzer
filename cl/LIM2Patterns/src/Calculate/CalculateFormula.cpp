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

#include "../../inc/Calculate/CalculateFormula.h"
#include "../../inc/Conditions/Checker/PatternValidator.h"
#include "../../inc/Conditions/CreateCondition.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graph;
using namespace columbus::lim::asg::base;
using namespace columbus::lim::patterns::RPN;
using columbus::lim::patterns::conditions::FormulaCondition;
using columbus::lim::patterns::conditions::limToGraph;

namespace columbus { namespace lim { namespace patterns { namespace calculate {
    FormulaCode::FormulaCode(const string &_left, vector<pair<string, string>> &_right) : left(_left), right(_right), _currentType(boost::any()){};
    FormulaCode::FormulaCode(const string &_left, vector<pair<string, string>> &&_right) : left(_left), right(_right), _currentType(boost::any()) {};
    FormulaCode::~FormulaCode() {};
    set<string> FormulaCode::collectFiltersOnce() {
        set<string> filters;
        for (const auto &var : filterTypesAndValues)
        {
            filters.insert(var.first);
            for (const auto &str : var.second.second) {
                filters.insert(str);
            }
        }
        return filters;
    }
    bool FormulaCode::runCode(Graph &inGraph, const Base &base, stringAnyLValue &scopeVariables) {
        auto _rightCopy = right;
        vector<string> constantValues, _right;
        static set<string> filters = collectFiltersOnce();
        static const auto &metricIDsAndCalcFor = Globals::metricIDsAndCalcFor();
        const auto &currentPatternDoc = Globals::currentPatternDocument();
        auto &roleNames = Globals::roleNames()[currentPatternDoc];
        if(_currentType.empty())
            _currentType = !scopeVariables[left].second.empty() ? scopeVariables[left].second : boost::any();
        // getting the values of the right side
        
        for (const auto &_str : _rightCopy) {
            const string &nodeToFindIn = _str.first;
            const string &valueToFind = _str.second;
            _right.push_back(valueToFind);

            const Base &_nodeToFindIn = (nodeToFindIn.empty() || isdigit(nodeToFindIn.at(0))) ?
                base :
                (roleNames.find(nodeToFindIn) != roleNames.end() ?
                    base.getFactory().getRef(roleNames[nodeToFindIn].first) :
                    *(boost::any_cast<Base*>(scopeVariables[nodeToFindIn].second))
                    );

            if (filters.find(valueToFind) != filters.end()) {
                _right.back() = Globals::getValueFromLim(_nodeToFindIn, valueToFind);
                boost::any _value(FormulaCondition::castStringToBoostAny(_right.back()));
                if (_value.type() == typeid(string)) {
                    scopeVariables[left].second = boost::any(_value);
                    return true;
                }
            }
            else if (scopeVariables.find(valueToFind) != scopeVariables.end()) {
                // first time assigning a value, based on _currentTypes
                if (scopeVariables[valueToFind].second.empty())
                {
                    if (valueToFind != left) return false;
                    scopeVariables[valueToFind].second = FormulaCondition::defaultValueForBoostAny(_currentType);
                }
                else {
                    if (scopeVariables[valueToFind].second.type() == typeid(Base*)) {
                        scopeVariables[left].second = scopeVariables[valueToFind].second;
                        return true;
                    }
                }
                _right.back() = FormulaCondition::castBoostAny(scopeVariables[valueToFind].second);
            }
            else if (metricIDsAndCalcFor.find(valueToFind) != metricIDsAndCalcFor.end()) {
                _right.back() = Globals::getValueFromGraph(limToGraph(inGraph, _nodeToFindIn), valueToFind);
            }
        }

        // check type
        {
            if(_currentType.empty())
                _currentType = FormulaCondition::castStringToBoostAny(_right[0]);
            // checking the value types of the right side
            for (const auto &_str : _right) {
                if (!isdigit(_str[0]) && !isalpha(_str[0]) && _str[0] != '_' && _str[0] != '-') continue;
                constantValues.push_back(_str);

                const auto &currentAny = FormulaCondition::castStringToBoostAny(_str);
                if (currentAny.type() != _currentType.type() && (currentAny.type() == typeid(int) && _currentType.type() == typeid(double)) && (currentAny.type() == typeid(double) && _currentType.type() == typeid(int))) {
                    throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("Types are different in: '" + FormulaCondition::castBoostAny(_currentType) + "' type != '" + FormulaCondition::castBoostAny(currentAny) + "'")));
                }
            }
        }

        // calculating the value and appointing it to the variable
        if (!_currentType.empty() && (_currentType.type() == typeid(float) || _currentType.type() == typeid(double) || _currentType.type() == typeid(int))) {
            double value = RPN::postfixCalculate(_right);
            // not nice... really not nice
            scopeVariables[left].second = ceil(value) == floor(value) ? boost::any(int(value)) : value;
            _currentType = ceil(value) == floor(value) ? boost::any(int(value)) : value;
        }
        else {
            string value = "";
            for (auto str : constantValues) value += str;
            scopeVariables[left].second = boost::any(string(value));
        }

        return true;
    }

}}}}