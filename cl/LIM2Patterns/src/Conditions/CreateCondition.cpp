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

#include "../../inc/Conditions/CreateCondition.h"
#include "../../inc/Calculate/CreateCalculate.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <sstream>

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::lim::patterns::conditions::validator;
using namespace columbus::lim::patterns::calculate;

namespace columbus { namespace lim { namespace patterns { namespace conditions {

    // mixing python with any other language is not possible (yet)
    vector<YAML::Node> convertToYaml(const string & patternFileName) {
        vector<YAML::Node> patternNode;
        string extension = common::pathFindExtension(patternFileName);
        // yaml and yml
        if (extension == validExtensions[0] || extension == validExtensions[1]) {
            ifstream f;
            f.open(patternFileName);
            patternNode = YAML::LoadAll(f);
            f.close();
        }
        // json
        else if (extension == validExtensions[2]) {
            ifstream f;
            f.open(patternFileName);
            patternNode.push_back(YAML::Load(f));
            f.close();
        }
        // xml
        else if (extension == validExtensions[3]){
            boost::property_tree::ptree _Ptree;
            boost::property_tree::read_xml(patternFileName, _Ptree, boost::property_tree::xml_parser::trim_whitespace);
            stringstream ss;
            boost::property_tree::write_json(ss, _Ptree);
            patternNode.push_back(YAML::Load(ss));
            ss.clear();
        }
        else {
            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("'" + patternFileName + "' Predefined pattern can't be a python script!"));
        }
        if (patternNode.empty()) {
            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("'" + patternFileName + "' Pattern file was empty!"));
        }
        return patternNode;
    }


    NodeTypeCondition* createCondition(const YAML::Node &node, const string &patternsFolder) {
        NodeTypeCondition *cond = dynamic_cast<NodeTypeCondition*>(createConditionFromNodeType(node, patternsFolder));
        return cond;
    };

    Condition* createConditionFromNodeType(const YAML::Node &node, const string &patternsFolder) {
        
        validateNode(node);

        const string &roleName = node[ROLE].Scalar();
        string patternName = node[NAME].IsDefined() ? node[NAME].Scalar() : "";
        string category = node[CATEGORY].IsDefined() ? node[CATEGORY].Scalar() : "AntiPattern";
        string priority = node[PRIORITY].IsDefined() ? node[PRIORITY].Scalar() : "Minor";
        string displayName = node[DISPLAY_NAME].IsDefined() ? node[DISPLAY_NAME].Scalar() : patternName;
        string description = node[DESCRIPTION].IsDefined() ? node[DESCRIPTION].Scalar() : "";
        
        NodeKind typeName = getNodeKind(node[TYPE].Scalar());

        currentlyIn().push_back({ typeName, roleName });
        string pureRoleName = roleName; if (pureRoleName.back() == '*') pureRoleName.erase(pureRoleName.end()-1);

        auto &roleNames = getRoleNames()[currentPatternDocument()];
        roleNames.insert({ pureRoleName, {NO_VALUE, roleName.back() == '*'} });

        Condition *cond = nullptr;
        Condition *filterCondition = nullptr;
        // TODO:: Calculate remove
        /*Code *calculate = nullptr;

        if (node[CALCULATE].IsDefined()) {
            calculate = createCalculate(node[CALCULATE]);
        }
        else {
            if (currentlyIn().size() > 1) {
                const auto &_previousVariables = getRoleNames()[currentPatternDocument()][currentlyIn()[currentlyIn().size() - 2].second].second;
                getRoleNames()[currentPatternDocument()][currentlyIn().back().second].second = _previousVariables;
            }
        }*/

        // need this because of xml conversion
        if (node[CONDITIONS].IsDefined()) {
            if (node[CONDITIONS].IsScalar()) {
                cond = createConditionFromScalar(node[CONDITIONS], patternsFolder);
            }
            else if (node[CONDITIONS].IsMap()) {
                cond = createConditionFromMap(node[CONDITIONS], patternsFolder);
            }
            else if (node[CONDITIONS].IsSequence()) {
                cond = createConditionFromMap(node[CONDITIONS], patternsFolder);
            }
        }

        if (node[FILTERS].IsDefined()) {
            // single filter, need this because of xml conversion
            if (node[FILTERS].IsScalar()) {
                filterCondition = createConditionFromScalar(node[FILTERS], patternsFolder);
            }
            else if (node[FILTERS].IsMap()) {
                filterCondition = createConditionFromMap(node[FILTERS], patternsFolder);
            }
            else if (node[FILTERS].IsSequence()){
                filterCondition = createConditionFromMap(node[FILTERS], patternsFolder);
            }
        }
        
        // TODO:: Calculate remove
        NodeTypeCondition *nTC = new NodeTypeCondition(typeName, cond, filterCondition, /*calculate,*/ pureRoleName, patternName, displayName, category, description, priority);
        
        currentlyIn().pop_back();
        return nTC;
    }

    Condition* createConditionFromMap(const YAML::Node &node, const string &patternsFolder) {
        if (node.IsMap()) {
            const auto &firstIt = node.begin();
            const string &type = firstIt->first.as<string>();
            if (type == AND) {
                return new AndCondition(dynamic_cast<MultiCondition*>(createConditionFromArray(firstIt->second, patternsFolder)));
            }
            else if (type == OR) {
                return new OrCondition(dynamic_cast<MultiCondition*>(createConditionFromArray(firstIt->second, patternsFolder)));
            }
            else if (type == NAND) {
                return new NandCondition(dynamic_cast<MultiCondition*>(createConditionFromArray(firstIt->second, patternsFolder)));
            }
            else if (type == XOR) {
                return new XorCondition(dynamic_cast<MultiCondition*>(createConditionFromArray(firstIt->second, patternsFolder)));
            }
            else if (type == NOR) {
                return new NorCondition(dynamic_cast<MultiCondition*>(createConditionFromArray(firstIt->second, patternsFolder)));
            }
            else if (type == NOT) {
                // TODO this
                return new NotCondition(firstIt->second.IsScalar() ? createConditionFromScalar(firstIt->second, patternsFolder) : createConditionFromMap(firstIt->second, patternsFolder));
            }
            else if (type == ALL) {
                vector<string> _from;
                Direction _edgeDirection;
                asg::EdgeKind _edgeKind;
                validateMap(firstIt->second, _edgeKind, _edgeDirection);
                if (firstIt->second[FROM].IsDefined()) boost::split(_from, firstIt->second[FROM].Scalar(), boost::is_any_of("."));
                return new AllCondition(_edgeKind, _edgeDirection, _from, dynamic_cast<NodeTypeCondition*>(createConditionFromNodeType(firstIt->second, patternsFolder)));
            }
            else if (type == ANY) {
                vector<string> _from;
                Direction _edgeDirection;
                asg::EdgeKind _edgeKind;
                validateMap(firstIt->second, _edgeKind, _edgeDirection);
                if (firstIt->second[FROM].IsDefined()) boost::split(_from, firstIt->second[FROM].Scalar(), boost::is_any_of("."));
                return new AnyCondition(_edgeKind, _edgeDirection, _from, dynamic_cast<NodeTypeCondition*>(createConditionFromNodeType(firstIt->second, patternsFolder)));
            }
            else if (type == EXISTS) {
                vector<string> _from;
                Direction _edgeDirection;
                asg::EdgeKind _edgeKind;
                validateMap(firstIt->second, _edgeKind, _edgeDirection);
                if (firstIt->second[FROM].IsDefined()) boost::split(_from, firstIt->second[FROM].Scalar(), boost::is_any_of("."));
                unique_ptr<NodeTypeCondition> _cond(dynamic_cast<NodeTypeCondition*>(createConditionFromNodeType(firstIt->second, patternsFolder)));
                return new ExistsCondition(_edgeKind, _cond->getNodeKind(), _edgeDirection, _from);
            }
            // predefined patterns
            else {
                string fullPath = patternsFolder;
                boost::filesystem::path path(fullPath);
                // concatenating the directory with the file
                path /= firstIt->second.Scalar();
                if (!common::pathFileExists(path.string(), false)) {
                    throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("In '" + firstIt->first.Scalar() + " : " + firstIt->second.Scalar() + "' formula, " + path.string() + " file doesn't exist!"));
                }

                YAML::Node predefinedPatternNode = convertToYaml(path.string()).front();

                // predifened 'patternName' == predifened pattern name
                if (predefinedPatternNode[NAME].IsDefined() && predefinedPatternNode[NAME].Scalar() == type) {
                    auto currentlyInBefore = currentlyIn().back().first;
                    NodeTypeCondition* preDefined = createCondition(predefinedPatternNode, patternsFolder);
                    if (currentlyInBefore != preDefined->getNodeKind()) {
                        throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("Predefined pattern 'type' must be equal to the 'type' where it's called from!"));
                    }
                    return preDefined;
                }
                else {
                    throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("'name' must be defined, and it's value must be equal to the condition name"));
                }
            }
        }
        else {
            return new AndCondition(dynamic_cast<MultiCondition*>(createConditionFromArray(node, patternsFolder)));
        }
    }

    Condition* createConditionFromArray(const YAML::Node &node, const string &patternsFolder) {
        MultiCondition *mC = new MultiCondition();
        for (size_t index = 0; index < node.size(); index++) {
            Condition* cond;
            if (node[index].IsScalar()) {
                cond = createConditionFromScalar(node[index], patternsFolder);
            }
            else {
                cond = createConditionFromMap(node[index], patternsFolder);
            }
            mC->addCondition(cond);
        }
        return mC;
    }

    // TODO:: replace it with a math library?
    // separates a formula into a vector "(3)+5" -> ["(", "3", ")", "+", "5"]
    void splitFormula(const string &formula, vector<string> &out) {
        string temp = "";
        for (size_t index = 0; index < formula.length(); index++) {
            char c = formula[index];
            switch (c)
            {
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
            case ')':
            case '(':
                if (!temp.empty()) out.push_back(temp);
                temp = c;
                out.push_back(temp);
                temp = "";
                break;
            default:
                temp += c;
                break;
            }
        }
        if(!temp.empty())
            out.push_back(temp);
    }

    Condition* createConditionFromScalar(const YAML::Node &node, const string &patternsFolder) {
        size_t relTypeNumber = 0;
        vector<string> form1, form2,
                       results;
        string nformat = node.Scalar();
        string rel = "";
        ConditionTypes _relationType;

        boost::erase_all(nformat, " ");
        boost::split(results, nformat, boost::is_any_of("~=<>!"), boost::token_compress_on);

        if (results.size() != 2) {
            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("Formula '" + nformat + "' is invalid! It must contain only one left and right side, e.g. LOC == 2"));
        }

        bool res0 = false;
        if (results[0][0] == '-') { res0 = true; results[0] = "0" + results[0]; }
        if (results[1][0] == '-') results[1] = "0" + results[1];
        splitFormula(results[0], form1);
        splitFormula(results[1], form2);

        for (size_t index = results[0].size(); index < nformat.size(); index++) {
            char c = nformat.at(index - (res0 ? 1 : 0));
            if (c == '=' || c == '!' || c == '~' || c == '<' || c == '>') {
                rel += c;
            }
            else {
                break;
            }
        }

        for (relTypeNumber = 0; relTypeNumber < relationTypes.size(); relTypeNumber++) {
            if (rel == relationTypes[relTypeNumber]) {
                break;
            };
        }
        _relationType = (ConditionTypes)relTypeNumber;

        validateScalar(nformat, form1, form2, _relationType, rel);

        vector<conditions::FormulaCondition::FormulaPart*> left, right;
        RPN::formulaToPostfix(form1, left);
        RPN::formulaToPostfix(form2, right);

        FormulaCondition *fC = new FormulaCondition(left, _relationType, right);
        return fC;
    }
}

// TODO:: replace it with a math library?
namespace RPN {
    void formulaToPostfix(vector<string> &formula, vector<conditions::FormulaCondition::FormulaPart*> &result) {
        stack <string> _stack;
        formula.push_back(")");
        _stack.push("(");
        bool variableIsNegative = false;
        for (size_t i = 0; i < formula.size(); i++) {
            string str = formula[i];
            if (str == "(") {
                _stack.push(str);
            }
            else if (str == "+" || str == "-") {
                if (str == "-" && ((i == 0) || (i != 0 && (formula[i - 1] == "+" || formula[i - 1] == "(" || formula[i - 1] == "*" || formula[i - 1] == "/" || formula[i - 1] == "^")))) {
                    variableIsNegative = true;
                    continue;
                }
                if (i != 0) {
                    for (string s = _stack.top(); s == "+" || s == "-" || s == "*" || s == "/" || s == "^"; _stack.pop(), s = _stack.top()) {
                        auto op = new conditions::FormulaCondition::Operator();
                        op->sign = s;
                        result.emplace_back(op);
                    }
                    _stack.push(str);
                    
                }
            }
            else if (str == "*" || str == "/" || str == "^") {
                for (string s = _stack.top(); s == "*" || s == "/" || s == "^"; _stack.pop(), s = _stack.top()) {
                    auto op = new conditions::FormulaCondition::Operator();
                    op->sign = s;
                    result.emplace_back(op);
                }
                _stack.push(str);
            }
            else if (str == ")") {
                for (string s = _stack.top(); s != "("; _stack.pop(), s = _stack.top()) {
                    auto op = new conditions::FormulaCondition::Operator();
                    op->sign = s;
                    result.emplace_back(op);
                }
                _stack.pop();

            }
            else {
                if (isdigit(str[0])) {
                    auto var = new conditions::FormulaCondition::Variable(conditions::FormulaCondition::FormulaPart::Number);
                    var->value = stoi(str);
                    result.push_back(var);
                }
                else {
                    auto var = new conditions::FormulaCondition::Variable(conditions::FormulaCondition::FormulaPart::Variable);
                    
                    for (size_t offC = 0, findC = str.find_first_of('.', offC); findC != string::npos; findC = str.find_first_of('.', offC)) {
                        var->parentRoles.emplace_back(str.substr(offC, findC - offC));
                        offC = findC + 1;
                    }
                    size_t findC = str.find_last_of('.');
                    if (findC != string::npos) {
                        str = str.substr(findC + 1, str.length() - findC);
                    }
                    var->name = str;

                    result.push_back(var);
                }
                if (variableIsNegative) {
                    result.back()->isNegative = true;
                    variableIsNegative = false;
                }
            }
        }

    };

    double postfixCalculate(vector<unique_ptr<conditions::FormulaCondition::FormulaPart>> &formula) {
        stack<long double> _stack;
        for (auto &part : formula) {
            if (part->type == conditions::FormulaCondition::FormulaPart::Variable || part->type == conditions::FormulaCondition::FormulaPart::Number) {
                long double val = part->value;
                if (part->isNegative) val = -val;
                _stack.push(val);
            }
            else {
                auto op = dynamic_cast<conditions::FormulaCondition::Operator*>(part.get());
                double val1 = _stack.top();
                _stack.pop();
                double val2 = _stack.top();
                _stack.pop();

                if (op->sign == "+") _stack.push(val2 + val1);
                if (op->sign == "-") _stack.push(val2 - val1);
                if (op->sign == "*") _stack.push(val2 * val1);
                if (op->sign == "/") _stack.push(val2 / val1);
                if (op->sign == "^") _stack.push(pow(val2, val1));
            }
        }
        return _stack.top();
    };
}}}}

