#!/bin/sh

../OpenStaticAnalyzerPython -projectBaseDir:ceilometer -projectName:ceilometer -resultsDir:Results -externalHardFilter:filter.txt -pylintOptions:--ignore=tests -pythonVersion:3 -pythonBinary:python3
