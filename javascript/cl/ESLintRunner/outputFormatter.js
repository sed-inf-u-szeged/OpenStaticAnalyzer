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

import * as os from "os";
import {ESLINTRUNNNER_VERSION, getOption} from "./src/globals.js";
import * as path from 'path';
import {USE_RELATIVE_PATH} from './src/assets/constants.js';
import * as globals from './src/globals.js';


function getMessageType(message) {
    if (message.fatal) {
        return "fatal";
    }
    return message.severity === 2 ? "error" : "warning";
}

function xmlEscape(s) {
    const regex = /[^\u000D\u00B7\u0020-\u007E\u00A2-\u00A4]/g;
    const corrected = ("" + s).replace(/[<>&"']/g, function (c) {
        switch (c) {
            case "<":
                return " &lt; ";
            case ">":
                return " &gt; ";
            case "&":
                return " &amp; ";
            case "\"":
                return " &quot; ";
            case "'":
                return " &apos; ";
            default:
                throw new Error(`Unknown character: ${c}`);
        }
    });
    return ("" + corrected).replace(regex, '');

}

/**
 * Transforms results into Columbus-style XML
 * @param resultset the results of ESLint analysis
 * @returns {string}
 */
function formatter(resultset) {
    let output = `<?xml version="1.0" encoding="utf-8"?>${os.EOL}`;
    output += `<ESLintToGraph version="${ESLINTRUNNNER_VERSION}">${os.EOL}`;
    if (output)
        resultset.forEach(function (result) {
            if (getOption(USE_RELATIVE_PATH) === true) {
                const relativeToThisCwd = globals.getOriginalCwd() === undefined ? "" : globals.getOriginalCwd();
                output += `    <file name="${xmlEscape(path.relative(relativeToThisCwd, result.filePath))}">${os.EOL}`;
            } else {
                output += `    <file name="${xmlEscape(result.filePath)}">${os.EOL}`;
            }
            result.messages.forEach(function (message) {
                output += `        <error line="${xmlEscape(message.line)}" ` +
                    `column="${xmlEscape(message.column)}" ` +
                    `severity="${xmlEscape(getMessageType(message))}" ` +
                    `ruleId="${(message.ruleId ? xmlEscape(message.ruleId) : "NotAvailable")}" ` +
                    `nodeType="${xmlEscape(message.nodeType)}" ` +
                    `message="${xmlEscape(message.message)}"` +
                    ` />${os.EOL}`;
            });
            output += `    </file>${os.EOL}`;
        });
    output += `</ESLintToGraph>`;
    output += `${os.EOL}`;
    return output;
}

/**
 * Transforms results into plain text format
 * @param resultset the results of ESLint analysis
 * @returns {string}
 */
function textFormatter(resultset) {
    let output = "";
    output += `ESLintRunner version: ${ESLINTRUNNNER_VERSION}${os.EOL}`;
    output += `Number of files: ${resultset.length}${os.EOL}`
    if (output) {
        resultset.forEach(function (result) {
            result.messages.forEach(function (message) {
                if (getOption(USE_RELATIVE_PATH) === true) {
                    const relativeToThisCwd = globals.getOriginalCwd() === undefined ? "" : globals.getOriginalCwd();
                    output += `${xmlEscape(path.relative(relativeToThisCwd, result.filePath))}`;
                } else {
                    output += `${xmlEscape(result.filePath)}`;
                }
                output += `:${xmlEscape(message.line)}:${xmlEscape(message.column)} ` +
                    `${xmlEscape(getMessageType(message))} ` +
                    `${(message.ruleId ? message.ruleId : "NotAvailable")} ` +
                    `${xmlEscape(message.nodeType)} ` +
                    `${message.message}${os.EOL}`;
            });
            output += `${os.EOL}`;
        });
    } else {
        output += `No warnings found.${os.EOL}`;
    }
    output += `${os.EOL}`;
    return output;
}

export {
    formatter,
    textFormatter
}
