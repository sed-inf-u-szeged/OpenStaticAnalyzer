# OpenStaticAnalyzer™ for Python

![](../../../doc/logo/OSA_small.png)

# Introduction

OpenStaticAnalyzer for Python is a source code analyzer tool, which can perform deep static analysis of the source code of complex Python systems.

The source code of a program is usually its only up-to-date documentation. At the same time, the source code is the exquisite bearer of knowledge, business processes and methodology, accumulated over a long period of time. Source code quality decrease, which happens due to many quick fixes and time pressure, results in the increase of development and testing costs, and operational risks. In spite of this, the source code usually receives hostile treatment and is merely considered as a tool.

OpenStaticAnalyzer provides deep static analysis of source code. Using the results of the analysis, the quality of the analyzed source code can be improved and developed both in the short- and long term in a directed way.

## Product characteristics

The most important product characteristics of OpenStaticAnalyzer are the following:

- Platform-independent command line tools

- Transparent integration into build processes

- Powerful filter management

- Coding issue detection:

    - Metric threshold violations (MetricHunter module)

    - [Pylint] 1.9.4 and 2.3.1 coding rule violations

    - [SONARQUBE™] platform 8.0 (“SonarQube” in the following) coding rule violations

- Clone detection (copy-pasted source code fragments) extended with clone tracking and "clone smells"

    - Syntax-based, so-called Type-2 clones

- Metrics calculation at component, file, module, class, and method levels:

    - Source code metrics

    - Clone metrics

    - Coding rule violation metrics

[Pylint]:http://www.pylint.org/
[SONARQUBE™]:https://www.sonarqube.org

By continuous static analysis, the software developers can:

- reduce the software erosion rate and this way decrease development costs;

- coding problems can be identified before testing, so the number of test iterations and the testing costs can be reduced;

- the number of errors in delivered software can be reduced, so the operational risks can be decreased, increasing the company's reputation.

OpenStaticAnalyzer can analyze source code conforming to Python 2.7.x, 3.8.x and earlier versions.
It is sufficient to set the source directory of the project to be analyzed.

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

In order to use OpenStaticAnalyzer it is necessary to have Python 2.7 or 3.x installed on the computer.

For Pylint coding rule violations Pylint 1.9.4 (for Python 2.7) or 2.3.1 (Python >= 3.0) also must be installed.
In the case of a different version, the collected violations may be incomplete or incorrect.

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
It can be executed with the command line program AnalyzerPython.

The OpenStaticAnalyzer for Python package contains the following directories and files:

Windows:

-------------------  -----------------------  --------------------------------------
Analyzer\\Python
                     Demo                     \# Example project directory
                     Tools                    \# ASG checker and exporter tools directory
                     AnalyzerPython.exe       \# Program file to execute the analysis
                     UsersGuide.html          \# User's guide
-------------------  -----------------------  ---------------------------------------

Linux:

-------------------  -----------------------  --------------------------------------
Analyzer/Python
                     Demo                     \# Example project directory
                     Tools                    \# ASG checker and exporter tools directory
                     AnalyzerPython           \# Program file to execute the analysis
                     UsersGuide.html          \# User's guide
-------------------  -----------------------  --------------------------------------

# Preconditions

It is enough to give only the directory of the source code (project directory). The only requirement is that the Python files shall be available under this directory. The results will be created regardless of the possible import errors of the Python modules.

# Command line parameters

OpenStaticAnalyzer can be executed with the following parameters:

**-help**

  : It displays the detailed help and exits.

**-resultsDir**

  : Relative or absolute path name of the directory where the results of the analysis will be stored. The directory will be created automatically if it does not exist.

**-projectName**

  : The name of the analyzed software system. The name specified here will be used for storing the results.

**-externalHardFilter**

  : Filter file specified with relative or absolute path, to filter out certain files from the analysis based on their path names.
Filtered files will not appear in the results. The filter file is a simple text file containing lines starting with '+' or '-' characters followed by a regular expression[^2]. Tip: you can use the \Q and \E anchors to make a substring literal, reducing the need of escaping backslashes. During the analysis, each input file will be checked for these expressions. If the first character of the last matching expression is '-', then the given file will be excluded from the analysis. If the first character of the last matching expression is '+', or there is no matching expression, then the file will be analyzed. A line starting with a different character than '-' or '+' will be ignored. On Windows the checking is case-insensitive. Example filter file content:

        # Filter out all source files starting with "test":
        -test[^\.]*.py
        # But test576.py is needed:
        +test576.py
        # Furthermore, files beginning with "test1742" are also needed:
        +test1742[^\.]*.py
        # Finally, test1742_b.py is not needed:
        -test1742_b.py

**-runMetricHunter**

  : This parameter turns on or off the MetricHunter module. With this feature, OpenStaticAnalyzer lists metric threshold violations. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "true".

**-runDCF**

  : This parameter turns on or off the DuplicatedCodeFinder module. With this feature, OpenStaticAnalyzer identifies copy-pasted code fragments. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "true".

**-runMET**

  : This parameter turns on or off the Metric module. With this feature, OpenStaticAnalyzer computes source code metrics. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "true".

**-profileXML**

  : Global configuration file for OpenStaticAnalyzer. Its *tool-options* tag can be used to override the default metric thresholds for the MetricHunter tool or define custom metric formulas for the UserDefinedMetrics tool. Furthermore, its *rule-options* tag can enable/disable or modify the priorities of multiple rules. An example profile xml file is shown below:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.xml}
      <analyzer-profile>
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
          <rule id="ORS" name="Old Raise Syntax" priority="Major" enabled="false"/>
          <rule id="WI" name="Wildcard Import" priority="Critical" enabled="true"/>
        </rule-options>
      </analyzer-profile>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**-runUDM**

  : This parameter turns on or off the UserDefinedMetrics module. With this feature, OpenStaticAnalyzer computes custom source code metrics based on other, previously computed metrics. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is dependent on the presence of custom metric definitions in the profile xml.

**-cloneGenealogy**

  : This parameter turns on or off the tracking of code clones (copy-pasted source code fragments) through the consecutive revisions of the software system. It is required that during the analysis of the different revisions, the values set to projectName and resultsDir remain the same, so OpenStaticAnalyzer will handle them as different revisions of the same system. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "false".

**-cloneMinLines**

  : This parameter sets the minimum required size of each duplication in lines of code. The default value is 20.

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

  : Cleans all but the last n number of timestamped result directory of the current project.

**-projectBaseDir**

  : Directory of the source code to be analyzed specified with relative or absolute path.

**-pythonBinary**

  : Sets Python 2.7/3.x binary executable name (full path is required if its directory is not in PATH).

**-pythonVersion**

  : This parameter sets the Python version (2 or 3).

**-runPylint**

  : This parameter turns on or off the Pylint coding rule violation checking. With this feature, OpenStaticAnalyzer lists coding rule violations detected by Pylint. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "true".

**-pylintOptions**

  : Passes command line options to Pylint. Options with arguments can be passed with successive -pylintOptions options. For example, to filter out directories and python files named "tests", the "-pylintOptions:--ignore=tests" option must be specified.

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

  : The pattern file or pattern directory for LIM2Patterns. By default it searches for the predefined Anti Patterns found in Common/Patterns/AntiPatterns.

# Usage

OpenStaticAnalyzer can be used by simply invoking it on a directory containing the Python source modules.
The analysis works as follows:

- If the directory contains an \_\_init\_\_.py file, OpenStaticAnalyzer analyzes the given directory (i.e. a python package) recursively while it founds a corresponding \_\_init\_\_.py file in the appropriate sub-directories.

- If the directory does not contain an \_\_init\_\_.py file, OpenStaticAnalyzer checks all the first level sub-directories of the given directory and analyzes each of them containing an \_\_init\_\_.py file recursively (like in the above case).

- In order to analyze python files not forming a python package, an empty \_\_init\_\_.py file needs to be added to the analysis directory.


Execute the following command to analyze the source code of a software system:

   Example (Windows):

     C:\Users\UserName\Analyzer\Python\AnalyzerPython
       -projectName=MyProject
       -projectBaseDir=MyProjectDir
       -resultsDir=Results

   Example (Linux):

     ~$ Analyzer/Python/AnalyzerPython
       -projectName=MyProject
       -projectBaseDir=MyProjectDir
       -resultsDir=Results


# Result files

If any problems occur in the execution of the tools of the OpenStaticAnalyzer package during the code analysis, OpenStaticAnalyzer returns with error code 1. The error code of the given tool appears on the screen (detailed information on the bug can be found in the log directory), and the analysis is stopped, but the result files created until the failure are not deleted.

An error-free execution of OpenStaticAnalyzer produces the following files:

- Files containing the results of the static analysis in the results directory (set by the resultsDir parameter):

    - \$(projectName)\\python\\\$(DATE)\\\$(projectName)-\*.csv

        CSV (comma separated values) files containing different metrics: Component, Folder, File, Package, Module, Class, Method, Function, and Attribute level source code metrics, rule violation counts, and clone-related metrics at CloneClass and CloneInstance level.

    - \$(projectName)\\python\\\$(DATE)\\\$(projectName)-clones.txt

        List of the code clones (copy-pasted source code fragments) in the system.

    - \$(projectName)\\python\\\$(DATE)\\\$(projectName)-MetricHunter.txt

        List of the MetricHunter metric value violations in the system.

    - \$(projectName)\\python\\\$(DATE)\\\$(projectName)-Pylint.txt

        List of the Pylint coding rule violations in the system.

    - \$(projectName)\\python\\\$(DATE)\\\$(projectName).graph

        Binary representation of the result graph containing all the metrics, code clones and coding rule violations.

    - \$(projectName)\\python\\\$(DATE)\\\$(projectName).xml

        XML representation of the result graph containing all the metrics, code clones and coding rule violations.

    - \$(projectName)\\python\\\$(projectName).gsi

        Binary data file containing information for tracking the code clones through the consecutive revisions of the analyzed software system.

    - \$(projectName)\\python\\\$(DATE)\\\$(projectName).sarif

        SARIF representation of the rule violations.

    - \$(projectName)\\python\\\$(DATE)\\\$(projectName)-summary.graph

        Binary representation of the summary result graph containing only the System component node.

    - \$(projectName)\\python\\\$(DATE)\\\$(projectName)-summary.xml

        XML representation of the summary result graph containing only the System component node.

    - \$(projectName)\\python\\\$(DATE)\\\$(projectName)-summary.json

        JSON representation of the summary result graph containing only the System component node.

- Other files and directories created in the results directory:

    - \$(projectName)\\python\\\$(DATE)\\analyzer

        Directory, which contains configuration, binary, ASG, log, and temporary files created during the source code analysis.

    - \$(projectName)\\python\\\$(DATE)\\analyzer\\asg

        Directory, which contains backup copies of the ASG and LIM files, the corresponding filter files, and the GSI file.

    - \$(projectName)\\python\\\$(DATE)\\analyzer\\graph

        Directory, which contains backup copies of the graph files.

    - \$(projectName)\\python\\\$(DATE)\\analyzer\\log

        Directory, which contains the log files created during the code analysis.

    - \$(projectName)\\python\\\$(DATE)\\analyzer\\temp

        Directory, which contains the temporary files created during the code analysis.

# Coding rule violation suppression

The warnings issued by the integrated 3^rd^ party tool (Pylint) can be suppressed with its own official warning suppression mechanisms by modifying the "[MESSAGE CONTROL]" section of the OpenStaticAnalyzer/Python/Tools/Pylint.conf configuration file.

The warnings of the MetricHunter module cannot be suppressed at the moment.

# Demo

The Demo directory of the installation package contains the directory structure, the build and analyzer scripts for the analysis of an example project.
The ceilometer Open Stack Python module is included as the example project, which can also be downloaded from the following URL:

[https://github.com/openstack/ceilometer]

[https://github.com/openstack/ceilometer]:https://github.com/openstack/ceilometer

To perform the source code analysis of the demo project, the analyze.bat/analyze.sh script has to be executed.

Contents of the Demo directory:

Windows:

--------  -------------  --------------------------------------
 Demo\\
           ceilometer     \# source code of OpenStack ceilometer
           analyze.bat    \# starts OpenStaticAnalyzer for Python
           filter.txt     \# a file to filter out the tests directory
--------  -------------  --------------------------------------

Linux:

--------  -------------  --------------------------------------
 Demo/
           ceilometer     \# source code of OpenStack ceilometer
           analyze.sh     \# starts OpenStaticAnalyzer for Python
           filter.txt     \# a file to filter out the tests directory
--------  -------------  --------------------------------------

# Error messages

- Message: Please set the resultsDir parameter. Under this directory a new directory with the name of the analyzed project will be created, if it does not exist yet. All results will be stored there under separate directories with their names containing the date and time.

    Solution: The resultsDir parameter must be set.

- Message: Please set the projectName parameter to the name of the analyzed software system.

    Solution: The projectName parameter must be set.

# Known bugs and deficiencies

Known bugs and deficiencies of OpenStaticAnalyzer for Python.

- OpenStaticAnalyzer places the results into the directory specified by the projectName parameter. If special characters (like '\<', '\>', etc.) are used in the parameter, the analysis will probably fail.

# FAQ

Frequently Asked Questions regarding OpenStaticAnalyzer.

- Problem: On Windows platforms, in case of deep directory hierarchies, it may happen that the full paths of some files exceed 259 characters. In this case some OpenStaticAnalyzer tools may have problems with opening these files; they will terminate and write appropriate messages in the logs.

    Solution: Move the files to be analyzed to a directory closer to the file system root, or use the 'subst' shell command.

# Appendices
