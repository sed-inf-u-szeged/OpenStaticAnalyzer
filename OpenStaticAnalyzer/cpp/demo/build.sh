#!/bin/sh

cd log4cplus-1.1.0

make distclean

export OSA_DISABLE_ANALYSIS=true
./configure CXX=clang++  CC=clang
unset OSA_DISABLE_ANALYSIS

make
