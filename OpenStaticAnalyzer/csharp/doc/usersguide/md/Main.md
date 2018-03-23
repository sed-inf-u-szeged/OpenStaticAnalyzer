# OpenStaticAnalyzer™ for C\#

![](../../../doc/logo/OSA_small.png)

# Introduction

OpenStaticAnalyzer for C# is a source code analyzer tool, which can perform deep static analysis of the source code of complex C# systems.

The source code of a program is usually its only up-to-date documentation. At the same time, the source code is the exquisite bearer of knowledge, business processes and methodology, accumulated over a long period of time. Source code quality decrease, which happens due to many quick fixes and time pressure, results in the increase of development and testing costs, and operational risks. In spite of this, the source code usually receives hostile treatment and is merely considered as a tool.

OpenStaticAnalyzer provides deep static analysis of source code. Using the results of the analysis, the quality of the analyzed source code can be improved and developed both in the short- and long term in a directed way.

## Product characteristics

The most important product characteristics of OpenStaticAnalyzer are the following:

- Transparent integration into build processes

- Powerful filter management

- Coding issue detection:

    - Metric threshold violations (MetricHunter module)
    
    - FxCop coding rule violations

- Clone detection (copy-pasted source code fragments) extended with clone tracking and "clone smells"

    - Syntax-based, so-called Type-2 clones

- Metrics calculation at component, file, namespace, class, structure, interface and method levels:

    - Source code metrics

    - Clone metrics

    - Coding rule violation metrics

By continuous static analysis, the software developers can:

- reduce the software erosion rate and this way decrease development costs;

- coding problems can be identified before testing, so the number of test iterations and the testing costs can be reduced;

- the number of errors in delivered software can be reduced, so the operational risks can be decreased, increasing the company's reputation.

OpenStaticAnalyzer can analyze source code conforming to C# 6.0.
The following can be analyzed: a solution (.sln), a project (.csproj) or a single source file (.cs). In case of a project or a solution, it is recommended to build it with pdb generation enabled before analyzing, therefore FxCop can be run on the binaries in parallel. See more on this in the FxCop appendix.

With the help of the filtering mechanism it is possible to specify a certain part of the ASG to be used (or not to be used) during the analysis, hence the results can be made more focused and the usage of memory and CPU can be reduced (e.g. generated source files or test code can be filtered out).

## Background

During the static analysis, an Abstract Semantic Graph (ASG) is constructed from the language elements of the source code. This ASG is then processed by the different tools in the package to calculate product metrics, identify copy-pasted code (clones), coding rule violations, etc.

# Installation

## Supported platforms

OpenStaticAnalyzer supports the following x86 and x86-64 platforms:

- Microsoft Windows 7, 8, 8.1, and 10

- Microsoft Windows 2008 R2 Server

- Microsoft Windows 2012 Server

## Requirements

The following software packages are required to be installed:

- [Microsoft .NET Framework 4.5.2 Developer Pack]

- [Microsoft Build Tools 2015]

- [Microsoft Visual C++ 2015  Redistributable Package]

[Microsoft .NET Framework 4.5.2 Developer Pack]:http://www.microsoft.com/en-ca/download/details.aspx?id=42637
[Microsoft Build Tools 2015]:https://www.microsoft.com/en-us/download/details.aspx?id=48159
[Visual Studio 2013]:https://www.visualstudio.com/en-us/downloads/download-visual-studio-vs.aspx
[Visual Studio 2013 SDK]:https://www.microsoft.com/en-us/download/details.aspx?id=40758
[Microsoft Visual C++ 2015  Redistributable Package]:https://www.microsoft.com/en-us/download/details.aspx?id=48145

## Installation package

The OpenStaticAnalyzer installation package can be extracted into any folder and used from that location.
It can be executed with the command line program OpenStaticAnalyzerCsharp.

The OpenStaticAnalyzer for C# package contains the following directories and files:


|                              |                                |                                             |
|------------------------------|--------------------------------|---------------------------------------------|
| OpenStaticAnalyzer\\Csharp\\ |                                |                                             |
|                              | Demo                           | \# Example project directory                |
|                              | WindowsTools                   | \# ASG checker and exporter tools directory |
|                              | OpenStaticAnalyzerCsharp.exe   | \# Program file to execute the analysis     |
|                              | UsersGuide.html                | \# User's guide                             |

# Preconditions

## Solution or Project analysis

The software system shall be compilable with C# 6.0 and the build process with MSBuild.

In order to use OpenStaticAnalyzer for C# it is necessary to meet all the requirements of your project's build process. Before starting the analysis, it is recommended to open your solution in Visual Studio and start a build. If it completed successfully, you can proceed with OpenStaticAnalyzer.
If these conditions are not met, the solution and project files must be modified accordingly.  

OpenStaticAnalyzer creates the ASG files in the result directory.

## Single file analysis

It is possible to analyze a single source file (.cs), which can be provided instead of a solution or project. Analyzing multiple source files without a project is not supported.

# Command line parameters

OpenStaticAnalyzer can be executed with the following parameters:

**-help**

  : It displays the detailed help and exits.

**-resultsDir**

  : Relative or absolute path name of the directory where the results of the analysis will be stored. The directory will be created automatically if it does not exist.

**-projectName**

  : The name of the analyzed software system. The name specified here will be used for storing the results.
  
**-input**
  
  : The solution (.sln), project (.csproj) or C# source (.cs) file to analyze.

**-externalHardFilter**

  : Filter file specified with relative or absolute path, to filter out certain files from the analysis based on their path names. Filtered files will not appear in the results. The filter file is a simple text file containing lines starting with '+' or '-' characters followed by a regular expression[^2]. Tip: you can use the \Q and \E anchors to make a substring literal, reducing the need of escaping backslashes. During the analysis, each input file will be checked for these expressions. If the first character of the last matching expression is '-', then the given file will be excluded from the analysis. If the first character of the last matching expression is '+', or there is no matching expression, then the file will be analyzed. A line starting with a different character than '-' or '+' will be ignored. Checking is case-insensitive. Example filter file content:

        # Filter out all source files starting with "test":
        -test[^\.]*.cs
        # But test576.cs is needed:
        +test576.cs
        # Furthermore, files beginning with "test1742" are also needed:
        +test1742[^\.]*.cs
        # Finally, test1742_b.cs is not needed:
        -test1742_b.cs

**-externalSoftFilter**

  : Filter file specified with relative or absolute path to filter out source code elements (e.g. classes, methods) which are not important for some reason, but could not be filtered out via the externalHardFilter parameter. Source files containing these elements will be analyzed, but the matching results will not be calculated. The filter file is a simple text file containing lines starting with '+' or '-' characters followed by a regular expression. Tip: you can use the \Q and \E anchors to make a substring literal, reducing the need of escaping backslashes. Checking is case-insensitive. After the analysis, those source elements whose absolute path of their source position last matches an expression starting with '-' will not be considered in the results. If the first character of the last matching expression is '+', or there is no matching expression, then the source element will be considered as part of the software system. Example filter file content:

        -C:\\
        +C:\\Users\\UserName\\MyProject\\
        -\\3rd\_party\\
        -\\generated\\
        -\\test\\
        +\\important\.cs
        -\\resource\.cs

  : Directory structure marked with the results of filtering:
  : ![](img/structure.png)

Source code elements in the files marked with darker background will not be considered when creating the results of the analysis.

**-runMetricHunter**

  : This parameter turns on or off the MetricHunter module. With this feature, OpenStaticAnalyzer lists metric threshold violations. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "true".

**-runDCF**

  : This parameter turns on or off the DuplicatedCodeFinder module. With this feature, OpenStaticAnalyzer identifies copy-pasted code fragments. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "true".

**-runMET**

  : This parameter turns on or off the Metric module. With this feature, OpenStaticAnalyzer computes source code metrics. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "true".

**-profileXML**

  : Global configuration file for OpenStaticAnalyzer. Its *tool-options* tag can be used to override the default metric thresholds for the MetricHunter tool. Furthermore, its *rule-options* tag can enable/disable or modify the priorities of multiple rules. An example profile xml file is shown below:

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
    <rule id="AEC" name="Avoid excessive complexity" priority="Minor" enabled="false"/>
    <rule id="DNREIEC" name="Do not raise exceptions in exception clauses" priority="Major" enabled="true"/>
  </rule-options>
</openstaticanalyzer-profile>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


**-cloneGenealogy**

  : This parameter turns on or off the tracking of code clones (copy-pasted source code fragments) through the consecutive revisions of the software system. It is required that during the analysis of the different revisions, the values set to projectName and resultsDir remain the same, so OpenStaticAnalyzer will handle them as different revisions of the same system. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "false".

**-cloneMinLines**

  : This parameter sets the minimum required size of each duplication in lines of code. The default value is 10.

**-csvSeparator**

  : This parameter sets the separator character in the CSV outputs. The default value is the comma (","). The character set here must be placed in quotation marks (e.g. -csvSeparator=";"). Tabulator character can be set by the special "\\t" value.

**-csvDecimalMark**

  : This parameter sets the decimal mark character in the CSV outputs. The default is locale dependent. The character set here must be placed in quotation marks (e.g. -csvDecimalMark=",")

**-maximumThreads**

  : This parameter sets the maximum number of parallel tasks the controller can start. The default value is the number of available CPU cores on the current system.

**-currentDate**

  : The name of the directory with date inside the result directory of the project. If it is not set, then the current date is used.

**-cleanResults**

  : Cleans all but the last n number of timestamped result directory of the current project.

**-runFxCop**

  : This parameter turns on or off the FxCop coding rule violation checking. With this feature, OpenStaticAnalyzer lists coding rule violations detected by FxCop. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "true". FxCop is only able to run if there was a successfull build of the given project with pdb files generated.
  
**-FxCopPath**
  
  : Specifies the the directory which contains the FxCop binaries. If not provided, the program will search through the installed Visual Studio directories and use the latest one if found.

**-configuration**

  : The name of the project configuration.
  
**-platform**

  : The name of the target platform.
  
# Usage

Execute the following command to analyze the source code of a software system:

    OpenStaticAnalyzerCsharp.exe -input="c:\My Project\MyProject.sln" -projectName=MyProject -resultsDir=Results
      -configuration=Debug -platform=AnyCPU


# Result files

If any problems occur in the execution of the tools of the OpenStaticAnalyzer package during the code analysis, OpenStaticAnalyzer returns with error code 1. The error code of the given tool appears on the screen (detailed information on the bug can be found in the log directory), and the analysis is stopped, but the result files created until the failure are not deleted.

An error-free execution of OpenStaticAnalyzer produces the following files:

- Files containing the results of the static analysis in the results directory (set by the resultsDir parameter):

    - \$(projectName)\\csharp\\\$(DATE)\\\$(projectName)-\*.csv

        CSV (comma separated values) files containing different metrics:
Component, File, Namespace, Class, Interface, Structure, Enum, Method, and Attribute level source code metrics, rule violation counts, and clone-related metrics at CloneClass and CloneInstance level.

    - \$(projectName)\\csharp\\\$(DATE)\\\$(projectName)-clones.txt

        List of the code clones (copy-pasted source code fragments) in the system.

    - \$(projectName)\\csharp\\\$(DATE)\\\$(projectName)-MetricHunter.txt

        List of the MetricHunter metric value violations in the system.

    - \$(projectName)\\csharp\\\$(DATE)\\\$(projectName)-FxCop.txt

        List of the FxCop coding rule violations in the system.

    - \$(projectName)\\csharp\\\$(DATE)\\\$(projectName).graph

        Binary representation of the result graph containing all the metrics, code clones and coding rule violations.

    - \$(projectName)\\csharp\\\$(DATE)\\\$(projectName).xml

        XML representation of the result graph containing all the metrics, code clones and coding rule violations.

    - \$(projectName)\\csharp\\\$(projectName).gsi

        Binary data file containing information for tracking the code clones through the consecutive revisions of the analyzed software system.

- Other files and directories created in the results directory:

    - \$(projectName)\\csharp\\\$(DATE)\\openstaticanalyzer

        Directory, which contains configuration, binary, ASG, log, and temporary files created during the source code analysis.

    - \$(projectName)\\csharp\\\$(DATE)\\openstaticanalyzer\\asg

        Directory, which contains the linked ASG and LIM files, the corresponding filter files, and the GSI file.

    - \$(projectName)\\csharp\\\$(DATE)\\openstaticanalyzer\\graph

        Directory, which contains backup copies of the graph files.

    - \$(projectName)\\csharp\\\$(DATE)\\openstaticanalyzer\\log

        Directory, which contains the log files created during the code analysis.

    - \$(projectName)\\csharp\\\$(DATE)\\openstaticanalyzer\\temp

        Directory, which contains the temporary files created during the code analysis.


It is important to note that "standard parts" are not taken into consideration while creating the results. This means that e.g. when a class does not have an explicit superclass, its number of parents (and ancestors) will be 0 (zero) despite the fact that every C# class inherits implicitly from object, which would suggest that the number will be 1. Similarly, other metrics and results also disregard "standard parts".

# Coding rule violation suppression

OpenStaticAnalyzer for C# currently does not have its own coding rule violation checker. We use Microsoft's FxCop and incorporate its results into ours. You can find out more on the [MSDN site of FxCop].

The warnings of MetricHunter cannot be suppressed at the moment.

[MSDN site of FxCop]:https://msdn.microsoft.com/en-us/library/bb429476%28v=vs.80%29.aspx

# Demo

The Demo directory of the installation package contains the directory structure, the build and analyzer scripts for the analysis of an example project.
The log4net open source C# program is included as the example project, which can also be downloaded from the following URL:

[http://archive.apache.org/dist/logging/log4net/source/log4net-1.2.13-src.zip](http://archive.apache.org/dist/logging/log4net/source/log4net-1.2.13-src.zip)

To perform the source code analysis of the demo project, execute the analyze.bat file.

Contents of the Demo directory:

-------------  -----------------------  --------------------------------------
Demo\\
               log4net-1.2.13           \# source code of log4net version 1.2.13
               hardfilter               \# example hardfilter file, see above
               softfilter               \# example softfilter file, see above
               analyze.bat              \# batch file to run the demo analysis
-------------  -----------------------  --------------------------------------

# Error messages

- Message: Please set the resultsDir parameter. Under this directory a new directory with the name of the analyzed project will be created, if it does not exist yet. All results will be stored there under separate directories with their names containing the date and time.

    Solution: The resultsDir parameter must be set.

- Message: Please set the projectName parameter to the name of the analyzed software system.

    Solution: The projectName parameter must be set.

# Known bugs and deficiencies

Known bugs and deficiencies of OpenStaticAnalyzer for C#.

- OpenStaticAnalyzer places the results into the directory specified by the projectName parameter. If special characters (like '\<', '\>', etc.) are used in the parameter, the analysis will probably fail.

- FxCop may not run if placed in a directory containing special characters. To be safe, run OpenStaticAnalyzer and FxCop from a directory containing english letters, numbers, hyphen and underscore only.

# FAQ

Frequently Asked Questions regarding OpenStaticAnalyzer.

- Problem: On Windows platforms, in case of deep directory hierarchies, it may happen that the full paths of some files exceed 259 characters. In this case some OpenStaticAnalyzer tools may have problems with opening these files; they will terminate and write appropriate messages in the logs.

    Solution: Move the files to be analyzed to a directory closer to the file system root, or use the 'subst' shell command.

# Appendices
