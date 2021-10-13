@echo off
WHERE dotnet >nul 2>nul
IF %ERRORLEVEL% NEQ 0 (
  echo dotnet was not found on PATH
  echo OpenStaticAnalyzer for C# requires the .NET Core SDK to be installed
  echo See the User's Guide for details
  exit /b 1
)

dotnet build log4net-2.0.10\src\log4net.sln
..\OpenStaticAnalyzerCSharp -input:log4net-2.0.10\src\log4net.sln -projectName=log4net-2.0.10 -resultsDir=Results -externalSoftFilter=softfilter -externalHardFilter=hardfilter -configuration=Debug -platform=AnyCPU
