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
const addon = require('../javascriptAddon');
const path = require('path');


var nodeAndWrapperMap = new hashmap();
var actualFile = undefined;
var factory = new addon.Factory();
var options = undefined;
var actualProgramNode = null;
var commentMap = new hashmap();

module.exports.addComment = function(comment){
    commentMap.set(comment.loc, comment);
};

module.exports.isCommentExists = function(comment){
    return  commentMap.has(comment.loc);
};

module.exports.clearCommentMap = function(){
    commentMap.clear();
};

module.exports.getActualProgramNode = function () {
    return actualProgramNode;
};

module.exports.setActualProgramNode = function (node) {
    actualProgramNode = node;
};

module.exports.setActualFile = function (filename) {
    actualFile = filename;
};

module.exports.getActualFile = function () {
    return actualFile;
};

module.exports.getFactory = function () {
    return factory;
};

module.exports.putNodeWrapperPair = function (node, wrapper) {
    nodeAndWrapperMap.set(node, wrapper);
};

module.exports.getWrapperOfNode = function (node) {
    return nodeAndWrapperMap.get(node);//returns the wrapper
};

module.exports.setOptions = function (opt) {
    options = opt;
};

module.exports.getOptions = function () {
    return options;
};

module.exports.getOption = function (obj) {
    if (options !== undefined)
        if (obj in options)
            return options[obj];
    return false;
};


module.exports.setPositionInfo = function (node, wrapper) {
    try {
        if (options.useRelativePath) {
            wrapper.setPath(path.relative(process.cwd(), actualFile));
        }
        else {
            wrapper.setPath(actualFile);
        }

        //A JS file always starts from 1,1 (line, column)
        if (node.type === "Program") {
            wrapper.setLine(1);
            wrapper.setCol(1);
            wrapper.setWideLine(1);
            wrapper.setWideCol(1);
        }
        else {
            wrapper.setLine(node.loc.start.line);
            wrapper.setCol(node.loc.start.column);
            wrapper.setWideLine(node.loc.start.line);
            wrapper.setWideCol(node.loc.start.column);
        }

        wrapper.setEndLine(node.loc.end.line);
        wrapper.setEndCol(node.loc.end.column);
        wrapper.setWideEndLine(node.loc.end.line);
        wrapper.setWideEndCol(node.loc.end.column);
    } catch (e) {
        console.error(node.type + " - Position cannot be set! Reason of the error: " + e + "\n");
    }
};


module.exports.getLiteralType = function (node) {
    if (typeof (node.value) !== "object") {
        var type = typeof (node.value);
        return type.charAt(0).toLocaleUpperCase() + type.substring(1, type.length);
    } else {
        if (node.raw === "null") {
            return "Null";
        } else if (node.regex != null) {
            return "RegExp";
        }
    }

};
