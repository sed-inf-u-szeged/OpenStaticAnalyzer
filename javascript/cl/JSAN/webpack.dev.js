const common = require('./webpack.common');
const webpackMerge = require('webpack-merge');

module.exports = webpackMerge.merge(common, {
    mode: "development",
    //devtool: "none",
});
