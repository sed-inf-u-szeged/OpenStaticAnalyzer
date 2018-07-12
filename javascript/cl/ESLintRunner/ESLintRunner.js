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
const formatter = require('./OpenStaticAnalyzerFormatter');
const memwatch = require('memwatch-next');
const JSONStream = require('JSONStream');
const parseXML = require('xml2js').parseString;

var CLIEngine = eslint.CLIEngine;
var SourceCode = eslint.SourceCode;

var ignoredFilesList = ".eslintignore";
var globals = require('./src/globals');
var options = clOptions.parse();
globals.setOptions(options);
const util = require('util');

var resultSet = [];

/*
 * Parses a given .rul configuration file and transforms it into a json config object for ESLint
 * */
function externalRul(file) {
    var metrics = {};
    try {
        console.log("Loading external rul file (" + file + ")");
        var rulcontent = fs.readFileSync(file, 'utf-8');
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

            });

        });
    } catch (err) {
        console.error("Syntax error around '" + currentPointer + "' metric. Please check the metric and neighbours.");
        console.error("A possible error: Maybe not valid JSAN format at __eslint_param__ setting.");
        console.log("The analyze will use the default eslint.json config file. Loading..");
        return require('./eslint.json');
    }

    return metrics;
}

function parseAst(astShadow) {
    console.log("Processing " + astShadow.filename + "...");
    try {
        var code = new SourceCode("", astShadow);
        var cli = new CLIEngine({
            useEslintrc: false,
            ignore: false,
            rules: eslintConfig
        });
        var exec = cli.executeOnText(code, astShadow.filename);
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
    var stream = fs.createReadStream(options.input, {flags: 'r', encoding: 'utf-8'});
    var parse = JSONStream.parse();
    stream.pipe(parse);
    parse.on('data', function (data) {
        data.forEach(function (current) {
            parseAst(current);
        });
        saveToFile(options.out, finishEvent);
    });
}

function wrappedRunESLint() {
    "use strict";
    var peakHeap = 0;

    memwatch.on('stats', function (stats) {
        var currentPeakHeap = stats.max / 1e6;

        if (currentPeakHeap > peakHeap) {
            peakHeap = currentPeakHeap;
        }
    });

    const start = process.hrtime();
    var elapsed;
    var sec;
    var used;

    runESLint(function () {
        memwatch.gc(); // This will trigger one stat event at least
        elapsed = process.hrtime(start);
        used = process.memoryUsage().heapUsed / 1024 / 1024;
        sec = elapsed[0] + (elapsed[1] / 1e9);
        console.log("Total time of ESLintRunner was %d s.", sec);
        waitAndWriteStats(20);
    });

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
            setTimeout(waitAndWriteStats, 300, --numOfTries);
            return;
        }

        console.log("Peak memory usage was %f MB", peakHeap);

        const csv = [
            "Run time (s);Peak memory usage (MB)",
            sec + ";" + peakHeap
        ];

        fs.writeFile(globals.getOption("stat"), csv.join("\n"), function (err) {
            if (err) throw err;
        });
    }

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
