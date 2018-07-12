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

const fs =              require('fs');
const path =            require('path');
const getUsage =        require('command-line-usage');    //for printing the usage
const commandLineArgs = require('command-line-args');      //for parsing command line args
const toolDescription = require('./toolDescription');   //Tool description

//List of command line options
const definitions = [
  { name: 'input', alias: 'i', type: String, multiple: true, defaultOption: true, description: 'Input file(s) or directory to be analyzed.' },
  { name: 'out', alias: 'o', type: String, defaultValue: 'out', description: 'The output filename for the results to be saved in. It will contain the results in binary.' },
  { name: 'dumpjsml', alias: 'd', type: Boolean, defaultValue: false, description: 'An XML style file is also created not just a binary if this option is used.' },
  { name: 'externalHardFilter', alias: 'e', type: String, description: 'A file that specifies the list of files/directories to be ignored during the analysis.' },
  { name: 'help', type: Boolean, defaultValue: false, description: 'Prints out the help of JSAN.' },
  { name: 'useRelativePath', alias: 'r', type: Boolean, defaultValue: false, description: 'Relative paths are used in the output if this option is given.' },
  { name: 'saveEspreeAst', alias: 's', type: Boolean, description: 'Use this option to save the AST constructed by Espree.' },
  { name: 'html', alias: 'h', type: Boolean, description: 'Analyze not only JavaScript files but extracts JavaScript code snippets from HTML files too if this option is given.' },
  { name: 'stat', type: String, description: 'Create stats', defaultValue: false}
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

module.exports.parse = function(){
    var options;
    try{
        options = commandLineArgs(definitions);
        options = checkOptions(options);
    }
    catch(e){
        console.error("Bad command line!");
        console.log(e);
        printUsage();
    }

    return options;
    
};


function isNull(parameter) {
    return typeof parameter === "undefined" || parameter === null;
}

//checks whether the parsed command line options are correct
function checkOptions(parsedOptions) {
    var i; // used in the for loops

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
        var dirContent = fs.readdirSync(inputFile);
        for (var i = 0; i < dirContent.length; i++) {
            constructInputList(path.join(inputFile, dirContent[i]), parsedOptions);
        }
    } else {
        if (path.extname(inputFile) !== ".js" && path.extname(inputFile) !== ".html" || externalHardFiltering(inputFile, parsedOptions.hardFilterArray)) {
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

    var filterIt = false;
    for (var i = 0; i < hardFilterArray.length; i++) {
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
    var hardFilterArray = [];
    if(!fs.existsSync(hardFilterFile)){
        console.warn("Hard filter file: " + hardFilterFile + " does not exist. Filtering step is left out.");
        return hardFilterArray;
    }

    if (fs.lstatSync(hardFilterFile).isFile() && path.extname(hardFilterFile) === ".txt") {
        fs.readFileSync(hardFilterFile).toString().split('\n').forEach(function (line) {
            if(line.trim().length == 0){
                return;
            }

            var firstChar = line.substring(0, 1);
            var regex = line.substring(1, line.length);
            if(regex.endsWith("\r")){
                regex = regex.substring(0, regex.length-1);
            }

            regex = ".*" + regex + ".*";

            if (firstChar === "-") {
                hardFilterArray.push({ regex: regex, filter: true });
            } else if (firstChar === "+") {
                hardFilterArray.push({ regex: regex, filter: false });
            } else if (firstChar !== "#") {
                console.error("External hard filter contains an invalid line: " + line +"\n");
                return;
            }
        });
    } else {
        console.error("Hard filter file does not exist or not a file! Skipping filtering step.");
    }

    return hardFilterArray;
}
