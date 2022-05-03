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
        const forStatement = factory.createForStatementWrapper();
        globals.setPositionInfo(node, forStatement);
        return forStatement;
    } else {
        const forStatementWrapper = globals.getWrapperOfNode(node);

        if (node.init != null) {
            globals.safeSet(forStatementWrapper, "setInit", node.init, "FORSTATEMENT - Could not set init!");
        }

        if (node.test != null) {
            globals.safeSet(forStatementWrapper, "setTest", node.test, "FORSTATEMENT - Could not set test!");
        }

        if (node.update != null) {
            globals.safeSet(forStatementWrapper, "setUpdate", node.update, "FORSTATEMENT - Could not set update!");
        }

        if (node.body != null) {
            globals.safeSet(forStatementWrapper, "setBody", node.body, "FORSTATEMENT - Could not set body!");
        }
    }
}
