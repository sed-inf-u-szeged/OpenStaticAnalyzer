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
        var taggedTemplateExpression = factory.createTaggedTemplateExpressionWrapper();
        globals.setPositionInfo(node, taggedTemplateExpression);
        return taggedTemplateExpression;
    } else {
        var taggedTemplateExpressionWrapper = globals.getWrapperOfNode(node);

        if (node.tag != null) {
            var tagWrapper = globals.getWrapperOfNode(node.tag);
            try {
                taggedTemplateExpressionWrapper.setTag(tagWrapper);
            } catch (e) {
                console.error("TAGGEDTEMPLATEEXPRESSION - Could not add tag! Reason of the error: " + e + "\n");
            }
        }

        if (node.quasi != null) {
            var quasiWrapper = globals.getWrapperOfNode(node.quasi);
            try {
                taggedTemplateExpressionWrapper.setQuasi(quasiWrapper);
            } catch (e) {
                console.error("TAGGEDTEMPLATEEXPRESSION - Could not set quasi! Reason of the error: " + e + "\n");
            }
        }

    }
}