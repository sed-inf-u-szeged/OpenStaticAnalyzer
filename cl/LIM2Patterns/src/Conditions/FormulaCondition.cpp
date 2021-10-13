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

#include "../../inc/Conditions/FormulaCondition.h"
#include "../../inc/Conditions/CreateCondition.h"

using namespace std;
using namespace columbus::graph;
using namespace columbus::lim::asg;
using namespace columbus::lim::asg::base;
using boost::any;

namespace columbus { namespace lim { namespace patterns { namespace conditions {

    FormulaCondition::FormulaCondition(vector<FormulaPart*> &leftPostfix, ConditionTypes relationType, vector<FormulaPart*> &rightPostfix)
        : relation(relationType) {
        for (auto &_left : leftPostfix) {
            left.emplace_back(move(_left));
        }
        for (auto &_right : rightPostfix) {
            right.emplace_back(move(_right));
        }
    }
    FormulaCondition::~FormulaCondition() {}

    /*boost::any FormulaCondition::defaultValueForBoostAny(const boost::any &_anyValue)
    {
        if (_anyValue.type() == typeid(int)) {
            return boost::any(int(0));
        }
        else if (_anyValue.type() == typeid(double)) {
            return boost::any(double(0.0));
        }
        else if (_anyValue.type() == typeid(float)) {
            return boost::any(double(0.0));
        }
        else if (_anyValue.type() == typeid(NodeId)) {
            return boost::any(int(0));
        }
        else if (_anyValue.type() == typeid(long)) {
            return boost::any(int(0));
        }
        else if (_anyValue.type() == typeid(unsigned long)) {
            return boost::any(int(0));
        }
        else if (_anyValue.type() == typeid(long long)) {
            return boost::any(int(0));
        }
        else if (_anyValue.type() == typeid(unsigned long long)) {
            return boost::any(int(0));
        }
        else if (_anyValue.type() == typeid(const char*)) {
            return string("");
        }
        else if (_anyValue.type() == typeid(char*)) {
            return string("");
        }
        else if (_anyValue.type() == typeid(string)) {
            return string("");
        }
        else if (_anyValue.type() == typeid(bool)) {
            return string("");
        }
        else if (_anyValue.type() == typeid(uint32_t)) {
            return boost::any(int(0));
        }
        else if (_anyValue.type() == typeid(uint16_t)) {
            return boost::any(int(0));
        }
        return boost::any();
    }*/

    bool FormulaCondition::testCondition(Graph &inGraph, const Base& limNode) {
        //replace every variable to its double equivalent
        const auto &currentPatternDoc = currentPatternDocument();
        //const auto &depth = calculatedVariablesInNodesDepth();
        auto &roleNames = getRoleNames()[currentPatternDoc];
        //auto &cD = currentPatternDocument();
        // TODO:: Calculate remove
        //auto &currentVariables = calculatedVariables[cD][depth];
        //auto &currentVariables = !currentlyIn().empty() ? roleNames[currentlyIn().back().second].second : stringAnyLValue();
        
        // TODO:: Calculate remove
        // error occured while searching for the 'nodeToFindIn', it happens when a variable has no value
        // bool noError = true;

        auto getNodeToFindIn = [&](const Variable *var) -> Base*{
            // TODO:: Calculate remove
            /*if (!_str.first.empty()) {
                if (roleNames.find(_str.first) == roleNames.end()) {
                    if (currentVariables[_str.first].second.empty()) {
                        noError = false;
                        return limNode;
                    }
                }
            }*/
            Base *base = limNode.getFactory().getPointer(limNode.getId());
            vector<string> parents = var->parentRoles;
            parents.emplace_back(var->name);

            for (const auto &str : parents) {
                if (roleNames.find(str) != roleNames.end()) {
                    base = limNode.getFactory().getPointer(roleNames[str].first);
                }
                else if (str == limTypesString[classType] || str == limTypesString[type] || str == limTypesString[parent]) {
                    base = limNode.getFactory().getPointer(stoi(getValue(inGraph, str, *base)));
                }
            }

            return base;
        };
        
        auto getValuesFor = [&] (vector<std::unique_ptr<conditions::FormulaCondition::FormulaPart>> &formula){

            for (auto &part : formula) {
                if (part->type == FormulaPart::Number || part->type == FormulaPart::Operator) continue;

                auto var = dynamic_cast<Variable*>(part.get());
                const Base *nodeToFindIn = getNodeToFindIn(var);
                // TODO:: Calculate remove
                // if (!noError) return false;

                if (getRoleNames()[currentPatternDocument()].find(var->name) != getRoleNames()[currentPatternDocument()].end()) {
                    part->value = nodeToFindIn->getId();
                    continue;
                }
                string ret = getValue(inGraph, var->name, *nodeToFindIn);
                auto retAny = castStringToBoostAny(ret);
                part->value = retAny.type() == typeid(string) ? 
                    hash<string>{}(ret) : (retAny.type() == typeid(double) ?
                    boost::any_cast<double>(retAny) :
                    boost::any_cast<int>(retAny));
            }
        };

        auto isName = [&](vector<unique_ptr<FormulaPart>> &formula) -> bool{
            for (auto &part : formula) {
                if (part->type == part->Variable) {
                    if (dynamic_cast<Variable*>(part.get())->name == limTypesString[name]) {
                        return true;
                    }
                }
            }
            return false;
        };

        // special case for returnType/type on Attribute/Method/Parameter
        auto varLeft  = dynamic_cast<Variable*>(left[0] .get());
        auto varRight = dynamic_cast<Variable*>(right[0].get());
        bool leftType  = varLeft->type  == FormulaPart::Variable && (varLeft->name  == limTypesString[returnType] || varLeft->name  == limTypesString[type]);
        bool rightType = varRight->type == FormulaPart::Variable && (varRight->name == limTypesString[returnType] || varRight->name == limTypesString[type]);
        bool isSimilar = this->relation == similar || this->relation == equal || this->relation == notEqual ? true : false;
        bool leftName  = isName(left);
        bool rightName = isName(right);

        if (isSimilar && (leftType || rightType)){
            Base *nodeToFindIn, *nodeToFindInValue;
            if (leftType) {
                nodeToFindIn      = getNodeToFindIn(varLeft);
                nodeToFindInValue = getNodeToFindIn(varRight);
                // TODO:: Calculate remove
                // if (!noError) return false;
                //string _value = getSingleValue(rightCopy[0].second, nodeToFindInValue);
                //int value;
                //if (isdigit(_value.at(0)) || _value.at(0) == '-') value = stoi(_value);
                //else return false;
            }
            else if (rightType) {
                nodeToFindIn      = getNodeToFindIn(varRight);
                nodeToFindInValue = getNodeToFindIn(varLeft);
                // TODO:: Calculate remove
                // if (!noError) return false;
                // string _value = getSingleValue(leftCopy[0].second, nodeToFindInValue);
                //int value;
                //if (isdigit(_value.at(0)) || _value.at(0) == '-') value = stoi(_value);
                //else return false;
            }
            if (this->relation != similar) {
                varLeft->value = stoi(getValue(inGraph, "type", *nodeToFindIn));
                varRight->value = stoi(getValue(inGraph, "type", *nodeToFindInValue));
            }
            else if (this->relation == similar) return findTypeValue(*nodeToFindIn, *nodeToFindInValue, DEPTH_TO_SEARCH_IN);
        }
        // handling names are a bit tricky... might just remove the whole 'role.name == customString'
        else if (leftName || rightName) {
            if (leftName)getValuesFor(left);
            else {
                varLeft->value = hash<string>{}(varLeft->name);
            }
            if (rightName)getValuesFor(right);
            else {
                varRight->value = hash<string>{}(varRight->name);
            }
        }
        else{
            getValuesFor(left);
            getValuesFor(right);
        }

        double val1 = RPN::postfixCalculate(left);
        double val2 = RPN::postfixCalculate(right);

        switch (relation)
        {
        case less:
            return val1 < val2;
        case greater:
            return val1 > val2;
        case equal:
            return val1 == val2;
        case lessEqual:
            return val1 <= val2;
        case greaterEqual:
            return val1 >= val2;
        case notEqual:
            return val1 != val2;
        default:
            return false;
        }
        return false;
    };

}}}}
