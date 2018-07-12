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
        defaultOption: true,
        description: 'Input AST file, what should transform to XML Graph.'
    },
    {
        name: 'out',
        alias: 'o',
        type: String,
        description: 'The output filename for the generated XML-Graph to be saved in.'
    },
    {
        name: 'rul',
        alias: 'r',
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
        description: 'Create stats',
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
        console.error("The given command line arguments was bad. Please use the --help switch to read documentations.");
        process.exit();
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


