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
        var tryStatement = factory.createTryStatementWrapper();
        globals.setPositionInfo(node, tryStatement);
        return tryStatement;
    } else {
        var tryStatementWrapper = globals.getWrapperOfNode(node);

        if (node.handler != null) {
            var handlerWrapper = globals.getWrapperOfNode(node.handler);
            try {
                tryStatementWrapper.setHandler(handlerWrapper);
            } catch (e) {
                console.error("TRYSTATEMENT - Could not set handler! Reason of the error: " + e + "\n");
            }
        }

        if (node.block != null) {
            var blockWrapper = globals.getWrapperOfNode(node.block);
            try {
                tryStatementWrapper.setBlock(blockWrapper);
            } catch (e) {
                console.error("TRYSTATEMENT - Could not set block! Reason of the error: " + e + "\n");
            }
        }

        if (node.finalizer != null) {
            var finalizerWrapper = globals.getWrapperOfNode(node.finalizer);
            try {
                tryStatementWrapper.setFinalizer(finalizerWrapper);
            } catch (e) {
                console.error("TRYSTATEMENT - Could not set finalizer! Reason of the error: " + e + "\n");
            }
        }

    }
}