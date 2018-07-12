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
        var memberExpression = factory.createMemberExpressionWrapper(factory);
        globals.setPositionInfo(node, memberExpression);
        memberExpression.setComputed(node.computed);
        return memberExpression;
    } else {
        var memberExpressionWrapper = globals.getWrapperOfNode(node);

        if (node.property != null) {
            var propertyWrapper = globals.getWrapperOfNode(node.property);
            if (node.property.type !== "Literal") {
                var propertyWrapperFunctionString = "setProperty" + node.property.type;
            } else {
                var propertyWrapperFunctionString = "setProperty" + globals.getLiteralType(node.property) + node.property.type;
            }
            try {
                memberExpressionWrapper[propertyWrapperFunctionString](propertyWrapper);
            } catch (e) {
                console.error("MEMBEREXPRESSION - Function not exist: memberExpressionWrapper." + propertyWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

        if (node.object != null) {
            var objectWrapper = globals.getWrapperOfNode(node.object);
            if (node.object.type !== "Literal") {
                var objectWrapperFunctionString = "setObject" + node.object.type;
            } else {
                var objectWrapperFunctionString = "setObject" + globals.getLiteralType(node.object) + node.object.type;
            }
            try {
                memberExpressionWrapper[objectWrapperFunctionString](objectWrapper);
            } catch (e) {
                console.error("MEMBEREXPRESSION - Function not exist: memberExpressionWrapper." + objectWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

    }
}