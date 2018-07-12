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

#ifndef _SMCSHARP_CONTR_PROP_H_
#define _SMCSHARP_CONTR_PROP_H_

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
     runLimMetrics(true),
     runFxCop(true),
     runDCF(true),
     runMetricHunter(true),
     config(""),
     platform("")
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
  bool createStats;                                   // Invoke the tools with -stat commandline options.
  int cleanResults;                                   // Keep the last 'cleanResults' number of timestamped directory of the project in the results.
  bool runLimMetrics;                                 // Run Lim2Metrics.
  bool runFxCop;                                      // Run FxCop.
  bool runDCF;                                        // Run DCF.
  bool runMetricHunter;                               // Run MetricHunter.
  std::string config;
  std::string platform;
};

extern Properties props;

#endif
