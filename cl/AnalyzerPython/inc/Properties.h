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

#ifndef _OSAPY_PROP_H_
#define _OSAPY_PROP_H_

#include <string>
#include <list>
#include <boost/filesystem/path.hpp>
#include <controller/inc/Properties.h>

struct Properties : public columbus::controller::BaseProperties
{
  Properties()
    : cloneGenealogy(false)
    , csvSeparator(',')
    , csvDecimalmark('.')
    , cleanResults(-1)
    , cloneMinLines(-1)
    , runDCF(true)
    , runPylint(true)
    , runMetricHunter(true)
    , runLim2Metric(true)
    , runUDM(false)
    , runUDMExplicit(false)
    , runLIM2Patterns(true)
  {}

  bool cloneGenealogy;                                // Create clone genealogy or no.

  std::string projectName;                            // The name of the project which is given by the user

  boost::filesystem::path startCurrentDir;            // Absolute path of the current directory when the CAC was started
  boost::filesystem::path toolchainDir;               // Absolute path of the directory of the CA toolchain
  boost::filesystem::path toolsDir;                   // Absolute path of the directory of the tools inside the CA package
  
  boost::filesystem::path profileXML;
  boost::filesystem::path rulesCSV;
  
  boost::filesystem::path resultsDir;                 // Absolute path of the result directory given by the user
  boost::filesystem::path currentDate;                // The current date
  boost::filesystem::path projectResultDir;           // resultsDir / projectName /
  boost::filesystem::path projectTimedResultDir;      // projectResultDir / currentDate
  boost::filesystem::path projectBaseDir;             // Absolute path of the base directory given by the user
  boost::filesystem::path tempDir;                    // Absolute path of the directory of the temporary files
  boost::filesystem::path asgDir;                     // Absolute path of the directory of the asg files
  boost::filesystem::path graphDir;                   // Absolute path of the directory of the graph files
  boost::filesystem::path externalHardFilter;         // Absolute path of the external hardfilter file
  boost::filesystem::path pythonBinary;               // Path of the Python 2.7/3.x binary
  std::string pythonVersion;                          // Python version (2 or 3)
  std::list<std::string> pylintOptions;               // Options passed to Pylint
  char csvSeparator;                                  // Column separator character of the csv outputs.
  char csvDecimalmark;                                // Decimal mark character in the csv outputs.
  std::string sarifSeverityLevel;                     // Severity level to be converted into sarif
  int cleanResults;                                   // Keep the last 'cleanResults' number of timestamped directory of the project in the results.
  int cloneMinLines;                                  // Minimum number of lines of clone instances.

  bool runDCF;                                        // Run DCF.
  bool runPylint;                                     // Run Pylint2Graph
  bool runMetricHunter;                               // Run MetricHunter.
  bool runLim2Metric;                                 // Run Lim2Metric.
  bool runUDM;                                        // Run UserDefinedMetrics
  bool runUDMExplicit;                                // Was the "runUDM" switch explicitly set on the command line?

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

  bool runLIM2Patterns;                               // Run LIM2Patterns
  std::string patternFile;                            // Location of the pattern file
  std::string whitelist;                              // Pattern whitelist, can be set from profileXML
  std::string blacklist;                              // Pattern blacklist, can be set from profileXML
};

extern Properties props;

#endif
