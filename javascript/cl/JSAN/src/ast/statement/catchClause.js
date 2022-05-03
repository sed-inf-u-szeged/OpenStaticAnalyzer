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

import * as globals from '../../globals.js';

const factory = globals.getFactory();

export default function (node, parent, firstVisit) {
    if (firstVisit) {
        if (globals.getWrapperOfNode(node) !== undefined) {
            return;
        }
        const catchClause = factory.createCatchClauseWrapper();
        globals.setPositionInfo(node, catchClause);
        return catchClause;
    } else {
        const catchClauseWrapper = globals.getWrapperOfNode(node);

        if (node.body != null) {
            globals.safeSet(catchClauseWrapper, "setBody", node.body, "CATCHCLAUSE - Could not set body!");
        }

        if (node.param != null) {
            globals.safeSet(catchClauseWrapper, "setParam", node.param, "CATCHCLAUSE - Could not set param!");
        }
    }
}
