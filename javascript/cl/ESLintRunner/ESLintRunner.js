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
const eslint = require('eslint');
const fs = require('fs');
var eslintConfig;
const formatter = require('./OpenStaticAnalyzerFormater');
const JSONStream = require('JSONStream');
const parseXML = require('xml2js').parseString;

var CLIEngine = eslint.CLIEngine;
var SourceCode = eslint.SourceCode;

var ignoredFilesList = ".eslintignore";
var globals = require('./src/globals');
var options = clOptions.parse();
globals.setOptions(options);
const util = require('util');
const path = require('path');
const espree = require('espree');


var resultSet = [];

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
 * TODO: Delete this code once JSAN and ESLintRunner are merged
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
        attachComment: false,
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
 * TODO: Delete this code once JSAN and ESLintRunner are merged
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
 * TODO: Delete this code once JSAN and ESLintRunner are merged
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
 * TODO: Delete this code once JSAN and ESLintRunner are merged
 * Trim shebang to avoid parse error
 * Doing it this way will preserve the original absolute positions
 * This snippet is taken from: https://github.com/jquery/esprima/issues/1151#issuecomment-85706244
 * @param code the loaded code that might include starting shebang
 * @returns the stripped source code
 */
function trimHashbang(code) {
    if (typeof code !== 'string') {
        console.log("Code was not string, it was: " + code);
        return code;
    }
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
 * TODO: Delete this code once JSAN and ESLintRunner are merged
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

/*
 * Parses a given .rul configuration file and transforms it into a json config object for ESLint
 * */
function externalRul(file) {
    var metrics = {};
    try {
        console.log("Loading external rul file (" + file + ")");
        var rulcontent = fs.readFileSync(file, 'utf-8');
        Memory.check();
    } catch (err) {
        console.log(err);
        process.exit();
    }
    var currentPointer;
    try {
        parseXML(rulcontent, {trim: true}, function (err, result) {
            if (err)
                console.log(err);
            result.Rul.Metric.forEach(function (elem) {
                Memory.check();
                if (elem.Configuration[0].Group[0] == "false") {
                    var originalID = elem.Configuration[0].OriginalId;
                    var enabled = (elem.Configuration[0].Enabled[0] == "true" ? 1 : 0);
                    var param = null;
                    var settings = elem.Configuration[0].Settings[0].Setting;
                    currentPointer = originalID;
                    settings.forEach(function (setting) {
                        if (setting.$.name == "__eslint_param__") {
                            param = setting._;
                        }
                    });

                    if (param) {
                        var ruleOptions = [];
                        ruleOptions.push(enabled);
                        ruleOptions.push(JSON.parse(param));
                        metrics[originalID] = ruleOptions;
                    }
                    else {
                        metrics[originalID] = enabled;
                    }
                }
                Memory.check();

            });
            Memory.check();
        });
    } catch (err) {
        console.error("Syntax error around '" + currentPointer + "' metric. Please check the metric and neighbours.");
        console.error("A possible error: Maybe not valid JSAN format at __eslint_param__ setting.");
        console.log("The analyze will use the default eslint.json config file. Loading..");
        return require('./eslint.json');
    }
    Memory.check();
    return metrics;
}

function parseAst(astShadow) {
    console.log("Processing " + astShadow.filename + "...");
    try {
        var code = new SourceCode("", astShadow);
        Memory.check();
        var cli = new CLIEngine({
            parserOptions: {sourceType: astShadow.sourceType},
            baseConfig: {
                env: { es6: true }
            },
            useEslintrc: false,
            ignore: false,
            rules: eslintConfig
        });
        var exec = cli.executeOnText(code, astShadow.filename);
        Memory.check();
        exec.results.filename = astShadow.filename;
        resultSet.push(exec.results);
    } catch (err) {
        console.log(err);
    }
}

function saveToFile(outputFileShadow, finishEvent) {
    if (!outputFileShadow.endsWith(".xml")) {
        outputFileShadow += ".xml";
    }
    console.log("Save result into " + outputFileShadow + " file.");
    var wstream = fs.createWriteStream(outputFileShadow);
    wstream.write(formatter(resultSet));
    Memory.check();
    wstream.end();
    if (typeof finishEvent === 'function') {
        finishEvent();
    }
    console.log("Done.");
}

/**
 * Runs ESLint on every input.
 */
function runESLint(finishEvent) {
    "use strict";
    Memory.check();
    let resultOfAnalyze = loadCode(globals.getOption('inputList'));

    resultOfAnalyze.result.forEach(function (ast) {
        parseAst(ast);
        Memory.check();
    });
    saveToFile(options.out, finishEvent);
    Memory.check();
}

function wrappedRunESLint() {
    "use strict";

    const start = process.hrtime();
    var elapsed;
    var sec;
    var used;

    runESLint(function () {
        elapsed = process.hrtime(start);
        used = process.memoryUsage().heapUsed / 1024 / 1024;
        sec = elapsed[0] + (elapsed[1] / 1e9);

        console.log("Total time of ESLintRunner was %d s.", sec);
        console.log("Peak memory usage was %f MB", Memory.result());

        const csv = [
            "Run time (s);Peak memory usage (MB)",
            sec + ";" + Memory.result()
        ];

        fs.writeFile(globals.getOption("stat"), csv.join("\n"), function (err) {
            if (err) throw err;
        });
    });
}

/**
 * Entry point
 *
 * Here we will decide whether statistics needed or not.
 */
function analyzeMain() {
    "use strict";

    //Determine if default json should be used or use a rul file from which the config should be generated
    if (options.rul) {
        eslintConfig = externalRul(options.rul);
        Memory.check();
    } else {
        console.log("The external rul file is missing. Using the built-in rules (eslint.json).");
        eslintConfig = require('./eslint.json');
    }

    if (globals.getOption("stat")) {
        wrappedRunESLint();
    } else {
        runESLint();
    }
}

analyzeMain();
