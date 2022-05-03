import * as globals from '../../globals.js';

const factory = globals.getFactory();

export default function (node, parent, firstVisit) {
    if (firstVisit) {
        if (globals.getWrapperOfNode(node) !== undefined) {
            return;
        }
        let chainExpression = factory.createChainExpressionWrapper();
        globals.setPositionInfo(node, chainExpression);
        return chainExpression;
    } else {
        let chainExpressionWrapper = globals.getWrapperOfNode(node);

        if (node.expression != null) {
            globals.safeSet(chainExpressionWrapper, "setExpression", node.expression, "CHAINEXPRESSION - Could not set expression!");
        }
    }
}
