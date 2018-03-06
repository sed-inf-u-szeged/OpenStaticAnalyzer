# OpenStaticAnalyzer™ for Java

![](../../../doc/logo/OSA_small.png)

# Introduction

OpenStaticAnalyzer for Java is a source code analyzer tool, which can perform deep static analysis of the source code of complex Java systems.

The source code of a program is usually its only up-to-date documentation. At the same time, the source code is the exquisite bearer of knowledge, business processes and methodology, accumulated over a long period of time. Source code quality decrease, which happens due to many quick fixes and time pressure, results in the increase of development and testing costs, and operational risks. In spite of this, the source code usually receives hostile treatment and is merely considered as a tool.

OpenStaticAnalyzer provides deep static analysis of source code. Using the results of the analysis, the quality of the analyzed source code can be improved and developed both in the short- and long term in a directed way.

## Product characteristics

The most important product characteristics of OpenStaticAnalyzer are the following:

- Platform-independent command line tools

- Transparent integration into build processes

- Powerful filter management

- Coding issue detection:

    - Metric threshold violations (MetricHunter module)

    - Re-prioritized and carefully selected [PMD] 5.2.3 coding rule violations

    - [FindBugs] 3.0.0 coding rule violations

- Clone detection (copy-pasted source code fragments) extended with clone tracking and "clone smells"

    - Syntax-based, so-called Type-2 clones

- Metrics calculation at component, file, package, class, and method levels:

    - Source code metrics

    - Clone metrics

    - Coding rule violation metrics

[PMD]:http://pmd.sourceforge.net/
[FindBugs]:http://findbugs.sourceforge.net

By continuous static analysis, the software developers can:

- reduce the software erosion rate and this way decrease development costs;

- coding problems can be identified before testing, so the number of test iterations and the testing costs can be reduced;

- the number of errors in delivered software can be reduced, so the operational risks can be decreased, increasing the company's reputation.

OpenStaticAnalyzer can analyze source code conforming to Java 1.8.
Two kinds of analysis processes are supported in the current version.
For smaller systems, it is sufficient to set the source directory of the project to be analyzed and its classpath and java compiler settings, if needed.
For more complex systems it is advised to analyze the system through its Ant or Maven build process.
In this case, the analysis runs in parallel with the compilation process by wrapping the Ant or the Maven program.

With the help of the filtering mechanism it is possible to specify a certain part of the ASG to be used (or not to be used) during the analysis, hence the results can be made more focused and the usage of memory and CPU can be reduced (e.g. generated source files or test code can be filtered out).

## Background

During the static analysis, an Abstract Semantic Graph (ASG) is constructed from the language elements of the source code. This ASG is then processed by the different tools in the package to calculate product metrics, identify copy-pasted code (clones), coding rule violations, etc.


# Installation

## Supported platforms

OpenStaticAnalyzer supports the following x86 and x86-64 platforms:

- Microsoft Windows 7, 8, 8.1, and 10

- Microsoft Windows 2008 R2 Server

- Microsoft Windows 2012 Server

- GNU/Linux with kernel version 2.6.18 and GNU C library 2.11 or newer

## Requirements

In order to use OpenStaticAnalyzer it is necessary to have JDK 1.8 or newer installed on the computer and the necessary environment variables must be set correctly (JAVA\_HOME, PATH).

In case of Windows, the appropriate Microsoft Visual C++ 2015 Redistributable Package must be installed. It can be downloaded from the following URL:

- [https://www.microsoft.com/en-us/download/details.aspx?id=48145] (x86/x64)

[https://www.microsoft.com/en-us/download/details.aspx?id=48145]:https://www.microsoft.com/en-us/download/details.aspx?id=48145

If the Maven build analysis will be used then Maven 2.2.1, 3.0.5, 3.1.1, 3.2.2 or 3.2.5 has to be installed with the necessary environment variable (M2\_HOME).

The Linux package uses bash scripts.

The Linux package uses the code page conversion functions of the GNU C Library. If the conversion modules are not in the standard /usr/lib/gconv directory then the GCONV\_PATH environment variable must be set according to the current installation of the GNU C Library.

E.g.: for the Windows package:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.bash}
set "JAVA_HOME=C:\Program Files\Java\jdk1.8.0_31"
set "M2_HOME=C:\Program Files\apache-maven-3.2.5"
set "PATH=%ANT_HOME%\bin;%JAVA_HOME%\bin;%M2_HOME%\bin;%PATH%"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

E.g.: for the Linux package:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.bash}
export "JAVA_HOME=/opt/jdk1.8.0_31"
export "M2_HOME=/opt/apache-maven-3.2.5"
export "PATH=$ANT_HOME/bin:$JAVA_HOME/bin:$M2_HOME/bin:$PATH"
export "GCONV_PATH=/usr/lib/x86_64-linux-gnu/gconv"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## Installation package

The OpenStaticAnalyzer installation package can be extracted into any folder and used from that location.
It can be executed with the command line program OpenStaticAnalyzerJava.

The OpenStaticAnalyzer for Java package contains the following directories and files:

Windows:

|                            |                            |                                               |
|----------------------------|----------------------------|-----------------------------------------------|
|OpenStaticAnalyzer\\Java\\  |                            |                                               |
|                            | Demo                       |   \# Example project directory                |
|                            | WindowsTools               |   \# ASG checker and exporter tools directory |
|                            | WindowsWrapper             |   \# Wrapper and analyzer tools directory     |
|                            | OpenStaticAnalyzerJava.exe |   \# Program file to execute the analysis     |
|                            | installMavenWrapper.bat    |  \# Batch file to install the Maven wrapper   |
|                            | UsersGuide.html            |  \# User's guide                              |


Linux:

|                            |                           |                                             |
|----------------------------|---------------------------|---------------------------------------------|
|OpenStaticAnalyzer/Java/    |                           |                                             |
|                            | Demo                      | \# Example project directory                |
|                            | LinuxTools                | \# ASG checker and exporter tools directory |
|                            | LinuxWrapper              | \# Wrapper and analyzer tools directory     |
|                            | OpenStaticAnalyzerJava    | \# Program file to execute the analysis     |
|                            | installMavenWrapper.sh    | \# Shell script to install the Maven wrapper|
|                            | UsersGuide.html           | \# User's guide                             |



To analyze Maven based projects, installMavenWrapper.bat (in case of Windows) or installMavenWrapper.sh (in case of Linux) must be executed in an environment where all the necessary environment variables of Maven are set and the user has write privilege for the Maven repository required for the install.

During the execution of these scripts, every file required by OpenStaticAnalyzer will be installed to the local Maven repository. These are the following:

- Inside the .m2/repository directory a hu/u-szeged/OpenStaticAnalyzer/OpenStaticAnalyzer-Maven-plugin-mojo-executer directory hierarchy will be created that contains:

    - 2.2.1/OpenStaticAnalyzer-Maven-plugin-mojo-executer-2.2.1.jar

    - 2.2.1/OpenStaticAnalyzer-Maven-plugin-mojo-executer-2.2.1.pom

    - 3.0/OpenStaticAnalyzer-Maven-plugin-mojo-executer-3.0.jar

    - 3.0/OpenStaticAnalyzer-Maven-plugin-mojo-executer-3.0.pom

    - 3.1/OpenStaticAnalyzer-Maven-plugin-mojo-executer-3.1.jar

    - 3.1/OpenStaticAnalyzer-Maven-plugin-mojo-executer-3.1.pom

- Inside the .m2/repository/org/apache/maven/plugins directory a OpenStaticAnalyzer-maven-plugin/7.0 directory hierarchy will be created that contains:

    - OpenStaticAnalyzer-maven-plugin-7.0.jar

    - OpenStaticAnalyzer-maven-plugin-7.0.pom


If the local Maven repository is deleted then the appropriate installMavenWrapper batch/script must be executed again for the wrapper to function correctly.

# Preconditions

## Ant build analysis

For the easy integration and precise analysis results, OpenStaticAnalyzer uses a so-called "wrapping" technique.
Although this technique is the best choice in Ant build environments, it has its own limitations.
The requirements listed below must be met to enable OpenStaticAnalyzer to analyze the subject system.

- The software system shall be compilable with Java 1.8 and the build process must be managed with Ant version 1.8.4 or higher.

- The PATH environment variable must not change during the build process regarding the compilers.

- Compilers must not be invoked with relative or with absolute paths during the build process (only by name).

- Since the analyzer redefines the javac, jar, war, ear, copy and delete tasks of Ant, if these tasks are redefined again during the build process, the analyzer might not produce the expected results.

- If the desired functionality of the redefined tasks are reached via non-standard ways (e.g. by calling external programs), then the wrapper might erroneously finish running. For instance, if the exec task is used for the compilation instead of the javac task, the analyzer will not be invoked. Similarly, if archiving is done via the exec tasks instead of proper archiving tasks, then the temporary files of the analysis might become archived too.

- The wrapper does not support performing tasks in parallel.

If these conditions are not met, the build scripts must be modified accordingly.

Using Ant build, besides the class files created by the standard javac compiler, OpenStaticAnalyzer creates the ASG files next to the class files. The different archiving tasks (jar, war, ear) trigger the linking of ASG files of the classes too, besides their usual tasks. Using the move, copy, and delete tasks in the build scripts are allowed, the operation will have the proper effect on the results of the static analysis as well.

## Maven build analysis

Similarly to the Ant build analysis, OpenStaticAnalyzer uses the so-called "wrapping" technique also in the case of the Maven build analysis. Although this technique is the best choice in Maven build environments, it has its own limitations. The requirements listed below must be met to enable OpenStaticAnalyzer to analyze the subject system.

- The software system shall be compilable with Java 1.8 and the build process must be managed with Maven versions 2.2.1, 3.0.5, 3.1.1, 3.2.2 or 3.2.5.

- Maven's built-in compiler plugin must execute the compilation, its built-in jar plugin must do the packaging and its built-in install and deploy plugins must be responsible for the placement of the final artifacts in the local or remote repositories, respectively.

- Only those parts of the system are taken into consideration during the analysis which are either placed inside a jar archive by Maven's packaging plugin (org.apache.maven.plugins:maven-jar-plugin) or installed to the local repository by Maven's install plugin (org.apache.maven.plugins:maven-install-plugin).

- The wrapper does not support performing tasks in parallel.

All created output artifacts are placed in the local repository.

## Directory analysis

If Ant build scripts are not available, the so-called directory analysis mode can be used. In this case, it is enough to give only the directory of the source code (project directory) and a build script is not required. The only requirement in this case is the following:

- The java files shall be compilable with Java 1.8.

- If specific javac options are necessary for the compilation (classpath, sourcepath, target, etc.), these have to be specified to OpenStaticAnalyzer as well.

In this analysis mode, the results may be less accurate, the possible compiler errors occur only as warnings, the results will be created, but the accuracy cannot be guaranteed mainly because of eventually missing types. In order to increase the accuracy of the analysis, external jar files with the missing types can be set with the javacOptions command line parameter.

# Command line parameters

OpenStaticAnalyzer can be executed with the following parameters:

**-help**

  : It displays the detailed help and exits.

**-resultsDir**

  : Relative or absolute path name of the directory where the results of the analysis will be stored. The directory will be created automatically if it does not exist.

**-projectName**

  : The name of the analyzed software system. The name specified here will be used for storing the results.

**-buildScript**

  : Relative or absolute path name of the executable build script which manages the build process of the system. Using this option the Ant or Maven build analysis mode will be activated. If the build script does not return with 0, OpenStaticAnalyzer will stop with an error and no analysis results will be available.

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
          <rule id="ECB" name="Empty Catch Block" priority="Critical" enabled="false"/>
          <rule id="AFLV" name="Avoid Final Local Variable" priority="Major" enabled="true"/>
        </rule-options>
      </openstaticanalyzer-profile>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**-rulesCSV**

  : There are certain rule violations that are computed by more than one tool. E.g. ADLIBDC (Avoid Decimal Literals In BigDecimal Constructor) is checked by both FindBugs and PMD. In these cases, in order to avoid duplications, there is a priority order among the tools. This parameter can be used to override these default priorizations by specifying a .csv file in the following format:

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

  : This parameter sets the minimum required size of each duplication in lines of code. The default value is 10.

**-csvSeparator**

  : This parameter sets the separator character in the CSV outputs. The default value is the comma (","). The character set here must be placed in quotation marks (e.g. -csvSeparator=";"). Tabulator character can be set by the special "\\t" value.

**-csvDecimalMark**

  : This parameter sets the decimal mark character in the CSV outputs. The default is value is the dot ("."). The character set here must be placed in quotation marks (e.g. -csvDecimalMark=",").

**-maximumThreads**

  : This parameter sets the maximum number of parallel tasks the controller can start. The default value is the number of available CPU cores on the current system.

**-currentDate**

  : The name of the directory with date inside the result directory of the project. If it is not set, then the current date is used.

**-cleanResults**
  
  : Cleans all but the last n number of timestamped result directory of the current project.

**-cleanProject**

  : Removes all files (from the directory set by the projectBaseDir parameter) created during the analysis (in case of directory or Ant build analysis .jsi, .ljsi, .fjsi files in the .columbus_java directories, in case of Maven build analysis .ajsi, .list, and other temp files in the target/openstaticanalyzer directories), but does not remove anything from the results directory (resultsDir). Its value can be "true" (turn this feature on, setting projectBaseDir is mandatory in this case) or "false" (turn this feature off). The default value is "false".

**-projectBaseDir**

  : Directory of the source code to be analyzed specified with relative or absolute path. Using this option the directory analysis mode will be activated. Setting projectBaseDir is mandatory, if buildScript is not set. If both buildScript and projectBaseDir are set, then the Ant or Maven build analysis mode will be activated.

**-javacOptions**

  : In directory analysis mode, the necessary parameters for compilation can be set with this option, like classpath for instance (e.g. -javacOptions="-cp .;mydir/classpath"[^1]). The classpath given by this option is added to the auxiliary classpath of the PMD as well.

**-JVMOptions**

  : Extra parameters can be added for the JVM used by OpenStaticAnalyzer. For instance the maximum available memory of the JVM can be set manually if the default value (1/4 of the physical memory) is not enough.

**-runFB**

  : This parameter turns on or off the FindBugs coding rule violation checking. With this feature, OpenStaticAnalyzer lists coding rule violations detected by FindBugs. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "true". Currently, FindBugs is invoked only in the case of Directory analysis mode. The FBFileList parameter has to be provided.

**-FBFileList**

  : List file with binary inputs (class or jar files). If it is set then OpenStaticAnalyzer lists coding rule violations detected by the FindBugs tool. The given Java binaries have to be compiled with debug information.

**-FBOptions**

  : Extra command line parameters for FindBugs can be set with this option. For instance if some auxiliary classes are needed, these can be set by adding the -FBOptions="-auxclasspath external.jar" option.

**-runPMD**

  : This parameter turns on or off the PMD coding rule violation checking. With this feature, OpenStaticAnalyzer lists coding rule violations detected by PMD, such as unused variables, empty catch blocks, etc. Its value can be "true" (turn this feature on) or "false" (turn this feature off). The default value is "true".

**-pmdOptions**

  : In directory analysis mode, the necessary parameters required by PMD can be set with this option, like the version or encoding for instance (e.g. -pmdOptions="-version 1.4 -encoding UTF-8").

**-mavenFilter=regexp**

  : In Maven build analysis mode, the results of previous module builds and analyses are stored in the Maven repository. When analyzing a module, the ASGs of its dependencies are automatically downloaded from this repository. The regexp value of this parameter can specify which module's results should be downloaded (regexp should fit to [groupId]:[artifactID]:[Version]) and considered while creating the final results. This parameter only applies to Maven builds; in other cases, it will be ignored.

# Usage

There are two ways to use OpenStaticAnalyzer. It can be used by simply invoking it on the directory, which contains the source files, or it can be invoked with an Ant or a Maven build script.

## Ant and Maven build analysis

The following steps have to be performed to analyze the source code of a software system:

1.  The static analysis requires a build script, which contains the commands needed to compile the software system. If this build script is not readily available, it must be prepared as it can be seen in the following example.

    Ant example (Windows):

        ---------- build.bat ------------
        @echo off
        ant -f MyProject\build.xml clean jar


    Ant example (Linux):

        -------- build.sh ------------
        #!/bin/sh
        ant -f MyProject/build.xml clean jar

    Maven example (Windows):

        ---------- build.bat ------------
        @echo off
        mvn -f MyProject\pom.xml clean install -DskipTests

    Maven example (Linux):

        ---------- build.sh ------------
        #!/bin/sh
        mvn -f MyProject/pom.xml clean install -DskipTests

2.  Create hard and/or soft filter file(s) to filter out unnecessary (e.g. external, generated, or unit test) source code, if necessary.

    Example (Windows):

        ---------- SoftFilter.txt --------
        -C:\\Users\\UserName\\MyProject\\src\\generated
        +C:\\Users\\UserName\\MyProject

    Example (Linux):

        ---------- SoftFilter.txt --------
        -/home/UserName/MyProject/src/generated
        +/home/UserName/MyProject

3.  Execute OpenStaticAnalyzer:

    Example (Windows):

        C:\Users\UserName\OpenStaticAnalyzer\Java\OpenStaticAnalyzerJava
         -projectName=MyProject
         -buildScript=MyProject\build.bat
         -resultsDir=Results
         -externalSoftFilter=SoftFilter.txt

    Example (Linux):

        ~$ OpenStaticAnalyzer/Java/OpenStaticAnalyzerJava
         -projectName=MyProject
         -buildScript=MyProject/build.sh
         -resultsDir=Results
         -externalSoftFilter=SoftFilter.txt

## Directory analysis

Execute the following command to analyze the source code of a software system:

  Example (Windows):

    OpenStaticAnalyzerJava -projectName=MyProject -projectBaseDir=MyProjectDir
    -resultsDir=Results -runFB=true -FBFileList=filelist.txt

  Example (Linux):

    OpenStaticAnalyzerJava -projectName=MyProject -projectBaseDir=MyProjectDir
    -resultsDir=Results -runFB=true -FBFileList=filelist.txt

If the directory does not contain all the source files or it uses already compiled binaries (.class files), then the precise analysis might require the compilation parameters of the standard javac Java compiler.

  Example (Windows):

    OpenStaticAnalyzerJava -projectName=MyProject -projectBaseDir=MyProjectDir
    -resultsDir=Results -javacOptions="-cp .;..\\..\\classes"

  Example (Linux):

    OpenStaticAnalyzerJava -projectName=MyProject -projectBaseDir=MyProjectDir
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

        List of the FindBugs coding rule violations in the system.

    - \$(projectName)\\java\\\$(DATE)\\\$(projectName).graph

        Binary representation of the result graph containing all the metrics, code clones and coding rule violations.

    - \$(projectName)\\java\\\$(DATE)\\\$(projectName).xml

        XML representation of the result graph containing all the metrics, code clones and coding rule violations.

    - \$(projectName)\\java\\\$(projectName).gsi

        Binary data file containing information for tracking the code clones through the consecutive revisions of the analyzed software system.

- Other files and directories created in the results directory:

    - \$(projectName)\\java\\\$(DATE)\\openstaticanalyzer

        Directory, which contains configuration, binary, ASG, log, and temporary files created during the source code analysis.

    - \$(projectName)\\java\\\$(DATE)\\openstaticanalyzer\\asg

        Directory, which contains backup copies of the linked ASG and LIM files, the corresponding filter files, and the GSI file.

    - \$(projectName)\\java\\\$(DATE)\\openstaticanalyzer\\graph

        Directory, which contains backup copies of the graph files.

    - \$(projectName)\\java\\\$(DATE)\\openstaticanalyzer\\log

        Directory, which contains the log files created during the code analysis.

    - \$(projectName)\\java\\\$(DATE)\\openstaticanalyzer\\temp

        Directory, which contains the temporary files created during the code analysis.

- Files created outside the results directory:

    - .jsi

        Java language dependent ASG file. In case of an Ant build analysis, the .jsi files are created in the .columbus_java directory located in the directory of the corresponding class files of the compiled Java source files.

    - .ljsi

        Linked Java language dependent ASG file. In case of an Ant build analysis, it is created in the .columbus_java sub-directory of the directory containing the corresponding archive file (jar, war, ear) produced by the archiver programs. In case of a Maven build analysis, it is created in the OpenStaticAnalyzer sub-directory of the "target" (unless otherwise specified in the pom file) directory. This is where the analysis automatically downloads the dependent files and from where it uploads the result jar file of this component. In case of directory analysis, one .ljsi file is created in the .columbus_java sub-directory of the directory set by the projectBaseDir parameter.

    - .fjsi

        Filter file belonging to the linked Java language dependent ASG file (.ljsi). It is created in the corresponding directory of the .ljsi file.

    - .ajsi and .apmd

        Archive files created in the OpenStaticAnalyzer directory in case of a Maven build analysis. The results of the analysis are also placed in the local Maven repository.


It is important to note that "standard parts" are not taken into consideration while creating the results. This means that e.g. when a class does not have an explicit superclass, its number of parents (and ancestors) will be 0 (zero) despite the fact that every Java class inherits implicitly from Object, which would suggest that the number will be 1. Similarly, other metrics and results also disregard "standard parts".

# Coding rule violation suppression

The warnings issued by the integrated 3^rd^ party tools (PMD, FindBugs) can be suppressed with their own official warning suppression mechanisms in case they are found to be invalid or for any other reason.

Example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {

  @SuppressWarnings("PMD")
  public void goo() {
  }

}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In this example, all PMD warnings are suppressed in the method "goo".

The warnings of the MetricHunter module cannot be suppressed at the moment.

# Demo

The Demo directory of the installation package contains the directory structure, the build and analyzer scripts for the analysis of an example project.
Version 1.2.17 and version 2.3 of the log4j open source program are included as example projects, which can also be downloaded from the following URLs:

[http://archive.apache.org/dist/logging/log4j/1.2.17/log4j-1.2.17.zip]

[http://archive.apache.org/dist/logging/log4j/1.2.17/log4j-1.2.17.zip]:http://archive.apache.org/dist/logging/log4j/1.2.17/log4j-1.2.17.zip

[http://archive.apache.org/dist/logging/log4j/2.3/apache-log4j-2.3-src.zip]

[http://archive.apache.org/dist/logging/log4j/2.3/apache-log4j-2.3-src.zip]:http://archive.apache.org/dist/logging/log4j/2.3/apache-log4j-2.3-src.zip

To perform the source code analysis of the demo project, one of the analyze-*.bat/analyze-*.sh scripts has to be executed.

Contents of the Demo directory:

Windows:

-------------  -----------------------  --------------------------------------
Demo\\
               apache-log4j-1.2.17      \# source code of log4j version 1.2.17
               apache-log4j-2.3-src     \# source code of log4j version 2.3
               build-ant.bat            \# builds log4j (Ant call)
               build-maven.bat          \# builds log4j (Maven call)
               analyze-ant.bat          \# starts OpenStaticAnalyzer in Ant build analysis mode
               analyze-maven.bat        \# starts OpenStaticAnalyzer in Maven build analysis mode
               analyze-dir.bat          \# starts OpenStaticAnalyzer in Directory analysis mode
-------------  -----------------------  --------------------------------------

Linux:

-------------  -----------------------  --------------------------------------
Demo/
               apache-log4j-1.2.17      \# source code of log4j version 1.2.17
               apache-log4j-2.3-src     \# source code of log4j version 2.3
               build-ant.sh             \# builds log4j (Ant call)
               build-maven.sh           \# builds log4j (Maven call)
               analyze-ant.sh           \# starts OpenStaticAnalyzer in Ant build analysis mode
               analyze-maven.sh         \# starts OpenStaticAnalyzer in Maven build analysis mode
               analyze-dir.sh           \# starts OpenStaticAnalyzer in Directory analysis mode
-------------  -----------------------  --------------------------------------

# Error messages

- Message: Please set the resultsDir parameter. Under this directory a new directory with the name of the analyzed project will be created, if it does not exist yet. All results will be stored there under separate directories with their names containing the date and time.

    Solution: The resultsDir parameter must be set.

- Message: Please set the projectName parameter to the name of the analyzed software system.

    Solution: The projectName parameter must be set.

- Message: Please set the buildScript or projectBaseDir parameter. The usage of buildScript is recommended.

    Solution: At least one of the buildScript or projectBaseDir parameters must be set.

- Message: Required java version is 1.8 or later

    Solution: In order to use OpenStaticAnalyzer the installation of JDK 1.8 or later version is required, and the corresponding environment variables must be set correctly.

- Message: Required Ant version is 1.8.4 or later

    Solution: To use OpenStaticAnalyzer the installation of Ant 1.8.4 or later version is required.

- Message: ASG list file does not exist: .../openstaticanalyzer/log/superlinklist.txt

    Solution 1: In case of an Ant or Maven build analysis check whether the build script calls the appropriate Ant target or Maven goal and whether any kind of archive files (jar, war, ear, etc.) is created. If not, the analyzer cannot produce the corresponding output files (.ljsi). Please modify the build script accordingly.

    Solution 2: Check if the JAVA\_HOME and PATH environment variables are set to the appropriate JDK and they do not point to some JRE. In the latter case the .../openstaticanalyzer/log/build.log file will contain an error message similar to the following:

        Unable to find a javac compiler; com.sun.tools.javac.Main is not on the classpath.
        Perhaps JAVA_HOME does not point to the JDK.

        It is currently set to "c:\Program Files\Java\jre7"

- Message: exec returned: 255

    If any of the log files in the the
    \$(projectName)\\\$(DATE)\\openstaticanalyzer\\log directory starts with "Could not load a transcoding service", then the GCONV\_PATH should be set to the current gconv directory. Check the "Requirements" section of the user's guide.

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
