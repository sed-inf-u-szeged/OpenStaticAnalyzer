const fs = require('fs');
const path = require('path');

/**
 * Deletes esquery's unnecessary 'module' line from package.json
 *
 * With this line being present, the webpacked and minified version of ESLintRunner would throw error:
 *      TypeError: esquery.parse is not a function
 *
 *  See: https://github.com/estools/esquery/issues/123
 */
function fix_esquery() {
    const esquery_path = path.resolve("node_modules", "esquery")
    if (!fs.existsSync(esquery_path)) {
        console.log("esquery path does not exist! Forgot to install modules with 'npm install'?");
    }
    const package_json_path = path.resolve(esquery_path, 'package.json');
    const package_json = JSON.parse(fs.readFileSync(package_json_path));

    if (package_json["module"]) {
        console.log("Bad line found!")
        delete package_json["module"];
        fs.writeFile(package_json_path, JSON.stringify(package_json, null, 2), (err) => {
            if (err) throw err;
            console.log('package.json was modified successfully!');
        });

    } else {
        console.log("Nothing to fix, 'module' was already removed from esquery's package.json!")
    }

}

fix_esquery();
