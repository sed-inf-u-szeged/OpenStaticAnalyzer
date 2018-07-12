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
*
*/

var exports = module.exports = {};
const estraverse = require('estraverse');
var escope = require('escope');
var globals = require('../globals');

var scopeManager = null;
var scopeTree = null;
var currentScope = null;
var actNode = null;
var parsingOptions = null;

/*
    tree definition for cross reference
*/
function Node(data) {
    this.data = data;
    this.parent = null;
    this.children = [];
}

function Tree(data) {
    var node = new Node(data);
    this._root = node;

    this.add = function (data, parent) {
        var child = new Node(data);
        child.parent = parent;
        parent.children.push(child);
        return child;
    }
}

function leave(node) {
    if (/Function/.test(node.type) || /ClassDeclaration/.test(node.type)) {
        if (currentScope != null) {
            currentScope = currentScope.upper;  // set to parent scope
        }
        actNode = actNode.parent;
    }
}

function enter(ast, node) {
    if (!scopeManager) {
        scopeManager = escope.analyze(ast, parsingOptions);
    }

    if ("Program" == node.type) {
        currentScope = scopeManager.acquire(ast); //global scope for that file

        scopeTree = new Tree({ position: undefined, scope: currentScope, variables: [] });
        actNode = scopeTree._root;
    } else if (/Function/.test(node.type) || /ClassDeclaration/.test(node.type)) {
        //add var to actNode
        if (node.id && node.id.name) {
            actNode.data.variables.push({ name: node.id.name, node: node });
        }

        //new scope
        currentScope = scopeManager.acquire(node);  // get current function scope
        actNode = scopeTree.add({ position: node.range, scope: currentScope, variables: [] }, actNode);

        //add function params to vars
        if (/Function/.test(node.type)) {
            var idsInAsParams = extractIdentifiersFromParams(node.params);
            for (var i = 0; i < idsInAsParams.length; i++) {
                actNode.data.variables.push({ name: idsInAsParams[i].name, node: idsInAsParams[i] });
            }

        }

    }
    else if (/VariableDeclarator/.test(node.type)) {
        actNode.data.variables.push({ name: node.id.name, node: node });
    }
}

exports.setParsingOptions = function(parsingOptions){
	this.parsingOptions = parsingOptions;
}

exports.gatherScopes = function (ast, node, enterOrLeave) {
	parsingOptions = this.parsingOptions;
    if (enterOrLeave === "enter") {
        enter(ast, node);
    }
    else if (enterOrLeave === "leave") {
        leave(node);
    }

    
}

exports.resolveCrossRefs = function (node, parent) {
    if (/Identifier/.test(node.type)) {
        //reference -> create a cross edge
        if (!/VariableDeclarator/.test(parent.type) && !/Function/.test(parent.type)) {
            var referencedNode = getReferencedNode(node, scopeTree);
            if (referencedNode != null) {
                setRefersTo(node, referencedNode);
            }
        }
    }
}



/**
 * 
 */
function getReferencedNode(identifier, tree) {
    var actNode = tree._root;

    for (var i = 0; i < actNode.children.length; i++) {
        //matching scope
        if (actNode.children[i].data.position[0] <= identifier.range[0] && actNode.children[i].data.position[1] >= identifier.range[1]) {
            i = 0;
            actNode = actNode.children[i];
        }
    }

    while (actNode != null) {
        for (var i = 0; i < actNode.data.variables.length; i++) {
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

    if (/VariableDeclarator/.test(referencedNode.type)) {
        globals.getWrapperOfNode(identifier).setRefersToVariableDeclarator(globals.getWrapperOfNode(referencedNode));
    }
    else if (/Function/.test(referencedNode.type)) {
        globals.getWrapperOfNode(identifier).setRefersToFunction(globals.getWrapperOfNode(referencedNode));

    }
    else if (referencedNode.type === "Identifier") {
        globals.getWrapperOfNode(identifier).setRefersToIdentifier(globals.getWrapperOfNode(referencedNode));
    }



}


function extractIdentifiersFromParams(params) {
    var identifiers = [];

    for (var i = 0; i < params.length; i++) {
        //in case of identifier
        if (params[i].type === "Identifier" && params[i].name) {
            identifiers.push(params[i]);
        }
            //
        else if (params[i].type == "AssignmentPattern") {

            //function f(x = 10, y = 20){}
            if (params[i].left.type === "Identifier" && params[i].left.name) {
                identifiers.push(params[i].left);
            }

            //assignment is an array
            //function f([x,y] = 10)
            //function f([x,y] = [20,30])
            if (params[i].left.type === "ArrayPattern") {
                for (var j = 0; j < params[i].left.elements.length; j++) {
                    if (params[i].left.elements[j].type === "Identifier") {
                        identifiers.push(params[i].left.elements[j]);
                    }
                }
            }
        }
    }

    return identifiers;
}