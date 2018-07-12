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
        var switchStatement = factory.createSwitchStatementWrapper(factory);
        globals.setPositionInfo(node, switchStatement);
        return switchStatement;
    } else {
        var switchStatementWrapper = globals.getWrapperOfNode(node);
        if (node.cases != null) {
            for (var i = 0; i < node.cases.length; i++) {
                if (node.cases[i] != null) {
                    var casesWrapper = globals.getWrapperOfNode(node.cases[i]);
                    if (node.cases[i].type !== "Literal") {
                        var casesWrapperFunctionString = "addCases" + node.cases[i].type;
                    } else {
                        var casesWrapperFunctionString = "addCases" + globals.getLiteralType(node.cases[i]) + node.cases[i].type;
                    }
                    try {
                        switchStatementWrapper[casesWrapperFunctionString](casesWrapper);
                    } catch (e) {
                        console.error("SWITCHSTATEMENT - Function not exist: switchStatementWrapper." + casesWrapperFunctionString + "! Reason of the error: " + e + "\n");
                    }
                }
            }
        }
        if (node.discriminant != null) {
            var discriminantWrapper = globals.getWrapperOfNode(node.discriminant);
            if (node.discriminant.type !== "Literal") {
                var discriminantWrapperFunctionString = "setDiscriminant" + node.discriminant.type;
            } else {
                var discriminantWrapperFunctionString = "setDiscriminant" + globals.getLiteralType(node.discriminant) + node.discriminant.type;
            }
            try {
                switchStatementWrapper[discriminantWrapperFunctionString](discriminantWrapper);
            } catch (e) {
                console.error("SWITCHSTATEMENT - Function not exist: switchStatementWrapper." + discriminantWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }


    }
}