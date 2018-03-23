@echo off
IF "%VS140COMNTOOLS%" == "" (
  echo No Microsoft Visual Studio 2015 has been found!
  echo The demo project will not be compiled and no fxcop warnings will be generated!
) else (
  call "%VS140COMNTOOLS%vsvars32.bat"
  msbuild log4net-1.2.13\src\log4net.vs2010.csproj /t:Rebuild /p:Configuration=Debug
)
..\OpenStaticAnalyzerCSharp -input:log4net-1.2.13\src\log4net.vs2010.csproj -projectName=log4net-1.2.13 -resultsDir=Results -externalSoftFilter=softfilter -externalHardFilter=hardfilter -configuration=Debug -platform=AnyCPU

