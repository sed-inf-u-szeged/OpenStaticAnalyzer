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

const clOptions = require('./src/assets/options');
const htmlExtractor = require('./src/assets/htmlExtractor');
const astTransformer = require('./src/ast/astTransformer');
const fs = require('fs');
const espree = require('espree');
const path = require('path');
const JSONStream = require('JSONStream');
const jcg = require('@persper/js-callgraph/src/runner');

let globals = require('./src/globals');

const NODEJS_MINIMUM_VERSION = 8;

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
        sourceType: type,
        comment: true,
        tolerant: true,
        loc: true,
        raw: true,
        tokens: true,
        range: true,
        ecmaVersion: 2018,
        attachComment: true,
    };

    try {
        let rawAst = espree.parse(code, options);
        console.log("Succesfully parsed as " + type + ": " + filePath.absolute);
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
 * Trim shebang to avoid parse error
 * Doing it this way will preserve the original absolute positions
 * This snippet is taken from: https://github.com/jquery/esprima/issues/1151#issuecomment-85706244
 * @param code the loaded code that might include starting shebang
 * @returns the stripped source code
 */
function trimHashbang(code) {
    if (code.substring(0, 2) === '#!') {
        let end = code.indexOf('\n');
        let filler = '';
        for (let i = 0; i < end; ++i) {
           filler += ' ';
        }
        code = filler + code.substring(end, code.length);
        console.log("Leading shebang was removed");
    }
    return code;
}

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
        let filePath = {
            absolute: null,
            relative: null
        };
        if (path.isAbsolute(file)) {
            filePath = {
                absolute: path.normalize(file),
                relative: path.relative(process.cwd(), file)
            };
        }
        else {
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

        if (path.extname(filePath.relative) === '.js') {
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
 * @param result The analyzed, processed result, what we want save into file
 */
function saveToAST(target, result) {
    "use strict";
    /* TODO: remove this code once JSAN and ESLintRunner is merged
    if (globals.getOption('saveEspreeAst')) {
        let transformStream = JSONStream.stringify();
        let outputStream = fs.createWriteStream(target + '.ast');
        transformStream.pipe(outputStream);
        result.forEach(transformStream.write);
        transformStream.end();
        Memory.check();

        outputStream.on('finish', function handleFinish() {
            console.log('Saving AST to file is done');
        });
    }
     */
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
    if (successfullyParsedFiles.length === 0){
       console.log("CrossReference binding is being skipped as there are no modules in the input.");
    } else {
        try {
            //jcg.setFiles(globals.getOption('inputList'));
            jcg.setFiles(successfullyParsedFiles);
            jcg.setArgs({
                fg: null,
                cg: [],
                time: null,
                strategy: 'ONESHOT',
                countCB: null,
                reqJs: null,
                output: null,
                filter: null
            });
            jcg.setConsoleOutput(false);
            let resultOfACG = jcg.build();
            Memory.check();
            astTransformer.transform(resultOfAnalyze.result, parsingOptions);
            Memory.check();
            let resultOfVU = astTransformer.variableUsages(resultOfAnalyze.result);
            Memory.check();
            astTransformer.binder("ACG", resultOfAnalyze.result, resultOfACG, "addCalls");
            astTransformer.binder("VU", resultOfAnalyze.result, resultOfVU, "setRefersTo");
            Memory.check();
        } catch (e) {
            console.warn(e);
            console.warn("CrossReference Binding was failed.");
        }
    }

    saveToAST(globals.getOption('out'), resultOfAnalyze.result);
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
    if (process.version.split(".")[0].substring(1) < NODEJS_MINIMUM_VERSION) {  // check Node.js version
        console.log("Failed to start JSAN as the minimum required Node.js version cannot be found!");
        console.log("Minimum version: " + NODEJS_MINIMUM_VERSION);
        console.log("Your version: " + process.version.split(".")[0].substring(1));
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
}catch (e) {
    console.log(e);
}
