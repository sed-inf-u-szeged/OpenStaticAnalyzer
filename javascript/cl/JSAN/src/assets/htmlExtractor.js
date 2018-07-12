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
const parse5 = require('parse5');


/**
 * input: html filename
 * output: any kind of JS found in the file
 * outputformat: an containing every occuring script in the html file represented by 2 kinds of Objects:
 *      embedded js: { //eg.: <button onclick="embedded js">
 *          file: <<filename>>,
 *          type:'embedded',
 *          node: {name, attrs, selfClosing, location} <<data of the node the script belongs to>>,
 *          event: <<the event attribues name the script fires on>>,
 *          text: <<script text>>,
 *          location:script location
 *      }
 *      js script : { //eg.: <script></script>
 *          file: <<filename>>,
 *          type: 'script',
 *          text: <<script text>>,
 *          location: script location
 *      }
 */
function extractJS(file) {
    const JSEvents = ['onafterprint', 'onbeforeprint', 'onbeforeunload', 'onerror', 'onhashchange', 'onload', 'onmessage', 'onoffline', 'ononline', 'onpagehide', 'onpageshow', 'onpopstate', 'onresize', 'onstorage', 'onunload', 'onblur', 'onchange', 'oncontextmenu', 'onfocus', 'oninput', 'oninvalid', 'onreset', 'onsearch', 'onselect', 'onsubmit', 'onkeydown', 'onkeypress', 'onkeyup', 'onclick', 'ondblclick', 'onmousedown', 'onmousemove', 'onmouseout', 'onmouseover', 'onmouseup', 'onmousewheel', 'onwheel', 'ondrag', 'ondragend', 'ondragenter', 'ondragleave', 'ondragover', 'ondragstart', 'ondrop', 'onscroll', 'oncopy', 'oncut', 'onpaste', 'onabort', 'oncanplay', 'oncanplaythrough', 'oncuechange', 'ondurationchange', 'onemptied', 'onended', 'onerror', 'onloadeddata', 'onloadedmetadata', 'onloadstart', 'onpause', 'onplay', 'onplaying', 'onprogress', 'onratechange', 'onseeked', 'onseeking', 'onstalled', 'onsuspend', 'ontimeupdate', 'onvolumechange', 'onwaiting', 'onshow', 'ontoggle']; //src: https://www.w3schools.com/tags/ref_eventattributes.asp

    var ret = [];

    htmlTXT = fs.readFileSync(file, 'utf-8');
    const parser = new parse5.SAXParser({ locationInfo: true });

    var isJS = null; // is set <=> script tag was found
    var skip = null; // is set <=> script tag was found
    var loc = null; // start tag location
    var str = '';   // this is where the scripts text is buffered

    parser.on('startTag', (name, attrs, selfClosing, location) => { // (name: string, attrs: Attribute[], selfClosing: boolean, location?: StartTagLocation)
        /*
         * Following has to be filtered for:
         * 
         * PARSE anything[onSomeValidEvent='...']
         * 
         * PARSE script (nincs attr)
         * PARSE script[type='text/javascript' || type='application/javascript]
         * 
         * SKIP script[type!='text/javascript' && type!='application/javascript]
         * SKIP script[src]
         * 
         */
        if (name === 'script') {
            if (attrs.length === 0) {
                isJS = true;
                skip = false;
            } else {
                attrs.forEach(attr => {
                    if (attr.name === 'type' && (attr.value === 'text/javascript' || attr.value === 'application/javascript')) {
                        isJS = true;
                    } else {
                        isJS = false;
                    }
                    if (skip || attr.name === 'src') { // if it has a src tag, then skip it
                        skip = true;
                    } else {
                        skip = false;
                    }
                })
            }
        }
        // PARSE anything[onSomeValidEvent='...']
        attrs.forEach(attr => {
            if (JSEvents.includes(attr.name)) {
                // fix location to point at the script, not at the tag
                var event = attr.name;
                var regExp = new RegExp("\\s(" + event + "\\s*=\\s*)(['\"])");
                var str = htmlTXT.substr(location.startOffset, location.endOffset - location.startOffset + 1); //text of the html tag
                var match = regExp.exec(str);
                var apos = match[2];

                regExp = new RegExp("\\s(" + event + "\\s*=\\s*" + apos + ")(.*?)(" + apos + ")");
                match = regExp.exec(str);

                var rawtext = match[2];
                var textlength = rawtext.length;
                var startOffset = location.startOffset + match.index + match[1].length;
                var endOffset = startOffset + textlength;

                ret.push({
                    file: file,
                    type: 'embedded',
                    node: { name: name, attrs: attrs, selfClosing: selfClosing, location: location },
                    event: attr.name,
                    text: attr.value,
                    location: {
                        startOffset: startOffset,
                        endOffset: endOffset
                    }
                });
                var rep = ""; var len = match[0].length;
                for (var i = 0; i < len; i++) rep += " "; //construct an empty string with length of the scriplet found
                htmlTXT = htmlTXT.replaceAt(match.index, rep); //clear the script, so it wont be parsed twice
            }
        })
    });

    parser.on("text", (text, location) => {
        if (isJS && (skip === false)) {
            str += text;
            loc = location; //location-fix
        }
    });

    parser.on("endTag", (name, location) => {
        if (name === 'script') {
            if (isJS && (skip === false)) {
                ret.push({
                    file: file,
                    type: 'script',
                    text: str,
                    location: loc
                });
            }
            //reset for next tag:
            str = '';
            isJS = null;
            skip = null;
            loc = null;
        }
    });

    parser.write(htmlTXT);

    return ret;
}

/**
  * Reads html file, and strips everything from it thats not part of some javascript. The original formatting of the file is not modified (tabs, linebreaks remain), but every other character that's not part of a js is replaced by space.
  * @param file Has to be a valid html file
  * @returns String the parsed file string
  */
module.exports.extractJSToString = function (file) {
    var ret = "";

    var htmlTXT = fs.readFileSync(file, 'utf-8');

    var scripts = extractJS(file);

    if (scripts.length === 0) return "";

    var sortBy = require('lodash.sortby');
    scripts = sortBy(scripts, (script) => {
        return script.location.startOffset;
    });

    //parse html character entities in attributes, replace them, add padding to preserve lengthof the attribute.
    //WARNING this will mess up positions, but only inside the current attribute value, it wont affect global positions. I cant think of a better way to fix this.
    scripts.forEach(script => {
        if (script.type === "embedded") {
            var rep = script.text; //this is the unescaped script text
            var length = script.location.endOffset - script.location.startOffset;
            for (; rep.length < length; rep += " ");
            htmlTXT = htmlTXT.replaceAt(script.location.startOffset, rep);
        }
    });

    var toclear = [];
    toclear.push({
        start: 0,
        end: scripts[0].location.startOffset
    });
    for (var i = 0; i < scripts.length - 1; i++) {
        toclear.push({
            start: scripts[i].location.endOffset,
            end: scripts[i + 1].location.startOffset
        });
    };
    toclear.push({
        start: scripts[scripts.length - 1].location.endOffset,
        end: htmlTXT.length
    });

    toclear.forEach(clear => {
        var rep = "";
        for (var i = clear.start; i < clear.end; i++) {
            var c = htmlTXT[i];
            if ((c === '\t') || (c === '\n')) {
                rep += c;
            } else {
                rep += ' ';
            }
        }
        htmlTXT = htmlTXT.replaceAt(clear.start, rep);

    });

    return htmlTXT;
}



// UTILS

/**
 * Replace a substring in a string with another. example: "hello".replaceAt(4, "p", 2) === "help"
 * @param index the starting point from where to start replacing
 * @param replacement the replacement string
 * @param numOfChar the number of characters that will be deleted from the string. DEFAULT = replacement.length
 * @return String the result string
 */
String.prototype.replaceAt = function (index, replacement) {
    return this.substr(0, index) + replacement + this.substr(index + replacement.length);
}