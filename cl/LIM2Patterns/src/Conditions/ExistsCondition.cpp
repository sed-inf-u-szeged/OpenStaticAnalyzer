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

#include "../../inc/Conditions/ExistsCondition.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::lim::asg::base;
using namespace columbus::graph;
using columbus::lim::patterns::Direction;

namespace columbus {
    namespace lim {
        namespace patterns {
            namespace conditions {
                ExistsCondition::ExistsCondition(const EdgeKind _edgeKind, const NodeKind _nodeKind, Direction _edgeDirection, const vector<string> &_from)
                    : from(_from), edgeDirection(_edgeDirection), edgeKind(_edgeKind), nodeKind(_nodeKind) {};
                ExistsCondition::~ExistsCondition() {}

                bool ExistsCondition::testCondition(Graph &inGraph, const Base& limNode) {
                    const static auto &factory = limNode.getFactory();
                    const auto &currentPatternDoc = currentPatternDocument();
                    auto &roleNames = getRoleNames()[currentPatternDoc];
                    int nodeId;
                    // TODO:: move to globals?
                    // throws if 'from' is invalid
                    if (!this->from.empty()) {
                        auto *node = factory.getPointer(roleNames[from.front()].first);
                        nodeId = node->getId();
                        for (size_t index = 1; index < from.size(); index++) {
                            // must be int
                            nodeId = stoi(getValue(inGraph, from[index], *node));
                            node = factory.getPointer(nodeId);
                        }
                        if (!factory.getExist(nodeId)) {
                            throw columbus::Exception(COLUMBUS_LOCATION, "'" + from.front() + "' gives back an invalid node!");
                        }
                    }
                    auto &nodeToFindIn = this->from.empty() ? limNode : factory.getRef(nodeId);

                    const auto &travelTo = getTraversalEdges(nodeToFindIn, this->edgeKind, this->edgeDirection);

                    for (size_t index = 0; index < travelTo.size(); index++) {
                        if (recursiveNodeKindSearching(travelTo[index]->getNodeKind(), nodeKind)) {
                            return true;
                        }
                    }

                    return false;
                };
            }
        }
    }
}