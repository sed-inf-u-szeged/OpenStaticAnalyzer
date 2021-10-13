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
        var exportSpecifier = factory.createExportSpecifierWrapper();
        globals.setPositionInfo(node, exportSpecifier);
        return exportSpecifier;
    } else {
        var exportSpecifierWrapper = globals.getWrapperOfNode(node);

        if (node.exported != null) {
            var exportedWrapper = globals.getWrapperOfNode(node.exported);
            try {
                exportSpecifierWrapper.setExported(exportedWrapper);
            } catch (e) {
                console.error("EXPORTSPECIFIER - Could not set exported! Reason of the error: " + e + "\n");
            }
        }

        if (node.local != null) {
            var localWrapper = globals.getWrapperOfNode(node.local);
            try {
                exportSpecifierWrapper.setLocal(localWrapper);
            } catch (e) {
                console.error("EXPORTSPECIFIER - Could not set local! Reason of the error: " + e + "\n");
            }
        }

    }
}