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

import {walk} from 'estree-walker';
import * as path from 'path';
import * as globals from '../globals.js';
import * as varUsages from '../assets/varUsages.js'
import * as scopeManager from '../assets/scopeManager.js'
import * as conversions from './conversions.js';

import {default as sha1} from 'sha1';

import {default as Cache} from 'lru-cache-node';

import {default as program} from "./base/program.js";

import {default as classDeclaration} from "./declaration/classDeclaration.js";
import {default as exportAllDeclaration} from "./declaration/exportAllDeclaration.js";
import {default as exportDefaultDeclaration} from "./declaration/exportDefaultDeclaration.js";
import {default as exportNamedDeclaration} from "./declaration/exportNamedDeclaration.js";
import {default as functionDeclaration} from "./declaration/functionDeclaration.js";
import {default as importDeclaration} from "./declaration/importDeclaration.js";
import {default as variableDeclaration} from "./declaration/variableDeclaration.js";
import {default as variableDeclarator} from "./declaration/variableDeclarator.js";

import {default as arrayExpression} from "./expression/arrayExpression.js";
import {default as arrowFunctionExpression} from "./expression/arrowFunctionExpression.js";
import {default as assignmentExpression} from "./expression/assignmentExpression.js";
import {default as awaitExpression} from "./expression/awaitExpression.js";
import {default as binaryExpression} from "./expression/binaryExpression.js";
import {default as callExpression} from "./expression/callExpression.js";
import {default as chainExpression} from "./expression/chainExpression.js";
import {default as classExpression} from "./expression/classExpression.js";
import {default as conditionalExpression} from "./expression/conditionalExpression.js";
import {default as functionExpression} from "./expression/functionExpression.js";
import {default as identifier} from "./expression/identifier.js";
import {default as importExpression} from "./expression/importExpression.js";
import {default as literal} from "./expression/literal.js";
import {default as logicalExpression} from "./expression/logicalExpression.js";
import {default as memberExpression} from "./expression/memberExpression.js";
import {default as metaProperty} from "./expression/metaProperty.js";
import {default as newExpression} from "./expression/newExpression.js";
import {default as objectExpression} from "./expression/objectExpression.js";
import {default as property} from "./expression/property.js";
import {default as privateIdentifier} from "./expression/privateIdentifier.js";
import {default as regExpLiteral} from "./expression/regExpLiteral.js";
import {default as sequenceExpression} from "./expression/sequenceExpression.js";
import {default as spreadElement} from "./expression/spreadElement.js";
import {default as superExp} from "./expression/super.js";
import {default as taggedTemplateExpression} from "./expression/taggedTemplateExpression.js";
import {default as templateElement} from "./expression/templateElement.js";
import {default as templateLiteral} from "./expression/templateLiteral.js";
import {default as thisExpression} from "./expression/thisExpression.js";
import {default as unaryExpression} from "./expression/unaryExpression.js";
import {default as updateExpression} from "./expression/updateExpression.js";
import {default as yieldExpression} from "./expression/yieldExpression.js";

import {default as arrayPattern} from "./statement/arrayPattern.js";
import {default as assignmentPattern} from "./statement/assignmentPattern.js";
import {default as blockStatement} from "./statement/blockStatement.js";
import {default as breakStatement} from "./statement/breakStatement.js";
import {default as catchClause} from "./statement/catchClause.js";
import {default as continueStatement} from "./statement/continueStatement.js";
import {default as debuggerStatement} from "./statement/debuggerStatement.js";
import {default as doWhileStatement} from "./statement/doWhileStatement.js";
import {default as emptyStatement} from "./statement/emptyStatement.js";
import {default as expressionStatement} from "./statement/expressionStatement.js";
import {default as forInStatement} from "./statement/forInStatement.js";
import {default as forOfStatement} from "./statement/forOfStatement.js";
import {default as forStatement} from "./statement/forStatement.js";
import {default as ifStatement} from "./statement/ifStatement.js";
import {default as labeledStatement} from "./statement/labeledStatement.js";
import {default as objectPattern} from "./statement/objectPattern.js";
import {default as restElement} from "./statement/restElement.js";
import {default as returnStatement} from "./statement/returnStatement.js";
import {default as switchCase} from "./statement/switchCase.js";
import {default as switchStatement} from "./statement/switchStatement.js";
import {default as throwStatement} from "./statement/throwStatement.js";
import {default as tryStatement} from "./statement/tryStatement.js";
import {default as whileStatement} from "./statement/whileStatement.js";
import {default as withStatement} from "./statement/withStatement.js";

import {default as classStructure} from "./structure/class.js";
import {default as classBody} from "./structure/classBody.js";
import {default as exportSpecifier} from "./structure/exportSpecifier.js";
import {default as importDefaultSpecifier} from "./structure/importDefaultSpecifier.js";
import {default as importNamespaceSpecifier} from "./structure/importNamespaceSpecifier.js";
import {default as importSpecifier} from "./structure/importSpecifier.js";
import {default as methodDefinition} from "./structure/methodDefinition.js";
import {default as propertyDefinition} from "./structure/propertyDefinition.js";

let factory = globals.getFactory();


let convertNodeToFunction = function (node) {
    switch (node.type) {
        case "Program":
            return program //NodeProgramFunction;
        case "EmptyStatement":
            return emptyStatement;
        case "BlockStatement":
            return blockStatement;
        case "ExpressionStatement":
            return expressionStatement;
        case "IfStatement":
            return ifStatement;
        case "LabeledStatement":
            return labeledStatement;
        case "BreakStatement":
            return breakStatement;
        case "ContinueStatement":
            return continueStatement;
        case "WithStatement":
            return withStatement;
        case "ReturnStatement":
            return returnStatement;
        case "SwitchStatement":
            return switchStatement;
        case "ThrowStatement":
            return throwStatement;
        case "TryStatement":
            return tryStatement;
        case "WhileStatement":
            return whileStatement;
        case "DoWhileStatement":
            return doWhileStatement;
        case "ForStatement":
            return forStatement;
        case "ForInStatement":
            return forInStatement;
        case "DebuggerStatement":
            return debuggerStatement;
        case "FunctionDeclaration":
            return functionDeclaration;
        case "VariableDeclaration":
            return variableDeclaration;
        case "VariableDeclarator":
            return variableDeclarator;
        case "ChainExpression":
            return chainExpression;
        case "ImportExpression":
            return importExpression;
        case "ThisExpression":
            return thisExpression;
        case "ArrayExpression":
            return arrayExpression;
        case "ObjectExpression":
            return objectExpression;
        case "Property":
            return property;
        case "FunctionExpression":
            return functionExpression;
        case "SequenceExpression":
            return sequenceExpression;
        case "UnaryExpression":
            return unaryExpression;
        case "BinaryExpression":
            return binaryExpression;
        case "AssignmentExpression":
            return assignmentExpression;
        case "UpdateExpression":
            return updateExpression;
        case "LogicalExpression":
            return logicalExpression;
        case "ConditionalExpression":
            return conditionalExpression;
        case "CallExpression":
            return callExpression;
        case "NewExpression":
            return newExpression;
        case "MemberExpression":
            return memberExpression;
        case "SwitchCase":
            return switchCase;
        case "CatchClause":
            return catchClause;
        case "Identifier":
            return identifier;
        case "Literal":
            return literal;
        case "RegExpLiteral":
            return regExpLiteral;
        case "YieldExpression":
            return yieldExpression;
        case "Super":
            return superExp;
        case "SpreadElement":
            return spreadElement;
        case "ArrowFunctionExpression":
            return arrowFunctionExpression;
        case "TaggedTemplateExpression":
            return taggedTemplateExpression;
        case "ClassExpression":
            return classExpression;
        case "TemplateLiteral":
            return templateLiteral;
        case "TemplateElement":
            return templateElement;
        case "MetaProperty":
            return metaProperty;
        case "ForOfStatement":
            return forOfStatement;
        case "AssignmentPattern":
            return assignmentPattern;
        case "ArrayPattern":
            return arrayPattern;
        case "RestElement":
            return restElement;
        case "ObjectPattern":
            return objectPattern;
        case "ImportDeclaration":
            return importDeclaration;
        case "ExportNamedDeclaration":
            return exportNamedDeclaration;
        case "ExportDefaultDeclaration":
            return exportDefaultDeclaration;
        case "ExportAllDeclaration":
            return exportAllDeclaration;
        case "ClassDeclaration":
            return classDeclaration;
        case "Class":
            return classStructure;
        case "ClassBody":
            return classBody;
        case "MethodDefinition":
            return methodDefinition;
        case "ImportSpecifier":
            return importSpecifier;
        case "ExportSpecifier":
            return exportSpecifier;
        case "ImportNamespaceSpecifier":
            return importNamespaceSpecifier;
        case "ImportDefaultSpecifier":
            return importDefaultSpecifier;
        case "AwaitExpression":
            return awaitExpression;
        case "ClassProperty": // TODO: Remove this once parser correctly handles PropertyDefinitions
        case "PropertyDefinition":
            return propertyDefinition;
        case "PrivateIdentifier":
        case "TSPrivateIdentifier": // TODO: Remove this once parser correctly handles private identifiers
            return privateIdentifier;
        case "Line":
        case "Block":
            /*
                Intentionally ignored types
             */
            break;
        default:
            console.log("Could not recognize type: " + node.type);
    }
};

/**
 * Gets the absolute or relative path of a file path.
 * @param filePath
 */
function getFilePath(filePath) {
    if (globals.getOption('useRelativePath') && path.isAbsolute(filePath)) {
        return path.relative(process.cwd(), filePath);
    }
    return filePath;
}

function createASGNode(node, parent) {
    let func = convertNodeToFunction(node);
    if (func !== undefined) {
        let nodeWrapper = func(node, parent, true);
        if (nodeWrapper !== undefined) {
            globals.putNodeWrapperPair(node, nodeWrapper);
        }
    }
}

/**
 * Transforms the Espree AST
 *
 * @param {type} astSet: an ast created by espree
 * @param {type} parsingOptions: The espree runner configurations
 */
let transform = function (astSet, parsingOptions) {
    astSet.forEach(ast => {
        globals.setActualFile(ast.filename);
        //first traverse

        walk(ast, {
            enter: function (node, parent) {
                createASGNode(node, parent);
            }
        });
    });
    astSet.forEach(ast => {
        globals.setActualFile(ast.filename);

        //second traverse
        walk(ast, {
            enter: function (node, parent) {
                // console.log(node.type);
                handleComments(node);
                let func = convertNodeToFunction(node);

                if (func !== undefined) {
                    func(node, parent, false);
                }
            },
            // leave: function (node, parent) {
            //     console.log("Leaving node type " + node.type)
            // }
        });
    });
    console.log("Transform finished!");
};

let handleComments = function (node) {
    if (node.comments) {
        for (let comment of node.comments) {
            const commentWrapper = factory.createCommentWrapper();
            commentWrapper.setText(comment.value);
            commentWrapper.setType(conversions.convertCommentType(comment.type));
            commentWrapper.setLocation(conversions.convertCommentLocation(comment));
            globals.setPositionInfo(comment, commentWrapper);
            const nodeWrapper = globals.getWrapperOfNode(node);
            if (nodeWrapper !== undefined) {
                nodeWrapper.addComments(commentWrapper);
            } else {
                console.log("Cannot add comments to undefined node.")
            }
        }
    }
}

let saveAST = function (filename, dumpjsml) {
    factory.saveAST(filename + ".jssi", dumpjsml);
};


function variableUsages(astSet) {
    let vus = [];
    astSet.forEach(ast => {
        const sm = new scopeManager.JSANScopeManager()

        //TODO: Move this?
        walk(ast, {
            enter: (node, parent) => {
                sm.enter(ast, node);
            },
            leave: (node, parent) => {
                sm.leave(node);
            }
        })

        globals.setActualFile(ast.filename);
        walk(ast, {
            enter: function (node, parent) {
                let varUse = varUsages.resolveVariableUsages(node, parent, sm);
                if (varUse !== null) {
                    vus.push(varUse);
                }
            }
        });
    });
    return vus;
}


let makeHash = function (element) {
    return sha1(element.source.file + ":" + element.source.range.start + ":" + element.source.range.end) + sha1(element.target.file + ":" + element.target.range.start + ":" + element.target.range.end);
};


let resolveNode = function (ast, filename, range_start, range_end, inner = false) {
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
        walk(astNode, {
            enter: function (node) {
                if (status) {
                    if (inner) { // return the most inner node
                        if (node.range[0] !== searchNode.range.start || node.range[1] !== searchNode.range.end) {
                            return;
                        }
                    } else { // return the most outer node
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

/**
 * Bind the references for JSAN2LIM. This method callable more.
 * The format of references see here:
 * https://github.com/Persper/js-callgraph#unified-json-format
 * @param name The name of bindings data
 * @param astSet The ColumbusStyle AST
 * @param references A JSON, which contains the links.
 * @param type
 */
const binder = function (name, astSet, references, type) {
    let success = 0;
    let numberOfReferences = references.length;
    let cache = new Cache(1000);
    global.binded = [];

    references.forEach(element => {
        let hash = makeHash(element);
        if (global.binded.indexOf(hash) !== -1) {
            numberOfReferences--;
            return;
        }
        globals.setActualFile(element.source.file);

        let sourceFile = getFilePath(element.source.file);

        let hashSource = sha1(element.source.file + ":" + element.source.range.start + ":" + element.source.range.end);
        if (!cache.contains(hashSource)) {
            let wrappedNode = globals.getWrapperOfNode(resolveNode(astSet, sourceFile, element.source.range.start, element.source.range.end, true));
            cache.set(hashSource, wrappedNode || null);
        }
        let sourcenode = cache.get(hashSource);
        if (sourcenode === null) {
            return;
        }
        // Only for cross-ref binding
        if (element.target.file === "Native") {
            numberOfReferences--;
            return;
        }
        globals.setActualFile(element.target.file);
        let targetFile = getFilePath(element.target.file);
        let hashTarget = sha1(element.target.file + ":" + element.target.range.start + ":" + element.target.range.end);
        if (!cache.contains(hashTarget)) {
            let wrappedNode = globals.getWrapperOfNode(resolveNode(astSet, targetFile, element.target.range.start, element.target.range.end, false));
            cache.set(hashTarget, wrappedNode || null);
        }
        let targetnode = cache.get(hashTarget);
        if (targetnode === null) {
            return;
        }
        try {
            if (type === "addCalls") {
                sourcenode.addCalls(targetnode);
            } else if (type === "setRefersTo") {
                sourcenode.setRefersTo(targetnode);
            } else {
                console.log("Not implemented yet!");
            }
            //eval("sourcenode."+type+"(targetnode);");
            global.binded.push(hash);
            success++;
        } catch (e) {
            console.log(e);
        }
    });
    console.log("Binding " + name + ": " + success + "/" + numberOfReferences);
};


export {
    createASGNode,
    transform,
    saveAST,
    variableUsages,
    binder,
}
