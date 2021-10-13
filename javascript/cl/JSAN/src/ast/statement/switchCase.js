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
        var switchCase = factory.createSwitchCaseWrapper();
        globals.setPositionInfo(node, switchCase);
        return switchCase;
    } else {
        var switchCaseWrapper = globals.getWrapperOfNode(node);

        if (node.test != null) {
            var testWrapper = globals.getWrapperOfNode(node.test);
            try {
                switchCaseWrapper.setTest(testWrapper);
            } catch (e) {
                console.error("SWITCHCASE - Could not set test! Reason of the error: " + e + "\n");
            }
        }

        if (node.consequent != null) {
            for (var i = 0; i < node.consequent.length; i++) {
                if (node.consequent[i] != null) {
                    var consequentWrapper = globals.getWrapperOfNode(node.consequent[i]);
                    try {
                        switchCaseWrapper.addConsequent(consequentWrapper);
                    } catch (e) {
                        console.error("SWITCHCASE - Could not add consequent! Reason of the error: " + e + "\n");
                    }
                }
            }
        }
    }
}