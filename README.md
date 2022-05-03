![](OpenStaticAnalyzer/doc/logo/OSA_small.png)
# OpenStaticAnalyzer™
Copyright (c) 2004-2022 Department of Software Engineering, University of Szeged, Hungary.

## About

OpenStaticAnalyzer is a source code analyzer tool, which can perform deep static analysis of the source code of complex systems.

The source code of a program is usually its only up-to-date documentation. At the same time, the source code is the exquisite bearer of knowledge, business processes and methodology, accumulated over a long period of time. Source code quality decrease, which happens due to many quick fixes and time pressure, results in the increase of development and testing costs, and operational risks. In spite of this, the source code usually receives hostile treatment and is merely considered as a tool.

OpenStaticAnalyzer provides deep static analysis of source code. Using the results of the analysis, the quality of the analyzed source code can be improved and developed both in the short- and long term in a directed way.

### Product characteristics

The most important product characteristics of OpenStaticAnalyzer are the following:
- Platform-independent command line tools
- Transparent integration into build processes
- Powerful filter management
- Coding issue detection:
    - Metric threshold violations (MetricHunter module)
    - Common programming mistakes (clang-tidy)
    - [Cppcheck] 2.5 coding rule violation
    - Re-prioritized and carefully selected [PMD] 6.32.0 coding rule violations
    - [SpotBugs] 4.2.2 coding rule violations
    - [Pylint] 1.9.4 and 2.3.1 coding rule violations
    - FxCop coding rule violations
    - Roslyn Analyzer coding rule violations
    - [ESLint] coding rule violations
    - [SONARQUBE™] platform 8.0 (“SonarQube” in the following) coding rule violations
- Clone detection (copy-pasted source code fragments) extended with clone tracking and "clone smells"
    - Syntax-based, so-called Type-2 clones
- Metrics calculation at component, file, package, class, method, and function levels:
    - Source code metrics
    - Clone metrics
    - Coding rule violation metrics
- Supported languages: Java, Python, C#, JavaScript, C/C++.

[Cppcheck]:http://cppcheck.sourceforge.net/
[PMD]:https://pmd.github.io
[SpotBugs]:https://spotbugs.github.io
[Pylint]:http://www.pylint.org/
[ESLint]:https://eslint.org/
[SONARQUBE™]:https://www.sonarqube.org

By continuous static analysis, the software developers can:
- reduce the software erosion rate and this way decrease development costs;
- coding problems can be identified before testing, so the number of test iterations and the testing costs can be reduced;
- the number of errors in delivered software can be reduced, so the operational risks can be decreased, increasing the company's reputation.

## License
OpenStaticAnalyzer 5.0 is licensed under the [European Union Public Licence](https://joinup.ec.europa.eu/software/page/eupl) (EUPL) v1.2.

OpenStaticAnalyzer is free software, distributed in the hope that it will be useful, but on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the LICENSE file for more details.

## Documentation

### User's Guide

[Java](OpenStaticAnalyzer/java/doc/usersguide/md/Main.md)

[Python](OpenStaticAnalyzer/python/doc/usersguide/md/Main.md)

[C#](OpenStaticAnalyzer/csharp/doc/usersguide/md/Main.md)

[JavaScript](OpenStaticAnalyzer/javascript/doc/usersguide/md/Main.md)

[C/C++](OpenStaticAnalyzer/cpp/doc/usersguide/md/Main.md)

### How to compile

In order to build the OpenStaticAnalyzer software package the following tools are required:


- CMake 3.19.0
- Compiler
    - Linux : gcc 10.2
    - Windows : Microsoft Visual Studio 2017, NASM 2.14, Perl 5.30
        - Install Windows 8.1 SDK and Windows Universal CRT SDK in Visual Studio Installer (if Visual Studio is already installed, then run the installer, Modify > Individual components > Install)
- JDK 11
- Gradle 5.3
- Ant 1.10
- Apache Maven 3.2.5
- Pandoc 1.16
- Node 12.x.x
- Ninja (for building the clang on windows)


Some of the 3rd party libraries are used as a submodule so either `--recursive` 
parameter has to be used with the `git clone` command, or they have to be 
initialized immediately after the cloning with the `git submodule update 
--init --recursive` command. OpenStaticAnalyzer uses CMake for generating the 
platform dependent build files. After cloning the source code into an 
`OpenStaticAnalyzer` directory and creating a `Build` directory next to it, it can be 
built by executing the following commands in the `Build` directory:

- Linux:
    
        cmake ../OpenStaticAnalyzer -G "Unix Makefiles"
        make OpenStaticAnalyzer-Package

- Windows:

    - Building with Visual Studio 2017 IDE
    
        `cmake ..\OpenStaticAnalyzer -G "Visual Studio 15 2017 Win64"`
   
        Open the generated OpenStaticAnalyzer.sln file with the VS IDE and build the `Columbus\OpenStaticAnalyzer\OpenStaticAnalyzer-Package` project to generate the OpenStaticAnalyzer package.
    
    - Building from command line
        
        Activate the VS 2017 compiler environment. For example:
        
        `"c:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\Common7\Tools\VsMSBuildCmd.bat"`
        
        Then execute the following commands in the same terminal.
        
        ```
        cmake ..\OpenStaticAnalyzer -G "Visual Studio 15 2017 Win64"
        msbuild /p:Configuration=Release /m /t:Build OpenStaticAnalyzer\OpenStaticAnalyzer-Package.vcxproj
        ```    

The generated build directory hierarchy can be so deep that due to the length limit of the path on Windows (260 characters) the build can fail. In this case a new drive should be associated with the directory containing the source and build directories with the `subst` command, from which the build can be run.

### How to contribute
Coming soon, stay tuned!
