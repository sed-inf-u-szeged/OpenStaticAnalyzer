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
        var type = globals.getLiteralType(node);
        var literalNode;

        if (globals.getWrapperOfNode(node) !== undefined) {
            return;
        }

        switch (type) {
            case "Number":
                literalNode = factory.createNumberLiteralWrapper();
                literalNode.setValue(node.value);
                break;
            case "Boolean":
                literalNode = factory.createBooleanLiteralWrapper();
                literalNode.setValue(node.value);
                break;
            case "String":
                literalNode = factory.createStringLiteralWrapper();
                literalNode.setValue(node.value);
                break;
            case "Null":
                literalNode = factory.createNullLiteralWrapper();
                break;
            case "RegExp":
                literalNode = factory.createRegExpLiteralWrapper();
                literalNode.setFlags(node.regex.flags);
                literalNode.setPattern(node.regex.pattern);
                break;
            default:
                console.log("Literal type not recognized! Type: " + type);
                return;
        }

        globals.setPositionInfo(node, literalNode);
        literalNode.setRaw(node.raw);

        return literalNode;
    }

}