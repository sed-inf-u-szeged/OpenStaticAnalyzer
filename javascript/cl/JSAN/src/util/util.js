/**
 * Check whether a parameter is undefined or null.
 *
 * Used in command line parsing.
 *
 * @param parameter
 * @returns {boolean}
 */
export function isNull(parameter) {
    return typeof parameter === "undefined" || parameter === null;
}

/**
 * Trim shebang to avoid parse error
 * Doing it this way will preserve the original absolute positions
 * This snippet is taken from: https://github.com/jquery/esprima/issues/1151#issuecomment-85706244
 * @param code the loaded code that might include starting shebang
 * @returns the stripped source code
 */
export function trimHashbang(code) {
    if (code.substring(0, 2) === '#!') {
        let end = code.indexOf('\n');
        let filler = '';
        for (let i = 0; i < end; ++i) {
            filler += ' ';
        }
        code = filler + code.substring(end, code.length);
        console.log("Leading shebang was removed");
    }
    return code;
}