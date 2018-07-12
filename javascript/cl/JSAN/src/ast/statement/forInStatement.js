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
        var forInStatement = factory.createForInStatementWrapper(factory);
        globals.setPositionInfo(node, forInStatement);
        return forInStatement;
    } else {
        var forInStatementWrapper = globals.getWrapperOfNode(node);

        if (node.left != null) {
            var leftWrapper = globals.getWrapperOfNode(node.left);
            if (node.left.type !== "Literal") {
                var leftWrapperFunctionString = "setLeft" + node.left.type;
            } else {
                var leftWrapperFunctionString = "setLeft" + globals.getLiteralType(node.left) + node.left.type;
            }
            try {
                forInStatementWrapper[leftWrapperFunctionString](leftWrapper);
            } catch (e) {
                console.error("FORINSTATEMENT - Function not exist: forInStatementWrapper." + leftWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

        if (node.right != null) {
            var rightWrapper = globals.getWrapperOfNode(node.right);
            if (node.right.type !== "Literal") {
                var rightWrapperFunctionString = "setRight" + node.right.type;
            } else {
                var rightWrapperFunctionString = "setRight" + globals.getLiteralType(node.right) + node.right.type;
            }
            try {
                forInStatementWrapper[rightWrapperFunctionString](rightWrapper);
            } catch (e) {
                console.error("FORINSTATEMENT - Function not exist: forInStatementWrapper." + rightWrapperFunctionString + "! Reason of the error: " + e + "\n");
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
                forInStatementWrapper[bodyWrapperFunctionString](bodyWrapper);
            } catch (e) {
                console.error("FORINSTATEMENT - Function not exist: forInStatementWrapper." + bodyWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

    }
}