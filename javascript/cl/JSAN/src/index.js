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

import * as clOptions from './assets/options.js';
import * as tsEstree from '@typescript-eslint/typescript-estree';
import * as globals from './globals.js';
import * as htmlExtractor from './assets/htmlExtractor.js';
import {attachComments} from "estree-util-attach-comments";

import * as fs from 'fs';
import * as path from 'path';
import * as astTransformer from './ast/astTransformer.js';
import {trimHashbang} from "./util/util.js";

// const jcg = require('jscg');
import * as jcg from 'jscg';

const NODEJS_MINIMUM_VERSION = 12;

globals.setOptions(clOptions.parse());

class Memory {
    static init() {
        this.used = process.memoryUsage().heapUsed / 1024 / 1024;
        this.peak = this.used;
    }

    static check() {
        this.used = process.memoryUsage().heapUsed / 1024 / 1024;
        if (this.used > this.peak) {
            this.peak = this.used;
        }
        return this.used;
    }

    static result() {
        return this.peak;
    }
}

Memory.init();

/**
 * This method make the parsing with Espree
 * and generate the raw of AST.
 * @param code The path of the parsable file
 * @param type The code, what we want parse
 * @returns {*} The result of parsing
 */
let parsingOptions;
let parseCode = function (filePath, code, type) {
    const options = {
        filePath: filePath,
        sourceType: type,
        comment: true,
        loc: true,
        tokens: false,
        range: true,
        //ecmaVersion: 2020,
    };

    try {
        let rawAst = tsEstree.parse(code, options);
        console.log("Succesfully parsed as " + type + ": " + filePath.absolute);
        rawAst = attachComments(rawAst, rawAst.comments);
        //fs.writeFileSync('ast.json', JSON.stringify(rawAst, null, 4));

        return {success: true, ast: rawAst, options: options, sourceType: type};
    } catch (e) {
        if (type !== 'script') {
            console.log("Failed to parse as " + type + ": " + filePath.absolute);
            console.error(e);
            console.log("Trying to parse as script.");
            return parseCode(filePath, code, 'script');
        } else {
            console.log("Failed to parse: " + filePath.absolute);
            console.error(e);
            return {success: false, error: e};
        }
    }

};

/**
 * This method start the parsing of the code,
 * create the ast format json and concatenate
 * the filename.
 * @param filePath The path of analyzeable file
 * @param code The code, what we want parse
 * @returns {number|*}
 */
let makeAstFromCode = function (filePath, code) {
    const rawAst = parseCode(filePath, code, 'module');
    Memory.check();
    if (rawAst.success) {
        parsingOptions = rawAst.options;
        let ast = rawAst.ast;
        ast.filename = globals.getOption('useRelativePath') ? filePath.relative : filePath.absolute;
        ast.sourceType = rawAst.sourceType;
        return ast;
    } else {
        throw new Error('The parsing of code was unsuccessful: ' + rawAst.error);
    }
};

/**
 * This method start the analyze, transform the ast
 * and return with results.
 * @param filePath The path of analyzing file
 * @param code The code, what we want analyze
 * @returns {*}
 */
let makeAnalyzeCodeResult = function (filePath, code) {
    try {
        Memory.check();
        let ast = makeAstFromCode(filePath, code);
        return {success: true, ast: ast};
    } catch (e) {
        return {success: false, error: e};
    }
};

/**
 * The loadCode method traverse the files, which
 * we gave in parameter and on each file start the
 * analyzing.
 *
 * @param files The list of the analyzing files.
 * @returns {{result: Array}}
 */
function loadCode(files) {
    console.time('Total time of loading code');
    let result = [];
    Memory.check();
    let successfullyParsedFiles = [];
    files.forEach(function (file) {
        let filePath;
        if (path.isAbsolute(file)) {
            filePath = {
                absolute: path.normalize(file),
                relative: path.relative(process.cwd(), file)
            };
        } else {
            filePath = {
                absolute: path.join(process.cwd(), file),
                relative: path.normalize(file)
            };
        }

        let code;

        globals.setActualFile(globals.getOption('useRelativePath') ? filePath.relative : filePath.absolute);

        if (!fs.existsSync(filePath.relative)) {
            console.log(filePath.absolute + " does not exists. It will be omitted from the analysis");
            return;
        }

        if (globals.supportedExts.includes(path.extname(filePath.relative)) && path.extname(filePath.relative) !== ".html") {
            if (path.extname(filePath.relative) === '.ts') {
                console.log("TypeScript parsing is currently in experimental phase.")
            }
            try {
                code = fs.readFileSync(filePath.absolute);
                code = String(code);
            } catch (err) {
                console.log("Error while loading the code from file: " + filePath.absolute);
                console.log(err);
                return;
            }
        } else if (path.extname(filePath.relative) === '.html') {
            code = htmlExtractor.extractJSToString(filePath.relative);
            Memory.check();
        }

        // Preprocessing steps
        const preprocessors = [trimHashbang];
        preprocessors.forEach(function (preprocessorFunction) {
            code = preprocessorFunction(code);
        });

        let analyzeResult = makeAnalyzeCodeResult(filePath, code);
        if (analyzeResult.success) {
            if (analyzeResult.ast.sourceType === 'module') {
                successfullyParsedFiles.push(filePath.absolute);
            }
            result.push(analyzeResult.ast);
        } else {
            console.error(analyzeResult.error);
        }
    });
    Memory.check();
    console.timeEnd('Total time of loading code');
    return {result: result, successfullyParsedFiles: successfullyParsedFiles};
}

/**
 * This method save the result into AST file.
 * @param target The target file of result
 */
function saveToAST(target) {
    "use strict";
    astTransformer.saveAST(target, globals.getOption('dumpjsml'));
}

/**
 * Analysis
 * This method will actually analyze to source code
 */
function analysis() {
    if (!globals.getOption('inputList')) {
        return;
    }
    Memory.check();
    let resultOfAnalyze = loadCode(globals.getOption('inputList'));
    let successfullyParsedFiles = resultOfAnalyze.successfullyParsedFiles;
    Memory.check();
    if (successfullyParsedFiles.length === 0) {
        console.log("CrossReference binding is being skipped as there are no modules in the input.");
    } else {
        let resultOfACG = undefined;
        try {
            console.time("ACG");
            //jcg.setFiles(globals.getOption('inputList'));
            jcg.setFiles(successfullyParsedFiles);
            jcg.setArgs({
                fg: undefined,
                cg: [],
                time: undefined,
                strategy: 'ONESHOT',
                countCB: undefined,
                reqJs: undefined,
                output: undefined,
                filter: undefined
            });
            jcg.setConsoleOutput(false);
            resultOfACG = jcg.build();

        } catch (err) {
            console.log("Something bad happened while running JSCG");
            console.log(err)
        } finally {
            console.timeEnd("ACG");
            Memory.check();
        }
        try {
            // Transform raw results
            astTransformer.transform(resultOfAnalyze.result, parsingOptions);
            Memory.check();

            // Variable usage
            let resultOfVU = astTransformer.variableUsages(resultOfAnalyze.result);
            Memory.check();
            astTransformer.binder("VU", resultOfAnalyze.result, resultOfVU, "setRefersTo");
            Memory.check();

            // Bind cross references
            if (resultOfACG !== undefined) {
                astTransformer.binder("ACG", resultOfAnalyze.result, resultOfACG, "addCalls");
                Memory.check();
            } else {
                console.log("Binding JSCG was skipped due to a previous error.")
            }
        } catch (e) {
            console.warn(e);
        }
    }

    saveToAST(globals.getOption('out'));
    Memory.check();
}

/**
 * Analysis wrapper
 * This wrapper will measure memory usage and elapsed time.
 */
function wrappedAnalysis() {
    "use strict";
    const start = process.hrtime();

    analysis();
    Memory.check();
    const elapsed = process.hrtime(start);
    const sec = elapsed[0] + (elapsed[1] / 1e9);

    console.log('Total time of JSAN was %d s.', sec);
    console.log('Peak memory usage was %f MB', Memory.result());

    const csv = [
        'Run time (s);Peak memory usage (MB)',
        sec + ';' + Memory.result()
    ];

    fs.writeFile(globals.getOption('stat'), csv.join('\n'), function (err) {
        if (err) throw err;
    });
}

/**
 * Entry point
 *
 * Here we will decide whether statistics needed or not.
 */
function analyzeMain() {
    "use strict";

    const currentNodeVersion = process.version.split(".")[0].substring(1);
    if (currentNodeVersion < NODEJS_MINIMUM_VERSION) {  // check Node.js version
        console.log("Failed to start JSAN as the minimum required Node.js version cannot be found!");
        console.log("Minimum version: " + NODEJS_MINIMUM_VERSION);
        console.log("Your version: " + currentNodeVersion);
        process.exit(6633);
    }
    if (globals.getOption('stat')) {
        wrappedAnalysis();
    } else {
        analysis();
    }
}

try {
    analyzeMain();
    console.log("JSAN finished!")
} catch (e) {
    console.log(e);
}

