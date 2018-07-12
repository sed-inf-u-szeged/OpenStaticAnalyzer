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
        var sequenceExpression = factory.createSequenceExpressionWrapper(factory);
        globals.setPositionInfo(node, sequenceExpression);
        return sequenceExpression;
    } else {
        var sequenceExpressionWrapper = globals.getWrapperOfNode(node);
        if (node.expressions != null) {
            for (var i = 0; i < node.expressions.length; i++) {
                if (node.expressions[i] != null) {
                    var expressionsWrapper = globals.getWrapperOfNode(node.expressions[i]);
                    if (node.expressions[i].type !== "Literal") {
                        var expressionsWrapperFunctionString = "addExpressions" + node.expressions[i].type;
                    } else {
                        var expressionsWrapperFunctionString = "addExpressions" + globals.getLiteralType(node.expressions[i]) + node.expressions[i].type;
                    }
                    try {
                        sequenceExpressionWrapper[expressionsWrapperFunctionString](expressionsWrapper);
                    } catch (e) {
                        console.error("SEQUENCEEXPRESSION - Function not exist: sequenceExpressionWrapper." + expressionsWrapperFunctionString + "! Reason of the error: " + e + "\n");
                    }
                }
            }
        }
    }
}