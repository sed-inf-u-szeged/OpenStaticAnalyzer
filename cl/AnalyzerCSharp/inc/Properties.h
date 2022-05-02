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

#ifndef _OSACSHARP_CONTR_PROP_H_
#define _OSACSHARP_CONTR_PROP_H_

#include <string>
#include <controller/inc/Properties.h>
#include <boost/filesystem/path.hpp>

struct Properties : public columbus::controller::BaseProperties
{
  Properties() : 
     cloneGenealogy(false),
     cloneMinLines(-1),
     txtoutput(true),
     csvSeparator(','),
     csvDecimalmark('.'),
     cleanResults(-1),
     analyzeOnly(false),
     runLimMetrics(true),
     runFxCop(true),
     runDCF(true),
     runMetricHunter(true),
     runUDM(false),
     runUDMExplicit(false),
     config(""),
     platform(""),
     runLIM2Patterns(true),
     runRoslynAnalyzers(true),
     restorePackages(true)
  {}

  bool cloneGenealogy;                                // Create clone genealogy or no.
  int cloneMinLines;   
  bool txtoutput;                                     //
  
  std::string projectName;                            // The name of the project which is given by the user
  std::string licenseServer;                          // URL of the license server

  boost::filesystem::path startCurrentDir;            // Absolute path of the current directory when the CA was started
  boost::filesystem::path toolchainDir;               // Absolute path of the directory of the CA toolchain
  boost::filesystem::path toolsDir;                   // Absolute path of the directory of the tools inside the CA package
  
  boost::filesystem::path profileXML;
  boost::filesystem::path rulesCSV;

  boost::filesystem::path fxcopBinaryPath;            // Absolute path of the FxCop binary
  boost::filesystem::path fxcopOutPath;               // Absolute path of the FxCop output directory
  boost::filesystem::path resultsDir;                 // Absolute path of the result directory given by the user
  boost::filesystem::path inputFile;                  // Absolute path of the solution file
  boost::filesystem::path currentDate;                // The current date
  boost::filesystem::path projectResultDir;           // resultsDir / projectName /
  boost::filesystem::path projectTimedResultDir;      // projectResultDir / currentDate
  boost::filesystem::path tempDir;                    // Absolute path of the directory of the temporary files
  boost::filesystem::path asgDir;                     // Absolute path of the directory of the asg files
  boost::filesystem::path graphDir;                   // Absolute path of the directory of the graph files
  boost::filesystem::path lcssiList;
  boost::filesystem::path externalHardFilter;         // Absolute path of the external hardfilter file
  boost::filesystem::path externalSoftFilter;         // Absolute path of the external softfilter file
  char csvSeparator;                                  // Column separator character of the csv outputs.
  char csvDecimalmark;                                // Decimal mark character in the csv outputs.
  std::string sarifSeverityLevel;                     // Severity level to be converted into sarif
  bool createStats;                                   // Invoke the tools with -stat commandline options.
  int cleanResults;                                   // Keep the last 'cleanResults' number of timestamped directory of the project in the results.
  bool analyzeOnly;                                   // Run the analysis only.
  bool runLimMetrics;                                 // Run Lim2Metrics.
  bool runFxCop;                                      // Run FxCop.
  bool runDCF;                                        // Run DCF.
  bool runMetricHunter;                               // Run MetricHunter.
  bool runUDM;                                        // Run UserDefinedMetrics
  bool runUDMExplicit;                                // Was the "runUDM" switch explicitly set on the command line?
  bool GenealogyDump;                                 // Genealogy dump
  std::string config;
  std::string platform;

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

  bool runRoslynAnalyzers;                            // Run Roslyn Analyzers
  boost::filesystem::path roslynAnalyzersOutPath;     // Absolute path of the Roslyn Analyzers output directory

  bool restorePackages;                               // Restore NuGet packages automatically
};

extern Properties props;

#endif
