#!/bin/sh

set -e
dotnet build log4net-2.0.10/src/log4net.sln
../OpenStaticAnalyzerCSharp -input:log4net-2.0.10/src/log4net.sln -projectName=log4net-2.0.10 -resultsDir=Results -externalSoftFilter=softfilter -externalHardFilter=hardfilter -configuration=Debug -platform=AnyCPU
