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
        var exportAllDeclaration = factory.createExportAllDeclarationWrapper(factory);
        globals.setPositionInfo(node, exportAllDeclaration);
        return exportAllDeclaration;
    } else {
        var exportAllDeclarationWrapper = globals.getWrapperOfNode(node);

        if (node.source != null) {
            var sourceWrapper = globals.getWrapperOfNode(node.source);
            if (node.source.type !== "Literal") {
                var sourceWrapperFunctionString = "setSource" + node.source.type;
            } else {
                var sourceWrapperFunctionString = "setSource" + globals.getLiteralType(node.source) + node.source.type;
            }
            try {
                exportAllDeclarationWrapper[sourceWrapperFunctionString](sourceWrapper);
            } catch (e) {
                console.error("EXPORTALLDECLARATION - Function not exist: exportAllDeclarationWrapper." + sourceWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

    }
}