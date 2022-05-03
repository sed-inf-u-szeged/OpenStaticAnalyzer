import * as globals from '../../globals.js';

const factory = globals.getFactory();

export default function (node, parent, firstVisit) {
    if (firstVisit) {
        if (globals.getWrapperOfNode(node) !== undefined) {
            return;
        }
        const propertyDefinition = factory.createPropertyDefinitionWrapper();
        globals.setPositionInfo(node, propertyDefinition);

        propertyDefinition.setComputed(node.computed);
        propertyDefinition.setStatic(node.static);
        return propertyDefinition;
    } else {
        const propertyDefinitionWrapper = globals.getWrapperOfNode(node);

        if (node.key !== null) {
            globals.safeSet(propertyDefinitionWrapper, "setKey", node.key, "PROPERTYDEFINITION - Could not set key!");
        }

        if (node.value !== null) {
            globals.safeSet(propertyDefinitionWrapper, "setValue", node.value, "PROPERTYDEFINITION - Could not set value!");
        }

    }
}
