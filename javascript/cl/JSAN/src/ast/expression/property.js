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
const conversions = require('../conversions');

module.exports = function (node, parent, firstVisit) {
    if (firstVisit) {
        if (globals.getWrapperOfNode(node) !== undefined) {
            return;
        }
        var property = factory.createPropertyWrapper(factory);
        globals.setPositionInfo(node, property);
        property.setKind(conversions.convertPropertyKind(node.kind));
        property.setMethod(node.method);
        property.setShorthand(node.shorthand);
        property.setComputed(node.computed);
        return property;
    } else {
        var propertyWrapper = globals.getWrapperOfNode(node);

        if (node.key != null) {
            var keyWrapper = globals.getWrapperOfNode(node.key);
            if (node.key.type !== "Literal") {
                var keyWrapperFunctionString = "setKey" + node.key.type;
            } else {
                var keyWrapperFunctionString = "setKey" + globals.getLiteralType(node.key) + node.key.type;
            }
            try {
                propertyWrapper[keyWrapperFunctionString](keyWrapper);
            } catch (e) {
                console.error("PROPERTY - Function not exist: propertyWrapper." + keyWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

        if (node.value != null) {
            var valueWrapper = globals.getWrapperOfNode(node.value);
            if (node.value.type !== "Literal") {
                var valueWrapperFunctionString = "setValue" + node.value.type;
            } else {
                var valueWrapperFunctionString = "setValue" + globals.getLiteralType(node.value) + node.value.type;
            }
            try {
                propertyWrapper[valueWrapperFunctionString](valueWrapper);
            } catch (e) {
                console.error("PROPERTY - Function not exist: propertyWrapper." + valueWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

    }
}