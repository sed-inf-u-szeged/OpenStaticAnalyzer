/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2018 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

#ifndef _OSACPP_CONTR_PROP_H_
#define _OSACPP_CONTR_PROP_H_

#include <string>
#include <boost/filesystem/path.hpp>
#include <controller/inc/Properties.h>

enum WrapperMode {
  WM_CL,
  WM_GCC,
  WM_CLANG
};


typedef struct WrappedTool {
  bool fullpath;
  boost::filesystem::path wrappedToolName;
  boost::filesystem::path wrapperToolName;
} WrappedTool;

struct Properties : public columbus::controller::BaseProperties {
  Properties()
    : cloneGenealogy(false)
    , cloneMinLines(-1)
    , wrapperMode(
#ifdef _WIN32
      WM_CL
#else
      WM_CLANG
#endif
     )
    , csvSeparator(',')
    , csvDecimalmark('.')
    , cleanResults(-1)
    , cleanProject(false)
    , maxCan2LimThreads(0)
    , runCppcheck(true)
    , runClangTidy(true)
    , runLimMetrics(true)
    , runDCF(true)
    , runFaultHunter(true)
    , runMetricHunter(true)
    , runUDM(false)
    , runUDMExplicit(false)
    , analysisOutputDir(".columbus_cpp")
    , faultTolerantMode(true)
    , runLIM2Patterns(true)
  {}

  bool cloneGenealogy;                                // Create clone genealogy or no.
  int  cloneMinLines;

  WrapperMode wrapperMode;                            // The wrapper mode
  std::string prefix;                                 // The wrapped tool prefix which is given by the user
  std::string postfix;                                // The wrapped tool postfix which is given by the user
  std::string projectName;                            // The name of the project which is given by the user

  boost::filesystem::path startCurrentDir;            // Absolute path of the current directory when the CAC was started
  boost::filesystem::path toolchainDir;               // Absolute path of the directory of the CA toolchain
  boost::filesystem::path wrapperDir;                 // Absolute path of the directory of the wrapper inside the CA package
  boost::filesystem::path wrapperBinDir;              // Absolute path of the directory of the wrapper binaries inside the CA package
  boost::filesystem::path wrapperToolsDir;            // Absolute path of the directory of the wrapper tools inside the CA package
  boost::filesystem::path toolsDir;                   // Absolute path of the directory of the tools inside the CA package

  boost::filesystem::path profileXML;
  boost::filesystem::path rulesCSV;

  boost::filesystem::path resultsDir;                 // Absolute path of the result directory given by the user
  boost::filesystem::path buildScript;                // Absolute path of the build script given by the user
  boost::filesystem::path currentDate;                // The current date
  boost::filesystem::path projectResultDir;           // resultsDir / projectName /
  boost::filesystem::path projectTimedResultDir;      // projectResultDir / currentDate
  boost::filesystem::path projectBaseDir;             // Absolute path of the base directory given by the user
  boost::filesystem::path tempDir;                    // Absolute path of the directory of the temporary files
  boost::filesystem::path asgDir;                     // Absolute path of the directory of the asg files
  boost::filesystem::path graphDir;                   // Absolute path of the directory of the graph files
  boost::filesystem::path columbusWrapperTmpDir;      // Absolute path of the directory where the wrapper is assembled
  boost::filesystem::path columbusWrapperTmpDirName;  // Name of the directory where the wrapper is assembled (smDir / temp / wrapper)
  boost::filesystem::path externalHardFilter;         // Absolute path of the external hardfilter file
  boost::filesystem::path externalSoftFilter;         // Absolute path of the external softfilter file
  char csvSeparator;                                  // Column separator character of the csv outputs.
  char csvDecimalmark;                                // Decimal mark character in the csv outputs.
  std::string sarifSeverityLevel;                     // Severity level to be converted into sarif
  int cleanResults;                                   // Keep the last 'cleanResults' number of timestamped directory of the project in the results.
  bool cleanProject;                                  // Removes all files created outside the results directory during previous analyses, but does not remove anything from the results directory.
  bool analyzeOnly;                                   // Run the analysis only.
  int maxCan2LimThreads;                              // Number of maximum threads the Can2Lim task can use
  bool runCppcheck;                                   // Run cppcheck.
  bool runClangTidy;                                  // Run clang-tidy.
  bool runLimMetrics;                                 // Run Lim2Metrics.
  bool runDCF;                                        // Run DCF.
  bool runFaultHunter;                                // Run FaultHunter.
  bool runMetricHunter;                               // Run MetricHunter.
  bool runUDM;                                        // Run UserDefinedMetrics
  bool runUDMExplicit;                                // Was the "runUDM" switch explicitly set on the command line?
  std::string analysisOutputDir;                      // The name of the output directory (.columbus_cpp)
  bool faultTolerantMode;                             // Fault tolerant mode

  bool runSonar2Graph;                                // Run Sonar2Graph tool to extrat issues from SonarQube server.
  std::string host;                                   // IP of the SonarQube server.
  std::string port;                                   // Port of the SonarQube server.
  std::string projectKey;                             // Key of the project on the SonarQube server.
  std::string projectPrefix;                          // Prefix path of the project's base directory.
  std::string jsonPath;                               // For testing only.
  std::string sqUsername;                             // Username for the SonarQube server.
  std::string sqPassword;                             // Password for the SonarQube server.
  std::string languageKey;                            // Key of the language in SonarQube.
  bool sonar2GraphVerbose;                            // Prints more information about the running of Sonar2Graph tool.
  bool strict;                                        // If true, the tool will stop working if finds too many issues in one file.
  bool noDelayedTemplateParsing;                      // If true, -fno-delayed-template-parsing will be passed to the CAN.

  bool runLIM2Patterns;                               // Run LIM2Patterns
  std::string patternFile;                            // Location of the pattern file
  std::string whitelist;                              // Pattern whitelist, can be set from profileXML
  std::string blacklist;                              // Pattern blacklist, can be set from profileXML
};

extern Properties props;

#endif
