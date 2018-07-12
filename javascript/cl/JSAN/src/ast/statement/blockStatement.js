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
        var blockStatement = factory.createBlockStatementWrapper(factory);
        globals.setPositionInfo(node, blockStatement);
        return blockStatement;
    } else {
        var blockStatementWrapper = globals.getWrapperOfNode(node);
        if (node.body != null) {
            for (var i = 0; i < node.body.length; i++) {
                if (node.body[i] != null) {
                    var bodyWrapper = globals.getWrapperOfNode(node.body[i]);
                    if (node.body[i].type !== "Literal") {
                        var bodyWrapperFunctionString = "addBody" + node.body[i].type;
                    } else {
                        var bodyWrapperFunctionString = "addBody" + globals.getLiteralType(node.body[i]) + node.body[i].type;
                    }
                    try {
                        blockStatementWrapper[bodyWrapperFunctionString](bodyWrapper);
                    } catch (e) {
                        console.error("BLOCKSTATEMENT - Function not exist: blockStatementWrapper." + bodyWrapperFunctionString + "! Reason of the error: " + e + "\n");
                    }
                }
            }
        }
    }
}