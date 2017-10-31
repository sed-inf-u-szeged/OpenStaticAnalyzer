@echo off
..\OpenStaticAnalyzerJava.exe -projectName=log4j-2.3 -buildScript=build-maven.bat -resultsDir=Results -externalSoftFilter=SoftFilter.txt
