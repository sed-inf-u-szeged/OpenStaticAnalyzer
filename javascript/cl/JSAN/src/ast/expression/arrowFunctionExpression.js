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
        const arrowFunctionExpression = factory.createArrowFunctionExpressionWrapper();
        globals.setPositionInfo(node, arrowFunctionExpression);
        arrowFunctionExpression.setExpression(node.expression);
        arrowFunctionExpression.setGenerator(node.generator);
        arrowFunctionExpression.setAsync(node.async);
        return arrowFunctionExpression;
    } else {
        const arrowFunctionExpressionWrapper = globals.getWrapperOfNode(node);

        if (node.params != null) {
            for (let i = 0; i < node.params.length; i++) {
                if (node.params[i] != null) {
                    globals.safeSet(arrowFunctionExpressionWrapper, "addParams", node.params[i], "ARROWFUNCTIONEXPRESSION - Could not add param!");
                }
            }
        }

        if (node.body != null) {
            globals.safeSet(arrowFunctionExpressionWrapper, "setBody", node.body, "ARROWFUNCTIONEXPRESSION - Could not set body!");
        }

        if (node.id != null) {
            globals.safeSet(arrowFunctionExpressionWrapper, "setIdentifier", node.id, "ARROWFUNCTIONEXPRESSION - Could not set identifier!");
        }
    }
}
