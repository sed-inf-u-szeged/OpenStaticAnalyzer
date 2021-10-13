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

#include "../../../inc/Calculate/Checker/PatternValidator.h"
#include "../../../inc/messages.h"

using namespace std;

namespace columbus { namespace lim { namespace patterns { namespace calculate { namespace validator {

    void validateNode(const YAML::Node &node) {
        if (!node.IsMap()) {
            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("'" + CALCULATE + "' must be a map type (key/value)!")));
        }
        if (!node[DEFINE].IsDefined() || !node[CODE_BLOCK]) {
            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("Node must contain both '" + DEFINE + "' and '" + CODE_BLOCK + "' !")));
        }
        if (!node[DEFINE].IsSequence()) {
            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("'" + DEFINE + "' Must be an array/sequence type!")));
        }
        if (!node[CODE_BLOCK].IsSequence()) {
            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("'" + CODE_BLOCK + "' Must be an array/sequence type!")));
        }
        if (node[CODE_BLOCK].size() == 0) {
            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("Define must contain atleast 1 global variable!")));
        }

        for (size_t index = 0; index < node[DEFINE].size(); index++) {
            if (!node[DEFINE][index].IsScalar()) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("Variable definition must be scalar (string) type!")));
            }
        }
    }

    void validateMap(const YAML::Node &node, const std::string &type, const YAML::Node &_second, stringAnyLValue &variables) {
        if (!node.IsMap()) {
            stringstream ss;
            ss << node;
            string outNode = ss.str();
            ss.clear();
            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)( outNode + "\n\nMust be a map(key/value) type")));
        }

        if (type == FOR) {
            if (_second[DIRECTION].IsDefined()) {
                if (_second[DIRECTION].IsScalar()) {
                    const string &_str = _second[DIRECTION].Scalar();
                    if (_str != FORWARD && _str != REVERSE) {
                        throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("The value of '" + DIRECTION + "' must be '" + FORWARD + "' or '" + REVERSE + "'!")));
                    }
                }
                else {
                    throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("'" + DIRECTION + "' must be a text value!")));
                }
            }

            if (!_second[EDGE].IsDefined()) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("'" + EDGE + "' must be defined!")));
            }
            else if (!_second[EDGE].IsScalar()) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("The value of '" + EDGE + "' must be a string/text!")));
            }
            else {
                vector<string> result;
                const string &_edge = _second[EDGE].Scalar();
                boost::split(result, _edge, boost::is_any_of("."));
                string nodeToFindInName = result[0];

                if (result.size() > 2) {
                    throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("'" + _edge + "' can only reference to a single variable")));
                }
                asg::EdgeKind edge = asg::edkLAST;
                for (size_t index = 0; index < edgesKind.size(); index++) {
                    if (edgesKind[index] == result.back()) {
                        edge = (asg::EdgeKind)index;
                    }
                }
                if (edge == asg::edkLAST) {
                    throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("Edge '" + _edge + "' is invalid")));
                }
                set<string> roleNames;
                for (auto &_pair : Globals::roleNames()[Globals::currentPatternDocument()]) {
                    roleNames.insert(_pair.first);
                }
                
                if (result.size() == 2 && variables.find(nodeToFindInName) == variables.end() && roleNames.find(nodeToFindInName) == roleNames.end()) {
                    throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("Role/Variable named '" + nodeToFindInName + "' is not defined in '" + EDGE + " : " + _edge + "'")));
                }
            }

            if (_second[DEFINE].IsDefined()) {
                if (!_second[DEFINE].IsSequence()) {
                    throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("'" + DEFINE + "' must be sequence/array type!")));
                }
                for (size_t index = 0; index < _second[DEFINE].size(); index++) {
                    if (!_second[DEFINE][index].IsScalar()) {
                        throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("Variable definition must be scalar (string/text) type!")));
                    }
                }
            }
        }
        else if (type == IF) {
            if ((!_second.IsMap() && !_second.IsSequence()) || (!_second.IsMap() && _second.IsSequence() && _second.size() <= 1)) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("Incorrect IF/ELSE/ELSEIF statement!")));
            }
        }
        else {
            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("'" + type + "' is incorrect/doesn't exist!")));
        }
    }

    void validateSequence(const YAML::Node &node) {
        if (!node.IsSequence()) {
            stringstream ss;
            ss << node;
            string errText = ss.str();
            ss.clear();
            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)( errText + "\n\nMust be array/sequence type")));
        }
    }

    void validateScalar(std::vector<std::string> splitLeft, std::vector<std::string> splitRight, stringAnyLValue &variables) {
        string left = "", formula = "";
        for (string &_str : splitLeft) {
            left += _str;
        }
        formula += left + "=";
        for (string &_str : splitRight) {
            formula += _str;
        }

        if (splitLeft.size() != 1) {
            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("The left side of the formula '" + left + "' must contain only one thing, and it must be a variable!")));
        }

        if (variables.find(splitLeft[0]) == variables.end()) {
            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN((string)("The left side of the assignment must be a variable defined by the user!\n" + formula)));
        }
    }

}}}}}