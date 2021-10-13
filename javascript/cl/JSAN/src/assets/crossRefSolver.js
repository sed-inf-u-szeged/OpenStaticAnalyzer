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

/*
* Module that solves the cross references of the given AST.
*/
const estraverse = require('estraverse');
const escope = require('escope');
let globals = require('../globals');
let scopeManager = null;
let scopeTree = null;
let currentScope = null;
let actNode = null;
let parsingOptions = null;

/*
    tree definition for cross reference
*/
function Node(data) {
    this.data = data;
    this.parent = null;
    this.children = [];
}

function Tree(data) {
    let node = new Node(data);
    this._root = node;

    this.add = function (data, parent) {
        let child = new Node(data);
        child.parent = parent;
        parent.children.push(child);
        return child;
    }
}

function leave(node) {
    if (/Function/.test(node.type) || /ClassDeclaration/.test(node.type)) {
        if (currentScope !== null) {
            currentScope = currentScope.upper;  // set to parent scope
        }
        actNode = actNode.parent;
    }
}

function enter(ast, node) {
    if (!scopeManager) {
        scopeManager = escope.analyze(ast, parsingOptions);
    }
    if ("Program" === node.type) {
        currentScope = scopeManager.acquire(ast); //global scope for that file

        scopeTree = new Tree({position: undefined, scope: currentScope, variables: []});
        actNode = scopeTree._root;
    } else if (/Function/.test(node.type) || /ClassDeclaration/.test(node.type)) {
        //add var to actNode
        if (node.id && node.id.name) {
            actNode.data.variables.push({name: node.id.name, node: node});
        }

        //new scope
        currentScope = scopeManager.acquire(node);  // get current function scope
        actNode = scopeTree.add({position: node.range, scope: currentScope, variables: []}, actNode);

        //add function params to vars
        if (/Function/.test(node.type)) {
            let idsInAsParams = extractIdentifiersFromParams(node.params);
            for (let i = 0; i < idsInAsParams.length; i++) {
                actNode.data.variables.push({name: idsInAsParams[i].name, node: idsInAsParams[i]});
            }
        }
    }
    else if (/VariableDeclarator/.test(node.type)) {
        actNode.data.variables.push({name: node.id.name, node: node});
    }
}

exports.setParsingOptions = function (parsingOptions) {
    this.parsingOptions = parsingOptions;
};

exports.gatherScopes = function (ast, node, enterOrLeave) {
    parsingOptions = this.parsingOptions;
    if (enterOrLeave === "enter") {
        enter(ast, node);
    }
    else if (enterOrLeave === "leave") {
        leave(node);
    }
};

exports.resolveNode = function (ast, filename, range_start, range_end, inner = false) {
    const searchNode = {
        file: filename, range: {
            start: range_start, end: range_end
        }
    };
    let result = null;
    let status = false;
    
    ast.forEach(astNode => {
        if (status || astNode.filename !== searchNode.file) {
            return;
        }
        globals.setActualFile(astNode.filename);

        // find the most inner node which has the same exact source position
        estraverse.traverse(astNode, {
            enter: function (node) {
                if (status){
                    if(inner){ // return the most inner node
                        if (node.range[0] !== searchNode.range.start || node.range[1] !== searchNode.range.end){
                            return;
                        }
                    }
                    else{ // return the most outer node
                        return;
                    }

                }
                if (node.range[0] === searchNode.range.start && node.range[1] === searchNode.range.end && node.type !== 'Program') {
                    status = true;
                    result = node;
                }
            }
        });
    });
    return result;
};

exports.resolveVariableUsages = function (node, parent) {

    let skip = [
        "VariableDeclarator",
        "Function"
    ];
    if (/Identifier/.test(node.type)) {
        //reference -> create a cross edge
        if (skip.indexOf(parent.type) === -1) {
            let referencedNode = getReferencedNode(node, scopeTree);
            if (referencedNode !== null) {
                if(referencedNode.range[0] === node.range[0] && referencedNode.range[1] === node.range[1]){
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

function setRefersTo(identifier, referencedNode) {
    if (identifier === referencedNode) {
        return;
    }
    if (/VariableDeclarator/.test(referencedNode.type) || /Function/.test(referencedNode.type) || /Identifier/.test(referencedNode.type)) {
        globals.getWrapperOfNode(identifier).setRefersTo(globals.getWrapperOfNode(referencedNode));
    }
}

function extractIdentifiersFromParams(params) {
    let identifiers = [];
    for (let i = 0; i < params.length; i++) {
        //in case of identifier
        if (params[i].type === "Identifier" && params[i].name) {
            identifiers.push(params[i]);
        }
        //
        else if (params[i].type === "AssignmentPattern") {
            //function f(x = 10, y = 20){}
            if (params[i].left.type === "Identifier" && params[i].left.name) {
                identifiers.push(params[i].left);
            }

            //assignment is an array
            //function f([x,y] = 10)
            //function f([x,y] = [20,30])
            if (params[i].left.type === "ArrayPattern") {
                for (let j = 0; j < params[i].left.elements.length; j++) {
                    if (params[i].left.elements[j].type === "Identifier") {
                        identifiers.push(params[i].left.elements[j]);
                    }
                }
            }
            //TODO: objectPattern
        }
    }
    return identifiers;
}
