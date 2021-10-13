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

#include "../../../inc/Conditions/Checker/PatternValidator.h"

using namespace std;
using namespace columbus;
using namespace columbus::lim::asg;
using namespace columbus::lim::patterns::conditions;

namespace columbus { namespace lim { namespace patterns { namespace conditions { 
    namespace validator {

        void validateScalar(const string &formula, vector<string> &formulaLeft, vector<string> &formulaRight, const ConditionTypes &relType, const string &relation) {
            
            if (relType == ConditionTypes::LAST) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("Relation '" + relation + "' type is incorrect in '" + formula + "'"));
            }

            if (formulaLeft.size() == 0 || formulaRight.size() == 0) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("'" + formula + "' must containt 1 metric name / value on each side of the formula"));
            }
            const static set<string> filters = []() {
                set<string> temp;
                for (const auto &_filter : filterTypesAndValues) {
                    temp.insert(limTypesString[_filter.first]);
                }
                return temp;
            }();
            const static set<string> filtersAndValues = []() {
                set<string> temp;
                for (const auto &_filter : filterTypesAndValues) {
                    temp.insert(limTypesString[_filter.first]);
                    for (const auto &_value : _filter.second.second) {
                        temp.insert(_value);
                    }
                }
                return temp;
            }();
            const static set<string> nodeLimValues = []() {
                set<string> temp;
                temp.insert(limTypesString[type]); // type
                temp.insert(limTypesString[classType]); // class
                temp.insert(limTypesString[parent]); // parent
                return temp;
            }();
            const auto &roleNames = getRoleNames()[currentPatternDocument()];
            const auto &metricIDs = getMetricIDsAndCalcFor();

            auto checkSide = [&roleNames, &formula, &metricIDs](const vector<string> &str) {
                bool canBe = false;
                for (auto _str : str) {
                    // ignore operations and names that starts with _
                    if (!isalpha(_str[0]) && _str[0] != '_') continue;
                    vector<string> refs;
                    boost::split(refs, _str, boost::is_any_of("."));

                    for (auto temp : refs) {
                        if (temp.empty()) {
                            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("In '" + formula + "' is invalid! Refernce must point to something!"));
                        }
                    }

                    if (refs.size() > 1 && nodeLimValues.find(refs[0]) == nodeLimValues.end() && roleNames.find(refs[0]) == roleNames.end()) {
                        throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("In '" + formula + "', '" + refs[0] + "' is invalid!"));
                    }
                    for (size_t index = 1; index < refs.size() - 1; index++) {
                        if (nodeLimValues.find(refs[index]) == nodeLimValues.end() || isdigit(refs[index][0])) {
                            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("In '" + formula + "', '" + refs[index] + "' is invalid!"));
                        }
                    }
                    if (filters.find(refs.back()) == filters.end() && (!metricIDs.empty() && metricIDs.find(refs.back()) == metricIDs.end())) {
                        if (refs.size() != 1)
                            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("In '" + formula + "', '" + refs.back() + "' is invalid!"));
                    }

                    if (refs.back() == limTypesString[type] || refs.back() == limTypesString[returnType] || refs.back() == limTypesString[name]) {
                        canBe = true;
                    }
                }
                return canBe;
            };

            bool canLeftBeSimilar  = checkSide(formulaLeft);
            bool canRightBeSimilar = checkSide(formulaRight);

            if (relType == similar && !canLeftBeSimilar && !canRightBeSimilar) throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("In '" + formula + "' LIM '~=' condition is invalid! Only '" + limTypesString[type] + "','" + limTypesString[returnType] + "' and '" + limTypesString[name] + "' can have the '~=' condition!"));

            if (formulaLeft.size() == 1 && formulaRight.size() == 1) {
                vector<string> splitLeft, splitRight;
                boost::split(splitLeft, formulaLeft[0], boost::is_any_of("."));
                boost::split(splitRight, formulaRight[0], boost::is_any_of("."));
                string left = splitLeft.back(), right = splitRight.back();
                if (filters.find(left) != filters.end() || filters.find(right) != filters.end()) {
                    if (filters.find(left) != filters.end()) {
                        auto acceptableValues = [&left] {
                            set<string> types;
                            for (const auto &_filters : filterTypesAndValues) {
                                if (limTypesString[_filters.first] == left) {
                                    for (auto _types : _filters.second.second) {
                                        types.insert(_types);
                                    }
                                }
                            }
                            return types;
                        }();
                        if (!acceptableValues.empty() && acceptableValues.find(right) == acceptableValues.end() && left != right) {
                            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("In '" + formula + "' is invalid! '" + left + "' cannot be compared to '" + right + "'"));
                        }
                    }
                    else {
                        auto acceptableValues = [&right] {
                            set<string> types;
                            for (const auto &_filters : filterTypesAndValues) {
                                if (limTypesString[_filters.first] == right) {
                                    for (auto _types : _filters.second.second) {
                                        types.insert(_types);
                                    }
                                }
                            }
                            return types;
                        }();
                        if (!acceptableValues.empty() && acceptableValues.find(left) == acceptableValues.end() && left != right) {
                            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("In '" + formula + "' is invalid! '" + left + "' cannot be compared to '" + right + "'"));
                        }
                    }
                        

                }
            }

        }

        void validateMap(const YAML::Node &node, EdgeKind &edgeKind, Direction &direction) {

            static auto getDirection = [](const YAML::Node &_node) {
                return _node[DIRECTION].IsDefined() == false ? Direction::forward : (_node[DIRECTION].IsScalar() && _node[DIRECTION].Scalar() == FORWARD ? Direction::forward : (_node[DIRECTION].IsScalar() && _node[DIRECTION].Scalar() == REVERSE ? Direction::reverse : Direction::dirLAST));
            };
            direction = getDirection(node);

            if (!node[EDGE].IsDefined()) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("Edge doesnt exist!"));
            }
            if (direction == Direction::dirLAST) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("The value of '" + DIRECTION + "' must be '" + FORWARD + "' or '" + REVERSE + "'!"));
            }

            NodeKind ndk = ndkLAST;

            if (node[FROM].IsDefined()) {
                vector<string> res;
                const string &from = node[FROM].Scalar();
                boost::split(res, from, boost::is_any_of("."));
                // checking node[FROM] if its valid or not
                if (res.back() == "type") ndk = ndkType;
                else if (res.back() == "class") ndk = ndkClass;
                else if (res.back() == "parent") ndk = ndkBase;
                else {
                    for (auto &_role : currentlyIn()) {
                        if (_role.second == res.back()) {
                            ndk = _role.first;
                            break;
                        }
                    }
                }
                if (ndk == ndkLAST)
                    throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("The value of '" + FROM +"' must be an existing '" + ROLE + "' name!"));
            }
            else {
                ndk = currentlyIn().back().first;
            }
            
            edgeKind = getEdgeKind(node[EDGE].Scalar());

            if (direction == Direction::forward && validateEdge(edgeKind,ndk) == false) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("Edge: '" + Common::toString(edgeKind) + "' is invalid in '" + Common::toString(ndk) + "'"));
            }
        };

        void validateNode(const YAML::Node &node) {
            static set<string> possibleKeyWords = [](){
                set<string> temp;
                for (auto it = filterTypesAndValues[11].second.second.begin(); it != filterTypesAndValues[11].second.second.end(); it++) {
                    temp.insert(*it);
                }
                return temp;
            }();

            if (!node[TYPE].IsDefined()) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("'" + TYPE + "' must be defined!"));
            }

            if (!node[TYPE].IsScalar()) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("The value of '" + TYPE + "' must be a text/string!"));
            }

            if (possibleKeyWords.find(node[TYPE].Scalar()) == possibleKeyWords.end()) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("Type '" + node[TYPE].Scalar() + "' in the given language!"));
            }

            if (node[CONDITIONS].IsDefined() && node[CONDITIONS].IsNull()) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("A defined'" + CONDITIONS + "' must not be empty!"));
            }

            if (node[FILTERS].IsDefined() && node[FILTERS].IsNull()) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("A defined'" + FILTERS + "' must not be empty!"));
            }

            if (!node[ROLE].IsDefined()) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("'" + ROLE + "' must be defined!"));
            }

            if (!node[ROLE].IsScalar()) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("The value of '" + ROLE + "' must be a text/string!"));
            }

            /*if (!node[CONDITIONS].IsDefined()) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("Conditions must be defined!"));
            }*/

            if (!node[NAME].IsDefined() && !node[EDGE].IsDefined()) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("Node type must contain either 'edge' or 'name'"));
            }

            if (node[NAME].IsDefined() && !node[NAME].IsScalar()) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("The value of '" + NAME + "' must be a text/string!"));
            }

            if (node[EDGE].IsDefined() && !node[EDGE].IsScalar()) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("The value of '" + EDGE + "' must be a text/string!"));
            }

            if (node[PRIORITY].IsDefined() && !node[PRIORITY].IsScalar()) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("The value of '" + PRIORITY + "' must be a text/string!"));
            }

            if (node[PRIORITY].IsDefined() && priorityValues.find(node[PRIORITY].Scalar()) == priorityValues.end()) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("Priority value '" + node[PRIORITY].Scalar() + "' is invalid!"));
            }

            if (node[FROM].IsDefined() && !node[FROM].IsScalar()) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("The value of '" + FROM + "' must be a text/string!"));
            }
            else if (node[FROM].IsDefined() && node[FROM].IsScalar()) {
                const string &_from = node[FROM].Scalar();
                vector<string> result;
                boost::split(result, _from, boost::is_any_of("."));
                auto &roleNames = getRoleNames()[currentPatternDocument()];
                if (roleNames.find(result.front()) == roleNames.end()) {
                    throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("The value of '" + FROM + "' must be a '" + ROLE + "' name!"));
                }

                string _type = limTypesString[type];
                string _class = limTypesString[classType];
                for (size_t index = 1; index < result.size(); index++) {
                    if (result[index] != _type && result[index] != _class) {
                        throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("The value after '" + result[0] + "' must be '" + _type + "' or '" + _class + "'!"));
                    }
                }
            }

            const string &roleName = node[ROLE].Scalar();
            auto &roleNames = getRoleNames()[currentPatternDocument()];
            if (roleNames.find(roleName) != roleNames.end()) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("Role must be unique!"));
            }
        }
    }
}}}}
