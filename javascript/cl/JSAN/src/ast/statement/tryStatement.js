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
        var tryStatement = factory.createTryStatementWrapper(factory);
        globals.setPositionInfo(node, tryStatement);
        return tryStatement;
    } else {
        var tryStatementWrapper = globals.getWrapperOfNode(node);

        if (node.handler != null) {
            var handlerWrapper = globals.getWrapperOfNode(node.handler);
            if (node.handler.type !== "Literal") {
                var handlerWrapperFunctionString = "setHandler" + node.handler.type;
            } else {
                var handlerWrapperFunctionString = "setHandler" + globals.getLiteralType(node.handler) + node.handler.type;
            }
            try {
                tryStatementWrapper[handlerWrapperFunctionString](handlerWrapper);
            } catch (e) {
                console.error("TRYSTATEMENT - Function not exist: tryStatementWrapper." + handlerWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

        if (node.block != null) {
            var blockWrapper = globals.getWrapperOfNode(node.block);
            if (node.block.type !== "Literal") {
                var blockWrapperFunctionString = "setBlock" + node.block.type;
            } else {
                var blockWrapperFunctionString = "setBlock" + globals.getLiteralType(node.block) + node.block.type;
            }
            try {
                tryStatementWrapper[blockWrapperFunctionString](blockWrapper);
            } catch (e) {
                console.error("TRYSTATEMENT - Function not exist: tryStatementWrapper." + blockWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

        if (node.finalizer != null) {
            var finalizerWrapper = globals.getWrapperOfNode(node.finalizer);
            if (node.finalizer.type !== "Literal") {
                var finalizerWrapperFunctionString = "setFinalizer" + node.finalizer.type;
            } else {
                var finalizerWrapperFunctionString = "setFinalizer" + globals.getLiteralType(node.finalizer) + node.finalizer.type;
            }
            try {
                tryStatementWrapper[finalizerWrapperFunctionString](finalizerWrapper);
            } catch (e) {
                console.error("TRYSTATEMENT - Function not exist: tryStatementWrapper." + finalizerWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

    }
}