@echo off

call ..\AnalyzerPython.exe -projectBaseDir:ceilometer -projectName:ceilometer -resultsDir:Results -externalHardFilter:filter.txt -pylintOptions:--ignore=tests -pythonVersion:3 -pythonBinary:python
