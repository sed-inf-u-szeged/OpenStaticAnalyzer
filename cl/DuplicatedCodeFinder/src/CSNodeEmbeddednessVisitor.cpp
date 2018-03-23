/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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

#ifdef SCHEMA_CSHARP

#include "../inc/common.h"
#include "../inc/Visitors/CSNodeEmbeddednessVisitor.h"
#include "../inc/dcm.h"

using namespace columbus;

void NODE_EMBEDDEDNESS_VISITOR::putNode(const LANGUAGE_NAMESPACE::base::Positioned& n1, const LANGUAGE_NAMESPACE::base::Positioned& n2, bool unique) {
    
    if (dcf.isItFilteredInLim(limComponenetId, n2))
        return;

    NodeId limNode = dcf.getLimNodeIdByNode(limComponenetId, n1);
    if (limNode) {
        aliasMap[limNode] = NodeGlobalId(limComponenetId, n1.getId());
    }

    if (!aliasMode) {
        alias = NodeGlobalId(limComponenetId, n1.getId());
    }

    const std::string& baseNodeFile = n1.getPosition().getFileName();
    const std::string& endNodeFile = n2.getPosition().getFileName();
    ConectedEdgesMap::iterator itFoundAssociation = conectedEdgesMap.find(NodeGlobalId(limComponenetId, n1.getId()));

    int distance = calculateNDC(baseNodeFile, endNodeFile);
    if (itFoundAssociation != conectedEdgesMap.end()) {
        bool found = false;
        if (unique) {
            std::list<NodeWithWeight >& listRef = conectedEdgesMap[NodeGlobalId(limComponenetId, n1.getId())];
            for (std::list< NodeWithWeight >::iterator it = listRef.begin(); it != listRef.end(); ++it) {
                if (it->nodeUniqueId == NodeGlobalId(limComponenetId, n2.getId())) {
                    found = true;
                }
            }
        }
        if (!found) {
            conectedEdgesMap[alias].push_front(
                NodeWithWeight(NodeGlobalId(limComponenetId, n2.getId()), NdcWeight(distance, !unique))
            );
        }
    }
    else {
        std::list< NodeWithWeight > newList;
        newList.push_front(NodeWithWeight(NodeGlobalId(limComponenetId, n2.getId()), NdcWeight(distance, !unique)));
        conectedEdgesMap.insert(std::make_pair(alias, newList));
    }
}



#endif
