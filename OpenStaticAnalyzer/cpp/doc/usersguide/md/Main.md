# OpenStaticAnalyzer™ for C/C++

![](../../../doc/logo/OSA_small.png)

# Introduction

OpenStaticAnalyzer for C/C++ is a source code analyzer tool, which can perform deep static analysis of the source code of complex C/C++ systems.

The source code of a program is usually its only up-to-date documentation. At the same time, the source code is the exquisite bearer of knowledge, business processes and methodology, accumulated over a long period of time. Source code quality decreases, which happens due to many quick fixes and time pressure, results in the increase of development and testing costs, and operational risks. In spite of this, the source code usually receives hostile treatment and is merely considered as a tool.

OpenStaticAnalyzer provides deep static analysis of source code. Using the results of the analysis, the quality of the analyzed source code can be improved and developed both in the short- and long term in a directed way.

## Product characteristics

The most important product characteristics of OpenStaticAnalyzer are the following:

- Platform-independent command line tools

- Transparent integration into build processes

- Powerful filter management

- Coding issue detection:

    - Common programming mistakes (clang-tidy extended with some additional checkers)

    - Metric threshold violations (MetricHunter module)

    - [Cppcheck] 2.5 coding rule violations

    - [SONARQUBE™] platform 8.0 (“SonarQube” in the following) coding rule violations

- Clone detection (copy-pasted source code fragments) extended with clone tracking and "clone smells"

    - Syntax-based, so-called Type-2 clones

- Metrics calculation at component, file, namespace, class, function and method levels:

    - Source code metrics

    - Clone metrics

    - Coding rule violation metrics

[Cppcheck]:http://cppcheck.sourceforge.net/
[SONARQUBE™]:https://www.sonarqube.org

By continuous static analysis, the software developers can:

- reduce the software erosion rate and this way decrease development costs;

- coding problems can be identified before testing, so the number of test iterations and the testing costs can be reduced;

- the number of errors in delivered software can be reduced, so the operational risks can be decreased, increasing the company's reputation.

OpenStaticAnalyzer supports the C++ language defined by the ISO/IEC 14882:1998, ISO/IEC 14882:2003, ISO/IEC 14882:2011, ISO/IEC 14882:2014, ISO/IEC 14882:2017 international standard extended with several new features from ISO/IEC 14882:2020, and C language defined by the ANSI/ISO 9899:1990, ISO/IEC 9899:1999, ISO/IEC 9899:2011 and ISO/IEC 9899:2017 standards. Besides the standard features, several GNU and Microsoft specific extensions are also supported.

OpenStaticAnalyzer uses a so-called compiler wrapping technique during source code analysis, which means that the code analysis is performed in parallel with the usual build process transparently, by wrapping the calls to the compiler. These is no need to modify the source code or the build system. The analysis results will reflect the actual build configuration of the analyzed system.

With the help of the filtering mechanism it is possible to specify a certain part of the ASG to be used (or not to be used) during the analysis, hence the results can be made more focused and the usage of memory and CPU can be reduced (e.g. generated source files or test code can be filtered out).

[Department of Software Engineering]:http://www.sed.inf.u-szeged.hu/softwarequality

## Background

During the static analysis, an Abstract Semantic Graph (ASG) is constructed from the language elements of the source code. This ASG is then processed by the different tools in the package to calculate product metrics, identify copy-pasted code (clones), coding rule violations, etc.

# Installation

## Supported platforms

OpenStaticAnalyzer supports the following x64 platforms:

- Microsoft Windows 7, 8, 8.1, and 10

- Microsoft Windows 2008 R2 Server

- Microsoft Windows 2012 Server

- GNU/Linux with kernel version 2.6.18 and GNU C library 2.11 or newer

## Requirements

In case of Windows, the Microsoft Visual C++ 2017 Redistributable Package must be installed. It can be downloaded from the following URL:

- [https://aka.ms/vs/15/release/vc_redist.x64.exe] (x64)

[https://aka.ms/vs/15/release/vc_redist.x64.exe]:https://aka.ms/vs/15/release/vc_redist.x64.exe

The Linux package uses the code page conversion functions of the GNU C Library. If the conversion modules are not in the standard /usr/lib/gconv directory then the GCONV_PATH environment variable must be set according to the current installation of the GNU C Library.

E.g.:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.bash}
export "GCONV_PATH=/usr/lib/x86_64-linux-gnu/gconv"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## Installation package

The OpenStaticAnalyzer installation package can be extracted into any folder and used from that location.
It can be executed with the command line program OpenStaticAnalyzerCPP.

The OpenStaticAnalyzer for C/C++ package contains the following directories and files:

Windows:

----------------  -----------------------  --------------------------------------
OpenStaticAnalyzer\\CPP
                  Demo                     \# Example project directory
                  WindowsTools             \# ASG checker and exporter tools directory
                  WindowsWrapper           \# Wrapper and analyzer tools directory
                  OpenStaticAnalyzerCPP.exe       \# Program file to execute the analysis
                  UsersGuide.html          \# User's guide
----------------  -----------------------  ------------------------------------

Linux:

---------------  -----------------------  --------------------------------------
OpenStaticAnalyzer/CPP
                 Demo                     \# Example project directory
                 LinuxTools               \# ASG checker and exporter tools directory
                 LinuxWrapper             \# Wrapper and analyzer tools directory
                 OpenStaticAnalyzerCPP           \# Program file to execute the analysis
                 UsersGuide.html          \# User's guide
---------------  -----------------------  --------------------------------------

# Preconditions

For the easy integration and precise analysis results, OpenStaticAnalyzer uses a so-called "compiler-wrapping" technique.
Although this technique is the best choice in most cases, it has some limitations.
The requirements listed below must be met to enable OpenStaticAnalyzer to analyze the subject system.

  - The PATH environment variable must not change during the build process regarding the compilers.

  - Compilers must not be invoked with relative or with absolute paths during the build process.

  - If the software system uses precompiled headers, then it shall be compilable without using the precompiled headers as well.

Linux:

  - The software system shall be compilable with Clang.

  - The compiler tools have to be in the PATH environment variable when OpenStaticAnalyzer is started.

Windows:

  - The software system shall be compilable with Microsoft Visual Studio 2010/2012/2013/2015/2017/2019.

  - The software system shall be compilable to a 64 bit target.

  - The 64 bit native visual studio compiler environment has to be active when OpenStaticAnalyzer is started.
    The compiler environment can be set up by running the 'x64 Native Tools Command Prompt' or by starting the 'vcvarsall.bat' with the 'amd64' parameter from a command line.
    The location of the 'vcvarsall.bat' depends on the version and the installation of the VisualStudio, but in VS2010-VS2015 usually it can be found in the '%VSINSTALLDIR%\\VC' directory and in VS2017 in the '%VSINSTALLDIR%\\VC\\Auxiliary\\Build' directory.

If these conditions are not met, the build scripts must be modified accordingly. More about this in the chapter *Tips for compiler-wrapping*.

# Command line parameters

OpenStaticAnalyzer can be executed with the following parameters:

**-help**

  : It displays the detailed help and exits.

**-resultsDir**

  : Relative or absolute path name of the directory where the results of the analysis will be stored. The directory will be created automatically if it does not exist.

**-projectName**

  : The name of the analyzed software system. The name specified here will be used for storing the results.

**-buildScript**

  : Relative or absolute path name of the executable build script which manages the build process of the system. If the build script does not return with 0, OpenStaticAnalyzer will stop with an error and no analysis results will be available.

**-externalHardFilter**

  : Filter file specified with relative or absolute path, to filter out certain files from the analysis. Filtered files will not appear in the results. The filter file is a simple text file containing lines starting with '+' or '-' characters followed by a regular expression[^2]. Tip: you can use the \\Q and \\E anchors to make a substring literal, reducing the need of escaping backslashes. During the analysis, the arguments of the wrapped commands  will be checked for these expressions. If the first character of the last matching expression is '-', then the given command will not be wrapped and it will be excluded from the analysis. If the first character of the last matching expression is '+', or there is no matching expression, then the command will be wrapped. A line starting with a different character than '-' or '+' will be ignored. On Windows the checking is case-insensitive. Example filter file content:

        # Filter out commands containing 'conftest':
        -conftest
        # Filter out default 'a.out' binary outputs:
        -a\.out

  : Please note that contrary to other languages, the arguments of the wrapped commands are checked not the names of the input files! If filtering based on arguments would be too difficult (e.g. because the build contains a *configure* step that should be completely disregarded but its subcommands are unknown) then the **OSA_DISABLE_ANALYSIS** environment variable can be specified. While it is set to *true*, every wrappable command will be ignored. A build script using this method is shown in the Usage section.

**-externalSoftFilter**

  : Filter file specified with relative or absolute path to filter out source code elements (e.g. classes, methods) which are not important for some reason, but could not be filtered out via the externalHardFilter parameter. Source files containing these elements will be analyzed, but the matching results will not be calculated. The filter file is a simple text file containing lines starting with '+' or '-' characters followed by a regular expression. Tip: you can use the \\Q and \\E anchors to make a substring literal, reducing the need of escaping backslashes. On Windows the checking is case-insensitive. After the analysis, those source elements whose absolute path of their source position last matches an expression starting with '-' will not be considered in the results. If the first character of the last matching expression is '+', or there is no matching expression, then the source element will be considered as part of the software system. Example filter file content:

        -C:\\
        +C:\\Users\\UserName\\MyProject\\
        -\\3rd\_party\\
        -\\generated\\
        -\\tests\\
        +\\important\.cpp
        -resource\.cpp

  : Directory structure marked with the results of filtering:
  : ![](img/structure.png)

  : Source code elements in the files marked with darker background will not be considered when creating the results of the analysis.

**-runMetricHunter**

  : This parameter turns on or off the MetricHunter module. With this feature, OpenStaticAnalyzer lists metric threshold violations. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "true".

**-runClangTidy**

  : This parameter turns on or off the Clang-tidy coding rule violation checking. With this feature, OpenStaticAnalyzer lists coding rule violations detected by Clang-tidy. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "true".

**-runDCF**

  : This parameter turns on or off the DuplicatedCodeFinder module. With this feature, OpenStaticAnalyzer identifies copy-pasted code fragments. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "true".

**-runMET**

  : This parameter turns on or off the Metric module. With this feature, OpenStaticAnalyzer computes source code metrics. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "true".

**-profileXML**

  : Global configuration file for OpenStaticAnalyzer. Its *tool-options* tag can be used to override the default metric thresholds for the MetricHunter tool or define custom metric formulas for the UserDefinedMetrics tool. Furthermore, its *rule-options* tag can enable/disable or modify the priorities of multiple rules. An example profile xml file is shown below:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.xml}
      <openstaticanalyzer-profile>
        <tool-options>
          <tool name = "MetricHunter" enabled = "true">
              <metric-thresholds>
                  <threshold metric-id="LOC" relation="gt" value="100" entity="Method" />
                  <threshold metric-id="LLOC" relation="gt" value="none" entity="Method" />
                  <threshold metric-id="NUMPAR" relation="gt" value="43" entity="Method" />
                  <threshold metric-id="TLOC" relation="gt" value="-32" entity="Method" />
              </metric-thresholds>
          </tool>
        </tool-options>

        <rule-options>
          <rule id="IL" name="Member Init Order" priority="Critical" enabled="false"/>
          <rule id="ULTZ" name="Unsigned Compare Less Than Zero" priority="Major" enabled="true"/>
        </rule-options>
      </openstaticanalyzer-profile>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**-runUDM**

  : This parameter turns on or off the UserDefinedMetrics module. With this feature, OpenStaticAnalyzer computes custom source code metrics based on other, previously computed metrics. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is dependent on the presence of custom metric definitions in the profile xml.


**-cloneGenealogy**

  : This parameter turns on or off the tracking of code clones (copy-pasted source code fragments) through the consecutive revisions of the software system. It is required that during the analysis of the different revisions, the values set to projectName and resultsDir remain the same, so OpenStaticAnalyzer will handle them as different revisions of the same system. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "false".

**-cloneMinLines**

  : This parameter sets the minimum required size of each duplication in lines of code. The default value is 10.

**-csvSeparator**

  : This parameter sets the separator character in the CSV outputs. The default value is the comma (","). The character set here must be placed in quotation marks (e.g. -csvSeparator=";"). Tabulator character can be set by the special "\\t" value.

**-csvDecimalMark**

  : This parameter sets the decimal mark character in the CSV outputs. The default is value is the dot ("."). The character set here must be placed in quotation marks (e.g. -csvDecimalMark=",").

**-sarifseverity**

  : This parameter sets the severity levels to be saved in the SARIF output. (1 - Info, 2 - Minor, 3 - Major, 4 - Critical, 5 - Blocker, c/C - CloneClass). The value should not be placed in quotation marks (e.g. -sarifseverity=2345c). The default value is 2345c.

**-maximumThreads**

  : This parameter sets the maximum number of parallel tasks the controller can start. The default value is the number of available CPU cores on the current system.

**-currentDate**

  : The name of the directory with date inside the result directory of the project. If it is not set, then the current date is used.

**-cleanResults**

  : Cleans all but the last n number of timestamped result directories of the current project.

**-cleanProject**

  : Removes all files created during the analysis from the given directory recursively.

**-faultTolerant**

  : This parameter turns on or off the fault tolerant mode. In fault tolerant mode if any non critical error happens, then the analysis will continue and some of the results will be generated. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "true".

**-prefix**

  : We can give a certain prefix for the wrapped program names in Linux to wrapp special versions of these. If it is not set then the following commands are wrapped during the analysis:
  : Linux: 'clang', 'clang++', 'ld', 'ar', 'ln'
  : Windows: 'cl', 'lib', 'link', 'clang-cl', 'lld-link', 'llvm-lib'

**-postfix**

  : We can give a certain postfix for the wrapped program names in Linux to wrapp special versions of these. If it is not set then the following commands are wrapped during the analysis:
  : Linux: 'clang', 'clang++', 'ld', 'ar', 'ln'
  : Windows: 'cl', 'lib', 'link', 'clang-cl', 'lld-link', 'llvm-lib

**-runCppcheck**
  : This parameter turns on or off the Cppcheck coding rule violation checking. With this feature, OpenStaticAnalyzer lists coding rule violations detected by Cppcheck. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "true".

**-runSQ**

  : Import issues from SonarQube server.

**-SQHost**

  : The URL address of the SonarQube server.

**-SQPort**

  : The port of the SonarQube server.

**-SQProjectKey**

  : The key of the project in the SonarQube server.

**-SQProjectPrefix**

  : Prefix path of the project's base directory (the path of the sonar-project.properties file).

**-SQUserName**

  : The user name for the SonarQube server.

**-SQPassword**

  : The password for the SonarQube server.

**-SQLanguageKey**

  : The key of the language in SonarQube.

**-runLIM2Patterns**

  : This parameter can be used to enable or disable the LIM2Patterns module during analysis (default = on). 

**-pattern**

  : The pattern file or pattern directory for LIM2Patterns. By default it searches for the predefined Anti Patterns found in Tools/Patterns/AntiPatterns.

# Usage

The following steps have to be performed to analyze the source code of a software system:

1.  The static analysis requires a build script, which contains the commands needed to compile the software system. If this build script is not readily available, it must be prepared as shown in the following example.

        ---------- build.bat ------------
        msbuild /t:Rebuild /p:Configuration=Release /p:Platform=Win32 Example.sln

        -------- build.sh ------------
        #!/bin/sh
        export OSA_DISABLE_ANALYSIS=true
        ./configure
        unset OSA_DISABLE_ANALYSIS
        ./make


2.  Create hard and/or soft filter file(s) to filter out unnecessary (e.g. external, generated, or unit tests) source code, if necessary.

        ---------- SoftFilter.txt ------------
        -C:\\Users\\UserName\\MyProject\\src\\generated
        +C:\\Users\\UserName\\MyProject

        ---------- HardFilter.txt --------
        -conftest


3.  Execute OpenStaticAnalyzer:

    Example (Windows):

        C:\Users\UserName\OpenStaticAnalyzer\CPP\OpenStaticAnalyzerCPP
         -projectName=MyProject
         -buildScript=MyProject\\build.bat
         -resultsDir=Results
         -externalSoftFilter=SoftFilter.txt
         -externalHardFilter=HardFilter.txt

    Example (Linux):

        ~$ OpenStaticAnalyzer/CPP/OpenStaticAnalyzerCPP
         -projectName=MyProject
         -buildScript=MyProject/build.sh
         -resultsDir=Results
         -externalSoftFilter=SoftFilter.txt
         -externalHardFilter=HardFilter.txt


# Result files

If any critical problems occur in the execution of the tools of the OpenStaticAnalyzer package during the code analysis, OpenStaticAnalyzer returns with non zero exit code. The error code of the given tool appears on the screen (detailed information on the bug can be found in the log directory), and the analysis stops, but the result files created until the failure are not deleted. Unless the fault tolerant mode is disabled the OpenStaticAnalyzer tries to generate as much result as it can with tolerating the not critical errors. If the fault tolerant mode is disabled with the faultTolerant parameter, then the analysis will stop in case of any error.

An error-free execution of OpenStaticAnalyzer produces the following files:

- Files containing the results of the static analysis in the results directory (set by the resultsDir parameter):

    - \$(projectName)\\cpp\\\$(DATE)\\\$(projectName)-\*.csv

        CSV (comma separated values) files containing different metrics:
Component, File, Namespace, Class, Interface, Enum, Method, Attribute, and Function level source code metrics, rule violation counts, and clone-related metrics at CloneClass and CloneInstance level.

    - \$(projectName)\\cpp\\\$(DATE)\\\$(projectName)-clones.txt

        List of the code clones (copy-pasted source code fragments) in the system.

    - \$(projectName)\\cpp\\\$(DATE)\\\$(projectName)-MetricHunter.txt

        List of the MetricHunter metric value violations in the system.

    - \$(projectName)\\cpp\\\$(DATE)\\\$(projectName)-ClangTidy.txt

        List of the clang-tidy coding rule violations in the system.

    - \$(projectName)\\cpp\\\$(DATE)\\\$(projectName)-Cppcheck.txt

        List of the Cppcheck coding rule violations in the system.

    - \$(projectName)\\cpp\\\$(DATE)\\\$(projectName).graph

        Binary representation of the result graph containing all the metrics, code clones and coding rule violations.

    - \$(projectName)\\cpp\\\$(DATE)\\\$(projectName).xml

        XML representation of the result graph containing all the metrics, code clones and coding rule violations.

    - \$(projectName)\\cpp\\\$(projectName).gsi

        Binary data file containing information for tracking the code clones through the consecutive revisions of the analyzed software system.

    - \$(projectName)\\cpp\\\$(DATE)\\\$(projectName).sarif

        SARIF representation of the rule violations.

    - \$(projectName)\\cpp\\\$(DATE)\\\$(projectName)-summary.graph

        Binary representation of the summary result graph containing only the System component node.

    - \$(projectName)\\cpp\\\$(DATE)\\\$(projectName)-summary.xml

        XML representation of the summary result graph containing only the System component node.

    - \$(projectName)\\cpp\\\$(DATE)\\\$(projectName)-summary.json

        JSON representation of the summary result graph containing only the System component node.

- Other files and directories created in the results directory:

    - \$(projectName)\\cpp\\\$(DATE)\\openstaticanalyzer

        Directory, which contains configuration, binary, ASG, log, and temporary files created during the source code analysis.

    - \$(projectName)\\cpp\\\$(DATE)\\openstaticanalyzer\\asg

        Directory, which contains backup copies of the linked ASG and LIM files, the corresponding filter files, and the GSI file.

    - \$(projectName)\\cpp\\\$(DATE)\\openstaticanalyzer\\graph

        Directory, which contains backup copies of the graph files.

    - \$(projectName)\\cpp\\\$(DATE)\\openstaticanalyzer\\log

        Directory, which contains the log files created during the code analysis.

    - \$(projectName)\\cpp\\\$(DATE)\\openstaticanalyzer\\temp

        Directory, which contains the temporary files created during the code analysis.

- Files created outside the results directory:

    - .csi

        C/C++ language dependent ASG file. The .csi files are created in the .columbus_cpp directory located in the directory of the corresponding object files of the compiled C/C++ source files.

    - .lcsi

        Linked C/C++ language dependent ASG file. It is created in the .columbus_cpp sub-directory of the directory containing the corresponding binary file (binary executable, shared object) produced by the linker programs.

    - .acsi

        Archive of C/C++ language dependent ASG files. The .acsi files are created in the .columbus_cpp directory located in the directory of the corresponding static library files produced by the ‘ar’ program.

    - .fcsi

        Filter file belonging to the linked C/C++ language dependent ASG file (.lcsi). It is created in the corresponding directory of the .lcsi file.

# Coding rule violation suppression

The warnings issued by the rule checker modules can be suppressed in case they are found to be invalid or for any other reason. In the case of the integrated 3^rd^ party Cppcheck tool and clang-tidy the warnings can be suppressed with the inline comment suppression mechanism of the tools.

Example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.cpp}
class A {
  bool operator=(const A&) {
    // cppcheck-suppress unusedVariable
    int i;  // NOLINT
  }
};
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In this example, the "variable 'i' is not initialized" warning of the clang-tidy module and the "Unused variable" warning of Cppcheck will be suppressed.

The warnings of MetricHunter cannot be suppressed at the moment.

# Demo

The Demo directory of the installation package contains the directory structure, the build and analyzer scripts for the analysis of an example project.
The log4cplus open source program is included as the example project, which can also be downloaded from the following URL:

[http://sourceforge.net/projects/log4cplus/files/log4cplus-stable/1.1.0/log4cplus-1.1.0.tar.gz]

[http://sourceforge.net/projects/log4cplus/files/log4cplus-stable/1.1.0/log4cplus-1.1.0.tar.gz]:http://sourceforge.net/projects/log4cplus/files/log4cplus-stable/1.1.0/log4cplus-1.1.0.tar.gz

To perform the source code analysis of the demo project, the analyze.bat/analyze.sh script has to be executed.

Contents of the Demo directory:

Windows:

----------- ---------------------------- --------------------------------------
Demo\\
             log4cplus                    \# log4cplus project
             log4cplus\\log4cplus-1.1.0    \# source code of log4cplus
             log4cplus\\build.bat          \# builds log4cplus
             log4cplus\\analyze.bat        \# starts the analysis
             log4cplus\\softfilter.txt     \# softfilter
----------- ---------------------------- --------------------------------------

Linux:

----------- ---------------------------- --------------------------------------
Demo/
             log4cplus                    \# log4cplus project
             log4cplus/log4cplus-1.1.0    \# source code of log4cplus
             log4cplus/build.sh           \# builds log4cplus
             log4cplus/analyze.sh         \# starts the analysis
             log4cplus/softfilter.txt     \# softfilter
----------- ---------------------------- --------------------------------------

# Error messages

- Message: Please set the resultsDir parameter. Under this directory a new directory with the name of the analyzed project will be created, if it does not exist yet. All results will be stored there under separate directories with their names containing the date and time.

    Solution: The resultsDir parameter must be set.

- Message: Please set the projectName parameter to the name of the analyzed software system.

    Solution: The projectName parameter must be set.

- Message: Please set the buildScript parameter. This is the script, which will build the project.

    Solution: The buildScript parameter must be set.

# Known bugs and deficiencies

Known bugs and deficiencies of OpenStaticAnalyzer for C/C++.

- OpenStaticAnalyzer places the results into the directory specified by the projectName parameter. If special characters (like '\<', '\>', etc.) are used in the parameter, the analysis will probably fail.

# FAQ

Frequently Asked Questions regarding OpenStaticAnalyzer.

- Problem: After starting the analysis, the computer does not show elevated load and none of the OpenStaticAnalyzer tools are running.

    Solution: OpenStaticAnalyzer creates temporary files during the analysis (e.g. tmp-wrapper.bat) which might be judged as suspicious by certain antivirus programs so they may block them. In these cases, the temporary files must be manually whitelisted.

- Problem: On Windows platforms, in case of deep directory hierarchies, it may happen that the full paths of some files exceed 259 characters. In this case some OpenStaticAnalyzer tools may have problems with opening these files; they will terminate and write appropriate messages in the logs.

    Solution: Move the files to be analyzed to a directory closer to the file system root, or use the 'subst' shell command.

- Problem: Analysis of a VS2008 project stops with a critical error of the CAN2Lim task.

    Solution: Use to 'devenv' command for building the project instead of the 'msbuild' or 'vcbuild' commands.

# Appendices
