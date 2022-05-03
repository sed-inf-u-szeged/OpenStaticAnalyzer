import * as globals from '../globals.js';


const skip = [
    "VariableDeclarator",
    "Function"
];

const resolveVariableUsages = function (node, parent, scopeMgr) {
    if (/Identifier/.test(node.type)) {
        //reference -> create a cross edge
        if (skip.indexOf(parent.type) === -1) {
            let referencedNode = getReferencedNode(node, scopeMgr.scopeTree);
            if (referencedNode !== null) {
                if (referencedNode.range[0] === node.range[0] && referencedNode.range[1] === node.range[1]) {
                    return null;
                }

                return {
                    source: {
                        label: node.name,
                        file: globals.getActualFile(),
                        start: {row: node.loc.start.line, column: node.loc.start.column},
                        end: {row: node.loc.end.line, column: node.loc.end.column},
                        range: {start: node.range[0], end: node.range[1]},
                        node: node
                    },
                    target: {
                        label: null,
                        file: globals.getActualFile(),
                        start: {row: referencedNode.loc.start.line, column: referencedNode.loc.start.column},
                        end: {row: referencedNode.loc.end.line, column: referencedNode.loc.end.column},
                        range: {start: referencedNode.range[0], end: referencedNode.range[1]},
                        node: referencedNode
                    }
                };
            }
        }
    }
    return null;
};

function getReferencedNode(identifier, tree) {
    let actNode = tree._root;
    for (let i = 0; i < actNode.children.length; i++) {
        //matching scope
        if (actNode.children[i].data.position[0] <= identifier.range[0] && actNode.children[i].data.position[1] >= identifier.range[1]) {
            i = 0;
            actNode = actNode.children[i];
        }
    }

    while (actNode !== null) {
        for (let i = 0; i < actNode.data.variables.length; i++) {
            if (actNode.data.variables[i].name === identifier.name) {
                return actNode.data.variables[i].node;
            }
        }

        actNode = actNode.parent;
    }
    return null;
}

// function setRefersTo(identifier, referencedNode) {
//     if (identifier === referencedNode) {
//         return;
//     }
//     if (/VariableDeclarator/.test(referencedNode.type) || /Function/.test(referencedNode.type) || /Identifier/.test(referencedNode.type)) {
//         globals.getWrapperOfNode(identifier).setRefersTo(globals.getWrapperOfNode(referencedNode));
//     }
// }

export {
    resolveVariableUsages
}