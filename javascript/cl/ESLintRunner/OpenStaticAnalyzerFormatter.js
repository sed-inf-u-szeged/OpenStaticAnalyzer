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

var os = require('os');
var path = require("path");

function getMessageType(message) {
    if (message.fatal)
        return "fatal";
    return message.severity === 2 ? "error" : "warning";
}

function xmlEscape(s) {
    var regex = /[^\u000D\u00B7\u0020-\u007E\u00A2-\u00A4]/g;
    var corrected = ("" + s).replace(/[<>&"']/g, function (c) {
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
            // no default
        }
    });
    return ("" + corrected).replace(regex, '');

}

//------------------------------------------------------------------------------
// Public Interface
//------------------------------------------------------------------------------
module.exports = function (resultset) {
    var output = "<?xml version=\"1.0\" encoding=\"utf-8\"?>" + os.EOL;
    output += "<ESLintToGraph version=\"4.3\">" + os.EOL;
    resultset.forEach(function (results) {
        var pathToFile = results.filename;
        results.forEach(function (result) {
            output += "    <file name=\"" + xmlEscape(pathToFile) + "\">" + os.EOL;
            result.messages.forEach(function (message) {
                output += "        <error line=\"" + xmlEscape(message.line) + "\" " +
                    "column=\"" + xmlEscape(message.column) + "\" " +
                    "severity=\"" + xmlEscape(getMessageType(message)) + "\" " +
                    "ruleId=\"" + (message.ruleId ? xmlEscape(message.ruleId) : "NotAvailable") + "\" " +
                    "nodeType=\"" + xmlEscape(message.nodeType) + "\" " +
                    "message=\"" + xmlEscape(message.message)
                    + "\" />" + os.EOL;
            });
            output += "    </file>" + os.EOL;
        });
    });
    output += "</ESLintToGraph>";
    return output;
};