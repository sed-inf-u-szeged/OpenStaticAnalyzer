import {analyze} from '@typescript-eslint/scope-manager';
import {Tree} from '../util/tree'

class JSANScopeManager {

    constructor(parsingOptions = null) {
        this.scopeManager = null;
        this.scopeTree = null;
        this.currentScope = null;
        this.actNode = null;
        this.parsingOptions = parsingOptions;
    }


    static extractIdentifiersFromParams(params) {
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

                //TODO: review objectPattern
                // https://esprima.readthedocs.io/en/latest/syntax-tree-format.html
                if (params[i].left.type === "ObjectPattern") {
                    for (let j = 0; j < params[i].left.properties.length; j++) {
                        if (params[i].left.properties[j].key.type === "Identifier") {
                            identifiers.push(params[i].left.properties[j].key)
                        }
                    }
                }
            }
        }
        return identifiers;
    }


    enter(ast, node) {
        if (!this.scopeManager) {
            this.scopeManager = analyze(ast, this.parsingOptions);
        }
        if ("Program" === node.type) {
            this.currentScope = this.scopeManager.acquire(ast); //global scope for that file
            this.scopeTree = new Tree({position: undefined, scope: this.currentScope, variables: []});
            this.actNode = this.scopeTree._root;
        } else if (/Function/.test(node.type) || /ClassDeclaration/.test(node.type)) {

            //add var to actNode
            if (node.id && node.id.name) {
                this.actNode.data.variables.push({name: node.id.name, node: node});
            }

            //new scope
            this.currentScope = this.scopeManager.acquire(node);  // get current function scope
            this.actNode = this.scopeTree.add({
                position: node.range,
                scope: this.currentScope,
                variables: []
            }, this.actNode);

            //add function params to vars
            if (/Function/.test(node.type)) {
                let idsInAsParams = JSANScopeManager.extractIdentifiersFromParams(node.params);
                for (let i = 0; i < idsInAsParams.length; i++) {
                    this.actNode.data.variables.push({name: idsInAsParams[i].name, node: idsInAsParams[i]});
                }

            }
        } else if (/VariableDeclarator/.test(node.type)) {
            this.actNode.data.variables.push({name: node.id.name, node: node});
        }
    }

    leave(node) {
        if (/Function/.test(node.type) || /ClassDeclaration/.test(node.type)) {
            if (this.currentScope !== null) {
                this.currentScope = this.currentScope.upper;  // set to parent scope
            }
            this.actNode = this.actNode.parent;
        }
    }
}

export {
    JSANScopeManager
}