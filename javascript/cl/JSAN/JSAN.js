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
const memwatch = require('memwatch-next');

var globals = require('./src/globals');

globals.setOptions(clOptions.parse());

/**
 * This method make the parsing with Espree
 * and generate the raw of AST.
 * @param code The path of the parsable file
 * @param type The code, what we want parse
 * @returns {*} The result of parsing
 */
var parsingOptions;
var parsing = function (code, type) {
    var options = {
        sourceType: type,
        comment: true,
        tolerant: true,
        loc: true,
        raw: true,
        tokens: true,
        range: true,
        ecmaVersion: 9,
        attachComment: true,
    };
    try {
        return { success: true, ast: espree.parse(code, options), options: options };
    } catch (e) {
        if (type !== 'module') {
            return parsing(code, 'module');
        } else {
            return { success: false, error: e };
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
var makeAstFromCode = function (filePath, code) {
    const rawAst = parsing(code, 'script');
    if (rawAst.success) {
		parsingOptions = rawAst.options;
        var ast = rawAst.ast;
        ast.filename = globals.getOption('useRelativePath') ? filePath.relative : filePath.absolute;
        return ast;
    } else {
        throw new Error('The parsing of code was unsucessful: ' + rawAst.error);
    }
};

/**
 * This method start the analyze, transform the ast
 * and return with results.
 * @param filePath The path of analyzing file
 * @param code The code, what we want analyze
 * @returns {*}
 */
var makeAnalyzeCodeResult = function (filePath, code) {
    try {
        var ast = makeAstFromCode(filePath, code);
        astTransformer.transform(ast, parsingOptions);
        return { success: true, ast: ast };
    } catch (e) {
        return { success: false, error: e };
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
    var result = [];
    files.forEach(function (file) {
        if(path.isAbsolute(file)){
            var filePath = {
                absolute: path.normalize(file),
                relative: path.relative(process.cwd(), file)
            };
        }
        else{
            var filePath = {
                absolute: path.join(process.cwd(), file),
                relative: path.normalize(file)
            };
        }

        var code;

        globals.setActualFile(globals.getOption('useRelativePath') ? filePath.relative : filePath.absolute);
        if (path.extname(filePath.relative) === '.js') {
            code = fs.readFileSync(filePath.relative);
            code = String(code);
            if (code[0] === '#' && code[1] === '!') {
                var end = code.indexOf('\n');
                code = '' + code.substring(end, code.length);
            }
        } else if (path.extname(filePath.relative) === '.html') {
            code = htmlExtractor.extractJSToString(filePath.relative);
        }
        var analyzeResult = makeAnalyzeCodeResult(filePath, code);
        if (analyzeResult.success) {
            result.push(analyzeResult.ast);
        } else {
            console.error(analyzeResult.error);
        }
    });
    console.timeEnd('Total time of loading code');
    return { result: result };
}

/**
 * This method save the result into AST file.
 * @param target The target file of result
 * @param result The analyzed, processed result, what we want save into file
 */
function saveToAST(target, result) {
    "use strict";
    if (globals.getOption('saveEspreeAst')) {
        var transformStream = JSONStream.stringify();
        var outputStream = fs.createWriteStream(target + '.ast');
        transformStream.pipe(outputStream);
        result.forEach(transformStream.write);
        transformStream.end();

        outputStream.on('finish', function handleFinish() {
            console.log('Saving AST to file is done');
        });
    }
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
    var resultOfAnalyze = loadCode(globals.getOption('inputList'));
    saveToAST(globals.getOption('out'), resultOfAnalyze.result);
    memwatch.gc(); // This will trigger one stat event at least
}

/**
 * Analysis wrapper
 * This wrapper will measure memory usage and elapsed time.
 */
function wrappedAnalysis() {
    "use strict";
    var peakHeap = 0;

    memwatch.on('stats', function (stats) {
        var currentPeakHeap = stats.max / 1e6;

        if (currentPeakHeap > peakHeap) {
            peakHeap = currentPeakHeap;
        }
    });

    const start = process.hrtime();

    analysis();

    const elapsed = process.hrtime(start);
    const used = process.memoryUsage().heapUsed / 1024 / 1024;
    const sec = elapsed[0] + (elapsed[1] / 1e9);

    console.log('Total time of JSAN was %d s.', sec);

    /**
     * Waits for statistics and write it to a file.
     *
     * This is needed because both process.memoryUsage() and memwatch can be inaccurate and
     * can show false statistics. So we measure heap usage with process.memoryUsage() and then
     * we wait for a "stat" event from memwatch which shows a bigger used heap than we
     * have now. If this happens in 20 cycles, we use that for statistics. Otherwise we use
     * statistics from process.memoryUsage()
     *
     * @param numOfTries - number of tries we have
     */
    function waitAndWriteStats(numOfTries) {
        if (peakHeap < used && numOfTries > 0) {
            setTimeout(waitAndWriteStats, 300, numOfTries-1);
            return;
        }

        console.log('Peak memory usage was %f MB', peakHeap);
        const csv = [
            'Run time (s);Peak memory usage (MB)',
            sec + ';' + peakHeap
        ];

        fs.writeFile(globals.getOption('stat'), csv.join('\n'), function (err) {
            if (err) throw err;
        });
    }

    waitAndWriteStats(20);
}

/**
 * Entry point
 *
 * Here we will decide whether statistics needed or not.
 */
function analyzeMain() {
    "use strict";
    if (globals.getOption('stat')) {
        wrappedAnalysis();
    } else {
        analysis();
    }
}

analyzeMain();
