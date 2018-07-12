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
        var exportNamedDeclaration = factory.createExportNamedDeclarationWrapper(factory);
        globals.setPositionInfo(node, exportNamedDeclaration);
        return exportNamedDeclaration;
    } else {
        var exportNamedDeclarationWrapper = globals.getWrapperOfNode(node);

        if (node.source != null) {
            var sourceWrapper = globals.getWrapperOfNode(node.source);
            if (node.source.type !== "Literal") {
                var sourceWrapperFunctionString = "setSource" + node.source.type;
            } else {
                var sourceWrapperFunctionString = "setSource" + globals.getLiteralType(node.source) + node.source.type;
            }
            try {
                exportNamedDeclarationWrapper[sourceWrapperFunctionString](sourceWrapper);
            } catch (e) {
                console.error("EXPORTNAMEDDECLARATION - Function not exist: exportNamedDeclarationWrapper." + sourceWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

        if (node.declaration != null) {
            var declarationWrapper = globals.getWrapperOfNode(node.declaration);
            if (node.declaration.type !== "Literal") {
                var declarationWrapperFunctionString = "setDeclaration" + node.declaration.type;
            } else {
                var declarationWrapperFunctionString = "setDeclaration" + globals.getLiteralType(node.declaration) + node.declaration.type;
            }
            try {
                exportNamedDeclarationWrapper[declarationWrapperFunctionString](declarationWrapper);
            } catch (e) {
                console.error("EXPORTNAMEDDECLARATION - Function not exist: exportNamedDeclarationWrapper." + declarationWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

        if (node.specifiers != null) {
            for (var i = 0; i < node.specifiers.length; i++) {
                if (node.specifiers[i] != null) {
                    var specifiersWrapper = globals.getWrapperOfNode(node.specifiers[i]);
                    if (node.specifiers[i].type !== "Literal") {
                        var specifiersWrapperFunctionString = "addSpecifiers" + node.specifiers[i].type;
                    } else {
                        var specifiersWrapperFunctionString = "addSpecifiers" + globals.getLiteralType(node.specifiers[i]) + node.specifiers[i].type;
                    }
                    try {
                        exportNamedDeclarationWrapper[specifiersWrapperFunctionString](specifiersWrapper);
                    } catch (e) {
                        console.error("EXPORTNAMEDDECLARATION - Function not exist: exportNamedDeclarationWrapper." + specifiersWrapperFunctionString + "! Reason of the error: " + e + "\n");
                    }
                }
            }
        }
    }
}