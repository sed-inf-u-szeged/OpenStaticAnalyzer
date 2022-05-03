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

import * as eslint from 'eslint';
import * as clOptions from './src/assets/options.js';
import * as fs from 'fs';
import * as path from 'path';
import {formatter} from "./outputFormatter.js";
import {parseString} from 'xml2js';
import * as globals from './src/globals.js';
import * as constants from './src/assets/constants.js';
import * as JSON5 from "json5";

/**
 * The parsed command line arguments.
 */
const options = clOptions.parse();
globals.setOptions(options);

/**
 * Path for the default Typescript-ESLint configuration
 * @type: {string}
 */
const defaultTSConfigurationPath = path.resolve(__dirname, "typescript-eslint.json");
/**
 * If a project wants to extend a non-existing, file it creates an empty one and stores its path in this array.
 * @type: {*[]}
 */
let filesToBeDeleted = [];

/**
 * Typescript-ESLint configuration which is either from the rul file, or from the default configuration.
 */
let typescriptEslintConfig;

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
 * Parses a given .rul configuration file and transforms it into a json config object for ESLint
 */
function externalRul(file) {
    const metrics = {};

    console.log("Loading external rul file (" + file + ")");
    if (!fs.existsSync(file)) {
        console.log("The external rul file does not exists!")
        process.exit()
    }
    const rulContent = fs.readFileSync(file, 'utf-8');
    Memory.check();

    let currentPointer;
    try {
        parseString(rulContent, {trim: true}, function (err, result) {
            if (err) {
                console.log(err);
            }

            result.Rul.Metric.forEach(function (elem) {
                Memory.check();
                if (elem.Configuration[0].Group[0] === "false") {
                    const originalID = elem.Configuration[0].OriginalId;
                    const enabled = (elem.Configuration[0].Enabled[0] === "true" ? 1 : 0);
                    const settings = elem.Configuration[0].Settings[0].Setting;

                    let param = null;
                    currentPointer = originalID;
                    settings.forEach(function (setting) {
                        if (setting.$.name === "__eslint_param__") {
                            param = setting._;
                        }
                    });

                    if (param) {
                        const ruleOptions = [];
                        ruleOptions.push(enabled);
                        ruleOptions.push(JSON.parse(param));
                        metrics[originalID] = ruleOptions;
                    } else {
                        metrics[originalID] = enabled;
                    }
                }
                Memory.check();
            });
            Memory.check();
        });
    } catch (err) {
        console.error(`Syntax error around '${currentPointer}' metric. Please check the metric and neighbours.`);
        console.error("A possible error: Maybe not valid JSAN format at __eslint_param__ setting.");
        console.log("The analyze will use the default typescript-eslint.json config file. Loading..");
        return readDefaultRules();
    }
    Memory.check();
    return metrics;
}

/**
 * @path: The absolute path of the package.json file
 * Reads the entire package.json and returns it as an object.
 * **/
function readPackageJSON(path) {
    let data;
    try {
        data = JSON.parse(fs.readFileSync(path));
    } catch (err) {
        console.error(err);
    }
    return data;
}

function saveToFile(outputFileShadow, resultSet, finishEvent) {
    if (!outputFileShadow.endsWith(".xml")) {
        outputFileShadow += ".xml";
    }
    console.log(`Saving results into ${outputFileShadow}.`);
    const writeStream = fs.createWriteStream(outputFileShadow);
    writeStream.write(formatter(resultSet));
    Memory.check();
    writeStream.end();
    if (typeof finishEvent === 'function') {
        finishEvent();
    }
    console.log("Done.");
}

/**
 * This function searches for all of the tsconfig files which exist in the current project.
 * Any file that contains "tsconfig" in its name is stored in the returnableArray.
 * @param: input - An absolute path, which can be a file or a directory.
 * @param: returnableArray - An array that contains the paths of tsconfig files.
 * @returns: returnableArray - Returns all the absolute paths of the tsconfig files.
 */
function searchFoldersForConfig(input, returnableArray) {
    if (!fs.existsSync(input)) {
        return returnableArray;
    }
    if (fs.lstatSync(input).isDirectory()) {
        const dirContent = fs.readdirSync(input);
        for (let i = 0; i < dirContent.length; i++) {
            returnableArray = searchFoldersForConfig(path.join(input, dirContent[i]), returnableArray);
        }
        return returnableArray;
    } else {
        if (path.basename(input).search("tsconfig") === 0) {
            returnableArray.push(input);
        }
        return returnableArray;
    }
}

/**
 * This function detects if the analyzed project has a tsconfig.json file, and if not,
 * creates a temporary .json file in the dist directory.
 * This is necessary, as some rules cannot be used without the "include" field in said file.
 *
 * @param: typeScriptOptions the config for the typescript-eslint parser
 * @param: tsConfigContent content of tsconfig.json in case the analyzed project has no such file
 */
function readProjectTsconfig(typeScriptOptions, tsConfigContent) {
    let configPathsArray = [];
    searchFoldersForConfig(globals.getOption("inputList")[0], configPathsArray);
    if (configPathsArray.length > 0) { //in case at least 1 tsconfig exists within the analyzed project
        //using JSON5 due to comments.
        for (let index in configPathsArray) {
            try {
                const options = JSON5.parse(fs.readFileSync(configPathsArray[index]).toString());
                //Checks if tsconfig has exclude parameter.
                if (options["exclude"] !== undefined) {
                    for (let i = 0; i < options["exclude"].length; i++) {
                        typeScriptOptions["baseConfig"]["ignorePatterns"].push(options["exclude"][i]);
                    }
                }
                //In case the tsconfig wants to extend from a non-existent file, we create an empty one.
                if (options["extends"] !== undefined) {
                    let extendedFile = path.join(path.dirname(configPathsArray[index]), options["extends"]);
                    if (!fs.existsSync(extendedFile)) {
                        fs.writeFileSync(extendedFile, "");
                        filesToBeDeleted.push(extendedFile);
                    }
                }
                typeScriptOptions["baseConfig"]["parserOptions"]["project"].push((configPathsArray[index].replace(/\\/g, '/')));
            } catch (e) {
                console.log(e);
            }
        }
        return;
    }
    //in case project has no tsconfig / a single file is being linted and might need type information
    console.log("Creating temporary config...");
    typeScriptOptions["baseConfig"]["parserOptions"]["project"] = __dirname + '/tsconfig.json';
    if (globals.getOption(constants.MODULE_BASED_ANALYSIS)
        && globals.getOption('inputList').length === 1
        && fs.existsSync(globals.getOption('inputList')[0])) {
        if (path.extname(globals.getOption("inputList")[0]) === '.ts' || path.extname(globals.getOption("inputList")[0]) === '.js' || path.extname(globals.getOption("inputList")[0]) === '.tsx') { //in case a single file is being analyzed
            tsConfigContent["include"].push(path.resolve(globals.getOption("inputList")[0]));
        } else { //directory
            tsConfigContent["include"].push(path.resolve(globals.getOption("inputList")[0]) + '/**/**.ts');
            tsConfigContent["include"].push(path.resolve(globals.getOption("inputList")[0]) + '/**/**.tsx');
            tsConfigContent["include"].push(path.resolve(globals.getOption("inputList")[0]) + '/**/**.jsx');
            tsConfigContent["include"].push(path.resolve(globals.getOption("inputList")[0]) + '/**/**.js');
        }
    } else {
        for (let index in globals.getOption("inputList")) { //mba is not enabled, analyzing lots of files
            tsConfigContent["include"].push(path.resolve(globals.getOption("inputList")[index]));
        }
    }
    //creates a temporary directory which contains the now created tsconfig
    const tmpDir = path.resolve(path.basename(globals.getOption("inputList")[0]).replace(path.extname(globals.getOption("inputList")[0]), ''));
    if (!fs.existsSync(tmpDir)) {
        fs.mkdirSync((tmpDir), (err) => {
            if (err) {
                console.log(err)
            }
        });
    } else {
        fs.unlinkSync(tmpDir + '/tsconfig.json'); // in case project has already been analysed, and in just in case the tsconfig.json file has changed
    }
    fs.writeFileSync((tmpDir + '/tsconfig.json').replace(/\\/g, '/'), JSON.stringify(tsConfigContent));
    typeScriptOptions["baseConfig"]["parserOptions"]["project"] = tmpDir + '/tsconfig.json';
}

/**
 * Appends ignore patterns from package.json to running config.
 * @packageContent: Contents of the analyzed project's eslintIgnore field in package.json
 * @param: typeScriptOptions the config for the typescript-eslint parser
 * */
function appendToIgnore(packageContent, typeScriptOptions) {
    for (let i in packageContent["eslintIgnore"]) {
        typeScriptOptions["baseConfig"]["ignorePatterns"].push(packageContent["eslintIgnore"][i])
    }
}

function readDefaultRules() {
    if (!fs.existsSync(defaultTSConfigurationPath)) {
        throw new Error("Default typescript-eslint configuration is missing!");
    }
    return JSON.parse(fs.readFileSync(defaultTSConfigurationPath, "utf8"));
}

/**
 * @packageJsonPath: The absolut epath of the package.json's file.
 * It reads the rules from the package.json file if it has any.
 * If not it reads the built-in one.
 * */
function readRulesFromPackageJson(packageJsonPath) {
    try {
        if (packageJsonPath["eslintConfig"]["rules"] !== undefined) {
            const packageJsonContents = readPackageJSON(packageJsonPath)["eslintConfig"]["rules"];
            if (packageJsonContents !== undefined) {
                console.log("The external rul file is missing. Using rules from package.json");
                typescriptEslintConfig = packageJsonContents;
            }
        }
    } catch {
        console.log("The package.json file is missing ESLint rules. Using the built-in rules (typescript-eslint.json).");
        typescriptEslintConfig = readDefaultRules();
    }
}

/**
 * Runs ESLint on every input.
 */
function runESLint(finishEvent) {
    "use strict";
    //default options for the parser

    const typeScriptOptions = { // options in case package.json has no eslintConfig & typescript files are analyzed
        baseConfig: {
            root: true,
            env: {
                es2020: true,
            },
            parserOptions: {
                ecmaFeatures: {
                    jsx: false
                },
                tsconfigRootDir: globals.getOption("inputList")[0],
                project: [],
                rules: ""
            },
            overrides: [
                {
                    files: ["*.ts", "*.tsx"],
                    excludedFiles: [],
                    extends: [],
                    settings: {
                        import: {
                            parsers: {
                                "@typescript-eslint/parser": ["*.ts", "*.tsx"],
                            }
                        }
                    }
                }
            ],
            plugins: [
                "@typescript-eslint/eslint-plugin",
                "eslint-plugin-react",
                "eslint-plugin-angular",
                "eslint-plugin-flowtype",
                "eslint-plugin-import",
                "eslint-plugin-jsx-a11y",
                "eslint-plugin-react-hooks"
            ],
            parser: "@typescript-eslint/parser",
            //Certain configuration files aren't analyzed.
            ignorePatterns: ["**/*.config.js", "**/*.config.ts", ".eslintrc*", "**/*.conf.js", "**/*.conf.ts", "**/*-config.js", "**/*-config.ts", "gulpfile.js"]
        },
        useEslintrc: false,
        globInputPaths: false,
    };
    //checking if the path is a directory or a file
    if (fs.existsSync(globals.getOption("inputList")[0]) && fs.lstatSync(globals.getOption("inputList")[0]).isDirectory()) {
        typeScriptOptions["baseConfig"]["parserOptions"]["sourceType"] = "module";
    } else {
        typeScriptOptions["baseConfig"]["parserOptions"]["sourceType"] = "script";
        typeScriptOptions["baseConfig"]["parserOptions"]["tsconfigRootDir"] = path.basename(globals.getOption("inputList")[0]);
    }
    //default configuration for analyzed projects
    let defaultTSConfig = {
        compilerOptions: {
            baseUrl: "node_modules",
            target: "es2020",
            module: "commonjs",
            moduleResolution: "node",
            noEmitOnError: true,
            lib: [
                "es2020"
            ],
            strict: true,
            esModuleInterop: false,
            outDir: "dist"
        },
        include: [],
        exclude: [
            "node_modules",
            "dist"
        ]
    };
    readProjectTsconfig(typeScriptOptions, defaultTSConfig);
    const packageJsonPath = path.join(globals.getOption("inputList")[0], "package.json");
    let packageJsonContents;
    if (fs.existsSync(packageJsonPath)) {
        packageJsonContents = readPackageJSON(packageJsonPath);
    }
    if (packageJsonContents !== undefined) {
        if (packageJsonContents["eslintConfig"] !== undefined) {
            for (let key in packageJsonContents["eslintConfig"]) {
                typeScriptOptions["baseConfig"][key] = packageJsonContents["eslintConfig"][key];
            }
        }
    }
    typeScriptOptions["baseConfig"]["rules"] = typescriptEslintConfig;
    Memory.check();
    // If module-based analysis is set, we set the .eslintignore file to the ignore path
    if (globals.getOption(constants.MODULE_BASED_ANALYSIS)
        && globals.getOption('inputList').length === 1
        && fs.existsSync(globals.getOption('inputList')[0])) {
        const eslintIgnorePath = path.join(globals.getOption('inputList')[0], ".eslintignore");
        if (fs.existsSync(eslintIgnorePath)) {
            typeScriptOptions.ignorePath = eslintIgnorePath;
        } else {
            try { //check if package.json contains eslintIgnore
                if (fs.existsSync(packageJsonPath)) {
                    let packageContent = readPackageJSON(packageJsonPath);
                    if (packageContent["eslintIgnore"] !== undefined) {
                        appendToIgnore(packageContent, typeScriptOptions);
                    }

                }
            } catch (err) {
                console.log(err);
            }
        }
    }
    //if externalhardfilter was used and files were filtered
    if (globals.getOption('filteredFiles').length > 0) {
        for (let i in globals.getOption('filteredFiles')) {
            typeScriptOptions["baseConfig"]["ignorePatterns"].push(globals.getOption('filteredFiles')[i]);
        }
    }
    let eslintProgram = new eslint.ESLint(typeScriptOptions);
    Memory.check();
    //console.debug(`Analyzing input ${globals.getOption('inputList')}`);
    eslintProgram.lintFiles(globals.getOption('inputList')).then(results => {
        Memory.check();
        // Save raw results
        if (globals.getOption(constants.RAW_OUTPUT)) {
            fs.writeFile("eslint-raw-results.json", JSON.stringify(results), 'utf8', function (err) {
                if (err) {
                    console.log("An error occurred while writing raw results to JSON file.");
                    return console.log(err);
                }
                console.log("Raw results have been saved.");
            });
        }
        saveToFile(options.out, results, finishEvent);
        for (let dfile in filesToBeDeleted) {
            console.log("anyád");
            fs.unlinkSync(filesToBeDeleted[dfile]);
        }
        Memory.check();
    }).catch(err => {
        console.log("An error occurred while running ESLint!")
        console.log(err);
    }).finally(() => {
        console.log("Finished!");
    });
    Memory.check();
}

function wrappedRunESLint() {

    "use strict";
    const start = process.hrtime();
    let elapsed;
    let sec;
    let used;

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

        fs.writeFile(globals.getOption(constants.STAT), csv.join("\n"), function (err) {
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
    try {
        const packageJsonPath = path.join(globals.getOption("inputList")[0], "package.json").toString();
        if (options.rul) {
            typescriptEslintConfig = externalRul(options.rul);
            Memory.check();
        } else if (fs.existsSync(packageJsonPath)) {
            readRulesFromPackageJson(packageJsonPath);
        } else {
            console.log("The package.json file is missing. Using the built-in rules (typescript-eslint.json).");
            typescriptEslintConfig = readDefaultRules();
        }
        if (globals.getOption("stat")) {
            wrappedRunESLint();
        } else {
            runESLint();
        }
    } catch (e) {
        console.log(e);
    }
}

try {
    analyzeMain();
} catch (e) {
    console.log(e);
}
