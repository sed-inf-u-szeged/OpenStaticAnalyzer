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
        var functionExpression = factory.createFunctionExpressionWrapper(factory);
        globals.setPositionInfo(node, functionExpression);
        functionExpression.setGenerator(node.generator);
        functionExpression.setExpression(node.expression);
        functionExpression.setAsync(node.async);
        return functionExpression;
    } else {
        var functionExpressionWrapper = globals.getWrapperOfNode(node);

        if (node.params != null) {
            for (var i = 0; i < node.params.length; i++) {
                if (node.params[i] != null) {
                    var paramsWrapper = globals.getWrapperOfNode(node.params[i]);
                    if (node.params[i].type !== "Literal") {
                        var paramsWrapperFunctionString = "addParams" + node.params[i].type;
                    } else {
                        var paramsWrapperFunctionString = "addParams" + globals.getLiteralType(node.params[i]) + node.params[i].type;
                    }
                    try {
                        functionExpressionWrapper[paramsWrapperFunctionString](paramsWrapper);
                    } catch (e) {
                        console.error("FUNCTIONEXPRESSION - Function not exist: functionExpressionWrapper." + paramsWrapperFunctionString + "! Reason of the error: " + e + "\n");
                    }
                }
            }
        }

        if (node.body != null) {
            var bodyWrapper = globals.getWrapperOfNode(node.body);
            if (node.body.type !== "Literal") {
                var bodyWrapperFunctionString = "setBody" + node.body.type;
            } else {
                var bodyWrapperFunctionString = "setBody" + globals.getLiteralType(node.body) + node.body.type;
            }
            try {
                functionExpressionWrapper[bodyWrapperFunctionString](bodyWrapper);
            } catch (e) {
                console.error("FUNCTIONEXPRESSION - Function not exist: functionExpressionWrapper." + bodyWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

        if (node.id != null) {
            var identifierWrapper = globals.getWrapperOfNode(node.id);
            if (node.id.type !== "Literal") {
                var identifierWrapperFunctionString = "setIdentifier" + node.id.type;
            } else {
                var identifierWrapperFunctionString = "setIdentifier" + globals.getLiteralType(node.id) + node.id.type;
            }
            try {
                functionExpressionWrapper[identifierWrapperFunctionString](identifierWrapper);
            } catch (e) {
                console.error("FUNCTIONEXPRESSION - Function not exist: functionExpressionWrapper." + identifierWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

    }
}