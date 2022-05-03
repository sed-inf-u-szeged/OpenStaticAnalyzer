const path = require('path');
const webpack = require('webpack');


module.exports = {
    target: "node",
    node: {
        __dirname: false,
    },
    entry: "./src/index.js",
    output: {
        filename: "JSAN.js",
        path: path.resolve(__dirname, "dist")
    },
    module: {
        rules: [
            {
                test: /\.node$/,
                loader: "node-loader",
                options: {
                    name: "[name].[ext]"
                }
            },
        ]
    },
    plugins: [
        new webpack.BannerPlugin({
            banner: 'fullhash:[fullhash], chunkhash:[chunkhash], name:[name], base:[base], query:[query], file:[file]',
        })
    ]
}
