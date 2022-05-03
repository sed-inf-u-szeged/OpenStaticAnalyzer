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

import * as path from 'path';
import * as conversions from '../conversions.js';
import * as globals from '../../globals.js';

const factory = globals.getFactory();

export default function (node, parent, firstVisit) {
    globals.setActualProgramNode(node);
    const actualJsFilePath = globals.getActualFile();
    //new program => clear comments

    if (firstVisit) {
        if (globals.getWrapperOfNode(node) !== undefined) {
            return;
        }
        const program = factory.createProgramWrapper();
        program.setName(path.basename(actualJsFilePath, path.extname(actualJsFilePath)));
        globals.setPositionInfo(node, program);
        factory.getRoot().addPrograms(program);
        program.setSourceType(conversions.convertSourceType(node.sourceType));
        return program;
    } else {
        const programWrapper = globals.getWrapperOfNode(node);
        if (node.body != null) {
            for (let i = 0; i < node.body.length; i++) {
                if (node.body[i] != null) {

                    globals.safeSet(programWrapper, "addBody", node.body[i], "PROGRAM - Cannot add body to program!");
                }
            }
        }
    }
}
