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
        var metaProperty = factory.createMetaPropertyWrapper(factory);
        globals.setPositionInfo(node, metaProperty);
        return metaProperty;
    } else {
        var metaPropertyWrapper = globals.getWrapperOfNode(node);

        if (node.meta != null) {
            var metaWrapper = globals.getWrapperOfNode(node.meta);
            if (node.meta.type !== "Literal") {
                var metaWrapperFunctionString = "setMeta" + node.meta.type;
            } else {
                var metaWrapperFunctionString = "setMeta" + globals.getLiteralType(node.meta) + node.meta.type;
            }
            try {
                metaPropertyWrapper[metaWrapperFunctionString](metaWrapper);
            } catch (e) {
                console.error("METAPROPERTY - Function not exist: metaPropertyWrapper." + metaWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

        if (node.property != null) {
            var propertyWrapper = globals.getWrapperOfNode(node.property);
            if (node.property.type !== "Literal") {
                var propertyWrapperFunctionString = "setProperty" + node.property.type;
            } else {
                var propertyWrapperFunctionString = "setProperty" + globals.getLiteralType(node.property) + node.property.type;
            }
            try {
                metaPropertyWrapper[propertyWrapperFunctionString](propertyWrapper);
            } catch (e) {
                console.error("METAPROPERTY - Function not exist: metaPropertyWrapper." + propertyWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

    }
}