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
        var switchCase = factory.createSwitchCaseWrapper(factory);
        globals.setPositionInfo(node, switchCase);
        return switchCase;
    } else {
        var switchCaseWrapper = globals.getWrapperOfNode(node);

        if (node.test != null) {
            var testWrapper = globals.getWrapperOfNode(node.test);
            if (node.test.type !== "Literal") {
                var testWrapperFunctionString = "setTest" + node.test.type;
            } else {
                var testWrapperFunctionString = "setTest" + globals.getLiteralType(node.test) + node.test.type;
            }
            try {
                switchCaseWrapper[testWrapperFunctionString](testWrapper);
            } catch (e) {
                console.error("SWITCHCASE - Function not exist: switchCaseWrapper." + testWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

        if (node.consequent != null) {
            for (var i = 0; i < node.consequent.length; i++) {
                if (node.consequent[i] != null) {
                    var consequentWrapper = globals.getWrapperOfNode(node.consequent[i]);
                    if (node.consequent[i].type !== "Literal") {
                        var consequentWrapperFunctionString = "addConsequent" + node.consequent[i].type;
                    } else {
                        var consequentWrapperFunctionString = "addConsequent" + globals.getLiteralType(node.consequent[i]) + node.consequent[i].type;
                    }
                    try {
                        switchCaseWrapper[consequentWrapperFunctionString](consequentWrapper);
                    } catch (e) {
                        console.error("SWITCHCASE - Function not exist: switchCaseWrapper." + consequentWrapperFunctionString + "! Reason of the error: " + e + "\n");
                    }
                }
            }
        }
    }
}