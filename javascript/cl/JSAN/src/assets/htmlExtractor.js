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

import * as fs from "fs";
import * as htmlparser2 from "htmlparser2";
import {sortBy} from 'lodash-es';

const JSEvents = ['onafterprint', 'onbeforeprint', 'onbeforeunload', 'onerror', 'onhashchange', 'onload', 'onmessage', 'onoffline', 'ononline', 'onpagehide', 'onpageshow', 'onpopstate', 'onresize', 'onstorage', 'onunload', 'onblur', 'onchange', 'oncontextmenu', 'onfocus', 'oninput', 'oninvalid', 'onreset', 'onsearch', 'onselect', 'onsubmit', 'onkeydown', 'onkeypress', 'onkeyup', 'onclick', 'ondblclick', 'onmousedown', 'onmousemove', 'onmouseout', 'onmouseover', 'onmouseup', 'onmousewheel', 'onwheel', 'ondrag', 'ondragend', 'ondragenter', 'ondragleave', 'ondragover', 'ondragstart', 'ondrop', 'onscroll', 'oncopy', 'oncut', 'onpaste', 'onabort', 'oncanplay', 'oncanplaythrough', 'oncuechange', 'ondurationchange', 'onemptied', 'onended', 'onerror', 'onloadeddata', 'onloadedmetadata', 'onloadstart', 'onpause', 'onplay', 'onplaying', 'onprogress', 'onratechange', 'onseeked', 'onseeking', 'onstalled', 'onsuspend', 'ontimeupdate', 'onvolumechange', 'onwaiting', 'onshow', 'ontoggle']; //src: https://www.w3schools.com/tags/ref_eventattributes.asp

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

    let htmlTXT = fs.readFileSync(file, 'utf-8');

    /**
     * This method extracts line and column information from a given index.
     * @param startIndex
     * @param endIndex
     * @returns {{endOffset: number, startOffset: number}}
     */
    function extractLocation(startIndex, endIndex) {
        return {
            "endOffset": endIndex,
            "startOffset": startIndex,
        }
    }


    let ret = [];

    let isJS = null; // is set <=> script tag was found
    let skip = null; // is set <=> script tag was found
    let loc = null; // start tag location
    let str = '';   // this is where the scripts text is buffered


    const parser = new htmlparser2.Parser({

        onopentag(name, attrs) {
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
                if (Object.keys(attrs).length === 0) {
                    isJS = true;
                    skip = false;
                } else {
                    for (const [attributeName, attributeValue] of Object.entries(attrs)) {
                        if (attributeName === 'type' && (attributeValue === 'text/javascript' || attributeValue === 'application/javascript')) {
                            isJS = true;
                        }
                        skip = skip || attributeName === 'src';
                    }
                }
            }

            // PARSE anything[onSomeValidEvent='...']
            for (const [attributeName, attributeValue] of Object.entries(attrs)) {
                if (JSEvents.includes(attributeName)) {
                    // fix location to point at the script, not at the tag
                    // (aki ezeknek a pozíciónak a meghatározására tud jobbat, az nyugodtan javítsa)
                    let event = attributeName;
                    let regExp = new RegExp("\\s(" + event + "\\s*=\\s*)(['\"])");
                    // let str = htmlTXT.substr(location.startOffset, location.endOffset - location.startOffset + 1); //text of the html tag
                    let str = htmlTXT.substr(parser.startIndex, parser.endIndex - parser.startIndex + 1); //text of the html tag
                    //kitaláljuk '-t vagy "-t használ e az attribútum
                    let match = regExp.exec(str);
                    let apos = match[2];

                    regExp = new RegExp("\\s(" + event + "\\s*=\\s*" + apos + ")(.*?)(" + apos + ")");
                    match = regExp.exec(str);

                    let rawtext = match[2];
                    let textlength = rawtext.length;
                    let startOffset = parser.startIndex + match.index + match[1].length;
                    let endOffset = startOffset + textlength;

                    ret.push({
                        file: file,
                        type: 'embedded',
                        node: {
                            name: name,
                            attrs: attrs,
                            selfClosing: false,
                            location: extractLocation(startOffset, endOffset)
                            // location: extractLocation(parser.startIndex, parser.endIndex)
                        },
                        event: attributeName,
                        text: attributeValue,
                        location: extractLocation(startOffset, endOffset)
                    });
                    let rep = "";
                    let len = match[0].length;
                    for (let i = 0; i < len; i++) {
                        rep += " ";
                    } //construct an empty string with length of the scriplet found
                    htmlTXT = htmlTXT.replaceAt(match.index, rep); //clear the script, so it wont be parsed twice
                }
            }
        },

        ontext(text) {
            if (isJS && (skip === false)) {
                str += text;
                // dirty hack to get the real positions for text as parser indexes always shows the actual token's index
                const loc2 = extractLocation(parser.startIndex, parser.endIndex);
                if (!loc) {
                    loc = loc2;
                }
                loc.endOffset = loc2.endOffset;
            }
        },

        onclosetag(name) {
            if (name === 'script') {
                if (isJS && (skip === false)) {
                    // dirty hack to get the real ending index of a script
                    loc.endOffset = parser.startIndex;
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
        },
    });

    parser.write(htmlTXT);
    return ret;
}

/**
 * Reads html file, and strips everything from it thats not part of some javascript. The original formatting of the file is not modified (tabs, linebreaks remain), but every other character that's not part of a js is replaced by space.
 * @param file Has to be a valid html file
 * @returns String the parsed file string
 */
let extractJSToString = function (file) {

    let htmlTXT = fs.readFileSync(file, 'utf-8');

    let scripts = extractJS(file);

    if (scripts.length === 0) return "";

    scripts = sortBy(scripts, (script) => {
        return script.location.startOffset;
    });

    //parse html character entities in attributes, replace them, add padding to preserve length of the attribute.
    //WARNING this will mess up positions, but only inside the current attribute value, it wont affect global positions. I cant think of a better way to fix this.
    scripts.forEach(script => {
        if (script.type === "embedded") {
            let rep = script.text; //this is the unescaped script text
            const length = script.location.endOffset - script.location.startOffset;
            for (; rep.length < length; rep += " ") ;
            htmlTXT = htmlTXT.replaceAt(script.location.startOffset, rep);
        }
    });

    let toclear = [];
    toclear.push({
        start: 0,
        end: scripts[0].location.startOffset
    });
    for (let i = 0; i < scripts.length - 1; i++) {
        toclear.push({
            start: scripts[i].location.endOffset,
            end: scripts[i + 1].location.startOffset
        });
    }
    toclear.push({
        start: scripts[scripts.length - 1].location.endOffset,
        end: htmlTXT.length
    });

    toclear.forEach(clear => {
        let rep = "";
        for (let i = clear.start; i < clear.end; i++) {
            const c = htmlTXT[i];
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

export {extractJSToString}
