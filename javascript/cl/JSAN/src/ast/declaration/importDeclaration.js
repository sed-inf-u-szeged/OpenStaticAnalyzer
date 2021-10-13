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
        var importDeclaration = factory.createImportDeclarationWrapper();
        globals.setPositionInfo(node, importDeclaration);
        return importDeclaration;
    } else {
        var importDeclarationWrapper = globals.getWrapperOfNode(node);

        if (node.source != null) {
            var sourceWrapper = globals.getWrapperOfNode(node.source);
            try {
                importDeclarationWrapper.setSource(sourceWrapper);
            } catch (e) {
                console.error("IMPORTDECLARATION - Could not set source! Reason of the error: " + e + "\n");
            }
        }

        if (node.specifiers != null) {
            for (var i = 0; i < node.specifiers.length; i++) {
                if (node.specifiers[i] != null) {
                    var specifiersWrapper = globals.getWrapperOfNode(node.specifiers[i]);
                    try {
                        importDeclarationWrapper.addSpecifiers(specifiersWrapper);
                    } catch (e) {
                        console.error("IMPORTDECLARATION - Could not add specifiers! Reason of the error: " + e + "\n");
                    }
                }
            }
        }
    }
}