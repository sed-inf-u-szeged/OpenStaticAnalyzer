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
        var classNode = factory.createClassWrapper(factory);
        globals.setPositionInfo(node, classNode);
        return classNode;
    } else {
        var classWrapper = globals.getWrapperOfNode(node);

        if (node.superClass != null) {
            var superClassWrapper = globals.getWrapperOfNode(node.superClass);
            if (node.superClass.type !== "Literal") {
                var superClassWrapperFunctionString = "setSuperClass" + node.superClass.type;
            } else {
                var superClassWrapperFunctionString = "setSuperClass" + globals.getLiteralType(node.superClass) + node.superClass.type;
            }
            try {
                classWrapper[superClassWrapperFunctionString](superClassWrapper);
            } catch (e) {
                console.error("CLASS - Function not exist: classWrapper." + superClassWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

        if (node.body != null) {
            var bodyWrapper = globals.getWrapperOfNode(node.body);
            if (node.body.type !== "Literal") {
                var bodyWrapperFunctionString = "setBody" + node.body.type;
            } else {
                var bodyWrapperFunctionString = "setBody" + globals.getLiteralType(node.body) + node.body.type;
            }
            try {
                classWrapper[bodyWrapperFunctionString](bodyWrapper);
            } catch (e) {
                console.error("CLASS - Function not exist: classWrapper." + bodyWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

        if (node.id != null) {
            var identifierWrapper = globals.getWrapperOfNode(node.id);
            if (node.id.type !== "Literal") {
                var identifierWrapperFunctionString = "setIdentifier" + node.id.type;
            } else {
                var identifierWrapperFunctionString = "setIdentifier" + globals.getLiteralType(node.id) + node.id.type;
            }
            try {
                classWrapper[identifierWrapperFunctionString](identifierWrapper);
            } catch (e) {
                console.error("CLASS - Function not exist: classWrapper." + identifierWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

    }
}