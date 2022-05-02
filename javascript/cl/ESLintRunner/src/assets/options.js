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

import * as fs from 'fs';
import * as path from 'path';
import {default as getUsage} from 'command-line-usage'; //for printing the usage
import {default as commandLineArgs} from 'command-line-args'; //for parsing command line args
import * as toolDescription from './toolDescription.js';
import * as constants from "./constants.js";
import {MODULE_BASED_ANALYSIS} from "./constants.js";


//List of command line options
const definitions = [
    {
        name: constants.INPUT,
        alias: 'i',
        type: String,
        multiple: true,
        defaultOption: true,
        description: 'Input file(s) or directory to be analyzed. Note: simply giving the input file(s) or directory after the last command line parameter will have the same effect too.'
    },
    {
        name: constants.USE_RELATIVE_PATH,
        alias: 'r',
        type: Boolean,
        defaultValue: false,
        description: 'Relative paths are used in the output if this option is given.'
    },

    {
        name: constants.OUTPUT,
        alias: 'o',
        type: String,
        description: 'The output filename for the generated XML-Graph to be saved in.'
    },
    {
        name: constants.RUL,
        type: String,
        defaultValue: false,
        description: 'Input RUL file, which contains the excluded and included rules.'
    },
    {
        name: constants.HELP,
        alias: 'h',
        type: Boolean,
        defaultValue: false,
        description: 'Prints out this help screen of EsLintRunner.'
    },
    {
        name: constants.STAT,
        type: String,
        description: 'Write memory and runtime stats to the given file.',
        defaultValue: false
    },
    {
        name: constants.IGNORE_NODE_MODULES,
        alias: 'n',
        type: Boolean,
        description: 'Ignore all node_modules folder.',
        defaultValue: false
    },
    {
        name: constants.RAW_OUTPUT,
        type: Boolean,
        description: 'Save raw results into JSON.',
        defaultValue: false
    },
    {
        name: constants.TEXT_OUTPUT,
        type: Boolean,
        description: "Save results into simple text-based format.",
        defaultValue: false
    },
    {
        name: constants.MODULE_BASED_ANALYSIS,
        type: Boolean,
        description: 'Use module-based analysis instead of file-based analysis',
        defaultValue: true // Change this to false if you want to use file based analysis.
    },
    {
        name: constants.EXTERNAL_HARD_FILTER,
        alias: 'e',
        defaultValue: false,
        type: String,
        description: 'Filter file specified with relative or absolute path, to filter out certain files from the analysis based on their path names. Filtered files will not appear in the results.'
    },
    {
        name: constants.TEMP_DIR_PATH,
        defaultValue: false,
        type: String,
        description: 'Directory where temporary files will be stored.'
    },
    {
        name: constants.EXECUTION_DIR,
        type: String,
        multiple: false,
        defaultValue: false,
        description: 'Execution dir'
    },
];

//sections of usage
const sections = [
    {
        content: toolDescription.banner,
        raw: true
    },
    {
        header: toolDescription.header,
        content: toolDescription.description
    },
    {
        header: 'Options',
        optionList: definitions
    }
];

const usage = getUsage(sections); //construction of usage text

//Exports
function printUsage() {
    console.log(usage);
}

function parse() {
    if (process.argv.length === 2) {
        printUsage();
    }
    let options;
    try {
        options = commandLineArgs(definitions);
        options = checkOptions(options);
    } catch (e) {
        console.error(e);
        console.error("The given command line arguments was bad. Please use the --help switch to read documentations.");
        process.exit();
    }
    options.inputList = [];
    options.filteredFiles = [];
    for (let i = 0; i < options.input.length; i++) {
        //check if inputs have .ts files
        constructInputList(options.input[i], options);
        if (MODULE_BASED_ANALYSIS && options.externalHardFilter) {
            hardFilterChecking(options.input[i], options);
        }
    }
    return options;
}

//checks whether the parsed command line options are correct
function checkOptions(parsedOptions) {
    //help and default screen
    if (parsedOptions.help) {
        printUsage();
        process.exit();
    }
    if (!parsedOptions.input) {
        console.error("The --input (-i) parameter is required.");
        process.exit();
    }

    if (!parsedOptions.out) {
        console.error("The --out (-o) parameter is required.");
        process.exit();
    }
    if (parsedOptions.externalHardFilter) {
        parsedOptions.hardFilterArray = getHardFilterFiles(parsedOptions.externalHardFilter);
    }
    return parsedOptions;
}

function constructInputList(inputFile, parsedOptions) {
    if (!fs.existsSync(inputFile)) {
        console.log(`${inputFile} is missing, skipping this file/directory.`);
        return;
    }

    if (parsedOptions[constants.IGNORE_NODE_MODULES] && inputFile.includes("node_modules")) {
        return;
    }

    if (fs.lstatSync(inputFile).isDirectory()) {
        if (parsedOptions[constants.MODULE_BASED_ANALYSIS]) {
            parsedOptions.inputList.push(path.resolve(inputFile));
            return;
        }
        const dirContent = fs.readdirSync(inputFile);
        for (let i = 0; i < dirContent.length; i++) {
            constructInputList(path.join(inputFile, dirContent[i]), parsedOptions);
        }
    } else {
        if ((path.extname(inputFile) !== ".js" && path.extname(inputFile) !== ".jsx" && path.extname(inputFile) !== ".ts" && path.extname(inputFile) !== ".tsx") || externalHardFiltering(inputFile, parsedOptions.hardFilterArray, parsedOptions.filteredFiles)) {
            return;
        }
        parsedOptions.inputList.push(inputFile);
    }
}

/**
 * Filters files based on the external hard filter when module based analysis is used.
 * Mostly the same as constructInputList, but files passing the filter aren't added to the input list.
 * @param inputFile
 * @param parsedOptions
 */
function hardFilterChecking(inputFile, parsedOptions) {
    if (!fs.existsSync(inputFile)) {
        console.log(`${inputFile} is missing, skipping this file/directory.`);
        return;
    }

    if (parsedOptions[constants.IGNORE_NODE_MODULES] && inputFile.includes("node_modules")) {
        return;
    }

    if (fs.lstatSync(inputFile).isDirectory()) {
        const dirContent = fs.readdirSync(inputFile);
        for (let i = 0; i < dirContent.length; i++) {
            hardFilterChecking(path.join(inputFile, dirContent[i]), parsedOptions);
        }
    } else {
        if ((path.extname(inputFile) !== ".js" && path.extname(inputFile) !== ".jsx" && path.extname(inputFile) !== ".ts" && path.extname(inputFile) !== ".tsx") || externalHardFiltering(inputFile, parsedOptions.hardFilterArray, parsedOptions.filteredFiles)) {
            return;
        }
    }
}

/**
 * Filters files based on the external hard filter
 * @param: inputFile: absolute path of a file (!)
 * @param: hardFilterArray: contains the regex formulas from the external hard filter
 * @param: filteredArray: An array that contains files that were filtered.
 * */
function externalHardFiltering(inputFile, hardFilterArray, filteredArray) {
    if (!hardFilterArray) {
        return;
    }
    let filterIt = false;
    for (let i = 0; i < hardFilterArray.length; i++) {
        if (inputFile.match(hardFilterArray[i].regex)) {
            filterIt = hardFilterArray[i].filter;
        }
    }
    if (filterIt) {
        let splitPath = inputFile.split('\\');
        filteredArray.push(splitPath[splitPath.length - 1]);
    }
    return filterIt;
}

/**
 * Collects the regexp formulas from the filter file and stores them in an array (hardFilterArray)
 * @param hardFilterFile the path/name of the hard filter (.txt)
 */
function getHardFilterFiles(hardFilterFile) {
    let hardFilterArray = [];
    let filterPath;
    if (!path.isAbsolute(hardFilterFile)) {
        filterPath = path.resolve(hardFilterFile);
    } else {
        filterPath = hardFilterFile;
    }
    if (!fs.existsSync(filterPath)) {
        console.warn("Hard filter file: " + hardFilterFile + " does not exist. Filtering step is being skipped.");
        return hardFilterArray;
    }

    if (fs.lstatSync(filterPath).isFile() && path.extname(filterPath) === ".txt") {
        fs.readFileSync(filterPath).toString().split('\n').forEach(function (line) {
            //if empty line then continue
            if (line.trim().length === 0) {
                return;
            }
            let firstChar = line.substring(0, 1);
            let regex = line.substring(1, line.length);
            if (regex.endsWith("\r")) {
                regex = regex.substring(0, regex.length - 1);
            }
            regex = ".*" + regex + ".*";

            if (firstChar === "-") {
                hardFilterArray.push({regex: regex, filter: true});
            } else if (firstChar === "+") {
                hardFilterArray.push({regex: regex, filter: false});
            } else if (firstChar !== "#") {
                console.error("External hard filter contains an invalid line: " + line + "\n");
                return;
            }

        });
    } else {
        console.error("Hard filter file does not exist or not a file! Skipping filtering step.");
    }

    return hardFilterArray;
}

export {
    printUsage,
    parse
}
