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
        var forStatement = factory.createForStatementWrapper();
        globals.setPositionInfo(node, forStatement);
        return forStatement;
    } else {
        var forStatementWrapper = globals.getWrapperOfNode(node);

        if (node.init != null) {
            var initWrapper = globals.getWrapperOfNode(node.init);
            try {
                forStatementWrapper.setInit(initWrapper);
            } catch (e) {
                console.error("FORSTATEMENT - Could not set init! Reason of the error: " + e + "\n");
            }
        }

        if (node.test != null) {
            var testWrapper = globals.getWrapperOfNode(node.test);
            try {
                forStatementWrapper.setTest(testWrapper);
            } catch (e) {
                console.error("FORSTATEMENT - Could not set test! Reason of the error: " + e + "\n");
            }
        }

        if (node.update != null) {
            var updateWrapper = globals.getWrapperOfNode(node.update);
            try {
                forStatementWrapper.setUpdate(updateWrapper);
            } catch (e) {
                console.error("FORSTATEMENT - Could not set update! Reason of the error: " + e + "\n");
            }
        }

        if (node.body != null) {
            var bodyWrapper = globals.getWrapperOfNode(node.body);
            try {
                forStatementWrapper.setBody(bodyWrapper);
            } catch (e) {
                console.error("FORSTATEMENT - Could not set body! Reason of the error: " + e + "\n");
            }
        }


    }
}