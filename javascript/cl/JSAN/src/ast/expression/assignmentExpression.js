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
import * as conversions from '../conversions.js';

const factory = globals.getFactory();

export default function (node, parent, firstVisit) {
    if (firstVisit) {
        if (globals.getWrapperOfNode(node) !== undefined) {
            return;
        }
        const assignmentExpression = factory.createAssignmentExpressionWrapper();
        globals.setPositionInfo(node, assignmentExpression);
        assignmentExpression.setOperator(conversions.convertOperatorToString(node.operator));
        return assignmentExpression;
    } else {
        const assignmentExpressionWrapper = globals.getWrapperOfNode(node);

        if (node.left != null) {
            globals.safeSet(assignmentExpressionWrapper, "setLeft", node.left, "ASSIGNMENTEXPRESSION - Could not set left!");
        }

        if (node.right != null) {
            globals.safeSet(assignmentExpressionWrapper, "setRight", node.right, "ASSIGNMENTEXPRESSION - Could not set right!");
        }
    }
}
