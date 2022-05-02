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
import {formatter, textFormatter} from "./outputFormatter.js";
import * as globals from './src/globals.js';
import * as constants from './src/assets/constants.js';
import * as JSON5 from "json5";

/**
 * The parsed command line arguments.
 */
const options = clOptions.parse();
globals.setOptions(options);

/**
 * Whether we created the temporary dir
 * @type {boolean}
 */
let tempDirExistedBefore = true;

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

    const pattern = {
        metrics: new RegExp(/^# +Metrics/),
        metric: new RegExp(/^## +/),
        defaultConfig: new RegExp(/^### +Default/),
        originalID: new RegExp(/^#### +OriginalId *=/),
        enabled: new RegExp(/^#### +Enabled *=/),
        esLintParam: new RegExp(/^- +__eslint_param__ *=/),
    };

    const state = { lineNumber: 0 };

    try {
        rulContent.split(/\r?\n/).forEach(line => {
            ++state.lineNumber;
            if (line.length === 0) { return; }

            if (line.startsWith("# ")) {
                state.metrics = line.search(pattern.metrics) !== -1 ? {} : null;
                return;
            }
            if (state.metrics == null) { return; }

            if (line.search(pattern.metric) !== -1) { state.metrics.metric = {}; }
            if (state.metrics.metric == null) { return; }

            if (line.startsWith("### ")) {
                state.metrics.metric.defaultConfig = line.search(pattern.defaultConfig) !== -1 ? {} : null;
            }
            if (state.metrics.metric.defaultConfig == null) { return; }

            const originalIDMatch = line.match(pattern.originalID);
            if (originalIDMatch != null) {
                const originalIDBegin = originalIDMatch[0].length + originalIDMatch.index;
                state.metrics.metric.defaultConfig.originalId = line.substring(originalIDBegin).trim();
                return;
            }
            const currentOriginalId = state.metrics.metric.defaultConfig.originalId;
            if (currentOriginalId == null) { return; }

            const enabledMatch = line.match(pattern.enabled);
            if (enabledMatch != null) {
                const enabledBegin = enabledMatch[0].length + enabledMatch.index;
                const enabled = line.substring(enabledBegin).trim() === "true" ? 1 : 0;
                if (Array.isArray(metrics[currentOriginalId])) {
                    metrics[currentOriginalId][0] = enabled;
                } else {
                    metrics[currentOriginalId] = enabled;
                }
            }

            const esParamMatch = line.match(pattern.esLintParam);
            if (esParamMatch != null) {
                const esParamBegin = esParamMatch[0].length + esParamMatch.index;
                const param = line.substring(esParamBegin);
                if (param.length === 0) { return; }
                const esParam = JSON.parse(param);
                if (Array.isArray(metrics[currentOriginalId])) {
                    metrics[currentOriginalId][1] = esParam;
                } else {
                    metrics[currentOriginalId] = [metrics[currentOriginalId], esParam];
                }
                return;
            }
        });
    } catch (err) {
        console.error(`Syntax error around line '${state.lineNumber}'. Please check the metric and neighbours.`);
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
    let formatters = [];
    formatters.push({'ext': '.xml', 'formatter': formatter});

    if (globals.getOption(constants.TEXT_OUTPUT)) {
        formatters.push({'ext': '.txt', 'formatter': textFormatter});
    }

    for (const formatterObj of formatters) {
        let outputFileNameShadow = outputFileShadow;
        if (!outputFileNameShadow.endsWith(formatterObj.ext)) {
            outputFileNameShadow += formatterObj.ext;
        }
        console.log(`Saving results into ${outputFileNameShadow}.`);
        const writeStream = fs.createWriteStream(outputFileNameShadow);
        writeStream.write(formatterObj.formatter(resultSet));
        Memory.check();
        writeStream.end();
    }
    if (typeof finishEvent === 'function') {
        finishEvent();
    }

    Memory.check();
    console.log("Finished saving results.");
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
 * Resolve path for .tsconfig file.
 *
 * Placed into in its own method as the reading is so fragile, it might break any time,
 * and we will be able to fix the issue here.
 *
 * @param filePath
 * @returns {string}
 */
function resolvePathForTSConfig(filePath) {
    return path.resolve(filePath);
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
                typeScriptOptions["baseConfig"]["parserOptions"]["project"].push(configPathsArray[index].replace(/\\/g, '/'));
            } catch (e) {
                console.log(e);
            }
        }
        return;
    }
    //in case project has no tsconfig / a single file is being linted and might need type information
    console.log("Creating temporary tsconfig.json...");
    let tempDir = path.resolve(import.meta.url); //TODO: This is buggy as webpack resolved import.meta on transpile time.
    tempDir = path.resolve(tempDir.substring(0, tempDir.indexOf("file:")), "tmp-eslintrunner"); // TODO: FIX THIS

    if (globals.getOption(constants.TEMP_DIR_PATH)) {
        tempDir = globals.getOption(constants.TEMP_DIR_PATH);
        if (!fs.existsSync(tempDir)) {
            tempDirExistedBefore = false;
            fs.mkdirSync(tempDir, {recursive: true});
        }
    }

    const tempTsConfigPath = path.resolve(tempDir, "tsconfig.json");
    globals.setTempTSConfigPath(tempTsConfigPath);

    typeScriptOptions["baseConfig"]["parserOptions"]["project"] = tempTsConfigPath;

    if (globals.getOption(constants.MODULE_BASED_ANALYSIS)
        && globals.getOption('inputList').length === 1
        && fs.existsSync(globals.getOption('inputList')[0])) {
        if (path.extname(globals.getOption("inputList")[0]) === '.ts' || path.extname(globals.getOption("inputList")[0]) === '.js' || path.extname(globals.getOption("inputList")[0]) === '.tsx') { //in case a single file is being analyzed
            tsConfigContent["include"].push(resolvePathForTSConfig(globals.getOption("inputList")[0]));
        } else { //directory
            tsConfigContent["include"].push(resolvePathForTSConfig(globals.getOption("inputList")[0]) + '/**/**.ts');
            tsConfigContent["include"].push(resolvePathForTSConfig(globals.getOption("inputList")[0]) + '/**/**.tsx');
            tsConfigContent["include"].push(resolvePathForTSConfig(globals.getOption("inputList")[0]) + '/**/**.jsx');
            tsConfigContent["include"].push(resolvePathForTSConfig(globals.getOption("inputList")[0]) + '/**/**.js');
        }
    } else {
        for (let index in globals.getOption("inputList")) { //mba is not enabled, analyzing lots of files
            tsConfigContent["include"].push(resolvePathForTSConfig(globals.getOption("inputList")[index]));
        }
    }

    // Create a temporary directory which contains the newly created .tsconfig
    // const tmpDir = path.resolve(path.basename(globals.getOption("inputList")[0]).replace(path.extname(globals.getOption("inputList")[0]), ''));
    if (!fs.existsSync(tempDir)) {
        fs.mkdirSync((tempDir), (err) => {
            if (err) {
                console.error(err);
            }
        });
    } else { // in case project has already been analysed, and in just in case the tsconfig.json file has changed
        fs.rmSync(tempTsConfigPath, {
            force: true
        });
    }

    fs.writeFileSync(tempTsConfigPath, JSON.stringify(tsConfigContent));
    typeScriptOptions["baseConfig"]["parserOptions"]["project"] = tempTsConfigPath;
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
                tsconfigRootDir: path.dirname(globals.getOption("inputList")[0]),
                project: [],
                rules: ""
            },
            overrides: [
                {
                    files: ["*.ts", "*.tsx", "*.js", "*.jsx"],
                    excludedFiles: [],
                    extends: [],
                    settings: {
                        import: {
                            parsers: {
                                "@typescript-eslint/parser": ["*.ts", "*.tsx", "*.js", "*.jsx"],
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
            allowJs: true,
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

    if (globals.getTempTSConfigPath() !== undefined) {
        typeScriptOptions["baseConfig"]["parserOptions"]["tsconfigRootDir"] = path.dirname(globals.getTempTSConfigPath());
    }

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
                    console.error("An error occurred while writing raw results to JSON file.");
                }
                console.log("Raw results have been saved.");
            });
        }
        saveToFile(options.out, results, finishEvent);
        for (let dfile in filesToBeDeleted) {
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

    if (!globals.tempTSConfigPath) {
        return;
    }

    if (fs.existsSync(globals.getTempTSConfigPath())) {
        fs.unlinkSync(globals.getTempTSConfigPath());
        if (!tempDirExistedBefore) {
            fs.unlinkSync(globals.getOption(constants.TEMP_DIR_PATH));
        }
    }
}

try {
    const cwd = process.cwd();
    globals.setOriginalCwd(cwd);

    if (globals.getOption(constants.EXECUTION_DIR)) {
        process.chdir(globals.getOption(constants.EXECUTION_DIR));
    }

    analyzeMain();

    if (globals.getOption(constants.EXECUTION_DIR)) {
        process.chdir(cwd);
    }
} catch (e) {
    console.log(e);
}
