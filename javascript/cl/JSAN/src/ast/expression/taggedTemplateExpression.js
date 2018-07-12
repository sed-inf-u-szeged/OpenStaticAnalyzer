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
        var taggedTemplateExpression = factory.createTaggedTemplateExpressionWrapper(factory);
        globals.setPositionInfo(node, taggedTemplateExpression);
        return taggedTemplateExpression;
    } else {
        var taggedTemplateExpressionWrapper = globals.getWrapperOfNode(node);

        if (node.tag != null) {
            var tagWrapper = globals.getWrapperOfNode(node.tag);
            if (node.tag.type !== "Literal") {
                var tagWrapperFunctionString = "setTag" + node.tag.type;
            } else {
                var tagWrapperFunctionString = "setTag" + globals.getLiteralType(node.tag) + node.tag.type;
            }
            try {
                taggedTemplateExpressionWrapper[tagWrapperFunctionString](tagWrapper);
            } catch (e) {
                console.error("TAGGEDTEMPLATEEXPRESSION - Function not exist: taggedTemplateExpressionWrapper." + tagWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

        if (node.quasi != null) {
            var quasiWrapper = globals.getWrapperOfNode(node.quasi);
            if (node.quasi.type !== "Literal") {
                var quasiWrapperFunctionString = "setQuasi" + node.quasi.type;
            } else {
                var quasiWrapperFunctionString = "setQuasi" + globals.getLiteralType(node.quasi) + node.quasi.type;
            }
            try {
                taggedTemplateExpressionWrapper[quasiWrapperFunctionString](quasiWrapper);
            } catch (e) {
                console.error("TAGGEDTEMPLATEEXPRESSION - Function not exist: taggedTemplateExpressionWrapper." + quasiWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

    }
}