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
        var forStatement = factory.createForStatementWrapper(factory);
        globals.setPositionInfo(node, forStatement);
        return forStatement;
    } else {
        var forStatementWrapper = globals.getWrapperOfNode(node);

        if (node.init != null) {
            var initWrapper = globals.getWrapperOfNode(node.init);
            if (node.init.type !== "Literal") {
                var initWrapperFunctionString = "setInit" + node.init.type;
            } else {
                var initWrapperFunctionString = "setInit" + globals.getLiteralType(node.init) + node.init.type;
            }
            try {
                forStatementWrapper[initWrapperFunctionString](initWrapper);
            } catch (e) {
                console.error("FORSTATEMENT - Function not exist: forStatementWrapper." + initWrapperFunctionString + "! Reason of the error: " + e + "\n");
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
                forStatementWrapper[testWrapperFunctionString](testWrapper);
            } catch (e) {
                console.error("FORSTATEMENT - Function not exist: forStatementWrapper." + testWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

        if (node.update != null) {
            var updateWrapper = globals.getWrapperOfNode(node.update);
            if (node.update.type !== "Literal") {
                var updateWrapperFunctionString = "setUpdate" + node.update.type;
            } else {
                var updateWrapperFunctionString = "setUpdate" + globals.getLiteralType(node.update) + node.update.type;
            }
            try {
                forStatementWrapper[updateWrapperFunctionString](updateWrapper);
            } catch (e) {
                console.error("FORSTATEMENT - Function not exist: forStatementWrapper." + updateWrapperFunctionString + "! Reason of the error: " + e + "\n");
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
                forStatementWrapper[bodyWrapperFunctionString](bodyWrapper);
            } catch (e) {
                console.error("FORSTATEMENT - Function not exist: forStatementWrapper." + bodyWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }


    }
}