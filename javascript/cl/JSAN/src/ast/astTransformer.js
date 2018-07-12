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

var crossRefSolver = require('../assets/crossRefSolver');
var globals = require('../globals');
var factory = globals.getFactory();


var convertNodeToFunction = function (node) {
    switch (node.type) {
        case "Program":
            return require('./base/program')//NodeProgramFunction;
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
            return require('./declaration/ImportDeclaration');
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
    var wrapper = globals.getWrapperOfNode(node);


    if (node.leadingComments != null) {
        for (var j = 0; j < node.leadingComments.length; j++) {
            if (node.leadingComments[j] != null && node.leadingComments[j] != undefined) {

                if (globals.isCommentExists(node.leadingComments[j])) {
                    node.leadingComments.splice(j, 1);
                    j--;
                    continue;
                }

                var leadingComment = factory.createCommentWrapper(factory);
                leadingComment.setText(node.leadingComments[j].value);
                globals.setPositionInfo(node.leadingComments[j], leadingComment);
                leadingComment.setType("ct" + node.leadingComments[j].type);
                leadingComment.setLocation("clLeading");

                globals.addComment(node.leadingComments[j]);

                //Handle program comment at the beginning
                if (node.leadingComments[j].loc.start.line == 1 && node.leadingComments[j].type === "Block") {
                    globals.getWrapperOfNode(globals.getActualProgramNode()).addCommentsComment(leadingComment);

                    //attach this comment to the program
                    globals.getActualProgramNode().leadingComments = [];
                    globals.getActualProgramNode().leadingComments.push(node.leadingComments[j]);

                    //remove comment from the original node
                    node.leadingComments.splice(j, 1);
                    j--;
                }
                else {
                    wrapper.addCommentsComment(leadingComment);
                }
            }

        }
    }


    if (node.trailingComments != null) {
        for (var j = 0; j < node.trailingComments.length; j++) {
            if (node.trailingComments[j] != null && node.trailingComments[j] != undefined) {

                if (globals.isCommentExists(node.trailingComments[j]) || Math.abs(node.loc.end.line - node.trailingComments[j].loc.start.line) > 1) {
                    node.trailingComments.splice(j, 1);
                    j--;
                    continue;
                }


                var trailingComment = factory.createCommentWrapper(factory);
                trailingComment.setText(node.trailingComments[j].value);
                globals.setPositionInfo(node.trailingComments[j], trailingComment);
                trailingComment.setType("ct" + node.trailingComments[j].type);
                trailingComment.setLocation("clTrailing");
                wrapper.addCommentsComment(trailingComment);

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
    var unattachedComments = node.comments;
    for (var i = 0; i < unattachedComments.length; i++) {
        if (globals.isCommentExists(unattachedComments[i])) {
            unattachedComments.splice(i, 1);
            i--;
        }
    }

    return unattachedComments;
}


/**
 * Transforms the Espree AST into columbus AST
 *
 * @param {type} espreeAst: an ast created by espree
 */
module.exports.transform = function (ast, parsingOptions) {
    //first traverse
	crossRefSolver.setParsingOptions(parsingOptions);
    estraverse.traverse(ast, {
        enter: function (node, parent) {
            var func = convertNodeToFunction(node);
            if (func !== undefined) {
                var nodeWrapper = func(node, parent, true);
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

    //second traverse
    estraverse.traverse(ast, {
        enter: function (node, parent) {

            var func = convertNodeToFunction(node);
            if (func !== undefined) {
                func(node, parent, false);
            }
            //handle comments
            handleComments(node);

            crossRefSolver.resolveCrossRefs(node, parent);
        },
        leave: function (node, parent) {
            if (node.type === 'Program') {
                var comments = detectUnAttachedComments(node);

                //create these unattached comments and attach them to the program
                for (var i = 0; i < comments.length; i++) {
                    var comment = factory.createCommentWrapper(factory);
                    comment.setText(comments[i].value);
                    globals.setPositionInfo(comments[i], comment);
                    comment.setType("ct" + comments[i].type);
                    comment.setLocation("clTrailing");
                    var programWrapper = globals.getWrapperOfNode(node);
                    programWrapper.addCommentsComment(comment);

                    if (node.loc.end.line < comments[i].loc.start.line || (node.loc.end.line === comments[i].loc.start.line && node.loc.end.column < comments[i].loc.start.column)) {
                        programWrapper.setEndLine(comments[i].loc.end.line);
                        programWrapper.setEndCol(comments[i].loc.end.column);
                        programWrapper.setWideEndLine(comments[i].loc.end.line);
                        programWrapper.setWideEndCol(comments[i].loc.end.column);
                    }

                }
            }
        }

    });


};


module.exports.saveAST = function (filename, dumpjsml) {
    factory.saveAST(filename + ".jssi", dumpjsml);
};


