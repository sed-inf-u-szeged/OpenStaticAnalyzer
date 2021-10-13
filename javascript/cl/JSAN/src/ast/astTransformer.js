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

const hashmap = require('hashmap');
const addon = require('../../javascriptAddon');
const fs = require('fs');
const estraverse = require('estraverse');
const sha1 = require('sha1');
const path = require('path');
const Cache = require('lru-cache-node');

let crossRefSolver = require('../assets/crossRefSolver');
let globals = require('../globals');
let factory = globals.getFactory();

let convertNodeToFunction = function (node) {
    switch (node.type) {
        case "Program":
            return require('./base/program'); //NodeProgramFunction;
        case "EmptyStatement":
            return require('./statement/emptyStatement');
        case "BlockStatement":
            return require('./statement/blockStatement');
        case "ExpressionStatement":
            return require('./statement/expressionStatement');
        case "IfStatement":
            return require('./statement/ifStatement');
        case "LabeledStatement":
            return require('./statement/labeledStatement');
        case "BreakStatement":
            return require('./statement/breakStatement');
        case "ContinueStatement":
            return require('./statement/continueStatement');
        case "WithStatement":
            return require('./statement/withStatement');
        case "ReturnStatement":
            return require('./statement/returnStatement');
        case "SwitchStatement":
            return require('./statement/switchStatement');
        case "ThrowStatement":
            return require('./statement/throwStatement');
        case "TryStatement":
            return require('./statement/tryStatement');
        case "WhileStatement":
            return require('./statement/whileStatement');
        case "DoWhileStatement":
            return require('./statement/doWhileStatement');
        case "ForStatement":
            return require('./statement/forStatement');
        case "ForInStatement":
            return require('./statement/forInStatement');
        case "DebuggerStatement":
            return require('./statement/debuggerStatement');
        case "FunctionDeclaration":
            return require('./declaration/functionDeclaration');
        case "VariableDeclaration":
            return require('./declaration/variableDeclaration');
        case "VariableDeclarator":
            return require('./declaration/variableDeclarator');
        case "ThisExpression":
            return require('./expression/thisExpression');
        case "ArrayExpression":
            return require('./expression/arrayExpression');
        case "ObjectExpression":
            return require('./expression/objectExpression');
        case "Property":
            return require('./expression/property');
        case "AssignmentProperty":
            return require('./expression/assignmentExpression');
        case "FunctionExpression":
            return require('./expression/functionExpression');
        case "SequenceExpression":
            return require('./expression/sequenceExpression');
        case "UnaryExpression":
            return require('./expression/unaryExpression');
        case "BinaryExpression":
            return require('./expression/binaryExpression');
        case "AssignmentExpression":
            return require('./expression/assignmentExpression');
        case "UpdateExpression":
            return require('./expression/updateExpression');
        case "LogicalExpression":
            return require('./expression/logicalExpression');
        case "ConditionalExpression":
            return require('./expression/conditionalExpression');
        case "CallExpression":
            return require('./expression/callExpression');
        case "NewExpression":
            return require('./expression/newExpression');
        case "MemberExpression":
            return require('./expression/memberExpression');
        case "SwitchCase":
            return require('./statement/switchCase');
        case "CatchClause":
            return require('./statement/catchClause');
        case "Identifier":
            return require('./expression/identifier');
        case "Literal":
            return require('./expression/literal');
        case "RegExpLiteral":
            return require('./expression/regExpLiteral');
        case "YieldExpression":
            return require('./expression/yieldExpression');
        case "Super":
            return require('./expression/super');
        case "SpreadElement":
            return require('./expression/spreadElement');
        case "ArrowFunctionExpression":
            return require('./expression/arrowFunctionExpression');
        case "TaggedTemplateExpression":
            return require('./expression/taggedTemplateExpression');
        case "ClassExpression":
            return require('./expression/classExpression');
        case "TemplateLiteral":
            return require('./expression/templateLiteral');
        case "TemplateElement":
            return require('./expression/templateElement');
        case "MetaProperty":
            return require('./expression/metaProperty');
        case "ForOfStatement":
            return require('./statement/forOfStatement');
        case "AssignmentPattern":
            return require('./statement/assignmentPattern');
        case "ArrayPattern":
            return require('./statement/arrayPattern');
        case "RestElement":
            return require('./statement/restElement');
        case "ObjectPattern":
            return require('./statement/objectPattern');
        case "Line":
            return require('./base/comment');
        case "Block":
            return require('./base/comment');
        case "ImportDeclaration":
            return require('./declaration/importDeclaration');
        case "ExportNamedDeclaration":
            return require('./declaration/exportNamedDeclaration');
        case "ExportDefaultDeclaration":
            return require('./declaration/exportDefaultDeclaration');
        case "ExportAllDeclaration":
            return require('./declaration/exportAllDeclaration');
        case "ClassDeclaration":
            return require('./declaration/classDeclaration');
        case "Class":
            return require('./structure/class');
        case "ClassBody":
            return require('./structure/classBody');
        case "MethodDefinition":
            return require('./structure/methodDefinition');
        case "ImportSpecifier":
            return require('./structure/importSpecifier');
        case "ExportSpecifier":
            return require('./structure/exportSpecifier');
        case "ImportNamespaceSpecifier":
            return require('./structure/importNamespaceSpecifier');
        case "ImportDefaultSpecifier":
            return require('./structure/importDefaultSpecifier');
        case "AwaitExpression":
            return require('./expression/awaitExpression');
        default:
            console.log("Not recognized type: " + node.type + "\n");

    }
};

/**
 * Transforms the leading and trailing comments attached by Espree for a node.
 * Leading Block comment at the beginning handled as a comment for the whole program.
 * @param {type} node
 * @param {type} wrapper
 */
function handleComments(node) {
    let wrapper = globals.getWrapperOfNode(node);

    if (node.leadingComments !== undefined && node.leadingComments !== null) {
        for (let j = 0; j < node.leadingComments.length; j++) {
            if (node.leadingComments[j] !== null && node.leadingComments[j] !== undefined) {

                if (globals.isCommentExists(node.leadingComments[j])) {
                    node.leadingComments.splice(j, 1);
                    j--;
                    continue;
                }

                let leadingComment = factory.createCommentWrapper();
                leadingComment.setText(node.leadingComments[j].value);
                globals.setPositionInfo(node.leadingComments[j], leadingComment);
                leadingComment.setType("ct" + node.leadingComments[j].type);
                leadingComment.setLocation("clLeading");

                globals.addComment(node.leadingComments[j]);

                //Handle program comment at the beginning
                if (node.leadingComments[j].loc.start.line === 1 && node.leadingComments[j].type === "Block") {
                    globals.getWrapperOfNode(globals.getActualProgramNode()).addComments(leadingComment);

                    //attach this comment to the program
                    globals.getActualProgramNode().leadingComments = [];
                    globals.getActualProgramNode().leadingComments.push(node.leadingComments[j]);

                    //remove comment from the original node
                    node.leadingComments.splice(j, 1);
                    j--;
                }
                else {
                    wrapper.addComments(leadingComment);
                }
            }

        }
    }

    if (node.trailingComments !== undefined && node.trailingComments !== null) {
        for (let j = 0; j < node.trailingComments.length; j++) {
            if (node.trailingComments[j] !== null && node.trailingComments[j] !== undefined) {

                if (globals.isCommentExists(node.trailingComments[j]) || Math.abs(node.loc.end.line - node.trailingComments[j].loc.start.line) > 1) {
                    node.trailingComments.splice(j, 1);
                    j--;
                    continue;
                }

                let trailingComment = factory.createCommentWrapper();
                trailingComment.setText(node.trailingComments[j].value);
                globals.setPositionInfo(node.trailingComments[j], trailingComment);
                trailingComment.setType("ct" + node.trailingComments[j].type);
                trailingComment.setLocation("clTrailing");
                wrapper.addComments(trailingComment);

                globals.addComment(node.trailingComments[j]);
            }
        }
    }
}

/**
 * Detects all unattached comments in the file
 */
function detectUnAttachedComments(node) {
    if (!node || node.type !== 'Program') {
        return null;
    }
    //initially all the comments, then remove attached comments
    //var unattachedComments = Object.assign({}, node.comments);
    let unattachedComments = node.comments;
    for (let i = 0; i < unattachedComments.length; i++) {
        if (globals.isCommentExists(unattachedComments[i])) {
            unattachedComments.splice(i, 1);
            i--;
        }
    }
    return unattachedComments;
}


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

/**
 * Bind the references for JSAN2LIM. This method callable more.
 * The format of references see here:
 * https://github.com/Persper/js-callgraph#unified-json-format
 * @param name The name of bindings data
 * @param astSet The ColumbusStyle AST
 * @param references A JSON, which contains the links.
 */
module.exports.binder = function (name, astSet, references, type) {
    let success = 0;
    let numberOfReferences = references.length;
    let cache = new Cache(1000);
    global.binded = [];

    references.forEach(element => {
        let hash = makeHash(element);
        if(global.binded.indexOf(hash)!==-1){
            numberOfReferences--;
            return;
        }
        globals.setActualFile(element.source.file);

        let sourceFile = getFilePath(element.source.file);

        let hashSource = sha1(element.source.file+":"+element.source.range.start+":"+element.source.range.end);
        if (!cache.contains(hashSource)) {
            let wrappedNode = globals.getWrapperOfNode(crossRefSolver.resolveNode(astSet, sourceFile, element.source.range.start, element.source.range.end, true));
            cache.set(hashSource, wrappedNode || null);
        }
        let sourcenode = cache.get(hashSource);
        if (sourcenode === null) {
            return;
        }
        if (element.target.file === "Native") {
            numberOfReferences--;
            return;
        }
        globals.setActualFile(element.target.file);
        let targetFile = getFilePath(element.target.file);
        let hashTarget = sha1(element.target.file+":"+element.target.range.start+":"+element.target.range.end);
        if (!cache.contains(hashTarget)) {
            let wrappedNode = globals.getWrapperOfNode(crossRefSolver.resolveNode(astSet, targetFile, element.target.range.start, element.target.range.end, false));
            cache.set(hashTarget, wrappedNode || null);
        }
        let targetnode = cache.get(hashTarget);
        if (targetnode === null) {
            return;
        }
        try {
            if (type === "addCalls"){
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

let makeHash = function(element){
    return sha1(element.source.file+":"+element.source.range.start+":"+element.source.range.end)+sha1(element.target.file+":"+element.target.range.start+":"+element.target.range.end);
};

module.exports.variableUsages = function (astSet) {
    let vus = [];
    astSet.forEach(ast => {
        globals.setActualFile(ast.filename);
        estraverse.traverse(ast, {
            enter: function (node, parent) {
                let varUse = crossRefSolver.resolveVariableUsages(node, parent);
                if (varUse !== null) {
                    vus.push(varUse);
                }
            }
        });
    });
    return vus;
};

module.exports.variableUsages = function (astSet) {
    let vus = [];
    astSet.forEach(ast => {
        globals.setActualFile(ast.filename);
        estraverse.traverse(ast, {
            enter: function (node, parent) {
                let varUse = crossRefSolver.resolveVariableUsages(node, parent);
                if (varUse !== null) {
                    vus.push(varUse);
                }
            }
        });
    });
    return vus;
};

/**
 * Transforms the Espree AST
 *
 * @param {type} astSet: an ast created by espree
 * @param {type} parsingOptions: The espree runner configurations
 */
module.exports.transform = function (astSet, parsingOptions) {
    astSet.forEach(ast => {
        globals.setActualFile(ast.filename);
        //first traverse
        crossRefSolver.setParsingOptions(parsingOptions);
        estraverse.traverse(ast, {
            enter: function (node, parent) {
                let func = convertNodeToFunction(node);
                if (func !== undefined) {
                    let nodeWrapper = func(node, parent, true);
                    if (nodeWrapper !== undefined) {
                        globals.putNodeWrapperPair(node, nodeWrapper);
                    }
                }
                //gathering the scopes and the identifiers located in them
                crossRefSolver.gatherScopes(ast, node, "enter");
            },
            leave: function (node, parent) {
                crossRefSolver.gatherScopes(ast, node, "leave");
            }
        });
    });

    astSet.forEach(ast => {
        globals.setActualFile(ast.filename);
        //second traverse
        estraverse.traverse(ast, {
            enter: function (node, parent) {
                let func = convertNodeToFunction(node);
                if (func !== undefined) {
                    func(node, parent, false);

                }
                //handle comments
                handleComments(node);
            },
            leave: function (node, parent) {
                if (node.type === 'Program') {
                    let comments = detectUnAttachedComments(node);

                    //create these unattached comments and attach them to the program
                    for (let i = 0; i < comments.length; i++) {
                        let comment = factory.createCommentWrapper();
                        comment.setText(comments[i].value);
                        globals.setPositionInfo(comments[i], comment);
                        comment.setType("ct" + comments[i].type);
                        comment.setLocation("clTrailing");
                        let programWrapper = globals.getWrapperOfNode(node);
                        programWrapper.addComments(comment);

                        if (node.loc.end.line < comments[i].loc.start.line || (node.loc.end.line === comments[i].loc.start.line && node.loc.end.column < comments[i].loc.start.column)) {
                            programWrapper.setPosition({
                                'endline': comments[i].loc.end.line,
                                'endcol': comments[i].loc.end.column,
                                'wideendline': comments[i].loc.end.line,
                                'wideendcol': comments[i].loc.end.column
                            });
                        }
                    }
                }
            }
        });
    });
};

module.exports.saveAST = function (filename, dumpjsml) {
    factory.saveAST(filename + ".jssi", dumpjsml);
};
