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
        var assignmentPattern = factory.createAssignmentPatternWrapper(factory);
        globals.setPositionInfo(node, assignmentPattern);
        return assignmentPattern;
    } else {
        var assignmentPatternWrapper = globals.getWrapperOfNode(node);

        if (node.left != null) {
            var leftWrapper = globals.getWrapperOfNode(node.left);
            if (node.left.type !== "Literal") {
                var leftWrapperFunctionString = "setLeft" + node.left.type;
            } else {
                var leftWrapperFunctionString = "setLeft" + globals.getLiteralType(node.left) + node.left.type;
            }
            try {
                assignmentPatternWrapper[leftWrapperFunctionString](leftWrapper);
            } catch (e) {
                console.error("ASSIGNMENTPATTERN - Function not exist: assignmentPatternWrapper." + leftWrapperFunctionString + "! Reason of the error: " + e + "\n");
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
                assignmentPatternWrapper[rightWrapperFunctionString](rightWrapper);
            } catch (e) {
                console.error("ASSIGNMENTPATTERN - Function not exist: assignmentPatternWrapper." + rightWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

    }
}