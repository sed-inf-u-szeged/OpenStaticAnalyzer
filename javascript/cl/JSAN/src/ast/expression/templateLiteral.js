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
        var templateLiteral = factory.createTemplateLiteralWrapper(factory);
        globals.setPositionInfo(node, templateLiteral);
        return templateLiteral;
    } else {
        var templateLiteralWrapper = globals.getWrapperOfNode(node);

        if (node.quasi != null) {
            var quasiWrapper = globals.getWrapperOfNode(node.quasi);
            if (node.quasi.type !== "Literal") {
                var quasiWrapperFunctionString = "setQuasi" + node.quasi.type;
            } else {
                var quasiWrapperFunctionString = "setQuasi" + globals.getLiteralType(node.quasi) + node.quasi.type;
            }
            try {
                templateLiteralWrapper[quasiWrapperFunctionString](quasiWrapper);
            } catch (e) {
                console.error("TEMPLATELITERAL - Function not exist: templateLiteralWrapper." + quasiWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

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
                        templateLiteralWrapper[expressionsWrapperFunctionString](expressionsWrapper);
                    } catch (e) {
                        console.error("TEMPLATELITERAL - Function not exist: templateLiteralWrapper." + expressionsWrapperFunctionString + "! Reason of the error: " + e + "\n");
                    }
                }
            }
        }
        if (node.quasis != null) {
            for (var i = 0; i < node.quasis.length; i++) {
                if (node.quasis[i] != null) {
                    var quasisWrapper = globals.getWrapperOfNode(node.quasis[i]);
                    if (node.quasis[i].type !== "Literal") {
                        var quasisWrapperFunctionString = "addQuasis" + node.quasis[i].type;
                    } else {
                        var quasisWrapperFunctionString = "addQuasis" + globals.getLiteralType(node.quasis[i]) + node.quasis[i].type;
                    }
                    try {
                        templateLiteralWrapper[quasisWrapperFunctionString](quasisWrapper);
                    } catch (e) {
                        console.error("TEMPLATELITERAL - Function not exist: templateLiteralWrapper." + quasisWrapperFunctionString + "! Reason of the error: " + e + "\n");
                    }
                }
            }
        }
    }
}