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
        var ifStatement = factory.createIfStatementWrapper(factory);
        globals.setPositionInfo(node, ifStatement);
        return ifStatement;
    } else {
        var ifStatementWrapper = globals.getWrapperOfNode(node);


        if (node.consequent != null) {
            var consequentWrapper = globals.getWrapperOfNode(node.consequent);
            if (node.consequent.type !== "Literal") {
                var consequentWrapperFunctionString = "setConsequent" + node.consequent.type;
            } else {
                var consequentWrapperFunctionString = "setConsequent" + globals.getLiteralType(node.consequent) + node.consequent.type;
            }
            try {
                ifStatementWrapper[consequentWrapperFunctionString](consequentWrapper);
            } catch (e) {
                console.error("IFSTATEMENT - Function not exist: ifStatementWrapper." + consequentWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

        if (node.test != null) {
            var testWrapper = globals.getWrapperOfNode(node.test);
            if (node.test.type !== "Literal") {
                var testWrapperFunctionString = "setTest" + node.test.type;
            } else {
                var testWrapperFunctionString = "setTest" + globals.getLiteralType(node.test) + node.test.type;
            }
            try {
                ifStatementWrapper[testWrapperFunctionString](testWrapper);
            } catch (e) {
                console.error("IFSTATEMENT - Function not exist: ifStatementWrapper." + testWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

        if (node.alternate != null) {
            var alternateWrapper = globals.getWrapperOfNode(node.alternate);
            if (node.alternate.type !== "Literal") {
                var alternateWrapperFunctionString = "setAlternate" + node.alternate.type;
            } else {
                var alternateWrapperFunctionString = "setAlternate" + globals.getLiteralType(node.alternate) + node.alternate.type;
            }
            try {
                ifStatementWrapper[alternateWrapperFunctionString](alternateWrapper);
            } catch (e) {
                console.error("IFSTATEMENT - Function not exist: ifStatementWrapper." + alternateWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

    }
}