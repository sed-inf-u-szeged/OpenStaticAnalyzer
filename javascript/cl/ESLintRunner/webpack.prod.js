const common = require('./webpack.common');
const webpackMerge = require('webpack-merge');
const CleanWebpackPlugin = require('clean-webpack-plugin').CleanWebpackPlugin;

module.exports = webpackMerge.merge(common, {
    mode: "production",
    plugins: [
        new CleanWebpackPlugin()
    ]
});
