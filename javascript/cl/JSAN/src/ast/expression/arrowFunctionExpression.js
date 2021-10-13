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

var globals = require('../../globals');
var factory = globals.getFactory();

module.exports = function (node, parent, firstVisit) {
    if (firstVisit) {
        if (globals.getWrapperOfNode(node) !== undefined) {
            return;
        }
        var arrowFunctionExpression = factory.createArrowFunctionExpressionWrapper(factory);
        globals.setPositionInfo(node, arrowFunctionExpression);
        arrowFunctionExpression.setExpression(node.expression);
        arrowFunctionExpression.setGenerator(node.generator);
        arrowFunctionExpression.setAsync(node.async);
        return arrowFunctionExpression;
    } else {
        var arrowFunctionExpressionWrapper = globals.getWrapperOfNode(node);

        if (node.params != null) {
            for (var i = 0; i < node.params.length; i++) {
                if (node.params[i] != null) {
                    var paramsWrapper = globals.getWrapperOfNode(node.params[i]);
                    try {
                        arrowFunctionExpressionWrapper.addParams(paramsWrapper);
                    } catch (e) {
                        console.error("ARROWFUNCTIONEXPRESSION - Could not add param! Reason of the error: " + e + "\n");
                    }
                }
            }
        }

        if (node.body != null) {
            var bodyWrapper = globals.getWrapperOfNode(node.body);
            try {
                arrowFunctionExpressionWrapper.setBody(bodyWrapper);
            } catch (e) {
                console.error("ARROWFUNCTIONEXPRESSION - Could not set body! Reason of the error: " + e + "\n");
            }
        }

        if (node.id != null) {
            var identifierWrapper = globals.getWrapperOfNode(node.id);
            try {
                arrowFunctionExpressionWrapper.setIdentifier(identifierWrapper);
            } catch (e) {
                console.error("ARROWFUNCTIONEXPRESSION - Could not set identifier! Reason of the error: " + e + "\n");
            }
        }

    }
}