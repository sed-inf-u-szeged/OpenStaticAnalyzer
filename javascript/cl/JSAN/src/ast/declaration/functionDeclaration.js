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
        const functionDeclaration = factory.createFunctionDeclarationWrapper();
        globals.setPositionInfo(node, functionDeclaration);
        functionDeclaration.setGenerator(node.generator);
        functionDeclaration.setAsync(node.async);
        return functionDeclaration;
    } else {
        const functionDeclarationWrapper = globals.getWrapperOfNode(node);

        if (node.params != null) {
            for (let i = 0; i < node.params.length; i++) {
                if (node.params[i] != null) {
                    globals.safeSet(functionDeclarationWrapper, "addParams", node.params[i], "FUNCTIONDECLARATION - Could not add param");
                }
            }
        }

        if (node.declaration != null) {
            globals.safeSet(functionDeclarationWrapper, "setDeclaration", node.declaration, "FUNCTIONDECLARATION - Could not set declaration!");
        }

        if (node.body != null) {
            globals.safeSet(functionDeclarationWrapper, "setBody", node.body, "FUNCTIONDECLARATION - Could not set body!");
        }

        if (node.id != null) {
            globals.safeSet(functionDeclarationWrapper, "setIdentifier", node.id, "FUNCTIONDECLARATION - Could not set identifier!");
        }

    }
}
