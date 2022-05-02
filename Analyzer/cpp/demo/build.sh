#!/bin/sh

cd log4cplus-1.1.0

make distclean

export ANALYZER_DISABLE_ANALYSIS=true
./configure CXX=clang++  CC=clang
unset ANALYZER_DISABLE_ANALYSIS

make
