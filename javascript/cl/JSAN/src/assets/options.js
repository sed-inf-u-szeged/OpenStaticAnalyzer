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
import {default as getUsage} from 'command-line-usage';
import {default as commandLineArgs} from 'command-line-args';
import * as toolDescription from './toolDescription.js';
import * as globals from '../globals.js';
import {isNull} from "../util/util.js";

//List of command line options
const definitions = [
    {
        name: 'input',
        alias: 'i',
        type: String,
        multiple: true,
        defaultOption: true,
        description: 'Input file(s) or directory to be analyzed. Note: simply giving the input file(s) or directory after the last command line parameter will have the same effect too.'
    },
    {
        name: 'out',
        alias: 'o',
        type: String,
        defaultValue: 'out',
        description: 'The output filename for the results to be saved in. It will contain the results in binary format.'
    },
    {
        name: 'dumpjsml',
        alias: 'd',
        type: Boolean,
        defaultValue: false,
        description: 'Dump the output into an XML-style file.'
    },
    {
        name: 'externalHardFilter',
        alias: 'e',
        type: String,
        description: 'Filter file specified with relative or absolute path, to filter out certain files from the analysis based on their path names. Filtered files will not appear in the results. The filter file is a simple text file containing lines starting with " + " or " - " characters followed by a regular expression. During the analysis, each input file will be checked for these expressions. If the first character of the last matching expression is  " - ", then the given file will be excluded from the analysis. If the first character of the last matching expression is " + ", or there is no matching expression, then the file will be analyzed. A line starting with a different character than "-" or "+" will be ignored.'
    },
    {
        name: 'help',
        type: Boolean,
        defaultValue: false,
        description: 'Prints out the help of JSAN.'
    },
    {
        name: 'useRelativePath',
        alias: 'r',
        type: Boolean,
        defaultValue: false,
        description: 'Relative paths are used in the output if this option is given.'
    },
    {
        name: 'html',
        alias: 'h',
        type: Boolean,
        description: 'Analyze not only JavaScript files but extracts JavaScript code snippets from HTML files too if this option is given.'
    },
    {
        name: 'stat',
        type: String,
        defaultValue: false,
        description: 'Write memory and runtime stats to the given file.'
    },
    //{ name: 'saveEspreeAst', alias: 's', type: Boolean, description: 'Save the AST constructed by Espree into a JSON-style file.' },

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

function printUsage() {
    console.log(usage);
}


let parse = function () {
    let options;
    try {
        options = commandLineArgs(definitions);
        options = checkOptions(options);
    } catch (e) {
        console.error("Bad command line!");
        console.log(e);
        printUsage();
    }

    return options;

};


//checks whether the parsed command line options are correct
function checkOptions(parsedOptions) {
    let i; // used in the for loops

    //help
    if (parsedOptions.help) {
        printUsage();
        process.exit();
    }

    //input
    if (isNull(parsedOptions.input) || parsedOptions.input.length === 0) {
        console.error("Error: Missing input.");
        process.exit();
    }

    //validate inputs, not valid paths are removed
    for (i = 0; i < parsedOptions.input.length; i++) {

        if (!fs.existsSync(parsedOptions.input[i])) {
            console.warn("Warning: " + parsedOptions.input[i] + " does not exist. This entry is removed.");
            parsedOptions.input.splice(i, 1);
        }
    }

    //validate output if given
    if (!isNull(parsedOptions.out)) {
        if (path.extname(parsedOptions.out) === ".jssi") {
            parsedOptions.out = parsedOptions.out.substr(0, parsedOptions.out.length - path.extname(parsedOptions.out).length);
        }
    }

    //check hard filter file and create an array of files to be hard filtered
    if (parsedOptions.externalHardFilter) {
        parsedOptions.hardFilterArray = getHardFilterFiles(parsedOptions.externalHardFilter);
    }


    //get all input files (dirs turned into files to be analyzed)
    parsedOptions.inputList = [];
    for (i = 0; i < parsedOptions.input.length; i++) {
        constructInputList(parsedOptions.input[i], parsedOptions);
    }

    return parsedOptions;
}


//recursive function which fill the input list
function constructInputList(inputFile, parsedOptions) {
    if (fs.lstatSync(inputFile).isDirectory()) {
        const dirContent = fs.readdirSync(inputFile);
        for (let i = 0; i < dirContent.length; i++) {
            constructInputList(path.join(inputFile, dirContent[i]), parsedOptions);
        }
    } else {
        if (!globals.supportedExts.includes(path.extname(inputFile)) || externalHardFiltering(inputFile, parsedOptions.hardFilterArray)) {
            return;
        }

        if (path.extname(inputFile) === ".html" && !parsedOptions.html) {
            return;
        }

        parsedOptions.inputList.push(inputFile);
    }
}

function externalHardFiltering(inputFile, hardFilterArray) {
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
        console.log("Filtered: " + inputFile);
    }
    return filterIt;
}

function getHardFilterFiles(hardFilterFile) {
    let hardFilterArray = [];
    if (!fs.existsSync(hardFilterFile)) {
        console.warn("Hard filter file: " + hardFilterFile + " does not exist. Filtering step is being skipped.");
        return hardFilterArray;
    }

    if (fs.lstatSync(hardFilterFile).isFile() && path.extname(hardFilterFile) === ".txt") {
        fs.readFileSync(hardFilterFile).toString().split('\n').forEach(function (line) {
            //if empty line then continue
            if (line.trim().length === 0) {
                return;
            }
            let firstChar = line.substring(0, 1);
            let regex = line.substring(1, line.length);
            if (regex.endsWith("\r")) {
                // regex = regex.substring(0, regex.length - 1);
                regex = regex.trim();
            }
            regex = ".*" + regex + ".*";

            // validate the regex
            // if the regex is faulty, throw an error here
            try {
                new RegExp(regex);
            } catch (err) {
                console.error(`The following regex is not valid and is being skipped from filtering: "${regex}"`);
                return;
            }

            if (firstChar === "-") {
                hardFilterArray.push({regex: regex, filter: true});
            } else if (firstChar === "+") {
                hardFilterArray.push({regex: regex, filter: false});
            } else if (firstChar !== "#") {
                console.error("External hard filter contains an invalid line: " + line + "\n");
            }
        });
    } else {
        console.error("Hard filter file does not exist or not a file! Skipping filtering step.");
    }

    return hardFilterArray;
}


export {printUsage, parse}
