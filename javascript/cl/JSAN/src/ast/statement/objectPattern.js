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
        var objectPattern = factory.createObjectPatternWrapper(factory);
        globals.setPositionInfo(node, objectPattern);
        return objectPattern;
    } else {
        var objectPatternWrapper = globals.getWrapperOfNode(node);
        if (node.properties != null) {
            for (var i = 0; i < node.properties.length; i++) {
                if (node.properties[i] != null) {
                    var propertiesWrapper = globals.getWrapperOfNode(node.properties[i]);
                    if (node.properties[i].type !== "Literal") {
                        var propertiesWrapperFunctionString = "addProperties" + node.properties[i].type;
                    } else {
                        var propertiesWrapperFunctionString = "addProperties" + globals.getLiteralType(node.properties[i]) + node.properties[i].type;
                    }
                    try {
                        objectPatternWrapper[propertiesWrapperFunctionString](propertiesWrapper);
                    } catch (e) {
                        console.error("OBJECTPATTERN - Function not exist: objectPatternWrapper." + propertiesWrapperFunctionString + "! Reason of the error: " + e + "\n");
                    }
                }
            }
        }
    }
}