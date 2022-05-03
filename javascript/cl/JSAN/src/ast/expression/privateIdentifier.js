import * as globals from '../../globals.js';

const factory = globals.getFactory();

export default function (node, parent, firstVisit) {
    if (firstVisit) {
        if (globals.getWrapperOfNode(node) !== undefined) {
            return;
        }
        const privateIdentifier = factory.createPrivateIdentifierWrapper();
        globals.setPositionInfo(node, privateIdentifier);

        // Workaround until parser gets updated
        // TODO: Remove this once parser gets updated
        if (node.type === 'TSPrivateIdentifier') {
            privateIdentifier.setName(node.escapedText.substring(1));
        } else {
            privateIdentifier.setName(node.name);
        }
        return privateIdentifier;
    }
}
