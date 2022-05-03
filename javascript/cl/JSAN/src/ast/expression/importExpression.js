import * as globals from '../../globals.js';

const factory = globals.getFactory();

export default function (node, parent, firstVisit) {
    if (firstVisit) {
        if (globals.getWrapperOfNode(node) !== undefined) {
            return;
        }
        const importExpression = factory.createImportExpressionWrapper();
        globals.setPositionInfo(node, importExpression);
        return importExpression;
    } else {
        const importExpressionWrapper = globals.getWrapperOfNode(node);

        if (node.source != null) {
            globals.safeSet(importExpressionWrapper, "setSource", node.source, "IMPORTEXPRESSION - Could not set source!");
        }
    }
}
