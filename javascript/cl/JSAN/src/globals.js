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

import {default as hashmap} from 'hashmap';
import * as path from 'path';
import * as addon from '../javascriptAddon.node';

let nodeAndWrapperMap = new hashmap();
let actualFile = undefined;
let factory = new addon.Factory();
let options = undefined;
let actualProgramNode = null;

/**
 * Supported extensions by JSAN
 * @type {string[]}
 */
const supportedExts = [
    ".js",
    ".ts",
    ".html",
]


let getActualProgramNode = function () {
    return actualProgramNode;
};

let setActualProgramNode = function (node) {
    actualProgramNode = node;
};

let setActualFile = function (filename) {
    actualFile = filename;
};

let getActualFile = function () {
    return actualFile;
};

let getFactory = function () {
    return factory;
};

let putNodeWrapperPair = function (node, wrapper) {
    nodeAndWrapperMap.set(node, wrapper);
};

let getWrapperOfNode = function (node) {
    return nodeAndWrapperMap.get(node); //returns the wrapper
};

let setOptions = function (opt) {
    options = opt;
};

let getOptions = function () {
    return options;
};

let getOption = function (obj) {
    if (options !== undefined)
        if (obj in options) {
            return options[obj];
        }
    return false;
};

let setPositionInfo = function (node, wrapper) {
    try {
        if (options.useRelativePath) {
            wrapper.setPath(path.relative(process.cwd(), actualFile));
        } else {
            wrapper.setPath(actualFile);
        }

        //A JS file always starts from 1,1 (line, column)
        if (node.type === "Program") {
            wrapper.setPosition(1, 0, node.loc.end.line, node.loc.end.column, 1, 0, node.loc.end.line, node.loc.end.column);
        } else {
            wrapper.setPosition(
                node.loc.start.line,
                node.loc.start.column,
                node.loc.end.line,
                node.loc.end.column,
                node.loc.start.line,
                node.loc.start.column,
                node.loc.end.line,
                node.loc.end.column
            );
        }

    } catch (e) {
        console.error(node.type + " - Position cannot be set! Reason of the error: " + e + "\n");
    }
};

let getLiteralType = function (node) {
    if (typeof (node.value) !== "object") {
        const type = typeof (node.value);
        return type.charAt(0).toLocaleUpperCase() + type.substring(1, type.length);
    } else {
        if (node.raw === "null") {
            return "Null";
        } else if (node.regex != null) {
            return "RegExp";
        }
    }

};

const safeSet = function (setFunctionContext, functionName, nodeToWrap, errorMessage) {
    const wrappedNode = getWrapperOfNode(nodeToWrap);
    if (wrappedNode !== undefined) {
        try {
            // setFunction(wrappedNode);
            setFunctionContext[functionName](wrappedNode);
        } catch (e) {
            console.error(`${errorMessage}. Reason of the error: ${e}\n`);
        }
    }
}
//
// const safeSet = function (setFunction, nodeToWrap, errorMessage) {
//     const wrappedNode = getWrapperOfNode(nodeToWrap);
//     if (wrappedNode !== undefined) {
//         try {
//             setFunction(wrappedNode);
//         } catch (e) {
//             console.error(`${errorMessage}. Reason of the error: ${e}\n`);
//         }
//     }
// }


export {
    getActualProgramNode,
    setActualProgramNode,
    setActualFile,
    getActualFile,
    getFactory,
    putNodeWrapperPair,
    getWrapperOfNode,
    setOptions,
    getOptions,
    getOption,
    setPositionInfo,
    getLiteralType,
    safeSet,
    supportedExts
}
