# OpenStaticAnalyzer™ for Java

![](../../../doc/logo/OSA_small.png)

# Introduction

OpenStaticAnalyzer for Java is a source code analyzer tool, which can perform deep static analysis of the source code of complex Java systems.

The source code of a program is usually its only up-to-date documentation. At the same time, the source code is the exquisite bearer of knowledge, business processes and methodology, accumulated over a long period of time. Source code quality decrease, which happens due to many quick fixes and time pressure, results in the increase of development and testing costs, and operational risks. In spite of this, the source code usually receives hostile treatment and is merely considered as a tool.

OpenStaticAnalyzer provides deep static analysis of source code. Using the results of the analysis, the quality of the analyzed source code can be improved and developed both in the short- and long term in a directed way.

## Product characteristics

The most important product characteristics of OpenStaticAnalyzer are the following:

- Platform-independent command line tools

- Powerful filter management

- Coding issue detection:

    - Metric threshold violations (MetricHunter module)

    - Re-prioritized and carefully selected [PMD] 6.32.0 coding rule violations [^3]

    - [SpotBugs] 4.2.2 coding rule violations

    - [SONARQUBE™] platform 8.0 (“SonarQube” in the following) coding rule violations

- Clone detection (copy-pasted source code fragments) extended with clone tracking and "clone smells"

    - Syntax-based, so-called Type-2 clones

- Metrics calculation at component, file, package, class, and method levels:

    - Source code metrics

    - Clone metrics

    - Coding rule violation metrics

[PMD]:https://pmd.github.io
[SpotBugs]:https://spotbugs.github.io
[SONARQUBE™]:https://www.sonarqube.org

By continuous static analysis, the software developers can:

- reduce the software erosion rate and this way decrease development costs;

- coding problems can be identified before testing, so the number of test iterations and the testing costs can be reduced;

- the number of errors in delivered software can be reduced, so the operational risks can be decreased, increasing the company's reputation.

OpenStaticAnalyzer can analyze source code conforming to Java 11.

With the help of the filtering mechanism it is possible to specify a certain part of the ASG to be used (or not to be used) during the analysis, hence the results can be made more focused and the usage of memory and CPU can be reduced (e.g. generated source files or test code can be filtered out).

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

In order to use OpenStaticAnalyzer it is necessary to have JDK 11 installed on the computer and the necessary environment variables must be set correctly (JAVA\_HOME, PATH).

In case of Windows, the Microsoft Visual C++ 2017 Redistributable Package must be installed. It can be downloaded from the following URL:

- [https://aka.ms/vs/15/release/vc_redist.x64.exe] (x64)

[https://aka.ms/vs/15/release/vc_redist.x64.exe]:https://aka.ms/vs/15/release/vc_redist.x64.exe

The Linux package uses bash scripts.

The Linux package uses the code page conversion functions of the GNU C Library. If the conversion modules are not in the standard /usr/lib/gconv directory then the GCONV\_PATH environment variable must be set according to the current installation of the GNU C Library.

E.g.: for the Windows package:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.bash}
set "JAVA_HOME=C:\Program Files\Java\jdk-11.0.2"
set "PATH=%ANT_HOME%\bin;%JAVA_HOME%\bin;%M2_HOME%\bin;%PATH%"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

E.g.: for the Linux package:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.bash}
export "JAVA_HOME=/opt/jdk-11.0.2"
export "PATH=$ANT_HOME/bin:$JAVA_HOME/bin:$M2_HOME/bin:$PATH"
export "GCONV_PATH=/usr/lib/x86_64-linux-gnu/gconv"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## Installation package

The OpenStaticAnalyzer installation package can be extracted into any folder and used from that location.
It can be executed with the command line program AnalyzerJava.

The OpenStaticAnalyzer for Java package contains the following directories and files:

Windows:

-----------------  -----------------------  --------------------------------------
Analyzer\\Java\\
                   Demo                     \# Example project directory
                   WindowsTools             \# ASG checker and exporter tools directory
                   WindowsWrapper           \# Wrapper and analyzer tools directory
                   AnalyzerJava.exe         \# Program file to execute the analysis
                   UsersGuide.html          \# User's guide
-----------------  -----------------------  ---------------------------------------

Linux:

-------------------  -----------------------  --------------------------------------
Analyzer/Java/
                     Demo                     \# Example project directory
                     LinuxTools               \# ASG checker and exporter tools directory
                     LinuxWrapper             \# Wrapper and analyzer tools directory
                     AnalyzerJava             \# Program file to execute the analysis
                     UsersGuide.html          \# User's guide
-------------------  -----------------------  --------------------------------------




# Preconditions

- The java files shall be compilable with Java 11.

- If specific javac options are necessary for the compilation (classpath, sourcepath, target, etc.), these have to be specified to OpenStaticAnalyzer as well.

In order to increase the accuracy of the analysis, external jar files with the missing types can be set with the javacOptions command line parameter.

# Command line parameters

OpenStaticAnalyzer can be executed with the following parameters:

**-help**

  : It displays the detailed help and exits.

**-resultsDir**

  : Relative or absolute path name of the directory where the results of the analysis will be stored. The directory will be created automatically if it does not exist.

**-projectName**

  : The name of the analyzed software system. The name specified here will be used for storing the results.

**-externalHardFilter**

  : Filter file specified with relative or absolute path, to filter out certain files from the analysis based on their path names. Filtered files will not appear in the results. The filter file is a simple text file containing lines starting with '+' or '-' characters followed by a regular expression[^2]. Tip: you can use the \Q and \E anchors to make a substring literal, reducing the need of escaping backslashes. During the analysis, each input file will be checked for these expressions. If the first character of the last matching expression is '-', then the given file will be excluded from the analysis. If the first character of the last matching expression is '+', or there is no matching expression, then the file will be analyzed. A line starting with a different character than '-' or '+' will be ignored. On Windows the checking is case-insensitive. Example filter file content:

        # Filter out all source files starting with "test":
        -test[^\.]*.java
        # But test576.java is needed:
        +test576.java
        # Furthermore, files beginning with "test1742" are also needed:
        +test1742[^\.]*.java
        # Finally, test1742_b.java is not needed:
        -test1742_b.java

**-externalSoftFilter**

  : Filter file specified with relative or absolute path to filter out source code elements (e.g. classes, methods) which are not important for some reason, but could not be filtered out via the externalHardFilter parameter. Source files containing these elements will be analyzed, but the matching results will not be calculated. The filter file is a simple text file containing lines starting with '+' or '-' characters followed by a regular expression. Tip: you can use the \Q and \E anchors to make a substring literal, reducing the need of escaping backslashes. On Windows the checking is case-insensitive. After the analysis, those source elements whose absolute path of their source position last matches an expression starting with '-' will not be considered in the results. If the first character of the last matching expression is '+', or there is no matching expression, then the source element will be considered as part of the software system. Example filter file content:

        -C:\\
        +C:\\Users\\UserName\\MyProject\\
        -\\3rd\_party\\
        -\\generated\\
        -\\test\\
        +\\important\.java
        -resource\.java

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
          <rule id="ECB" name="Empty Catch Block" priority="Critical" enabled="false"/>
          <rule id="AFLV" name="Avoid Final Local Variable" priority="Major" enabled="true"/>
        </rule-options>
      </analyzer-profile>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**-runUDM**

  : This parameter turns on or off the UserDefinedMetrics module. With this feature, OpenStaticAnalyzer computes custom source code metrics based on other, previously computed metrics. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is dependent on the presence of custom metric definitions in the profile xml.

**-rulesCSV**

  : There are certain rule violations that are computed by more than one tool. E.g. ADLIBDC (Avoid Decimal Literals In BigDecimal Constructor) is checked by both SpotBugs and PMD. In these cases, in order to avoid duplications, there is a priority order among the tools. This parameter can be used to override these default priorizations by specifying a .csv file in the following format:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.csv}
      toolId;FB;PMD
      ...
      ADLIBDC;1;2
      ADNIS;-;1
      ADS;-;1
      AEAI;-;1
      ...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

**-cleanProject**

  : Removes all files (from the directory set by the projectBaseDir parameter) created during the analysis (.ljsi, .fjsi files in the .columbus_java directories), but does not remove anything from the results directory (resultsDir). Its value can be "true" (turn this feature on, setting projectBaseDir is mandatory in this case) or "false" (turn this feature off). The default value is "false".

**-projectBaseDir**

  : Directory of the source code to be analyzed specified with relative or absolute path. Using this option the directory analysis mode will be activated. Setting projectBaseDir is mandatory.

**-javacOptions**

  : In directory analysis mode, the necessary parameters for compilation can be set with this option, like classpath for instance (e.g. -javacOptions="-cp .;mydir/classpath"[^1]). The classpath given by this option is added to the auxiliary classpath of the PMD as well.

**-JVMOptions**

  : Extra parameters can be added for the JVM used by OpenStaticAnalyzer. For instance the maximum available memory of the JVM can be set manually if the default value (1/4 of the physical memory) is not enough.

**-runFB**

  : This parameter turns on or off the SpotBugs coding rule violation checking. With this feature, OpenStaticAnalyzer lists coding rule violations detected by SpotBugs. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "true". Currently, SpotBugs is invoked only in the case of Directory analysis mode. The FBFileList parameter has to be provided.

**-FBFileList**

  : List file with binary inputs (class or jar files). If it is set then OpenStaticAnalyzer lists coding rule violations detected by the SpotBugs tool. The given Java binaries have to be compiled with debug information.

**-FBOptions**

  : Extra command line parameters for SpotBugs can be set with this option. For instance if some auxiliary classes are needed, these can be set by adding the -FBOptions="-auxclasspath external.jar" option.

**-runPMD**

  : This parameter turns on or off the PMD coding rule violation checking. With this feature, OpenStaticAnalyzer lists coding rule violations detected by PMD, such as unused variables, empty catch blocks, etc. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "true".

**-pmdOptions**

  : In directory analysis mode, the necessary parameters required by PMD can be set with this option, like the version or encoding for instance (e.g. -pmdOptions="-version 1.4 -encoding UTF-8").

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

It can be used by simply invoking it on the directory, which contains the source files.

Execute the following command to analyze the source code of a software system:

  Example (Windows):

    AnalyzerJava -projectName=MyProject -projectBaseDir=MyProjectDir
    -resultsDir=Results -runFB=true -FBFileList=filelist.txt

  Example (Linux):

    AnalyzerJava -projectName=MyProject -projectBaseDir=MyProjectDir
    -resultsDir=Results -runFB=true -FBFileList=filelist.txt

If the directory does not contain all the source files or it uses already compiled binaries (.class files), then the precise analysis might require the compilation parameters of the standard javac Java compiler.

  Example (Windows):

    AnalyzerJava -projectName=MyProject -projectBaseDir=MyProjectDir
    -resultsDir=Results -javacOptions="-cp .;..\\..\\classes"

  Example (Linux):

    AnalyzerJava -projectName=MyProject -projectBaseDir=MyProjectDir
    -resultsDir=Results -javacOptions="-cp .:../../classes"

where "../../classes" is the directory of the class files needed for compilation.


# Result files

If any problems occur in the execution of the tools of the OpenStaticAnalyzer package during the code analysis, OpenStaticAnalyzer returns with error code 1. The error code of the given tool appears on the screen (detailed information on the bug can be found in the log directory), and the analysis is stopped, but the result files created until the failure are not deleted.

An error-free execution of OpenStaticAnalyzer produces the following files:

- Files containing the results of the static analysis in the results directory (set by the resultsDir parameter):

    - \$(projectName)\\java\\\$(DATE)\\\$(projectName)-\*.csv

        CSV (comma separated values) files containing different metrics:
Component, File, Package, Class, Interface, Enum, Method, Attribute, and Annotation level source code metrics, rule violation counts, and clone-related metrics at CloneClass and CloneInstance level.

    - \$(projectName)\\java\\\$(DATE)\\\$(projectName)-clones.txt

        List of the code clones (copy-pasted source code fragments) in the system.

    - \$(projectName)\\java\\\$(DATE)\\\$(projectName)-MetricHunter.txt

        List of the MetricHunter metric value violations in the system.

    - \$(projectName)\\java\\\$(DATE)\\\$(projectName)-PMD.txt

        List of the PMD coding rule violations in the system.

    - \$(projectName)\\java\\\$(DATE)\\\$(projectName)-FindBugs.txt

        List of the SpotBugs coding rule violations in the system.

    - \$(projectName)\\java\\\$(DATE)\\\$(projectName).graph

        Binary representation of the result graph containing all the metrics, code clones and coding rule violations.

    - \$(projectName)\\java\\\$(DATE)\\\$(projectName).xml

        XML representation of the result graph containing all the metrics, code clones and coding rule violations.

    - \$(projectName)\\java\\\$(projectName).gsi

        Binary data file containing information for tracking the code clones through the consecutive revisions of the analyzed software system.

    - \$(projectName)\\java\\\$(DATE)\\\$(projectName).sarif

        SARIF representation of the rule violations.

    - \$(projectName)\\java\\\$(DATE)\\\$(projectName)-summary.graph

        Binary representation of the summary result graph containing only the System component node.

    - \$(projectName)\\java\\\$(DATE)\\\$(projectName)-summary.xml

        XML representation of the summary result graph containing only the System component node.

    - \$(projectName)\\java\\\$(DATE)\\\$(projectName)-summary.json

        JSON representation of the summary result graph containing only the System component node.

- Other files and directories created in the results directory:

    - \$(projectName)\\java\\\$(DATE)\\analyzer

        Directory, which contains configuration, binary, ASG, log, and temporary files created during the source code analysis.

    - \$(projectName)\\java\\\$(DATE)\\analyzer\\asg

        Directory, which contains backup copies of the linked ASG and LIM files, the corresponding filter files, and the GSI file.

    - \$(projectName)\\java\\\$(DATE)\\analyzer\\graph

        Directory, which contains backup copies of the graph files.

    - \$(projectName)\\java\\\$(DATE)\\analyzer\\log

        Directory, which contains the log files created during the code analysis.

    - \$(projectName)\\java\\\$(DATE)\\analyzer\\temp

        Directory, which contains the temporary files created during the code analysis.

- Files created outside the results directory:

    - .ljsi

        Linked Java language dependent ASG file. One .ljsi file is created in the .columbus_java sub-directory of the directory set by the projectBaseDir parameter.

    - .fjsi

        Filter file belonging to the linked Java language dependent ASG file (.ljsi). It is created in the corresponding directory of the .ljsi file.


It is important to note that "standard parts" are not taken into consideration while creating the results. This means that e.g. when a class does not have an explicit superclass, its number of parents (and ancestors) will be 0 (zero) despite the fact that every Java class inherits implicitly from Object, which would suggest that the number will be 1. Similarly, other metrics and results also disregard "standard parts".

# Coding rule violation suppression

The warnings issued by the rule checker modules can be suppressed in case they are found to be invalid or for any other reason. In the case of the integrated 3^rd^ party tools (PMD, SpotBugs) the warnings can be suppressed with their own official warning suppression mechanisms.

Example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {

  @SuppressWarnings("PMD")
  public void goo() {
  }

}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In this example, all PMD warnings in the method "goo".

The warnings of the MetricHunter module cannot be suppressed at the moment.

# Demo

The Demo directory of the installation package contains the directory structure, the build and analyzer scripts for the analysis of an example project.
Version 1.2.17 of the log4j open source program are included as example projects, which can also be downloaded from the following URLs:

[http://archive.apache.org/dist/logging/log4j/1.2.17/log4j-1.2.17.zip]

[http://archive.apache.org/dist/logging/log4j/1.2.17/log4j-1.2.17.zip]:http://archive.apache.org/dist/logging/log4j/1.2.17/log4j-1.2.17.zip

To perform the source code analysis of the demo project, one of the analyze-dir.bat/analyze-dir.sh scripts has to be executed.

Contents of the Demo directory:

Windows:

-------------  -----------------------  --------------------------------------
Demo\\
               apache-log4j-1.2.17      \# source code of log4j version 1.2.17
               analyze-dir.bat          \# starts OpenStaticAnalyzer in Directory analysis mode
-------------  -----------------------  --------------------------------------

Linux:

-------------  -----------------------  --------------------------------------
Demo/
               apache-log4j-1.2.17      \# source code of log4j version 1.2.17
               analyze-dir.sh           \# starts OpenStaticAnalyzer in Directory analysis mode
-------------  -----------------------  --------------------------------------

# Error messages

- Message: Please set the resultsDir parameter. Under this directory a new directory with the name of the analyzed project will be created, if it does not exist yet. All results will be stored there under separate directories with their names containing the date and time.

    Solution: The resultsDir parameter must be set.

- Message: Please set the projectName parameter to the name of the analyzed software system.

    Solution: The projectName parameter must be set.

- Message: Please set the projectBaseDir parameter.

    Solution: The projectBaseDir parameters must be set.

- Message: Required java version is Java 11

    Solution: In order to use OpenStaticAnalyzer the installation of JDK 11 version is required, and the corresponding environment variables must be set correctly.

- Message: ASG list file does not exist: .../analyzer/log/superlinklist.txt

    Solution 2: Check if the JAVA\_HOME and PATH environment variables are set to the appropriate JDK and they do not point to some JRE. In the latter case the .../analyzer/log/build.log file will contain an error message similar to the following:

        Unable to find a javac compiler; com.sun.tools.javac.Main is not on the classpath.
        Perhaps JAVA_HOME does not point to the JDK.

        It is currently set to "c:\Program Files\Java\jre11"

- Message: exec returned: 255

    If any of the log files in the the
    \$(projectName)\\\$(DATE)\\analyzer\\log directory starts with "Could not load a transcoding service", then the GCONV\_PATH should be set to the current gconv directory. Check the "Requirements" section of the user's guide.

# Known bugs and deficiencies

Known bugs and deficiencies of OpenStaticAnalyzer for Java.

- Regarding the computation of most of the metrics the init and static init blocks of Java classes, and lambdas are not taken into consideration.

- OpenStaticAnalyzer places the results into the directory specified by the projectName parameter. If special characters (like '\<', '\>', etc.) are used in the parameter, the analysis will probably fail.

# FAQ

Frequently Asked Questions regarding OpenStaticAnalyzer.

- Problem: After starting the analysis, neither does the computer show elevated load nor is any of the OpenStaticAnalyzer tools running.

    Solution: OpenStaticAnalyzer creates temporary files during the analysis (e.g. tmp-wrapper.bat) which might be judged as suspicious by certain antivirus programs so they may block them. In these cases, the temporary files must be manually whitelisted.

- Problem: On Windows platforms, in case of deep directory hierarchies, it may happen that the full paths of some files exceed 259 characters. In this case some OpenStaticAnalyzer tools may have problems with opening these files; they will terminate and write appropriate messages in the logs.

    Solution: Move the files to be analyzed to a directory closer to the file system root, or use the 'subst' shell command.

# Appendices
