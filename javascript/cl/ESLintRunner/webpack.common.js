const path = require('path');
const CopyPlugin = require('copy-webpack-plugin');
const webpack = require('webpack');
const nodeExternals = require('webpack-node-externals');

module.exports = {
    target: "node",
    externals: [nodeExternals()],
    externalsPresets:{
        node:true
    },
    node: {
        __dirname: false,
    },
    entry: {
        ESLintRunner:"./ESLintRunner.js"
    },
    output: {
        filename: '[name].js',
        path: path.resolve(__dirname, "dist"),
        clean: true,
    },
    optimization: {
        usedExports: 'global',
    },

    module: {
        rules: [
            {
                test: /\.node$/,
                loader: "node-loader",
                exclude: /"node_modules"/,
                options: {
                    name: "[name].[ext]"
                }
            }
        ]
    },

    plugins: [
        new webpack.BannerPlugin({
            banner: 'fullhash:[fullhash], chunkhash:[chunkhash], name:[name], base:[base], query:[query], file:[file]',
        }),
        new CopyPlugin({
            patterns: [{from: 'typescript-eslint.json'}],
        }),
    ]
}
