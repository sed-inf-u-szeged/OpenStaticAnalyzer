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
        var callExpression = factory.createCallExpressionWrapper(factory);
        globals.setPositionInfo(node, callExpression);
        return callExpression;
    } else {
        var callExpressionWrapper = globals.getWrapperOfNode(node);

        if (node.callee != null) {
            var calleeWrapper = globals.getWrapperOfNode(node.callee);
            if (node.callee.type !== "Literal") {
                var calleeWrapperFunctionString = "setCallee" + node.callee.type;
            } else {
                var calleeWrapperFunctionString = "setCallee" + globals.getLiteralType(node.callee) + node.callee.type;
            }
            try {
                callExpressionWrapper[calleeWrapperFunctionString](calleeWrapper);
            } catch (e) {
                console.error("CALLEXPRESSION - Function not exist: callExpressionWrapper." + calleeWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

        if (node.arguments != null) {
            for (var i = 0; i < node.arguments.length; i++) {
                if (node.arguments[i] != null) {
                    var argumentsWrapper = globals.getWrapperOfNode(node.arguments[i]);
                    if (node.arguments[i].type !== "Literal") {
                        var argumentsWrapperFunctionString = "addArguments" + node.arguments[i].type;
                    } else {
                        var argumentsWrapperFunctionString = "addArguments" + globals.getLiteralType(node.arguments[i]) + node.arguments[i].type;
                    }
                    try {
                        callExpressionWrapper[argumentsWrapperFunctionString](argumentsWrapper);
                    } catch (e) {
                        console.error("CALLEXPRESSION - Function not exist: callExpressionWrapper." + argumentsWrapperFunctionString + "! Reason of the error: " + e + "\n");
                    }
                }
            }
        }

    }
}