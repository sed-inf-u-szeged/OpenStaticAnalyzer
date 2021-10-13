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

const fs = require('fs');
const path = require('path');
const getUsage = require('command-line-usage');    //for printing the usage
const commandLineArgs = require('command-line-args');      //for parsing command line args
const toolDescription = require('./toolDescription');   //Tool description

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
        name: 'useRelativePath',
        alias: 'r',
        type: Boolean,
        defaultValue: false,
        description: 'Relative paths are used in the output if this option is given.'
    },

    {
        name: 'out',
        alias: 'o',
        type: String,
        description: 'The output filename for the generated XML-Graph to be saved in.'
    },
    {
        name: 'rul',
        type: String,
        defaultValue: false,
        description: 'Input RUL file, which contains the exluded and included rules.'
    },
    {
        name: 'help',
        alias: 'h',
        type: Boolean,
        defaultValue: false,
        description: 'Prints out this help screen of EsLintRunner.'
    },
    {
        name: 'stat',
        type: String,
        description: 'Write memory and runtime stats to the given file.',
        defaultValue: false
    }

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

//recursive function which fill the input list
function constructInputList(inputFile, parsedOptions) {
    if (fs.lstatSync(inputFile).isDirectory()) {
        var dirContent = fs.readdirSync(inputFile);
        for (var i = 0; i < dirContent.length; i++) {
            constructInputList(path.join(inputFile, dirContent[i]), parsedOptions);
        }
    } else {
        if (path.extname(inputFile) !== ".js" && path.extname(inputFile) !== ".html") {
            return;
        }

        parsedOptions.inputList.push(inputFile);
    }
}

//Exports
module.exports.printUsage = printUsage;
module.exports.parse = function () {
    if (process.argv.length == 2) {
        printUsage();
    }
    var options;
    try {
        options = commandLineArgs(definitions);
        options = checkOptions(options);
    }
    catch (e) {
        console.error(e);
        console.error("The given command line arguments was bad. Please use the --help switch to read documentations.");
        process.exit();
    }

    //get all input files (dirs turned into files to be analyzed)
    options.inputList = [];
    for (let i = 0; i < options.input.length; i++) {
        constructInputList(options.input[i], options);
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
    return parsedOptions;
}


