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
        const forInStatement = factory.createForInStatementWrapper();
        globals.setPositionInfo(node, forInStatement);
        return forInStatement;
    } else {
        const forInStatementWrapper = globals.getWrapperOfNode(node);

        if (node.left != null) {
            globals.safeSet(forInStatementWrapper, "setLeft", node.left, "FORINSTATEMENT - Could not set left!");
        }

        if (node.right != null) {
            globals.safeSet(forInStatementWrapper, "setRight", node.right, "FORINSTATEMENT - Could not set right!");
        }

        if (node.body != null) {
            globals.safeSet(forInStatementWrapper, "setBody", node.body, "FORINSTATEMENT - Could not set body!");
        }
    }
}
