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
        const functionExpression = factory.createFunctionExpressionWrapper();
        globals.setPositionInfo(node, functionExpression);
        functionExpression.setGenerator(node.generator);
        functionExpression.setExpression(node.expression);
        functionExpression.setAsync(node.async);
        return functionExpression;
    } else {
        const functionExpressionWrapper = globals.getWrapperOfNode(node);

        if (node.params != null) {
            for (let i = 0; i < node.params.length; i++) {
                if (node.params[i] != null) {
                    globals.safeSet(functionExpressionWrapper, "addParams", node.params[i], "FUNCTIONEXPRESSION - Could not add params!");
                }
            }
        }

        if (node.body != null) {
            globals.safeSet(functionExpressionWrapper, "setBody", node.body, "FUNCTIONEXPRESSION - Could not set body!");
        }

        if (node.id != null) {
            globals.safeSet(functionExpressionWrapper, "setIdentifier", node.id, "FUNCTIONEXPRESSION - Could not set identifier!")
        }

    }
}
