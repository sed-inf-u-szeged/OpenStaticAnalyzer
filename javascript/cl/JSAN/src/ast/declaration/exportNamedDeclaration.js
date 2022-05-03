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

import * as globals from '../../globals.js';

const factory = globals.getFactory();

export default function (node, parent, firstVisit) {
    if (firstVisit) {
        if (globals.getWrapperOfNode(node) !== undefined) {
            return;
        }
        const exportNamedDeclaration = factory.createExportNamedDeclarationWrapper();
        globals.setPositionInfo(node, exportNamedDeclaration);
        return exportNamedDeclaration;
    } else {
        const exportNamedDeclarationWrapper = globals.getWrapperOfNode(node);

        if (node.source != null) {
            globals.safeSet(exportNamedDeclarationWrapper, "setSource", node.source, "EXPORTNAMEDDECLARATION - Could not set source!");
        }

        if (node.declaration != null) {
            globals.safeSet(exportNamedDeclarationWrapper, "setDeclaration", node.declaration, "EXPORTNAMEDDECLARATION - Could not set declaration!")
        }

        if (node.specifiers != null) {
            for (let i = 0; i < node.specifiers.length; i++) {
                if (node.specifiers[i] != null) {
                    globals.safeSet(exportNamedDeclarationWrapper, "addSpecifiers", node.specifiers[i], "EXPORTNAMEDDECLARATION - Could not add specifier!")
                }
            }
        }
    }
}
