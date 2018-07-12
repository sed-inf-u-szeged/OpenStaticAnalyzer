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
const conversions = require('../conversions');

module.exports = function (node, parent, firstVisit) {
    if (firstVisit) {
        if (globals.getWrapperOfNode(node) !== undefined) {
            return;
        }
        var variableDeclaration = factory.createVariableDeclarationWrapper(factory);
        globals.setPositionInfo(node, variableDeclaration);
        variableDeclaration.setKind(conversions.convertDeclarationKind(node.kind));
        return variableDeclaration;
    } else {
        var variableDeclarationWrapper = globals.getWrapperOfNode(node);
        if (node.declarations != null) {
            for (var i = 0; i < node.declarations.length; i++) {
                if (node.declarations[i] != null) {
                    var declarationsWrapper = globals.getWrapperOfNode(node.declarations[i]);
                    if (node.declarations[i].type !== "Literal") {
                        var declarationsWrapperFunctionString = "addDeclarations" + node.declarations[i].type;
                    } else {
                        var declarationsWrapperFunctionString = "addDeclarations" + globals.getLiteralType(node.declarations[i]) + node.declarations[i].type;
                    }
                    try {
                        variableDeclarationWrapper[declarationsWrapperFunctionString](declarationsWrapper);
                    } catch (e) {
                        console.error("VARIABLEDECLARATION - Function not exist: variableDeclarationWrapper." + declarationsWrapperFunctionString + "! Reason of the error: " + e + "\n");
                    }
                }
            }
        }
    }
}