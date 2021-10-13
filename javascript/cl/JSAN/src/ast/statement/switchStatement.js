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
        var switchStatement = factory.createSwitchStatementWrapper();
        globals.setPositionInfo(node, switchStatement);
        return switchStatement;
    } else {
        var switchStatementWrapper = globals.getWrapperOfNode(node);
        if (node.cases != null) {
            for (var i = 0; i < node.cases.length; i++) {
                if (node.cases[i] != null) {
                    var casesWrapper = globals.getWrapperOfNode(node.cases[i]);
                    try {
                        switchStatementWrapper.addCases(casesWrapper);
                    } catch (e) {
                        console.error("SWITCHSTATEMENT - Could not add case! Reason of the error: " + e + "\n");
                    }
                }
            }
        }
        if (node.discriminant != null) {
            var discriminantWrapper = globals.getWrapperOfNode(node.discriminant);
            try {
                switchStatementWrapper.setDiscriminant(discriminantWrapper);
            } catch (e) {
                console.error("SWITCHSTATEMENT - Could not set discriminant! Reason of the error: " + e + "\n");
            }
        }


    }
}