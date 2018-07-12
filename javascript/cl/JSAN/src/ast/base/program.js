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

const path = require('path');
const conversions = require('../conversions');

var globals = require('../../globals');
var factory = globals.getFactory();



module.exports = function (node, parent, firstVisit) {
    globals.setActualProgramNode(node);
    var actualJsFilePath = globals.getActualFile();
    //new program => clear comments
    globals.clearCommentMap();

    if (firstVisit) {
        if (globals.getWrapperOfNode(node) !== undefined) {
            return;
        }
        var program = factory.createProgramWrapper(factory);
        program.setName(path.basename(actualJsFilePath, path.extname(actualJsFilePath)));
        globals.setPositionInfo(node, program);
        factory.getRoot(factory).addProgramsProgram(program);
        program.setSourceType(conversions.convertSourceType(node.sourceType));
        return program;
    } else {
        var programWrapper = globals.getWrapperOfNode(node);
        if (node.body != null) {
            for (var i = 0; i < node.body.length; i++) {
                if (node.body[i] != null) {
                    var bodyWrapper = globals.getWrapperOfNode(node.body[i]);
                    if (node.body[i].type !== "Literal") {
                        var bodyWrapperFunctionString = "addBody" + node.body[i].type;
                    } else {
                        var bodyWrapperFunctionString = "addBody" + globals.getLiteralType(node.body[i]) + node.body[i].type;
                    }
                    try {
                        programWrapper[bodyWrapperFunctionString](bodyWrapper);
                    } catch (e) {
                        console.error("PROGRAM - Function not exist: programWrapper." + bodyWrapperFunctionString + "! Reason of the error: " + e + "\n");
                    }
                }
            }
        }
    }
}